dnl
dnl This file contains Zend specific autoconf functions.
dnl

AC_DEFUN([LIBZEND_CHECK_INT_TYPE],[
AC_MSG_CHECKING(for $1)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#if HAVE_INTTYPES_H
#include <inttypes.h>
#elif HAVE_STDINT_H
#include <stdint.h>
#endif]],
[[if (($1 *) 0)
  return 0;
if (sizeof ($1))
  return 0;
]])],[
  AC_DEFINE_UNQUOTED([HAVE_]translit($1,a-z_-,A-Z__), 1,[Define if $1 type is present. ])
  AC_MSG_RESULT(yes)
], [AC_MSG_RESULT(no)
])dnl
])

AC_DEFUN([LIBZEND_BASIC_CHECKS],[

AC_REQUIRE([AC_PROG_YACC])
AC_REQUIRE([AC_PROG_CC])
AC_REQUIRE([AC_PROG_CC_C_O])
AC_REQUIRE([AC_HEADER_STDC])

LIBZEND_BISON_CHECK

dnl Ugly hack to get around a problem with gcc on AIX.
if test "$CC" = "gcc" -a "$ac_cv_prog_cc_g" = "yes" -a \
   "`uname -sv`" = "AIX 4"; then
	CFLAGS=`echo $CFLAGS | sed -e 's/-g//'`
fi

dnl Hack to work around a Mac OS X cpp problem
dnl Known versions needing this workaround are 5.3 and 5.4
if test "$ac_cv_prog_gcc" = "yes" -a "`uname -s`" = "Rhapsody"; then
        CPPFLAGS="$CPPFLAGS -traditional-cpp"
fi

AC_CHECK_HEADERS(
inttypes.h \
stdint.h \
limits.h \
malloc.h \
unistd.h \
sys/types.h \
sys/time.h \
signal.h \
unix.h \
cpuid.h \
dlfcn.h)

AC_TYPE_SIZE_T

AC_DEFUN([LIBZEND_LIBDL_CHECKS],[
AC_CHECK_LIB(dl, dlopen, [LIBS="-ldl $LIBS"])
AC_CHECK_FUNC(dlopen,[AC_DEFINE(HAVE_LIBDL, 1,[ ])])
])

AC_DEFUN([LIBZEND_DLSYM_CHECK],[
dnl
dnl Ugly hack to check if dlsym() requires a leading underscore in symbol name.
dnl
AC_MSG_CHECKING([whether dlsym() requires a leading underscore in symbol names])
_LT_AC_TRY_DLOPEN_SELF([
  AC_MSG_RESULT(no)
], [
  AC_MSG_RESULT(yes)
  AC_DEFINE(DLSYM_NEEDS_UNDERSCORE, 1, [Define if dlsym() requires a leading underscore in symbol names. ])
], [
  AC_MSG_RESULT(no)
], [])
])

dnl This is required for QNX and may be some BSD derived systems
AC_CHECK_TYPE( uint, unsigned int )
AC_CHECK_TYPE( ulong, unsigned long )

dnl Check if int32_t and uint32_t are defined
LIBZEND_CHECK_INT_TYPE(int32_t)
LIBZEND_CHECK_INT_TYPE(uint32_t)

dnl Checks for library functions.
AC_FUNC_ALLOCA
AC_CHECK_FUNCS(memcpy strdup getpid kill strtod strtol finite fpclass sigsetjmp)
AC_ZEND_BROKEN_SPRINTF

AC_CHECK_DECLS([isfinite, isnan, isinf], [], [], [[#include <math.h>]])

ZEND_FP_EXCEPT

ZEND_CHECK_FLOAT_PRECISION

dnl test whether double cast to long preserves least significant bits
AC_MSG_CHECKING(whether double cast to long preserves least significant bits)

AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <limits.h>

int main()
{
	if (sizeof(long) == 4) {
		double d = (double) LONG_MIN * LONG_MIN + 2e9;

		if ((long) d == 2e9 && (long) -d == -2e9) {
			exit(0);
		}
	} else if (sizeof(long) == 8) {
		double correct = 18e18 - ((double) LONG_MIN * -2); /* Subtract ULONG_MAX + 1 */

		if ((long) 18e18 == correct) { /* On 64-bit, only check between LONG_MAX and ULONG_MAX */
			exit(0);
		}
	}
	exit(1);
}
]])], [
  AC_DEFINE([ZEND_DVAL_TO_LVAL_CAST_OK], 1, [Define if double cast to long preserves least significant bits])
  AC_MSG_RESULT(yes)
], [
  AC_MSG_RESULT(no)
], [
  AC_MSG_RESULT(no)
])

])

