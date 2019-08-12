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
#include <db.h>
#include <sys/stat.h>

static DB_ENV *env;
static DB *db;
DB_TXN *txn;

const int num_insert = 25000;

static void
setup (void) {
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r=toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);       CKERR(r);

    r=db_env_create(&env, 0); CKERR(r);
    r=env->set_redzone(env, 0); CKERR(r);
    r=env->set_default_bt_compare(env, int_dbt_cmp); CKERR(r);
    env->set_errfile(env, stderr);
    
    r=env->open(env, TOKU_TEST_FILENAME, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r=db_create(&db, env, 0); CKERR(r);

    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    r=db->open(db, txn, "foo.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r=txn->commit(txn, 0);    assert(r==0);
}

static void
test_shutdown (void) {
    int r;
    r= db->close(db, 0); CKERR(r);
    r= env->close(env, 0); CKERR(r);
}

static void
doit (bool committed_provdels) {
    DBT key,data;
    DBC *dbc;
    int r;
    int i;
    int j;

    r=env->txn_begin(env, 0, &txn, 0); CKERR(r);
    for (i = 0; i < num_insert; i++) {
        j = (i<<1) + 37;
        r=db->put(db, txn, dbt_init(&key, &i, sizeof(i)), dbt_init(&data, &j, sizeof(j)), 0);
    }
    r=txn->commit(txn, 0);    CKERR(r);
    r=env->txn_begin(env, 0, &txn, 0); CKERR(r);
    r = db->cursor(db, txn, &dbc, 0);                           CKERR(r);
    for (i = 0; i < num_insert; i++) {
        j = (i<<1) + 37;
        r = dbc->c_get(dbc, &key, &data, DB_NEXT); CKERR(r);
        assert(*(int*)key.data == i);
        assert(*(int*)data.data == j);
        r = db->del(db, txn, &key, DB_DELETE_ANY); CKERR(r);
    }
    r = dbc->c_get(dbc, &key, &data, DB_NEXT); CKERR2(r, DB_NOTFOUND);
    r = dbc->c_get(dbc, &key, &data, DB_FIRST); CKERR2(r, DB_NOTFOUND);
    if (committed_provdels) {
        r = dbc->c_close(dbc);                                      CKERR(r);
        r=txn->commit(txn, 0);    CKERR(r);
        r=env->txn_begin(env, 0, &txn, 0); CKERR(r);
        r = db->cursor(db, txn, &dbc, 0);                           CKERR(r);
    }
    int ifirst, ilast, jfirst, jlast;
    ilast=2*num_insert;
    jlast=(ilast<<1)+37;
    ifirst=-1*num_insert;
    jfirst=(ifirst<<1)+37;
    r=db->put(db, txn, dbt_init(&key, &ifirst, sizeof(ifirst)), dbt_init(&data, &jfirst, sizeof(jfirst)), 0);
    CKERR(r);
    r=db->put(db, txn, dbt_init(&key, &ilast, sizeof(ilast)), dbt_init(&data, &jlast, sizeof(jlast)), 0);
    CKERR(r);

    r = dbc->c_get(dbc, dbt_init(&key, NULL, 0), dbt_init(&data, NULL, 0), DB_FIRST); CKERR(r);
    assert(*(int*)key.data == ifirst);
    assert(*(int*)data.data == jfirst);
    r = dbc->c_get(dbc, dbt_init(&key, NULL, 0), dbt_init(&data, NULL, 0), DB_NEXT); CKERR(r);
    assert(*(int*)key.data == ilast);
    assert(*(int*)data.data == jlast);
    r = dbc->c_get(dbc, dbt_init(&key, NULL, 0), dbt_init(&data, NULL, 0), DB_LAST); CKERR(r);
    assert(*(int*)key.data == ilast);
    assert(*(int*)data.data == jlast);
    r = dbc->c_get(dbc, dbt_init(&key, NULL, 0), dbt_init(&data, NULL, 0), DB_PREV); CKERR(r);
    assert(*(int*)key.data == ifirst);
    assert(*(int*)data.data == jfirst);
    r = dbc->c_close(dbc);                                      CKERR(r);
    r=txn->commit(txn, 0);    CKERR(r);
}

int
test_main (int argc, char * const argv[]) {
    parse_args(argc, argv);

    setup();
    doit(true);
    test_shutdown();
    setup();
    doit(false);
    test_shutdown();

    return 0;
}

