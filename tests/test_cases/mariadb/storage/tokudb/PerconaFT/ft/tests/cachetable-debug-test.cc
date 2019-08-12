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

static void
cachetable_debug_test (int n) {
    const int test_limit = n;
    int r;
    CACHETABLE ct;
    toku_cachetable_create(&ct, test_limit, ZERO_LSN, nullptr);
    const char *fname1 = TOKU_TEST_FILENAME;
    unlink(fname1);
    CACHEFILE f1;
    r = toku_cachetable_openf(&f1, ct, fname1, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO); assert(r == 0);

    int num_entries, hash_size; long size_current, size_limit;
    toku_cachetable_get_state(ct, &num_entries, &hash_size, &size_current, &size_limit);
    assert(num_entries == 0);
    assert(size_current == 0);
    assert(size_limit == n);
    // printf("%d %d %ld %ld\n", num_entries, hash_size, size_current, size_limit);

    int i;
    for (i=1; i<=n; i++) {
        const int item_size = 1;
        uint32_t hi;
        hi = toku_cachetable_hash(f1, make_blocknum(i));
        CACHETABLE_WRITE_CALLBACK wc = def_write_callback(NULL);
        toku_cachetable_put(f1, make_blocknum(i), hi, (void *)(long)i, make_pair_attr(item_size), wc, put_callback_nop);

        void *v; int dirty; long long pinned; long pair_size;
        r = toku_cachetable_get_key_state(ct, make_blocknum(i), f1, &v, &dirty, &pinned, &pair_size);
        assert(r == 0);
        assert(v == (void *)(long)i);
        assert(dirty == CACHETABLE_DIRTY);
        assert(pinned == 1);
        assert(pair_size == item_size);

        r = toku_test_cachetable_unpin(f1, make_blocknum(i), hi, CACHETABLE_CLEAN, make_pair_attr(1));
        assert(r == 0);

        toku_cachetable_get_state(ct, &num_entries, &hash_size, &size_current, &size_limit);
        assert(num_entries == i);
        assert(size_current == i);
        assert(size_limit == n);

        if (verbose) toku_cachetable_print_state(ct);
    }
    toku_cachetable_verify(ct);

    toku_cachefile_close(&f1, false, ZERO_LSN);
    toku_cachetable_close(&ct);
}

int
test_main(int argc, const char *argv[]) {
    default_parse_args(argc, argv);
    cachetable_debug_test(8);
    return 0;
}
