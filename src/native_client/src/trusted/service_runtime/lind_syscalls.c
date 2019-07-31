/*
 * lind_api.c
 *
 *  Created on: Jun 27, 2013
 *      Author: sji
 */

#include <stdio.h>
#include <assert.h>

/* avoid errors caused by conflicts with feature_test_macros(7) */
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <Python.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "native_client/src/shared/platform/nacl_sync_checked.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_host_desc.h"
#include "native_client/src/shared/platform/lind_platform.h"

#include "native_client/src/include/portability.h"

#include "native_client/src/trusted/desc/nacl_desc_io.h"
#include "native_client/src/trusted/service_runtime/include/sys/errno.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"
#include "native_client/src/trusted/service_runtime/nacl_config.h"
#include "native_client/src/trusted/service_runtime/nacl_app_thread.h"
#include "native_client/src/trusted/service_runtime/nacl_copy.h"
#include "native_client/src/trusted/service_runtime/lind_syscalls.h"

extern PyObject *py_context;

#define MAX_INARGS 16
#define MAX_OUTARGS 16

typedef enum _LindArgType {
    AT_INT,
    AT_STRING,
    AT_STRING_OPTIONAL,
    AT_DATA,
    AT_DATA_OPTIONAL
} LindArgType;

extern struct NaClDescVtbl const kNaClDescIoDescVtbl;

typedef struct _LindArg
{
    LindArgType type;
    uint64_t ptr;
    uint64_t len;
} LindArg;

static INLINE void DumpArg(const LindArg *arg)
{
    printf("%"NACL_PRId64":%"NACL_PRIu64":%"NACL_PRIu64"\n", (uint64_t)arg->type, arg->ptr, arg->len);
}

/*
 * If error occurs, any data malloc'ed in Preprocess
 * must be freed before return otherwise, they must
 * be freed in Cleanup
 */
typedef int(*PreprocessType)(struct NaClApp*, uint32_t, LindArg*, void**);
typedef int(*PostprocessType)(struct NaClApp*, int, int*, char*, int, void*);
typedef int(*CleanupType)(struct NaClApp*, uint32_t, LindArg*, void*);

typedef struct _StubType {PreprocessType pre; PostprocessType post; CleanupType clean;} StubType;

static int NaClFdToRepyFD(struct NaClApp *nap, int NaClFd) {
        struct NaClDesc *ndp;
        int retval;
        NaClFastMutexLock(&nap->desc_mu);
        ndp = NaClGetDescMu(nap, NaClFd);
        NaClFastMutexUnlock(&nap->desc_mu);
        if(!ndp || ndp->base.vtbl != (struct NaClRefCountVtbl const *)&kNaClDescIoDescVtbl) {
                retval = -1;
                goto cleanup;
        }
        retval = ((struct NaClDescIoDesc *)ndp)->hd->d;
cleanup:
        NaClDescSafeUnref(ndp);
        NaClLog(1, "NaClFdToRepyFD: %d->%d\n", NaClFd, retval);
        return retval;
}

static int NaClHostDescCtor(struct NaClHostDesc  *d,
                            int fd,
                            int flags) {
  d->d = fd;
  d->flags = flags;
  NaClLog(1, "%s\n", "NaClHostDescCtor: success.");
  return 0;
}

struct FcntlExchangeData {
        struct NaClHostDesc *nhd;
        int minFd;
};

int LindFcntlPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata) {
        int retval;
        int lindFd;
        NaClLog(1, "Entered LindFcntlPreprocess inNum=%8u\n", inNum);
        *xchangedata = 0;
        lindFd = NaClFdToRepyFD(nap, (int)(*(int64_t*)&inArgs[0].ptr));
        if(lindFd<0) {
                retval = -NACL_ABI_EINVAL;
                goto cleanup;
        }
        inArgs[0].ptr = lindFd;
        if(inNum>=3 && (inArgs[1].ptr == 0 /*F_DUPFD*/ || inArgs[1].ptr == 1030 /*F_DUPFD_CLOEXEC*/)) {
                *xchangedata = (struct FcntlExchangeData*)malloc(sizeof(struct FcntlExchangeData));
                if(!*xchangedata) {
                        retval = -NACL_ABI_ENOMEM;
                        goto cleanup;
                }
                ((struct FcntlExchangeData*)(*xchangedata))->nhd = (struct NaClHostDesc*)malloc(sizeof(struct NaClHostDesc));
                if(!((struct FcntlExchangeData*)(*xchangedata))->nhd) {
                        retval = -NACL_ABI_ENOMEM;
                        free(*xchangedata);
                        goto cleanup;
                }
                ((struct FcntlExchangeData*)(*xchangedata))->minFd = (int)(*(int64_t *)&inArgs[2].ptr);
                NaClLog(1, "MinFD: %d\n", ((struct FcntlExchangeData*)(*xchangedata))->minFd);
        }
        retval = 0;
cleanup:
        NaClLog(1, "%s\n", "Exiting LindFcntlPreprocess");
        return retval;
}

