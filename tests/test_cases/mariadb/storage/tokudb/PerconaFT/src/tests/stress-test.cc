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

enum state {
    UNTOUCHED = 0,
    INSERTED,
    DELETED
};
struct pair {
    DBT key, val;
    enum state state;
};

#define NKEYS (1<<20)
#define NDELS (1<<17)

int keys[NKEYS];
struct pair pairs[NKEYS];
struct pair sorted[NKEYS];
int dels[NDELS];

char some_data[200] = ("abetefocebbrk3894d,h"
                       "tebe73t90htb349i83d4"
                       "h3498bk4onhaosnetkb0"
                       "bk934bkgpbk0,8kh4c.r"
                       "bk9,438k4bkr,09k8hkb"
                       "bk9,gr,gkhb,k9,.bkg,"
                       "b4kg4,39k,3k890,.bkr"
                       "bugk349kc,b.rk,.0k8,"
                       "bkreb,0k8.p,k,r,bkhr"
                       "kb.rpgxbeu0xcehu te");

static int
pair_cmp(const void *a, const void *b)
{
    const struct pair *CAST_FROM_VOIDP(p1, a);
    const struct pair *CAST_FROM_VOIDP(p2, b);
    if (p1->key.size < p2->key.size) {
        int c = memcmp(p1->key.data, p2->key.data, p1->key.size);
        if (!c) {
            return -1;
        }
        return c;
    } else if (p1->key.size > p2->key.size) {
        int c = memcmp(p1->key.data, p2->key.data, p2->key.size);
        if (!c) {
            return 1;
        }
        return c;
    } else {
        return memcmp(p1->key.data, p2->key.data, p1->key.size);
    }
}

static void
gen_data(void)
{
    srandom(0);
    for (int i = 0; i < NKEYS; ++i) {
        keys[i] = htonl(i);
    }
    for (int e = NKEYS-1; e > 0; --e) {
        int r = random() % e;
        int t = keys[r];
        keys[r] = keys[e];
        keys[e] = t;
    }
    for (int i = 0; i < NKEYS; ++i) {
        int vallen = random() % 150;
        int idx = random() % (200 - vallen);
        dbt_init(&pairs[i].key, &keys[i], sizeof keys[i]);
        dbt_init(&pairs[i].val, &some_data[idx], vallen);
        pairs[i].state = UNTOUCHED;
    }

    for (int i = 0; i < NDELS; ) {
        int idx = random() % NKEYS;
        if (pairs[idx].state != DELETED) {
            dels[i++] = idx;
            pairs[idx].state = DELETED;
        }
    }
    for (int i = 0; i < NDELS; ++i) {
        pairs[dels[i]].state = UNTOUCHED;
    }
}

