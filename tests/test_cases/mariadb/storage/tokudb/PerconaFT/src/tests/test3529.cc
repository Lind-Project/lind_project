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

/* Test for #3522.    Show that even with DB_TRYAGAIN, isolation still works.
 * Strategy:
 *  1. Create a tree (with relatively small nodes so things happen quickly, and relatively large compared to the cache).
 *  2. Start two transactions YY and XX.
 *  3. Force XX to precede YY (e.g., XX reads the last row, and then YY deletes it, under MVCC).
 *  4. YY, in a single transaction: deletes everything
 *  5. YY does do a DB_FIRST.
 *     Set things up so that while YY is doing it's retries, XX inserts a row at the beginning.
 *  Make the test terminate by capturing the calls to pread(). */

#include "test.h"
#include <portability/toku_atomic.h>

static DB_ENV *env;
static DB *db;
const int N = 1000;
static DB_TXN *XX, *YY;

long do_XX_on_pread = -1;
const int n_preads_limit = 1000;
long n_preads = 0;

static void insert(int i, DB_TXN *txn);

static ssize_t my_pread (int fd, void *buf, size_t count, off_t offset) {
    long n_read_so_far = toku_sync_fetch_and_add(&n_preads, 1);
    if (do_XX_on_pread==n_read_so_far && XX != NULL) {
	// we're supposed to do the XX operation now.  Insert a row.
	printf("Did XX\n");
	insert(0, XX);
    }
    if (n_read_so_far > n_preads_limit) {
	if (verbose) fprintf(stderr, "Apparent infinite loop detected\n");
	abort();
    }
    return pread(fd, buf, count, offset);
}

static void
insert(int i, DB_TXN *txn)
{
    char hello[30], there[30];
    snprintf(hello, sizeof(hello), "hello%04d", i);
    snprintf(there, sizeof(there), "there%d", i);
    DBT key, val;
    if (db) {
    int r=db->put(db, txn,
		  dbt_init(&key, hello, strlen(hello)+1),
		  dbt_init(&val, there, strlen(there)+1),
		  0);
    CKERR(r);
    }
}

static void op_delete (int i, DB_TXN *x) {
    char hello[30];
    DBT key;
    if (verbose>1) printf("op_delete %d\n", i);
    snprintf(hello, sizeof(hello), "hello%04d", i);
    int r = db->del(db, x,
		    dbt_init(&key,  hello, strlen(hello)+1),
		    0);
    CKERR(r);
}

int did_nothing = 0;

static int
do_nothing(DBT const *UU(a), DBT  const *UU(b), void *UU(c)) {
    did_nothing++;
    return 0;
}


static void
setup (void) {
    db = NULL;
    db_env_set_func_pread(my_pread);
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    r = db_env_create(&env, 0);                                                       CKERR(r);
    r = env->set_redzone(env, 0);                                                     CKERR(r);
    r = env->set_cachesize(env, 0, 2*128*1024, 1);                                      CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r = db_create(&db, env, 0);                                                       CKERR(r);
    r = db->set_pagesize(db, 4096);                                                   CKERR(r);
    {
	DB_TXN *txn;
	r = env->txn_begin(env, 0, &txn, 0);                                              CKERR(r);
	r = db->open(db, txn, "foo.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
	r = txn->commit(txn, 0);                                                          CKERR(r);
    }
    {
	DB_TXN *txn;
	r = env->txn_begin(env, 0, &txn, 0);                                              CKERR(r);
	for (int i=0; i<N; i++) insert(i+1, txn);
	r = txn->commit(txn, 0);                                                          CKERR(r);
    }
    r = env->txn_begin(env, 0, &XX, DB_TXN_SNAPSHOT);                                     CKERR(r);
    r = env->txn_begin(env, 0, &YY, DB_TXN_SNAPSHOT);                                     CKERR(r);

    // Force XX to preceed YY by making XX read something.  (YY will op_delete everything in a moment).
    {
	DBC *cursor;
	r = db->cursor(db, XX, &cursor, 0);                                               CKERR(r);
	did_nothing = 0;
	//r = cursor->c_getf_next(cursor, 0, do_nothing, NULL);                             CKERR(r);
	//assert(did_nothing==1);
	did_nothing = 0;
	r = cursor->c_close(cursor);                                                      CKERR(r);
    }
}

static void finish (void) {
    int r;
    r = YY->commit(YY, 0);                                                            CKERR(r);
    YY = NULL;
    r = XX->commit(XX, 0);                                                            CKERR(r);
    XX = NULL;
    r = db->close(db, 0);                                                             CKERR(r);
    r = env->close(env, 0);                                                           CKERR(r);
}


static void run_del_next (void) {
    DBC *cursor;
    int r;
    for (int i=0; i<N; i++) op_delete(i+1, YY);

    r = db->cursor(db, YY, &cursor, 0);                                               CKERR(r);
    if (verbose) printf("read_next\n");
    n_preads = 0;
    do_XX_on_pread = 2;
    printf("doing on %ld\n", do_XX_on_pread);
    r = cursor->c_getf_next(cursor, 0, do_nothing, NULL);                             CKERR2(r, DB_NOTFOUND);
    do_XX_on_pread = 0;
    assert(did_nothing==0);
    if (verbose) printf("n_preads=%ld\n", n_preads);
    r = cursor->c_close(cursor);                                                      CKERR(r);
}

static void run_del_prev (void) {
    DBC *cursor;
    int r;
    for (int i=0; i<N; i++) op_delete(i+1, YY);

    r = db->cursor(db, YY, &cursor, 0);                                               CKERR(r);
    if (verbose) printf("read_prev\n");
    n_preads = 0;
    r = cursor->c_getf_prev(cursor, 0, do_nothing, NULL);                             CKERR2(r, DB_NOTFOUND);
    assert(did_nothing==0);
    if (verbose) printf("n_preads=%ld\n", n_preads);
    r = cursor->c_close(cursor);                                                      CKERR(r);
}

static void run_test (void) {
    setup();
    run_del_next();
    finish();

    setup();
    run_del_prev();
    finish();
}
int test_main (int argc, char*const argv[]) {
    parse_args(argc, argv);
    run_test();
    return 0;
}


