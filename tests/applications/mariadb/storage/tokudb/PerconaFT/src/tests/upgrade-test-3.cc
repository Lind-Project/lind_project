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

// Purpose of this test is to verify that dictionaries created with 4.2.0
// can be properly truncated with PerconaFT version 5.x or later.


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
int NUM_DBS=5;
int NUM_ROWS=100000;
int CHECK_RESULTS=0;
int SRC_VERSION = 4;
int littlenode = 0;

#define OLDDATADIR "../../../../tokudb.data/"

char *env_dir = TOKU_TEST_FILENAME; // the default env_dir.
char *db_v5_dir = "dir.preload-db.c.tdb";
char *db_v4_dir        = OLDDATADIR "env_preload.4.2.0.cleanshutdown";
char *db_v4_dir_node4k = OLDDATADIR "env_preload.4.2.0.node4k.cleanshutdown";


static void upgrade_test_3(DB **dbs) {
    int r = 0;
    char name[MAX_NAME*2];

    // truncate, verify, close, open, verify again
    DBC *cursor;
    DB_TXN * txn;
    DBT desc;
    int idx[MAX_DBS];

    dbt_init(&desc, "foo", sizeof("foo"));

    for(int i=0;i<NUM_DBS;i++) {
	idx[i] = i;
	r = db_create(&dbs[i], env, 0);                                                                       CKERR(r);
	dbs[i]->app_private = &idx[i];
	snprintf(name, sizeof(name), "db_%04x", i);
	r = dbs[i]->open(dbs[i], NULL, name, NULL, DB_BTREE, DB_CREATE, 0666);                                CKERR(r);
    IN_TXN_COMMIT(env, NULL, txn_desc, 0, {
            { int chk_r = dbs[i]->change_descriptor(dbs[i], txn_desc, &desc, 0); CKERR(chk_r); }
    });

	r = env->txn_begin(env, NULL, &txn, DB_SERIALIZABLE);
	CKERR(r);

	// truncate the tree
	uint32_t row_count = 0;
	r = dbs[i]->truncate(dbs[i], 0, &row_count, 0); assert(r == 0);

	// walk the tree - expect 0 rows
	int rowcount = 0;
	r = dbs[i]->cursor(dbs[i], txn, &cursor, 0); 
	CKERR(r);
	while (1) {
	    DBT key, val;
	    r = cursor->c_get(cursor, dbt_init(&key, 0, 0), dbt_init(&val, 0, 0), DB_NEXT);
	    if (r == DB_NOTFOUND) break;
	    rowcount++;
	}
	r = cursor->c_close(cursor); 
	CKERR(r);
	assert(rowcount == 0);

	r = txn->commit(txn, 0);
	CKERR(r);
	    
	r = dbs[i]->close(dbs[i], 0); assert(r == 0);

	r = db_create(&dbs[i], env, 0); assert(r == 0);
	snprintf(name, sizeof(name), "db_%04x", i);
	r = dbs[i]->open(dbs[i], NULL, name, NULL, DB_BTREE, DB_CREATE, 0666);                                CKERR(r);

	// open new txn and walk the tree again - expect 0 rows

	r = env->txn_begin(env, NULL, &txn, DB_SERIALIZABLE);
	CKERR(r);
	    
	rowcount = 0;
	r = dbs[i]->cursor(dbs[i], txn, &cursor, 0); assert(r == 0);
	while (1) {
	    DBT key, val;
	    r = cursor->c_get(cursor, dbt_init(&key, 0, 0), dbt_init(&val, 0, 0), DB_NEXT);
	    if (r == DB_NOTFOUND) break;
	    rowcount++;
	}
	r = cursor->c_close(cursor); assert(r == 0);
	assert(rowcount == 0);

	r = txn->commit(txn, 0);
	CKERR(r);

	r = dbs[i]->close(dbs[i], 0); 
	CKERR(r);
	    
	dbs[i] = NULL;
    }

}


static void setup(void) {
    int r;
    int len = 256;
    char syscmd[len];
    char * src_db_dir;

    if ( SRC_VERSION == 4 ) {
	if (littlenode)
	    src_db_dir = db_v4_dir_node4k;
	else
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

}

static void run_test(int checkpoint_period) 
{
    int r;

    r = db_env_create(&env, 0);                                                                               CKERR(r);
    if (littlenode) {
	r = env->set_cachesize(env, 0, 512*1024, 1);                                                              CKERR(r); 
    }
    r = env->set_redzone(env, 0);                                                                             CKERR(r);
    int envflags = DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_MPOOL | DB_INIT_TXN | DB_CREATE | DB_PRIVATE;
    r = env->open(env, env_dir, envflags, S_IRWXU+S_IRWXG+S_IRWXO);                                            CKERR(r);
    env->set_errfile(env, stderr);
    r = env->checkpointing_set_period(env, checkpoint_period);                                                  CKERR(r);

    DB **dbs = (DB**)toku_malloc(sizeof(DB*) * NUM_DBS);
    assert(dbs != NULL);

    // --------------------------
    upgrade_test_3(dbs);
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
    if (SRC_VERSION == 4) {
	littlenode = 1;  // 4k nodes, small cache
    }
    setup();
    run_test(1);
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
	    fprintf(stderr, "Usage: -h -d <num_dbs> -V <version> %s\n", cmd);
	    exit(resultcode);
        } else if (strcmp(argv[0], "-d")==0) {
            argc--; argv++;
            NUM_DBS = atoi(argv[0]);
            if ( NUM_DBS > MAX_DBS ) {
                fprintf(stderr, "max value for -d field is %d\n", MAX_DBS);
                resultcode=1;
                goto do_usage;
            }
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
