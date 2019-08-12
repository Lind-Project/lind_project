/* Test of <netdb.h> substitute in C++ mode.
   Copyright (C) 2011-2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Bruno Haible <bruno@clisp.org>, 2011.  */

#define GNULIB_NAMESPACE gnulib
#include <config.h>

#include <netdb.h>

#include "signature.h"


#if GNULIB_TEST_GETADDRINFO
SIGNATURE_CHECK (GNULIB_NAMESPACE::getaddrinfo, int,
                 (const char *, const char *, const struct addrinfo *,
                  struct addrinfo **));
SIGNATURE_CHECK (GNULIB_NAMESPACE::freeaddrinfo, void, (struct addrinfo *));
SIGNATURE_CHECK (GNULIB_NAMESPACE::gai_strerror, const char *, (int));
SIGNATURE_CHECK (GNULIB_NAMESPACE::getnameinfo, int,
                 (const struct sockaddr *, socklen_t, char *, socklen_t,
                  char *, socklen_t, int));
#endif


int
main ()
{
}
