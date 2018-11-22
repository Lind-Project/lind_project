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

#include "loader/dbufio.h"
#include <stdio.h>
#include <fcntl.h>
#include <toku_assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

enum { N  = 5 };
enum { M = 10 };
static void test1 (size_t chars_per_file, size_t UU(bytes_per_read)) {
    int fds[N];
    char fnames[N][100];
    size_t n_read[N];
    int UU(n_live)=N;
    for (int i=0; i<N; i++) {
	snprintf(fnames[i], 100, "dbufio-test-destroy-file%d.data", i);
	unlink(fnames[i]);
	fds[i] = open(fnames[i], O_CREAT|O_RDWR, S_IRWXU);
	//printf("fds[%d]=%d is %s\n", i, fds[i], fnames[i]);
	assert(fds[i]>=0);
	n_read[i]=0;
	for (size_t j=0; j<chars_per_file; j++) {
	    unsigned char c = (i+j)%256;
	    int r = toku_os_write(fds[i], &c, 1);
	    if (r!=0) {
                int er = get_maybe_error_errno();
                printf("fds[%d]=%d r=%d errno=%d (%s)\n", i, fds[i], r, er, strerror(er));
            }
	    assert(r==0);
	}
	{
	    int r = lseek(fds[i], 0, SEEK_SET);
	    assert(r==0);
	}
	
    }
    DBUFIO_FILESET bfs;
    {
	int r = create_dbufio_fileset(&bfs, N, fds, M, false);
	assert(r==0);
    }

    { int r = panic_dbufio_fileset(bfs, EIO); assert(r == 0); }

    {
	int r = destroy_dbufio_fileset(bfs);
	assert(r==0);
    }
    for (int i=0; i<N; i++) {
	{
	    int r = unlink(fnames[i]);
	    assert(r==0);
	}
	{
	    int r = close(fds[i]);
	    assert(r==0);
	}
	assert(n_read[i]==0);
    }
}

				  

int main (int argc __attribute__((__unused__)), char *argv[]__attribute__((__unused__))) {
//    test1(0, 1);
//    test1(1, 1);
//    test1(15, 1);
//    test1(100, 1);
    test1(30, 3); // 3 and M are relatively prime.  But 3 divides the file size.
    return 0;
}
