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

#include <toku_assert.h>
#include <locktree/locktree.h>

int main(void) {
    toku::txnid_set set;
    set.create();
    // make sure this set is a real set
    for (size_t i = 0; i < 5; i++) {
        set.add(0);
        invariant(set.size() == 1);
    }
    set.add(1);
    set.add(100);
    invariant(set.size() == 3);
    invariant(!set.contains(2));
    invariant(!set.contains(99));
    invariant(!set.contains(101));
    invariant(set.contains(100));
    invariant(set.contains(1));

    // go through the set and make sure we saw everything
    bool saw0 = false, saw1 = false, saw100 = false;
    for (size_t i = 0; i < set.size(); i++) {
        TXNID x = set.get(i);
        if (x == 0) {
            invariant(!saw0);
            saw0 = true;
        } else if (x == 1) {
            invariant(!saw1);
            saw1 = true;
        } else if (x == 100) {
            invariant(!saw100);
            saw100 = true;
        } else {
            assert(false);
        }
    }
    invariant(saw0);
    invariant(saw1);
    invariant(saw100);

    // make sure we see 0 and 100 but not 1
    set.remove(1);
    saw0 = false;
    saw100 = false;
    for (size_t i = 0; i < set.size(); i++) {
        TXNID x = set.get(i);
        if (x == 0) {
            invariant(!saw0);
            saw0 = true;
        } else if (x == 100) {
            invariant(!saw100);
            saw100 = true;
        } else {
            assert(false);
        }
    }
    invariant(saw0);
    invariant(saw100);

    // removing non-existant things is okay
    set.remove(0);
    set.remove(100);
    set.remove(1);
    set.remove(1010101);
    set.remove(1212121);

    // empty out what we know is in there
    set.remove(100);
    set.remove(0);
    invariant(set.size() == 0);
    set.destroy();
}
