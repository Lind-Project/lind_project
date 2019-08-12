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

// This test verifies that queries that have a provisional delete at the end of a basement node work.
// The issue is that when we read off the end of a basement node, the next basement node may not be available memory, so we
// need to release the ydb lock and try again. This test verifies that this scenario works by having many deletes
// and a small cachetable.

#include "test.h"

const int envflags = DB_INIT_MPOOL|DB_CREATE|DB_THREAD |DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_TXN|DB_PRIVATE;

int test_main (int argc, char * const argv[]) {
  parse_args(argc, argv);
  int r;
  toku_os_recursive_delete(TOKU_TEST_FILENAME);
  toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
  DB_ENV *env;
  r = db_env_create(&env, 0);                                                         CKERR(r);
  env->set_errfile(env, stderr);
  // set a cachetable size of 10K
  uint32_t cachesize = 100*1024;
  // as part of #4503, arbitrarily increasing sizze of cachetable
  // the idea is to make it small enough such that all data 
  // cannot fit in the cachetable, but big enough such that 
  // we don't have cachet pressure
  r = env->set_cachesize(env, 0, 4*cachesize, 1); CKERR(r);
  r = env->set_lg_bsize(env, 4096);                                                   CKERR(r);
  r = env->set_default_bt_compare(env, int64_dbt_cmp); CKERR(r);
  r = env->open(env, TOKU_TEST_FILENAME, envflags, S_IRWXU+S_IRWXG+S_IRWXO);                      CKERR(r);
    
  DB *db;
  {
    DB_TXN *txna;
    r = env->txn_begin(env, NULL, &txna, 0);                                        CKERR(r);

    r = db_create(&db, env, 0);                                                     CKERR(r);
    r = db->set_pagesize(db, 4096);
    CKERR(r);
    r = db->set_readpagesize(db, 1024);
    CKERR(r);
    r = db->open(db, txna, "foo.db", NULL, DB_BTREE, DB_CREATE, 0666);              CKERR(r);

    r = txna->commit(txna, 0);                                                      CKERR(r);
  }
  if (verbose) printf("starting insertion of even elements\n");
  //
  // now insert a bunch of elements
  //
  DB_TXN* txn;
  r = env->txn_begin(env, NULL, &txn, 0);
  CKERR(r);
  for (uint32_t i = 0; i < cachesize; i++) {
      DBT key,val;
      uint64_t key_data = 2*i;
      uint64_t val_data = 4*i;
      r = db->put(
          db,
          txn,
          dbt_init(&key, &key_data, sizeof(key_data)),
          dbt_init(&val, &val_data, sizeof(val_data)),
          0
          );       
      CKERR(r);
  }
  r = txn->commit(txn, 0);
  CKERR(r);

  // this transaction will read all even keys inserted above
  DB_TXN* txn_first = NULL;
  r = env->txn_begin(env, NULL, &txn_first, DB_TXN_SNAPSHOT);
  CKERR(r);

  if (verbose) printf("starting insertion of odd elements and deletion of even elements\n");
  r = env->txn_begin(env, NULL, &txn, 0);
  CKERR(r);
  for (uint32_t i = 0; i < cachesize; i++) {
      //
      // insert odd values, and delete even values
      //
      DBT key,val;
      uint64_t key_data = 2*i+1;
      uint64_t val_data = 4*i+2;
      dbt_init(&key, &key_data, sizeof(key_data));
      dbt_init(&val, &val_data, sizeof(val_data));
      r = db->put(
          db,
          txn,
          &key,
          &val,
          0
          );       
      CKERR(r);

      key_data = 2*i;
      r = db->del(db, txn, &key, DB_DELETE_ANY);
      CKERR(r);
  }
  r = txn->commit(txn, 0);
  CKERR(r);
  
  // this transaction will read all odd keys inserted in the second round
  DB_TXN* txn_second = NULL;
  r = env->txn_begin(env, NULL, &txn_second, DB_TXN_SNAPSHOT);
  CKERR(r);

  DBC* cursor_first = NULL;
  DBC* cursor_second = NULL;  
  r = db->cursor(db, txn_first, &cursor_first, 0); 
  CKERR(r);
  r = db->cursor(db, txn_second, &cursor_second, 0); 
  CKERR(r);

  DBT key, val;
  memset(&key, 0, sizeof(key));
  memset(&val, 0, sizeof(val));
  if (verbose) printf("starting cursor first query\n");
  // now let's do the cursor reads and verify that all the data is read properly
  for (uint32_t i = 0; i < cachesize; i++) {
      r = cursor_first->c_get(cursor_first, &key, &val, DB_NEXT);
      CKERR(r);
      assert(key.size == 8);
      assert(val.size == 8);
      assert(*(uint64_t *)key.data == 2*i);
      assert(*(uint64_t *)val.data == 4*i);
  }
  r = cursor_first->c_get(cursor_first, &key, &val, DB_NEXT);
  CKERR2(r, DB_NOTFOUND);
  
  if (verbose) printf("starting cursor second query\n");
  // now let's do the cursor reads and verify that all the data is read properly
  for (uint32_t i = 0; i < cachesize; i++) {
      r = cursor_second->c_get(cursor_second, &key, &val, DB_NEXT);
      CKERR(r);
      assert(key.size == 8);
      assert(val.size == 8);
      assert(*(uint64_t *)key.data == 2*i+1);
      assert(*(uint64_t *)val.data == 4*i+2);
  }
  r = cursor_second->c_get(cursor_second, &key, &val, DB_NEXT);
  CKERR2(r, DB_NOTFOUND);  

  if (verbose) printf("cleaning up\n");

  r = cursor_first->c_close(cursor_first);
  CKERR(r);
  r = cursor_second->c_close(cursor_second);
  CKERR(r);

  r = txn_first->commit(txn_first,0);
  CKERR(r);
  r = txn_second->commit(txn_second,0);
  CKERR(r);

  r = db->close(db, 0);
  CKERR(r);
  r = env->close(env, 0);
  CKERR(r);
    
  return 0;
}