int LindFcntlPostprocess(struct NaClApp *nap,
                         int iserror,
                         int *code,
                         char *data,
                         int len,
                         void *xchangedata) {
        struct NaClHostDesc  *hd;
        int minFd;
        UNREFERENCED_PARAMETER(nap);
        UNREFERENCED_PARAMETER(iserror);
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(len);
        NaClLog(1, "%s\n", "Entered LindFcntlPostprocess");
        if(xchangedata) {
                hd = ((struct FcntlExchangeData*)xchangedata)->nhd;
                NaClHostDescCtor(hd, *code, NACL_ABI_O_RDWR);
                minFd = ((struct FcntlExchangeData*)xchangedata)->minFd;
                NaClLog(1, "Try to find a valid FD: %d\n", minFd);
                NaClFastMutexLock(&nap->desc_mu);
                while(DynArrayGet(&nap->desc_tbl, minFd)) {
                        ++minFd;
                }
                NaClLog(1, "Found a valid FD: %d\n", minFd);
                if (!DynArraySet(&nap->desc_tbl, minFd, ((struct NaClDesc *) NaClDescIoDescMake(hd)))) {
                NaClLog(LOG_FATAL,
                                "NaClSetDesc: could not set descriptor %d to 0x%08"
                                NACL_PRIxPTR"\n",
                                minFd,
                                (uintptr_t) hd);
                }
                NaClFastMutexUnlock(&nap->desc_mu);
                *code = minFd;
        }
        NaClLog(1, "%s\n", "Exiting LindFcntlPostprocess");
        return 0;
}

int LindFcntlCleanup(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void *xchangedata) {
        UNREFERENCED_PARAMETER(nap);
        UNREFERENCED_PARAMETER(inNum);
        UNREFERENCED_PARAMETER(inArgs);
        if(xchangedata) {
                free(xchangedata);
        }
        return 0;
}


int LindSelectCleanup(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void *xchangedata)
{
    UNREFERENCED_PARAMETER(nap);
    UNREFERENCED_PARAMETER(inNum);
    if (xchangedata) {
        free((void *)inArgs[1].ptr);
        free((void *)inArgs[2].ptr);
        free((void *)inArgs[3].ptr);
        free(xchangedata);
    }
    return 0;
}

int LindSelectPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    struct NaClDesc *ndp = NULL;
    int hfd;
    int retval = 0;
    int *mapdata;
    fd_set rs;
    fd_set ws;
    fd_set es;
    int64_t max_fd;
    int64_t max_hfd = -1;
    NaClLog(1, "Entered LindSelectPreprocess inNum=%8u\n", inNum);
    max_fd = *(int64_t*)&inArgs[0].ptr;
    if (inArgs[1].ptr) {
        rs = *(fd_set*)inArgs[1].ptr;
        inArgs[1].ptr = (uintptr_t)malloc(sizeof(fd_set));
        if (!inArgs[1].ptr) {
            retval = -NACL_ABI_ENOMEM;
            goto finish;
        }
        FD_ZERO((fd_set*)inArgs[1].ptr);
    }
    if(inArgs[2].ptr) {
        ws = *(fd_set*)inArgs[2].ptr;
        inArgs[2].ptr = (uintptr_t)malloc(sizeof(fd_set));
        if (!inArgs[2].ptr) {
            retval = -NACL_ABI_ENOMEM;
            goto cleanup_rs;
        }
        FD_ZERO((fd_set*)inArgs[2].ptr);
    }
    if(inArgs[3].ptr) {
        es = *(fd_set*)inArgs[3].ptr;
        inArgs[3].ptr = (uintptr_t)malloc(sizeof(fd_set));
        if (!inArgs[3].ptr) {
            retval = -NACL_ABI_ENOMEM;
            goto cleanup_ws;
        }
        FD_ZERO((fd_set*)inArgs[3].ptr);
    }
    *xchangedata = malloc(sizeof(int) * (FD_SETSIZE + 1));
    if (!*xchangedata) {
        retval = -NACL_ABI_ENOMEM;
        goto cleanup_es;
    }
    memset(*xchangedata, 0xFF, sizeof(int) * FD_SETSIZE);
    mapdata = &((int*)(*xchangedata))[1];
    NaClFastMutexLock(&nap->desc_mu);
    for(int i=0; i<max_fd; ++i) {
        ndp = NULL;
        if((inArgs[1].ptr && FD_ISSET(i, &rs)) ||
                (inArgs[2].ptr && FD_ISSET(i, &ws)) ||
                (inArgs[3].ptr && FD_ISSET(i, &es))) {
            ndp = NaClGetDescMu(nap, i);
            if(ndp && ndp->base.vtbl == (struct NaClRefCountVtbl const *)&kNaClDescIoDescVtbl) {
                hfd = ((struct NaClDescIoDesc*)ndp)->hd->d;
                NaClDescUnref(ndp);
                if(hfd<FD_SETSIZE) {
                    if(hfd > max_hfd) {
                        max_hfd = hfd;
                    }
                    mapdata[hfd]=i;
                } else {
                    NaClLog(LOG_ERROR, "Host desc too large: %d->%d\n", i, hfd);
                    retval = -NACL_ABI_EINVAL;
                    goto cleanup_xdata;
                }
            } else {
                NaClLog(LOG_ERROR, "Invalid NaCl desc: %d\n", i);
                NaClDescSafeUnref(ndp);
                retval = -NACL_ABI_EINVAL;
                goto cleanup_xdata;
            }
            if(inArgs[1].ptr && FD_ISSET(i, &rs)) {
                NaClLog(1, "%d in RS with host desc %d\n", i, hfd);
                FD_SET(hfd, (fd_set*)inArgs[1].ptr);
            }
            if(inArgs[2].ptr && FD_ISSET(i, &ws)) {
                NaClLog(1, "%d in WS with host desc %d\n", i, hfd);
                FD_SET(hfd, (fd_set*)inArgs[2].ptr);
            }
            if(inArgs[3].ptr && FD_ISSET(i, &es)) {
                NaClLog(1, "%d in ES with host desc %d\n", i, hfd);
                FD_SET(hfd, (fd_set*)inArgs[3].ptr);
            }
        }
    }
    *(int64_t *)&inArgs[0].ptr = max_hfd + 1;
    ((int *)(*xchangedata))[0] = max_hfd + 1;
    NaClLog(1, "max_fd is set to %"NACL_PRId64" was %"NACL_PRId64"\n", *(int64_t *)&inArgs[0].ptr, max_fd);
    NaClFastMutexUnlock(&nap->desc_mu);
    goto finish;
