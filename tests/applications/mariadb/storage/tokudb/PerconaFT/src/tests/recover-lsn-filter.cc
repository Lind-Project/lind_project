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

// this test makes sure the LSN filtering is used during recovery

#include <sys/stat.h>
#include <fcntl.h>
#include "test.h"


const int envflags = DB_INIT_MPOOL|DB_CREATE|DB_THREAD |DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_TXN|DB_PRIVATE;

const char *namea="a.db";

static void run_test (void) {
    int r;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);

    DB_ENV *env;
    r = db_env_create(&env, 0);                                                         CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags, S_IRWXU+S_IRWXG+S_IRWXO);                      CKERR(r);

    // create a txn that never closes, forcing recovery to run from the beginning of the log
    {
        DB_TXN *oldest_living_txn;
        r = env->txn_begin(env, NULL, &oldest_living_txn, 0);                                         CKERR(r);
    }

    DB *db;
    r = db_create(&db, env, 0);                                                         CKERR(r);
    r = db->open(db, NULL, namea, NULL, DB_BTREE, DB_AUTO_COMMIT|DB_CREATE, 0666);      CKERR(r);

    // txn_begin; insert <a,a>; txn_abort
    {
        DB_TXN *txn;
        r = env->txn_begin(env, NULL, &txn, 0);                                         CKERR(r);
        DBT k,v;
        dbt_init(&k, "a", 2);
        dbt_init(&v, "b", 2);
	r = db->put(db, txn, &k, &v, 0);                                  CKERR(r);
        r = txn->abort(txn);                                                            CKERR(r);
    }

    // txn_begin; insert <a,b>;
    {
        DB_TXN *txn;
        r = env->txn_begin(env, NULL, &txn, 0);                                         CKERR(r);
        DBT k,v;
        dbt_init(&k, "a", 2);
        dbt_init(&v, "b", 2);
	r = db->put(db, txn, &k, &v, 0);                                  CKERR(r);
    }

    // checkpoint
    r = env->txn_checkpoint(env, 0, 0, 0);                                              CKERR(r);

    // abort the process
    toku_hard_crash_on_purpose();
}


static void run_recover (void) {
    DB_ENV *env;
    int r;

    // Recovery starts from oldest_living_txn, which is older than any inserts done in run_test,
    // so recovery always runs over the entire log.

    // run recovery
    r = db_env_create(&env, 0);                                                         CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags + DB_RECOVER, S_IRWXU+S_IRWXG+S_IRWXO);         CKERR(r);

    // verify the data
    DB *db;
    r = db_create(&db, env, 0);                                                         CKERR(r);
    r = db->open(db, NULL, namea, NULL, DB_UNKNOWN, DB_AUTO_COMMIT, 0666);              CKERR(r);
    
    DB_TXN *txn;
    r = env->txn_begin(env, NULL, &txn, 0);                                             CKERR(r);
    DBC *cursor;
    r = db->cursor(db, txn, &cursor, 0);                                                CKERR(r);
    DBT k, v;
    r = cursor->c_get(cursor, dbt_init_malloc(&k), dbt_init_malloc(&v), DB_FIRST);
    assert(r == DB_NOTFOUND);

    r = cursor->c_close(cursor);                                                        CKERR(r);

    r = txn->commit(txn, 0); CKERR(r);
    r = db->close(db, 0); CKERR(r);
    r = env->close(env, 0);                                                             CKERR(r);
    exit(0);
}

static void run_no_recover (void) {
    DB_ENV *env;
    int r;

    r = db_env_create(&env, 0);                                                         CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags & ~DB_RECOVER, S_IRWXU+S_IRWXG+S_IRWXO);        CKERR(r);
    r = env->close(env, 0);                                                             CKERR(r);
    exit(0);
}

const char *cmd;

bool do_test=false, do_recover=false, do_recover_only=false, do_no_recover = false;

static void test_parse_args (int argc, char * const argv[]) {
    int resultcode;
    cmd = argv[0];
    argc--; argv++;
    while (argc>0) {
	if (strcmp(argv[0], "-v") == 0) {
	    verbose++;
	} else if (strcmp(argv[0],"-q")==0) {
	    verbose--;
	    if (verbose<0) verbose=0;
	} else if (strcmp(argv[0], "--test")==0) {
	    do_test=true;
        } else if (strcmp(argv[0], "--recover") == 0) {
            do_recover=true;
        } else if (strcmp(argv[0], "--recover-only") == 0) {
            do_recover_only=true;
        } else if (strcmp(argv[0], "--no-recover") == 0) {
            do_no_recover=true;
	} else if (strcmp(argv[0], "-h")==0) {
	    resultcode=0;
	do_usage:
	    fprintf(stderr, "Usage:\n%s [-v|-q]* [-h] {--test | --recover } \n", cmd);
	    exit(resultcode);
	} else {
	    fprintf(stderr, "Unknown arg: %s\n", argv[0]);
	    resultcode=1;
	    goto do_usage;
	}
	argc--;
	argv++;
    }
}

int test_main (int argc, char * const argv[]) {
    test_parse_args(argc, argv);
    if (do_test) {
	run_test();
    } else if (do_recover) {
        run_recover();
    } else if (do_recover_only) {
        run_recover();
    } else if (do_no_recover) {
        run_no_recover();
    } 
    return 0;
}
