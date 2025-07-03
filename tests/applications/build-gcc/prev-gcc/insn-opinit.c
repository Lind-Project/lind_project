/* Generated automatically by the program `genopinit'
from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "tm_p.h"
#include "flags.h"
#include "insn-config.h"
#include "recog.h"
#include "expr.h"
#include "optabs.h"
#include "reload.h"

void
init_all_optabs (void)
{
#ifdef FIXUNS_TRUNC_LIKE_FIX_TRUNC
  int i, j;
#endif

  if (HAVE_zero_extendhidi2)
    convert_optab_handler (zext_optab, DImode, HImode)->insn_code = CODE_FOR_zero_extendhidi2;
  if (HAVE_zero_extendqidi2)
    convert_optab_handler (zext_optab, DImode, QImode)->insn_code = CODE_FOR_zero_extendqidi2;
  if (HAVE_extendhidi2)
    convert_optab_handler (sext_optab, DImode, HImode)->insn_code = CODE_FOR_extendhidi2;
  if (HAVE_extendqidi2)
    convert_optab_handler (sext_optab, DImode, QImode)->insn_code = CODE_FOR_extendqidi2;
  convert_optab_handler (sext_optab, SImode, HImode)->insn_code = CODE_FOR_extendhisi2;
  convert_optab_handler (sext_optab, HImode, QImode)->insn_code = CODE_FOR_extendqihi2;
  convert_optab_handler (sext_optab, SImode, QImode)->insn_code = CODE_FOR_extendqisi2;
  if (HAVE_divqi3)
    optab_handler (sdiv_optab, QImode)->insn_code = CODE_FOR_divqi3;
  if (HAVE_udivqi3)
    optab_handler (udiv_optab, QImode)->insn_code = CODE_FOR_udivqi3;
  if (HAVE_divmodhi4)
    optab_handler (sdivmod_optab, HImode)->insn_code = CODE_FOR_divmodhi4;
  if (HAVE_udivmoddi4)
    optab_handler (udivmod_optab, DImode)->insn_code = CODE_FOR_udivmoddi4;
  optab_handler (udivmod_optab, SImode)->insn_code = CODE_FOR_udivmodsi4;
  optab_handler (ctz_optab, SImode)->insn_code = CODE_FOR_ctzsi2;
  if (HAVE_ctzdi2)
    optab_handler (ctz_optab, DImode)->insn_code = CODE_FOR_ctzdi2;
  if (HAVE_popcounthi2)
    optab_handler (popcount_optab, HImode)->insn_code = CODE_FOR_popcounthi2;
  if (HAVE_popcountsi2)
    optab_handler (popcount_optab, SImode)->insn_code = CODE_FOR_popcountsi2;
  if (HAVE_popcountdi2)
    optab_handler (popcount_optab, DImode)->insn_code = CODE_FOR_popcountdi2;
  if (HAVE_bswapdi2)
    optab_handler (bswap_optab, DImode)->insn_code = CODE_FOR_bswapdi2;
  if (HAVE_sqrtxf2)
    optab_handler (sqrt_optab, XFmode)->insn_code = CODE_FOR_sqrtxf2;
  if (HAVE_sincosxf3)
    optab_handler (sincos_optab, XFmode)->insn_code = CODE_FOR_sincosxf3;
  if (HAVE_rintxf2)
    optab_handler (rint_optab, XFmode)->insn_code = CODE_FOR_rintxf2;
  if (HAVE_smaxsf3)
    optab_handler (smax_optab, SFmode)->insn_code = CODE_FOR_smaxsf3;
  if (HAVE_sminsf3)
    optab_handler (smin_optab, SFmode)->insn_code = CODE_FOR_sminsf3;
  if (HAVE_smaxdf3)
    optab_handler (smax_optab, DFmode)->insn_code = CODE_FOR_smaxdf3;
  if (HAVE_smindf3)
    optab_handler (smin_optab, DFmode)->insn_code = CODE_FOR_smindf3;
  if (HAVE_sqrtv4df2)
    optab_handler (sqrt_optab, V4DFmode)->insn_code = CODE_FOR_sqrtv4df2;
  if (HAVE_sqrtv2df2)
    optab_handler (sqrt_optab, V2DFmode)->insn_code = CODE_FOR_sqrtv2df2;
  if (HAVE_mulv16qi3)
    optab_handler (smul_optab, V16QImode)->insn_code = CODE_FOR_mulv16qi3;
  if (HAVE_mulv2di3)
    optab_handler (smul_optab, V2DImode)->insn_code = CODE_FOR_mulv2di3;
  if (HAVE_ashrv8hi3)
    optab_handler (ashr_optab, V8HImode)->insn_code = CODE_FOR_ashrv8hi3;
  if (HAVE_ashrv4si3)
    optab_handler (ashr_optab, V4SImode)->insn_code = CODE_FOR_ashrv4si3;
  if (HAVE_lshrv8hi3)
    optab_handler (lshr_optab, V8HImode)->insn_code = CODE_FOR_lshrv8hi3;
  if (HAVE_lshrv4si3)
    optab_handler (lshr_optab, V4SImode)->insn_code = CODE_FOR_lshrv4si3;
  if (HAVE_lshrv2di3)
    optab_handler (lshr_optab, V2DImode)->insn_code = CODE_FOR_lshrv2di3;
  if (HAVE_ashlv8hi3)
    optab_handler (ashl_optab, V8HImode)->insn_code = CODE_FOR_ashlv8hi3;
  if (HAVE_ashlv4si3)
    optab_handler (ashl_optab, V4SImode)->insn_code = CODE_FOR_ashlv4si3;
  if (HAVE_ashlv2di3)
    optab_handler (ashl_optab, V2DImode)->insn_code = CODE_FOR_ashlv2di3;
  if (HAVE_absv16qi2)
    optab_handler (abs_optab, V16QImode)->insn_code = CODE_FOR_absv16qi2;
  if (HAVE_absv8hi2)
    optab_handler (abs_optab, V8HImode)->insn_code = CODE_FOR_absv8hi2;
  if (HAVE_absv4si2)
    optab_handler (abs_optab, V4SImode)->insn_code = CODE_FOR_absv4si2;
  if (HAVE_absv8qi2)
    optab_handler (abs_optab, V8QImode)->insn_code = CODE_FOR_absv8qi2;
  if (HAVE_absv4hi2)
    optab_handler (abs_optab, V4HImode)->insn_code = CODE_FOR_absv4hi2;
  if (HAVE_absv2si2)
    optab_handler (abs_optab, V2SImode)->insn_code = CODE_FOR_absv2si2;
  if (HAVE_sync_old_addqi)
    sync_old_add_optab[QImode] = CODE_FOR_sync_old_addqi;
  if (HAVE_sync_old_addhi)
    sync_old_add_optab[HImode] = CODE_FOR_sync_old_addhi;
  if (HAVE_sync_old_addsi)
    sync_old_add_optab[SImode] = CODE_FOR_sync_old_addsi;
  if (HAVE_sync_old_adddi)
    sync_old_add_optab[DImode] = CODE_FOR_sync_old_adddi;
  sync_lock_test_and_set[QImode] = CODE_FOR_sync_lock_test_and_setqi;
  sync_lock_test_and_set[HImode] = CODE_FOR_sync_lock_test_and_sethi;
  sync_lock_test_and_set[SImode] = CODE_FOR_sync_lock_test_and_setsi;
  if (HAVE_sync_lock_test_and_setdi)
    sync_lock_test_and_set[DImode] = CODE_FOR_sync_lock_test_and_setdi;
  sync_add_optab[QImode] = CODE_FOR_sync_addqi;
  sync_add_optab[HImode] = CODE_FOR_sync_addhi;
  sync_add_optab[SImode] = CODE_FOR_sync_addsi;
  if (HAVE_sync_adddi)
    sync_add_optab[DImode] = CODE_FOR_sync_adddi;
  sync_sub_optab[QImode] = CODE_FOR_sync_subqi;
  sync_sub_optab[HImode] = CODE_FOR_sync_subhi;
  sync_sub_optab[SImode] = CODE_FOR_sync_subsi;
  if (HAVE_sync_subdi)
    sync_sub_optab[DImode] = CODE_FOR_sync_subdi;
  sync_ior_optab[QImode] = CODE_FOR_sync_iorqi;
  sync_ior_optab[HImode] = CODE_FOR_sync_iorhi;
  sync_ior_optab[SImode] = CODE_FOR_sync_iorsi;
  if (HAVE_sync_iordi)
    sync_ior_optab[DImode] = CODE_FOR_sync_iordi;
  sync_and_optab[QImode] = CODE_FOR_sync_andqi;
  sync_and_optab[HImode] = CODE_FOR_sync_andhi;
  sync_and_optab[SImode] = CODE_FOR_sync_andsi;
  if (HAVE_sync_anddi)
    sync_and_optab[DImode] = CODE_FOR_sync_anddi;
  sync_xor_optab[QImode] = CODE_FOR_sync_xorqi;
  sync_xor_optab[HImode] = CODE_FOR_sync_xorhi;
  sync_xor_optab[SImode] = CODE_FOR_sync_xorsi;
  if (HAVE_sync_xordi)
    sync_xor_optab[DImode] = CODE_FOR_sync_xordi;
  if (HAVE_cmpti)
    optab_handler (cmp_optab, TImode)->insn_code = CODE_FOR_cmpti;
  optab_handler (cmp_optab, DImode)->insn_code = CODE_FOR_cmpdi;
  optab_handler (cmp_optab, SImode)->insn_code = CODE_FOR_cmpsi;
  optab_handler (cmp_optab, HImode)->insn_code = CODE_FOR_cmphi;
  if (HAVE_cmpqi)
    optab_handler (cmp_optab, QImode)->insn_code = CODE_FOR_cmpqi;
  if (HAVE_cmpxf)
    optab_handler (cmp_optab, XFmode)->insn_code = CODE_FOR_cmpxf;
  if (HAVE_cmpsf)
    optab_handler (cmp_optab, SFmode)->insn_code = CODE_FOR_cmpsf;
  if (HAVE_cmpdf)
    optab_handler (cmp_optab, DFmode)->insn_code = CODE_FOR_cmpdf;
  optab_handler (mov_optab, SImode)->insn_code = CODE_FOR_movsi;
  optab_handler (mov_optab, HImode)->insn_code = CODE_FOR_movhi;
  optab_handler (movstrict_optab, HImode)->insn_code = CODE_FOR_movstricthi;
  optab_handler (mov_optab, QImode)->insn_code = CODE_FOR_movqi;
  optab_handler (movstrict_optab, QImode)->insn_code = CODE_FOR_movstrictqi;
  optab_handler (mov_optab, DImode)->insn_code = CODE_FOR_movdi;
  if (HAVE_movoi)
    optab_handler (mov_optab, OImode)->insn_code = CODE_FOR_movoi;
  if (HAVE_movti)
    optab_handler (mov_optab, TImode)->insn_code = CODE_FOR_movti;
  optab_handler (mov_optab, CDImode)->insn_code = CODE_FOR_movcdi;
  optab_handler (mov_optab, SFmode)->insn_code = CODE_FOR_movsf;
  optab_handler (mov_optab, DFmode)->insn_code = CODE_FOR_movdf;
  optab_handler (mov_optab, XFmode)->insn_code = CODE_FOR_movxf;
  if (HAVE_movtf)
    optab_handler (mov_optab, TFmode)->insn_code = CODE_FOR_movtf;
  convert_optab_handler (zext_optab, SImode, HImode)->insn_code = CODE_FOR_zero_extendhisi2;
  convert_optab_handler (zext_optab, HImode, QImode)->insn_code = CODE_FOR_zero_extendqihi2;
  convert_optab_handler (zext_optab, SImode, QImode)->insn_code = CODE_FOR_zero_extendqisi2;
  convert_optab_handler (zext_optab, DImode, SImode)->insn_code = CODE_FOR_zero_extendsidi2;
  convert_optab_handler (sext_optab, DImode, SImode)->insn_code = CODE_FOR_extendsidi2;
  if (HAVE_extendsfdf2)
    convert_optab_handler (sext_optab, DFmode, SFmode)->insn_code = CODE_FOR_extendsfdf2;
  if (HAVE_extendsfxf2)
    convert_optab_handler (sext_optab, XFmode, SFmode)->insn_code = CODE_FOR_extendsfxf2;
  if (HAVE_extenddfxf2)
    convert_optab_handler (sext_optab, XFmode, DFmode)->insn_code = CODE_FOR_extenddfxf2;
  if (HAVE_truncdfsf2)
    convert_optab_handler (trunc_optab, SFmode, DFmode)->insn_code = CODE_FOR_truncdfsf2;
  if (HAVE_truncxfsf2)
    convert_optab_handler (trunc_optab, SFmode, XFmode)->insn_code = CODE_FOR_truncxfsf2;
  if (HAVE_truncxfdf2)
    convert_optab_handler (trunc_optab, DFmode, XFmode)->insn_code = CODE_FOR_truncxfdf2;
  if (HAVE_fix_truncxfdi2)
    convert_optab_handler (sfixtrunc_optab, DImode, XFmode)->insn_code = CODE_FOR_fix_truncxfdi2;
  if (HAVE_fix_truncsfdi2)
    convert_optab_handler (sfixtrunc_optab, DImode, SFmode)->insn_code = CODE_FOR_fix_truncsfdi2;
  if (HAVE_fix_truncdfdi2)
    convert_optab_handler (sfixtrunc_optab, DImode, DFmode)->insn_code = CODE_FOR_fix_truncdfdi2;
  if (HAVE_fix_truncxfsi2)
    convert_optab_handler (sfixtrunc_optab, SImode, XFmode)->insn_code = CODE_FOR_fix_truncxfsi2;
  if (HAVE_fix_truncsfsi2)
    convert_optab_handler (sfixtrunc_optab, SImode, SFmode)->insn_code = CODE_FOR_fix_truncsfsi2;
  if (HAVE_fix_truncdfsi2)
    convert_optab_handler (sfixtrunc_optab, SImode, DFmode)->insn_code = CODE_FOR_fix_truncdfsi2;
  if (HAVE_fix_truncsfhi2)
    convert_optab_handler (sfixtrunc_optab, HImode, SFmode)->insn_code = CODE_FOR_fix_truncsfhi2;
  if (HAVE_fix_truncdfhi2)
    convert_optab_handler (sfixtrunc_optab, HImode, DFmode)->insn_code = CODE_FOR_fix_truncdfhi2;
  if (HAVE_fix_truncxfhi2)
    convert_optab_handler (sfixtrunc_optab, HImode, XFmode)->insn_code = CODE_FOR_fix_truncxfhi2;
  if (HAVE_fixuns_truncsfsi2)
    convert_optab_handler (ufixtrunc_optab, SImode, SFmode)->insn_code = CODE_FOR_fixuns_truncsfsi2;
  if (HAVE_fixuns_truncdfsi2)
    convert_optab_handler (ufixtrunc_optab, SImode, DFmode)->insn_code = CODE_FOR_fixuns_truncdfsi2;
  if (HAVE_fixuns_truncsfhi2)
    convert_optab_handler (ufixtrunc_optab, HImode, SFmode)->insn_code = CODE_FOR_fixuns_truncsfhi2;
  if (HAVE_fixuns_truncdfhi2)
    convert_optab_handler (ufixtrunc_optab, HImode, DFmode)->insn_code = CODE_FOR_fixuns_truncdfhi2;
  if (HAVE_floathisf2)
    convert_optab_handler (sfloat_optab, SFmode, HImode)->insn_code = CODE_FOR_floathisf2;
  if (HAVE_floathidf2)
    convert_optab_handler (sfloat_optab, DFmode, HImode)->insn_code = CODE_FOR_floathidf2;
  if (HAVE_floathixf2)
    convert_optab_handler (sfloat_optab, XFmode, HImode)->insn_code = CODE_FOR_floathixf2;
  if (HAVE_floatsisf2)
    convert_optab_handler (sfloat_optab, SFmode, SImode)->insn_code = CODE_FOR_floatsisf2;
  if (HAVE_floatsidf2)
    convert_optab_handler (sfloat_optab, DFmode, SImode)->insn_code = CODE_FOR_floatsidf2;
  if (HAVE_floatsixf2)
    convert_optab_handler (sfloat_optab, XFmode, SImode)->insn_code = CODE_FOR_floatsixf2;
  if (HAVE_floatdisf2)
    convert_optab_handler (sfloat_optab, SFmode, DImode)->insn_code = CODE_FOR_floatdisf2;
  if (HAVE_floatdidf2)
    convert_optab_handler (sfloat_optab, DFmode, DImode)->insn_code = CODE_FOR_floatdidf2;
  if (HAVE_floatdixf2)
    convert_optab_handler (sfloat_optab, XFmode, DImode)->insn_code = CODE_FOR_floatdixf2;
  if (HAVE_floatunssisf2)
    convert_optab_handler (ufloat_optab, SFmode, SImode)->insn_code = CODE_FOR_floatunssisf2;
  if (HAVE_floatunssidf2)
    convert_optab_handler (ufloat_optab, DFmode, SImode)->insn_code = CODE_FOR_floatunssidf2;
  if (HAVE_floatunssixf2)
    convert_optab_handler (ufloat_optab, XFmode, SImode)->insn_code = CODE_FOR_floatunssixf2;
  if (HAVE_floatunsdisf2)
    convert_optab_handler (ufloat_optab, SFmode, DImode)->insn_code = CODE_FOR_floatunsdisf2;
  if (HAVE_floatunsdidf2)
    convert_optab_handler (ufloat_optab, DFmode, DImode)->insn_code = CODE_FOR_floatunsdidf2;
  if (HAVE_addti3)
    optab_handler (add_optab, TImode)->insn_code = CODE_FOR_addti3;
  optab_handler (add_optab, DImode)->insn_code = CODE_FOR_adddi3;
  optab_handler (add_optab, SImode)->insn_code = CODE_FOR_addsi3;
  if (HAVE_addhi3)
    optab_handler (add_optab, HImode)->insn_code = CODE_FOR_addhi3;
  if (HAVE_addqi3)
    optab_handler (add_optab, QImode)->insn_code = CODE_FOR_addqi3;
  if (HAVE_addxf3)
    optab_handler (addv_optab, XFmode)->insn_code =
    optab_handler (add_optab, XFmode)->insn_code = CODE_FOR_addxf3;
  if (HAVE_addsf3)
    optab_handler (addv_optab, SFmode)->insn_code =
    optab_handler (add_optab, SFmode)->insn_code = CODE_FOR_addsf3;
  if (HAVE_adddf3)
    optab_handler (addv_optab, DFmode)->insn_code =
    optab_handler (add_optab, DFmode)->insn_code = CODE_FOR_adddf3;
  if (HAVE_subti3)
    optab_handler (sub_optab, TImode)->insn_code = CODE_FOR_subti3;
  optab_handler (sub_optab, DImode)->insn_code = CODE_FOR_subdi3;
  optab_handler (sub_optab, SImode)->insn_code = CODE_FOR_subsi3;
  if (HAVE_subhi3)
    optab_handler (sub_optab, HImode)->insn_code = CODE_FOR_subhi3;
  if (HAVE_subqi3)
    optab_handler (sub_optab, QImode)->insn_code = CODE_FOR_subqi3;
  if (HAVE_subxf3)
    optab_handler (subv_optab, XFmode)->insn_code =
    optab_handler (sub_optab, XFmode)->insn_code = CODE_FOR_subxf3;
  if (HAVE_subsf3)
    optab_handler (subv_optab, SFmode)->insn_code =
    optab_handler (sub_optab, SFmode)->insn_code = CODE_FOR_subsf3;
  if (HAVE_subdf3)
    optab_handler (subv_optab, DFmode)->insn_code =
    optab_handler (sub_optab, DFmode)->insn_code = CODE_FOR_subdf3;
  if (HAVE_muldi3)
    optab_handler (smul_optab, DImode)->insn_code = CODE_FOR_muldi3;
  optab_handler (smul_optab, SImode)->insn_code = CODE_FOR_mulsi3;
  if (HAVE_mulhi3)
    optab_handler (smul_optab, HImode)->insn_code = CODE_FOR_mulhi3;
  if (HAVE_mulqi3)
    optab_handler (smul_optab, QImode)->insn_code = CODE_FOR_mulqi3;
  if (HAVE_umulqihi3)
    optab_handler (umul_widen_optab, HImode)->insn_code = CODE_FOR_umulqihi3;
  if (HAVE_mulqihi3)
    optab_handler (smul_widen_optab, HImode)->insn_code = CODE_FOR_mulqihi3;
  if (HAVE_umulditi3)
    optab_handler (umul_widen_optab, TImode)->insn_code = CODE_FOR_umulditi3;
  if (HAVE_umulsidi3)
    optab_handler (umul_widen_optab, DImode)->insn_code = CODE_FOR_umulsidi3;
  if (HAVE_mulditi3)
    optab_handler (smul_widen_optab, TImode)->insn_code = CODE_FOR_mulditi3;
  if (HAVE_mulsidi3)
    optab_handler (smul_widen_optab, DImode)->insn_code = CODE_FOR_mulsidi3;
  if (HAVE_umuldi3_highpart)
    optab_handler (umul_highpart_optab, DImode)->insn_code = CODE_FOR_umuldi3_highpart;
  optab_handler (umul_highpart_optab, SImode)->insn_code = CODE_FOR_umulsi3_highpart;
  if (HAVE_smuldi3_highpart)
    optab_handler (smul_highpart_optab, DImode)->insn_code = CODE_FOR_smuldi3_highpart;
  optab_handler (smul_highpart_optab, SImode)->insn_code = CODE_FOR_smulsi3_highpart;
  if (HAVE_mulxf3)
    optab_handler (smulv_optab, XFmode)->insn_code =
    optab_handler (smul_optab, XFmode)->insn_code = CODE_FOR_mulxf3;
  if (HAVE_mulsf3)
    optab_handler (smulv_optab, SFmode)->insn_code =
    optab_handler (smul_optab, SFmode)->insn_code = CODE_FOR_mulsf3;
  if (HAVE_muldf3)
    optab_handler (smulv_optab, DFmode)->insn_code =
    optab_handler (smul_optab, DFmode)->insn_code = CODE_FOR_muldf3;
  if (HAVE_divxf3)
    optab_handler (sdiv_optab, XFmode)->insn_code = CODE_FOR_divxf3;
  if (HAVE_divdf3)
    optab_handler (sdiv_optab, DFmode)->insn_code = CODE_FOR_divdf3;
  if (HAVE_divsf3)
    optab_handler (sdiv_optab, SFmode)->insn_code = CODE_FOR_divsf3;
  if (HAVE_divmoddi4)
    optab_handler (sdivmod_optab, DImode)->insn_code = CODE_FOR_divmoddi4;
  optab_handler (sdivmod_optab, SImode)->insn_code = CODE_FOR_divmodsi4;
  if (HAVE_udivmodhi4)
    optab_handler (udivmod_optab, HImode)->insn_code = CODE_FOR_udivmodhi4;
  if (HAVE_anddi3)
    optab_handler (and_optab, DImode)->insn_code = CODE_FOR_anddi3;
  optab_handler (and_optab, SImode)->insn_code = CODE_FOR_andsi3;
  if (HAVE_andhi3)
    optab_handler (and_optab, HImode)->insn_code = CODE_FOR_andhi3;
  if (HAVE_andqi3)
    optab_handler (and_optab, QImode)->insn_code = CODE_FOR_andqi3;
  if (HAVE_iordi3)
    optab_handler (ior_optab, DImode)->insn_code = CODE_FOR_iordi3;
  optab_handler (ior_optab, SImode)->insn_code = CODE_FOR_iorsi3;
  if (HAVE_iorhi3)
    optab_handler (ior_optab, HImode)->insn_code = CODE_FOR_iorhi3;
  if (HAVE_iorqi3)
    optab_handler (ior_optab, QImode)->insn_code = CODE_FOR_iorqi3;
  if (HAVE_xordi3)
    optab_handler (xor_optab, DImode)->insn_code = CODE_FOR_xordi3;
  optab_handler (xor_optab, SImode)->insn_code = CODE_FOR_xorsi3;
  if (HAVE_xorhi3)
    optab_handler (xor_optab, HImode)->insn_code = CODE_FOR_xorhi3;
  if (HAVE_xorqi3)
    optab_handler (xor_optab, QImode)->insn_code = CODE_FOR_xorqi3;
  if (HAVE_negti2)
    optab_handler (neg_optab, TImode)->insn_code = CODE_FOR_negti2;
  optab_handler (neg_optab, DImode)->insn_code = CODE_FOR_negdi2;
  optab_handler (neg_optab, SImode)->insn_code = CODE_FOR_negsi2;
  if (HAVE_neghi2)
    optab_handler (neg_optab, HImode)->insn_code = CODE_FOR_neghi2;
  if (HAVE_negqi2)
    optab_handler (neg_optab, QImode)->insn_code = CODE_FOR_negqi2;
  if (HAVE_abssf2)
    optab_handler (absv_optab, SFmode)->insn_code =
    optab_handler (abs_optab, SFmode)->insn_code = CODE_FOR_abssf2;
  if (HAVE_negsf2)
    optab_handler (negv_optab, SFmode)->insn_code =
    optab_handler (neg_optab, SFmode)->insn_code = CODE_FOR_negsf2;
  if (HAVE_absdf2)
    optab_handler (absv_optab, DFmode)->insn_code =
    optab_handler (abs_optab, DFmode)->insn_code = CODE_FOR_absdf2;
  if (HAVE_negdf2)
    optab_handler (negv_optab, DFmode)->insn_code =
    optab_handler (neg_optab, DFmode)->insn_code = CODE_FOR_negdf2;
  if (HAVE_absxf2)
    optab_handler (absv_optab, XFmode)->insn_code =
    optab_handler (abs_optab, XFmode)->insn_code = CODE_FOR_absxf2;
  if (HAVE_negxf2)
    optab_handler (negv_optab, XFmode)->insn_code =
    optab_handler (neg_optab, XFmode)->insn_code = CODE_FOR_negxf2;
  if (HAVE_abstf2)
    optab_handler (absv_optab, TFmode)->insn_code =
    optab_handler (abs_optab, TFmode)->insn_code = CODE_FOR_abstf2;
  if (HAVE_negtf2)
    optab_handler (negv_optab, TFmode)->insn_code =
    optab_handler (neg_optab, TFmode)->insn_code = CODE_FOR_negtf2;
  if (HAVE_copysignsf3)
    optab_handler (copysign_optab, SFmode)->insn_code = CODE_FOR_copysignsf3;
  if (HAVE_copysigndf3)
    optab_handler (copysign_optab, DFmode)->insn_code = CODE_FOR_copysigndf3;
  if (HAVE_copysigntf3)
    optab_handler (copysign_optab, TFmode)->insn_code = CODE_FOR_copysigntf3;
  if (HAVE_one_cmpldi2)
    optab_handler (one_cmpl_optab, DImode)->insn_code = CODE_FOR_one_cmpldi2;
  optab_handler (one_cmpl_optab, SImode)->insn_code = CODE_FOR_one_cmplsi2;
  if (HAVE_one_cmplhi2)
    optab_handler (one_cmpl_optab, HImode)->insn_code = CODE_FOR_one_cmplhi2;
  if (HAVE_one_cmplqi2)
    optab_handler (one_cmpl_optab, QImode)->insn_code = CODE_FOR_one_cmplqi2;
  if (HAVE_ashlti3)
    optab_handler (ashl_optab, TImode)->insn_code = CODE_FOR_ashlti3;
  optab_handler (ashl_optab, DImode)->insn_code = CODE_FOR_ashldi3;
  optab_handler (ashl_optab, SImode)->insn_code = CODE_FOR_ashlsi3;
  if (HAVE_ashlhi3)
    optab_handler (ashl_optab, HImode)->insn_code = CODE_FOR_ashlhi3;
  if (HAVE_ashlqi3)
    optab_handler (ashl_optab, QImode)->insn_code = CODE_FOR_ashlqi3;
  if (HAVE_ashrti3)
    optab_handler (ashr_optab, TImode)->insn_code = CODE_FOR_ashrti3;
  optab_handler (ashr_optab, DImode)->insn_code = CODE_FOR_ashrdi3;
  optab_handler (ashr_optab, SImode)->insn_code = CODE_FOR_ashrsi3;
  if (HAVE_ashrhi3)
    optab_handler (ashr_optab, HImode)->insn_code = CODE_FOR_ashrhi3;
  if (HAVE_ashrqi3)
    optab_handler (ashr_optab, QImode)->insn_code = CODE_FOR_ashrqi3;
  if (HAVE_lshrti3)
    optab_handler (lshr_optab, TImode)->insn_code = CODE_FOR_lshrti3;
  optab_handler (lshr_optab, DImode)->insn_code = CODE_FOR_lshrdi3;
  optab_handler (lshr_optab, SImode)->insn_code = CODE_FOR_lshrsi3;
  if (HAVE_lshrhi3)
    optab_handler (lshr_optab, HImode)->insn_code = CODE_FOR_lshrhi3;
  if (HAVE_lshrqi3)
    optab_handler (lshr_optab, QImode)->insn_code = CODE_FOR_lshrqi3;
  optab_handler (rotl_optab, DImode)->insn_code = CODE_FOR_rotldi3;
  optab_handler (rotl_optab, SImode)->insn_code = CODE_FOR_rotlsi3;
  if (HAVE_rotlhi3)
    optab_handler (rotl_optab, HImode)->insn_code = CODE_FOR_rotlhi3;
  if (HAVE_rotlqi3)
    optab_handler (rotl_optab, QImode)->insn_code = CODE_FOR_rotlqi3;
  optab_handler (rotr_optab, DImode)->insn_code = CODE_FOR_rotrdi3;
  optab_handler (rotr_optab, SImode)->insn_code = CODE_FOR_rotrsi3;
  if (HAVE_rotrhi3)
    optab_handler (rotr_optab, HImode)->insn_code = CODE_FOR_rotrhi3;
  if (HAVE_rotrqi3)
    optab_handler (rotr_optab, QImode)->insn_code = CODE_FOR_rotrqi3;
  setcc_gen_code[NE] = CODE_FOR_sne;
  setcc_gen_code[EQ] = CODE_FOR_seq;
  setcc_gen_code[GE] = CODE_FOR_sge;
  setcc_gen_code[GT] = CODE_FOR_sgt;
  setcc_gen_code[LE] = CODE_FOR_sle;
  setcc_gen_code[LT] = CODE_FOR_slt;
  setcc_gen_code[GEU] = CODE_FOR_sgeu;
  setcc_gen_code[GTU] = CODE_FOR_sgtu;
  setcc_gen_code[LEU] = CODE_FOR_sleu;
  setcc_gen_code[LTU] = CODE_FOR_sltu;
  if (HAVE_sunordered)
    setcc_gen_code[UNORDERED] = CODE_FOR_sunordered;
  if (HAVE_sordered)
    setcc_gen_code[ORDERED] = CODE_FOR_sordered;
  if (HAVE_suneq)
    setcc_gen_code[UNEQ] = CODE_FOR_suneq;
  if (HAVE_sunge)
    setcc_gen_code[UNGE] = CODE_FOR_sunge;
  if (HAVE_sungt)
    setcc_gen_code[UNGT] = CODE_FOR_sungt;
  if (HAVE_sunle)
    setcc_gen_code[UNLE] = CODE_FOR_sunle;
  if (HAVE_sunlt)
    setcc_gen_code[UNLT] = CODE_FOR_sunlt;
  if (HAVE_sltgt)
    setcc_gen_code[LTGT] = CODE_FOR_sltgt;
  bcc_gen_fctn[NE] = gen_bne;
  bcc_gen_fctn[EQ] = gen_beq;
  bcc_gen_fctn[GE] = gen_bge;
  bcc_gen_fctn[GT] = gen_bgt;
  bcc_gen_fctn[LE] = gen_ble;
  bcc_gen_fctn[LT] = gen_blt;
  bcc_gen_fctn[GEU] = gen_bgeu;
  bcc_gen_fctn[GTU] = gen_bgtu;
  bcc_gen_fctn[LEU] = gen_bleu;
  bcc_gen_fctn[LTU] = gen_bltu;
  if (HAVE_bunordered)
    bcc_gen_fctn[UNORDERED] = gen_bunordered;
  if (HAVE_bordered)
    bcc_gen_fctn[ORDERED] = gen_bordered;
  if (HAVE_buneq)
    bcc_gen_fctn[UNEQ] = gen_buneq;
  if (HAVE_bunge)
    bcc_gen_fctn[UNGE] = gen_bunge;
  if (HAVE_bungt)
    bcc_gen_fctn[UNGT] = gen_bungt;
  if (HAVE_bunle)
    bcc_gen_fctn[UNLE] = gen_bunle;
  if (HAVE_bunlt)
    bcc_gen_fctn[UNLT] = gen_bunlt;
  if (HAVE_bltgt)
    bcc_gen_fctn[LTGT] = gen_bltgt;
  optab_handler (ffs_optab, SImode)->insn_code = CODE_FOR_ffssi2;
  if (HAVE_ffsdi2)
    optab_handler (ffs_optab, DImode)->insn_code = CODE_FOR_ffsdi2;
  optab_handler (clz_optab, SImode)->insn_code = CODE_FOR_clzsi2;
  optab_handler (bswap_optab, SImode)->insn_code = CODE_FOR_bswapsi2;
  if (HAVE_clzdi2)
    optab_handler (clz_optab, DImode)->insn_code = CODE_FOR_clzdi2;
  optab_handler (clz_optab, HImode)->insn_code = CODE_FOR_clzhi2;
  if (HAVE_paritydi2)
    optab_handler (parity_optab, DImode)->insn_code = CODE_FOR_paritydi2;
  if (HAVE_paritysi2)
    optab_handler (parity_optab, SImode)->insn_code = CODE_FOR_paritysi2;
  if (HAVE_sqrtsf2)
    optab_handler (sqrt_optab, SFmode)->insn_code = CODE_FOR_sqrtsf2;
  if (HAVE_sqrtdf2)
    optab_handler (sqrt_optab, DFmode)->insn_code = CODE_FOR_sqrtdf2;
  if (HAVE_fmodxf3)
    optab_handler (fmod_optab, XFmode)->insn_code = CODE_FOR_fmodxf3;
  if (HAVE_fmodsf3)
    optab_handler (fmod_optab, SFmode)->insn_code = CODE_FOR_fmodsf3;
  if (HAVE_fmoddf3)
    optab_handler (fmod_optab, DFmode)->insn_code = CODE_FOR_fmoddf3;
  if (HAVE_remainderxf3)
    optab_handler (remainder_optab, XFmode)->insn_code = CODE_FOR_remainderxf3;
  if (HAVE_remaindersf3)
    optab_handler (remainder_optab, SFmode)->insn_code = CODE_FOR_remaindersf3;
  if (HAVE_remainderdf3)
    optab_handler (remainder_optab, DFmode)->insn_code = CODE_FOR_remainderdf3;
  if (HAVE_sincossf3)
    optab_handler (sincos_optab, SFmode)->insn_code = CODE_FOR_sincossf3;
  if (HAVE_sincosdf3)
    optab_handler (sincos_optab, DFmode)->insn_code = CODE_FOR_sincosdf3;
  if (HAVE_tanxf2)
    optab_handler (tan_optab, XFmode)->insn_code = CODE_FOR_tanxf2;
  if (HAVE_tansf2)
    optab_handler (tan_optab, SFmode)->insn_code = CODE_FOR_tansf2;
  if (HAVE_tandf2)
    optab_handler (tan_optab, DFmode)->insn_code = CODE_FOR_tandf2;
  if (HAVE_atan2xf3)
    optab_handler (atan2_optab, XFmode)->insn_code = CODE_FOR_atan2xf3;
  if (HAVE_atan2sf3)
    optab_handler (atan2_optab, SFmode)->insn_code = CODE_FOR_atan2sf3;
  if (HAVE_atan2df3)
    optab_handler (atan2_optab, DFmode)->insn_code = CODE_FOR_atan2df3;
  if (HAVE_atanxf2)
    optab_handler (atan_optab, XFmode)->insn_code = CODE_FOR_atanxf2;
  if (HAVE_atansf2)
    optab_handler (atan_optab, SFmode)->insn_code = CODE_FOR_atansf2;
  if (HAVE_atandf2)
    optab_handler (atan_optab, DFmode)->insn_code = CODE_FOR_atandf2;
  if (HAVE_asinxf2)
    optab_handler (asin_optab, XFmode)->insn_code = CODE_FOR_asinxf2;
  if (HAVE_asinsf2)
    optab_handler (asin_optab, SFmode)->insn_code = CODE_FOR_asinsf2;
  if (HAVE_asindf2)
    optab_handler (asin_optab, DFmode)->insn_code = CODE_FOR_asindf2;
  if (HAVE_acosxf2)
    optab_handler (acos_optab, XFmode)->insn_code = CODE_FOR_acosxf2;
  if (HAVE_acossf2)
    optab_handler (acos_optab, SFmode)->insn_code = CODE_FOR_acossf2;
  if (HAVE_acosdf2)
    optab_handler (acos_optab, DFmode)->insn_code = CODE_FOR_acosdf2;
  if (HAVE_logxf2)
    optab_handler (log_optab, XFmode)->insn_code = CODE_FOR_logxf2;
  if (HAVE_logsf2)
    optab_handler (log_optab, SFmode)->insn_code = CODE_FOR_logsf2;
  if (HAVE_logdf2)
    optab_handler (log_optab, DFmode)->insn_code = CODE_FOR_logdf2;
  if (HAVE_log10xf2)
    optab_handler (log10_optab, XFmode)->insn_code = CODE_FOR_log10xf2;
  if (HAVE_log10sf2)
    optab_handler (log10_optab, SFmode)->insn_code = CODE_FOR_log10sf2;
  if (HAVE_log10df2)
    optab_handler (log10_optab, DFmode)->insn_code = CODE_FOR_log10df2;
  if (HAVE_log2xf2)
    optab_handler (log2_optab, XFmode)->insn_code = CODE_FOR_log2xf2;
  if (HAVE_log2sf2)
    optab_handler (log2_optab, SFmode)->insn_code = CODE_FOR_log2sf2;
  if (HAVE_log2df2)
    optab_handler (log2_optab, DFmode)->insn_code = CODE_FOR_log2df2;
  if (HAVE_log1pxf2)
    optab_handler (log1p_optab, XFmode)->insn_code = CODE_FOR_log1pxf2;
  if (HAVE_log1psf2)
    optab_handler (log1p_optab, SFmode)->insn_code = CODE_FOR_log1psf2;
  if (HAVE_log1pdf2)
    optab_handler (log1p_optab, DFmode)->insn_code = CODE_FOR_log1pdf2;
  if (HAVE_logbxf2)
    optab_handler (logb_optab, XFmode)->insn_code = CODE_FOR_logbxf2;
  if (HAVE_logbsf2)
    optab_handler (logb_optab, SFmode)->insn_code = CODE_FOR_logbsf2;
  if (HAVE_logbdf2)
    optab_handler (logb_optab, DFmode)->insn_code = CODE_FOR_logbdf2;
  if (HAVE_ilogbxf2)
    optab_handler (ilogb_optab, XFmode)->insn_code = CODE_FOR_ilogbxf2;
  if (HAVE_ilogbsf2)
    optab_handler (ilogb_optab, SFmode)->insn_code = CODE_FOR_ilogbsf2;
  if (HAVE_ilogbdf2)
    optab_handler (ilogb_optab, DFmode)->insn_code = CODE_FOR_ilogbdf2;
  if (HAVE_expxf2)
    optab_handler (exp_optab, XFmode)->insn_code = CODE_FOR_expxf2;
  if (HAVE_expsf2)
    optab_handler (exp_optab, SFmode)->insn_code = CODE_FOR_expsf2;
  if (HAVE_expdf2)
    optab_handler (exp_optab, DFmode)->insn_code = CODE_FOR_expdf2;
  if (HAVE_exp10xf2)
    optab_handler (exp10_optab, XFmode)->insn_code = CODE_FOR_exp10xf2;
  if (HAVE_exp10sf2)
    optab_handler (exp10_optab, SFmode)->insn_code = CODE_FOR_exp10sf2;
  if (HAVE_exp10df2)
    optab_handler (exp10_optab, DFmode)->insn_code = CODE_FOR_exp10df2;
  if (HAVE_exp2xf2)
    optab_handler (exp2_optab, XFmode)->insn_code = CODE_FOR_exp2xf2;
  if (HAVE_exp2sf2)
    optab_handler (exp2_optab, SFmode)->insn_code = CODE_FOR_exp2sf2;
  if (HAVE_exp2df2)
    optab_handler (exp2_optab, DFmode)->insn_code = CODE_FOR_exp2df2;
  if (HAVE_expm1xf2)
    optab_handler (expm1_optab, XFmode)->insn_code = CODE_FOR_expm1xf2;
  if (HAVE_expm1sf2)
    optab_handler (expm1_optab, SFmode)->insn_code = CODE_FOR_expm1sf2;
  if (HAVE_expm1df2)
    optab_handler (expm1_optab, DFmode)->insn_code = CODE_FOR_expm1df2;
  if (HAVE_ldexpxf3)
    optab_handler (ldexp_optab, XFmode)->insn_code = CODE_FOR_ldexpxf3;
  if (HAVE_ldexpsf3)
    optab_handler (ldexp_optab, SFmode)->insn_code = CODE_FOR_ldexpsf3;
  if (HAVE_ldexpdf3)
    optab_handler (ldexp_optab, DFmode)->insn_code = CODE_FOR_ldexpdf3;
  if (HAVE_scalbxf3)
    optab_handler (scalb_optab, XFmode)->insn_code = CODE_FOR_scalbxf3;
  if (HAVE_scalbsf3)
    optab_handler (scalb_optab, SFmode)->insn_code = CODE_FOR_scalbsf3;
  if (HAVE_scalbdf3)
    optab_handler (scalb_optab, DFmode)->insn_code = CODE_FOR_scalbdf3;
  if (HAVE_rintsf2)
    optab_handler (rint_optab, SFmode)->insn_code = CODE_FOR_rintsf2;
  if (HAVE_rintdf2)
    optab_handler (rint_optab, DFmode)->insn_code = CODE_FOR_rintdf2;
  if (HAVE_roundsf2)
    optab_handler (round_optab, SFmode)->insn_code = CODE_FOR_roundsf2;
  if (HAVE_rounddf2)
    optab_handler (round_optab, DFmode)->insn_code = CODE_FOR_rounddf2;
  if (HAVE_lrintxfhi2)
    convert_optab_handler (lrint_optab, HImode, XFmode)->insn_code = CODE_FOR_lrintxfhi2;
  if (HAVE_lrintxfsi2)
    convert_optab_handler (lrint_optab, SImode, XFmode)->insn_code = CODE_FOR_lrintxfsi2;
  if (HAVE_lrintxfdi2)
    convert_optab_handler (lrint_optab, DImode, XFmode)->insn_code = CODE_FOR_lrintxfdi2;
  if (HAVE_lrintsfsi2)
    convert_optab_handler (lrint_optab, SImode, SFmode)->insn_code = CODE_FOR_lrintsfsi2;
  if (HAVE_lrintdfsi2)
    convert_optab_handler (lrint_optab, SImode, DFmode)->insn_code = CODE_FOR_lrintdfsi2;
  if (HAVE_lrintsfdi2)
    convert_optab_handler (lrint_optab, DImode, SFmode)->insn_code = CODE_FOR_lrintsfdi2;
  if (HAVE_lrintdfdi2)
    convert_optab_handler (lrint_optab, DImode, DFmode)->insn_code = CODE_FOR_lrintdfdi2;
  if (HAVE_lroundsfsi2)
    convert_optab_handler (lround_optab, SImode, SFmode)->insn_code = CODE_FOR_lroundsfsi2;
  if (HAVE_lrounddfsi2)
    convert_optab_handler (lround_optab, SImode, DFmode)->insn_code = CODE_FOR_lrounddfsi2;
  if (HAVE_lroundsfdi2)
    convert_optab_handler (lround_optab, DImode, SFmode)->insn_code = CODE_FOR_lroundsfdi2;
  if (HAVE_lrounddfdi2)
    convert_optab_handler (lround_optab, DImode, DFmode)->insn_code = CODE_FOR_lrounddfdi2;
  if (HAVE_floorxf2)
    optab_handler (floor_optab, XFmode)->insn_code = CODE_FOR_floorxf2;
  if (HAVE_floorsf2)
    optab_handler (floor_optab, SFmode)->insn_code = CODE_FOR_floorsf2;
  if (HAVE_floordf2)
    optab_handler (floor_optab, DFmode)->insn_code = CODE_FOR_floordf2;
  if (HAVE_lfloorxfhi2)
    convert_optab_handler (lfloor_optab, HImode, XFmode)->insn_code = CODE_FOR_lfloorxfhi2;
  if (HAVE_lfloorxfsi2)
    convert_optab_handler (lfloor_optab, SImode, XFmode)->insn_code = CODE_FOR_lfloorxfsi2;
  if (HAVE_lfloorxfdi2)
    convert_optab_handler (lfloor_optab, DImode, XFmode)->insn_code = CODE_FOR_lfloorxfdi2;
  if (HAVE_lfloorsfdi2)
    convert_optab_handler (lfloor_optab, DImode, SFmode)->insn_code = CODE_FOR_lfloorsfdi2;
  if (HAVE_lfloordfdi2)
    convert_optab_handler (lfloor_optab, DImode, DFmode)->insn_code = CODE_FOR_lfloordfdi2;
  if (HAVE_lfloorsfsi2)
    convert_optab_handler (lfloor_optab, SImode, SFmode)->insn_code = CODE_FOR_lfloorsfsi2;
  if (HAVE_lfloordfsi2)
    convert_optab_handler (lfloor_optab, SImode, DFmode)->insn_code = CODE_FOR_lfloordfsi2;
  if (HAVE_ceilxf2)
    optab_handler (ceil_optab, XFmode)->insn_code = CODE_FOR_ceilxf2;
  if (HAVE_ceilsf2)
    optab_handler (ceil_optab, SFmode)->insn_code = CODE_FOR_ceilsf2;
  if (HAVE_ceildf2)
    optab_handler (ceil_optab, DFmode)->insn_code = CODE_FOR_ceildf2;
  if (HAVE_lceilxfhi2)
    convert_optab_handler (lceil_optab, HImode, XFmode)->insn_code = CODE_FOR_lceilxfhi2;
  if (HAVE_lceilxfsi2)
    convert_optab_handler (lceil_optab, SImode, XFmode)->insn_code = CODE_FOR_lceilxfsi2;
  if (HAVE_lceilxfdi2)
    convert_optab_handler (lceil_optab, DImode, XFmode)->insn_code = CODE_FOR_lceilxfdi2;
  if (HAVE_lceilsfdi2)
    convert_optab_handler (lceil_optab, DImode, SFmode)->insn_code = CODE_FOR_lceilsfdi2;
  if (HAVE_lceildfdi2)
    convert_optab_handler (lceil_optab, DImode, DFmode)->insn_code = CODE_FOR_lceildfdi2;
  if (HAVE_lceilsfsi2)
    convert_optab_handler (lceil_optab, SImode, SFmode)->insn_code = CODE_FOR_lceilsfsi2;
  if (HAVE_lceildfsi2)
    convert_optab_handler (lceil_optab, SImode, DFmode)->insn_code = CODE_FOR_lceildfsi2;
  if (HAVE_btruncxf2)
    optab_handler (btrunc_optab, XFmode)->insn_code = CODE_FOR_btruncxf2;
  if (HAVE_btruncsf2)
    optab_handler (btrunc_optab, SFmode)->insn_code = CODE_FOR_btruncsf2;
  if (HAVE_btruncdf2)
    optab_handler (btrunc_optab, DFmode)->insn_code = CODE_FOR_btruncdf2;
  if (HAVE_nearbyintxf2)
    optab_handler (nearbyint_optab, XFmode)->insn_code = CODE_FOR_nearbyintxf2;
  if (HAVE_nearbyintsf2)
    optab_handler (nearbyint_optab, SFmode)->insn_code = CODE_FOR_nearbyintsf2;
  if (HAVE_nearbyintdf2)
    optab_handler (nearbyint_optab, DFmode)->insn_code = CODE_FOR_nearbyintdf2;
  if (HAVE_isinfxf2)
    optab_handler (isinf_optab, XFmode)->insn_code = CODE_FOR_isinfxf2;
  if (HAVE_isinfsf2)
    optab_handler (isinf_optab, SFmode)->insn_code = CODE_FOR_isinfsf2;
  if (HAVE_isinfdf2)
    optab_handler (isinf_optab, DFmode)->insn_code = CODE_FOR_isinfdf2;
  if (HAVE_signbitsf2)
    optab_handler (signbit_optab, SFmode)->insn_code = CODE_FOR_signbitsf2;
  if (HAVE_signbitdf2)
    optab_handler (signbit_optab, DFmode)->insn_code = CODE_FOR_signbitdf2;
  if (HAVE_signbitxf2)
    optab_handler (signbit_optab, XFmode)->insn_code = CODE_FOR_signbitxf2;
  movmem_optab[SImode] = CODE_FOR_movmemsi;
  if (HAVE_movmemdi)
    movmem_optab[DImode] = CODE_FOR_movmemdi;
  setmem_optab[SImode] = CODE_FOR_setmemsi;
  if (HAVE_setmemdi)
    setmem_optab[DImode] = CODE_FOR_setmemdi;
  cmpstrn_optab[SImode] = CODE_FOR_cmpstrnsi;
  optab_handler (strlen_optab, SImode)->insn_code = CODE_FOR_strlensi;
  optab_handler (strlen_optab, DImode)->insn_code = CODE_FOR_strlendi;
  if (HAVE_movdicc)
    movcc_gen_code[DImode] = CODE_FOR_movdicc;
  movcc_gen_code[SImode] = CODE_FOR_movsicc;
  if (HAVE_movhicc)
    movcc_gen_code[HImode] = CODE_FOR_movhicc;
  if (HAVE_movqicc)
    movcc_gen_code[QImode] = CODE_FOR_movqicc;
  if (HAVE_movsfcc)
    movcc_gen_code[SFmode] = CODE_FOR_movsfcc;
  if (HAVE_movdfcc)
    movcc_gen_code[DFmode] = CODE_FOR_movdfcc;
  if (HAVE_movxfcc)
    movcc_gen_code[XFmode] = CODE_FOR_movxfcc;
  optab_handler (addcc_optab, QImode)->insn_code = CODE_FOR_addqicc;
  optab_handler (addcc_optab, HImode)->insn_code = CODE_FOR_addhicc;
  optab_handler (addcc_optab, SImode)->insn_code = CODE_FOR_addsicc;
  if (HAVE_adddicc)
    optab_handler (addcc_optab, DImode)->insn_code = CODE_FOR_adddicc;
  if (HAVE_movv8qi)
    optab_handler (mov_optab, V8QImode)->insn_code = CODE_FOR_movv8qi;
  if (HAVE_movv4hi)
    optab_handler (mov_optab, V4HImode)->insn_code = CODE_FOR_movv4hi;
  if (HAVE_movv2si)
    optab_handler (mov_optab, V2SImode)->insn_code = CODE_FOR_movv2si;
  if (HAVE_movv1di)
    optab_handler (mov_optab, V1DImode)->insn_code = CODE_FOR_movv1di;
  if (HAVE_movv2sf)
    optab_handler (mov_optab, V2SFmode)->insn_code = CODE_FOR_movv2sf;
  if (HAVE_pushv8qi1)
    optab_handler (push_optab, V8QImode)->insn_code = CODE_FOR_pushv8qi1;
  if (HAVE_pushv4hi1)
    optab_handler (push_optab, V4HImode)->insn_code = CODE_FOR_pushv4hi1;
  if (HAVE_pushv2si1)
    optab_handler (push_optab, V2SImode)->insn_code = CODE_FOR_pushv2si1;
  if (HAVE_pushv1di1)
    optab_handler (push_optab, V1DImode)->insn_code = CODE_FOR_pushv1di1;
  if (HAVE_pushv2sf1)
    optab_handler (push_optab, V2SFmode)->insn_code = CODE_FOR_pushv2sf1;
  if (HAVE_movmisalignv8qi)
    optab_handler (movmisalign_optab, V8QImode)->insn_code = CODE_FOR_movmisalignv8qi;
  if (HAVE_movmisalignv4hi)
    optab_handler (movmisalign_optab, V4HImode)->insn_code = CODE_FOR_movmisalignv4hi;
  if (HAVE_movmisalignv2si)
    optab_handler (movmisalign_optab, V2SImode)->insn_code = CODE_FOR_movmisalignv2si;
  if (HAVE_movmisalignv1di)
    optab_handler (movmisalign_optab, V1DImode)->insn_code = CODE_FOR_movmisalignv1di;
  if (HAVE_movmisalignv2sf)
    optab_handler (movmisalign_optab, V2SFmode)->insn_code = CODE_FOR_movmisalignv2sf;
  if (HAVE_vec_setv2sf)
    optab_handler (vec_set_optab, V2SFmode)->insn_code = CODE_FOR_vec_setv2sf;
  if (HAVE_vec_extractv2sf)
    optab_handler (vec_extract_optab, V2SFmode)->insn_code = CODE_FOR_vec_extractv2sf;
  if (HAVE_vec_initv2sf)
    optab_handler (vec_init_optab, V2SFmode)->insn_code = CODE_FOR_vec_initv2sf;
  if (HAVE_vec_setv2si)
    optab_handler (vec_set_optab, V2SImode)->insn_code = CODE_FOR_vec_setv2si;
  if (HAVE_vec_extractv2si)
    optab_handler (vec_extract_optab, V2SImode)->insn_code = CODE_FOR_vec_extractv2si;
  if (HAVE_vec_initv2si)
    optab_handler (vec_init_optab, V2SImode)->insn_code = CODE_FOR_vec_initv2si;
  if (HAVE_vec_setv4hi)
    optab_handler (vec_set_optab, V4HImode)->insn_code = CODE_FOR_vec_setv4hi;
  if (HAVE_vec_extractv4hi)
    optab_handler (vec_extract_optab, V4HImode)->insn_code = CODE_FOR_vec_extractv4hi;
  if (HAVE_vec_initv4hi)
    optab_handler (vec_init_optab, V4HImode)->insn_code = CODE_FOR_vec_initv4hi;
  if (HAVE_vec_setv8qi)
    optab_handler (vec_set_optab, V8QImode)->insn_code = CODE_FOR_vec_setv8qi;
  if (HAVE_vec_extractv8qi)
    optab_handler (vec_extract_optab, V8QImode)->insn_code = CODE_FOR_vec_extractv8qi;
  if (HAVE_vec_initv8qi)
    optab_handler (vec_init_optab, V8QImode)->insn_code = CODE_FOR_vec_initv8qi;
  if (HAVE_movv32qi)
    optab_handler (mov_optab, V32QImode)->insn_code = CODE_FOR_movv32qi;
  if (HAVE_movv16hi)
    optab_handler (mov_optab, V16HImode)->insn_code = CODE_FOR_movv16hi;
  if (HAVE_movv8si)
    optab_handler (mov_optab, V8SImode)->insn_code = CODE_FOR_movv8si;
  if (HAVE_movv4di)
    optab_handler (mov_optab, V4DImode)->insn_code = CODE_FOR_movv4di;
  if (HAVE_movv8sf)
    optab_handler (mov_optab, V8SFmode)->insn_code = CODE_FOR_movv8sf;
  if (HAVE_movv4df)
    optab_handler (mov_optab, V4DFmode)->insn_code = CODE_FOR_movv4df;
  if (HAVE_movv16qi)
    optab_handler (mov_optab, V16QImode)->insn_code = CODE_FOR_movv16qi;
  if (HAVE_movv8hi)
    optab_handler (mov_optab, V8HImode)->insn_code = CODE_FOR_movv8hi;
  if (HAVE_movv4si)
    optab_handler (mov_optab, V4SImode)->insn_code = CODE_FOR_movv4si;
  if (HAVE_movv2di)
    optab_handler (mov_optab, V2DImode)->insn_code = CODE_FOR_movv2di;
  if (HAVE_movv4sf)
    optab_handler (mov_optab, V4SFmode)->insn_code = CODE_FOR_movv4sf;
  if (HAVE_movv2df)
    optab_handler (mov_optab, V2DFmode)->insn_code = CODE_FOR_movv2df;
  if (HAVE_pushv32qi1)
    optab_handler (push_optab, V32QImode)->insn_code = CODE_FOR_pushv32qi1;
  if (HAVE_pushv16hi1)
    optab_handler (push_optab, V16HImode)->insn_code = CODE_FOR_pushv16hi1;
  if (HAVE_pushv8si1)
    optab_handler (push_optab, V8SImode)->insn_code = CODE_FOR_pushv8si1;
  if (HAVE_pushv4di1)
    optab_handler (push_optab, V4DImode)->insn_code = CODE_FOR_pushv4di1;
  if (HAVE_pushv8sf1)
    optab_handler (push_optab, V8SFmode)->insn_code = CODE_FOR_pushv8sf1;
  if (HAVE_pushv4df1)
    optab_handler (push_optab, V4DFmode)->insn_code = CODE_FOR_pushv4df1;
  if (HAVE_pushv16qi1)
    optab_handler (push_optab, V16QImode)->insn_code = CODE_FOR_pushv16qi1;
  if (HAVE_pushv8hi1)
    optab_handler (push_optab, V8HImode)->insn_code = CODE_FOR_pushv8hi1;
  if (HAVE_pushv4si1)
    optab_handler (push_optab, V4SImode)->insn_code = CODE_FOR_pushv4si1;
  if (HAVE_pushv2di1)
    optab_handler (push_optab, V2DImode)->insn_code = CODE_FOR_pushv2di1;
  if (HAVE_pushv4sf1)
    optab_handler (push_optab, V4SFmode)->insn_code = CODE_FOR_pushv4sf1;
  if (HAVE_pushv2df1)
    optab_handler (push_optab, V2DFmode)->insn_code = CODE_FOR_pushv2df1;
  if (HAVE_movmisalignv32qi)
    optab_handler (movmisalign_optab, V32QImode)->insn_code = CODE_FOR_movmisalignv32qi;
  if (HAVE_movmisalignv16hi)
    optab_handler (movmisalign_optab, V16HImode)->insn_code = CODE_FOR_movmisalignv16hi;
  if (HAVE_movmisalignv8si)
    optab_handler (movmisalign_optab, V8SImode)->insn_code = CODE_FOR_movmisalignv8si;
  if (HAVE_movmisalignv4di)
    optab_handler (movmisalign_optab, V4DImode)->insn_code = CODE_FOR_movmisalignv4di;
  if (HAVE_movmisalignv8sf)
    optab_handler (movmisalign_optab, V8SFmode)->insn_code = CODE_FOR_movmisalignv8sf;
  if (HAVE_movmisalignv4df)
    optab_handler (movmisalign_optab, V4DFmode)->insn_code = CODE_FOR_movmisalignv4df;
  if (HAVE_movmisalignv16qi)
    optab_handler (movmisalign_optab, V16QImode)->insn_code = CODE_FOR_movmisalignv16qi;
  if (HAVE_movmisalignv8hi)
    optab_handler (movmisalign_optab, V8HImode)->insn_code = CODE_FOR_movmisalignv8hi;
  if (HAVE_movmisalignv4si)
    optab_handler (movmisalign_optab, V4SImode)->insn_code = CODE_FOR_movmisalignv4si;
  if (HAVE_movmisalignv2di)
    optab_handler (movmisalign_optab, V2DImode)->insn_code = CODE_FOR_movmisalignv2di;
  if (HAVE_movmisalignv4sf)
    optab_handler (movmisalign_optab, V4SFmode)->insn_code = CODE_FOR_movmisalignv4sf;
  if (HAVE_movmisalignv2df)
    optab_handler (movmisalign_optab, V2DFmode)->insn_code = CODE_FOR_movmisalignv2df;
  if (HAVE_storentv4sf)
    optab_handler (storent_optab, V4SFmode)->insn_code = CODE_FOR_storentv4sf;
  if (HAVE_storentv2df)
    optab_handler (storent_optab, V2DFmode)->insn_code = CODE_FOR_storentv2df;
  if (HAVE_storentsf)
    optab_handler (storent_optab, SFmode)->insn_code = CODE_FOR_storentsf;
  if (HAVE_storentdf)
    optab_handler (storent_optab, DFmode)->insn_code = CODE_FOR_storentdf;
  if (HAVE_storentv2di)
    optab_handler (storent_optab, V2DImode)->insn_code = CODE_FOR_storentv2di;
  if (HAVE_storentsi)
    optab_handler (storent_optab, SImode)->insn_code = CODE_FOR_storentsi;
  if (HAVE_absv4sf2)
    optab_handler (absv_optab, V4SFmode)->insn_code =
    optab_handler (abs_optab, V4SFmode)->insn_code = CODE_FOR_absv4sf2;
  if (HAVE_negv4sf2)
    optab_handler (negv_optab, V4SFmode)->insn_code =
    optab_handler (neg_optab, V4SFmode)->insn_code = CODE_FOR_negv4sf2;
  if (HAVE_absv2df2)
    optab_handler (absv_optab, V2DFmode)->insn_code =
    optab_handler (abs_optab, V2DFmode)->insn_code = CODE_FOR_absv2df2;
  if (HAVE_negv2df2)
    optab_handler (negv_optab, V2DFmode)->insn_code =
    optab_handler (neg_optab, V2DFmode)->insn_code = CODE_FOR_negv2df2;
  if (HAVE_addv8sf3)
    optab_handler (addv_optab, V8SFmode)->insn_code =
    optab_handler (add_optab, V8SFmode)->insn_code = CODE_FOR_addv8sf3;
  if (HAVE_subv8sf3)
    optab_handler (subv_optab, V8SFmode)->insn_code =
    optab_handler (sub_optab, V8SFmode)->insn_code = CODE_FOR_subv8sf3;
  if (HAVE_addv4df3)
    optab_handler (addv_optab, V4DFmode)->insn_code =
    optab_handler (add_optab, V4DFmode)->insn_code = CODE_FOR_addv4df3;
  if (HAVE_subv4df3)
    optab_handler (subv_optab, V4DFmode)->insn_code =
    optab_handler (sub_optab, V4DFmode)->insn_code = CODE_FOR_subv4df3;
  if (HAVE_addv4sf3)
    optab_handler (addv_optab, V4SFmode)->insn_code =
    optab_handler (add_optab, V4SFmode)->insn_code = CODE_FOR_addv4sf3;
  if (HAVE_subv4sf3)
    optab_handler (subv_optab, V4SFmode)->insn_code =
    optab_handler (sub_optab, V4SFmode)->insn_code = CODE_FOR_subv4sf3;
  if (HAVE_addv2df3)
    optab_handler (addv_optab, V2DFmode)->insn_code =
    optab_handler (add_optab, V2DFmode)->insn_code = CODE_FOR_addv2df3;
  if (HAVE_subv2df3)
    optab_handler (subv_optab, V2DFmode)->insn_code =
    optab_handler (sub_optab, V2DFmode)->insn_code = CODE_FOR_subv2df3;
  if (HAVE_mulv8sf3)
    optab_handler (smulv_optab, V8SFmode)->insn_code =
    optab_handler (smul_optab, V8SFmode)->insn_code = CODE_FOR_mulv8sf3;
  if (HAVE_mulv4df3)
    optab_handler (smulv_optab, V4DFmode)->insn_code =
    optab_handler (smul_optab, V4DFmode)->insn_code = CODE_FOR_mulv4df3;
  if (HAVE_mulv4sf3)
    optab_handler (smulv_optab, V4SFmode)->insn_code =
    optab_handler (smul_optab, V4SFmode)->insn_code = CODE_FOR_mulv4sf3;
  if (HAVE_mulv2df3)
    optab_handler (smulv_optab, V2DFmode)->insn_code =
    optab_handler (smul_optab, V2DFmode)->insn_code = CODE_FOR_mulv2df3;
  if (HAVE_divv8sf3)
    optab_handler (sdiv_optab, V8SFmode)->insn_code = CODE_FOR_divv8sf3;
  if (HAVE_divv4df3)
    optab_handler (sdiv_optab, V4DFmode)->insn_code = CODE_FOR_divv4df3;
  if (HAVE_divv4sf3)
    optab_handler (sdiv_optab, V4SFmode)->insn_code = CODE_FOR_divv4sf3;
  if (HAVE_divv2df3)
    optab_handler (sdiv_optab, V2DFmode)->insn_code = CODE_FOR_divv2df3;
  if (HAVE_sqrtv8sf2)
    optab_handler (sqrt_optab, V8SFmode)->insn_code = CODE_FOR_sqrtv8sf2;
  if (HAVE_sqrtv4sf2)
    optab_handler (sqrt_optab, V4SFmode)->insn_code = CODE_FOR_sqrtv4sf2;
  if (HAVE_smaxv8sf3)
    optab_handler (smax_optab, V8SFmode)->insn_code = CODE_FOR_smaxv8sf3;
  if (HAVE_sminv8sf3)
    optab_handler (smin_optab, V8SFmode)->insn_code = CODE_FOR_sminv8sf3;
  if (HAVE_smaxv4df3)
    optab_handler (smax_optab, V4DFmode)->insn_code = CODE_FOR_smaxv4df3;
  if (HAVE_sminv4df3)
    optab_handler (smin_optab, V4DFmode)->insn_code = CODE_FOR_sminv4df3;
  if (HAVE_smaxv4sf3)
    optab_handler (smax_optab, V4SFmode)->insn_code = CODE_FOR_smaxv4sf3;
  if (HAVE_sminv4sf3)
    optab_handler (smin_optab, V4SFmode)->insn_code = CODE_FOR_sminv4sf3;
  if (HAVE_smaxv2df3)
    optab_handler (smax_optab, V2DFmode)->insn_code = CODE_FOR_smaxv2df3;
  if (HAVE_sminv2df3)
    optab_handler (smin_optab, V2DFmode)->insn_code = CODE_FOR_sminv2df3;
  if (HAVE_reduc_splus_v4sf)
    optab_handler (reduc_splus_optab, V4SFmode)->insn_code = CODE_FOR_reduc_splus_v4sf;
  if (HAVE_reduc_splus_v2df)
    optab_handler (reduc_splus_optab, V2DFmode)->insn_code = CODE_FOR_reduc_splus_v2df;
  if (HAVE_reduc_smax_v4sf)
    optab_handler (reduc_smax_optab, V4SFmode)->insn_code = CODE_FOR_reduc_smax_v4sf;
  if (HAVE_reduc_smin_v4sf)
    optab_handler (reduc_smin_optab, V4SFmode)->insn_code = CODE_FOR_reduc_smin_v4sf;
  if (HAVE_vcondv4sf)
    vcond_gen_code[V4SFmode] = CODE_FOR_vcondv4sf;
  if (HAVE_vcondv2df)
    vcond_gen_code[V2DFmode] = CODE_FOR_vcondv2df;
  if (HAVE_andv8sf3)
    optab_handler (and_optab, V8SFmode)->insn_code = CODE_FOR_andv8sf3;
  if (HAVE_iorv8sf3)
    optab_handler (ior_optab, V8SFmode)->insn_code = CODE_FOR_iorv8sf3;
  if (HAVE_xorv8sf3)
    optab_handler (xor_optab, V8SFmode)->insn_code = CODE_FOR_xorv8sf3;
  if (HAVE_andv4df3)
    optab_handler (and_optab, V4DFmode)->insn_code = CODE_FOR_andv4df3;
  if (HAVE_iorv4df3)
    optab_handler (ior_optab, V4DFmode)->insn_code = CODE_FOR_iorv4df3;
  if (HAVE_xorv4df3)
    optab_handler (xor_optab, V4DFmode)->insn_code = CODE_FOR_xorv4df3;
  if (HAVE_andv4sf3)
    optab_handler (and_optab, V4SFmode)->insn_code = CODE_FOR_andv4sf3;
  if (HAVE_iorv4sf3)
    optab_handler (ior_optab, V4SFmode)->insn_code = CODE_FOR_iorv4sf3;
  if (HAVE_xorv4sf3)
    optab_handler (xor_optab, V4SFmode)->insn_code = CODE_FOR_xorv4sf3;
  if (HAVE_andv2df3)
    optab_handler (and_optab, V2DFmode)->insn_code = CODE_FOR_andv2df3;
  if (HAVE_iorv2df3)
    optab_handler (ior_optab, V2DFmode)->insn_code = CODE_FOR_iorv2df3;
  if (HAVE_xorv2df3)
    optab_handler (xor_optab, V2DFmode)->insn_code = CODE_FOR_xorv2df3;
  if (HAVE_vec_unpacks_hi_v4sf)
    optab_handler (vec_unpacks_hi_optab, V4SFmode)->insn_code = CODE_FOR_vec_unpacks_hi_v4sf;
  if (HAVE_vec_unpacks_lo_v4sf)
    optab_handler (vec_unpacks_lo_optab, V4SFmode)->insn_code = CODE_FOR_vec_unpacks_lo_v4sf;
  if (HAVE_vec_unpacks_float_hi_v8hi)
    optab_handler (vec_unpacks_float_hi_optab, V8HImode)->insn_code = CODE_FOR_vec_unpacks_float_hi_v8hi;
  if (HAVE_vec_unpacks_float_lo_v8hi)
    optab_handler (vec_unpacks_float_lo_optab, V8HImode)->insn_code = CODE_FOR_vec_unpacks_float_lo_v8hi;
  if (HAVE_vec_unpacku_float_hi_v8hi)
    optab_handler (vec_unpacku_float_hi_optab, V8HImode)->insn_code = CODE_FOR_vec_unpacku_float_hi_v8hi;
  if (HAVE_vec_unpacku_float_lo_v8hi)
    optab_handler (vec_unpacku_float_lo_optab, V8HImode)->insn_code = CODE_FOR_vec_unpacku_float_lo_v8hi;
  if (HAVE_vec_unpacks_float_hi_v4si)
    optab_handler (vec_unpacks_float_hi_optab, V4SImode)->insn_code = CODE_FOR_vec_unpacks_float_hi_v4si;
  if (HAVE_vec_unpacks_float_lo_v4si)
    optab_handler (vec_unpacks_float_lo_optab, V4SImode)->insn_code = CODE_FOR_vec_unpacks_float_lo_v4si;
  if (HAVE_vec_pack_trunc_v2df)
    optab_handler (vec_pack_trunc_optab, V2DFmode)->insn_code = CODE_FOR_vec_pack_trunc_v2df;
  if (HAVE_vec_pack_sfix_trunc_v2df)
    optab_handler (vec_pack_sfix_trunc_optab, V2DFmode)->insn_code = CODE_FOR_vec_pack_sfix_trunc_v2df;
  if (HAVE_vec_initv16qi)
    optab_handler (vec_init_optab, V16QImode)->insn_code = CODE_FOR_vec_initv16qi;
  if (HAVE_vec_initv8hi)
    optab_handler (vec_init_optab, V8HImode)->insn_code = CODE_FOR_vec_initv8hi;
  if (HAVE_vec_initv4si)
    optab_handler (vec_init_optab, V4SImode)->insn_code = CODE_FOR_vec_initv4si;
  if (HAVE_vec_initv2di)
    optab_handler (vec_init_optab, V2DImode)->insn_code = CODE_FOR_vec_initv2di;
  if (HAVE_vec_initv4sf)
    optab_handler (vec_init_optab, V4SFmode)->insn_code = CODE_FOR_vec_initv4sf;
  if (HAVE_vec_initv2df)
    optab_handler (vec_init_optab, V2DFmode)->insn_code = CODE_FOR_vec_initv2df;
  if (HAVE_vec_setv16qi)
    optab_handler (vec_set_optab, V16QImode)->insn_code = CODE_FOR_vec_setv16qi;
  if (HAVE_vec_setv8hi)
    optab_handler (vec_set_optab, V8HImode)->insn_code = CODE_FOR_vec_setv8hi;
  if (HAVE_vec_setv4si)
    optab_handler (vec_set_optab, V4SImode)->insn_code = CODE_FOR_vec_setv4si;
  if (HAVE_vec_setv2di)
    optab_handler (vec_set_optab, V2DImode)->insn_code = CODE_FOR_vec_setv2di;
  if (HAVE_vec_setv4sf)
    optab_handler (vec_set_optab, V4SFmode)->insn_code = CODE_FOR_vec_setv4sf;
  if (HAVE_vec_setv2df)
    optab_handler (vec_set_optab, V2DFmode)->insn_code = CODE_FOR_vec_setv2df;
  if (HAVE_vec_extractv16qi)
    optab_handler (vec_extract_optab, V16QImode)->insn_code = CODE_FOR_vec_extractv16qi;
  if (HAVE_vec_extractv8hi)
    optab_handler (vec_extract_optab, V8HImode)->insn_code = CODE_FOR_vec_extractv8hi;
  if (HAVE_vec_extractv4si)
    optab_handler (vec_extract_optab, V4SImode)->insn_code = CODE_FOR_vec_extractv4si;
  if (HAVE_vec_extractv2di)
    optab_handler (vec_extract_optab, V2DImode)->insn_code = CODE_FOR_vec_extractv2di;
  if (HAVE_vec_extractv4sf)
    optab_handler (vec_extract_optab, V4SFmode)->insn_code = CODE_FOR_vec_extractv4sf;
  if (HAVE_vec_extractv2df)
    optab_handler (vec_extract_optab, V2DFmode)->insn_code = CODE_FOR_vec_extractv2df;
  if (HAVE_vec_extract_evenv4sf)
    optab_handler (vec_extract_even_optab, V4SFmode)->insn_code = CODE_FOR_vec_extract_evenv4sf;
  if (HAVE_vec_extract_evenv4si)
    optab_handler (vec_extract_even_optab, V4SImode)->insn_code = CODE_FOR_vec_extract_evenv4si;
  if (HAVE_vec_extract_oddv4sf)
    optab_handler (vec_extract_odd_optab, V4SFmode)->insn_code = CODE_FOR_vec_extract_oddv4sf;
  if (HAVE_vec_extract_oddv4si)
    optab_handler (vec_extract_odd_optab, V4SImode)->insn_code = CODE_FOR_vec_extract_oddv4si;
  if (HAVE_vec_extract_evenv2df)
    optab_handler (vec_extract_even_optab, V2DFmode)->insn_code = CODE_FOR_vec_extract_evenv2df;
  if (HAVE_vec_extract_evenv2di)
    optab_handler (vec_extract_even_optab, V2DImode)->insn_code = CODE_FOR_vec_extract_evenv2di;
  if (HAVE_vec_extract_oddv2df)
    optab_handler (vec_extract_odd_optab, V2DFmode)->insn_code = CODE_FOR_vec_extract_oddv2df;
  if (HAVE_vec_extract_oddv2di)
    optab_handler (vec_extract_odd_optab, V2DImode)->insn_code = CODE_FOR_vec_extract_oddv2di;
  if (HAVE_negv16qi2)
    optab_handler (neg_optab, V16QImode)->insn_code = CODE_FOR_negv16qi2;
  if (HAVE_negv8hi2)
    optab_handler (neg_optab, V8HImode)->insn_code = CODE_FOR_negv8hi2;
  if (HAVE_negv4si2)
    optab_handler (neg_optab, V4SImode)->insn_code = CODE_FOR_negv4si2;
  if (HAVE_negv2di2)
    optab_handler (neg_optab, V2DImode)->insn_code = CODE_FOR_negv2di2;
  if (HAVE_addv16qi3)
    optab_handler (add_optab, V16QImode)->insn_code = CODE_FOR_addv16qi3;
  if (HAVE_subv16qi3)
    optab_handler (sub_optab, V16QImode)->insn_code = CODE_FOR_subv16qi3;
  if (HAVE_addv8hi3)
    optab_handler (add_optab, V8HImode)->insn_code = CODE_FOR_addv8hi3;
  if (HAVE_subv8hi3)
    optab_handler (sub_optab, V8HImode)->insn_code = CODE_FOR_subv8hi3;
  if (HAVE_addv4si3)
    optab_handler (add_optab, V4SImode)->insn_code = CODE_FOR_addv4si3;
  if (HAVE_subv4si3)
    optab_handler (sub_optab, V4SImode)->insn_code = CODE_FOR_subv4si3;
  if (HAVE_addv2di3)
    optab_handler (add_optab, V2DImode)->insn_code = CODE_FOR_addv2di3;
  if (HAVE_subv2di3)
    optab_handler (sub_optab, V2DImode)->insn_code = CODE_FOR_subv2di3;
  if (HAVE_mulv8hi3)
    optab_handler (smul_optab, V8HImode)->insn_code = CODE_FOR_mulv8hi3;
  if (HAVE_smulv8hi3_highpart)
    optab_handler (smul_highpart_optab, V8HImode)->insn_code = CODE_FOR_smulv8hi3_highpart;
  if (HAVE_umulv8hi3_highpart)
    optab_handler (umul_highpart_optab, V8HImode)->insn_code = CODE_FOR_umulv8hi3_highpart;
  if (HAVE_mulv4si3)
    optab_handler (smul_optab, V4SImode)->insn_code = CODE_FOR_mulv4si3;
  if (HAVE_vec_widen_smult_hi_v8hi)
    optab_handler (vec_widen_smult_hi_optab, V8HImode)->insn_code = CODE_FOR_vec_widen_smult_hi_v8hi;
  if (HAVE_vec_widen_smult_lo_v8hi)
    optab_handler (vec_widen_smult_lo_optab, V8HImode)->insn_code = CODE_FOR_vec_widen_smult_lo_v8hi;
  if (HAVE_vec_widen_umult_hi_v8hi)
    optab_handler (vec_widen_umult_hi_optab, V8HImode)->insn_code = CODE_FOR_vec_widen_umult_hi_v8hi;
  if (HAVE_vec_widen_umult_lo_v8hi)
    optab_handler (vec_widen_umult_lo_optab, V8HImode)->insn_code = CODE_FOR_vec_widen_umult_lo_v8hi;
  if (HAVE_vec_widen_smult_hi_v4si)
    optab_handler (vec_widen_smult_hi_optab, V4SImode)->insn_code = CODE_FOR_vec_widen_smult_hi_v4si;
  if (HAVE_vec_widen_smult_lo_v4si)
    optab_handler (vec_widen_smult_lo_optab, V4SImode)->insn_code = CODE_FOR_vec_widen_smult_lo_v4si;
  if (HAVE_vec_widen_umult_hi_v4si)
    optab_handler (vec_widen_umult_hi_optab, V4SImode)->insn_code = CODE_FOR_vec_widen_umult_hi_v4si;
  if (HAVE_vec_widen_umult_lo_v4si)
    optab_handler (vec_widen_umult_lo_optab, V4SImode)->insn_code = CODE_FOR_vec_widen_umult_lo_v4si;
  if (HAVE_sdot_prodv8hi)
    optab_handler (sdot_prod_optab, V8HImode)->insn_code = CODE_FOR_sdot_prodv8hi;
  if (HAVE_udot_prodv4si)
    optab_handler (udot_prod_optab, V4SImode)->insn_code = CODE_FOR_udot_prodv4si;
  if (HAVE_vec_shl_v16qi)
    optab_handler (vec_shl_optab, V16QImode)->insn_code = CODE_FOR_vec_shl_v16qi;
  if (HAVE_vec_shl_v8hi)
    optab_handler (vec_shl_optab, V8HImode)->insn_code = CODE_FOR_vec_shl_v8hi;
  if (HAVE_vec_shl_v4si)
    optab_handler (vec_shl_optab, V4SImode)->insn_code = CODE_FOR_vec_shl_v4si;
  if (HAVE_vec_shl_v2di)
    optab_handler (vec_shl_optab, V2DImode)->insn_code = CODE_FOR_vec_shl_v2di;
  if (HAVE_vec_shr_v16qi)
    optab_handler (vec_shr_optab, V16QImode)->insn_code = CODE_FOR_vec_shr_v16qi;
  if (HAVE_vec_shr_v8hi)
    optab_handler (vec_shr_optab, V8HImode)->insn_code = CODE_FOR_vec_shr_v8hi;
  if (HAVE_vec_shr_v4si)
    optab_handler (vec_shr_optab, V4SImode)->insn_code = CODE_FOR_vec_shr_v4si;
  if (HAVE_vec_shr_v2di)
    optab_handler (vec_shr_optab, V2DImode)->insn_code = CODE_FOR_vec_shr_v2di;
  if (HAVE_umaxv16qi3)
    optab_handler (umax_optab, V16QImode)->insn_code = CODE_FOR_umaxv16qi3;
  if (HAVE_uminv16qi3)
    optab_handler (umin_optab, V16QImode)->insn_code = CODE_FOR_uminv16qi3;
  if (HAVE_smaxv8hi3)
    optab_handler (smax_optab, V8HImode)->insn_code = CODE_FOR_smaxv8hi3;
  if (HAVE_sminv8hi3)
    optab_handler (smin_optab, V8HImode)->insn_code = CODE_FOR_sminv8hi3;
  if (HAVE_umaxv8hi3)
    optab_handler (umax_optab, V8HImode)->insn_code = CODE_FOR_umaxv8hi3;
  if (HAVE_smaxv16qi3)
    optab_handler (smax_optab, V16QImode)->insn_code = CODE_FOR_smaxv16qi3;
  if (HAVE_smaxv4si3)
    optab_handler (smax_optab, V4SImode)->insn_code = CODE_FOR_smaxv4si3;
  if (HAVE_umaxv4si3)
    optab_handler (umax_optab, V4SImode)->insn_code = CODE_FOR_umaxv4si3;
  if (HAVE_sminv16qi3)
    optab_handler (smin_optab, V16QImode)->insn_code = CODE_FOR_sminv16qi3;
  if (HAVE_sminv4si3)
    optab_handler (smin_optab, V4SImode)->insn_code = CODE_FOR_sminv4si3;
  if (HAVE_uminv8hi3)
    optab_handler (umin_optab, V8HImode)->insn_code = CODE_FOR_uminv8hi3;
  if (HAVE_uminv4si3)
    optab_handler (umin_optab, V4SImode)->insn_code = CODE_FOR_uminv4si3;
  if (HAVE_vcondv16qi)
    vcond_gen_code[V16QImode] = CODE_FOR_vcondv16qi;
  if (HAVE_vcondv8hi)
    vcond_gen_code[V8HImode] = CODE_FOR_vcondv8hi;
  if (HAVE_vcondv4si)
    vcond_gen_code[V4SImode] = CODE_FOR_vcondv4si;
  if (HAVE_vcondv2di)
    vcond_gen_code[V2DImode] = CODE_FOR_vcondv2di;
  if (HAVE_vconduv16qi)
    vcondu_gen_code[V16QImode] = CODE_FOR_vconduv16qi;
  if (HAVE_vconduv8hi)
    vcondu_gen_code[V8HImode] = CODE_FOR_vconduv8hi;
  if (HAVE_vconduv4si)
    vcondu_gen_code[V4SImode] = CODE_FOR_vconduv4si;
  if (HAVE_vconduv2di)
    vcondu_gen_code[V2DImode] = CODE_FOR_vconduv2di;
  if (HAVE_one_cmplv16qi2)
    optab_handler (one_cmpl_optab, V16QImode)->insn_code = CODE_FOR_one_cmplv16qi2;
  if (HAVE_one_cmplv8hi2)
    optab_handler (one_cmpl_optab, V8HImode)->insn_code = CODE_FOR_one_cmplv8hi2;
  if (HAVE_one_cmplv4si2)
    optab_handler (one_cmpl_optab, V4SImode)->insn_code = CODE_FOR_one_cmplv4si2;
  if (HAVE_one_cmplv2di2)
    optab_handler (one_cmpl_optab, V2DImode)->insn_code = CODE_FOR_one_cmplv2di2;
  if (HAVE_andv16qi3)
    optab_handler (and_optab, V16QImode)->insn_code = CODE_FOR_andv16qi3;
  if (HAVE_iorv16qi3)
    optab_handler (ior_optab, V16QImode)->insn_code = CODE_FOR_iorv16qi3;
  if (HAVE_xorv16qi3)
    optab_handler (xor_optab, V16QImode)->insn_code = CODE_FOR_xorv16qi3;
  if (HAVE_andv8hi3)
    optab_handler (and_optab, V8HImode)->insn_code = CODE_FOR_andv8hi3;
  if (HAVE_iorv8hi3)
    optab_handler (ior_optab, V8HImode)->insn_code = CODE_FOR_iorv8hi3;
  if (HAVE_xorv8hi3)
    optab_handler (xor_optab, V8HImode)->insn_code = CODE_FOR_xorv8hi3;
  if (HAVE_andv4si3)
    optab_handler (and_optab, V4SImode)->insn_code = CODE_FOR_andv4si3;
  if (HAVE_iorv4si3)
    optab_handler (ior_optab, V4SImode)->insn_code = CODE_FOR_iorv4si3;
  if (HAVE_xorv4si3)
    optab_handler (xor_optab, V4SImode)->insn_code = CODE_FOR_xorv4si3;
  if (HAVE_andv2di3)
    optab_handler (and_optab, V2DImode)->insn_code = CODE_FOR_andv2di3;
  if (HAVE_iorv2di3)
    optab_handler (ior_optab, V2DImode)->insn_code = CODE_FOR_iorv2di3;
  if (HAVE_xorv2di3)
    optab_handler (xor_optab, V2DImode)->insn_code = CODE_FOR_xorv2di3;
  if (HAVE_andtf3)
    optab_handler (and_optab, TFmode)->insn_code = CODE_FOR_andtf3;
  if (HAVE_iortf3)
    optab_handler (ior_optab, TFmode)->insn_code = CODE_FOR_iortf3;
  if (HAVE_xortf3)
    optab_handler (xor_optab, TFmode)->insn_code = CODE_FOR_xortf3;
  if (HAVE_vec_pack_trunc_v8hi)
    optab_handler (vec_pack_trunc_optab, V8HImode)->insn_code = CODE_FOR_vec_pack_trunc_v8hi;
  if (HAVE_vec_pack_trunc_v4si)
    optab_handler (vec_pack_trunc_optab, V4SImode)->insn_code = CODE_FOR_vec_pack_trunc_v4si;
  if (HAVE_vec_pack_trunc_v2di)
    optab_handler (vec_pack_trunc_optab, V2DImode)->insn_code = CODE_FOR_vec_pack_trunc_v2di;
  if (HAVE_vec_interleave_highv16qi)
    optab_handler (vec_interleave_high_optab, V16QImode)->insn_code = CODE_FOR_vec_interleave_highv16qi;
  if (HAVE_vec_interleave_lowv16qi)
    optab_handler (vec_interleave_low_optab, V16QImode)->insn_code = CODE_FOR_vec_interleave_lowv16qi;
  if (HAVE_vec_interleave_highv8hi)
    optab_handler (vec_interleave_high_optab, V8HImode)->insn_code = CODE_FOR_vec_interleave_highv8hi;
  if (HAVE_vec_interleave_lowv8hi)
    optab_handler (vec_interleave_low_optab, V8HImode)->insn_code = CODE_FOR_vec_interleave_lowv8hi;
  if (HAVE_vec_interleave_highv4si)
    optab_handler (vec_interleave_high_optab, V4SImode)->insn_code = CODE_FOR_vec_interleave_highv4si;
  if (HAVE_vec_interleave_lowv4si)
    optab_handler (vec_interleave_low_optab, V4SImode)->insn_code = CODE_FOR_vec_interleave_lowv4si;
  if (HAVE_vec_interleave_highv2di)
    optab_handler (vec_interleave_high_optab, V2DImode)->insn_code = CODE_FOR_vec_interleave_highv2di;
  if (HAVE_vec_interleave_lowv2di)
    optab_handler (vec_interleave_low_optab, V2DImode)->insn_code = CODE_FOR_vec_interleave_lowv2di;
  if (HAVE_vec_interleave_highv4sf)
    optab_handler (vec_interleave_high_optab, V4SFmode)->insn_code = CODE_FOR_vec_interleave_highv4sf;
  if (HAVE_vec_interleave_lowv4sf)
    optab_handler (vec_interleave_low_optab, V4SFmode)->insn_code = CODE_FOR_vec_interleave_lowv4sf;
  if (HAVE_vec_interleave_highv2df)
    optab_handler (vec_interleave_high_optab, V2DFmode)->insn_code = CODE_FOR_vec_interleave_highv2df;
  if (HAVE_vec_interleave_lowv2df)
    optab_handler (vec_interleave_low_optab, V2DFmode)->insn_code = CODE_FOR_vec_interleave_lowv2df;
  if (HAVE_vec_unpacku_hi_v16qi)
    optab_handler (vec_unpacku_hi_optab, V16QImode)->insn_code = CODE_FOR_vec_unpacku_hi_v16qi;
  if (HAVE_vec_unpacks_hi_v16qi)
    optab_handler (vec_unpacks_hi_optab, V16QImode)->insn_code = CODE_FOR_vec_unpacks_hi_v16qi;
  if (HAVE_vec_unpacku_lo_v16qi)
    optab_handler (vec_unpacku_lo_optab, V16QImode)->insn_code = CODE_FOR_vec_unpacku_lo_v16qi;
  if (HAVE_vec_unpacks_lo_v16qi)
    optab_handler (vec_unpacks_lo_optab, V16QImode)->insn_code = CODE_FOR_vec_unpacks_lo_v16qi;
  if (HAVE_vec_unpacku_hi_v8hi)
    optab_handler (vec_unpacku_hi_optab, V8HImode)->insn_code = CODE_FOR_vec_unpacku_hi_v8hi;
  if (HAVE_vec_unpacks_hi_v8hi)
    optab_handler (vec_unpacks_hi_optab, V8HImode)->insn_code = CODE_FOR_vec_unpacks_hi_v8hi;
  if (HAVE_vec_unpacku_lo_v8hi)
    optab_handler (vec_unpacku_lo_optab, V8HImode)->insn_code = CODE_FOR_vec_unpacku_lo_v8hi;
  if (HAVE_vec_unpacks_lo_v8hi)
    optab_handler (vec_unpacks_lo_optab, V8HImode)->insn_code = CODE_FOR_vec_unpacks_lo_v8hi;
  if (HAVE_vec_unpacku_hi_v4si)
    optab_handler (vec_unpacku_hi_optab, V4SImode)->insn_code = CODE_FOR_vec_unpacku_hi_v4si;
  if (HAVE_vec_unpacks_hi_v4si)
    optab_handler (vec_unpacks_hi_optab, V4SImode)->insn_code = CODE_FOR_vec_unpacks_hi_v4si;
  if (HAVE_vec_unpacku_lo_v4si)
    optab_handler (vec_unpacku_lo_optab, V4SImode)->insn_code = CODE_FOR_vec_unpacku_lo_v4si;
  if (HAVE_vec_unpacks_lo_v4si)
    optab_handler (vec_unpacks_lo_optab, V4SImode)->insn_code = CODE_FOR_vec_unpacks_lo_v4si;
  if (HAVE_rotlv16qi3)
    optab_handler (rotl_optab, V16QImode)->insn_code = CODE_FOR_rotlv16qi3;
  if (HAVE_rotlv8hi3)
    optab_handler (rotl_optab, V8HImode)->insn_code = CODE_FOR_rotlv8hi3;
  if (HAVE_rotlv4si3)
    optab_handler (rotl_optab, V4SImode)->insn_code = CODE_FOR_rotlv4si3;
  if (HAVE_rotlv2di3)
    optab_handler (rotl_optab, V2DImode)->insn_code = CODE_FOR_rotlv2di3;
  if (HAVE_rotrv16qi3)
    optab_handler (rotr_optab, V16QImode)->insn_code = CODE_FOR_rotrv16qi3;
  if (HAVE_rotrv8hi3)
    optab_handler (rotr_optab, V8HImode)->insn_code = CODE_FOR_rotrv8hi3;
  if (HAVE_rotrv4si3)
    optab_handler (rotr_optab, V4SImode)->insn_code = CODE_FOR_rotrv4si3;
  if (HAVE_rotrv2di3)
    optab_handler (rotr_optab, V2DImode)->insn_code = CODE_FOR_rotrv2di3;
  if (HAVE_vrotrv16qi3)
    optab_handler (vrotr_optab, V16QImode)->insn_code = CODE_FOR_vrotrv16qi3;
  if (HAVE_vrotrv8hi3)
    optab_handler (vrotr_optab, V8HImode)->insn_code = CODE_FOR_vrotrv8hi3;
  if (HAVE_vrotrv4si3)
    optab_handler (vrotr_optab, V4SImode)->insn_code = CODE_FOR_vrotrv4si3;
  if (HAVE_vrotrv2di3)
    optab_handler (vrotr_optab, V2DImode)->insn_code = CODE_FOR_vrotrv2di3;
  if (HAVE_vrotlv16qi3)
    optab_handler (vrotl_optab, V16QImode)->insn_code = CODE_FOR_vrotlv16qi3;
  if (HAVE_vrotlv8hi3)
    optab_handler (vrotl_optab, V8HImode)->insn_code = CODE_FOR_vrotlv8hi3;
  if (HAVE_vrotlv4si3)
    optab_handler (vrotl_optab, V4SImode)->insn_code = CODE_FOR_vrotlv4si3;
  if (HAVE_vrotlv2di3)
    optab_handler (vrotl_optab, V2DImode)->insn_code = CODE_FOR_vrotlv2di3;
  if (HAVE_vlshrv16qi3)
    optab_handler (vlshr_optab, V16QImode)->insn_code = CODE_FOR_vlshrv16qi3;
  if (HAVE_vlshrv8hi3)
    optab_handler (vlshr_optab, V8HImode)->insn_code = CODE_FOR_vlshrv8hi3;
  if (HAVE_vlshrv4si3)
    optab_handler (vlshr_optab, V4SImode)->insn_code = CODE_FOR_vlshrv4si3;
  if (HAVE_vashrv16qi3)
    optab_handler (vashr_optab, V16QImode)->insn_code = CODE_FOR_vashrv16qi3;
  if (HAVE_vashrv8hi3)
    optab_handler (vashr_optab, V8HImode)->insn_code = CODE_FOR_vashrv8hi3;
  if (HAVE_vashrv4si3)
    optab_handler (vashr_optab, V4SImode)->insn_code = CODE_FOR_vashrv4si3;
  if (HAVE_vashlv16qi3)
    optab_handler (vashl_optab, V16QImode)->insn_code = CODE_FOR_vashlv16qi3;
  if (HAVE_vashlv8hi3)
    optab_handler (vashl_optab, V8HImode)->insn_code = CODE_FOR_vashlv8hi3;
  if (HAVE_vashlv4si3)
    optab_handler (vashl_optab, V4SImode)->insn_code = CODE_FOR_vashlv4si3;
  if (HAVE_ashlv16qi3)
    optab_handler (ashl_optab, V16QImode)->insn_code = CODE_FOR_ashlv16qi3;
  if (HAVE_ashrv16qi3)
    optab_handler (ashr_optab, V16QImode)->insn_code = CODE_FOR_ashrv16qi3;
  if (HAVE_ashrv2di3)
    optab_handler (ashr_optab, V2DImode)->insn_code = CODE_FOR_ashrv2di3;
  if (HAVE_vec_initv32qi)
    optab_handler (vec_init_optab, V32QImode)->insn_code = CODE_FOR_vec_initv32qi;
  if (HAVE_vec_initv16hi)
    optab_handler (vec_init_optab, V16HImode)->insn_code = CODE_FOR_vec_initv16hi;
  if (HAVE_vec_initv8si)
    optab_handler (vec_init_optab, V8SImode)->insn_code = CODE_FOR_vec_initv8si;
  if (HAVE_vec_initv4di)
    optab_handler (vec_init_optab, V4DImode)->insn_code = CODE_FOR_vec_initv4di;
  if (HAVE_vec_initv8sf)
    optab_handler (vec_init_optab, V8SFmode)->insn_code = CODE_FOR_vec_initv8sf;
  if (HAVE_vec_initv4df)
    optab_handler (vec_init_optab, V4DFmode)->insn_code = CODE_FOR_vec_initv4df;
  if (HAVE_sync_compare_and_swapqi)
    sync_compare_and_swap[QImode] = CODE_FOR_sync_compare_and_swapqi;
  if (HAVE_sync_compare_and_swaphi)
    sync_compare_and_swap[HImode] = CODE_FOR_sync_compare_and_swaphi;
  if (HAVE_sync_compare_and_swapsi)
    sync_compare_and_swap[SImode] = CODE_FOR_sync_compare_and_swapsi;
  if (HAVE_sync_compare_and_swapdi)
    sync_compare_and_swap[DImode] = CODE_FOR_sync_compare_and_swapdi;
  if (HAVE_sync_compare_and_swapti)
    sync_compare_and_swap[TImode] = CODE_FOR_sync_compare_and_swapti;
  if (HAVE_sync_compare_and_swap_ccqi)
    sync_compare_and_swap_cc[QImode] = CODE_FOR_sync_compare_and_swap_ccqi;
  if (HAVE_sync_compare_and_swap_cchi)
    sync_compare_and_swap_cc[HImode] = CODE_FOR_sync_compare_and_swap_cchi;
  if (HAVE_sync_compare_and_swap_ccsi)
    sync_compare_and_swap_cc[SImode] = CODE_FOR_sync_compare_and_swap_ccsi;
  if (HAVE_sync_compare_and_swap_ccdi)
    sync_compare_and_swap_cc[DImode] = CODE_FOR_sync_compare_and_swap_ccdi;
  if (HAVE_sync_compare_and_swap_ccti)
    sync_compare_and_swap_cc[TImode] = CODE_FOR_sync_compare_and_swap_ccti;

#ifdef FIXUNS_TRUNC_LIKE_FIX_TRUNC
  /* This flag says the same insns that convert to a signed fixnum
     also convert validly to an unsigned one.  */
  for (i = 0; i < NUM_MACHINE_MODES; i++)
    for (j = 0; j < NUM_MACHINE_MODES; j++)
      convert_optab_handler (ufixtrunc_optab, i, j)->insn_code
      = convert_optab_handler (sfixtrunc_optab, i, j)->insn_code;
#endif
}
