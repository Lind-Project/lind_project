# wcstok.m4 serial 2
dnl Copyright (C) 2011-2018 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_WCSTOK],
[
  AC_REQUIRE([gl_WCHAR_H_DEFAULTS])
  AC_CHECK_FUNCS_ONCE([wcstok])
  if test $ac_cv_func_wcstok = no; then
    HAVE_WCSTOK=0
  fi
])
