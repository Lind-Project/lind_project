/* Portability cruft.  Include after config.h and sys/types.h.
   Copyright 1996, 1998-2000, 2007, 2009-2017 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

#ifndef GREP_SYSTEM_H
#define GREP_SYSTEM_H 1

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "binary-io.h"
#include "configmake.h"
#include "dirname.h"
#include "ignore-value.h"
#include "minmax.h"
#include "same-inode.h"

#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

enum { EXIT_TROUBLE = 2 };
enum { NCHAR = UCHAR_MAX + 1 };

#include <gettext.h>
#define N_(String) gettext_noop(String)
#define _(String) gettext(String)

#include <locale.h>

#ifndef initialize_main
# define initialize_main(argcp, argvp)
#endif

#include "unlocked-io.h"

_GL_INLINE_HEADER_BEGIN
#ifndef SYSTEM_INLINE
# define SYSTEM_INLINE _GL_INLINE
#endif

#define STREQ(a, b) (strcmp (a, b) == 0)

/* Convert a possibly-signed character to an unsigned character.  This is
   a bit safer than casting to unsigned char, since it catches some type
   errors that the cast doesn't.  */
SYSTEM_INLINE unsigned char
to_uchar (char ch)
{
  return ch;
}

_GL_INLINE_HEADER_END

#ifndef __has_feature
# define __has_feature(F) false
#endif

#if defined __SANITIZE_ADDRESS__ || __has_feature (address_sanitizer)
# define HAVE_ASAN 1
#else
# define HAVE_ASAN 0
#endif

#if HAVE_ASAN

/* Mark memory region [addr, addr+size) as unaddressable.
   This memory must be previously allocated by the user program.  Accessing
   addresses in this region from instrumented code is forbidden until
   this region is unpoisoned.  This function is not guaranteed to poison
   the whole region - it may poison only a subregion of [addr, addr+size)
   due to ASan alignment restrictions.
   Method is NOT thread-safe in the sense that no two threads can
   (un)poison memory in the same memory region simultaneously.  */
void __asan_poison_memory_region (void const volatile *addr, size_t size);

/* Mark memory region [addr, addr+size) as addressable.
   This memory must be previously allocated by the user program.  Accessing
   addresses in this region is allowed until this region is poisoned again.
   This function may unpoison a superregion of [addr, addr+size) due to
   ASan alignment restrictions.
   Method is NOT thread-safe in the sense that no two threads can
   (un)poison memory in the same memory region simultaneously.  */
void __asan_unpoison_memory_region (void const volatile *addr, size_t size);

#else

static _GL_UNUSED void
__asan_poison_memory_region (void const volatile *addr, size_t size) { }
static _GL_UNUSED void
__asan_unpoison_memory_region (void const volatile *addr, size_t size) { }
#endif

#endif
