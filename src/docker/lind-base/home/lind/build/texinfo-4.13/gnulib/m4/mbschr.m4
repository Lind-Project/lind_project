# mbschr.m4 serial 1
dnl Copyright (C) 2007 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_MBSCHR],
[
  gl_PREREQ_MBSCHR
])

# Prerequisites of lib/mbschr.c.
AC_DEFUN([gl_PREREQ_MBSCHR], [
  AC_REQUIRE([gl_FUNC_MBRTOWC])
  :
])
