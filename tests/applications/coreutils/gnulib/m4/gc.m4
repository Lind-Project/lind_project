# gc.m4 serial 10
dnl Copyright (C) 2005-2018 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_GC],
[
  AC_SUBST([LIB_CRYPTO])
  AC_ARG_WITH([libgcrypt],
    AS_HELP_STRING([--with-libgcrypt], [use libgcrypt for low-level crypto]),
    libgcrypt=$withval, libgcrypt=no)
  if test "$libgcrypt" != no; then
    # gc-libgcrypt.c will fail on startup if we don't have
    # version 1.4.4 or later, so test for it early. */
    gl_good_gcrypt=no
    m4_ifdef([AM_PATH_LIBGCRYPT],
      [AM_PATH_LIBGCRYPT([1.4.4], [gl_good_gcrypt=yes],
        [AC_MSG_ERROR([libgcrypt is too old])])])
    if test "x$gl_good_gcrypt" != xno; then
      AC_LIB_HAVE_LINKFLAGS([gcrypt], [gpg-error], [#include <gcrypt.h>])
    else
      AC_MSG_ERROR([libgcrypt not found])
    fi
  fi
])