AC_DEFUN([LIBZEND_ENABLE_DEBUG],[

AC_ARG_ENABLE(debug,
[  --enable-debug          Compile with debugging symbols],[
  ZEND_DEBUG=$enableval
],[
  ZEND_DEBUG=no
])

])

AC_DEFUN([LIBZEND_OTHER_CHECKS],[

AC_ARG_ENABLE(maintainer-zts,
[  --enable-maintainer-zts Enable thread safety - for code maintainers only!!],[
  ZEND_MAINTAINER_ZTS=$enableval
],[
  ZEND_MAINTAINER_ZTS=no
])

AC_ARG_ENABLE(inline-optimization,
[  --disable-inline-optimization
                          If building zend_execute.lo fails, try this switch],[
  ZEND_INLINE_OPTIMIZATION=$enableval
],[
  ZEND_INLINE_OPTIMIZATION=yes
])

AC_MSG_CHECKING(whether to enable thread-safety)
AC_MSG_RESULT($ZEND_MAINTAINER_ZTS)

AC_MSG_CHECKING(whether to enable inline optimization for GCC)
AC_MSG_RESULT($ZEND_INLINE_OPTIMIZATION)

AC_MSG_CHECKING(whether to enable Zend debugging)
AC_MSG_RESULT($ZEND_DEBUG)

if test "$ZEND_DEBUG" = "yes"; then
  AC_DEFINE(ZEND_DEBUG,1,[ ])
  echo " $CFLAGS" | grep ' -g' >/dev/null || DEBUG_CFLAGS="-g"
  if test "$CFLAGS" = "-g -O2"; then
  	CFLAGS=-g
  fi
  test -n "$GCC" && DEBUG_CFLAGS="$DEBUG_CFLAGS -Wall"
  test -n "$GCC" && test "$USE_MAINTAINER_MODE" = "yes" && \
    DEBUG_CFLAGS="$DEBUG_CFLAGS -Wmissing-prototypes -Wstrict-prototypes -Wmissing-declarations"
else
  AC_DEFINE(ZEND_DEBUG,0,[ ])
fi

test -n "$DEBUG_CFLAGS" && CFLAGS="$CFLAGS $DEBUG_CFLAGS"

if test "$ZEND_MAINTAINER_ZTS" = "yes"; then
  AC_DEFINE(ZTS,1,[ ])
  CFLAGS="$CFLAGS -DZTS"
fi

changequote({,})
if test -n "$GCC" && test "$ZEND_INLINE_OPTIMIZATION" != "yes"; then
  INLINE_CFLAGS=`echo $ac_n "$CFLAGS $ac_c" | sed s/-O[0-9s]*//`
else
  INLINE_CFLAGS="$CFLAGS"
fi
changequote([,])

AC_C_INLINE

AC_SUBST(INLINE_CFLAGS)

AC_MSG_CHECKING(target system is Darwin)
if echo "$target" | grep "darwin" > /dev/null; then
  AC_DEFINE([DARWIN], 1, [Define if the target system is darwin])
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
fi

dnl test and set the alignment define for ZEND_MM
dnl this also does the logarithmic test for ZEND_MM.
AC_MSG_CHECKING(for MM alignment and log values)

AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <stdio.h>

typedef union _mm_align_test {
  void *ptr;
  double dbl;
  long lng;
} mm_align_test;

#if (defined (__GNUC__) && __GNUC__ >= 2)
#define ZEND_MM_ALIGNMENT (__alignof__ (mm_align_test))
#else
#define ZEND_MM_ALIGNMENT (sizeof(mm_align_test))
#endif

int main()
{
  int i = ZEND_MM_ALIGNMENT;
  int zeros = 0;
  FILE *fp;

  while (i & ~0x1) {
    zeros++;
    i = i >> 1;
  }

  fp = fopen("conftest.zend", "w");
  fprintf(fp, "%d %d\n", ZEND_MM_ALIGNMENT, zeros);
  fclose(fp);

  exit(0);
}
]])], [
  LIBZEND_MM_ALIGN=`cat conftest.zend | cut -d ' ' -f 1`
  LIBZEND_MM_ALIGN_LOG2=`cat conftest.zend | cut -d ' ' -f 2`
  AC_DEFINE_UNQUOTED(ZEND_MM_ALIGNMENT, $LIBZEND_MM_ALIGN, [ ])
  AC_DEFINE_UNQUOTED(ZEND_MM_ALIGNMENT_LOG2, $LIBZEND_MM_ALIGN_LOG2, [ ])
], [], [
  dnl cross-compile needs something here
  LIBZEND_MM_ALIGN=8
])

AC_MSG_RESULT(done)

AC_CHECK_FUNCS(mremap)


