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

#include "test.h"
#include "toku_pthread.h"
#include <db.h>
#include <sys/stat.h>

static const char *envdir = TOKU_TEST_FILENAME;

DB_ENV *env;
int DISALLOW_PUTS=0;
int COMPRESS=0;
enum {MAX_NAME=128};
enum {NUM_DBS=1};
enum {NUM_KV_PAIRS=3};
struct kv_pair {
    int64_t key;
    int64_t val;
};
struct kv_pair kv_pairs[NUM_KV_PAIRS] = {{1,4},
                                         {2,5},
                                         {3,6}};
static uint32_t block_size = 0;

static int put_multiple_generate(DB *dest_db, DB *src_db, DBT_ARRAY *dest_keys, DBT_ARRAY *dest_vals, const DBT *src_key, const DBT *src_val) {
    toku_dbt_array_resize(dest_keys, 1);
    toku_dbt_array_resize(dest_vals, 1);
    DBT *dest_key = &dest_keys->dbts[0];
    DBT *dest_val = &dest_vals->dbts[0];
    dest_key->flags = 0;
    dest_val->flags = 0;

    (void) src_db;

    uint32_t which = *(uint32_t*)dest_db->app_private;
    assert(which == 0);

    dbt_init(dest_key, src_key->data, src_key->size);
    dbt_init(dest_val, src_val->data, src_val->size);

//    printf("dest_key.data = %d\n", *(int*)dest_key->data);
//    printf("dest_val.data = %d\n", *(int*)dest_val->data);

    return 0;
}

static void test_loader(DB **dbs)
{
    int r;
    DB_TXN    *txn;
    DB_LOADER *loader;
    uint32_t db_flags[NUM_DBS];
    uint32_t dbt_flags[NUM_DBS];
    for(int i=0;i<NUM_DBS;i++) {
        db_flags[i] = DB_NOOVERWRITE;
        dbt_flags[i] = 0;
    }
    uint32_t loader_flags = DISALLOW_PUTS | COMPRESS; // set with -p or -c option

    // create and initialize loader
    r = env->txn_begin(env, NULL, &txn, 0);
    CKERR(r);
    r = env->create_loader(env, txn, &loader, dbs[0], NUM_DBS, dbs, db_flags, dbt_flags, loader_flags);
    CKERR(r);
    r = loader->set_error_callback(loader, NULL, NULL);
    CKERR(r);
    r = loader->set_poll_function(loader, NULL, NULL);
    CKERR(r);

    uint64_t before_puts = toku_test_get_latest_lsn(env);
    // using loader->put, put values into DB
    DBT key, val;
    for(int i=0;i<NUM_KV_PAIRS;i++) {
        dbt_init(&key, &kv_pairs[i].key, sizeof(kv_pairs[i].key));
        dbt_init(&val, &kv_pairs[i].val, sizeof(kv_pairs[i].val));
        r = loader->put(loader, &key, &val);
        if (DISALLOW_PUTS) {
            CKERR2(r, EINVAL);
        } else {
            CKERR(r);
        }
    }
    uint64_t after_puts = toku_test_get_latest_lsn(env);
    assert(before_puts == after_puts);

    // close the loader
    r = loader->close(loader);
    CKERR(r);
    r = txn->commit(txn, 0);
    CKERR(r);

    // verify the DBs
    DBC *cursor;
    r = env->txn_begin(env, NULL, &txn, 0);
    CKERR(r);

    for(int j=0;j<NUM_DBS;j++) {
        r = dbs[j]->cursor(dbs[j], txn, &cursor, 0);
        CKERR(r);
        for(int i=0;i<NUM_KV_PAIRS;i++) {
            r = cursor->c_get(cursor, &key, &val, DB_NEXT);
	    if (r!=0) { fprintf(stderr, "r==%d, failure\n", r); }
            if (DISALLOW_PUTS) {
                CKERR2(r, DB_NOTFOUND);
            } else {
                CKERR(r);
                assert(*(int64_t*)key.data == kv_pairs[i].key);
                assert(*(int64_t*)val.data == kv_pairs[i].val);
            }
        }
        cursor->c_close(cursor);
    }
    r = txn->commit(txn, 0);
    CKERR(r);

    if ( verbose ) printf("PASS\n");
}

