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
test_insert_delete_insert (void) {
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);

    if (verbose) printf("test_insert_delete_insert:\n");

    DB_TXN * const null_txn = 0;
    const char * const fname = "test.cursor.insert.delete.insert.ft_handle";

    /* create the dup database file */
    DB_ENV *env;
    r = db_env_create(&env, 0); assert(r == 0);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL, 0); assert(r == 0);

    DB *db;
    r = db_create(&db, env, 0); assert(r == 0);
    r = db->open(db, null_txn, fname, "main", DB_BTREE, DB_CREATE, 0666); assert(r == 0);

    DBC *cursor;
    r = db->cursor(db, null_txn, &cursor, 0); assert(r == 0);

    int k = htonl(1), v = 2;
    DBT key, val;

    r = db->put(db, null_txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), 0); 
    assert(r == 0);

    r = cursor->c_get(cursor, dbt_init(&key, &k, sizeof k), dbt_init_malloc(&val), DB_SET); 
    assert(r == 0);
    toku_free(val.data);

    r = db->del(db, null_txn, &key, DB_DELETE_ANY); assert(r == 0);
    assert(r == 0);

    r = cursor->c_get(cursor, dbt_init_malloc(&key), dbt_init_malloc(&val), DB_CURRENT);
    assert(r == DB_KEYEMPTY);
    if (key.data) toku_free(key.data);
    if (val.data) toku_free(val.data);

    r = db->put(db, null_txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), 0); 
    assert(r == 0);

    r = cursor->c_get(cursor, dbt_init_malloc(&key), dbt_init_malloc(&val), DB_CURRENT);
    assert(r == 0);
    if (key.data) toku_free(key.data);
    if (val.data) toku_free(val.data);

    r = cursor->c_close(cursor); assert(r == 0);

    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

int
test_main(int argc, char *const argv[]) {

    parse_args(argc, argv);
  
    test_insert_delete_insert();

    return 0;
}
