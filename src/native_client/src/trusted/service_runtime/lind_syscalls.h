/*
 * lind_api.h
 *
 *  Created on: Jun 27, 2013
 *      Author: sji
 */

#ifndef LIND_API_H_
#define LIND_API_H_

#include "native_client/src/shared/platform/lind_platform.h"
#include "native_client/src/trusted/service_runtime/nacl_app_thread.h"

int32_t NaClSysLindSyscall(struct NaClAppThread *natp,
                           uint32_t callNum,
                           uint32_t inNum,
                           void* inArgs,
                           uint32_t outNum,
                           void* outArgs);

#endif /* LIND_API_H_ */
