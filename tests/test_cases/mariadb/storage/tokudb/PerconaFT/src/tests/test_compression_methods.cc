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

/*
 * Test that different compression methods can be used.
 */

#include <db.h>
#include "test.h"

static const int VAL_SIZE = 248;
static const int NUM_ROWS = 1 << 12;

static int
insert(DB_ENV *env, DB *db, void *UU(extra))
{
    assert(VAL_SIZE%sizeof(int)==0);
    int val[VAL_SIZE/sizeof(int)];
    memset(val, 0, sizeof val);
    DB_TXN *txn;
    int r = env->txn_begin(env, 0, &txn, 0);
    CKERR(r);
    for (int i = 0; i < NUM_ROWS; ++i) {
        DBT k, v;
        val[0] = i;
        r = db->put(db, txn, dbt_init(&k, &i, sizeof i), dbt_init(&v, val, sizeof val), 0);
        CKERR(r);
    }
    r = txn->commit(txn, 0);
    CKERR(r);
    return 0;
}

static int
lookup(DB_ENV *env, DB *db, void *UU(extra))
{
    DB_TXN *txn;
    int r = env->txn_begin(env, 0, &txn, 0);
    CKERR(r);
    for (int i = 0; i < NUM_ROWS; ++i) {
        DBT k, v;
        r = db->get(db, txn, dbt_init(&k, &i, sizeof i), dbt_init(&v, NULL, 0), 0);
        CKERR(r);
        assert(v.size == (size_t) VAL_SIZE);
        assert(*(int *) v.data == i);
    }
    r = txn->commit(txn, 0);
    CKERR(r);
    return 0;
}

typedef int (*db_callback)(DB_ENV *env, DB *db, void *extra);
static int
with_open_db(db_callback cb, void *cb_extra, bool set_method, enum toku_compression_method method)
{
    DB_ENV *env;
    DB *db;
    int r;
    r = db_env_create(&env, 0);
    CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO);
    CKERR(r);
    r = db_create(&db, env, 0);
    CKERR(r);
    {
        DB_TXN *txn;
        r = env->txn_begin(env, 0, &txn, 0);
        CKERR(r);
        if (set_method) {
            r = db->set_compression_method(db, method);
            CKERR(r);
        }
        r = db->open(db, txn, "foo.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO);
        CKERR(r);
        r = txn->commit(txn, 0);
        CKERR(r);
    }

    {
        enum toku_compression_method saved_method;
        r = db->get_compression_method(db, &saved_method);
        CKERR(r);
        assert(saved_method == method);
    }

    int cr = cb(env, db, cb_extra);

    r = db->close(db, 0);
    CKERR(r);
    r = env->close(env, 0);
    CKERR(r);

    return cr;
}

static void
run_test(enum toku_compression_method method)
{
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r = toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    CKERR(r);

    r = with_open_db(insert, NULL, true, method);
    CKERR(r);
    r = with_open_db(lookup, NULL, false, method);
    CKERR(r);
}

int
test_main(int argc, char *const argv[])
{
    parse_args(argc, argv);
    run_test(TOKU_NO_COMPRESSION);
    run_test(TOKU_ZLIB_METHOD);
    run_test(TOKU_ZLIB_WITHOUT_CHECKSUM_METHOD);
    run_test(TOKU_QUICKLZ_METHOD);
    run_test(TOKU_LZMA_METHOD);
    return 0;
}
