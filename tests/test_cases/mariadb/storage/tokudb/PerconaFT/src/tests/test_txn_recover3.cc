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


static void
test_txn_recover3 (int nrows) {
    if (verbose) printf("test_txn_recover1:%d\n", nrows);

    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    char dirname[TOKU_PATH_MAX+1];
    toku_os_mkdir(toku_path_join(dirname, 2, TOKU_TEST_FILENAME, "t.tokudb"), S_IRWXU+S_IRWXG+S_IRWXO);

    DB_ENV *env;
    DB *mdb, *sdb;
    DB_TXN * const null_txn = 0;
    const char * const fname = "t.tokudb/main.ft_handle";
    const char * const sname = "t.tokudb/status.ft_handle";

    r = db_env_create(&env, 0);        assert(r == 0);
    env->set_errfile(env, stderr);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE|DB_INIT_MPOOL|DB_INIT_TXN|DB_INIT_LOCK|DB_INIT_LOG |DB_THREAD |DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r = env->close(env, 0); CKERR(r);

    r = db_env_create(&env, 0);        assert(r == 0);
    env->set_errfile(env, stderr);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE|DB_INIT_MPOOL|DB_INIT_TXN|DB_INIT_LOCK|DB_INIT_LOG |DB_THREAD |DB_PRIVATE | DB_RECOVER, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);

    r = db_create(&mdb, env, 0); assert(r == 0);
    mdb->set_errfile(mdb,stderr); // Turn off those annoying errors
    r = mdb->open(mdb, null_txn, fname, NULL, DB_BTREE, DB_CREATE+DB_THREAD+DB_AUTO_COMMIT, 0666); assert(r == 0);
    r = mdb->close(mdb, 0); assert(r == 0);

    r = db_create(&sdb, env, 0); assert(r == 0);
    sdb->set_errfile(sdb,stderr); // Turn off those annoying errors
    r = sdb->open(sdb, null_txn, sname, NULL, DB_BTREE, DB_CREATE+DB_THREAD+DB_AUTO_COMMIT, 0666); assert(r == 0);
    r = sdb->close(sdb, 0); assert(r == 0);

    r = db_create(&mdb, env, 0); assert(r == 0);
    mdb->set_errfile(mdb,stderr); // Turn off those annoying errors
    r = mdb->open(mdb, null_txn, fname, NULL, DB_BTREE, DB_CREATE+DB_THREAD+DB_AUTO_COMMIT, 0666); assert(r == 0);

    r = db_create(&sdb, env, 0); assert(r == 0);
    sdb->set_errfile(sdb,stderr); // Turn off those annoying errors
    r = sdb->open(sdb, null_txn, sname, NULL, DB_BTREE, DB_CREATE+DB_THREAD+DB_AUTO_COMMIT, 0666); assert(r == 0);


    DB_TXN *txn;
    r = env->txn_begin(env, null_txn, &txn, 0); assert(r == 0);

    int i;
    for (i=0; i<nrows; i++) {
        int k = htonl(i);
        int v = htonl(i);
        DBT key, val;
        r = mdb->put(mdb, txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), 0);
        assert(r == 0); 
        r = sdb->put(sdb, txn, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), 0);
        assert(r == 0); 
    }
   
    r = txn->commit(txn, 0); assert(r == 0);

    r = mdb->close(mdb, 0); assert(r == 0);
    r = sdb->close(sdb, 0); assert(r == 0);

    r = env->txn_checkpoint(env, 0, 0, 0); assert(r == 0);

    char **names;
    r = env->log_archive(env, &names, 0); assert(r == 0);
    if (names) {
        for (i=0; names[i]; i++)
            printf("%d:%s\n", i, names[i]);
        toku_free(names);
    }

    r = env->close(env, 0); assert(r == 0);

    r = db_env_create(&env, 0);        assert(r == 0);
    env->set_errfile(env, stderr);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE|DB_INIT_MPOOL|DB_INIT_TXN|DB_INIT_LOCK|DB_INIT_LOG |DB_THREAD |DB_PRIVATE | DB_RECOVER, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    r = env->close(env, 0); assert(r == 0);
}

int
test_main(int argc, char *const argv[]) {

    parse_args(argc, argv);
  
    test_txn_recover3(1);

    return 0;
}
