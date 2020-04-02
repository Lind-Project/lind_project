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
cleanup_and_free(struct simple_dbt *v) {
    if (v->data) toku_free(v->data);
    v->data = NULL;
    v->len = 0;
}

static void
cleanup(struct simple_dbt *v) {
    v->data = NULL;
    v->len = 0;
}

static void ybt_test0 (void) {
    struct simple_dbt v0 = {0,0}, v1 = {0,0};
    DBT  t0,t1;
    toku_init_dbt(&t0);
    toku_init_dbt(&t1);
    {
	const void *temp1 = "hello";
        toku_dbt_set(6, temp1, &t0, &v0);
    }
    {
        const void *temp2 = "foo";
	toku_dbt_set(  4, temp2, &t1, &v1);
    }
    assert(t0.size==6);
    assert(strcmp((char*)t0.data, "hello")==0); 
    assert(t1.size==4);
    assert(strcmp((char*)t1.data, "foo")==0);

    {
        const void *temp3 = "byebye";
	toku_dbt_set(7, temp3, &t1, &v0);      /* Use v0, not v1 */
    }
    // This assertion would be wrong, since v0 may have been realloc'd, and t0.data may now point
    // at the wrong place
    //assert(strcmp(t0.data, "byebye")==0);     /* t0's data should be changed too, since it used v0 */
    assert(strcmp((char*)t1.data, "byebye")==0);

    cleanup_and_free(&v0);
    cleanup_and_free(&v1);
    

    /* See if we can probe to find out how big something is by setting ulen=0 with YBT_USERMEM */
    toku_init_dbt(&t0);
    t0.flags = DB_DBT_USERMEM;
    t0.ulen  = 0;
    {
        const void *temp4 = "hello";
	toku_dbt_set(6, temp4, &t0, 0);
    }
    assert(t0.data==0);
    assert(t0.size==6);

    /* Check realloc. */
    toku_init_dbt(&t0);
    t0.flags = DB_DBT_REALLOC;
    cleanup(&v0);
    {
        const void *temp5 = "internationalization";
	toku_dbt_set(21, temp5, &t0, &v0);
    }
    assert(v0.data==0); /* Didn't change v0 */
    assert(t0.size==21);
    assert(strcmp((char*)t0.data, "internationalization")==0);

    {
        const void *temp6 = "provincial";
	toku_dbt_set(11, temp6, &t0, &v0);
    }
    assert(t0.size==11);
    assert(strcmp((char*)t0.data, "provincial")==0);
    
    toku_free(t0.data);
    
}

int
test_main (int argc __attribute__((__unused__)), const char *argv[] __attribute__((__unused__))) {
    ybt_test0();
    return 0;
}
