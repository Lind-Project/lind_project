/*
 * Copyright (c) 2014 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GLIBCEMU_SYS_TYPES_H
#define GLIBCEMU_SYS_TYPES_H 1

#include <limits.h>
#define SSIZE_MAX LONG_MAX

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 64
#endif

#include_next <sys/types.h>

/* TODO(sbc): Remove these once they get added to newlib headers */
dev_t makedev(int maj, int min);

/*
 * These must be macros otherwise we get compiler errors when
 * there are local variables that shadow them (this happens in
 * several projects including gdb).
 *
 * Arbitrarily split dev_t into upper and lower 32-bits.
 */
#define major(dev) ((int)((dev) >> 32) & 0xffff)
#define minor(dev) ((int)(dev) & 0xffff)

#endif  /* GLIBCEMU_SYS_TYPES_H */
