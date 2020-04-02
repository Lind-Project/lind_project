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

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <memory.h>
#include <sys/stat.h>
#include <db.h>

static void
walk (DB *db) {
    int r;
    DB_TXN * const null_txn = 0;

    DBC *cursor;
    r = db->cursor(db, null_txn, &cursor, 0); assert(r == 0);

    DBT key; memset(&key, 0, sizeof key); key.flags = DB_DBT_REALLOC;
    DBT val; memset(&val, 0, sizeof val); val.flags = DB_DBT_REALLOC;
    int i;
    for (i=0; ; i++) {
        r = cursor->c_get(cursor, &key, &val, DB_NEXT);
        if (r != 0) 
            break;
        if (verbose) printf("%d %u %u\n", i, key.size, val.size);
        if (i == 0) assert(key.size == 0);
    }
    assert(i != 0);
    r = cursor->c_close(cursor); assert(r == 0);

    if (key.data) toku_free(key.data);
    if (val.data) toku_free(val.data);
}

static void
test_insert_zero_length (int n, int dup_mode, const char *fname) {
    if (verbose) printf("test_insert_zero_length:%d %d\n", n, dup_mode);

    DB_TXN * const null_txn = 0;
    int r;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r = toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);

    /* create the dup database file */
    DB_ENV *env;
    r = db_env_create(&env, 0); assert(r == 0);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL, 0); assert(r == 0);

    DB *db;
    r = db_create(&db, env, 0); assert(r == 0);
    r = db->set_flags(db, dup_mode); assert(r == 0);
    r = db->set_pagesize(db, 4096); assert(r == 0);
    r = db->open(db, null_txn, fname, "main", DB_BTREE, DB_CREATE, 0666); assert(r == 0);

    int i;
    for (i=0; i<n; i++) {
        char k[n]; memset(k, i, n);
        char v[n]; memset(v, i, n);
        DBT key;
        DBT val;
        r = db->put(db, null_txn, dbt_init(&key, &k, i), dbt_init(&val, &v, i), 0);
        if (r != 0) {
            if (verbose) printf("db->put %d %d = %d\n", n, n, r);
            assert(r == 0);
        }
        if (i == 0) {
            dbt_init(&key, &k, i);
            memset(&val, 0, sizeof val);
            r = db->get(db, null_txn, &key, &val, 0);
            assert(r == 0 && val.data == 0 && val.size == 0);

            r = db->get(db, null_txn, &key, dbt_init_malloc(&val), 0);
            assert(r == 0 && val.data != 0 && val.size == 0);
            toku_free(val.data);

            memset(&key, 0, sizeof key);
            memset(&val, 0, sizeof val);
            r = db->get(db, null_txn, &key, &val, 0);
            assert(r == 0 && val.data == 0 && val.size == 0);

            r = db->get(db, null_txn, &key, dbt_init_malloc(&val), 0);
            assert(r == 0 && val.data != 0 && val.size == 0);
            toku_free(val.data);
        }
    }

    walk(db);

    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

static void
test_insert_zero_length_keys (int n, int dup_mode, const char *fname) {
    if (verbose) printf("test_insert_zero_length_keys:%d %d\n", n, dup_mode);

    DB_TXN * const null_txn = 0;
    int r;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r = toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);

    /* create the dup database file */
    DB_ENV *env;
    r = db_env_create(&env, 0); assert(r == 0);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL, 0); assert(r == 0);

    DB *db;
    r = db_create(&db, env, 0); assert(r == 0);
    r = db->set_flags(db, dup_mode); assert(r == 0);
    r = db->set_pagesize(db, 4096); assert(r == 0);
    r = db->open(db, null_txn, fname, "main", DB_BTREE, DB_CREATE, 0666); assert(r == 0);

    int i;
    for (i=0; i<n; i++) {
        char k[n]; memset(k, i, n);
        char v[n]; memset(v, i, n);
        DBT key;
        DBT val;
        r = db->put(db, null_txn, dbt_init(&key, &k, 0), dbt_init(&val, &v, i), 0);
        if (r != 0) {
            if (verbose) printf("db->put %d %d = %d\n", n, n, r);
            assert(r == 0);
        }
    }

    walk(db);

    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

int
test_main(int argc, char *const argv[]) {

    parse_args(argc, argv);
  
#define TFILE __FILE__ ".tktrace"
    unlink(TFILE);
    SET_TRACE_FILE(TFILE);

    test_insert_zero_length(32, 0, "test0");
    test_insert_zero_length_keys(32, 0, "test0keys");

    CLOSE_TRACE_FILE();

    return 0;
}
