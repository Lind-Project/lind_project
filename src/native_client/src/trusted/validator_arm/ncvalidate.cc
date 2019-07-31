/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <climits>
#include <limits>
#include <vector>

#include "native_client/src/include/nacl_string.h"
#include "native_client/src/include/portability.h"
#include "native_client/src/shared/platform/nacl_check.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/utils/types.h"
#include "native_client/src/trusted/service_runtime/nacl_config.h"
#include "native_client/src/trusted/cpu_features/arch/arm/cpu_arm.h"
#include "native_client/src/trusted/validator_arm/model.h"
#include "native_client/src/trusted/validator_arm/validator.h"
#include "native_client/src/trusted/validator/ncvalidate.h"

using nacl_arm_val::SfiValidator;
using nacl_arm_val::CodeSegment;
using nacl_arm_dec::Register;
using nacl_arm_dec::RegisterList;
using std::vector;

static inline bool IsAligned(intptr_t value) {
  return (value & (NACL_BLOCK_SHIFT - 1)) == 0;
}

static inline bool IsAlignedPtr(void *ptr) {
  return IsAligned(reinterpret_cast<intptr_t>(ptr));
}

static const uintptr_t kBytesPerBundle = 1 << NACL_BLOCK_SHIFT;
static const uintptr_t kBytesOfCodeSpace = 1U * 1024 * 1024 * 1024;
static const uintptr_t kBytesOfDataSpace = 1U * 1024 * 1024 * 1024;

// The following checks should have been checked at a higher level, any error
// here is a break of the validator's preconditions. Don't try to recover.
static inline void CheckAddressOverflow(uint8_t *ptr, size_t size) {
  CHECK(uintptr_t(ptr) < std::numeric_limits<uintptr_t>::max() - size);
}

static inline void CheckAddressAlignAndOverflow(uint8_t *ptr, size_t size) {
  CHECK(IsAlignedPtr(ptr));
  CHECK(IsAligned(size));
  CheckAddressOverflow(ptr, size);
}

static NaClValidationStatus ValidatorCopyArm(
    uintptr_t guest_addr,
    uint8_t *data_old,
    uint8_t *data_new,
    size_t size,
    const NaClCPUFeatures *cpu_features,
    NaClCopyInstructionFunc copy_func) {
  /* TODO(jfb) Use a safe cast here. */
  const NaClCPUFeaturesArm *features =
      (const NaClCPUFeaturesArm *) cpu_features;

  CheckAddressAlignAndOverflow((uint8_t *) guest_addr, size);
  CheckAddressOverflow(data_old, size);
  CheckAddressOverflow(data_new, size);

  // guest_addr should always be within 4GB, so static casts should not cause
  // any problems here. They are needed to shut up VC compiler.
  CHECK(guest_addr <= std::numeric_limits<uint32_t>::max());
  CodeSegment dest_code(data_old, static_cast<uint32_t>(guest_addr), size);
  CodeSegment source_code(data_new, static_cast<uint32_t>(guest_addr), size);
  SfiValidator validator(
      kBytesPerBundle,
      kBytesOfCodeSpace,
      kBytesOfDataSpace,
      RegisterList(Register::Tp()),
      RegisterList(Register::Sp()),
      features);

  bool success = validator.CopyCode(source_code, dest_code, copy_func,
                                    NULL);
  return success ? NaClValidationSucceeded : NaClValidationFailed;
}

static NaClValidationStatus ValidatorCodeReplacementArm(
    uintptr_t guest_addr,
    uint8_t *data_old,
    uint8_t *data_new,
    size_t size,
    const NaClCPUFeatures *cpu_features) {
  /* TODO(jfb) Use a safe cast here. */
  const NaClCPUFeaturesArm *features =
      (const NaClCPUFeaturesArm *) cpu_features;

  CheckAddressAlignAndOverflow((uint8_t *) guest_addr, size);
  CheckAddressOverflow(data_old, size);
  CheckAddressOverflow(data_new, size);

  CHECK(guest_addr <= std::numeric_limits<uint32_t>::max());
  CodeSegment new_code(data_new, static_cast<uint32_t>(guest_addr), size);
  CodeSegment old_code(data_old, static_cast<uint32_t>(guest_addr), size);
  SfiValidator validator(
      kBytesPerBundle,
      kBytesOfCodeSpace,
      kBytesOfDataSpace,
      RegisterList(Register::Tp()),
      RegisterList(Register::Sp()),
      features);

  bool success = validator.ValidateSegmentPair(old_code, new_code, NULL);
  return success ? NaClValidationSucceeded : NaClValidationFailed;
}