AC_ARG_ENABLE(zend-signals,
[  --disable-zend-signals  whether to enable zend signal handling],[
  ZEND_SIGNALS=$enableval
],[
  ZEND_SIGNALS=yes
])

AC_CHECK_FUNC(sigaction, [
	AC_DEFINE(HAVE_SIGACTION, 1, [Whether sigaction() is available])
], [
	ZEND_SIGNALS=no
])
if test "$ZEND_SIGNALS" = "yes"; then
	AC_DEFINE(ZEND_SIGNALS, 1, [Use zend signal handling])
	CFLAGS="$CFLAGS -DZEND_SIGNALS"
fi

AC_MSG_CHECKING(whether to enable zend signal handling)
AC_MSG_RESULT($ZEND_SIGNALS)

])

AC_MSG_CHECKING(whether /dev/urandom exists)
if test -r "/dev/urandom" && test -c "/dev/urandom"; then
  AC_DEFINE([HAVE_DEV_URANDOM], 1, [Define if the target system has /dev/urandom device])
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
fi

AC_MSG_CHECKING(whether /dev/arandom exists)
if test -r "/dev/arandom" && test -c "/dev/arandom"; then
  AC_DEFINE([HAVE_DEV_ARANDOM], 1, [Define if the target system has /dev/arandom device])
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
fi

AC_ARG_ENABLE(gcc-global-regs,
[  --disable-gcc-global-regs
                          whether to enable GCC global register variables],[
  ZEND_GCC_GLOBAL_REGS=$enableval
],[
  ZEND_GCC_GLOBAL_REGS=yes
])
AC_MSG_CHECKING(for global register variables support)
if test "$ZEND_GCC_GLOBAL_REGS" != "no"; then
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#if defined(__GNUC__)
# define ZEND_GCC_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
#else
# define ZEND_GCC_VERSION 0
#endif
#if defined(__GNUC__) && ZEND_GCC_VERSION >= 4008 && defined(i386)
# define ZEND_VM_FP_GLOBAL_REG "%esi"
# define ZEND_VM_IP_GLOBAL_REG "%edi"
#elif defined(__GNUC__) && ZEND_GCC_VERSION >= 4008 && defined(__x86_64__)
# define ZEND_VM_FP_GLOBAL_REG "%r14"
# define ZEND_VM_IP_GLOBAL_REG "%r15"
#elif defined(__GNUC__) && ZEND_GCC_VERSION >= 4008 && defined(__powerpc64__)
# define ZEND_VM_FP_GLOBAL_REG "r28"
# define ZEND_VM_IP_GLOBAL_REG "r29"
#elif defined(__IBMC__) && ZEND_GCC_VERSION >= 4002 && defined(__powerpc64__)
# define ZEND_VM_FP_GLOBAL_REG "r28"
# define ZEND_VM_IP_GLOBAL_REG "r29"
#else
# error "global register variables are not supported"
#endif
typedef int (*opcode_handler_t)(void);
register void *FP  __asm__(ZEND_VM_FP_GLOBAL_REG);
register const opcode_handler_t *IP __asm__(ZEND_VM_IP_GLOBAL_REG);
int emu(const opcode_handler_t *ip, void *fp) {
	const opcode_handler_t *orig_ip = IP;
	void *orig_fp = FP;
	IP = ip;
	FP = fp;
	while ((*ip)());
	FP = orig_fp;
	IP = orig_ip;
}
  ]], [[
  ]])], [
    ZEND_GCC_GLOBAL_REGS=yes
  ], [
    ZEND_GCC_GLOBAL_REGS=no
  ])
fi
if test "$ZEND_GCC_GLOBAL_REGS" = "yes"; then
  AC_DEFINE([HAVE_GCC_GLOBAL_REGS], 1, [Define if the target system has support for global register variables])
else
  HAVE_GCC_GLOBAL_REGS=no
fi
AC_MSG_RESULT($ZEND_GCC_GLOBAL_REGS)

dnl
dnl Check if atof() accepts NAN
dnl
AC_CACHE_CHECK(whether atof() accepts NAN, ac_cv_atof_accept_nan,[
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <math.h>
#include <stdlib.h>

#ifdef HAVE_ISNAN
#define zend_isnan(a) isnan(a)
#elif defined(HAVE_FPCLASS)
#define zend_isnan(a) ((fpclass(a) == FP_SNAN) || (fpclass(a) == FP_QNAN))
#else
#define zend_isnan(a) 0
#endif

int main(int argc, char** argv)
{
	return zend_isnan(atof("NAN")) ? 0 : 1;
}
]])],[
  ac_cv_atof_accept_nan=yes
],[
  ac_cv_atof_accept_nan=no
],[
  ac_cv_atof_accept_nan=no
])])
if test "$ac_cv_atof_accept_nan" = "yes"; then
  AC_DEFINE([HAVE_ATOF_ACCEPTS_NAN], 1, [whether atof() accepts NAN])
