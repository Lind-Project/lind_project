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

// verify that the tree create time is retuned in db->stat64

#include "test.h"

#include <db.h>
#include <sys/stat.h>

static void
test_stat64_create_time (uint64_t n) {
    if (verbose) printf("%s:%u\n", __FUNCTION__, __LINE__);

    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    
    DB_ENV *env = NULL;
    r = db_env_create(&env, 0);                                           CKERR(r);

    r = env->set_cachesize(env, 0, 20*1000000, 1);
    r = env->open(env, TOKU_TEST_FILENAME, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);

    DB *db = NULL;
    r = db_create(&db, env, 0);                                           CKERR(r);

    DB_TXN *txn = NULL;
    r = env->txn_begin(env, 0, &txn, 0); assert(r == 0);

    r = db->set_pagesize(db, 4096); assert(r == 0);
    r = db->open(db, txn, "foo.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);

    // initial stats
    DB_BTREE_STAT64 s0;
    r = db->stat64(db, txn, &s0); assert(r == 0);
    printf("initial stat create %" PRIu64 "\n", s0.bt_create_time_sec);
    assert(s0.bt_create_time_sec != 0);
    assert(s0.bt_modify_time_sec == s0.bt_create_time_sec);
    r = txn->commit(txn, 0);    assert(r == 0);

    // stats after create is committed
    r = env->txn_begin(env, 0, &txn, 0);  CKERR(r);
    DB_BTREE_STAT64 s1;
    r = db->stat64(db, txn, &s1); assert(r == 0);
    assert(s1.bt_create_time_sec == s0.bt_create_time_sec);
    assert(s1.bt_modify_time_sec == s0.bt_modify_time_sec);
    r = txn->commit(txn, 0);    assert(r == 0);

    // stats after checkpoint
    sleep(10);
    r = env->txn_checkpoint(env, 0, 0, 0); assert(r == 0);
    r = env->txn_begin(env, 0, &txn, 0);  CKERR(r);
    DB_BTREE_STAT64 s2;
    r = db->stat64(db, txn, &s2); assert(r == 0);
    assert(s2.bt_create_time_sec == s1.bt_create_time_sec);
    assert(s2.bt_modify_time_sec > s1.bt_modify_time_sec);
    r = txn->commit(txn, 0);    assert(r == 0);

    // stats after insertion
    DB_BTREE_STAT64 s3;
    assert(n > 0);
    for (uint64_t i = 0; i < n; i++) {
        r = env->txn_begin(env, 0, &txn, 0);  CKERR(r);
        DBT key, val;
        r = db->put(db, txn, dbt_init(&key, &i, sizeof i), dbt_init(&val, &i, sizeof i), 0);
        r = db->stat64(db, txn, &s3); assert(r == 0);
        assert(s3.bt_create_time_sec == s2.bt_create_time_sec);
        assert(s3.bt_modify_time_sec == s2.bt_modify_time_sec);
        r = txn->commit(txn, 0);    assert(r == 0);
    }

    // stats after checkpoint
    sleep(10);
    r = env->txn_checkpoint(env, 0, 0, 0); assert(r == 0);
    r = env->txn_begin(env, 0, &txn, 0);  CKERR(r);
    DB_BTREE_STAT64 s4;
    r = db->stat64(db, txn, &s4); assert(r == 0);
    assert(s4.bt_create_time_sec == s3.bt_create_time_sec);
    assert(s4.bt_modify_time_sec > s3.bt_modify_time_sec);
    r = txn->commit(txn, 0);    assert(r == 0);

    r = db->close(db, 0); CKERR(r);

    r = env->close(env, 0); CKERR(r);
}

int
test_main (int argc, char *const argv[]) {
    parse_args(argc, argv);
    test_stat64_create_time(1);
    test_stat64_create_time(1000);
    return 0;
}