cleanup_xdata:
    free(*xchangedata);
cleanup_es:
    if(inArgs[3].ptr) {
        free((void *)inArgs[3].ptr);
    }
cleanup_ws:
    if(inArgs[2].ptr) {
        free((void *)inArgs[2].ptr);
    }
cleanup_rs:
    if(inArgs[1].ptr) {
        free((void *)inArgs[1].ptr);
    }
finish:
    NaClLog(1, "%s\n", "Exiting LindSelectPreprocess");
    return retval;
}

int LindSelectPostprocess(struct NaClApp *nap,
                          int iserror,
                          int *code,
                          char *data,
                          int len,
                          void *xchangedata) {
    int *mapdata;
    int max_hfd;
    int retval = 0;
    fd_set rs;
    fd_set ws;
    fd_set es;
    UNREFERENCED_PARAMETER(nap);
    UNREFERENCED_PARAMETER(iserror);
    UNREFERENCED_PARAMETER(code);
    UNREFERENCED_PARAMETER(len);
    FD_ZERO(&rs);
    FD_ZERO(&ws);
    FD_ZERO(&es);
    max_hfd = ((int*)xchangedata)[0];
    mapdata = &((int*)xchangedata)[1];
    for(int i=0; i<max_hfd; ++i) {
        if(FD_ISSET(i, &((struct select_results*)data)->r)) {
            if(-1 != mapdata[i]) {
                NaClLog(1, "%d in RS with nacl desc %d\n", i, mapdata[i]);
                FD_SET(mapdata[i], &rs);
            } else {
                NaClLog(1, "%d in RS not valid, ignored\n", i);
            }
        }
        if(FD_ISSET(i, &((struct select_results*)data)->w)) {
            if(-1 != mapdata[i]) {
                NaClLog(1, "%d in WS with nacl desc %d\n", i, mapdata[i]);
                FD_SET(mapdata[i], &ws);
            } else {
                NaClLog(1, "%d in WS not valid, ignored\n", i);
            }
        }
        if(FD_ISSET(i, &((struct select_results*)data)->e)) {
            if(-1 != mapdata[i]) {
                NaClLog(1, "%d in ES with nacl desc %d\n", i, mapdata[i]);
                FD_SET(mapdata[i], &es);
            } else {
                NaClLog(1, "%d in ES not valid, ignored\n", i);
            }
        }
    }
    ((struct select_results*)data)->r = rs;
    ((struct select_results*)data)->w = ws;
    ((struct select_results*)data)->e = es;
    return retval;
}

#define CONVERT_NACL_DESC_TO_LIND_START	                                                        \
    int retval = 0;                                                                             \
    struct NaClDesc * ndp;                                                                      \
    UNREFERENCED_PARAMETER(inNum);                                                              \
    UNREFERENCED_PARAMETER(xchangedata)

#define CONVERT_NACL_DESC_TO_LIND_END                                                           \
cleanup:                                                                                        \
    NaClDescSafeUnref(ndp);                                                                     \
    return retval

#define CONVERT_NACL_DESC_TO_LIND(x)                                                            \
    NaClFastMutexLock(&nap->desc_mu);                                                           \
    ndp = NaClGetDescMu(nap, (int)(*(int64_t*)&inArgs[(x)].ptr));                               \
    NaClFastMutexUnlock(&nap->desc_mu);                                                         \
    if(!ndp || ndp->base.vtbl != (struct NaClRefCountVtbl const *)&kNaClDescIoDescVtbl) {       \
        retval = -NACL_ABI_EINVAL;                                                              \
        goto cleanup;                                                                           \
    }                                                                                           \
    *(int64_t*)&inArgs[(x)].ptr = ((struct NaClDescIoDesc *)ndp)->hd->d;

