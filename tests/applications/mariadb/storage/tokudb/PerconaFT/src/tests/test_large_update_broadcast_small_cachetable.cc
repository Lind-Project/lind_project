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

// This test sets the cache size to be small and then inserts enough data
// to make some basement nodes get evicted.  Then sends a broadcast update
// and checks all the data.  If the msns for evicted basement nodes and
// leaf nodes are not managed properly, this test should fail (because the
// broadcast message will not be applied to basement nodes being brought
// back in).

#include "test.h"

const int envflags = DB_INIT_MPOOL|DB_CREATE|DB_THREAD |DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_TXN|DB_PRIVATE;

DB_ENV *env;

const unsigned int NUM_KEYS = (1<<17);
const unsigned int MAGIC_EXTRA = 0x4ac0ffee;

const char original_data[] = "original: ha.rpbkasrkcabkshtabksraghpkars3cbkarpcpktkpbarkca.hpbtkvaekragptknbnsaotbknotbkaontekhba";
const char updated_data[]  = "updated: crkphi30bi8a9hpckbrap.k98a.pkrh3miachpk0[alr3s4nmubrp8.9girhp,bgoekhrl,nurbperk8ochk,bktoe";

static int update_fun(DB *UU(db),
                      const DBT *UU(key),
                      const DBT *old_val, const DBT *extra,
                      void (*set_val)(const DBT *new_val,
                                      void *set_extra),
                      void *set_extra) {
    unsigned int *e;
    assert(extra->size == sizeof(*e));
    CAST_FROM_VOIDP(e, extra->data);
    assert(*e == MAGIC_EXTRA);
    assert(old_val->size == sizeof(original_data));
    assert(memcmp(old_val->data, original_data, sizeof(original_data)) == 0);

    {
        DBT newval;
        set_val(dbt_init(&newval, updated_data, sizeof(updated_data)), set_extra);
    }

    return 0;
}

static int
int_cmp(DB *UU(db), const DBT *a, const DBT *b) {
    unsigned int *ap, *bp;
    assert(a->size == sizeof(*ap));
    CAST_FROM_VOIDP(ap, a->data);
    assert(b->size == sizeof(*bp));
    CAST_FROM_VOIDP(bp, b->data);
    return (*ap > *bp) - (*ap < *bp);
}

static void setup (void) {
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    { int chk_r = toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(chk_r); }
    { int chk_r = db_env_create(&env, 0); CKERR(chk_r); }
    env->set_errfile(env, stderr);
    env->set_update(env, update_fun);
    env->set_cachesize(env, 0, 10*(1<<20), 1);
    { int chk_r = env->set_default_bt_compare(env, int_cmp); CKERR(chk_r); }
    { int chk_r = env->open(env, TOKU_TEST_FILENAME, envflags, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(chk_r); }
}

static void cleanup (void) {
    { int chk_r = env->close(env, 0); CKERR(chk_r); }
}

static int do_inserts(DB_TXN *txn, DB *db) {
    int r = 0;
    DBT key, val;
    unsigned int i;
    DBT *keyp = dbt_init(&key, &i, sizeof(i));
    DBT *valp = dbt_init(&val, original_data, sizeof(original_data));
    for (i = 0; i < NUM_KEYS; ++i) {
        r = db->put(db, txn, keyp, valp, 0); CKERR(r);
    }
    return r;
}

static int do_updates(DB_TXN *txn, DB *db) {
    DBT extra;
    unsigned int e = MAGIC_EXTRA;
    DBT *extrap = dbt_init(&extra, &e, sizeof(e));
    int r = db->update_broadcast(db, txn, extrap, 0); CKERR(r);
    return r;
}

static int do_verify_results(DB_TXN *txn, DB *db) {
    int r = 0;
    DBT key, val;
    unsigned int i;
    DBT *keyp = dbt_init(&key, &i, sizeof(i));
    DBT *valp = dbt_init(&val, NULL, 0);
    for (i = 0; i < NUM_KEYS; ++i) {
        r = db->get(db, txn, keyp, valp, 0); CKERR(r);
        assert(val.size == sizeof(updated_data));
        assert(memcmp(val.data, updated_data, sizeof(updated_data)) == 0);
    }
    return r;
}

static int run_test(bool shutdown_before_update, bool shutdown_before_verify) {
    setup();

    DB *db;

    { int chk_r = db_create(&db, env, 0); CKERR(chk_r); }
    db->set_pagesize(db, 256*1024);
    IN_TXN_COMMIT(env, NULL, txn_1, 0, {
            { int chk_r = db->open(db, txn_1, "foo.db", NULL, DB_BTREE, DB_CREATE, 0666); CKERR(chk_r); }

            { int chk_r = do_inserts(txn_1, db); CKERR(chk_r); }
        });

    if (shutdown_before_update) {
        { int chk_r = db->close(db, 0); CKERR(chk_r); }
        { int chk_r = db_create(&db, env, 0); CKERR(chk_r); }
        IN_TXN_COMMIT(env, NULL, txn_reopen, 0, {
                { int chk_r = db->open(db, txn_reopen, "foo.db", NULL, DB_BTREE, DB_CREATE, 0666); CKERR(chk_r); }
            });
    }

    IN_TXN_COMMIT(env, NULL, txn_2, 0, {
            { int chk_r = do_updates(txn_2, db); CKERR(chk_r); }
        });

    if (shutdown_before_verify) {
        { int chk_r = db->close(db, 0); CKERR(chk_r); }
        { int chk_r = db_create(&db, env, 0); CKERR(chk_r); }
        IN_TXN_COMMIT(env, NULL, txn_reopen, 0, {
                { int chk_r = db->open(db, txn_reopen, "foo.db", NULL, DB_BTREE, DB_CREATE, 0666); CKERR(chk_r); }
            });
    }

    IN_TXN_COMMIT(env, NULL, txn_3, 0, {
            { int chk_r = do_verify_results(txn_3, db); CKERR(chk_r); }
        });

    { int chk_r = db->close(db, 0); CKERR(chk_r); }

    cleanup();

    return 0;
}

int test_main(int argc, char * const argv[]) {
    parse_args(argc, argv);

    run_test(false, false);
    run_test(false, true);
    run_test(true, false);
    run_test(true, true);

    return 0;
}