EXTERN_C_BEGIN

static int NCValidateSegment(
    uint8_t *mbase,
    uint32_t vbase,
    size_t size,
    const NaClCPUFeatures *cpu_features) {
  /* TODO(jfb) Use a safe cast here. */
  const NaClCPUFeaturesArm *features =
      (const NaClCPUFeaturesArm *) cpu_features;

  SfiValidator validator(
      kBytesPerBundle,
      kBytesOfCodeSpace,
      kBytesOfDataSpace,
      RegisterList(Register::Tp()),
      RegisterList(Register::Sp()),
      features);

  vector<CodeSegment> segments;
  segments.push_back(CodeSegment(mbase, vbase, size));

  bool success = validator.validate(segments, NULL);
  if (!success) return 2;  // for compatibility with old validator
  return 0;
}

static NaClValidationStatus ApplyValidatorArm(
    uintptr_t guest_addr,
    uint8_t *data,
    size_t size,
    int stubout_mode,
    int readonly_text,
    const NaClCPUFeatures *cpu_features,
    const struct NaClValidationMetadata *metadata,
    struct NaClValidationCache *cache) {
  /* The ARM validator is currently unsafe w.r.t. caching. */
  UNREFERENCED_PARAMETER(metadata);
  UNREFERENCED_PARAMETER(cache);
  CheckAddressAlignAndOverflow((uint8_t *) guest_addr, size);
  CheckAddressOverflow(data, size);
  CheckAddressOverflow(data, size);

  if (stubout_mode)
    return NaClValidationFailedNotImplemented;
  if (readonly_text)
    return NaClValidationFailedNotImplemented;

  CHECK(guest_addr <= std::numeric_limits<uint32_t>::max());
  return (NCValidateSegment(data,
                            static_cast<uint32_t>(guest_addr),
                            size,
                            cpu_features) == 0)
         ? NaClValidationSucceeded
         : NaClValidationFailed;
}

static struct NaClValidatorInterface validator = {
  FALSE, /* Optional stubout_mode is not implemented.            */
  FALSE, /* Optional readonly_text mode is not implemented.      */
  TRUE,  /* Optional code replacement functions are implemented. */
  ApplyValidatorArm,
  ValidatorCopyArm,
  ValidatorCodeReplacementArm,
  sizeof(NaClCPUFeaturesArm),
  NaClSetAllCPUFeaturesArm,
  NaClGetCurrentCPUFeaturesArm,
  NaClFixCPUFeaturesArm,
};

const struct NaClValidatorInterface *NaClValidatorCreateArm() {
  return &validator;
}

/*
 * It should be moved to be part of sel_ldr, not the validator.
 */
int NaClCopyInstruction(uint8_t *dst, uint8_t *src, uint8_t sz) {
  CHECK(sz == nacl_arm_dec::kArm32InstSize / CHAR_BIT);
  *(volatile uint32_t*) dst = *(volatile uint32_t*) src;
  // Don't invalidate i-cache on every instruction update.
  // CPU executing partially updated code doesn't look like a problem,
  // as we know for sure that both old and new instructions are safe,
  // so is their mix (single instruction update is atomic).
  // We just have to make sure that unintended fallthrough doesn't
  // happen, and we don't change position of guard instructions.
  // Problem is that code is mapped for execution at different address
  // that one we use here, and ARM usually use virtually indexed caches,
  // so we couldn't invalidate correctly anyway.
  return 0;
}

EXTERN_C_END
