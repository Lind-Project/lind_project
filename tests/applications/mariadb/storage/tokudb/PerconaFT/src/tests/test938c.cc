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

unsigned char N=5;

DB_ENV *env;
DB *db;

static void
run (void) {
    int r;
    DB_TXN *txn, *txn2;
    char v101=101, v102=102, v1=1, v2=1;
    // Add (1,102) to the tree
    // In one txn
    //   add (1,101) to the tree
    // In another concurrent txn
    //   look up (1,102) and do  DB_NEXT
    // That should be fine in PerconaFT.
    // It fails before #938 is fixed.
    // It also fails for BDB for other reasons (page-level locking vs. row-level locking)
    {
	r=env->txn_begin(env, 0, &txn, 0);                            CKERR(r);
	char kk[2] = {v2, v102};
	DBT k,v;
	r=db->put(db, txn, dbt_init(&k, &kk, 2), dbt_init(&v, &v102, 1), 0); CKERR(r);

	r=txn->commit(txn, 0);                                        CKERR(r);
    }
    {
	r=env->txn_begin(env, 0, &txn, 0);                            CKERR(r);
	r=env->txn_begin(env, 0, &txn2, 0);                           CKERR(r);    

	DBT k,v;
	{
	    char kk[2] = {v1, v101};
	    r=db->put(db, txn, dbt_init(&k, &kk, 2), dbt_init(&v, &v101, 1), 0); CKERR(r);
	}

	DBC *c2;
	r=db->cursor(db, txn2, &c2, 0);                                CKERR(r);

	{
	    char kk[2] = {v2, v102};
	    r=c2->c_get(c2, dbt_init(&k, &kk, 2), dbt_init(&v, &v102, 1), DB_SET); CKERR(r);
	}
	r=c2->c_get(c2, dbt_init_malloc(&k), dbt_init_malloc(&v), DB_NEXT);  assert(r==DB_NOTFOUND);

	r=c2->c_close(c2);
	r=txn->commit(txn, 0);                                             CKERR(r);
	r=txn2->commit(txn2, 0);                                             CKERR(r);
    }
}

int
test_main(int argc, char *const argv[]) {
    parse_args(argc, argv);

    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);

    DB_TXN *txn;
    {
        r = db_env_create(&env, 0);                                   CKERR(r);
	r = env->set_redzone(env, 0);                                 CKERR(r);
	r=env->open(env, TOKU_TEST_FILENAME, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
	env->set_errfile(env, stderr);
	r=env->txn_begin(env, 0, &txn, 0);                            CKERR(r);
	r=db_create(&db, env, 0);                                     CKERR(r);
	r=db->open(db, txn, "foo.db", 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO);  CKERR(r);
	r=txn->commit(txn, 0);                                        CKERR(r);
    }
    run();
    {
	r=db->close(db, 0);                                           CKERR(r);
	r=env->close(env, 0);                                         CKERR(r);
    }

    return 0;
}
