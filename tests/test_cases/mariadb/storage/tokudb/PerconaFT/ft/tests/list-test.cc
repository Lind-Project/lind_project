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

#include "toku_list.h"


#include "test.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

struct testlist {
    struct toku_list next;
    int tag;
};

static void testlist_init (struct testlist *tl, int tag) {
    tl->tag = tag;
}

static void test_push_pop (int n) {
    int i;
    struct toku_list head;

    toku_list_init(&head);
    for (i=0; i<n; i++) {
        struct testlist *tl = (struct testlist *) toku_malloc(sizeof *tl);
        assert(tl);
        testlist_init(tl, i);
        toku_list_push(&head, &tl->next);
        assert(!toku_list_empty(&head));
    }
    for (i=n-1; i>=0; i--) {
        struct toku_list *list;
        struct testlist *tl;

        list = toku_list_head(&head);
        tl  = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == 0);
        list = toku_list_tail(&head);
        tl = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == i);
        list = toku_list_pop(&head);
        tl = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == i);
        toku_free(tl);
    }
    assert(toku_list_empty(&head));
}

static void test_push_pop_head (int n) {
    int i;
    struct toku_list head;

    toku_list_init(&head);
    for (i=0; i<n; i++) {
        struct testlist *tl = (struct testlist *) toku_malloc(sizeof *tl);
        assert(tl);
        testlist_init(tl, i);
        toku_list_push(&head, &tl->next);
        assert(!toku_list_empty(&head));
    }
    for (i=0; i<n; i++) {
        struct toku_list *list;
        struct testlist *tl;

        list = toku_list_head(&head);
        tl  = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == i);
        list = toku_list_tail(&head);
        tl = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == n-1);

        list = toku_list_pop_head(&head);
        tl = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == i);
        toku_free(tl);
    }
    assert(toku_list_empty(&head));
}

static void test_push_head_pop (int n) {
    int i;
    struct toku_list head;

    toku_list_init(&head);
    for (i=0; i<n; i++) {
        struct testlist *tl = (struct testlist *) toku_malloc(sizeof *tl);
        assert(tl);
        testlist_init(tl, i);
        toku_list_push_head(&head, &tl->next);
        assert(!toku_list_empty(&head));
    }
    for (i=0; i<n; i++) {
        struct toku_list *list;
        struct testlist *tl;

        list = toku_list_head(&head);
        tl  = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == n-1);
        list = toku_list_tail(&head);
        tl = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == i);

        list = toku_list_pop(&head);
        tl = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == i);
        toku_free(tl);
    }
    assert(toku_list_empty(&head));
}

#if 0
// cant move an empty list
static void test_move_empty (void) {
    struct toku_list h1, h2;

    toku_list_init(&h1);
    toku_list_init(&h2);
    toku_list_move(&h1, &h2);
    assert(toku_list_empty(&h2));
    assert(toku_list_empty(&h1));
}
#endif

static void test_move (int n) {
    struct toku_list h1, h2;
    int i;

    toku_list_init(&h1);
    toku_list_init(&h2);
    for (i=0; i<n; i++) {
        struct testlist *tl = (struct testlist *) toku_malloc(sizeof *tl);
        assert(tl);
        testlist_init(tl, i);
        toku_list_push(&h2, &tl->next);
    }
    toku_list_move(&h1, &h2);
    assert(!toku_list_empty(&h1));
    assert(toku_list_empty(&h2));
    i = 0;
    while (!toku_list_empty(&h1)) {
        struct toku_list *list = toku_list_pop_head(&h1);
        struct testlist *tl = toku_list_struct(list, struct testlist, next);
        assert(tl->tag == i);
        toku_free(tl);
        i += 1;
    }
    assert(i == n);
}

int
test_main(int argc, const char *argv[]) {
    default_parse_args(argc, argv);
    test_push_pop(0);
    test_push_pop(8);
    test_push_pop_head(0);
    test_push_pop_head(8);
    test_push_head_pop(8);
    test_move(1);
    test_move(8);
    //    test_move_empty();

    return 0;
}

