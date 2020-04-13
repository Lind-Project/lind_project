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

/* Test what happens if we have deleted the first thing in the database.
 * Also the last.
 * Also if we've deleted a lot of stuff, so that the first good thing is not on the first page.
 */

#include <db.h>
#include <sys/stat.h>

static DB_ENV *env;
static DB *db;
static DB_TXN *txn;

static void
insert (int i) {
    char hello[30], there[30];
    DBT key,data;
    snprintf(hello, sizeof(hello), "hello%d", i);
    snprintf(there, sizeof(there), "there%d", i);
    int r = db->put(db, txn,
		    dbt_init(&key,  hello, strlen(hello)+1),
		    dbt_init(&data, there, strlen(there)+1),
		    0);
    CKERR(r);
}

static void
op_delete (int i) {
    char hello[30];
    DBT key;
    snprintf(hello, sizeof(hello), "hello%d", i);
    int r = db->del(db, txn,
		    dbt_init(&key,  hello, strlen(hello)+1),
		    0);
    CKERR(r);
}

static void
find (int i) {
    char hello[30];
    DBT key, val;
    memset(&val,0,sizeof(val));
    snprintf(hello, sizeof(hello), "hello%d", i);
    int r = db->get(db, txn,
		    dbt_init(&key,  hello, strlen(hello)+1),
		    &val,
		    0);
    CKERR(r);
}

static void
find_first_or_last (int i, int cflag) {
    int r;
    DBC *cursor;
    DBT key, val;
    memset(&key,0,sizeof(key));    
    memset(&val,0,sizeof(val));

    r = db->cursor(db, txn, &cursor, 0);
    CKERR(r);
    r = cursor->c_get(cursor, &key, &val, cflag);
    assert(r==0);
    
    char hello[30], there[30];
    snprintf(hello, sizeof(hello), "hello%d", i);
    snprintf(there, sizeof(there), "there%d", i);

    assert(strcmp(hello, (char*)key.data)==0);
    assert(strcmp(there, (char*)val.data)==0);

    r = cursor->c_close(cursor);
}

static void
do_abort_delete_first_or_last(int N,
			      int first // 1 for first, 0 for last
			      ) {
    int r,i;
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

    // First fill up the db
    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);

    for (i=0; i<N; i++) {
	insert(i);
    }
    r=txn->commit(txn, 0); CKERR(r);

    // Now op_delete a bunch of stuff and see if we can do DB_FIRST
    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    if (first) {
	for (i=0; i<N-1; i++) {
	    op_delete(i);
	}
	find(i);
	find_first_or_last(i, DB_FIRST);
    } else {
	for (i=1; i<N; i++) {
	    op_delete(i);
	}
	find_first_or_last(0, DB_LAST);
    }

    r=txn->commit(txn, 0); CKERR(r);

    r=db->close(db, 0); CKERR(r);
    r=env->close(env, 0); CKERR(r);

    // Oh man, this is gross.
    char cmd[sizeof("../../tools/tokudb_dump -h  foo.db >") + 2 * TOKU_PATH_MAX];
    snprintf(cmd, sizeof(cmd), "../../tools/tokudb_dump -h %s foo.db > %s", TOKU_TEST_FILENAME, DEV_NULL_FILE);
    r=system(cmd);
    CKERR(r);
}

int
test_main (int argc, char *const argv[]) {
    parse_args(argc, argv);
    int f;
    for (f=0; f<2; f++) {
	do_abort_delete_first_or_last(10, f);
	do_abort_delete_first_or_last(1000,f);
    }
    return 0;
}
