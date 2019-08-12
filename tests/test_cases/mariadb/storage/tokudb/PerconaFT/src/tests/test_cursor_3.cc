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
// Verify that different cursors return different data items when DBT is given no flags.


#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <memory.h>
#include <errno.h>
#include <sys/stat.h>
#include <db.h>


static void
verify_distinct_pointers (void **ptrs, int n) {
    int i,j;
    for (i=0; i<n; i++) {
	for (j=i+1; j<n; j++) {
	    assert(ptrs[i]!=ptrs[j]);
	}
    }
}

DB_ENV * env;
DB *db;
DB_TXN * const null_txn = 0;

enum { ncursors = 2 };
DBC *cursor[ncursors];

static void
testit (uint32_t cop)  {
    void *kptrs[ncursors];
    void *vptrs[ncursors];
    int i;
    for (i=0; i<ncursors; i++) {
	DBT k0; memset(&k0, 0, sizeof k0);
	DBT v0; memset(&v0, 0, sizeof v0);
	int r = cursor[i]->c_get(cursor[i], &k0, &v0, cop);
	CKERR(r);
	kptrs[i] = k0.data;
	vptrs[i] = v0.data;
    }
    verify_distinct_pointers(kptrs, ncursors);
    verify_distinct_pointers(vptrs, ncursors);
}

static void
test (void) {
    if (verbose) printf("test_cursor\n");

    const char * const fname = "test.cursor.ft_handle";
    int r;

    /* create the dup database file */
    r = db_env_create(&env, 0);        assert(r == 0);
    env->set_errfile(env, stderr);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE|DB_INIT_MPOOL|DB_THREAD|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r = db_create(&db, env, 0); assert(r == 0);
    db->set_errfile(db,stderr); // Turn off those annoying errors
    r = db->open(db, null_txn, fname, "main", DB_BTREE, DB_CREATE, 0666); assert(r == 0);

    int i;
    int n = 42;
    for (i=0; i<n; i++) {
        int k = htonl(i);
        int v = htonl(i);
        DBT key, val;
        r = db->put(db, null_txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), 0);
        assert(r == 0); 
    }

    for (i=0; i<ncursors; i++) {
	r = db->cursor(db, null_txn, &cursor[i], 0); CKERR(r);
    }

    testit(DB_FIRST);
    testit(DB_NEXT);
    testit(DB_PREV);
    testit(DB_LAST);

    r = cursor[0]->c_close(cursor[0]); assert(r == 0);
    r = cursor[1]->c_close(cursor[1]); assert(r == 0);

    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

int
test_main(int argc, char *const argv[]) {

    parse_args(argc, argv);
  
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    
    test();

    return 0;
}
