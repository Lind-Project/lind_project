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
expect_cursor_get (DBC *cursor, int k, int v, int op) {
    int kk, vv;
    DBT key, val;
    int r = cursor->c_get(cursor, dbt_init_malloc(&key), dbt_init_malloc(&val), op);
    assert(r == 0); 
    assert(key.size == sizeof kk); memcpy(&kk, key.data, key.size); assert(kk == k); toku_free(key.data); 
    assert(val.size == sizeof vv); memcpy(&vv, val.data, val.size); assert(vv == v); toku_free(val.data);
}

static DBC *
new_cursor (DB *db, int k, int v, int op) {
    DBC *cursor;
    int r;
    r = db->cursor(db, 0, &cursor, 0); assert(r == 0);
    expect_cursor_get(cursor, k, v, op);
    return cursor;
}

static int
db_put (DB *db, int k, int v) {
    DBT key, val;
    int r = db->put(db, 0, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), 0);
    return r;
}

static void
test_cursor_nonleaf_expand (int n, int reverse) {
    if (verbose) printf("test_cursor_nonleaf_expand:%d %d\n", n, reverse);

    DB_TXN * const null_txn = 0;
    const char * const fname = "test.insert.ft_handle";
    int r;

    // toku_os_recursive_delete(TOKU_TEST_FILENAME);
    // r = toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);

    /* create the dup database file */
    DB_ENV *env;
    r = db_env_create(&env, 0); assert(r == 0);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL, 0); assert(r == 0);

    DB *db;
    r = db_create(&db, env, 0); assert(r == 0);
    r = db->set_pagesize(db, 4096); assert(r == 0);
    r = db->open(db, null_txn, fname, "main", DB_BTREE, DB_CREATE, 0666); assert(r == 0);
    
    r = db_put(db, htonl(0), 0); assert(r == 0);
    DBC *cursor0 = new_cursor(db, htonl(0), 0, DB_FIRST); assert(cursor0);
    r = db_put(db, htonl(n), n); assert(r == 0);
    DBC *cursorn = new_cursor(db, htonl(n), n, DB_LAST); assert(cursorn);

    int i;
    if (reverse) {
        for (i=n-1; i > 0; i--) {
            r = db_put(db, htonl(i), i); assert(r == 0);
        }
    } else {
        for (i=1; i < n; i++) {
            r = db_put(db, htonl(i), i); assert(r == 0);
        } 
    }

    expect_cursor_get(cursor0, htonl(0), 0, DB_CURRENT);
    expect_cursor_get(cursorn, htonl(n), n, DB_CURRENT);

    r = cursor0->c_close(cursor0); assert(r == 0);
    r = cursorn->c_close(cursorn); assert(r == 0);
    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

int
test_main(int argc, char *const argv[]) {
    parse_args(argc, argv);

    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r=toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO); assert(r==0);

    int i;
    for (i=1; i<=65536; i *= 2) {
        test_cursor_nonleaf_expand(i, 0);
        test_cursor_nonleaf_expand(i, 1);
    }

    return 0;
}
