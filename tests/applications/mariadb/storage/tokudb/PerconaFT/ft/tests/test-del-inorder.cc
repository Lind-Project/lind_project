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

/* The goal of this test.  Make sure that inserts stay behind deletes. */


#include "test.h"


static TOKUTXN const null_txn = 0;

enum { NODESIZE = 1024, KSIZE=NODESIZE-100, TOKU_PSIZE=20 };

CACHETABLE ct;
FT_HANDLE t;
const char *fname = TOKU_TEST_FILENAME;

static void
doit (void) {
    BLOCKNUM nodea,nodeb;

    int r;

    toku_cachetable_create(&ct, 16*1024, ZERO_LSN, nullptr);
    unlink(fname);
    r = toku_open_ft_handle(fname, 1, &t, NODESIZE, NODESIZE, TOKU_DEFAULT_COMPRESSION_METHOD, ct, null_txn, toku_builtin_compare_fun);
    assert(r==0);

    toku_testsetup_initialize();  // must precede any other toku_testsetup calls

    r = toku_testsetup_leaf(t, &nodea, 1, NULL, NULL);
    assert(r==0);

    r = toku_testsetup_nonleaf(t, 1, &nodeb, 1, &nodea, 0, 0);
    assert(r==0);

    r = toku_testsetup_insert_to_nonleaf(t, nodeb, FT_DELETE_ANY, "hello", 6, 0, 0);
    assert(r==0);

    r = toku_testsetup_root(t, nodeb);
    assert(r==0);
    
    DBT k,v;
    toku_ft_insert(t,
                   toku_fill_dbt(&k, "hello", 6),
                   toku_fill_dbt(&v, "there", 6),
                   null_txn);

    memset(&v, 0, sizeof(v));
    struct check_pair pair = {6, "hello", 6, "there", 0};
    r = toku_ft_lookup(t, &k, lookup_checkf, &pair);
    assert(r==0);
    assert(pair.call_count == 1);

    r = toku_close_ft_handle_nolsn(t, 0);    assert(r==0);
    toku_cachetable_close(&ct);
}

int
test_main (int argc __attribute__((__unused__)), const char *argv[] __attribute__((__unused__))) {
    doit();
    return 0;
}
