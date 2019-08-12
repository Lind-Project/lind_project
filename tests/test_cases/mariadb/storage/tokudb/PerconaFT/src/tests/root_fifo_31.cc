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

// test txn commit after db close

#include "test.h"
#include <sys/stat.h>

DB_ENV *null_env = NULL;
DB *null_db = NULL;
DB_TXN *null_txn = NULL;
DBC *null_cursor = NULL;

static void create_non_empty(int n) {
    DB_ENV *env = null_env;
    int r;
    r = db_env_create(&env, 0); assert(r == 0); assert(env != NULL);
    r = env->open(env, 
		  TOKU_TEST_FILENAME,
                  DB_INIT_MPOOL+DB_INIT_LOG+DB_INIT_LOCK+DB_INIT_TXN+DB_PRIVATE+DB_CREATE, 
                  S_IRWXU+S_IRWXG+S_IRWXO); 
    assert(r == 0);

    DB_TXN *txn = null_txn;
    r = env->txn_begin(env, null_txn, &txn, 0); assert(r == 0); assert(txn != NULL);

    DB *db = null_db;
    r = db_create(&db, env, 0); assert(r == 0); assert(db != NULL);

    r = db->open(db, txn, "test.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); 
    assert(r == 0);

    int i;
    for (i=n; i<2*n; i++) {
        DBT key, val;
        int k = toku_htonl(i);
        r = db->put(db, txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &i, sizeof i), 0);
        assert(r == 0);
    }

    r = db->close(db, 0); assert(r == 0); db = null_db;

    r = txn->commit(txn, 0); assert(r == 0); txn = null_txn;

    r = env->close(env, 0); assert(r == 0); env = null_env;
}

static void root_fifo_verify(DB_ENV *env, int n) {
    if (verbose) printf("%s:%d %d\n", __FUNCTION__, __LINE__, n);

    int r;

    DB_TXN *txn = null_txn;
    r = env->txn_begin(env, null_txn, &txn, 0); assert(r == 0); assert(txn != NULL);
    DB *db = null_db;
    r = db_create(&db, env, 0); assert(r == 0); assert(db != NULL);
    r = db->open(db, txn, "test.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); 
    assert(r == 0);

    DBC *cursor = null_cursor;
    r = db->cursor(db, txn, &cursor, 0); assert(r == 0);
    int i;
    for (i = 0; ; i++) {
        DBT key, val;
        memset(&key, 0, sizeof key); memset(&val, 0, sizeof val);
        r = cursor->c_get(cursor, &key, &val, DB_NEXT);
        if (r != 0) break;
        int k;
        assert(key.size == sizeof k);
        memcpy(&k, key.data, key.size);
        assert((int)toku_ntohl(k) == i);
    }
    assert(i == 2*n);

    r = cursor->c_close(cursor); assert(r == 0); cursor = null_cursor;
    
    r = txn->commit(txn, 0); assert(r == 0); txn = null_txn;

    r = db->close(db, 0); assert(r == 0); db = null_db;
}

static void root_fifo_31(int n) {
    if (verbose) printf("%s:%d %d\n", __FUNCTION__, __LINE__, n);
    int r;

    // create the env
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);

    // populate
    create_non_empty(n);

    DB_ENV *env = null_env;
    r = db_env_create(&env, 0); assert(r == 0); assert(env != NULL);
    r = env->open(env, 
                  TOKU_TEST_FILENAME, 
                  DB_INIT_MPOOL+DB_INIT_LOG+DB_INIT_LOCK+DB_INIT_TXN+DB_PRIVATE+DB_CREATE, 
                  S_IRWXU+S_IRWXG+S_IRWXO); 
    assert(r == 0);

    DB_TXN *txn = null_txn;
    r = env->txn_begin(env, null_txn, &txn, 0); assert(r == 0); assert(txn != NULL);

    int i;
    for (i=0; i<n; i++) {
        DB *db = null_db;
        r = db_create(&db, env, 0); assert(r == 0); assert(db != NULL);

        r = db->open(db, txn, "test.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); 
        assert(r == 0);

        DBT key, val;
        int k = toku_htonl(i);
        r = db->put(db, txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &i, sizeof i), 0);
        assert(r == 0);

        r = db->close(db, 0); assert(r == 0); db = null_db;
    }

    r = txn->commit(txn, 0); assert(r == 0); txn = null_txn;

    // verify the db
    root_fifo_verify(env, n);

    // cleanup
    r = env->close(env, 0); assert(r == 0); env = null_env;
}

int test_main(int argc, char *const argv[]) {
    int i;
    int n = -1;

    // parse_args(argc, argv);
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
            continue;
        }
        if (strcmp(argv[i], "-n") == 0) {
            if (i+1 < argc)
                n = atoi(argv[++i]);
            continue;
        }
    }
              
    if (n >= 0)
        root_fifo_31(n);
    else 
        for (i=0; i<100; i++)
            root_fifo_31(i);
    return 0;
}

