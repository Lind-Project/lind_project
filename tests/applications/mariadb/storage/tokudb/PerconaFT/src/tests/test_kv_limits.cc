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


static uint64_t lorange = 0;
static uint64_t hirange = 1<<24;
static uint32_t pagesize = 0;

static void test_key_size_limit (void) {
    if (verbose > 1) printf("%s\n", __FUNCTION__);

    DB_TXN * const null_txn = 0;
    const char * const fname = "test.rand.insert.ft_handle";
    int r;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r=toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO); assert(r==0);

    DB_ENV *env;
    r = db_env_create(&env, 0); assert(r == 0);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL, 0); assert(r == 0);

    DB *db;
    r = db_create(&db, env, 0);
    assert(r == 0);
    if (pagesize) {
        r = db->set_pagesize(db, pagesize); assert(r == 0);
    }
    r = db->open(db, null_txn, fname, "main", DB_BTREE, DB_CREATE, 0666);
    assert(r == 0);

    void *k = 0;
    void *v = 0;
    uint32_t lo = lorange, mi = 0, hi = hirange;
    uint32_t bigest = 0;
    while (lo <= hi) {
        mi = lo + (hi - lo) / 2;
        assert(lo <= mi && mi <= hi);
        uint32_t ks = mi;
        if (verbose > 1) printf("trying %u %u %u ks=%u\n", lo, mi, hi, ks);
        k = toku_realloc(k, ks); assert(k);
        memset(k, 0, ks);
        memcpy(k, &ks, sizeof ks);
        uint32_t vs = sizeof (uint32_t);
        v = toku_realloc(v, vs); assert(v);
        memset(v, 0, vs);
        memcpy(v, &vs, sizeof vs);
        DBT key, val;
        r = db->put(db, null_txn, dbt_init(&key, k, ks), dbt_init(&val, v, vs), 0);
        if (r == 0) {
            bigest = mi;
            lo = mi+1;
        } else {
            if (verbose > 1) printf("%u too big\n", ks);
            hi = mi-1;
        }
    }
    toku_free(k);
    toku_free(v);
    assert(bigest > 0);
    if (verbose) printf("%s bigest %u\n", __FUNCTION__, bigest);

    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

static void test_data_size_limit (void) {
    if (verbose > 1) printf("%s\n", __FUNCTION__);

    DB_TXN * const null_txn = 0;
    const char * const fname = "test.rand.insert.ft_handle";
    int r;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r=toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO); assert(r==0);

    DB_ENV *env;
    r = db_env_create(&env, 0); assert(r == 0);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL, 0); assert(r == 0);

    DB *db;
    r = db_create(&db, env, 0);
    assert(r == 0);
    if (pagesize) {
        r = db->set_pagesize(db, pagesize); assert(r == 0);
    }
    r = db->open(db, null_txn, fname, "main", DB_BTREE, DB_CREATE, 0666);
    assert(r == 0);

    void *k = 0;
    void *v = 0;
    uint32_t lo = lorange, mi = 0, hi = hirange;
    uint32_t bigest = 0;
    while (lo <= hi) {
        mi = lo + (hi - lo) / 2;
        assert(lo <= mi && mi <= hi);
        uint32_t ks = sizeof (uint32_t);
        if (verbose > 1) printf("trying %u %u %u ks=%u\n", lo, mi, hi, ks);
        k = toku_realloc(k, ks); assert(k);
        memset(k, 0, ks);
        memcpy(k, &ks, sizeof ks);
        uint32_t vs = mi;
        v = toku_realloc(v, vs); assert(v);
        memset(v, 0, vs);
        memcpy(v, &vs, sizeof vs);
        DBT key, val;
        r = db->put(db, null_txn, dbt_init(&key, k, ks), dbt_init(&val, v, vs), 0);
        if (r == 0) {
            bigest = mi;
            lo = mi+1;
        } else {
            if (verbose > 1) printf("%u too big\n", vs);
            hi = mi-1;
        }
    }
    toku_free(k);
    toku_free(v);
    if (verbose && bigest > 0) printf("%s bigest %u\n", __FUNCTION__, bigest);

    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

int
test_main(int argc, char *const argv[]) {
    int do_key = 1;
    int do_data = 1;
    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        if (strcmp(arg, "-v") == 0) {
            verbose++;
            continue;
        }
        if (strcmp(arg, "-lorange") == 0 && i+1 < argc) {
            lorange = strtoull(argv[++i], 0, 10);
            if (lorange > ULLONG_MAX)
                return 2;
            continue;
        }
        if (strcmp(arg, "-hirange") == 0 && i+1 < argc) {
            hirange = strtoull(argv[++i], 0, 10);
            if (hirange > ULLONG_MAX)
                return 2;
            continue;
        }
        if (strcmp(arg, "-pagesize") == 0 && i+1 < argc) {
            pagesize = atoi(argv[++i]);
            continue;
        }
        if (strcmp(arg, "-nokey") == 0) {
            do_key = 0;
            continue;
        }
        if (strcmp(arg, "-nodata") == 0) {
            do_data = 0;
            continue;
        }
    }

    if (do_key)
        test_key_size_limit();
    if (do_data)
        test_data_size_limit();

    return 0;
}
