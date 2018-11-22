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
db_put (DB *db, int k, int v) {
    DB_TXN * const null_txn = 0;
    DBT key, val;
    int r = db->put(db, null_txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), 0);
    assert(r == 0);
}

static void
db_del (DB *db, int k) {
    DB_TXN * const null_txn = 0;
    DBT key;
    int r = db->del(db, null_txn, dbt_init(&key, &k, sizeof k), 0);
    assert(r == 0);
}

static void
expect_db_get (DB *db, int k, int v) {
    DB_TXN * const null_txn = 0;
    DBT key, val;
    int r = db->get(db, null_txn, dbt_init(&key, &k, sizeof k), dbt_init_malloc(&val), 0);
    assert(r == 0);
    int vv;
    assert(val.size == sizeof vv);
    memcpy(&vv, val.data, val.size);
    assert(vv == v);
    toku_free(val.data);
}

static void
expect_cursor_get (DBC *cursor, int k, int v) {
    DBT key, val;
    int r = cursor->c_get(cursor, dbt_init_malloc(&key), dbt_init_malloc(&val), DB_NEXT);
    assert(r == 0);
    assert(key.size == sizeof k);
    int kk;
    memcpy(&kk, key.data, key.size);
    assert(val.size == sizeof v);
    int vv;
    memcpy(&vv, val.data, val.size);
    if (kk != k || vv != v) printf("expect key %u got %u - %u %u\n", (uint32_t)htonl(k), (uint32_t)htonl(kk), (uint32_t)htonl(v), (uint32_t)htonl(vv));
    assert(kk == k);
    assert(vv == v);

    toku_free(key.data);
    toku_free(val.data);
}

static void
expect_cursor_set (DBC *cursor, int k, int expectr) {
    DBT key, val;
    int r = cursor->c_get(cursor, dbt_init(&key, &k, sizeof k), dbt_init_malloc(&val), DB_SET);
    assert(r == expectr);
    if (val.data) toku_free(val.data);
}

static void
expect_cursor_get_current (DBC *cursor, int k, int v) {
    DBT key, val;
    int r = cursor->c_get(cursor, dbt_init_malloc(&key), dbt_init_malloc(&val), DB_CURRENT);
    assert(r == 0);
    int kk, vv;
    assert(key.size == sizeof kk); memcpy(&kk, key.data, key.size); assert(kk == k);
    assert(val.size == sizeof vv); memcpy(&vv, val.data, val.size); assert(vv == v);
    toku_free(key.data); toku_free(val.data);
}


/* insert, close, delete, insert, search */
static void
test_icdi_search (int n, int dup_mode) {
    if (verbose) printf("test_icdi_search:%d %d\n", n, dup_mode);

    DB_TXN * const null_txn = 0;
    const char * const fname = "test_icdi_search.ft_handle";
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
        int k = htonl(i);
        int v = htonl(i);
        db_put(db, k, v);

        expect_db_get(db, k, v);
    } 

    /* reopen the database to force nonleaf buffering */
    r = db->close(db, 0); assert(r == 0);
    r = db_create(&db, env, 0); assert(r == 0);
    r = db->set_flags(db, dup_mode); assert(r == 0);
    r = db->set_pagesize(db, 4096); assert(r == 0);
    r = db->open(db, null_txn, fname, "main", DB_BTREE, 0, 0666); assert(r == 0);

    for (i=0; i<n; i++)
        db_del(db, htonl(i));

    {
    DBC *cursor;
    r = db->cursor(db, 0, &cursor, 0); assert(r == 0);
    expect_cursor_set(cursor, 0, DB_NOTFOUND);
    r = cursor->c_close(cursor); assert(r == 0);
    }

    for (i=0; i<n; i++) {
        int k = htonl(i);
        int v = htonl(n+i);
        db_put(db, k, v);

        DBC *cursor;
        r = db->cursor(db, 0, &cursor, 0); assert(r == 0);
        expect_cursor_set(cursor, k, 0);
        expect_cursor_get_current(cursor, k, v);
        r = cursor->c_close(cursor); assert(r == 0);
    } 

    DBC *cursor;
    r = db->cursor(db, null_txn, &cursor, 0); assert(r == 0);

    for (i=0; i<n; i++) {
        expect_cursor_get(cursor, htonl(i), htonl(n+i));
    }

    r = cursor->c_close(cursor); assert(r == 0);

    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}


int
test_main(int argc, char *const argv[]) {
    int i;

    parse_args(argc, argv);
  
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);

    for (i=1; i<65537; i *= 2) {
        test_icdi_search(i, 0);
    }
    return 0;
}
