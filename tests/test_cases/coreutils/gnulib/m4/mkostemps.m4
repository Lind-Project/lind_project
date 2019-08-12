# mkostemps.m4 serial 2
dnl Copyright (C) 2009-2018 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_MKOSTEMPS],
[
  AC_REQUIRE([gl_STDLIB_H_DEFAULTS])

  dnl Persuade glibc <stdlib.h> to declare mkostemps().
  AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])

  AC_CHECK_FUNCS_ONCE([mkostemps])
  if test $ac_cv_func_mkostemps != yes; then
    HAVE_MKOSTEMPS=0
  fi
])
