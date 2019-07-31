/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl Service Runtime.  Transferrable shared memory objects.
 */

#include "native_client/src/include/portability.h"
#include "native_client/src/include/nacl_platform.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>

#include "native_client/src/trusted/desc/nacl_desc_base.h"
#include "native_client/src/trusted/desc/nacl_desc_effector.h"
#include "native_client/src/trusted/desc/linux/nacl_desc_sysv_shm.h"

#include "native_client/src/shared/platform/nacl_find_addrsp.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"

#include "native_client/src/trusted/service_runtime/internal_errno.h"
#include "native_client/src/trusted/service_runtime/nacl_config.h"
#include "native_client/src/trusted/service_runtime/include/bits/mman.h"
#include "native_client/src/trusted/service_runtime/include/sys/errno.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"
#include "native_client/src/trusted/service_runtime/include/sys/stat.h"
#include "native_client/src/trusted/service_runtime/sel_util.h"


#if !defined(SIZE_T_MAX)
# define SIZE_T_MAX (~((size_t) 0))
#endif

/*
 * This file contains the implementation of the NaClDescSysvShm
 * subclass of NaClDesc.
 *
 * NaClDescSysvShm is the subclass that wraps SysV shared memory descriptors.
 *
 * Support for SysV shared memory descriptors is much more restricted than
 * for other types of descriptors.  In particular:
 * 1) NaCl provides no method for untrusted creation of SysV shared memory.
 * 2) Importing does not confer ownership of the descriptor, and hence
 *    we do not do the shmctl(IPC_RMID) to close it.  The lifetime of the
 *    descriptor is controlled by the X server that created it, and returned
 *    it for use by Chrome.
 */

static int NaClDescSysvShmSubclassCtorIntern(struct NaClDescSysvShm *self,
                                             int id,
                                             nacl_off64_t size,
                                             int rmid_in_dtor) {
  struct NaClDesc *basep = (struct NaClDesc *) self;

  /*
   * off_t is signed, but size_t is not; historically size_t is for
   * sizeof and similar, and off_t is also used for stat structure
   * st_size member.  This runtime test detects large object sizes
   * that are silently converted to negative values.  Additionally,
   * the size must be a multiple of 4K.
   */
  basep->base.vtbl = (struct NaClRefCountVtbl const *) NULL;
  if ((size_t) size != NaClRoundPage((size_t) size)
      || size < 0
      || SIZE_T_MAX < (uint64_t) size) {
    return 0;
  }

  self->id = id;
  self->size = size;
  self->rmid_in_dtor = rmid_in_dtor;
  basep->base.vtbl = (struct NaClRefCountVtbl const *) &kNaClDescSysvShmVtbl;
  return 1;
}

static int NaClDescSysvShmCtorIntern(struct NaClDescSysvShm *self,
                                     int                    id,
                                     nacl_off64_t           size,
                                     int                    rmid_in_dtor) {
  struct NaClDesc *basep = (struct NaClDesc *) self;
  int rv;

  NACL_VTBL(NaClRefCount, self) = (struct NaClRefCountVtbl const *) NULL;

  if (!NaClDescCtor(basep)) {
    return 0;
  }
  rv = NaClDescSysvShmSubclassCtorIntern(self, id, size, rmid_in_dtor);
  if (!rv) {
    (*NACL_VTBL(NaClRefCount, self)->Dtor)((struct NaClRefCount *) self);
  }
  (*NACL_VTBL(NaClDesc, basep)->SetFlags)(basep, NACL_ABI_O_RDWR);
  return rv;
}

int NaClDescSysvShmImportSubclassCtor(struct NaClDescSysvShm  *self,
                              int                     id,
                              nacl_off64_t            size) {
  return NaClDescSysvShmSubclassCtorIntern(self, id, size, 0);
}

int NaClDescSysvShmImportCtor(struct NaClDescSysvShm  *self,
                              int                     id,
                              nacl_off64_t            size) {
  return NaClDescSysvShmCtorIntern(self, id, size, 0);
}

/*
 * Creates a NaClDesc containing a new shared memory region.
 */
