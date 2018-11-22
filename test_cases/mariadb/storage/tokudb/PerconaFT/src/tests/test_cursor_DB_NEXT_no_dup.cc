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


static DBC* cursor      = NULL;
static DB*  db          = NULL;
static DB_ENV* env      = NULL;
static int r            = 0;
static DB_TXN* null_txn = NULL;

static void setup_env(void) {
    assert(!env && !db && !cursor);
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    r = db_env_create(&env, 0);
        CKERR(r);
    assert(env);
    env->set_errfile(env, stderr);
    r = env->open(env, TOKU_TEST_FILENAME, DB_CREATE|DB_INIT_MPOOL|DB_THREAD|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO);
        CKERR(r);
    assert(env);
}

static void close_env(void) {
    assert(env && !db && !cursor);
    r = env->close(env, 0);
        CKERR(r);
    env = NULL;
}

static void setup_db(void) {
    assert(env && !db && !cursor);
    r = db_create(&db, env, 0);
        CKERR(r);
    assert(db);
    db->set_errfile(db, stderr);
    r = db->open(db, null_txn, "foo.db", "main", DB_BTREE, DB_CREATE, 0666);
        CKERR(r);
    assert(db);
}

static void close_db(void) {
    assert(env && db && !cursor);
    r = db->close(db, 0);
        CKERR(r);
    db = NULL;
}

static void setup_cursor(void) {
    assert(env && db && !cursor);
    r = db->cursor(db, NULL, &cursor, 0);
        CKERR(r);
    assert(cursor);
}

static void close_cursor(void) {
    assert(env && db && cursor);
    r = cursor->c_close(cursor);
        CKERR(r);
    cursor = NULL;
}

static void insert(char k, char d) {
    DBT key;
    DBT data;
    r = db->put(db, null_txn, dbt_init(&key, &k, sizeof(k)), dbt_init(&data, &d, sizeof(d)), 0);
        CKERR(r);
}

static void c_get(uint32_t flag, char key_expect, char data_expect) {
    DBT key;
    DBT data;

    r = cursor->c_get(cursor, dbt_init(&key, 0, 0), dbt_init(&data, 0, 0), flag);
        CKERR(r);
    assert(key.size == sizeof(key_expect));
    assert(data.size == sizeof(data_expect));
    char got_key  = *(char*)key.data;
    char got_data = *(char*)data.data;
    if (verbose &&
        (got_key != key_expect || got_data != data_expect)) {
        printf("c_get(%u) Expect (%c,%c)\n"
               "   Got (%c,%c)\n",
               flag, key_expect, data_expect, got_key, got_data);
    }
    assert(got_key  == key_expect);
    assert(got_data == data_expect);
}

static void test_skip_key(uint32_t flag, bool is_next) {
    setup_env();
    setup_db();
    setup_cursor();

    /* ********************************************************************** */

    char key           = 'g';
    char data          = 'g';
    int forward = is_next ? 1 : -1;

    insert(key, data);
    insert((char)(key + forward), data);
    c_get(flag, key, data);
    insert(key, (char)(data + forward));
    c_get(flag, (char)(key + forward), data);

    /* ********************************************************************** */
    close_cursor();
    close_db();
    close_env();
}

static void run_test(void) {
    /* ********************************************************************** */
    /* Test DB_NEXT works properly. */
    test_skip_key(DB_NEXT, true);
    /* ********************************************************************** */
    /* Test DB_PREV works properly. */
    test_skip_key(DB_PREV, false);
}

int
test_main(int argc, char *const argv[]) {

    parse_args(argc, argv);
  
    
    run_test();

    return 0;
}