#define ALLOC_RET_DESC()                                                                        \
    int retval = 0;                                                                             \
    UNREFERENCED_PARAMETER(nap);                                                                \
    UNREFERENCED_PARAMETER(inNum);                                                              \
    UNREFERENCED_PARAMETER(inArgs);                                                             \
    *xchangedata = malloc(sizeof(struct NaClHostDesc));                                         \
    if (!*xchangedata) {                                                                 \
      retval = -NACL_ABI_ENOMEM;                                                                \
      goto cleanup;                                                                             \
    }                                                                                           \
cleanup:                                                                                        \
    return retval

#define CONVERT_NACL_DESC_TO_LIND_AND_ALLOC_RET_DESC(x)                                         \
      int retval = 0;                                                                           \
      struct NaClDesc *ndp = {0};                                                               \
      UNREFERENCED_PARAMETER(inNum);                                                            \
      *xchangedata = malloc(sizeof(struct NaClHostDesc));                                       \
      if (!*xchangedata) {                                                               \
        retval = -NACL_ABI_ENOMEM;                                                              \
        goto cleanup;                                                                           \
      }                                                                                         \
      NaClFastMutexLock(&nap->desc_mu);                                                         \
      ndp = NaClGetDescMu(nap, (int)(*(int64_t*)&inArgs[(x)].ptr));                             \
      NaClFastMutexUnlock(&nap->desc_mu);                                                       \
      if(!ndp || ndp->base.vtbl != (struct NaClRefCountVtbl const *)&kNaClDescIoDescVtbl) {     \
          retval = -NACL_ABI_EINVAL;                                                            \
          goto cleanup;                                                                         \
      }                                                                                         \
      *(int64_t*)&inArgs[(x)].ptr = ((struct NaClDescIoDesc *)ndp)->hd->d;                      \
cleanup:                                                                                        \
      NaClDescSafeUnref(ndp);                                                                   \
      return retval

#define BUILD_AND_RETURN_NACL_DESC()                                                            \
    int retval = 0;                                                                             \
    struct NaClHostDesc  *hd;                                                                   \
    UNREFERENCED_PARAMETER(iserror);                                                            \
    UNREFERENCED_PARAMETER(data);                                                               \
    UNREFERENCED_PARAMETER(len);                                                                \
    hd = (struct NaClHostDesc*)xchangedata;                                                     \
    NaClHostDescCtor(hd, *code, NACL_ABI_O_RDWR);                                               \
    *code = NaClSetAvail(nap, ((struct NaClDesc *) NaClDescIoDescMake(hd)));                    \
    return retval

int LindSocketPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    ALLOC_RET_DESC();
}

int LindSocketPostprocess(struct NaClApp *nap,
                          int iserror,
                          int *code,
                          char *data,
                          int len,
                          void *xchangedata)
{
    BUILD_AND_RETURN_NACL_DESC();
}

int LindAcceptPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    CONVERT_NACL_DESC_TO_LIND_AND_ALLOC_RET_DESC(0);
}

int LindAcceptPostprocess(struct NaClApp *nap,
                          int iserror,
                          int *code,
                          char *data,
                          int len,
                          void *xchangedata)
{
    BUILD_AND_RETURN_NACL_DESC();
}

int LindCommonPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    CONVERT_NACL_DESC_TO_LIND_START;
    CONVERT_NACL_DESC_TO_LIND(0);
    CONVERT_NACL_DESC_TO_LIND_END;
}

int LindEpollCreatePreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    ALLOC_RET_DESC();
}

int LindEpollCreatePostprocess(struct NaClApp *nap,
                               int iserror,
                               int *code,
                               char *data,
                               int len,
                               void *xchangedata)
{
    BUILD_AND_RETURN_NACL_DESC();
}

int LindEpollCtlPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    CONVERT_NACL_DESC_TO_LIND_START;
    CONVERT_NACL_DESC_TO_LIND(0);
    CONVERT_NACL_DESC_TO_LIND(2);
    CONVERT_NACL_DESC_TO_LIND_END;
}

typedef union epoll_data
{
  void *ptr;
  int fd;
  uint32_t u32;
  uint64_t u64;
} epoll_data_t;

struct epoll_event
{
  uint32_t events;
  epoll_data_t data;
};

int LindEpollWaitPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    CONVERT_NACL_DESC_TO_LIND_START;
    CONVERT_NACL_DESC_TO_LIND(0);
    CONVERT_NACL_DESC_TO_LIND_END;
}

