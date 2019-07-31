/*
 * Copyright (c) 2008 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl Service Runtime.  Directory descriptor / Handle abstraction.
 *
 * Note that we avoid using the thread-specific data / thread local
 * storage access to the "errno" variable, and instead use the raw
 * system call return interface of small negative numbers as errors.
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

#include "native_client/src/include/nacl_platform.h"

#include "native_client/src/shared/platform/nacl_check.h"
#include "native_client/src/shared/platform/nacl_host_desc.h"
#include "native_client/src/shared/platform/nacl_host_dir.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_sync.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"
#include "native_client/src/shared/platform/lind_platform.h"

#include "native_client/src/trusted/service_runtime/include/bits/mman.h"
#include "native_client/src/trusted/service_runtime/include/sys/dirent.h"
#include "native_client/src/trusted/service_runtime/include/sys/errno.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"
#include "native_client/src/trusted/service_runtime/include/sys/stat.h"


#ifndef SSIZE_T_MAX
# define SSIZE_T_MAX ((ssize_t) ((~(size_t) 0) >> 1))
#endif

struct linux_dirent {  /* offsets, ILP32 and LP64 */
  unsigned long  d_ino;             /*  0,  0 */
  unsigned long  d_off;             /*  4,  8 */
  unsigned short d_reclen;          /*  8, 16 */
  char           d_name[1];         /* 10, 18 */
  /* actual length is d_reclen - 2 - offsetof(struct linux_dirent, d_name) */
  /*
   * char pad;    / Zero padding byte
   * char d_type; / File type (only since Linux 2.6.4; offset is d_reclen - 1)
   */
};

int NaClHostDirCtor(struct NaClHostDir  *d,
                    int                 dir_desc) {
  if (!NaClMutexCtor(&d->mu)) {
    return -NACL_ABI_ENOMEM;
  }
  d->fd = dir_desc;
  d->cur_byte = 0;
  d->nbytes = 0;
  NaClLog(3, "NaClHostDirCtor: success.\n");
  return 0;
}

int NaClHostDirOpen(struct NaClHostDir  *d,
                    char                *path) {
  int         fd;
  nacl_host_stat_t stbuf;
  int         rv;

  NaClLog(3, "NaClHostDirOpen(0x%08"NACL_PRIxPTR", %s)\n", (uintptr_t) d, path);
  if (NULL == d) {
    NaClLog(LOG_FATAL, "NaClHostDirOpen: 'this' is NULL\n");
  }

  NaClLog(3, "NaClHostDirOpen: invoking open(%s)\n", path);
  fd = lind_open(O_RDONLY, 0, path);
  NaClLog(3, "NaClHostDirOpen: got DIR* %d\n", fd);
  if (-1 == fd) {
    NaClLog(LOG_ERROR,
            "NaClHostDirOpen: open returned -1, errno %d\n", errno);
    return -NaClXlateErrno(errno);
  }
  /* check that it is really a directory */
  if (-1 == lind_fxstat(fd, 1, &stbuf)) {
    NaClLog(LOG_ERROR,
            "NaClHostDirOpen: fstat failed?!?  errno %d\n", errno);
    (void) lind_close(fd);
    return -NaClXlateErrno(errno);
  }
  if (!S_ISDIR(stbuf.st_mode)) {
    (void) lind_close(fd);
    return -NACL_ABI_ENOTDIR;
  }
  rv = NaClHostDirCtor(d, fd);
  return rv;
}

/*
 * Copy and translate a single linux_dirent to nacl_abi_dirent.
 * Returns number of bytes consumed (includes alignment adjustment for
 * next entry).
 *
 * TODO(bsy): add filesystem info argument to specify which
 * directories are "root" inodes, to rewrite the inode number of '..'
 * as appropriate.
 */
