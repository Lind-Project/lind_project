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
/* How fast can we do insertions when there are many files? */

#include <db.h>
#include <sys/stat.h>

#define NFILES 1000
#define NINSERTS_PER 1000

static DB_ENV *env;
static DB *dbs[NFILES];
DB_TXN *txn;

static void
test_setup (void) {
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r=toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);       CKERR(r);

    r=db_env_create(&env, 0); CKERR(r);
    env->set_errfile(env, stderr);
    multiply_locks_for_n_dbs(env, NFILES);

    r=env->open(env, TOKU_TEST_FILENAME, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);

    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);

    int i;

    for (i=0; i<NFILES; i++) {
	char fname[20];
	snprintf(fname, sizeof(fname), "foo%d.db", i);
	r=db_create(&dbs[i], env, 0); CKERR(r);
	r = dbs[i]->set_pagesize(dbs[i], 4096);
	r=dbs[i]->open(dbs[i], txn, fname, 0, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(r);
    }
    r=txn->commit(txn, 0);    assert(r==0);
}

static void
test_shutdown (void) {
    int i;
    int r;
    for (i=0; i<NFILES; i++) {
	r= dbs[i]->close(dbs[i], 0); CKERR(r);
    }
    r= env->close(env, 0); CKERR(r);
}

static void
doit (void) {
    int j;
    int r;
    struct timeval startt, endt;
    gettimeofday(&startt, 0);
    r=env->txn_begin(env, 0, &txn, 0); assert(r==0);
    for (j=0; j<NINSERTS_PER; j++) {
	int i;
	DBT key,data;
	char str[10];
	snprintf(str, sizeof(str), "%08d", j);
	dbt_init(&key, str, 1+strlen(str));
	dbt_init(&data, str, 1+strlen(str));
	for (i=0; i<NFILES; i++) {
	    r = dbs[i]->put(dbs[i], txn, &key, &data, 0);
	    CKERR(r);
	}
    }
    r=txn->commit(txn, 0); assert(r==0);
    gettimeofday(&endt, 0);
    long long ninserts = NINSERTS_PER * NFILES;
    double diff = (endt.tv_sec - startt.tv_sec) + 1e-6*(endt.tv_usec-startt.tv_usec);
    if (verbose) printf("%lld insertions in %9.6fs, %9.3f ins/s \n", ninserts, diff, ninserts/diff);
}

int
test_main (int argc, char * const argv[]) {
    parse_args(argc, argv);

    test_setup();
    doit();
    test_shutdown();

    return 0;
}