int LindEpollWaitPostprocess(struct NaClApp *nap,
                             int iserror,
                             int *code,
                             char *data,
                             int len,
                             void *xchangedata)
{
    int retval = 0;
    int nfds;
    struct epoll_event *pfds;
    struct NaClDesc * ndp;
    int hfd;
    UNREFERENCED_PARAMETER(nap);
    UNREFERENCED_PARAMETER(iserror);
    UNREFERENCED_PARAMETER(code);
    UNREFERENCED_PARAMETER(len);
    UNREFERENCED_PARAMETER(xchangedata);
    nfds=*code;
    pfds = (struct epoll_event*)data;
    for(int i=0; i<nfds; ++i) {
        for(int j=0; j<1024; ++j) {
            NaClFastMutexLock(&nap->desc_mu);
            ndp = NaClGetDescMu(nap, j);
            NaClFastMutexUnlock(&nap->desc_mu);
            if(!ndp || ndp->base.vtbl != (struct NaClRefCountVtbl const *)&kNaClDescIoDescVtbl) {
                NaClDescSafeUnref(ndp);
                continue;
            }
            hfd = ((struct NaClDescIoDesc *)ndp)->hd->d;
            if(pfds[i].data.fd == hfd) {
                pfds[i].data.fd = j;
            }
            NaClDescUnref(ndp);
        }
    }
    return retval;
}

int LindSocketPairPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    int retval = 0;
    UNREFERENCED_PARAMETER(nap);
    UNREFERENCED_PARAMETER(inNum);
    UNREFERENCED_PARAMETER(inArgs);
    *xchangedata = malloc(sizeof(struct NaClHostDesc)*2);
    if (!*xchangedata) {
      retval = -NACL_ABI_ENOMEM;
      goto cleanup;
    }
cleanup:
    return retval;
}

int LindSocketPairPostprocess(struct NaClApp *nap,
                              int iserror,
                              int *code,
                              char *data,
                              int len,
                              void *xchangedata)
{
    int retval = 0;
    struct NaClHostDesc  *hd;
    int lind_fd;
    UNREFERENCED_PARAMETER(iserror);
    UNREFERENCED_PARAMETER(code);
    UNREFERENCED_PARAMETER(len);
    for(int i=0; i<2; ++i) {
        hd = &((struct NaClHostDesc*)xchangedata)[i];
        lind_fd = ((int*)data)[i];
        NaClHostDescCtor(hd, lind_fd, NACL_ABI_O_RDWR);
        ((int*)data)[i] = NaClSetAvail(nap, ((struct NaClDesc *) NaClDescIoDescMake(hd)));
    }
    return retval;
}

struct poll_map
{
    int nacl_fd;
    int lind_fd;
};

int LindPollPreprocess(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void** xchangedata)
{
    int retval = 0;
    struct pollfd *pfds;
    struct pollfd *inpfds;
    struct poll_map *mapdata;
    int nfds;
    struct NaClDesc *ndp;
    UNREFERENCED_PARAMETER(inNum);
    nfds = (int)inArgs[0].ptr;
    if(nfds <= 0) {
        retval = -NACL_ABI_EINVAL;
        goto finish;
    }
    inpfds = (struct pollfd*)inArgs[2].ptr;
    if(!inpfds) {
        retval = -NACL_ABI_EINVAL;
        goto finish;
    }
    *xchangedata = malloc(sizeof(int)+sizeof(struct poll_map)*nfds);
    if (!*xchangedata) {
      retval = -NACL_ABI_ENOMEM;
      goto finish;
    }
    ((int*)(*xchangedata))[0] = nfds; //first sizeof(int) bytes contains # of fds
    mapdata = (struct poll_map*)&((int*)(*xchangedata))[1]; //map data begins after sizeof(int) bytes
    pfds = malloc(sizeof *pfds * nfds);
    if (!pfds) {
      retval = -NACL_ABI_ENOMEM;
      goto cleanup_xdata;
    }
    NaClFastMutexLock(&nap->desc_mu);
    for(int i=0; i<nfds; ++i) {
        pfds[i] = inpfds[i];
        ndp = NaClGetDescMu(nap, inpfds[i].fd);
        if(!ndp || ndp->base.vtbl != (struct NaClRefCountVtbl const *)&kNaClDescIoDescVtbl) {
            NaClDescSafeUnref(ndp);
            retval = -NACL_ABI_EINVAL;
            goto cleanup_pfds;
        }
        pfds[i].fd = ((struct NaClDescIoDesc*)ndp)->hd->d;
        mapdata[i].nacl_fd = inpfds[i].fd;
        mapdata[i].lind_fd = pfds[i].fd;
        NaClDescUnref(ndp);
    }
    NaClFastMutexUnlock(&nap->desc_mu);
    inArgs[2].ptr = (uint64_t)(uintptr_t)pfds;
    goto finish;
cleanup_pfds:
    free(pfds);
cleanup_xdata:
    free(*xchangedata);
finish:
    return retval;
}

int LindPollPostprocess(struct NaClApp *nap,
                        int iserror,
                        int *code,
                        char *data,
                        int len,
                        void *xchangedata)
{
    int retval = 0;
    struct poll_map *mapdata;
    int nfds;
    struct pollfd *pfds;
    UNREFERENCED_PARAMETER(nap);
    UNREFERENCED_PARAMETER(iserror);
    UNREFERENCED_PARAMETER(code);
    UNREFERENCED_PARAMETER(len);
    /* first sizeof(int) bytes contains # of fds */
    nfds = ((int *)xchangedata)[0];
    /* map data begins after sizeof(int) bytes */
    mapdata = (struct poll_map*)&((int *)xchangedata)[1];
    pfds = (struct pollfd*)data;
    for(int i = 0; i < nfds; ++i) {
        for(int j = 0; j < nfds; ++j) {
            if(pfds[i].fd == mapdata[j].lind_fd) {
                pfds[i].fd = mapdata[j].nacl_fd;
            }
        }
    }
    return retval;
}

