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

// verify that the leaf split code can handle rows larger than nodesize

#include "test.h"

static void insert(DB *db, DB_TXN *txn, int k, int val_size) {
    int r;

    // generate the key
    char key_buffer[8]; 
    memset(key_buffer, 0, sizeof key_buffer);
    int newa = htonl(k);
    memcpy(key_buffer, &newa, sizeof newa);

    // generate the value
    char *XCALLOC_N(val_size, val_buffer);
    
    DBT key = { .data = key_buffer, .size = sizeof key_buffer };
    DBT value = { .data = val_buffer, .size = (uint32_t) val_size };
    r = db->put(db, txn, &key, &value, 0); assert_zero(r);

    toku_free(val_buffer);
}

int test_main(int argc, char * const argv[]) {
    const char *db_env_dir = "dir.blobs.leafsplit.env.tdb";
    int db_env_open_flags = DB_CREATE | DB_PRIVATE | DB_INIT_MPOOL | DB_INIT_TXN | DB_INIT_LOCK | DB_INIT_LOG;
    const char *db_filename = "blobs.db";
    int do_txn = 1;
    uint64_t cachesize = 0;
    uint32_t pagesize = 0;

    int i;
    for (i = 1; i < argc; i++) {
        char *arg = argv[i];
        if (strcmp(arg, "-v") == 0 || strcmp(arg, "--verbose") == 0) {
            verbose++;
            continue;
        }
        if (strcmp(arg, "-q") == 0) {
            if (verbose > 0) verbose--;
            continue;
        }
        if (strcmp(arg, "--txn") == 0 && i+1 < argc) {
            do_txn = atoi(argv[++i]);
            continue;
        }
        if (strcmp(arg, "--pagesize") == 0 && i+1 < argc) {
            pagesize = atoi(argv[++i]);
            continue;
        }
        if (strcmp(arg, "--cachesize") == 0 && i+1 < argc) {
            cachesize = atol(argv[++i]);
            continue;
        }

        assert(0);
    }

    int r;
    char rm_cmd[strlen(db_env_dir) + strlen("rm -rf ") + 1];
    snprintf(rm_cmd, sizeof(rm_cmd), "rm -rf %s", db_env_dir);
    r = system(rm_cmd); assert_zero(r);

    r = toku_os_mkdir(db_env_dir, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); assert_zero(r);

    // create and open the env
    DB_ENV *db_env = NULL;
    r = db_env_create(&db_env, 0); assert_zero(r);
    if (cachesize) {
        const uint64_t gig = 1 << 30;
        r = db_env->set_cachesize(db_env, cachesize / gig, cachesize % gig, 1); assert_zero(r);
    }
    if (!do_txn)
        db_env_open_flags &= ~(DB_INIT_TXN | DB_INIT_LOG);
    r = db_env->open(db_env, db_env_dir, db_env_open_flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); assert_zero(r);

    // create the db
    DB *db = NULL;
    r = db_create(&db, db_env, 0); assert_zero(r);
    DB_TXN *create_txn = NULL;
    if (do_txn) {
        r = db_env->txn_begin(db_env, NULL, &create_txn, 0); assert_zero(r);
    }
    if (pagesize) {
        r = db->set_pagesize(db, pagesize); assert_zero(r);
    }
    r = db->open(db, create_txn, db_filename, NULL, DB_BTREE, DB_CREATE, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); assert_zero(r);

    insert(db, create_txn, 1, 8000000);
    insert(db, create_txn, 1, 16000000);
    insert(db, create_txn, 1, 32000000);
    insert(db, create_txn, 2, 1);

    if (do_txn) {
        r = create_txn->commit(create_txn, 0); assert_zero(r);
    }

    // shutdown
    r = db->close(db, 0); assert_zero(r); db = NULL;
    r = db_env->close(db_env, 0); assert_zero(r); db_env = NULL;

    return 0;
}
