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


/*****************
 * Purpose: Verify fix for 3113
 * Bug:     Rollback log is checkpointed along with other cachefiles,
 *          but system crashes before checkpoint_end is written to recovery log.
 *          When recovery runs, it uses latest rollback log, which is out of synch
 *          with recovery log.  Latest version of rollback log would be correct for 
 *          last checkpoint if it completed, but version of rollback log needed
 *          is for last complete checkpoint.
 * Fix:     When opening rollback log for recovery, do not use latest, but use 
 *          latest that is no newer than last complete checkpoint.
 * Test:    begin txn
 *          insert
 *          commit
 *          complete checkpoint (no live txns in checkpoint)
 *          begin txn
 *          insert
 *          begin checkpoint (txn in checkpointed rollback log)
 *          crash using callback2 (just before checkpoint_end is written to disk)
 *          attempt to recover, should crash with 3113
 */        

static const int envflags = DB_INIT_MPOOL|DB_CREATE|DB_THREAD |DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_TXN|DB_PRIVATE;
static const char *namea="a.db";
static DB_ENV *env;
static bool do_test=false, do_recover=false;

static void checkpoint_callback_2(void * UU(extra)) {
    toku_hard_crash_on_purpose();
}


static void
run_test(void) {
    int r;

    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);

    r = db_env_create(&env, 0);                                                         CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags, S_IRWXU+S_IRWXG+S_IRWXO);                      CKERR(r);
    
    DB *db;
    r = db_create(&db, env, 0);                                                         CKERR(r);
    r = db->open(db, NULL, namea, NULL, DB_BTREE, DB_AUTO_COMMIT|DB_CREATE, 0666);      CKERR(r);

    DB_TXN *txn;
    r = env->txn_begin(env, NULL, &txn, 0);                                         CKERR(r);
    {
        DBT k,v;
        dbt_init(&k, "a", 2);
        dbt_init(&v, "a", 2);
        r = db->put(db, txn, &k, &v, 0);                                  CKERR(r);
        uint8_t gid[DB_GID_SIZE];
        memset(gid, 0, DB_GID_SIZE);
        gid[0]=42;
        r = txn->prepare(txn, gid, 0);                                                            CKERR(r);
    }

    r = env->txn_checkpoint(env, 0, 0, 0);                                              CKERR(r);

    DB_TXN *txn2;
    {
        r = env->txn_begin(env, NULL, &txn2, 0);                                         CKERR(r);
        DBT k,v;
        dbt_init(&k, "b", 2);
        dbt_init(&v, "b", 2);
        r = db->put(db, txn2, &k, &v, 0);                                  CKERR(r);
    }

    // cause crash at next checkpoint, after xstillopen written, before checkpoint_end is written
    db_env_set_checkpoint_callback2(checkpoint_callback_2, NULL);

    // checkpoint, putting xstillopen in recovery log (txn is still active)
    r = env->txn_checkpoint(env, 0, 0, 0);                                              CKERR(r);
}
 
static void run_recover (void) {
    int r;
    r = db_env_create(&env, 0);                                                         CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags + DB_RECOVER, S_IRWXU+S_IRWXG+S_IRWXO);         CKERR(r);
    // recover the prepared transaction and commit it
    DB_PREPLIST l[1];
    long count=-1;
    CKERR(env->txn_recover(env, l, 1, &count, DB_FIRST));
    printf("%s:%d count=%ld\n", __FILE__, __LINE__, count);
    assert(count==1);
    assert(l[0].gid[0]==42);
    r = l->txn->commit(l->txn, 0);
    CKERR(r);
    r = env->close(env, 0);                                                             CKERR(r);
    exit(0);

}

static void test_parse_args (int argc, char * const argv[]) {
    int resultcode;
    char * cmd = argv[0];
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



int
test_main (int argc, char * const argv[]) {
    test_parse_args(argc, argv);

    if (do_test)
        run_test();
    else if (do_recover)
        run_recover();

    return 0;
}