static void run_test(void) 
{
    int r;
    char rmcmd[32 + strlen(envdir)];
    snprintf(rmcmd, sizeof rmcmd, "rm -rf %s", envdir);
    r = system(rmcmd);                                                                             CKERR(r);
    r = toku_os_mkdir(envdir, S_IRWXU+S_IRWXG+S_IRWXO);                                                       CKERR(r);
    char logdir[8 + strlen(envdir)];
    snprintf(logdir, sizeof logdir, "%s/log", envdir);
    r = toku_os_mkdir(logdir, S_IRWXU+S_IRWXG+S_IRWXO);
    CKERR(r);

    r = db_env_create(&env, 0);                                                                               CKERR(r);
    r = env->set_lg_dir(env, "log");
    CKERR(r);
    r = env->set_default_bt_compare(env, int64_dbt_cmp);                                                      CKERR(r);
    r = env->set_generate_row_callback_for_put(env, put_multiple_generate);
    CKERR(r);
//    int envflags = DB_INIT_LOCK | DB_INIT_MPOOL | DB_INIT_TXN | DB_CREATE | DB_PRIVATE | DB_INIT_LOG;
    int envflags = DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_MPOOL | DB_INIT_TXN | DB_CREATE | DB_PRIVATE | DB_INIT_LOG;
    r = env->open(env, envdir, envflags, S_IRWXU+S_IRWXG+S_IRWXO);                                            CKERR(r);
    env->set_errfile(env, stderr);
    //Disable auto-checkpointing
    r = env->checkpointing_set_period(env, 0);                                                                CKERR(r);

    DBT desc;
    dbt_init(&desc, "foo", sizeof("foo"));
    char name[MAX_NAME*2];

    DB *dbs[NUM_DBS];
    int idx[NUM_DBS];
    for(int i=0;i<NUM_DBS;i++) {
        idx[i] = i;
        r = db_create(&dbs[i], env, 0);                                                                       CKERR(r);
        dbs[i]->app_private = &idx[i];
        if (block_size != 0) {
            r = dbs[i]->set_pagesize(dbs[i], block_size); CKERR(r);
        }
        snprintf(name, sizeof(name), "db_%04x", i);
        r = dbs[i]->open(dbs[i], NULL, name, NULL, DB_BTREE, DB_CREATE, 0666);                                CKERR(r);
        IN_TXN_COMMIT(env, NULL, txn_desc, 0, {
                { int chk_r = dbs[i]->change_descriptor(dbs[i], txn_desc, &desc, 0); CKERR(chk_r); }
        });
    }

    // -------------------------- //
    test_loader(dbs);
    // -------------------------- //

    for(int i=0;i<NUM_DBS;i++) {
        dbs[i]->close(dbs[i], 0);                                                                             CKERR(r);
        dbs[i] = NULL;
    }
    r = env->close(env, 0);                                                                                   CKERR(r);
}

// ------------ infrastructure ----------
static void do_args(int argc, char * const argv[]);

int test_main(int argc, char * const *argv) {
    do_args(argc, argv);
    run_test();
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
	    fprintf(stderr, "Usage:\n%s\n", cmd);
	    exit(resultcode);
        } else if (strcmp(argv[0], "-p")==0) {
            DISALLOW_PUTS = LOADER_DISALLOW_PUTS;
        } else if (strcmp(argv[0], "-z")==0) {
            COMPRESS = LOADER_COMPRESS_INTERMEDIATES;
        } else if (strcmp(argv[0], "--block_size") == 0) {
            argc--; argv++;
            block_size = atoi(argv[0]);
        } else if (strcmp(argv[0], "-e") == 0) {
            argc--; argv++;
            if (argc > 0)
                envdir = argv[0];
	} else {
	    fprintf(stderr, "Unknown arg: %s\n", argv[0]);
	    resultcode=1;
	    goto do_usage;
	}
	argc--;
	argv++;
    }
}
