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

#include <memory.h>
#include <db.h>

#include <errno.h>
#include <sys/stat.h>


// TOKU_TEST_FILENAME is defined in the Makefile

DB *db;
DB_ENV* dbenv;
DBC*    cursors[(int)256];
DB_TXN* null_txn = NULL;

static void
put (int _key, int _data) {
    int r;
    DBT key;
    DBT data;
    dbt_init(&key,  &_key,  sizeof(int));
    dbt_init(&data, &_data, sizeof(int));
    if (_key == -1) {
        key.data = NULL;
        key.size = 0;
    }
    if (_data == -1) {
        data.data = NULL;
        data.size = 0;
    }
    
    r = db->put(db, null_txn, &key, &data, 0);
    CKERR(r);
}

static void
cget (uint32_t flag, bool find, char txn, int _key, int _data) {
    assert(cursors[(int)txn]);

    int r;
    DBT key;
    DBT data;
    if (flag == DB_CURRENT) {
        _key++;
        _data++;
        dbt_init(&key,  &_key,  sizeof(int));
        dbt_init(&data, &_data, sizeof(int));
        _key--;
        _data--;
    }
    else if (flag == DB_SET) {
        dbt_init(&key,  &_key,  sizeof(int));
        if (_key == -1) {
            key.data = NULL;
            key.size = 0;
        }
        _data++;
        dbt_init(&data, &_data, sizeof(int));
        _data--;
    }
    else assert(false);
    r = cursors[(int)txn]->c_get(cursors[(int)txn], &key, &data, flag);
    if (find) {
        CKERR(r);
        if (_key == -1) {
            assert(key.data == NULL);
            assert(key.size == 0);
        }
        else {
            assert(key.size == sizeof(int));
            assert(*(int*)key.data == _key);
        }
        if (_data == -1) {
            assert(data.data == NULL);
            assert(data.size == 0);
        }
        else {
            assert(data.size == sizeof(int));
            assert(*(int*)data.data == _data);
        }
    }
    else        CKERR2(r, DB_NOTFOUND);
}

static void
init_dbc (char name) {
    int r;

    assert(!cursors[(int)name]);
    r = db->cursor(db, null_txn, &cursors[(int)name], 0);
        CKERR(r);
    assert(cursors[(int)name]);
}

static void
close_dbc (char name) {
    int r;

    assert(cursors[(int)name]);
    r = cursors[(int)name]->c_close(cursors[(int)name]);
        CKERR(r);
    cursors[(int)name] = NULL;
}

static void
setup_dbs (void) {
    int r;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    dbenv   = NULL;
    db      = NULL;
    /* Open/create primary */
    r = db_env_create(&dbenv, 0);
        CKERR(r);
    uint32_t env_txn_flags  = 0;
    uint32_t env_open_flags = DB_CREATE | DB_PRIVATE | DB_INIT_MPOOL;
	r = dbenv->open(dbenv, TOKU_TEST_FILENAME, env_open_flags | env_txn_flags, 0600);
        CKERR(r);
    
    r = db_create(&db, dbenv, 0);
        CKERR(r);

    char a;
    r = db->open(db, null_txn, "foobar.db", NULL, DB_BTREE, DB_CREATE, 0600);
        CKERR(r);
    for (a = 'a'; a <= 'z'; a++) init_dbc(a);
}

static void
close_dbs (void) {
    char a;
    for (a = 'a'; a <= 'z'; a++) {
        if (cursors[(int)a]) close_dbc(a);
    }

    int r;
    r = db->close(db, 0);
        CKERR(r);
    db      = NULL;
    r = dbenv->close(dbenv, 0);
        CKERR(r);
    dbenv   = NULL;
}

static void
test (void) {
    /* ********************************************************************** */
    int key;
    int data;
    int i;
    for (i = 0; i < 4; i++) {
        if (i & 0x1) key  = -1;
        else         key  = 1;
        if (i & 0x2) data = -1;
        else         data = 1;
        setup_dbs();
        put(key, data);
        cget(DB_SET,     true, 'a', key, data);
        cget(DB_CURRENT, true, 'a', key, data);
        close_dbs();
    }
    /* ********************************************************************** */
}

int
test_main(int argc, char *const argv[]) {
    parse_args(argc, argv);
    test();
    return 0;
}