fi

dnl
dnl Check if atof() accepts INF
dnl
AC_CACHE_CHECK(whether atof() accepts INF, ac_cv_atof_accept_inf,[
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <math.h>
#include <stdlib.h>

#ifdef HAVE_ISINF
#define zend_isinf(a) isinf(a)
#elif defined(INFINITY)
/* Might not work, but is required by ISO C99 */
#define zend_isinf(a) (((a)==INFINITY)?1:0)
#elif defined(HAVE_FPCLASS)
#define zend_isinf(a) ((fpclass(a) == FP_PINF) || (fpclass(a) == FP_NINF))
#else
#define zend_isinf(a) 0
#endif

int main(int argc, char** argv)
{
	return zend_isinf(atof("INF")) && zend_isinf(atof("-INF")) ? 0 : 1;
}
]])],[
  ac_cv_atof_accept_inf=yes
],[
  ac_cv_atof_accept_inf=no
],[
  ac_cv_atof_accept_inf=no
])])
if test "$ac_cv_atof_accept_inf" = "yes"; then
  AC_DEFINE([HAVE_ATOF_ACCEPTS_INF], 1, [whether atof() accepts INF])
fi

dnl
dnl Check if HUGE_VAL == INF
dnl
AC_CACHE_CHECK(whether HUGE_VAL == INF, ac_cv_huge_val_inf,[
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <math.h>
#include <stdlib.h>

#ifdef HAVE_ISINF
#define zend_isinf(a) isinf(a)
#elif defined(INFINITY)
/* Might not work, but is required by ISO C99 */
#define zend_isinf(a) (((a)==INFINITY)?1:0)
#elif defined(HAVE_FPCLASS)
#define zend_isinf(a) ((fpclass(a) == FP_PINF) || (fpclass(a) == FP_NINF))
#else
#define zend_isinf(a) 0
#endif

int main(int argc, char** argv)
{
	return zend_isinf(HUGE_VAL) ? 0 : 1;
}
]])],[
  ac_cv_huge_val_inf=yes
],[
  ac_cv_huge_val_inf=no
],[
  ac_cv_huge_val_inf=yes
])])
dnl This is the most probable fallback so we assume yes in case of cross compile.
if test "$ac_cv_huge_val_inf" = "yes"; then
  AC_DEFINE([HAVE_HUGE_VAL_INF], 1, [whether HUGE_VAL == INF])
fi

dnl
dnl Check if HUGE_VAL + -HUGEVAL == NAN
dnl
AC_CACHE_CHECK(whether HUGE_VAL + -HUGEVAL == NAN, ac_cv_huge_val_nan,[
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <math.h>
#include <stdlib.h>

#ifdef HAVE_ISNAN
#define zend_isnan(a) isnan(a)
#elif defined(HAVE_FPCLASS)
#define zend_isnan(a) ((fpclass(a) == FP_SNAN) || (fpclass(a) == FP_QNAN))
#else
#define zend_isnan(a) 0
#endif

int main(int argc, char** argv)
{
#if defined(__sparc__) && !(__GNUC__ >= 3)
	/* prevent bug #27830 */
	return 1;
#else
	return zend_isnan(HUGE_VAL + -HUGE_VAL) ? 0 : 1;
#endif
}
]])],[
  ac_cv_huge_val_nan=yes
],[
  ac_cv_huge_val_nan=no
],[
  ac_cv_huge_val_nan=yes
])])
dnl This is the most probable fallback so we assume yes in case of cross compile.
if test "$ac_cv_huge_val_nan" = "yes"; then
  AC_DEFINE([HAVE_HUGE_VAL_NAN], 1, [whether HUGE_VAL + -HUGEVAL == NAN])
fi

dnl
dnl Check whether __cpuid_count is available
dnl
AC_CACHE_CHECK(whether __cpuid_count is available, ac_cv_cpuid_count_available, [
AC_LINK_IFELSE([AC_LANG_PROGRAM([[
  #include <cpuid.h>
]], [[
  unsigned eax, ebx, ecx, edx;
  __cpuid_count(0, 0, eax, ebx, ecx, edx);
]])], [
  ac_cv_cpuid_count_available=yes
], [
  ac_cv_cpuid_count_available=no
])])
if test "$ac_cv_cpuid_count_available" = "yes"; then
  AC_DEFINE([HAVE_CPUID_COUNT], 1, [whether __cpuid_count is available])
fi
