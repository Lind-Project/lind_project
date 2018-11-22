dnl config.m4 for extension mbstring

AC_DEFUN([PHP_MBSTRING_ADD_SOURCES], [
  PHP_MBSTRING_SOURCES="$PHP_MBSTRING_SOURCES $1"
])

AC_DEFUN([PHP_MBSTRING_ADD_BASE_SOURCES], [
  PHP_MBSTRING_BASE_SOURCES="$PHP_MBSTRING_BASE_SOURCES $1"
])

AC_DEFUN([PHP_MBSTRING_ADD_BUILD_DIR], [
  PHP_MBSTRING_EXTRA_BUILD_DIRS="$PHP_MBSTRING_EXTRA_BUILD_DIRS $1"
])

AC_DEFUN([PHP_MBSTRING_ADD_INCLUDE], [
  PHP_MBSTRING_EXTRA_INCLUDES="$PHP_MBSTRING_EXTRA_INCLUDES $1"
])

AC_DEFUN([PHP_MBSTRING_ADD_CONFIG_HEADER], [
  PHP_MBSTRING_EXTRA_CONFIG_HEADERS="$PHP_MBSTRING_EXTRA_CONFIG_HEADERS $1"
])

AC_DEFUN([PHP_MBSTRING_ADD_CFLAG], [
  PHP_MBSTRING_CFLAGS="$PHP_MBSTRING_CFLAGS $1"
])

AC_DEFUN([PHP_MBSTRING_ADD_INSTALL_HEADERS], [
  PHP_MBSTRING_INSTALL_HEADERS="$PHP_MBSTRING_INSTALL_HEADERS $1"
])

