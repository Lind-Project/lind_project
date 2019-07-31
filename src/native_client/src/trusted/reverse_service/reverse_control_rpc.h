/*
 * Copyright (c) 2011 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef NATIVE_CLIENT_SRC_TRUSTED_REVERSE_SERVICE_REVERSE_CONTROL_RPC_H_
#define NATIVE_CLIENT_SRC_TRUSTED_REVERSE_SERVICE_REVERSE_CONTROL_RPC_H_

/*
 * Reverse channel control RPCs.  Used by the service runtime reverse
 * setup proceedure, testing, and by the manifest proxy to add a new
 * client channel.
 */

#define NACL_REVERSE_CONTROL_TEST             "test:s:"
#define NACL_REVERSE_CONTROL_LOG              "log:s:"
#define NACL_REVERSE_CONTROL_ADD_CHANNEL      "add_channel::b"
#define NACL_REVERSE_CONTROL_INIT_DONE        "init_done::"
#define NACL_REVERSE_CONTROL_REPORT_STATUS    "exit_status:i:"
#define NACL_REVERSE_CONTROL_POST_MESSAGE     "post_message:C:i"
#define NACL_REVERSE_CONTROL_CREATE_PROCESS   "create_process::ihh"
#define NACL_REVERSE_REQUEST_QUOTA_FOR_WRITE  "request_quota_for_write:Cll:l"
#define NACL_REVERSE_CONTROL_CREATE_PROCESS_INTERLOCKED \
  "create_process_interlocked::hhi"

#endif
