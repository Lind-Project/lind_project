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
/* Test to see if a big nested transaction (so big that it's rollbacks spill into a file)
 * can commit properly. 
 *  Four Tests:
 *     big child aborts, parent aborts
 *     big child aborts, parent commits (This test)
 *     big child commits, parent aborts
 *     big child commits, parent commits
 */

#include <db.h>
#include <sys/stat.h>

int N = 50000;

static DB_ENV *env;
static DB *db;
static DB_TXN *xchild, *xparent;

static void insert (int i, int j) {
    char hello[30], there[30];
    DBT key,data;
    if (verbose) printf("Insert %d\n", i);
    snprintf(hello, sizeof(hello), "hello%d", i);
    snprintf(there, sizeof(there), "there%d", j);
    int r = db->put(db, xchild,
		    dbt_init(&key,  hello, strlen(hello)+1),
		    dbt_init(&data, there, strlen(there)+1),
		    0);
    CKERR(r);
}

static void lookup (int i, int expect, int expectj) {
    char hello[30], there[30];
    DBT key,data;
    snprintf(hello, sizeof(hello), "hello%d", i);
    memset(&data, 0, sizeof(data));
    if (verbose) printf("Looking up %d (expecting %s)\n", i, expect==0 ? "to find" : "not to find");
    int r = db->get(db, xchild,
		    dbt_init(&key,  hello, strlen(hello)+1),
		    &data,
		    0);
    assert(expect==r);
    if (expect==0) {
	CKERR(r);
	snprintf(there, sizeof(there), "there%d", expectj);
	assert(data.size==strlen(there)+1);
	assert(strcmp((char*)data.data, there)==0);
    }
}

static void
test_abort_commit (void) {
    int i, r;
    r=env->txn_begin(env, 0, &xchild, 0); CKERR(r);
    for (i=0; i<N/2; i++) {
	insert(i*2,i*4+1);
    }
    r=xchild->commit(xchild, 0); CKERR(r);
    r=env->txn_begin(env, 0, &xparent, 0);  CKERR(r);
    r=env->txn_begin(env, xparent, &xchild, 0); CKERR(r);
    for (i=0; i<N; i++) {
	insert(i, i);
    }
    r=xchild->abort(xchild); CKERR(r);
    r=env->txn_begin(env, xparent, &xchild, 0); CKERR(r);
    for (i=0; i<N; i++) {
	lookup(i, (i%2==0)?0:DB_NOTFOUND, i*2+1);
    }
    r=xchild->commit(xchild, 0); CKERR(r);
    r=xparent->commit(xparent, 0); CKERR(r);
    r=env->txn_begin(env, 0, &xchild, 0); CKERR(r);
    for (i=0; i<N; i++) {
	lookup(i, (i%2==0)?0:DB_NOTFOUND, i*2+1);
    }
    r=xchild->commit(xchild, 0); CKERR(r);
}

static void
setup (void) {
    DB_TXN *txn;
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r=toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);       CKERR(r);

    r=db_env_create(&env, 0); CKERR(r);
    
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
    r=db->close(db, 0); CKERR(r);
    r=env->close(env, 0); CKERR(r);
}

int
test_main (int argc, char * const argv[]) {
    parse_args(argc, argv);
    setup();
    test_abort_commit();
    test_shutdown();
    return 0;
}
