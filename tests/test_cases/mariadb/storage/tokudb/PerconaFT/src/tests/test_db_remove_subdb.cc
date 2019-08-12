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

/* Does removing subdatabases corrupt the db file/other dbs in that file? (when nothing else open) */

#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <db.h>
#include <memory.h>


// TOKU_TEST_FILENAME is defined in the Makefile

DB_ENV *env;
DB *db;
DBT key;
DBT data;

int
test_main (int UU(argc), char UU(*const argv[])) {
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    r=toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);         assert(r==0);
    dbt_init(&key, "name", sizeof "name");
    dbt_init(&data, NULL, 0);
    
    r=db_env_create(&env, 0);   assert(r==0);
    // Note: without DB_INIT_MPOOL the BDB library will fail on db->open().
    r=env->open(env, TOKU_TEST_FILENAME, DB_INIT_MPOOL|DB_PRIVATE|DB_CREATE, S_IRWXU+S_IRWXG+S_IRWXO); assert(r==0);

    r=env->dbremove(env, NULL, "DoesNotExist.db", NULL, 0);       assert(r==ENOENT);

    r=env->dbremove(env, NULL, "DoesNotExist.db", "SubDb", 0);    assert(r==ENOENT);

    r=db_create(&db, env, 0);   assert(r==0);
    r=db->open(db, NULL, "master.db", "first", DB_BTREE, DB_CREATE, 0666); CKERR(r);
    dbt_init(&data, "first.db", sizeof "first.db");
    db->put(db, NULL, &key, &data, 0);
    r=db->close(db, 0);         assert(r==0);

    r=env->dbremove(env, NULL, "master.db", "second", 0); assert(r==ENOENT);

    r=db_create(&db, env, 0);   assert(r==0);
    r=db->open(db, NULL, "master.db", "second", DB_BTREE, DB_CREATE, 0666); assert(r==0);
    dbt_init(&key, "name", sizeof "name");
    dbt_init(&data, "second.db", sizeof "second.db");
    db->put(db, NULL, &key, &data, 0);
    r=db->close(db, 0);         assert(r==0);

    r=db_create(&db, env, 0);   assert(r==0);
    r=db->open(db, NULL, "master.db", "third", DB_BTREE, DB_CREATE, 0666); assert(r==0);
    dbt_init(&key, "name", sizeof "name");
    dbt_init(&data, "third.db", sizeof "third.db");
    db->put(db, NULL, &key, &data, 0);
    r=db->close(db, 0);         assert(r==0);

    r=env->dbremove(env, NULL, "master.db", "second", 0); assert(r==0);

    r=env->dbremove(env, NULL, "master.db", "second", 0); assert(r==ENOENT);

    dbt_init(&key, "name", sizeof "name");
    dbt_init(&data, NULL, 0);

    //Verify data still exists in first/third
    r=db_create(&db, env, 0);   assert(r==0);
    r=db->open(db, NULL, "master.db", "first", DB_BTREE, 0, 0666); assert(r==0);
    r=db->get(db, NULL, &key, &data, 0);    assert(r==0);
    assert(!strcmp((char*)data.data, "first.db"));
    r=db->close(db, 0);         assert(r==0);
    
    r=db_create(&db, env, 0);   assert(r==0);
    r=db->open(db, NULL, "master.db", "third", DB_BTREE, 0, 0666); assert(r==0);
    r=db->get(db, NULL, &key, &data, 0);    assert(r==0);
    assert(!strcmp((char*)data.data, "third.db"));
    r=db->close(db, 0);         assert(r==0);
    
    //Verify second is gone.
    r=db_create(&db, env, 0);   assert(r==0);
    r=db->open(db, NULL, "master.db", "second", DB_BTREE, 0, 0666); assert(r==ENOENT);
    //Create again, verify it does not have its old data.
    r=db->open(db, NULL, "master.db", "second", DB_BTREE, DB_CREATE, 0666); assert(r==0);
    r=db->get(db, NULL, &key, &data, 0);    assert(r==DB_NOTFOUND);
    
    r=db->close(db, 0);       assert(r==0);
    r=env->close(env, 0);     assert(r==0);
    return 0;
}
