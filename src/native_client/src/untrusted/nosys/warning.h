/*
 * Copyright 2008 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

/*
 * NaCl libnosys stub_warning macro. Note: can only be used with GCC & ELF.
 */

#ifndef NATIVE_CLIENT_SRC_UNTRUSTED_NOSYS_WARNING_H_
#define NATIVE_CLIENT_SRC_UNTRUSTED_NOSYS_WARNING_H_

/* We want the .gnu.warning.SYMBOL section to be unallocated.
   Tacking on "\n\t#" to the section name makes gcc put it's bogus
   section attributes on what looks like a comment to the assembler.  */
/* This hack does not work with PNaCl, and section attributes are not
   allowed on globals in the bitcode ABI, so we just define it away.
*/

#ifndef __pnacl__
#define link_warning(symbol, msg) \
  static const char __evoke_link_warning_##symbol[] \
    __attribute__((__used__, section (".gnu.warning." #symbol "\n\t#"))) = msg
/* A canned warning for sysdeps/stub functions.
   The GNU linker prepends a "warning: " string.  */
#define stub_warning(name) \
  link_warning(name, \
  "the `" #name "\' function is not implemented and will always fail")
#else
#define link_warning(symbol, msg)
#define stub_warning(symbol)
#endif

#endif  /* NATIVE_CLIENT_SRC_UNTRUSTED_NOSYS_WARNING_H_ */
