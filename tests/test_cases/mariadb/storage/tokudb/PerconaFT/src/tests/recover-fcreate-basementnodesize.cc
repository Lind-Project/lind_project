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

// verify thtat we can create the correct tree type after the db is removed
#include <sys/stat.h>
#include "test.h"


static const int envflags = DB_INIT_MPOOL|DB_CREATE|DB_THREAD |DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_TXN|DB_PRIVATE;

static const char *namea="a.db"; uint32_t nodesizea = 0;
static const char *nameb="b.db"; uint32_t nodesizeb = 32*1024;

static void do_remove(DB_ENV *env, const char *filename) {
    int r;
    DBT dname;
    DBT iname;
    dbt_init(&dname, filename, strlen(filename)+1);
    dbt_init(&iname, NULL, 0);
    iname.flags |= DB_DBT_MALLOC;
    r = env->get_iname(env, &dname, &iname); CKERR(r);
    if (verbose) printf("%s -> %s\n", filename, (char *) iname.data);
    char rmpath[TOKU_PATH_MAX+1];
    toku_path_join(rmpath, 2, TOKU_TEST_FILENAME, iname.data);
    toku_os_recursive_delete(rmpath);
    toku_free(iname.data);
}

static void run_test (void) {
    int r;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);

    DB_ENV *env;
    r = db_env_create(&env, 0);                                                         CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags, S_IRWXU+S_IRWXG+S_IRWXO);                      CKERR(r);

    r = env->txn_checkpoint(env, 0, 0, 0);                                              CKERR(r);

    DB_TXN *txn;
    r = env->txn_begin(env, NULL, &txn, 0);                                             CKERR(r);

    // create a db with the default nodesize
    DB *dba;
    r = db_create(&dba, env, 0);                                                        CKERR(r);
    r = dba->get_readpagesize(dba, &nodesizea); CKERR(r);
    if (verbose) printf("nodesizea=%u", nodesizea);
    r = dba->open(dba, NULL, namea, NULL, DB_BTREE, DB_AUTO_COMMIT|DB_CREATE, 0666);    CKERR(r);
    r = dba->close(dba, 0); CKERR(r);

    // create a db with a small nodesize
    DB *dbb;
    r = db_create(&dbb, env, 0);                                                        CKERR(r);
    r = dbb->set_readpagesize(dbb, nodesizeb);                                          CKERR(r);
    r = dbb->open(dbb, NULL, nameb, NULL, DB_BTREE, DB_AUTO_COMMIT|DB_CREATE, 0666);    CKERR(r);
    r = dbb->close(dbb, 0); CKERR(r);

    r = txn->commit(txn, 0);                                                            CKERR(r);

    // remove the inames to force recovery to recreate them
    do_remove(env, namea);
    do_remove(env, nameb);

    toku_hard_crash_on_purpose();
}

static void run_recover (void) {
    int r;

    // run recovery
    DB_ENV *env;
    r = db_env_create(&env, 0);                                                             CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags + DB_RECOVER, S_IRWXU+S_IRWXG+S_IRWXO);             CKERR(r);
    
    // verify that the trees have the correct nodesizes
    uint32_t pagesize;
    DB *dba;
    r = db_create(&dba, env, 0);                                                            CKERR(r);
    r = dba->open(dba, NULL, namea, NULL, DB_UNKNOWN, DB_AUTO_COMMIT, 0666);                CKERR(r);
    r = dba->get_readpagesize(dba, &pagesize); CKERR(r);
    if (verbose) printf("%u\n", pagesize);
    // assert(pagesize == nodesizea);
    r = dba->close(dba, 0);                                                                 CKERR(r);

    DB *dbb;
    r = db_create(&dbb, env, 0);                                                            CKERR(r);
    r = dbb->open(dbb, NULL, nameb, NULL, DB_UNKNOWN, DB_AUTO_COMMIT, 0666);                CKERR(r);
    r = dbb->get_readpagesize(dbb, &pagesize); CKERR(r);
    if (verbose) printf("%u\n", pagesize);
    assert(pagesize == nodesizeb);
    r = dbb->close(dbb, 0);                                                                 CKERR(r);

    r = env->close(env, 0);                                                                 CKERR(r);
    exit(0);
}

static void run_no_recover (void) {
    int r;

    DB_ENV *env;
    r = db_env_create(&env, 0);                                                             CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags & ~DB_RECOVER, S_IRWXU+S_IRWXG+S_IRWXO);            CKERR(r);
    r = env->close(env, 0);                                                                 CKERR(r);
    exit(0);
}

static const char *cmd;

static bool do_test=false, do_recover=false, do_recover_only=false, do_no_recover = false;

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
