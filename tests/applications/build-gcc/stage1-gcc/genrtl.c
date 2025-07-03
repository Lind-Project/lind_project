/* Generated automatically by gengenrtl from rtl.def.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "obstack.h"
#include "rtl.h"
#include "ggc.h"

rtx
gen_rtx_fmt_ee_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0,
	rtx arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_ue_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0,
	rtx arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_E_stat (RTX_CODE code, enum machine_mode mode,
	rtvec arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XVEC (rt, 0) = arg0;

  return rt;
}

rtx
gen_rtx_fmt_e_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;

  return rt;
}

rtx
gen_rtx_fmt_iuuBieie_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	rtx arg1,
	rtx arg2,
	struct basic_block_def *arg3,
	int arg4,
	rtx arg5,
	int arg6,
	rtx arg7 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;
  XBBDEF (rt, 3) = arg3;
  XINT (rt, 4) = arg4;
  XEXP (rt, 5) = arg5;
  XINT (rt, 6) = arg6;
  XEXP (rt, 7) = arg7;

  return rt;
}

rtx
gen_rtx_fmt_iuuBieie0_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	rtx arg1,
	rtx arg2,
	struct basic_block_def *arg3,
	int arg4,
	rtx arg5,
	int arg6,
	rtx arg7 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;
  XBBDEF (rt, 3) = arg3;
  XINT (rt, 4) = arg4;
  XEXP (rt, 5) = arg5;
  XINT (rt, 6) = arg6;
  XEXP (rt, 7) = arg7;
  X0EXP (rt, 8) = NULL_RTX;

  return rt;
}

rtx
gen_rtx_fmt_iuuBieiee_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	rtx arg1,
	rtx arg2,
	struct basic_block_def *arg3,
	int arg4,
	rtx arg5,
	int arg6,
	rtx arg7,
	rtx arg8 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;
  XBBDEF (rt, 3) = arg3;
  XINT (rt, 4) = arg4;
  XEXP (rt, 5) = arg5;
  XINT (rt, 6) = arg6;
  XEXP (rt, 7) = arg7;
  XEXP (rt, 8) = arg8;

  return rt;
}

rtx
gen_rtx_fmt_iuu00000_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	rtx arg1,
	rtx arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;
  X0EXP (rt, 3) = NULL_RTX;
  X0EXP (rt, 4) = NULL_RTX;
  X0EXP (rt, 5) = NULL_RTX;
  X0EXP (rt, 6) = NULL_RTX;
  X0EXP (rt, 7) = NULL_RTX;

  return rt;
}

rtx
gen_rtx_fmt_iuuB00is_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	rtx arg1,
	rtx arg2,
	struct basic_block_def *arg3,
	int arg4,
	const char *arg5 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;
  XBBDEF (rt, 3) = arg3;
  X0EXP (rt, 4) = NULL_RTX;
  X0EXP (rt, 5) = NULL_RTX;
  XINT (rt, 6) = arg4;
  XSTR (rt, 7) = arg5;

  return rt;
}

rtx
gen_rtx_fmt_si_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	int arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XINT (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_ssiEEi_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	const char *arg1,
	int arg2,
	rtvec arg3,
	rtvec arg4,
	int arg5 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XSTR (rt, 1) = arg1;
  XINT (rt, 2) = arg2;
  XVEC (rt, 3) = arg3;
  XVEC (rt, 4) = arg4;
  XINT (rt, 5) = arg5;

  return rt;
}

rtx
gen_rtx_fmt_Ei_stat (RTX_CODE code, enum machine_mode mode,
	rtvec arg0,
	int arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XVEC (rt, 0) = arg0;
  XINT (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_eEee0_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0,
	rtvec arg1,
	rtx arg2,
	rtx arg3 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;
  XVEC (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;
  XEXP (rt, 3) = arg3;
  X0EXP (rt, 4) = NULL_RTX;

  return rt;
}

rtx
gen_rtx_fmt_eee_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0,
	rtx arg1,
	rtx arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt__stat (RTX_CODE code, enum machine_mode mode MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);

  return rt;
}

rtx
gen_rtx_fmt_i_stat (RTX_CODE code, enum machine_mode mode,
	int arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;

  return rt;
}

rtx
gen_rtx_fmt_w_stat (RTX_CODE code, enum machine_mode mode,
	HOST_WIDE_INT arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XWINT (rt, 0) = arg0;

  return rt;
}

rtx
gen_rtx_fmt_www_stat (RTX_CODE code, enum machine_mode mode,
	HOST_WIDE_INT arg0,
	HOST_WIDE_INT arg1,
	HOST_WIDE_INT arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XWINT (rt, 0) = arg0;
  XWINT (rt, 1) = arg1;
  XWINT (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt_s_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;

  return rt;
}

rtx
gen_rtx_fmt_0_stat (RTX_CODE code, enum machine_mode mode MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  X0EXP (rt, 0) = NULL_RTX;

  return rt;
}

rtx
gen_rtx_fmt_i00_stat (RTX_CODE code, enum machine_mode mode,
	int arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  X0EXP (rt, 1) = NULL_RTX;
  X0EXP (rt, 2) = NULL_RTX;

  return rt;
}

rtx
gen_rtx_fmt_ei_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0,
	int arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;
  XINT (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_e0_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;
  X0EXP (rt, 1) = NULL_RTX;

  return rt;
}

rtx
gen_rtx_fmt_u_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;

  return rt;
}

rtx
gen_rtx_fmt_s00_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  X0EXP (rt, 1) = NULL_RTX;
  X0EXP (rt, 2) = NULL_RTX;

  return rt;
}

rtx
gen_rtx_fmt_tei_stat (RTX_CODE code, enum machine_mode mode,
	union tree_node *arg0,
	rtx arg1,
	int arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XTREE (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;
  XINT (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt_iss_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	const char *arg1,
	const char *arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XSTR (rt, 1) = arg1;
  XSTR (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt_is_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	const char *arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XSTR (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_isE_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	const char *arg1,
	rtvec arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XSTR (rt, 1) = arg1;
  XVEC (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt_iE_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	rtvec arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XVEC (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_ss_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	const char *arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XSTR (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_sEss_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	rtvec arg1,
	const char *arg2,
	const char *arg3 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XVEC (rt, 1) = arg1;
  XSTR (rt, 2) = arg2;
  XSTR (rt, 3) = arg3;

  return rt;
}

rtx
gen_rtx_fmt_eE_stat (RTX_CODE code, enum machine_mode mode,
	rtx arg0,
	rtvec arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XEXP (rt, 0) = arg0;
  XVEC (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_Ess_stat (RTX_CODE code, enum machine_mode mode,
	rtvec arg0,
	const char *arg1,
	const char *arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XVEC (rt, 0) = arg0;
  XSTR (rt, 1) = arg1;
  XSTR (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt_ses_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	rtx arg1,
	const char *arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;
  XSTR (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt_sss_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	const char *arg1,
	const char *arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XSTR (rt, 1) = arg1;
  XSTR (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt_sse_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	const char *arg1,
	rtx arg2 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XSTR (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;

  return rt;
}

rtx
gen_rtx_fmt_sies_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	int arg1,
	rtx arg2,
	const char *arg3 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XINT (rt, 1) = arg1;
  XEXP (rt, 2) = arg2;
  XSTR (rt, 3) = arg3;

  return rt;
}

rtx
gen_rtx_fmt_sE_stat (RTX_CODE code, enum machine_mode mode,
	const char *arg0,
	rtvec arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XSTR (rt, 0) = arg0;
  XVEC (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_ii_stat (RTX_CODE code, enum machine_mode mode,
	int arg0,
	int arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XINT (rt, 0) = arg0;
  XINT (rt, 1) = arg1;

  return rt;
}

rtx
gen_rtx_fmt_Ee_stat (RTX_CODE code, enum machine_mode mode,
	rtvec arg0,
	rtx arg1 MEM_STAT_DECL)
{
  rtx rt;
  rt = rtx_alloc_stat (code PASS_MEM_STAT);

  PUT_MODE (rt, mode);
  XVEC (rt, 0) = arg0;
  XEXP (rt, 1) = arg1;

  return rt;
}