int LindPollCleanup(struct NaClApp *nap, uint32_t inNum, LindArg *inArgs, void *xchangedata)
{
    UNREFERENCED_PARAMETER(nap);
    UNREFERENCED_PARAMETER(inNum);
    if(xchangedata) {
        free((void*)inArgs[2].ptr);
        free(xchangedata);
    }
    return 0;
}

StubType stubs[] = {
        {0}, /* 0 */
        {0}, /* 1 LIND_debug_noop */
        {0}, /* 2 LIND_safe_fs_access */
        {0}, /* 3 LIND_debug_trace */
        {0}, /* 4 LIND_safe_fs_unlink */
        {0}, /* 5 LIND_safe_fs_link */
        {0}, /* 6 LIND_safe_fs_chdir */
        {0}, /* 7 LIND_safe_fs_mkdir */
        {0}, /* 8 LIND_safe_fs_rmdir */
        {0}, /* 9 LIND_safe_fs_xstat */
        {0}, /* 10 LIND_safe_fs_open */
        {0}, /* 11 */
        {0}, /* 12 */
        {0}, /* 13 */
        {0}, /* 14 */
        {0}, /* 15 */
        {0}, /* 16 */
        {0}, /* 17 */
        {0}, /* 18 */
        {LindCommonPreprocess, 0, 0}, /* 19 LIND_safe_fs_fstatfs */
        {0}, /* 20 */
        {0}, // 21
        {0}, /* 22 */
        {0}, /* 23 */
        {0}, /* 24 */
        {0}, /* 25 */
        {0}, /* 26 */
        {0}, /* 27 */
        {LindFcntlPreprocess, LindFcntlPostprocess, LindFcntlCleanup}, /* 28 LIND_safe_fs_fcntl */
        {0}, /* 29 */
        {0}, /* 30 */
        {0}, /* 31 */
        {LindSocketPreprocess, LindSocketPostprocess, 0}, /* 32 LIND_safe_net_socket */
        {LindCommonPreprocess, 0, 0}, /* 33 LIND_safe_net_bind */
        {LindCommonPreprocess, 0, 0}, /* 34 LIND_safe_net_send */
        {LindCommonPreprocess, 0, 0}, /* 35 LIND_safe_net_sendto */
        {LindCommonPreprocess, 0, 0}, /* 36 LIND_safe_net_recv */
        {LindCommonPreprocess, 0, 0}, /* 37 LIND_safe_net_recvfrom */
        {LindCommonPreprocess, 0, 0}, /* 38 LIND_safe_net_connect */
        {LindCommonPreprocess, 0, 0}, /* 39 LIND_safe_net_listen */
        {LindAcceptPreprocess, LindAcceptPostprocess, 0}, /* 40 LIND_safe_net_accept */
        {LindCommonPreprocess, 0, 0}, /* 41 LIND_safe_net_getpeername */
        {LindCommonPreprocess, 0, 0}, /* 42 LIND_safe_net_getsockname */
        {LindCommonPreprocess, 0, 0}, /* 43 LIND_safe_net_getsockopt */
        {LindCommonPreprocess, 0, 0}, /* 44 LIND_safe_net_setsockopt */
        {LindCommonPreprocess, 0, 0}, /* 45 LIND_safe_net_shutdown */
        {LindSelectPreprocess, LindSelectPostprocess, LindSelectCleanup}, /* 46 LIND_safe_net_select */
        {0}, /* 47 */
        {LindPollPreprocess, LindPollPostprocess, LindPollCleanup}, /* 48 LIND_safe_net_poll */
        {LindSocketPairPreprocess, LindSocketPairPostprocess, 0}, /* 49 LIND_safe_net_socketpair */
        {0}, /* 50 */
        {0}, /* 51 */
        {0}, /* 52 */
        {0}, /* 53 */
        {0}, /* 54 */
        {0}, /* 55 */
        {LindEpollCreatePreprocess, LindEpollCreatePostprocess, 0}, /* 56 epoll_create */
        {LindEpollCtlPreprocess, 0, 0}, /* 57 epoll_ctl */
        {LindEpollWaitPreprocess, LindEpollWaitPostprocess, 0}, /* 58 epoll_wait */
        {LindCommonPreprocess, 0, 0}, /* 59 sendmsg */
        {LindCommonPreprocess, 0, 0}, /* 60 */
        {0} /* 61 LIND_sys_pipe */
};


