# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES="
crypto/base64/base64_test
crypto/bio/bio_test
crypto/bn/bn_test
crypto/bytestring/bytestring_test
crypto/cipher/aead_test
crypto/cipher/aead_test
crypto/cipher/aead_test
crypto/cipher/aead_test
crypto/cipher/aead_test
crypto/cipher/aead_test
crypto/cipher/cipher_test
crypto/dh/dh_test
crypto/digest/digest_test
crypto/dsa/dsa_test
crypto/ec/example_mul
crypto/ecdsa/ecdsa_test
crypto/err/err_test
crypto/evp/evp_test
crypto/hmac/hmac_test
crypto/lhash/lhash_test
crypto/modes/gcm_test
crypto/pkcs8/pkcs12_test
crypto/rsa/rsa_test
crypto/x509/pkcs7_test
crypto/x509v3/tab_test
crypto/x509v3/v3name_test
ssl/pqueue/pqueue_test
ssl/ssl_test
"

InstallStep() {
  MakeDir ${DESTDIR_LIB}
  MakeDir ${DESTDIR_INCLUDE}/openssl
  LogExecute install crypto/libcrypto.a ${DESTDIR_LIB}/
  LogExecute install ${SRC_DIR}/include/openssl/* -t ${DESTDIR_INCLUDE}/openssl
}

TestStep() {
  if [[ ${TOOLCHAIN} == pnacl ]]; then
    return
  fi
  LogExecute ssl/ssl_test.sh
  # TODO(sbc): Investigate test failure in digest_test
  #LogExecute crypto/digest/digest_test.sh

  # all_tests was converted to go, and we don't have the go toolchain
  # as a prerequiste.
  #bash ../boringssl-git/util/all_tests.sh ../boringssl-git/ .sh
}
