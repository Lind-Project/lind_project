/* vsnprintf in C locale.
   Copyright (C) 2012-2018 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, see <https://www.gnu.org/licenses/>.  */

#ifndef _C_VSNPRINTF_H
#define _C_VSNPRINTF_H

/* Get size_t.  */
#include <stddef.h>

/* Get va_list. */
#include <stdarg.h>

/* The __attribute__ feature is available in gcc versions 2.5 and later.
   The __-protected variants of the attributes 'format' and 'printf' are
   accepted by gcc versions 2.6.4 (effectively 2.7) and later.
   We enable _GL_ATTRIBUTE_FORMAT only if these are supported too, because
   gnulib and libintl do '#define printf __printf__' when they override
   the 'printf' function.  */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
# define _GL_ATTRIBUTE_FORMAT(spec) __attribute__ ((__format__ spec))
#else
# define _GL_ATTRIBUTE_FORMAT(spec) /* empty */
#endif

#ifdef __cplusplus
extern "C" {
#endif

int c_vsnprintf (char *str, size_t size, const char *format, va_list args)
       _GL_ATTRIBUTE_FORMAT ((__printf__, 3, 0));

#ifdef __cplusplus
}
#endif

#endif /* _C_VSNPRINTF_H */