static void
run_test(DB *db)
{
    DB_TXN * const null_txn = 0;
    int p = 0, d = 0;
    for (int cursz = NKEYS / 10; cursz <= NKEYS; cursz += NKEYS / 10) {
        // insert a chunk
        for (; p < cursz; ++p) {
            // put an element in
            invariant(pairs[p].state == UNTOUCHED);
            { int chk_r = db->put(db, null_txn, &pairs[p].key, &pairs[p].val, 0); CKERR(chk_r); }
            pairs[p].state = INSERTED;
            // delete everything we can so far, in the given order
            for (; d < NDELS && dels[d] <= p; ++d) {
                invariant(pairs[dels[d]].state == INSERTED);
                { int chk_r = db->del(db, null_txn, &pairs[dels[d]].key, 0); CKERR(chk_r); }
                pairs[dels[d]].state = DELETED;
            }
        }

        // get what the data should be
        memcpy(sorted, pairs, cursz * (sizeof pairs[0]));
        qsort(sorted, cursz, sizeof sorted[0], pair_cmp);

        // verify the data

        // with point queries
        if ((random() % 10) < 5) {
            for (int i = 0; i < cursz; ++i) {
                DBT val; dbt_init(&val, NULL, 0);
                invariant(sorted[i].state != UNTOUCHED);
                int r = db->get(db, null_txn, &sorted[i].key, &val, 0);
                if (sorted[i].state == INSERTED) {
                    CKERR(r);
                    assert(val.size == sorted[i].val.size);
                    assert(memcmp(val.data, sorted[i].val.data, val.size) == 0);
                } else {
                    CKERR2(r, DB_NOTFOUND);
                }
            }
	}

        // with a forward traversal
        if ((random() % 10) < 5) {
            DBC *cur;
            { int chk_r = db->cursor(db, null_txn, &cur, 0); CKERR(chk_r); }
            DBT ck, cv; dbt_init(&ck, NULL, 0); dbt_init(&cv, NULL, 0);
            int i, r;
            r = cur->c_get(cur, &ck, &cv, DB_FIRST);
            CKERR(r);
            for (i = 0;
                 r == 0 && i < cursz;
                 r = cur->c_get(cur, &ck, &cv, DB_NEXT), ++i) {
                invariant(sorted[i].state != UNTOUCHED);
                while (i < cursz && sorted[i].state == DELETED) {
                    i++;
                    invariant(sorted[i].state != UNTOUCHED);
                }
                invariant(i < cursz);
                assert(ck.size == sorted[i].key.size);
                assert(memcmp(ck.data, sorted[i].key.data, ck.size) == 0);
                assert(cv.size == sorted[i].val.size);
                assert(memcmp(cv.data, sorted[i].val.data, cv.size) == 0);
            }
            while (i < cursz && sorted[i].state == DELETED) {
                i++;
                invariant(sorted[i].state != UNTOUCHED);
            }
            assert(i == cursz);
            assert(r == DB_NOTFOUND);
        }

        // with a backward traversal
        if ((random() % 10) < 5) {
            DBC *cur;
            { int chk_r = db->cursor(db, null_txn, &cur, 0); CKERR(chk_r); }
            DBT ck, cv; dbt_init(&ck, NULL, 0); dbt_init(&cv, NULL, 0);
            int i, r;
            r = cur->c_get(cur, &ck, &cv, DB_LAST);
            CKERR(r);
            for (i = cursz - 1;
                 r == 0 && i >= 0;
                 r = cur->c_get(cur, &ck, &cv, DB_PREV), --i) {
                invariant(sorted[i].state != UNTOUCHED);
                while (i >= 0 && sorted[i].state == DELETED) {
                    i--;
                    invariant(sorted[i].state != UNTOUCHED);
                }
                invariant(i >= 0);
                assert(ck.size == sorted[i].key.size);
                assert(memcmp(ck.data, sorted[i].key.data, ck.size) == 0);
                assert(cv.size == sorted[i].val.size);
                assert(memcmp(cv.data, sorted[i].val.data, cv.size) == 0);
            }
            while (i >= 0 && sorted[i].state == DELETED) {
                i--;
                invariant(sorted[i].state != UNTOUCHED);
            }
            assert(i == -1);
            assert(r == DB_NOTFOUND);
        }
    }
}

static void
init_db(DB_ENV **env, DB **db)
{
    DB_TXN * const null_txn = 0;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    { int chk_r = toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(chk_r); }
    { int chk_r = db_env_create(env, 0); CKERR(chk_r); }
    (*env)->set_errfile(*env, stderr);
    { int chk_r = (*env)->open(*env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL, 0); CKERR(chk_r); }
    { int chk_r = db_create(db, *env, 0); CKERR(chk_r); }
    { int chk_r = (*db)->open(*db, null_txn, "test.stress.ft_handle", "main",
                              DB_BTREE, DB_CREATE, 0666); CKERR(chk_r); }
}

static void
destroy_db(DB_ENV *env, DB *db)
{
    { int chk_r = db->close(db, 0); CKERR(chk_r); }
    { int chk_r = env->close(env, 0); CKERR(chk_r); }
}

int
test_main(int argc, char * const argv[])
{
    DB_ENV *env;
    DB *db;

    parse_args(argc, argv);
    gen_data();
    init_db(&env, &db);
    run_test(db);
    destroy_db(env, db);

    return 0;
}
