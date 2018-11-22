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

#include <errno.h>
#include <sys/stat.h>
#include <db.h>
#include <memory.h>

const char *dbfile = "test.db";
const char *dbname = 0;

static int
db_put (DB *db, int k, int v) {
    DBT key, val;
    int r = db->put(db, 0, dbt_init(&key, &k, sizeof k), dbt_init(&val, &v, sizeof v), 0);
    return r;
}

static int
db_get (DB *db, int k, int expectv, int val_flags) {
    int v;
    DBT key, val;
    memset(&val, 0, sizeof val); val.flags = val_flags;
    if (val.flags == DB_DBT_USERMEM) {
        val.ulen = sizeof v; val.data = &v;
    }
    int r = db->get(db, 0, dbt_init(&key, &k, sizeof k), &val, 0);
    if (r == 0) {
        assert(val.size == sizeof v); 
        if ((val.flags & DB_DBT_USERMEM) == 0) memcpy(&v, val.data, val.size); 
        assert(v == expectv);
    } else {
        if (verbose) printf("%s:%d:%d:%s\n", __FILE__, __LINE__, r, db_strerror(r));
    }
    if (val.flags & (DB_DBT_MALLOC|DB_DBT_REALLOC))
        toku_free(val.data);
    return r;
}

static void
test_db_create (void) {
    int r;

    unlink(dbfile);

    DB_ENV *env;
    r = db_env_create(&env, 0); assert(r == 0);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL, 0); assert(r == 0);

    DB *db;
    r = db_create(&db, env, 0); assert(r == 0);
    db->set_errfile(db,0); // Turn off those annoying errors
    r = db->open(db, 0, dbfile, dbname, DB_BTREE, DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); assert(r == 0);
    r = db_put(db, htonl(1), 1); assert(r == 0);
    r = db_get(db, htonl(1), 1, 0); assert(r == 0);
    r = db_get(db, htonl(1), 1, DB_DBT_USERMEM); assert(r == 0);
    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

static void
test_db_thread (void) {
    int r;

    unlink(dbfile);

    DB_ENV *env;
    r = db_env_create(&env, 0); assert(r == 0);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE+DB_PRIVATE+DB_INIT_MPOOL+DB_THREAD, 0); assert(r == 0);

    DB *db;
    r = db_create(&db, env, 0); assert(r == 0);
    db->set_errfile(db,0); // Turn off those annoying errors
    r = db->open(db, 0, dbfile, dbname, DB_BTREE, DB_CREATE + DB_THREAD, S_IRWXU+S_IRWXG+S_IRWXO); assert(r == 0);
    r = db_put(db, htonl(1), 1); assert(r == 0);
    r = db_get(db, htonl(1), 1, 0); assert(r == EINVAL);
    r = db_get(db, htonl(1), 1, DB_DBT_MALLOC); assert(r == 0);
    r = db_get(db, htonl(1), 1, DB_DBT_REALLOC); assert(r == 0);
    r = db_get(db, htonl(1), 1, DB_DBT_USERMEM); assert(r == 0);
    r = db->close(db, 0); assert(r == 0);
    r = env->close(env, 0); assert(r == 0);
}

int
test_main(int argc, char *const argv[]) {
    parse_args(argc, argv);
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    test_db_create();
    test_db_thread();
    return 0;
}
