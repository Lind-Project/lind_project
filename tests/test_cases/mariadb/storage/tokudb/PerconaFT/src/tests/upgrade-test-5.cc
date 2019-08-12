/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// vim: ft=cpp:expandtab:ts=8:sw=4:softtabstop=4:
#ident "$Id$"
/*======
This file is part of PerconaFT.


Copyright (c) 2006, 2015, Percona and/or its affiliates. All rights reserved.

    PerconaFT is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2,
    as published by the Free Software Foundation.

    PerconaFT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PerconaFT.  If not, see <http://www.gnu.org/licenses/>.

----------------------------------------

    PerconaFT is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License, version 3,
    as published by the Free Software Foundation.

    PerconaFT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with PerconaFT.  If not, see <http://www.gnu.org/licenses/>.
======= */

#ident "Copyright (c) 2006, 2015, Percona and/or its affiliates. All rights reserved."

#define kv_pair_funcs 1 // pull in kv_pair generators from test.h

#include "test.h"
#include "toku_pthread.h"
#include <db.h>
#include <sys/stat.h>
#include "ydb-internal.h"

#include "test_kv_gen.h"

/*
 */

DB_ENV *env;
enum {MAX_NAME=128};
int NUM_DBS=1;
int NUM_ROWS=100000;
int SRC_VERSION = 4;

#define MAXDEPTH 64
#define OLDDATADIR "../../../../tokudb.data/"

char *env_dir = TOKU_TEST_FILENAME; // the default env_dir.
char *db_v5_dir = "dir.preload-db-nested.c.tdb";
char *db_v4_dir        = OLDDATADIR "env_preload.4.2.0.nested.cleanshutdown";


static void
check_results_nested(DB ** dbs, const uint num_rows) {
    int num_dbs = 1;  // maybe someday increase
    for(int j=0;j<num_dbs;j++){
        DBT key, val;
        unsigned int k=0, v=0;
        dbt_init(&key, &k, sizeof(unsigned int));
        dbt_init(&val, &v, sizeof(unsigned int));
        int r;

        DB_TXN *txn;
        r = env->txn_begin(env, NULL, &txn, 0);
        CKERR(r);

        DBC *cursor;
        r = dbs[j]->cursor(dbs[j], txn, &cursor, 0);
        CKERR(r);
        for(uint i=0;i<num_rows;i++) {
            if (i % MAXDEPTH) {
		r = cursor->c_get(cursor, &key, &val, DB_NEXT);    
		CKERR(r);
		uint observed_k = *(unsigned int*)key.data;
		uint observed_v = *(unsigned int*)val.data;
		uint expected_k = i;
		uint generated_value = generate_val(i, 0);
		uint expected_v = generated_value + (i%MAXDEPTH - 1);
		if (verbose >= 3)
		    printf("expected key %d, observed key %d, expected val %d, observed val %d\n", 
			   expected_k, observed_k, expected_v, observed_v);
		// test that we have the expected keys and values
		assert(observed_k == expected_k);
		assert(observed_v == expected_v);
	    }
            dbt_init(&key, NULL, sizeof(unsigned int));
            dbt_init(&val, NULL, sizeof(unsigned int));
	    if ( verbose && (i%10000 == 0)) {printf("."); fflush(stdout);}
        }
        r = cursor->c_close(cursor);
        CKERR(r);
        r = txn->commit(txn, 0);
        CKERR(r);
    }
    if ( verbose ) {printf("ok");fflush(stdout);}
}


