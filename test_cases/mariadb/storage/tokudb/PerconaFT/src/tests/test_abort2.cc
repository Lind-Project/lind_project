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
/* Put some insert messages into an internal buffer (by first creating a DB, filling it up, then closing it, and reopening, and inserting a few things)
 * Then perform a transaction that overwrites some of those internal things.
 * Then abort the transaction.
 * Make sure those middle things made it back into the tree.
 */

#include <db.h>
#include <sys/stat.h>

static DB_ENV *env;
static DB *db;
static DB_TXN *txn;

static void
insert (int i, int j) {
    char hello[30], there[230];
    DBT key,data;
    snprintf(hello, sizeof(hello), "hello%d", i);
    snprintf(there, sizeof(there), "%dthere%d %*s", j, i, 10+i%40, "padding");
    int r = db->put(db, txn,
		    dbt_init(&key,  hello, strlen(hello)+1),
		    dbt_init(&data, there, strlen(there)+1),
		    0);
    CKERR(r);
}

static void
do_test_abort2 (void) {
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r=toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);       assert(r==0);

    r=db_env_create(&env, 0); assert(r==0);
    env->set_errfile(env, stderr);
    r=env->open(env, TOKU_TEST_FILENAME, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r=db_create(&db, env, 0); CKERR(r);
    r=db->set_pagesize(db, 4096); // Use a small page
    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    r=db->open(db, txn, "foo.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r=txn->commit(txn, 0);    assert(r==0);

    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    {
	int i;
	for (i=0; i<1000; i++) {
	    insert(4*i, 0);
	}
    }
    r=txn->commit(txn, 0); CKERR(r);
    r=db->close(db, 0); CKERR(r);
    r=env->close(env, 0); CKERR(r);

    //printf("%s:%d\n", __FILE__, __LINE__);

    // Now do a few inserts that abort.
    r=db_env_create(&env, 0); assert(r==0);
    env->set_errfile(env, stderr);
    r=env->open(env, TOKU_TEST_FILENAME, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r=db_create(&db, env, 0); CKERR(r);
    r=env->txn_begin(env, 0, &txn, 0); CKERR(r);
    r=db->open(db, txn, "foo.db", 0, DB_BTREE, 0, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r=txn->commit(txn, 0);    assert(r==0);

    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    insert(3, 0);
    insert(5, 0);
    insert(7, 0);
    r=txn->commit(txn, 0); CKERR(r);

    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    insert(7, 1);
    r=txn->abort(txn); CKERR(r);


    //printf("%s:%d\n", __FILE__, __LINE__);
    //r=db->close(db,0); CKERR(r); r=env->close(env, 0); CKERR(r); return;

    // Don't do a lookup on "hello7", because that will force things out of the buffer.
    r=db->close(db, 0); CKERR(r);
    //printf("%s:%d\n", __FILE__, __LINE__);
    r=db_create(&db, env, 0); CKERR(r);
    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    r=db->open(db, txn, "foo.db", 0, DB_BTREE, 0, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r=txn->commit(txn, 0); CKERR(r);
    //printf("%s:%d\n", __FILE__, __LINE__);

    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    {
	DBT key,data;
	memset(&data, 0, sizeof(data));
	r = db->get(db, txn, dbt_init(&key, "hello7", strlen("hello7")+1), &data, 0);
	CKERR(r);
	//printf("data is %s\n", (char*)data.data);
	assert(((char*)data.data)[0]=='0');
    }
    r=txn->abort(txn); CKERR(r);
    
    r=db->close(db, 0); CKERR(r);
    r=env->close(env, 0); CKERR(r);

}

int
test_main (int argc, char *const argv[]) {
    parse_args(argc, argv);
    do_test_abort2();
    return 0;
}