int NaClDescSysvShmCtor(struct NaClDescSysvShm  *self,
                        nacl_off64_t            size) {
  int id;
  int retval;

  if (size < 0 || SIZE_T_MAX < (uint64_t) size) {
    return 0;
  }
  /* Create the region. */
  id = shmget(IPC_PRIVATE,
              (int) size,
              IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
  if (-1 == id) {
    return 0;
  }
  /* Construct the descriptor. */
  retval = NaClDescSysvShmCtorIntern(self, id, size, 1);
  /* If the constructor failed, mark the region for freeing. */
  if (0 == retval) {
    (void) shmctl(id, IPC_RMID, NULL);
    return 0;
  }
  /* Return success. */
  return 1;
}

static void NaClDescSysvShmDtor(struct NaClRefCount *vself) {
  struct NaClDescSysvShm  *self = (struct NaClDescSysvShm *) vself;

  /*
   * Importing does NOT confer ownership of the id. Hence the Dtor does not
   * do the shmctl(IPC_RMID).
   */
  if (self->rmid_in_dtor) {
    (void) shmctl(self->id, IPC_RMID, NULL);
  }
  /* NACL_INVALID_HANDLE is also an invalid id for shmat. */
  self->id = NACL_INVALID_HANDLE;
  vself->vtbl = (struct NaClRefCountVtbl const *) &kNaClDescVtbl;
  (*vself->vtbl->Dtor)(vself);
}

/*
 * For now, we just use shmat.  This means that the NaCl module's mmap
 * syscall must ask for the entire size, with a zero offset.  In the
 * future, we may choose to shmat to elsewhere in the trusted address
 * space, and then mremap from there into the untrusted address space,
 * using MREMAP_FIXED to ask for the new location.  This approach has
 * its own hazards, however since on x86-32 we are short on address
 * space already, and requiring shmat, mremap, munmap means that we
 * have to have enough trusted address space free to temporarily hold
 * the maximum sized sysv shm object.
 */
static uintptr_t NaClDescSysvShmMap(struct NaClDesc         *vself,
                                    struct NaClDescEffector *effp,
                                    void                    *start_addr,
                                    size_t                  len,
                                    int                     prot,
                                    int                     flags,
                                    nacl_off64_t            offset) {
  struct NaClDescSysvShm  *self = (struct NaClDescSysvShm *) vself;

  int           host_flags;
  void          *result;

  UNREFERENCED_PARAMETER(effp);

  NaClLog(4,
          "NaClDescSysVShmMmap(,,0x%08"NACL_PRIxPTR",0x%"NACL_PRIxS","
          "0x%x,0x%x,0x%08"NACL_PRIxNACL_OFF64")\n",
          (uintptr_t) start_addr, len, prot, flags, offset);
  /*
   * shm must have NACL_ABI_MAP_SHARED in flags.  we check, and may
   * relax this in the future.
   */
  if ((NACL_ABI_MAP_SHARED) !=
      (flags & (NACL_ABI_MAP_SHARING_MASK))) {
    NaClLog(LOG_INFO,
            ("NaClDescSysvShmMap: Mapping not"
             " NACL_ABI_MAP_SHARED\n"));
    return -NACL_ABI_EINVAL;
  }

  if (0 != (NACL_ABI_MAP_FIXED & flags) && NULL == start_addr) {
    NaClLog(LOG_INFO,
            ("NaClDescSysvShmMap: Mapping NACL_ABI_MAP_FIXED"
             " but start_addr is NULL\n"));
    return -NACL_ABI_EINVAL;
  }
  /* post-condition: if NULL == start_addr, then NACL_ABI_MAP_FIXED not set */

  if (NULL == start_addr) {
    uintptr_t addr;

    if (!NaClFindAddressSpace(&addr, len)) {
      NaClLog(1, "NaClDescSysvShmMap: could not find address space\n");
      return -NACL_ABI_ENOMEM;
    }
    if (-1 == munmap((void *) addr, len)) {
      NaClLog(LOG_FATAL,
              "Could not unmap found space at 0x%"NACL_PRIxPTR"\n",
              addr);
    }
    start_addr = (void *) addr;
  }

  /*
   * shmat can only map the shared memory region starting at its beginning
   * and continuing for its entire size.
   */
  if (0 != offset || self->size > len) {
    NaClLog(LOG_INFO,
            "NaClDescSysvShmMap: Mapping at non-zero offset or length"
            " mismatch\n");
    return -NACL_ABI_EINVAL;
  }
  /*
   * prot must be not be PROT_NONE nor contain other than PROT_{READ|WRITE}
   */
  if (NACL_ABI_PROT_NONE == prot) {
    NaClLog(LOG_INFO, "NaClDescSysvShmMap: PROT_NONE not supported\n");
    return -NACL_ABI_EINVAL;
  }
  if (0 == (NACL_ABI_PROT_READ & prot)) {
    NaClLog(LOG_INFO, "NaClDescSysvShmMap: PROT_READ not set\n");
    return -NACL_ABI_EINVAL;
  }
  if (0 != (~(NACL_ABI_PROT_READ | NACL_ABI_PROT_WRITE) & prot)) {
    NaClLog(LOG_INFO,
            "NaClDescSysvShmMap: prot has other bits than PROT_{READ|WRITE}\n");
    return -NACL_ABI_EINVAL;
  }
  /*
   * Map from NACL_ABI_ prot and flags bits to shmat flags.
   */
  host_flags = SHM_REMAP;
  if (NACL_ABI_PROT_READ == prot) {
    host_flags |= SHM_RDONLY;
  }

  /*
   * TODO(bsy): !NACL_ABI_MAP_FIXED, start_addr == NULL, find address
   * space (assuming no race), and set start_addr appropriately.
   *
   * If SHM_REMAP is defined, use it.  Else munmap and then shmat,
   * leaving a timing hole for multithreaded race.  Fail if we lose
   * the race and let the user code retry.
   */
  /*
   * Attach (map) the shared memory region.
   */
  result = shmat(self->id, (void *) start_addr, host_flags);
  if (NACL_MAP_FAILED == result) {
    NaClLog(LOG_FATAL, "NaClDescSysvMap: shmat failed %d\n", errno);
  }
  if (result != start_addr) {
    NaClLog(LOG_FATAL,
            ("NaClDescSysvShmMap: NACL_MAP_FIXED but"
             " got 0x%08"NACL_PRIxPTR" instead of 0x%08"NACL_PRIxPTR"\n"),
            (uintptr_t) result, (uintptr_t) start_addr);
  }

  return (uintptr_t) start_addr;
}

static int NaClDescSysvShmFstat(struct NaClDesc         *vself,
                                struct nacl_abi_stat    *stbp) {
  struct NaClDescSysvShm  *self = (struct NaClDescSysvShm *) vself;

  if (self->size > INT32_MAX) {
    return -NACL_ABI_EOVERFLOW;
  }

  stbp->nacl_abi_st_dev = 0;
  stbp->nacl_abi_st_ino = 0x6c43614e;
  stbp->nacl_abi_st_mode = (NACL_ABI_S_IFSHM_SYSV |
                            NACL_ABI_S_IRUSR |
                            NACL_ABI_S_IWUSR);
  stbp->nacl_abi_st_nlink = 1;
  stbp->nacl_abi_st_uid = -1;
  stbp->nacl_abi_st_gid = -1;
  stbp->nacl_abi_st_rdev = 0;
  /* TODO(sehr): this should really use shmctl instead. */
  stbp->nacl_abi_st_size = (nacl_abi_off_t) self->size;
  stbp->nacl_abi_st_blksize = 0;
  stbp->nacl_abi_st_blocks = 0;
  stbp->nacl_abi_st_atime = 0;
  stbp->nacl_abi_st_mtime = 0;
  stbp->nacl_abi_st_ctime = 0;

  return 0;
}

static int NaClDescSysvShmExternalizeSize(struct NaClDesc *vself,
                                          size_t          *nbytes,
                                          size_t          *nhandles) {
  struct NaClDescSysvShm  *self = (struct NaClDescSysvShm *) vself;
  int rv;

  rv = NaClDescExternalizeSize(vself, nbytes, nhandles);
  if (0 != rv) {
    return rv;
  }
  *nbytes += sizeof self->id + sizeof(nacl_off64_t);

  return 0;
}

static int NaClDescSysvShmExternalize(struct NaClDesc           *vself,
                                      struct NaClDescXferState  *xfer) {
  struct NaClDescSysvShm  *self = (struct NaClDescSysvShm *) vself;
  nacl_off64_t size64 = self->size;
  int rv;

  rv = NaClDescExternalize(vself, xfer);
  if (0 != rv) {
    return rv;
  }
  memcpy(xfer->next_byte, &self->id, sizeof self->id);
  xfer->next_byte += sizeof self->id;
  memcpy(xfer->next_byte, &size64, sizeof size64);
  xfer->next_byte += sizeof size64;
  return 0;
}

struct NaClDescVtbl const kNaClDescSysvShmVtbl = {
  {
    NaClDescSysvShmDtor,
  },
  NaClDescSysvShmMap,
  NACL_DESC_UNMAP_NOT_IMPLEMENTED
  NaClDescReadNotImplemented,
  NaClDescWriteNotImplemented,
  NaClDescSeekNotImplemented,
  NaClDescPReadNotImplemented,
  NaClDescPWriteNotImplemented,
  NaClDescIoctlNotImplemented,
  NaClDescSysvShmFstat,
  NaClDescGetdentsNotImplemented,
  NaClDescSysvShmExternalizeSize,
  NaClDescSysvShmExternalize,
  NaClDescLockNotImplemented,
  NaClDescTryLockNotImplemented,
  NaClDescUnlockNotImplemented,
  NaClDescWaitNotImplemented,
  NaClDescTimedWaitAbsNotImplemented,
  NaClDescSignalNotImplemented,
  NaClDescBroadcastNotImplemented,
  NaClDescSendMsgNotImplemented,
  NaClDescRecvMsgNotImplemented,
  NaClDescLowLevelSendMsgNotImplemented,
  NaClDescLowLevelRecvMsgNotImplemented,
  NaClDescConnectAddrNotImplemented,
  NaClDescAcceptConnNotImplemented,
  NaClDescPostNotImplemented,
  NaClDescSemWaitNotImplemented,
  NaClDescGetValueNotImplemented,
  NaClDescSetMetadata,
  NaClDescGetMetadata,
  NaClDescSetFlags,
  NaClDescGetFlags,
  NACL_DESC_SYSV_SHM,
};

int NaClDescSysvShmInternalize(struct NaClDesc               **out_desc,
                               struct NaClDescXferState      *xfer,
                               struct NaClDescQuotaInterface *quota_interface) {
  int                   rv;
  struct NaClDescSysvShm *ndisp;
  int                   id;
  nacl_off64_t          size;

  UNREFERENCED_PARAMETER(quota_interface);
  rv = -NACL_ABI_EIO;

  ndisp = malloc(sizeof *ndisp);
  if (NULL == ndisp) {
    rv = -NACL_ABI_ENOMEM;
    goto cleanup;
  }

  if (!NaClDescInternalizeCtor((struct NaClDesc *) ndisp, xfer)) {
    free(ndisp);
    ndisp = NULL;
    rv = -NACL_ABI_ENOMEM;
    goto cleanup;
  }

  if (xfer->next_byte + sizeof ndisp->id + sizeof ndisp->size >
      xfer->byte_buffer_end) {
    rv = -NACL_ABI_EIO;
    goto cleanup;
  }

  memcpy(&id, xfer->next_byte, sizeof id);
  xfer->next_byte += sizeof id;
  memcpy(&size, xfer->next_byte, sizeof size);
  xfer->next_byte += sizeof size;

  if (!NaClDescSysvShmImportSubclassCtor(ndisp, id, size)) {
    rv = -NACL_ABI_EIO;
    goto cleanup;
  }

  *out_desc = (struct NaClDesc *) ndisp;
  rv = 0;

cleanup:
  if (rv < 0) {
    NaClDescSafeUnref((struct NaClDesc *) ndisp);
  }
  return rv;
}
