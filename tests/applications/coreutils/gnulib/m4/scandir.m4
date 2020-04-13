# scandir.m4 serial 2
dnl Copyright (C) 2009-2018 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_SCANDIR],
[
  AC_REQUIRE([gl_DIRENT_H_DEFAULTS])

  dnl Persuade glibc and Solaris <dirent.h> to declare scandir().
  AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])

  AC_CHECK_FUNCS([scandir])
  if test $ac_cv_func_scandir = no; then
    HAVE_SCANDIR=0
  fi
])

# Prerequisites of lib/scandir.c.
AC_DEFUN([gl_PREREQ_SCANDIR], [:])