static int NaClCopyZStr(struct NaClApp *nap,
                        char           *dst_buffer,
                        size_t         dst_buffer_bytes,
                        uintptr_t      src_sys_addr) {
  NaClCopyTakeLock(nap);
  strncpy(dst_buffer, (char *) src_sys_addr, dst_buffer_bytes);
  NaClCopyDropLock(nap);

  /* POSIX strncpy pads with NUL characters */
  if (dst_buffer[dst_buffer_bytes - 1] != '\0') {
    dst_buffer[dst_buffer_bytes - 1] = '\0';
    return 0;
  }
  return 1;
}

int32_t NaClSysLindSyscall(struct NaClAppThread *natp,
                           uint32_t callNum,
                           uint32_t inNum,
                           void *inArgs,
                           uint32_t outNum,
                           void *outArgs)
{
    struct NaClApp *nap = natp->nap;
    int retval = -NACL_ABI_EINVAL;
    uintptr_t argSysAddr = 0;
    char stringArg[NACL_CONFIG_PATH_MAX] = {0};
    LindArg inArgSys[MAX_INARGS] = {0};
    LindArg outArgSys[MAX_OUTARGS] = {0};
    PyObject *callArgs = NULL;
    PyObject *apiArg = NULL;
    PyObject *response = NULL;
    PyGILState_STATE gstate = {0};
    unsigned int i = 0;
    int offset = 0;
    int _code = 0;
    int _isError = 0;
    char *_data = NULL;
    int _len = 0;
    void *xchangeData = NULL;
    clock_t lind_sys_begin = 0;
    clock_t lind_sys_finish = 0;

    NaClLog(1, "[NaClSysLindSyscall] Entered: callNum=%u inNum=%u outNum=%u\n", callNum, inNum, outNum);

    // yiwen: start recording time for making a Lind system call, this includes the time to parse and prepare the argument passing right now
    lind_sys_begin = clock();

    gstate = PyGILState_Ensure();

    if (inNum>MAX_INARGS || outNum>MAX_OUTARGS) {
        NaClLog(LOG_ERROR, "NaClSysLindSyscall: Number of in/out arguments too large\n");
        retval = -NACL_ABI_EINVAL;
        goto cleanup;
    }

    if ((inNum && !inArgs) || (outNum && !outArgs)) {
        NaClLog(LOG_ERROR, "NaClSysLindSyscall: in/out arguments are NULL\n");
        retval = -NACL_ABI_EFAULT;
        goto cleanup;
    }

    if (inNum && !NaClCopyInFromUser(nap, inArgSys, (uintptr_t)inArgs, sizeof(LindArg)*inNum)) {
        retval = -NACL_ABI_EFAULT;
        NaClLog(LOG_ERROR, "NaClSysLindSyscall: invalid input argument address\n");
        goto cleanup;
    }

    for (uint32_t j = 0; j<inNum; ++j) {
        if(inArgSys[j].type != AT_INT) {
            if(inArgSys[j].ptr) {
                argSysAddr = NaClUserToSysAddrRange(nap, (uintptr_t)inArgSys[j].ptr, inArgSys[j].len);
                if(kNaClBadAddress == argSysAddr) {
                    NaClLog(LOG_ERROR, "NaClSysLindSyscall: invalid input data address\n");
                    retval = -NACL_ABI_EFAULT;
                    goto cleanup;
                }
                inArgSys[j].ptr = argSysAddr;
            } else if(inArgSys[j].type == AT_DATA || inArgSys[j].type == AT_STRING) {
                NaClLog(LOG_ERROR, "NaClSysLindSyscall: mandatory input is NULL\n");
                retval = -NACL_ABI_EFAULT;
                goto cleanup;
            }
        }
    }

    if (outNum && !NaClCopyInFromUser(nap, outArgSys, (uintptr_t)outArgs, sizeof(LindArg)*outNum)) {
        NaClLog(LOG_ERROR, "NaClSysLindSyscall: invalid output argument address\n");
        retval = -NACL_ABI_EFAULT;
        goto cleanup;
    }

    for (uint32_t j = 0; j < outNum; ++j) {
        /* mandatory output address is zero */
        if(outArgSys[j].type == AT_INT || (!outArgSys[j].ptr && outArgSys[j].type == AT_DATA)) {
                retval = -NACL_ABI_EFAULT;
                goto cleanup;
        }
    }

    if (stubs[callNum].pre) {
        retval = stubs[callNum].pre(nap, inNum, inArgSys, &xchangeData);
        if (retval) {
            goto cleanup;
        }
    }

    callArgs = PyList_New(0);
    apiArg = PyTuple_New(2);
    PyTuple_SetItem(apiArg, 0, PyInt_FromLong(callNum));
    PyTuple_SetItem(apiArg, 1, callArgs);

    for (i=0; i<inNum; ++i) {
        switch(inArgSys[i].type) {
        case AT_INT:
            NaClLog(1, "Int argument: %" NACL_PRId64 ", %" NACL_PRIu64 "\n",
                    *(int64_t *)&inArgSys[i].ptr,
                    inArgSys[i].len);
            PyList_Append(callArgs, PyInt_FromLong(*(int64_t *)&inArgSys[i].ptr));
            break;
        case AT_STRING:
        case AT_STRING_OPTIONAL:
            if(inArgSys[i].ptr) {
                PyGILState_Release(gstate);
                if (!NaClCopyZStr(nap, stringArg, sizeof(stringArg), (uintptr_t)inArgSys[i].ptr)) {
                    gstate = PyGILState_Ensure();
                    if (stringArg[0] == '\0') {
                        NaClLog(LOG_ERROR, "NaClSysLindSyscall: input string is empty\n");
                        retval = -NACL_ABI_EFAULT;
                    } else {
                        NaClLog(LOG_ERROR,
                                "NaClSysLindSyscall: input string is too long (>%d)\n",
                                NACL_CONFIG_PATH_MAX);
                        retval = -NACL_ABI_ENAMETOOLONG;
                    }
                    goto cleanup;
                }
                gstate = PyGILState_Ensure();
                NaClLog(1, "String argument: %s\n", stringArg);
                PyList_Append(callArgs, PyString_FromString(stringArg));
            } else if(inArgSys[i].type == AT_STRING_OPTIONAL) {
                NaClLog(1, "%s\n", "Optional empty string argument");
                PyList_Append(callArgs, Py_None);
                Py_INCREF(Py_None);
            } else {
                NaClLog(LOG_ERROR, "NaClSysLindSyscall: input string is NULL\n");
                retval = -NACL_ABI_EFAULT;
                goto cleanup;
            }
            break;
        case AT_DATA:
        case AT_DATA_OPTIONAL:
            if(inArgSys[i].ptr) {
                NaClLog(1, "Data argument of length: %u\n", (unsigned int)inArgSys[i].len);
                PyGILState_Release(gstate);
                NaClXMutexLock(&nap->mu);
                gstate = PyGILState_Ensure();
                PyList_Append(callArgs,
                              PyString_FromStringAndSize((char *)inArgSys[i].ptr,
                              inArgSys[i].len));
                NaClXMutexUnlock(&nap->mu);
            } else if(inArgSys[i].type == AT_DATA_OPTIONAL) {
                NaClLog(1, "%s\n", "Optional empty data argument");
                PyList_Append(callArgs, Py_None);
                Py_INCREF(Py_None);
            } else {
                NaClLog(LOG_ERROR, "NaClSysLindSyscall: input data is NULL\n");
                retval = -NACL_ABI_EFAULT;
                goto cleanup;
            }
            break;
        default:
            NaClLog(LOG_ERROR, "NaClSysLindSyscall: invalid input data type\n");
            retval = -NACL_ABI_EINVAL;
            goto cleanup;
        }
    }

    response = CallPythonFunc(py_context, "LindSyscall", apiArg);
    if (!response) {
        goto error;
    }

    ParseResponse(response, &_isError, &_code, &_data, &_len);
    if(!_isError) {
        if(stubs[callNum].post) {
            stubs[callNum].post(nap, _isError, &_code, _data, _len, xchangeData);
        }
        if(outNum == 1) {
            assert(((unsigned int)_len)<=outArgSys[0].len);
            PyGILState_Release(gstate);
            if(outArgSys[0].ptr && !NaClCopyOutToUser(nap,
                                                      (uintptr_t)outArgSys[0].ptr,
                                                      _data,
                                                      _len)) {
                 gstate = PyGILState_Ensure();
                 retval = -NACL_ABI_EFAULT;
                 goto cleanup;
            }
            gstate = PyGILState_Ensure();
        } else if (outNum > 1) {
            offset = 0;
            for(i=0; i<outNum; ++i) {
                NaClLog(1, "Out#%d, len = %" NACL_PRIu32
                        "maxlen=%" NACL_PRIu64 "\n",
                        i, (unsigned int)(((int *)_data)[i]),
                        outArgSys[i].len);
                CHECK(((unsigned int)(((int*)_data)[i])) <= outArgSys[i].len);
                PyGILState_Release(gstate);
                if(outArgSys[i].ptr && !NaClCopyOutToUser(nap,
                                                          (uintptr_t)outArgSys[i].ptr,
                                                          _data + sizeof(int) * outNum+offset,
                                                          ((int *)_data)[i])) {
                    gstate = PyGILState_Ensure();
                    retval = -NACL_ABI_EFAULT;
                    goto cleanup;
                }
                gstate = PyGILState_Ensure();
                offset += ((int *)_data)[i];
            }
        }
    }
    if(stubs[callNum].clean) {
        stubs[callNum].clean(nap, inNum, inArgSys, xchangeData);
    }
    retval = _isError?-_code:_code;
    goto cleanup;
error:
    PyErr_Print();
    NaClLog(LOG_ERROR, "NaClSysLindSyscall: Python error\n");
cleanup:
    Py_XDECREF(apiArg);
    Py_XDECREF(response);
    PyGILState_Release(gstate);

    // yiwen: record the ending time of the Lind system call, this includes the post-processing of arguments right now
    lind_sys_finish = clock();
    // yiwen: record Lind system call timing info
    lind_syscall_counter++;
    lind_syscall_invoked_times[callNum]++;
    lind_syscall_execution_time[callNum] += (double)(lind_sys_finish - lind_sys_begin) / CLOCKS_PER_SEC;
    return retval;
}