static ssize_t NaClCopyDirent(struct NaClHostDir *d,
                              void               *buf,
                              size_t             len) {
  struct linux_dirent             *ldp = (struct linux_dirent *) (
      d->dirent_buf
      + d->cur_byte);
  struct nacl_abi_dirent volatile *nadp;
  size_t                          adjusted_size;

  /* make sure the buffer is aligned */
  CHECK(0 == ((sizeof(nacl_abi_ino_t) - 1) & (uintptr_t) buf));

  if (d->cur_byte == d->nbytes) {
    return 0;  /* none available */
  }
  CHECK(d->cur_byte < d->nbytes);
  CHECK(ldp->d_reclen <= d->nbytes - d->cur_byte);
  /* no partial record transferred. */

  nadp = (struct nacl_abi_dirent volatile *) buf;

  /*
   * is there enough space? assume Linux is sane, so no ssize_t
   * overflow in the adjusted_size computation.  (NAME_MAX is small.)
   */
  CHECK(NAME_MAX < 256);
  adjusted_size = offsetof(struct nacl_abi_dirent, nacl_abi_d_name)
      + strlen(ldp->d_name) + 1;  /* NUL termination */
  /* pad for alignment for access to d_ino */
  adjusted_size = (adjusted_size + (sizeof(nacl_abi_ino_t) - 1))
      & ~(sizeof(nacl_abi_ino_t) - 1);
  if (len < adjusted_size) {
    return -NACL_ABI_EINVAL;  /* result buffer is too small */
  }

#if defined(NACL_MASK_INODES)
  nadp->nacl_abi_d_ino = NACL_FAKE_INODE_NUM;
#else
  nadp->nacl_abi_d_ino = ldp->d_ino;
#endif
  nadp->nacl_abi_d_off = ldp->d_off;
  nadp->nacl_abi_d_reclen = adjusted_size;
  NaClLog(4, "NaClCopyDirent: %s\n", ldp->d_name);
  strcpy((char *) nadp->nacl_abi_d_name, ldp->d_name);
  /* NB: some padding bytes may not get overwritten */

  d->cur_byte += ldp->d_reclen;

  NaClLog(4, "NaClCopyDirent: returning %"NACL_PRIuS"\n", adjusted_size);
  return (ssize_t) adjusted_size;
}

static ssize_t NaClStreamDirents(struct NaClHostDir *d,
                                 void               *buf,
                                 size_t             len) {
  ssize_t retval;
  size_t  xferred = 0;
  ssize_t entry_size;

  NaClXMutexLock(&d->mu);
  while (len > 0) {
    NaClLog(4, "NaClStreamDirents: loop, xferred = %"NACL_PRIuS"\n", xferred);
    entry_size = NaClCopyDirent(d, buf, len);
    if (0 == entry_size) {
      CHECK(d->cur_byte == d->nbytes);
      retval = lind_getdents(d->fd,
                        sizeof d->dirent_buf,
                        (char* )(struct dirent *) d->dirent_buf);
      if (-1 == retval) {
        if (xferred > 0) {
          /* next time through, we'll pick up the error again */
          goto cleanup;
        } else {
          xferred = -NaClXlateErrno(errno);
          goto cleanup;
        }
      } else if (0 == retval) {
        goto cleanup;
      }
      d->cur_byte = 0;
      d->nbytes = retval;
    } else if (entry_size < 0) {
      /*
       * The only error return from NaClCopyDirent is NACL_ABI_EINVAL
       * due to destinaton buffer too small for the current entry.  If
       * we had copied some entries before, we were successful;
       * otherwise report that the buffer is too small for the next
       * directory entry.
       */
      if (xferred > 0) {
        goto cleanup;
      } else {
        xferred = entry_size;
        goto cleanup;
      }
    }
    /* entry_size > 0, maybe copy another */
    buf = (void *) ((char *) buf + entry_size);
    CHECK(len >= (size_t) entry_size);
    len -= entry_size;
    xferred += entry_size;
  }
  /* perfect fit! */
 cleanup:
  NaClXMutexUnlock(&d->mu);
  return xferred;
}

ssize_t NaClHostDirGetdents(struct NaClHostDir  *d,
                            void                *buf,
                            size_t              len) {
  int                     retval;

  if (NULL == d) {
    NaClLog(LOG_FATAL, "NaClHostDirGetdents: 'this' is NULL\n");
  }
  NaClLog(3, "NaClHostDirGetdents(0x%08"NACL_PRIxPTR", %"NACL_PRIuS"):\n",
          (uintptr_t) buf, len);

  if (0 != ((__alignof__(struct nacl_abi_dirent) - 1) & (uintptr_t) buf)) {
    retval = -NACL_ABI_EINVAL;
    goto cleanup;
  }

  retval = NaClStreamDirents(d, buf, len);
 cleanup:
  NaClLog(3, "NaClHostDirGetdents: returned %d\n", retval);
  return retval;
}

int NaClHostDirClose(struct NaClHostDir *d) {
  int retval;

  if (NULL == d) {
    NaClLog(LOG_FATAL, "NaClHostDirClose: 'this' is NULL\n");
  }
  NaClLog(3, "NaClHostDirClose(%d)\n", d->fd);
  retval = lind_close(d->fd);
  d->fd = -1;
  NaClMutexDtor(&d->mu);
  return (-1 == retval) ? -NaClXlateErrno(errno) : retval;
}
