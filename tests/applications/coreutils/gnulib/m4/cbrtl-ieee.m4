# cbrtl-ieee.m4 serial 1
dnl Copyright (C) 2012-2018 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This macro is in a separate file (not in cbrtl.m4 and not inlined in the
dnl module description), so that gl_FUNC_CBRTL can test whether 'aclocal' has
dnl found uses of this macro.

AC_DEFUN([gl_FUNC_CBRTL_IEEE],
[
  m4_divert_text([INIT_PREPARE], [gl_cbrtl_required=ieee])
  AC_REQUIRE([gl_FUNC_CBRTL])
])
