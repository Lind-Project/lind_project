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

/* a powerfail test. */
#include "test.h"
#include <stdio.h>

static void print_usage (void) {
    printf("Two modes:\n");
    printf(" ./powerfail --write\n");
    printf("      creates a database, and writes numbers out to stdout.  While this is running you can crash the machine and record\n");
    printf("      the last number printed.  It may be helpful to run this program via ssh so that you can see the output after the\n");
    printf("      machine crashes.  It would be wrong to pipe stdout into a file on the machine that crashes, since if we think there\n");
    printf("      is any possibility that recovery will fail, then the system cannot be trusted to restore that file properly either.\n");
    printf("  ./powerfail --check N\n");
    printf("      Feed the recorded number into the command line.  The system will check that transaction N committed properly and\n");
    printf("      that no more than one additional transaction committed.\n");
}


DB_ENV *env;
enum { N_DBS = 10 };
DB *dbs[N_DBS];
char dbname_template[]="foo%d.db";
const int envflags = DB_INIT_MPOOL|DB_THREAD|DB_CREATE |DB_INIT_LOCK|DB_PRIVATE | DB_INIT_LOG|DB_INIT_TXN|DB_RECOVER;

static void put (DB *db, DB_TXN *txn, long k, long v, int flags) {
    DBT key, val;
    int r = db->put(db, txn, dbt_init(&key, &k, sizeof(k)), dbt_init(&val, &v, sizeof(k)), flags);
    assert(r==0);
}

static void open_dbs (void) {
    int r;
    DB_TXN *txn = 0;
    r = env->txn_begin(env, 0, &txn, 0);                            CKERR(r);
    for (int i=0; i<N_DBS; i++) {
	char dbname[sizeof(dbname_template)+10];
	r = snprintf(dbname, sizeof(dbname), dbname_template, i);
	assert(r>0 && r<(int)sizeof(dbname));
	r = db_create(&dbs[i], env, 0);                                             CKERR(r);	
	r = dbs[i]->open(dbs[i], txn, dbname, NULL, DB_BTREE, DB_CREATE, 0666);     CKERR(r);
    }
    r = txn->commit(txn, 0);                                                        CKERR(r);
}

static void close_dbs (void) {
    for (int i=0; i<N_DBS; i++) {
	int r = dbs[i]->close(dbs[i], 0);                                           CKERR(r);
    }
	
}

static long shuffle (long l, int i) {
    (void)i;
    return l;
}

static void do_write (void) {
    int r;
    toku_os_recursive_delete(TOKU_TEST_FILENAME);
    toku_os_mkdir(TOKU_TEST_FILENAME, S_IRWXU+S_IRWXG+S_IRWXO);
    r = db_env_create(&env, 0);                                         CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags, S_IRWXU+S_IRWXG+S_IRWXO);      CKERR(r);

    open_dbs();
    // DB[0] contains the pairs TXN TXN
    // A transaction inserts a bunch of records where the vals all add up to 1.
    for (long N=0; 1; N++) {
	DB_TXN *txn = 0;
	r = env->txn_begin(env, 0, &txn, 0); CKERR(r);
	put(dbs[0], txn, N, N, 0);
	int sum=0;
	for (int i=1; i+1<N_DBS; i++) {
	    int rval = (random()%2048)-1024;
	    sum+=rval;
	    put(dbs[i], txn, shuffle(N, i), rval, (i%2==0) ? 0 : 0); // even numbered databases are overwritten
	}
	put(dbs[N_DBS-1],txn,  N, sum, 0);
	r = txn->commit(txn, 0); CKERR(r);
	printf("%ld\n", N);
    }
}

static void scan(DB *db, DB_TXN *txn,
		 void (*reduce)(DBT *k, DBT *v, void *extra), void *extra) {
    DBC *cursor;
    int r = db->cursor(db, txn, &cursor, 0);    CKERR(r);
    DBT key, val;
    memset(&key, 0, sizeof(key));
    memset(&val, 0, sizeof(val));
    key.flags = DB_DBT_MALLOC;
    val.flags = DB_DBT_MALLOC;
    int n=0;
    while (0==(r = cursor->c_get(cursor, &key, &val, DB_NEXT))) {
	reduce(&key, &val, extra);
	n++;
    }
    printf("n=%d\n", n);
    r = cursor->c_close(cursor);                CKERR(r);
    toku_free(key.data);
    toku_free(val.data);
}

static long maxl (long a, long b) {
    if (a<b) return b; else return a;
}

static void maxf (DBT *k, DBT *v, void *extrav) {
    long *CAST_FROM_VOIDP(extra, extrav);
    long *CAST_FROM_VOIDP(kd, k->data);
    long *CAST_FROM_VOIDP(vd, v->data);
    extra[0] = maxl(extra[0], *kd);
    extra[1] = maxl(extra[0], *vd);
}

static void do_check (long N) {
    int r;
    r = db_env_create(&env, 0);                                         CKERR(r);
    r = env->open(env, TOKU_TEST_FILENAME, envflags, S_IRWXU+S_IRWXG+S_IRWXO);      CKERR(r);
    open_dbs();
    DB_TXN *txn = 0;
    r = env->txn_begin(env, 0, &txn, 0);                                CKERR(r);
    long maxp[2]={0,0};
    scan(dbs[0], txn, maxf, &maxp);
    printf("max k,v = %ld, %ld\n", maxp[0], maxp[1]);
    assert(maxp[0]==maxp[1]);
    assert(maxp[0]>=N);
    r = txn->commit(txn, 0);                                            CKERR(r);
    close_dbs();
    r = env->close(env, 0);                                             CKERR(r);
    
}

int test_main (int argc, char * const argv[]) {
    assert(argc>=2 && argc<=3);
    if (strcmp(argv[1], "--write")==0) {
	assert(argc==2);
	do_write();
    } else if (strcmp(argv[1], "--check")==0) {
	assert(argc==3);
	char *end;
	errno=0;
	long N=strtol(argv[2], &end, 10);
	assert(0==errno && 0==*end);
	do_check(N);
    } else if (strcmp(argv[1],"-h")==0) {
	print_usage();
    }
    return 0;
}