static void upgrade_test_1(DB **dbs) {
    int r;
    // open the DBS
    {
        DBT desc;
        dbt_init(&desc, "foo", sizeof("foo"));
        char name[MAX_NAME*2];

        int idx[MAX_DBS];
        for(int i=0;i<NUM_DBS;i++) {
            idx[i] = i;
            r = db_create(&dbs[i], env, 0);                                                                       CKERR(r);
            dbs[i]->app_private = &idx[i];
            snprintf(name, sizeof(name), "db_%04x", i);
            r = dbs[i]->open(dbs[i], NULL, name, NULL, DB_BTREE, DB_CREATE, 0666);                                CKERR(r);
            IN_TXN_COMMIT(env, NULL, txn_desc, 0, {
                    { int chk_r = dbs[i]->change_descriptor(dbs[i], txn_desc, &desc, 0); CKERR(chk_r); }
            });
        }
    }

    // read and verify all rows
    {
        if ( verbose ) {printf("checking");fflush(stdout);}
        check_results_nested(&dbs[0], NUM_ROWS);
        if ( verbose) {printf("\ndone\n");fflush(stdout);}
    }
    // close
    {
        for(int i=0;i<NUM_DBS;i++) {
            dbs[i]->close(dbs[i], 0);                                                                             CKERR(r);
            dbs[i] = NULL;
        }
    }
}

static void setup(void) {
    int r;
    int len = 256;
    char syscmd[len];
    char * src_db_dir;

    if ( SRC_VERSION == 4 ) {
	src_db_dir = db_v4_dir;
    }
    else if ( SRC_VERSION == 5 ) {
        src_db_dir = db_v5_dir;
    }
    else {
        fprintf(stderr, "unsupported PerconaFT version %d to upgrade\n", SRC_VERSION);
        assert(0);
    }

    r = snprintf(syscmd, len, "rm -rf %s", env_dir);
    assert(r<len);
    r = system(syscmd);                                                                                  
    CKERR(r);
    
    r = snprintf(syscmd, len, "cp -r %s %s", src_db_dir, env_dir);
    assert(r<len);
    r = system(syscmd);                                                                                 
    CKERR(r);
    generate_permute_tables();

}

static void run_test(void) 
{
    int r;
    r = db_env_create(&env, 0);                                                                               CKERR(r);
    r = env->set_default_bt_compare(env, uint_dbt_cmp);                                                       CKERR(r);
    r = env->set_cachesize(env, 0, 512*1024, 1);                                                              CKERR(r); 
    r = env->set_redzone(env, 0);                                                                             CKERR(r);
    int envflags = DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_MPOOL | DB_INIT_TXN | DB_CREATE | DB_PRIVATE;
    r = env->open(env, env_dir, envflags, S_IRWXU+S_IRWXG+S_IRWXO);                                           CKERR(r);
    env->set_errfile(env, stderr);
    r = env->checkpointing_set_period(env, 1);                                                                CKERR(r);

    DB **dbs = (DB**)toku_malloc(sizeof(DB*) * NUM_DBS);
    assert(dbs != NULL);

    // --------------------------
    upgrade_test_1(dbs);
    // --------------------------

    if (verbose >= 2)
	print_engine_status(env);
    r = env->close(env, 0);                                                                                   CKERR(r);
    toku_free(dbs);

}

// ------------ infrastructure ----------
static void do_args(int argc, char * const argv[]);

int test_main(int argc, char * const *argv) {
    do_args(argc, argv);
    setup();
    run_test();  // read, upgrade, write back to disk
    run_test();  // read and verify
    return 0;
}

static void do_args(int argc, char * const argv[]) {
    int resultcode;
    char *cmd = argv[0];
    argc--; argv++;
    
    while (argc>0) {
	if (strcmp(argv[0], "-v")==0) {
	    verbose++;
	} else if (strcmp(argv[0],"-q")==0) {
	    verbose--;
	    if (verbose<0) verbose=0;
        } else if (strcmp(argv[0], "-h")==0) {
	    resultcode=0;
	do_usage:
	    fprintf(stderr, "Usage: -h -r <num_rows> %s\n", cmd);
	    exit(resultcode);
        } else if (strcmp(argv[0], "-r")==0) {
            argc--; argv++;
            NUM_ROWS = atoi(argv[0]);
        } else if (strcmp(argv[0], "-V")==0) {
            argc--; argv++;
            SRC_VERSION = atoi(argv[0]);
	} else {
	    fprintf(stderr, "Unknown arg: %s\n", argv[0]);
	    resultcode=1;
	    goto do_usage;
	}
	argc--;
	argv++;
    }
}
