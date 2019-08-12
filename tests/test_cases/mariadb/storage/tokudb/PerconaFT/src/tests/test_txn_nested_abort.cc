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
#include <errno.h>
#include <sys/stat.h>
#include <db.h>


static int
db_put (DB *db, DB_TXN *txn, int k, int v) {
    DBT key, val;
    return db->put(db, txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), DB_NOOVERWRITE);
}

static const char *db_error(int error) {
    static char errorbuf[32];
    switch (error) {
    case DB_NOTFOUND: return "DB_NOTFOUND";
    case DB_LOCK_DEADLOCK: return "DB_LOCK_DEADLOCK"; 
    case DB_LOCK_NOTGRANTED: return "DB_LOCK_NOTGRANTED";
    case DB_KEYEXIST: return "DB_KEYEXIST";
    default:
        sprintf(errorbuf, "%d", error);
        return errorbuf;
    }
}

static void
test_txn_nested(int do_commit) {
    if (verbose) printf("test_txn_nested:%d\n", do_commit);

    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);

    DB_ENV *env;
    DB *db;
    DB_TXN * const null_txn = 0;
    const char * const fname = "test.txn.nested.abort.ft_handle";

    /* create the dup database file */
    r = db_env_create(&env, 0);        assert(r == 0);
    env->set_errfile(env, stderr);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE|DB_INIT_MPOOL|DB_INIT_TXN|DB_INIT_LOCK|DB_INIT_LOG |DB_THREAD |DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r = db_create(&db, env, 0); assert(r == 0);
    db->set_errfile(db,stderr); // Turn off those annoying errors
    r = db->open(db, null_txn, fname, "main", DB_BTREE, DB_CREATE+DB_AUTO_COMMIT, 0666); assert(r == 0);
   
    DB_TXN *t1;
    r = env->txn_begin(env, null_txn, &t1, 0); assert(r == 0);
    if (verbose) printf("t1:begin\n");

    DB_TXN *t2;
    r = env->txn_begin(env, t1, &t2, 0); assert(r == 0);
    if (verbose) printf("t2:begin\n");

    r = db_put(db, t2, htonl(1), htonl(1));
    if (verbose) printf("t1:put:%s\n", db_error(r));

    if (do_commit) {
        r = t2->commit(t2, 0); 
        if (verbose) printf("t2:commit:%s\n", db_error(r));
    } else {
        r = t2->abort(t2);
        if (verbose) printf("t2:abort:%s\n", db_error(r));
    }

    r = db->close(db, 0); assert(r == 0);

    r = t1->commit(t1, 0); 
    if (verbose) printf("t1:commit:%s\n", db_error(r));

    r = env->close(env, 0); assert(r == 0);
}


int
test_main(int argc, char *const argv[]) {

    parse_args(argc, argv);
  
    test_txn_nested(0);
    test_txn_nested(1);

    return 0;
}
