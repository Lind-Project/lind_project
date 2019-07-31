/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl Service Runtime.  Directory descriptor / Handle abstraction.
 */
#include "native_client/src/include/portability.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>

#include "native_client/src/include/nacl_platform.h"
#include "native_client/src/shared/platform/nacl_check.h"
#include "native_client/src/shared/platform/nacl_host_desc.h"
#include "native_client/src/shared/platform/nacl_host_dir.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_sync.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"
#include "native_client/src/shared/platform/win/xlate_system_error.h"

#include "native_client/src/trusted/service_runtime/nacl_config.h"
#include "native_client/src/trusted/service_runtime/internal_errno.h"

#include "native_client/src/trusted/service_runtime/include/bits/mman.h"
#include "native_client/src/trusted/service_runtime/include/sys/dirent.h"
#include "native_client/src/trusted/service_runtime/include/sys/errno.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"
#include "native_client/src/trusted/service_runtime/include/sys/stat.h"


#define SSIZE_T_MAX ((ssize_t) ((~(size_t) 0) >> 1))


int NaClHostDirOpen(struct NaClHostDir  *d,
                    char                *path) {
  wchar_t pattern[NACL_CONFIG_PATH_MAX + 1];
  int     err;
  int     retval;

  if (NULL == d) {
    NaClLog(LOG_FATAL, "NaClHostDirOpen: 'this' is NULL\n");
  }


  /**
    * "path" is an 8-bit char string. Convert to UTF-16 here.
    * Using Microsoft "Secure CRT" snprintf. Passing _TRUNCATE
    * instructs the runtime to truncate and return -1 if the
    * buffer is too small, rather than the default behavior of
    * dumping core.
    *
    * NOTE: %hs specifies a single-byte-char string.
    */
  err = _snwprintf_s(pattern,
                     NACL_CONFIG_PATH_MAX + 1,
                     _TRUNCATE, L"%hs\\*.*", path);
  if (err < 0) {
    return -NACL_ABI_EOVERFLOW;
  }
  if (!NaClMutexCtor(&d->mu)) {
    return -NACL_ABI_ENOMEM;
  }
  d->handle = FindFirstFile(pattern, &d->find_data);
  d->off = 0;
  d->done = 0;

  if (INVALID_HANDLE_VALUE != d->handle) {
    retval = 0;
  } else {
    int win_error = GetLastError();
    NaClLog(LOG_ERROR, "NaClHostDirOpen: failed: %d\n", win_error);
    if (ERROR_NO_MORE_FILES == win_error) {
      d->done = 1;
      retval = 0;
    } else if (ERROR_PATH_NOT_FOUND == win_error) {
      retval = -NACL_ABI_ENOTDIR;
    } else {
      /* TODO(sehr): fix the errno handling */
      retval = -NaClXlateSystemError(win_error);
    }
  }

  if (0 != retval) {
    NaClMutexDtor(&d->mu);
  }
  return retval;
}

ssize_t NaClHostDirGetdents(struct NaClHostDir  *d,
                            void                *buf,
                            size_t               len) {
  struct nacl_abi_dirent volatile *p;
  size_t                          i;
  ssize_t                         retval;

  if (NULL == d) {
    NaClLog(LOG_FATAL, "NaClHostDirGetdents: 'this' is NULL\n");
  }
  NaClLog(3, "NaClHostDirGetdents(0x%08x, %u):\n", buf, len);
  if (len > SSIZE_T_MAX) {
    NaClLog(3, "Clamping to len SSIZE_T_MAX\n");
    len = SSIZE_T_MAX;
  }

  NaClXMutexLock(&d->mu);

  p = (struct nacl_abi_dirent *) buf;
  i = 0;

  /*
   * d->off is currently the record number, assuming that FindNextFile
   * output order is deterministic and consistent.
   */
  while (1) {
    /**
     * The FIND_DATA structure contains the filename as a UTF-16
     * string of length MAX_PATH.  This may or may not convert into an
     * 8-bit char string of similar length.  The safe thing to do here
     * is to assume the worst case: every UTF-16 character expands to
     * a four-byte MBCS sequence.  This should default to CP_ACP (ANSI
     * code page).
     *
     * TODO(bsy,sehr): consider using WideCharToMultiByte (and
     * MultiByteToWideChar before invoking _s_open_s in
     * NaClHostDescOpen) with CP_UTF8 to always present UTF8 to
     * untrusted application code.  NB: MB_ERR_INVALID_CHARS is needed
     * since otherwise we have an issue with silently dropping invalid
     * Unicode code points that can cause file name aliasing.
     *
     * http://code.google.com/p/nativeclient/issues/detail?id=2725
     *
     * NB: Keep in mind that MAX_PATH is an API limitation, not a
     * limitation of the underlying filesystem.
     */
    char name_mbcs[(MAX_PATH * 4) + 1];
    size_t name_length;
    size_t rec_length;
    uint16_t nacl_abi_rec_length;
    int err;

    if (d->done) {
      retval = 0;
      goto done;
    }

    err = _snprintf_s(name_mbcs,
                      _countof(name_mbcs),
                      _TRUNCATE,
                      "%ws", d->find_data.cFileName);
    if (err < 0) {
      retval = -NACL_ABI_EOVERFLOW;
      goto done;
    }
    name_length = strlen(name_mbcs) + 1;
    rec_length = (offsetof(struct nacl_abi_dirent, nacl_abi_d_name)
                    + (name_length + 3))
                  & ~3;

    /* Check for overflow in record length */
    nacl_abi_rec_length = (uint16_t) rec_length;
    if (rec_length > (size_t) nacl_abi_rec_length) {
      /*
       * Can there be file names that are longer than 64K?  Windows
       * API docs say that 1023 is the maximum file name length, so
       * with a 4x expansion we should only get 4092 + 1 or 4093
       * bytes.  But this may be filesystem dependent....
       */
      retval = -NACL_ABI_EOVERFLOW;
      goto done;
    }

    CHECK(rec_length <= SSIZE_T_MAX - i);
    /*
     * Should never happen, since len is clamped to SSIZE_T_MAX.
     */

    if (i + rec_length >= len) {
      /*
       * Insufficent buffer space!  Check if any entries have been
       * copied...
       */
      if (0 == i) {
        retval = (ssize_t) -NACL_ABI_EINVAL;
      } else {
        retval = (ssize_t) i;
      }
      goto done;
    }

    p = (struct nacl_abi_dirent volatile *) (((char *) buf) + i);
    p->nacl_abi_d_ino = NACL_FAKE_INODE_NUM;  /* windows doesn't do inodes */
    p->nacl_abi_d_off = d->off;
    p->nacl_abi_d_reclen = nacl_abi_rec_length;
    memcpy((char *) p->nacl_abi_d_name, name_mbcs, name_length);
    i += nacl_abi_rec_length;
    ++d->off;

    if (!FindNextFile(d->handle, &d->find_data)) {
      int win_err = GetLastError();
      if (win_err == ERROR_NO_MORE_FILES) {
        d->done = 1;
        retval = (ssize_t) i;
        goto done;
      } else {
        retval = -NaClXlateSystemError(win_err);
        goto done;
      }
    }
  }
done:
  NaClXMutexUnlock(&d->mu);
  return retval;
}

int NaClHostDirClose(struct NaClHostDir *d) {
  if (NULL == d) {
    NaClLog(LOG_FATAL, "NaClHostDirClose: 'this' is NULL\n");
  }
  NaClMutexDtor(&d->mu);
  if (!FindClose(d->handle)) {
    return -NaClXlateSystemError(GetLastError());
  }
  return 0;
}
