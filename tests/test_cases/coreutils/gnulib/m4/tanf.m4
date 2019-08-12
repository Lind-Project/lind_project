# tanf.m4 serial 3
dnl Copyright (C) 2011-2018 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_TANF],
[
  AC_REQUIRE([gl_MATH_H_DEFAULTS])
  AC_REQUIRE([gl_FUNC_TAN])

  dnl Persuade glibc <math.h> to declare tanf().
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])

  dnl Test whether tanf() exists. Assume that tanf(), if it exists, is
  dnl defined in the same library as tan().
  save_LIBS="$LIBS"
  LIBS="$LIBS $TAN_LIBM"
  AC_CHECK_FUNCS([tanf])
  LIBS="$save_LIBS"
  if test $ac_cv_func_tanf = yes; then
    TANF_LIBM="$TAN_LIBM"
  else
    HAVE_TANF=0
    dnl If the function is declared but does not appear to exist, it may be
    dnl defined as an inline function. In order to avoid a conflict, we have
    dnl to define rpl_tanf, not tanf.
    AC_CHECK_DECLS([tanf], [REPLACE_TANF=1], , [[#include <math.h>]])
    TANF_LIBM="$TAN_LIBM"
  fi
  AC_SUBST([TANF_LIBM])
])