AC_DEFUN([PHP_MBSTRING_EXTENSION], [
  PHP_NEW_EXTENSION(mbstring, $PHP_MBSTRING_SOURCES, $ext_shared,, $PHP_MBSTRING_CFLAGS -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
  PHP_SUBST(MBSTRING_SHARED_LIBADD)

  for dir in $PHP_MBSTRING_EXTRA_BUILD_DIRS; do
    PHP_ADD_BUILD_DIR([$ext_builddir/$dir], 1)
  done

  for dir in $PHP_MBSTRING_EXTRA_INCLUDES; do
    PHP_ADD_INCLUDE([$ext_srcdir/$dir])
    PHP_ADD_INCLUDE([$ext_builddir/$dir])
  done

  if test "$ext_shared" = "no"; then
    PHP_ADD_SOURCES(PHP_EXT_DIR(mbstring), $PHP_MBSTRING_BASE_SOURCES)
    out="php_config.h"
  else
    PHP_ADD_SOURCES_X(PHP_EXT_DIR(mbstring),$PHP_MBSTRING_BASE_SOURCES,,shared_objects_mbstring,yes)
    if test -f "$ext_builddir/config.h.in"; then
      out="$abs_builddir/config.h"
    else
      out="php_config.h"
    fi
  fi

  if test "$PHP_MBSTRING_BUNDLED_ONIG" = "1"; then
    cp $ext_srcdir/oniguruma/src/oniguruma.h $ext_srcdir/oniguruma/oniguruma.h
  fi

  for cfg in $PHP_MBSTRING_EXTRA_CONFIG_HEADERS; do
    cat > $ext_builddir/$cfg <<EOF
#include "$out"
EOF
  done
  PHP_MBSTRING_ADD_INSTALL_HEADERS([mbstring.h])
  PHP_INSTALL_HEADERS([ext/mbstring], [$PHP_MBSTRING_INSTALL_HEADERS])
])

AC_DEFUN([PHP_MBSTRING_SETUP_MBREGEX], [
  if test "$PHP_MBREGEX" = "yes"; then
    if test "$PHP_ONIG" = "yes" || test "$PHP_ONIG" = "no"; then
      dnl
      dnl Bundled oniguruma
      dnl
      PHP_MBSTRING_BUNDLED_ONIG=1
      if test "$PHP_MBREGEX_BACKTRACK" != "no"; then
        AC_DEFINE([USE_COMBINATION_EXPLOSION_CHECK],1,[whether to check multibyte regex backtrack])
      fi

      AC_CHECK_HEADERS([strings.h unistd.h sys/time.h sys/times.h limits.h])
      AC_CHECK_SIZEOF(int, 4)
      AC_CHECK_SIZEOF(short, 2)
      AC_CHECK_SIZEOF(long, 4)
      AC_FUNC_ALLOCA
      AC_CHECK_HEADER([stdarg.h], [
        AC_DEFINE([HAVE_STDARG_PROTOTYPES], [1], [Define to 1 if you have the <stdarg.h> header file.])
      ], [])
      AC_DEFINE([PHP_ONIG_BUNDLED], [1], [Define to 1 if the bundled oniguruma is used])
      AC_DEFINE([HAVE_ONIG], [1], [Define to 1 if the oniguruma library is available])
      PHP_MBSTRING_ADD_CFLAG([-DNOT_RUBY])
      PHP_MBSTRING_ADD_BUILD_DIR([oniguruma])
      PHP_MBSTRING_ADD_BUILD_DIR([oniguruma/src])
      PHP_MBSTRING_ADD_INCLUDE([oniguruma])
      PHP_MBSTRING_ADD_CONFIG_HEADER([oniguruma/src/config.h])
      PHP_MBSTRING_ADD_SOURCES([
                oniguruma/src/ascii.c
                oniguruma/src/big5.c
                oniguruma/src/cp1251.c
                oniguruma/src/euc_jp.c
                oniguruma/src/euc_jp_prop.c
                oniguruma/src/euc_kr.c
                oniguruma/src/euc_tw.c
                oniguruma/src/gb18030.c
                oniguruma/src/iso8859_1.c
                oniguruma/src/iso8859_10.c
                oniguruma/src/iso8859_11.c
                oniguruma/src/iso8859_13.c
                oniguruma/src/iso8859_14.c
                oniguruma/src/iso8859_15.c
                oniguruma/src/iso8859_16.c
                oniguruma/src/iso8859_2.c
                oniguruma/src/iso8859_3.c
                oniguruma/src/iso8859_4.c
                oniguruma/src/iso8859_5.c
                oniguruma/src/iso8859_6.c
                oniguruma/src/iso8859_7.c
                oniguruma/src/iso8859_8.c
                oniguruma/src/iso8859_9.c
                oniguruma/src/koi8.c
                oniguruma/src/koi8_r.c
                oniguruma/src/onig_init.c
                oniguruma/src/regcomp.c
                oniguruma/src/regenc.c
                oniguruma/src/regerror.c
                oniguruma/src/regexec.c
                oniguruma/src/regext.c
                oniguruma/src/reggnu.c
                oniguruma/src/regparse.c
                oniguruma/src/regposerr.c
                oniguruma/src/regposix.c
                oniguruma/src/regsyntax.c
                oniguruma/src/regtrav.c
                oniguruma/src/regversion.c
                oniguruma/src/sjis.c
                oniguruma/src/sjis_prop.c
                oniguruma/src/st.c
                oniguruma/src/unicode.c
                oniguruma/src/unicode_fold1_key.c
                oniguruma/src/unicode_fold2_key.c
                oniguruma/src/unicode_fold3_key.c
                oniguruma/src/unicode_unfold_key.c
                oniguruma/src/utf16_be.c
                oniguruma/src/utf16_le.c
                oniguruma/src/utf32_be.c
                oniguruma/src/utf32_le.c
                oniguruma/src/utf8.c
      ])
      PHP_MBSTRING_ADD_INSTALL_HEADERS([oniguruma/oniguruma.h])
    else
      dnl
      dnl External oniguruma
      dnl
      PHP_MBSTRING_BUNDLED_ONIG=0
      if test ! -f "$PHP_ONIG/include/oniguruma.h"; then
        AC_MSG_ERROR([oniguruma.h not found in $PHP_ONIG/include])
      fi
      PHP_ADD_INCLUDE([$PHP_ONIG/include])

      PHP_CHECK_LIBRARY(onig, onig_init, [
        PHP_ADD_LIBRARY_WITH_PATH(onig, $PHP_ONIG/$PHP_LIBDIR, MBSTRING_SHARED_LIBADD)
        AC_DEFINE([HAVE_ONIG], [1], [Define to 1 if the oniguruma library is available])
      ],[
        AC_MSG_ERROR([Problem with oniguruma. Please check config.log for more information.])
      ], [
        -L$PHP_ONIG/$PHP_LIBDIR
      ])

      save_old_LDFLAGS=$LDFLAGS
      PHP_EVAL_LIBLINE([$MBSTRING_SHARED_LIBADD], LDFLAGS)
      AC_MSG_CHECKING([if oniguruma has an invalid entry for KOI8 encoding])
      AC_LINK_IFELSE([AC_LANG_PROGRAM([[
#include <oniguruma.h>
      ]], [[
return (int)(ONIG_ENCODING_KOI8 + 1);
      ]])], [
        AC_MSG_RESULT([no])
      ], [
        AC_MSG_RESULT([yes])
        AC_DEFINE([PHP_ONIG_BAD_KOI8_ENTRY], [1], [define to 1 if oniguruma has an invalid entry for KOI8 encoding])
      ])
      LDFLAGS=$save_old_LDFLAGS
    fi

    PHP_MBSTRING_ADD_CFLAG([-DONIG_ESCAPE_UCHAR_COLLISION=1])
    PHP_MBSTRING_ADD_CFLAG([-DUChar=OnigUChar])

    AC_DEFINE([HAVE_MBREGEX], 1, [whether to have multibyte regex support])

    PHP_MBSTRING_ADD_BASE_SOURCES([php_mbregex.c])
    PHP_MBSTRING_ADD_INSTALL_HEADERS([php_mbregex.h php_onig_compat.h])
  fi
])

AC_DEFUN([PHP_MBSTRING_SETUP_LIBMBFL], [
  dnl
  dnl Bundled libmbfl is required and can not be disabled
  dnl
  PHP_MBSTRING_ADD_BUILD_DIR([libmbfl])
  PHP_MBSTRING_ADD_BUILD_DIR([libmbfl/mbfl])
  PHP_MBSTRING_ADD_BUILD_DIR([libmbfl/filters])
  PHP_MBSTRING_ADD_BUILD_DIR([libmbfl/nls])
  PHP_MBSTRING_ADD_INCLUDE([libmbfl])
  PHP_MBSTRING_ADD_INCLUDE([libmbfl/mbfl])
  PHP_MBSTRING_ADD_CONFIG_HEADER([libmbfl/config.h])

  PHP_MBSTRING_ADD_SOURCES([
    libmbfl/filters/html_entities.c
    libmbfl/filters/mbfilter_7bit.c
    libmbfl/filters/mbfilter_ascii.c
    libmbfl/filters/mbfilter_base64.c
    libmbfl/filters/mbfilter_big5.c
    libmbfl/filters/mbfilter_byte2.c
    libmbfl/filters/mbfilter_byte4.c
    libmbfl/filters/mbfilter_cp1251.c
    libmbfl/filters/mbfilter_cp1252.c
    libmbfl/filters/mbfilter_cp1254.c
    libmbfl/filters/mbfilter_cp5022x.c
    libmbfl/filters/mbfilter_cp51932.c
    libmbfl/filters/mbfilter_cp850.c
    libmbfl/filters/mbfilter_cp866.c
    libmbfl/filters/mbfilter_cp932.c
    libmbfl/filters/mbfilter_cp936.c
    libmbfl/filters/mbfilter_gb18030.c
    libmbfl/filters/mbfilter_euc_cn.c
    libmbfl/filters/mbfilter_euc_jp.c
    libmbfl/filters/mbfilter_euc_jp_2004.c
    libmbfl/filters/mbfilter_euc_jp_win.c
    libmbfl/filters/mbfilter_euc_kr.c
    libmbfl/filters/mbfilter_euc_tw.c
    libmbfl/filters/mbfilter_htmlent.c
    libmbfl/filters/mbfilter_hz.c
    libmbfl/filters/mbfilter_iso2022_jp_ms.c
    libmbfl/filters/mbfilter_iso2022jp_2004.c
    libmbfl/filters/mbfilter_iso2022jp_mobile.c
    libmbfl/filters/mbfilter_iso2022_kr.c
    libmbfl/filters/mbfilter_iso8859_1.c
    libmbfl/filters/mbfilter_iso8859_10.c
    libmbfl/filters/mbfilter_iso8859_13.c
    libmbfl/filters/mbfilter_iso8859_14.c
    libmbfl/filters/mbfilter_iso8859_15.c
    libmbfl/filters/mbfilter_iso8859_16.c
    libmbfl/filters/mbfilter_iso8859_2.c
    libmbfl/filters/mbfilter_iso8859_3.c
    libmbfl/filters/mbfilter_iso8859_4.c
    libmbfl/filters/mbfilter_iso8859_5.c
    libmbfl/filters/mbfilter_iso8859_6.c
    libmbfl/filters/mbfilter_iso8859_7.c
    libmbfl/filters/mbfilter_iso8859_8.c
    libmbfl/filters/mbfilter_iso8859_9.c
    libmbfl/filters/mbfilter_jis.c
    libmbfl/filters/mbfilter_koi8r.c
    libmbfl/filters/mbfilter_armscii8.c
    libmbfl/filters/mbfilter_qprint.c
    libmbfl/filters/mbfilter_sjis.c
    libmbfl/filters/mbfilter_sjis_open.c
    libmbfl/filters/mbfilter_sjis_mobile.c
    libmbfl/filters/mbfilter_sjis_mac.c
    libmbfl/filters/mbfilter_sjis_2004.c
    libmbfl/filters/mbfilter_tl_jisx0201_jisx0208.c
    libmbfl/filters/mbfilter_ucs2.c
    libmbfl/filters/mbfilter_ucs4.c
    libmbfl/filters/mbfilter_uhc.c
    libmbfl/filters/mbfilter_utf16.c
    libmbfl/filters/mbfilter_utf32.c
    libmbfl/filters/mbfilter_utf7.c
    libmbfl/filters/mbfilter_utf7imap.c
    libmbfl/filters/mbfilter_utf8.c
    libmbfl/filters/mbfilter_utf8_mobile.c
    libmbfl/filters/mbfilter_uuencode.c
    libmbfl/filters/mbfilter_koi8u.c
    libmbfl/mbfl/mbfilter.c
    libmbfl/mbfl/mbfilter_8bit.c
    libmbfl/mbfl/mbfilter_pass.c
    libmbfl/mbfl/mbfilter_wchar.c
    libmbfl/mbfl/mbfl_convert.c
    libmbfl/mbfl/mbfl_encoding.c
    libmbfl/mbfl/mbfl_filter_output.c
    libmbfl/mbfl/mbfl_ident.c
    libmbfl/mbfl/mbfl_language.c
    libmbfl/mbfl/mbfl_memory_device.c
    libmbfl/mbfl/mbfl_string.c
    libmbfl/mbfl/mbfl_allocators.c
    libmbfl/nls/nls_de.c
    libmbfl/nls/nls_en.c
    libmbfl/nls/nls_ja.c
    libmbfl/nls/nls_kr.c
    libmbfl/nls/nls_neutral.c
    libmbfl/nls/nls_ru.c
    libmbfl/nls/nls_uni.c
    libmbfl/nls/nls_zh.c
    libmbfl/nls/nls_hy.c
    libmbfl/nls/nls_tr.c
    libmbfl/nls/nls_ua.c
  ])
  PHP_MBSTRING_ADD_CFLAG([-DHAVE_CONFIG_H])
  PHP_MBSTRING_ADD_INSTALL_HEADERS([libmbfl/config.h libmbfl/mbfl/eaw_table.h libmbfl/mbfl/mbfilter.h libmbfl/mbfl/mbfilter_8bit.h libmbfl/mbfl/mbfilter_pass.h libmbfl/mbfl/mbfilter_wchar.h libmbfl/mbfl/mbfl_allocators.h libmbfl/mbfl/mbfl_consts.h libmbfl/mbfl/mbfl_convert.h libmbfl/mbfl/mbfl_defs.h libmbfl/mbfl/mbfl_encoding.h libmbfl/mbfl/mbfl_filter_output.h libmbfl/mbfl/mbfl_ident.h libmbfl/mbfl/mbfl_language.h libmbfl/mbfl/mbfl_memory_device.h libmbfl/mbfl/mbfl_string.h])
])

dnl
dnl Main config
dnl

PHP_ARG_ENABLE(mbstring, whether to enable multibyte string support,
[  --enable-mbstring       Enable multibyte string support])

PHP_ARG_ENABLE([mbregex], [whether to enable multibyte regex support],
[  --disable-mbregex       MBSTRING: Disable multibyte regex support], yes, no)

PHP_ARG_ENABLE([mbregex_backtrack], [whether to check multibyte regex backtrack],
[  --disable-mbregex-backtrack
                          MBSTRING: Disable multibyte regex backtrack check], yes, no)

PHP_ARG_WITH(onig, [for external oniguruma],
[  --with-onig[=DIR]         MBSTRING: Use external oniguruma. DIR is the oniguruma install prefix.
                          If DIR is not set, the bundled oniguruma will be used], no, no)

if test "$PHP_MBSTRING" != "no"; then
  AC_DEFINE([HAVE_MBSTRING],1,[whether to have multibyte string support])

  PHP_MBSTRING_ADD_BASE_SOURCES([mbstring.c php_unicode.c mb_gpc.c])

  if test "$PHP_MBREGEX" != "no"; then
    PHP_MBSTRING_SETUP_MBREGEX
  fi

  dnl libmbfl is required
  PHP_MBSTRING_SETUP_LIBMBFL
  PHP_MBSTRING_EXTENSION
fi

# vim600: sts=2 sw=2 et
