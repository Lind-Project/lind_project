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
#include <sys/wait.h>

// Verify that if tokudb crashes during recovery, then the prepared transactions are still prepared.

static void clean_env (const char *envdir) {
    const int len = strlen(envdir)+100;
    char cmd[len];
    snprintf(cmd, len, "rm -rf %s", envdir);
    int r = system(cmd);
    CKERR(r);
    CKERR(toku_os_mkdir(envdir, S_IRWXU+S_IRWXG+S_IRWXO));
}

static void setup_env (DB_ENV **envp, const char *envdir) {
    { int chk_r = db_env_create(envp, 0); CKERR(chk_r); }
    (*envp)->set_errfile(*envp, stderr);
    { int chk_r = (*envp)->set_redzone(*envp, 0); CKERR(chk_r); }
    { int chk_r = (*envp)->open(*envp, envdir, DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN|DB_CREATE|DB_PRIVATE|DB_RECOVER, S_IRWXU+S_IRWXG+S_IRWXO); CKERR(chk_r); }
}

static void setup_env_and_prepare (DB_ENV **envp, const char *envdir, bool commit) {
    DB *db;
    DB_TXN *txn;
    clean_env(envdir);
    setup_env(envp, envdir);
    CKERR(db_create(&db, *envp, 0));
    CKERR(db->open(db, NULL, "foo.db", 0, DB_BTREE, DB_CREATE | DB_AUTO_COMMIT, S_IRWXU+S_IRWXG+S_IRWXO));
    CKERR((*envp)->txn_begin(*envp, 0, &txn, 0));
    DBT key;
    dbt_init(&key, "foo", 4);
    CKERR(db->put(db, txn, &key, &key, 0));
    { int chk_r = db->close(db, 0); CKERR(chk_r); }
    uint8_t gid[DB_GID_SIZE];
    memset(gid, 0, DB_GID_SIZE);
    gid[0]=42;
    CKERR(txn->prepare(txn, gid, 0));
    if (commit)
	CKERR(txn->commit(txn, 0));
}

static void test (void) {
    pid_t pid;

    if (0==(pid=fork())) {
	DB_ENV *env;
	setup_env_and_prepare(&env, TOKU_TEST_FILENAME, false);
	{
	    DB_PREPLIST l[1];
	    long count=-1;
	    CKERR(env->txn_recover(env, l, 1, &count, DB_FIRST));
	    printf("%s:%d count=%ld\n", __FILE__, __LINE__, count);
	    assert(count==1);
	    assert(l[0].gid[0]==42);
	}
	exit(0);
    }
    {
	int status;
	pid_t pid2 = wait(&status);
	assert(pid2==pid);
	assert(WIFEXITED(status) && WEXITSTATUS(status)==0);
    }
    // Now run recovery and crash on purpose.
    if (0==(pid=fork())) {
	DB_ENV *env;
	setup_env(&env, TOKU_TEST_FILENAME);

	// make sure there is 1 prepared txn.
	{
	    DB_PREPLIST l[1];
	    long count=-1;
	    int r = env->txn_recover(env, l, 1, &count, DB_FIRST);
	    printf("r=%d count=%ld\n", r, count);
	    assert(count==1);
	    assert(l[0].gid[0]==42);
	    for (int i=1; i<DB_GID_SIZE; i++) {
		assert(l[0].gid[i]==0);
	    }
	}

	exit(0);
    }
    {
	int status;
	pid_t pid2 = wait(&status);
	assert(pid2==pid);
	assert(WIFEXITED(status) && WEXITSTATUS(status)==0);
    }

    // Now see if recovery works the second time.
    DB_ENV *env;
    setup_env(&env, TOKU_TEST_FILENAME);
    {
	DB_PREPLIST l[1];
	long count=-1;
	int r = env->txn_recover(env, l, 1, &count, DB_FIRST);
	printf("r=%d count=%ld\n", r, count);
	assert(count==1);
	assert(l[0].gid[0]==42);
	for (int i=1; i<DB_GID_SIZE; i++) {
	    assert(l[0].gid[i]==0);
	}
	{ int chk_r = l->txn->commit(l->txn, 0); CKERR(chk_r); }
    }
    { int chk_r = env ->close(env,  0); CKERR(chk_r); }
}

int test_main (int argc, char *const argv[]) {
    default_parse_args(argc, argv);
    // first test: open an environment, a db, a txn, and do a prepare.   Then do txn_prepare (without even closing the environment).
    test();
    

    // second test: poen environment, a db, a txn, prepare, close the environment.  Then reopen and do txn_prepare.

    // third test: make sure there is an fsync on txn_prepare, but not on the following commit.

    
    // Then close the environment Find out what BDB does when ask for the txn prepares.
    // Other tests: read prepared txns, 1 at a time. Then close it and read them again.
    return 0;
}
