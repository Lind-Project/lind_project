/* Generated automatically by the program `genextract'
   from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "insn-config.h"
#include "recog.h"
#include "toplev.h"

/* This variable is used as the "location" of any missing operand
   whose numbers are skipped by a given pattern.  */
static rtx junk ATTRIBUTE_UNUSED;

void
insn_extract (rtx insn)
{
  rtx *ro = recog_data.operand;
  rtx **ro_loc = recog_data.operand_loc;
  rtx pat = PATTERN (insn);
  int i ATTRIBUTE_UNUSED; /* only for peepholes */

#ifdef ENABLE_CHECKING
  memset (ro, 0xab, sizeof (*ro) * MAX_RECOG_OPERANDS);
  memset (ro_loc, 0xab, sizeof (*ro_loc) * MAX_RECOG_OPERANDS);
#endif

  switch (INSN_CODE (insn))
    {
    default:
      /* Control reaches here if insn_extract has been called with an
         unrecognizable insn (code -1), or an insn whose INSN_CODE
         corresponds to a DEFINE_EXPAND in the machine description;
         either way, a bug.  */
      if (INSN_CODE (insn) < 0)
        fatal_insn ("unrecognizable insn:", insn);
      else
        fatal_insn ("insn with invalid code number:", insn);

    case 2042:  /* sync_xordi */
    case 2041:  /* sync_xorsi */
    case 2040:  /* sync_xorhi */
    case 2039:  /* sync_xorqi */
    case 2038:  /* sync_anddi */
    case 2037:  /* sync_andsi */
    case 2036:  /* sync_andhi */
    case 2035:  /* sync_andqi */
    case 2034:  /* sync_iordi */
    case 2033:  /* sync_iorsi */
    case 2032:  /* sync_iorhi */
    case 2031:  /* sync_iorqi */
    case 2030:  /* sync_subdi */
    case 2029:  /* sync_subsi */
    case 2028:  /* sync_subhi */
    case 2027:  /* sync_subqi */
    case 2026:  /* sync_adddi */
    case 2025:  /* sync_addsi */
    case 2024:  /* sync_addhi */
    case 2023:  /* sync_addqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 2022:  /* sync_lock_test_and_setdi */
    case 2021:  /* sync_lock_test_and_setsi */
    case 2020:  /* sync_lock_test_and_sethi */
    case 2019:  /* sync_lock_test_and_setqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 2018:  /* sync_old_adddi */
    case 2017:  /* sync_old_addsi */
    case 2016:  /* sync_old_addhi */
    case 2015:  /* sync_old_addqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[1] = 1;
      break;

    case 2014:  /* *sync_double_compare_and_swap_ccdi_pic */
    case 2013:  /* sync_double_compare_and_swap_ccti */
    case 2012:  /* sync_double_compare_and_swap_ccdi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0, 3);
      recog_data.dup_num[0] = 4;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0, 2);
      recog_data.dup_num[1] = 3;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0, 1);
      recog_data.dup_num[2] = 2;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0, 0);
      recog_data.dup_num[3] = 1;
      recog_data.dup_loc[4] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 1);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[5] = 1;
      recog_data.dup_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[6] = 1;
      break;

    case 2011:  /* *sync_compare_and_swap_ccdi */
    case 2010:  /* *sync_compare_and_swap_ccsi */
    case 2009:  /* *sync_compare_and_swap_cchi */
    case 2008:  /* *sync_compare_and_swap_ccqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0, 2);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0, 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0, 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 1);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[5] = 1;
      break;

    case 2007:  /* *sync_double_compare_and_swapdi_pic */
    case 2006:  /* sync_double_compare_and_swapti */
    case 2005:  /* sync_double_compare_and_swapdi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[1] = 1;
      break;

    case 2004:  /* *sync_compare_and_swapdi */
    case 2003:  /* *sync_compare_and_swapsi */
    case 2002:  /* *sync_compare_and_swaphi */
    case 2001:  /* *sync_compare_and_swapqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[1] = 1;
      break;

    case 2000:  /* memory_barrier_nosse */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0);
      recog_data.dup_num[0] = 0;
      break;

    case 1987:  /* avx_maskstorepd256 */
    case 1986:  /* avx_maskstoreps256 */
    case 1985:  /* avx_maskstorepd */
    case 1984:  /* avx_maskstoreps */
    case 1983:  /* avx_maskloadpd256 */
    case 1982:  /* avx_maskloadps256 */
    case 1981:  /* avx_maskloadpd */
    case 1980:  /* avx_maskloadps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 2);
      recog_data.dup_num[0] = 0;
      break;

    case 1965:  /* avx_vbroadcastss256 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0);
      recog_data.dup_num[3] = 1;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0);
      recog_data.dup_num[5] = 1;
      recog_data.dup_loc[6] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1);
      recog_data.dup_num[6] = 1;
      break;

    case 1964:  /* avx_vbroadcastsd256 */
    case 1963:  /* avx_vbroadcastss */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 1);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 1);
      recog_data.dup_num[2] = 1;
      break;

    case 1949:  /* *avx_vzeroall */
      ro[0] = *(ro_loc[0] = &PATTERN (insn));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 1));
      break;

    case 1932:  /* sse5_maskcmp_uns2v2di3 */
    case 1931:  /* sse5_maskcmp_uns2v4si3 */
    case 1930:  /* sse5_maskcmp_uns2v8hi3 */
    case 1929:  /* sse5_maskcmp_uns2v16qi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 1916:  /* *sse5_vmmaskcmpv2df3 */
    case 1915:  /* *sse5_vmmaskcmpv4sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1912:  /* sse5_vmfrczv2df2 */
    case 1911:  /* sse5_vmfrczv4sf2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      break;

    case 1908:  /* sse5_lshlv2di3 */
    case 1907:  /* sse5_lshlv4si3 */
    case 1906:  /* sse5_lshlv8hi3 */
    case 1905:  /* sse5_lshlv16qi3 */
    case 1904:  /* sse5_ashlv2di3 */
    case 1903:  /* sse5_ashlv4si3 */
    case 1902:  /* sse5_ashlv8hi3 */
    case 1901:  /* sse5_ashlv16qi3 */
    case 1900:  /* sse5_vrotlv2di3 */
    case 1899:  /* sse5_vrotlv4si3 */
    case 1898:  /* sse5_vrotlv8hi3 */
    case 1897:  /* sse5_vrotlv16qi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 1);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 2), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 2), 1), 0);
      recog_data.dup_num[2] = 2;
      break;

    case 1886:  /* sse5_pperm_pack_v8hi_v16qi */
    case 1885:  /* sse5_pperm_pack_v4si_v8hi */
    case 1884:  /* sse5_pperm_pack_v2di_v4si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 1883:  /* sse5_pperm_sign_v4si_v2di */
    case 1882:  /* sse5_pperm_zero_v4si_v2di */
    case 1881:  /* sse5_pperm_sign_v8hi_v4si */
    case 1880:  /* sse5_pperm_zero_v8hi_v4si */
    case 1879:  /* sse5_pperm_sign_v16qi_v8hi */
    case 1878:  /* sse5_pperm_zero_v16qi_v8hi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 1870:  /* sse5_phaddubq */
    case 1864:  /* sse5_phaddbq */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0), 0);
      recog_data.dup_num[3] = 1;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0), 0);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0), 0);
      recog_data.dup_num[5] = 1;
      recog_data.dup_loc[6] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0), 0);
      recog_data.dup_num[6] = 1;
      break;

    case 1872:  /* sse5_phadduwq */
    case 1869:  /* sse5_phaddubd */
    case 1866:  /* sse5_phaddwq */
    case 1863:  /* sse5_phaddbd */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0);
      recog_data.dup_num[2] = 1;
      break;

    case 1876:  /* sse5_phsubdq */
    case 1875:  /* sse5_phsubwd */
    case 1874:  /* sse5_phsubbw */
    case 1873:  /* sse5_phaddudq */
    case 1871:  /* sse5_phadduwd */
    case 1868:  /* sse5_phaddubw */
    case 1867:  /* sse5_phadddq */
    case 1865:  /* sse5_phaddwd */
    case 1862:  /* sse5_phaddbw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 1861:  /* sse5_pcmov_v2df */
    case 1860:  /* sse5_pcmov_v4sf */
    case 1859:  /* sse5_pcmov_v2di */
    case 1858:  /* sse5_pcmov_v4si */
    case 1857:  /* sse5_pcmov_v8hi */
    case 1856:  /* sse5_pcmov_v16qi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 2));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1855:  /* sse5_pmadcswd */
    case 1854:  /* sse5_pmadcsswd */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 1853:  /* sse5_pmacswd */
    case 1852:  /* sse5_pmacsswd */
    case 1850:  /* *sse5_pmacsdqh_mem */
    case 1849:  /* sse5_pmacsdqh */
    case 1847:  /* *sse5_pmacsdql_mem */
    case 1846:  /* sse5_pmacsdql */
    case 1845:  /* sse5_pmacssdqh */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1844:  /* sse5_pmacssdql */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1839:  /* sse4_2_pcmpistr_cconly */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      break;

    case 1838:  /* sse4_2_pcmpistrm */
    case 1837:  /* sse4_2_pcmpistri */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[2] = 1;
      break;

    case 1836:  /* sse4_2_pcmpistr */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 2);
      recog_data.dup_num[0] = 4;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[1] = 3;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[2] = 2;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[3] = 4;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[4] = 3;
      recog_data.dup_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[5] = 2;
      break;

    case 1835:  /* sse4_2_pcmpestr_cconly */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 4));
      break;

    case 1834:  /* sse4_2_pcmpestrm */
    case 1833:  /* sse4_2_pcmpestri */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 4));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 4);
      recog_data.dup_num[0] = 5;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3);
      recog_data.dup_num[1] = 4;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[2] = 3;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[4] = 1;
      break;

    case 1832:  /* sse4_2_pcmpestr */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 4));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 4);
      recog_data.dup_num[0] = 6;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 3);
      recog_data.dup_num[1] = 5;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 2);
      recog_data.dup_num[2] = 4;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[3] = 3;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 4);
      recog_data.dup_num[5] = 6;
      recog_data.dup_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3);
      recog_data.dup_num[6] = 5;
      recog_data.dup_loc[7] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[7] = 4;
      recog_data.dup_loc[8] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[8] = 3;
      recog_data.dup_loc[9] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[9] = 2;
      break;

    case 1831:  /* sse4_1_roundsd */
    case 1830:  /* sse4_1_roundss */
    case 1829:  /* *avx_roundsd */
    case 1828:  /* *avx_roundss */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 1));
      break;

    case 1823:  /* sse4_1_ptest */
    case 1822:  /* avx_ptest256 */
    case 1821:  /* avx_vtestpd256 */
    case 1820:  /* avx_vtestps256 */
    case 1819:  /* avx_vtestpd */
    case 1818:  /* avx_vtestps */
      ro[0] = *(ro_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 1));
      break;

    case 1792:  /* sse4_1_pblendw */
    case 1791:  /* *avx_pblendw */
    case 1775:  /* sse4_1_blendpd */
    case 1774:  /* sse4_1_blendps */
    case 1769:  /* avx_blendpd256 */
    case 1768:  /* avx_blendps256 */
    case 1767:  /* avx_blendpd */
    case 1766:  /* avx_blendps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

    case 1764:  /* sse4a_insertqi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (pat, 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (pat, 1), 0, 3));
      break;

    case 1736:  /* *ssse3_pmulhrswv4hi3 */
    case 1735:  /* *ssse3_pmulhrswv8hi3 */
    case 1734:  /* *avx_pmulhrswv8hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 1), 0));
      break;

    case 1729:  /* ssse3_phsubswv8hi3 */
    case 1728:  /* *avx_phsubswv8hi3 */
    case 1723:  /* ssse3_phsubwv8hi3 */
    case 1722:  /* *avx_phsubwv8hi3 */
    case 1720:  /* ssse3_phaddswv8hi3 */
    case 1719:  /* *avx_phaddswv8hi3 */
    case 1714:  /* ssse3_phaddwv8hi3 */
    case 1713:  /* *avx_phaddwv8hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 1), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0);
      recog_data.dup_num[3] = 1;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 1), 0);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[5] = 1;
      recog_data.dup_loc[6] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 1), 0);
      recog_data.dup_num[6] = 1;
      recog_data.dup_loc[7] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 1), 0);
      recog_data.dup_num[7] = 2;
      recog_data.dup_loc[8] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0), 0);
      recog_data.dup_num[8] = 2;
      recog_data.dup_loc[9] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 1), 0);
      recog_data.dup_num[9] = 2;
      recog_data.dup_loc[10] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0), 0);
      recog_data.dup_num[10] = 2;
      recog_data.dup_loc[11] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 1), 0);
      recog_data.dup_num[11] = 2;
      recog_data.dup_loc[12] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0), 0);
      recog_data.dup_num[12] = 2;
      recog_data.dup_loc[13] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 1), 0);
      recog_data.dup_num[13] = 2;
      break;

    case 1712:  /* sse3_monitor64 */
    case 1711:  /* sse3_monitor */
      ro[0] = *(ro_loc[0] = &XVECEXP (pat, 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (pat, 0, 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (pat, 0, 2));
      break;

    case 1710:  /* sse3_mwait */
      ro[0] = *(ro_loc[0] = &XVECEXP (pat, 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (pat, 0, 1));
      break;

    case 1665:  /* sse2_pshufhw_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 4));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 5));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 6));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 7));
      break;

    case 1967:  /* avx_vbroadcastf128_pd256 */
    case 1966:  /* avx_vbroadcastf128_ps256 */
    case 1454:  /* *vec_concatv2df_sse3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1440:  /* sse2_shufpd_v2di */
    case 1439:  /* sse2_shufpd_v2df */
    case 1438:  /* *avx_shufpd_v2di */
    case 1437:  /* *avx_shufpd_v2df */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      break;

    case 1669:  /* *vec_ext_v4si_mem */
    case 1662:  /* *sse4_1_pextrq */
    case 1661:  /* *sse4_1_pextrd */
    case 1660:  /* *sse4_1_pextrw_memory */
    case 1658:  /* *sse4_1_pextrb_memory */
    case 1422:  /* *vec_extract_v4sf_mem */
    case 1421:  /* *sse4_1_extractps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      break;

    case 1407:  /* sse4_1_insertps */
    case 1406:  /* *avx_insertps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (pat, 1), 0, 2));
      break;

    case 1667:  /* sse2_loadld */
    case 1666:  /* *avx_loadld */
    case 1403:  /* vec_setv4sf_0 */
    case 1402:  /* *vec_setv4sf_0_avx */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 1451:  /* sse2_movsd */
    case 1450:  /* *avx_movsd */
    case 1394:  /* sse_movss */
    case 1393:  /* *avx_movss */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1978:  /* vec_set_lo_v32qi */
    case 1976:  /* vec_set_lo_v16hi */
    case 1973:  /* vec_set_lo_v8sf */
    case 1972:  /* vec_set_lo_v8si */
    case 1969:  /* vec_set_lo_v4df */
    case 1968:  /* vec_set_lo_v4di */
    case 1447:  /* sse2_loadlpd */
    case 1446:  /* *avx_loadlpd */
    case 1392:  /* sse_loadlps */
    case 1391:  /* *avx_loadlps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1432:  /* avx_shufpd256_1 */
    case 1385:  /* sse_shufps_v4si */
    case 1384:  /* sse_shufps_v4sf */
    case 1383:  /* *avx_shufps_v4si */
    case 1382:  /* *avx_shufps_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 2));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 3));
      break;

    case 1381:  /* avx_shufps256_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 2));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 3));
      ro[7] = *(ro_loc[7] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 4));
      ro[8] = *(ro_loc[8] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 5));
      ro[9] = *(ro_loc[9] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 6));
      ro[10] = *(ro_loc[10] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 7));
      break;

    case 1428:  /* *sse3_movddup */
    case 1427:  /* *avx_movddup */
    case 1426:  /* avx_movddup256 */
    case 1380:  /* sse3_movsldup */
    case 1379:  /* avx_movsldup256 */
    case 1378:  /* sse3_movshdup */
    case 1377:  /* avx_movshdup256 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1319:  /* sse_cvtps2pi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      break;

    case 1362:  /* sse2_cvtss2sd */
    case 1361:  /* *avx_cvtss2sd */
    case 1360:  /* sse2_cvtsd2ss */
    case 1359:  /* *avx_cvtsd2ss */
    case 1346:  /* sse2_cvtsi2sdq */
    case 1345:  /* *avx_cvtsi2sdq */
    case 1344:  /* sse2_cvtsi2sd */
    case 1343:  /* *avx_cvtsi2sd */
    case 1324:  /* sse_cvtsi2ssq */
    case 1323:  /* *avx_cvtsi2ssq */
    case 1322:  /* sse_cvtsi2ss */
    case 1321:  /* *avx_cvtsi2ss */
    case 1318:  /* sse_cvtpi2ps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      break;

    case 1317:  /* *sse5i_vmfnmsubv2df4 */
    case 1316:  /* *sse5i_vmfnmsubv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1315:  /* *sse5i_vmfnmaddv2df4 */
    case 1314:  /* *sse5i_vmfnmaddv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1313:  /* *sse5i_vmfmsubv2df4 */
    case 1312:  /* *sse5i_vmfmsubv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1311:  /* *sse5i_vmfmaddv2df4 */
    case 1310:  /* *sse5i_vmfmaddv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1);
      recog_data.dup_num[0] = 0;
      break;

    case 1309:  /* *sse5i_fnmsubv2df4 */
    case 1308:  /* *sse5i_fnmsubv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 1307:  /* *sse5i_fnmaddv2df4 */
    case 1306:  /* *sse5i_fnmaddv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      break;

    case 1305:  /* *sse5i_fmsubv2df4 */
    case 1304:  /* *sse5i_fmsubv4sf4 */
    case 1303:  /* *sse5i_fmaddv2df4 */
    case 1302:  /* *sse5i_fmaddv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 1301:  /* sse5_vmfnmsubv2df4 */
    case 1300:  /* sse5_vmfnmsubv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1299:  /* sse5_fnmsubv2df4 */
    case 1298:  /* sse5_fnmsubv4sf4 */
    case 1297:  /* sse5_fnmsubdf4 */
    case 1296:  /* sse5_fnmsubsf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1295:  /* sse5_vmfnmaddv2df4 */
    case 1294:  /* sse5_vmfnmaddv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1293:  /* sse5_fnmaddv2df4 */
    case 1292:  /* sse5_fnmaddv4sf4 */
    case 1291:  /* sse5_fnmadddf4 */
    case 1290:  /* sse5_fnmaddsf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1289:  /* sse5_vmfmsubv2df4 */
    case 1288:  /* sse5_vmfmsubv4sf4 */
    case 1283:  /* sse5_vmfmaddv2df4 */
    case 1282:  /* sse5_vmfmaddv4sf4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1237:  /* sse2_ucomi */
    case 1236:  /* sse_ucomi */
    case 1235:  /* sse2_comi */
    case 1234:  /* sse_comi */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      break;

    case 1233:  /* sse2_vmmaskcmpv2df3 */
    case 1232:  /* sse_vmmaskcmpv4sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1223:  /* avx_cmpsdv2df3 */
    case 1222:  /* avx_cmpssv4sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 2));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1209:  /* avx_hsubv8sf3 */
    case 1208:  /* avx_haddv8sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 1), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 1), 0);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 1), 0);
      recog_data.dup_num[5] = 2;
      recog_data.dup_loc[6] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0), 0);
      recog_data.dup_num[6] = 1;
      recog_data.dup_loc[7] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 1), 0);
      recog_data.dup_num[7] = 1;
      recog_data.dup_loc[8] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0), 0);
      recog_data.dup_num[8] = 1;
      recog_data.dup_loc[9] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 1), 0);
      recog_data.dup_num[9] = 1;
      recog_data.dup_loc[10] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0), 0);
      recog_data.dup_num[10] = 2;
      recog_data.dup_loc[11] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 1), 0);
      recog_data.dup_num[11] = 2;
      recog_data.dup_loc[12] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0), 0);
      recog_data.dup_num[12] = 2;
      recog_data.dup_loc[13] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 1), 0);
      recog_data.dup_num[13] = 2;
      break;

    case 1730:  /* ssse3_phsubswv4hi3 */
    case 1726:  /* ssse3_phsubdv4si3 */
    case 1725:  /* *avx_phsubdv4si3 */
    case 1724:  /* ssse3_phsubwv4hi3 */
    case 1721:  /* ssse3_phaddswv4hi3 */
    case 1717:  /* ssse3_phadddv4si3 */
    case 1716:  /* *avx_phadddv4si3 */
    case 1715:  /* ssse3_phaddwv4hi3 */
    case 1213:  /* sse3_hsubv4sf3 */
    case 1212:  /* sse3_haddv4sf3 */
    case 1211:  /* *avx_hsubv4sf3 */
    case 1210:  /* *avx_haddv4sf3 */
    case 1207:  /* avx_hsubv4df3 */
    case 1206:  /* avx_haddv4df3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0);
      recog_data.dup_num[5] = 2;
      break;

    case 1356:  /* *sse2_cvtpd2dq */
    case 1155:  /* sse_vmrsqrtv4sf2 */
    case 1154:  /* *avx_vmrsqrtv4sf2 */
    case 1143:  /* sse_vmrcpv4sf2 */
    case 1142:  /* *avx_vmrcpv4sf2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1187:  /* sse2_vmsminv2df3 */
    case 1186:  /* sse2_vmsmaxv2df3 */
    case 1185:  /* sse_vmsminv4sf3 */
    case 1184:  /* sse_vmsmaxv4sf3 */
    case 1183:  /* *avx_vmsminv2df3 */
    case 1182:  /* *avx_vmsmaxv2df3 */
    case 1181:  /* *avx_vmsminv4sf3 */
    case 1180:  /* *avx_vmsmaxv4sf3 */
    case 1139:  /* sse2_vmdivv2df3 */
    case 1138:  /* sse_vmdivv4sf3 */
    case 1137:  /* *avx_vmdivv2df3 */
    case 1136:  /* *avx_vmdivv4sf3 */
    case 1127:  /* sse2_vmmulv2df3 */
    case 1126:  /* sse_vmmulv4sf3 */
    case 1125:  /* *avx_vmmulv2df3 */
    case 1124:  /* *avx_vmmulv4sf3 */
    case 1117:  /* sse2_vmsubv2df3 */
    case 1116:  /* sse2_vmaddv2df3 */
    case 1115:  /* sse_vmsubv4sf3 */
    case 1114:  /* sse_vmaddv4sf3 */
    case 1113:  /* *avx_vmsubv2df3 */
    case 1112:  /* *avx_vmaddv2df3 */
    case 1111:  /* *avx_vmsubv4sf3 */
    case 1110:  /* *avx_vmaddv4sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1703:  /* *sse2_maskmovdqu_rex64 */
    case 1702:  /* *sse2_maskmovdqu */
    case 1053:  /* *mmx_maskmovq_rex */
    case 1052:  /* *mmx_maskmovq */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 2), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 1664:  /* sse2_pshuflw_1 */
    case 1663:  /* sse2_pshufd_1 */
    case 1041:  /* mmx_pshufw_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 3));
      break;

    case 1659:  /* *sse2_pextrw */
    case 1657:  /* *sse4_1_pextrb */
    case 1040:  /* mmx_pextrw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0, 0));
      break;

    case 1656:  /* *sse4_1_pinsrq */
    case 1655:  /* *avx_pinsrq */
    case 1654:  /* *sse4_1_pinsrd */
    case 1653:  /* *sse2_pinsrw */
    case 1652:  /* *sse4_1_pinsrb */
    case 1651:  /* *avx_pinsrd */
    case 1650:  /* *avx_pinsrw */
    case 1649:  /* *avx_pinsrb */
    case 1405:  /* *vec_setv4sf_sse4_1 */
    case 1404:  /* *vec_setv4sf_avx */
    case 1039:  /* *mmx_pinsrw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

    case 1648:  /* sse2_punpckldq */
    case 1647:  /* *avx_punpckldq */
    case 1646:  /* sse2_punpckhdq */
    case 1645:  /* *avx_punpckhdq */
    case 1644:  /* sse2_punpcklwd */
    case 1643:  /* *avx_punpcklwd */
    case 1642:  /* sse2_punpckhwd */
    case 1641:  /* *avx_punpckhwd */
    case 1640:  /* sse2_punpcklbw */
    case 1639:  /* *avx_punpcklbw */
    case 1638:  /* sse2_punpckhbw */
    case 1637:  /* *avx_punpckhbw */
    case 1436:  /* sse2_punpcklqdq */
    case 1435:  /* *avx_punpcklqdq */
    case 1434:  /* sse2_punpckhqdq */
    case 1433:  /* *avx_punpckhqdq */
    case 1431:  /* sse2_unpcklpd */
    case 1430:  /* *avx_unpcklpd */
    case 1429:  /* avx_unpcklpd256 */
    case 1425:  /* sse2_unpckhpd */
    case 1424:  /* *avx_unpckhpd */
    case 1423:  /* avx_unpckhpd256 */
    case 1376:  /* sse_unpcklps */
    case 1375:  /* *avx_unpcklps */
    case 1374:  /* avx_unpcklps256 */
    case 1373:  /* sse_unpckhps */
    case 1372:  /* *avx_unpckhps */
    case 1371:  /* avx_unpckhps256 */
    case 1370:  /* sse_movlhps */
    case 1369:  /* *avx_movlhps */
    case 1368:  /* sse_movhlps */
    case 1367:  /* *avx_movhlps */
    case 1038:  /* mmx_punpckldq */
    case 1037:  /* mmx_punpckhdq */
    case 1036:  /* mmx_punpcklwd */
    case 1035:  /* mmx_punpckhwd */
    case 1034:  /* mmx_punpcklbw */
    case 1033:  /* mmx_punpckhbw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 1788:  /* sse4_1_packusdw */
    case 1787:  /* *avx_packusdw */
    case 1636:  /* sse2_packuswb */
    case 1635:  /* *avx_packuswb */
    case 1634:  /* sse2_packssdw */
    case 1633:  /* *avx_packssdw */
    case 1632:  /* sse2_packsswb */
    case 1631:  /* *avx_packsswb */
    case 1032:  /* mmx_packuswb */
    case 1031:  /* mmx_packssdw */
    case 1030:  /* mmx_packsswb */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      break;

    case 1851:  /* sse5_mulv2div2di3_high */
    case 1848:  /* sse5_mulv2div2di3_low */
    case 1499:  /* *sse4_1_mulv2siv2di3 */
    case 1498:  /* *avx_mulv2siv2di3 */
    case 1497:  /* *sse2_umulv2siv2di3 */
    case 1496:  /* *avx_umulv2siv2di3 */
    case 999:  /* *sse2_umulv1siv1di3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      break;

    case 1694:  /* *sse2_uavgv8hi3 */
    case 1693:  /* *avx_uavgv8hi3 */
    case 1692:  /* *sse2_uavgv16qi3 */
    case 1691:  /* *avx_uavgv16qi3 */
    case 1049:  /* *mmx_uavgv4hi3 */
    case 1048:  /* *mmx_uavgv8qi3 */
    case 998:  /* *mmx_pmulhrwv4hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 0));
      break;

    case 1733:  /* ssse3_pmaddubsw */
    case 1732:  /* ssse3_pmaddubsw128 */
    case 1731:  /* *avx_pmaddubsw128 */
    case 1501:  /* *sse2_pmaddwd */
    case 1500:  /* *avx_pmaddwd */
    case 997:  /* *mmx_pmaddwd */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 1495:  /* *umulv8hi3_highpart */
    case 1494:  /* *avx_umulv8hi3_highpart */
    case 1493:  /* *smulv8hi3_highpart */
    case 1492:  /* *avxv8hi3_highpart */
    case 996:  /* *mmx_umulv4hi3_highpart */
    case 995:  /* *mmx_smulv4hi3_highpart */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0));
      break;

    case 1817:  /* *sse4_1_zero_extendv2siv2di2 */
    case 1815:  /* *sse4_1_zero_extendv2hiv2di2 */
    case 1813:  /* *sse4_1_zero_extendv4hiv4si2 */
    case 1811:  /* *sse4_1_zero_extendv2qiv2di2 */
    case 1809:  /* *sse4_1_zero_extendv4qiv4si2 */
    case 1807:  /* *sse4_1_zero_extendv8qiv8hi2 */
    case 1805:  /* *sse4_1_extendv2siv2di2 */
    case 1803:  /* *sse4_1_extendv2hiv2di2 */
    case 1801:  /* *sse4_1_extendv4hiv4si2 */
    case 1799:  /* *sse4_1_extendv2qiv2di2 */
    case 1797:  /* *sse4_1_extendv4qiv4si2 */
    case 1795:  /* *sse4_1_extendv8qiv8hi2 */
    case 971:  /* mmx_pi2fw */
    case 970:  /* mmx_pf2iw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      break;

    case 1205:  /* sse3_addsubv2df3 */
    case 1204:  /* *avx_addsubv2df3 */
    case 1203:  /* sse3_addsubv4sf3 */
    case 1202:  /* *avx_addsubv4sf3 */
    case 1201:  /* avx_addsubv4df3 */
    case 1200:  /* avx_addsubv8sf3 */
    case 965:  /* mmx_addsubv2sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 1727:  /* ssse3_phsubdv2si3 */
    case 1718:  /* ssse3_phadddv2si3 */
    case 1217:  /* sse3_hsubv2df3 */
    case 1216:  /* sse3_haddv2df3 */
    case 1215:  /* *avx_hsubv2df3 */
    case 1214:  /* *avx_haddv2df3 */
    case 964:  /* mmx_hsubv2sf3 */
    case 963:  /* mmx_haddv2sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 919:  /* *prefetch_sse_rex */
    case 918:  /* *prefetch_sse */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 2));
      break;

    case 917:  /* *sse_prologue_save_insn */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 0), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0), 1));
      break;

    case 1979:  /* vec_set_hi_v32qi */
    case 1977:  /* vec_set_hi_v16hi */
    case 1975:  /* vec_set_hi_v8sf */
    case 1974:  /* vec_set_hi_v8si */
    case 1971:  /* vec_set_hi_v4df */
    case 1970:  /* vec_set_hi_v4di */
    case 1579:  /* *andnottf3 */
    case 1578:  /* sse2_andnotv2di3 */
    case 1577:  /* sse2_andnotv4si3 */
    case 1576:  /* sse2_andnotv8hi3 */
    case 1575:  /* sse2_andnotv16qi3 */
    case 1574:  /* *avx_andnotv2di3 */
    case 1573:  /* *avx_andnotv4si3 */
    case 1572:  /* *avx_andnotv8hi3 */
    case 1571:  /* *avx_andnotv16qi3 */
    case 1570:  /* *sse_andnotv2di3 */
    case 1569:  /* *sse_andnotv4si3 */
    case 1568:  /* *sse_andnotv8hi3 */
    case 1567:  /* *sse_andnotv16qi3 */
    case 1566:  /* *avx_andnotv4di3 */
    case 1565:  /* *avx_andnotv8si3 */
    case 1564:  /* *avx_andnotv16hi3 */
    case 1563:  /* *avx_andnotv32qi3 */
    case 1445:  /* sse2_loadhpd */
    case 1444:  /* *avx_loadhpd */
    case 1388:  /* sse_loadhps */
    case 1387:  /* *avx_loadhps */
    case 1364:  /* *sse2_cvtpd2ps */
    case 1358:  /* *sse2_cvttpd2dq */
    case 1265:  /* *andnotdf3 */
    case 1264:  /* *andnotsf3 */
    case 1263:  /* *avx_andnotdf3 */
    case 1262:  /* *avx_andnotsf3 */
    case 1243:  /* sse2_andnotv2df3 */
    case 1242:  /* sse_andnotv4sf3 */
    case 1241:  /* avx_andnotv4df3 */
    case 1240:  /* avx_andnotv8sf3 */
    case 1239:  /* avx_andnotv2df3 */
    case 1238:  /* avx_andnotv4sf3 */
    case 1151:  /* sse2_vmsqrtv2df2 */
    case 1150:  /* sse_vmsqrtv4sf2 */
    case 1149:  /* *avx_vmsqrtv2df2 */
    case 1148:  /* *avx_vmsqrtv4sf2 */
    case 1020:  /* mmx_andnotv2si3 */
    case 1019:  /* mmx_andnotv4hi3 */
    case 1018:  /* mmx_andnotv8qi3 */
    case 915:  /* *sibcall_value_1_rex64 */
    case 914:  /* *call_value_1_rex64_large */
    case 912:  /* *call_value_1_rex64 */
    case 911:  /* *sibcall_value_1 */
    case 910:  /* *call_value_1 */
    case 908:  /* *call_value_0_rex64 */
    case 907:  /* *call_value_0 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 906:  /* *sibcall_value_pop_1 */
    case 905:  /* *call_value_pop_1 */
    case 904:  /* *call_value_pop_0 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      break;

    case 903:  /* allocate_stack_worker_64 */
    case 902:  /* allocate_stack_worker_32 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 901:  /* pro_epilogue_adjust_stack_rex64_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 876:  /* *movqicc_noc */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 882:  /* *sse5_pcmov_df */
    case 881:  /* *sse5_pcmov_sf */
    case 880:  /* *movxfcc_1 */
    case 879:  /* *movdfcc_1_rex64 */
    case 878:  /* *movdfcc_1 */
    case 877:  /* *movsfcc_1_387 */
    case 875:  /* *movhicc_noc */
    case 874:  /* *movsicc_noc */
    case 871:  /* *movdicc_c_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

    case 868:  /* *strlenqi_rex_1 */
    case 867:  /* *strlenqi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      break;

    case 866:  /* *cmpstrnqi_rex_1 */
    case 865:  /* *cmpstrnqi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 4), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 5), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1), 0));
      ro[6] = *(ro_loc[6] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      break;

    case 864:  /* *cmpstrnqi_nz_rex_1 */
    case 863:  /* *cmpstrnqi_nz_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 4), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 5), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[6] = *(ro_loc[6] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 862:  /* *rep_stosqi_rex64 */
    case 861:  /* *rep_stosqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 4), 0);
      recog_data.dup_num[0] = 4;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 0), 0);
      recog_data.dup_num[1] = 3;
      break;

    case 860:  /* *rep_stossi_rex64 */
    case 859:  /* *rep_stossi */
    case 858:  /* *rep_stosdi_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 4), 0);
      recog_data.dup_num[0] = 4;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 0), 0);
      recog_data.dup_num[1] = 3;
      break;

    case 857:  /* *strsetqi_rex_1 */
    case 856:  /* *strsetqi_1 */
    case 855:  /* *strsethi_rex_1 */
    case 854:  /* *strsethi_1 */
    case 853:  /* *strsetsi_rex_1 */
    case 852:  /* *strsetsi_1 */
    case 851:  /* *strsetdi_rex_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 850:  /* *rep_movqi_rex64 */
    case 849:  /* *rep_movqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 4), 0);
      recog_data.dup_num[0] = 5;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 0), 0);
      recog_data.dup_num[1] = 3;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 1), 0);
      recog_data.dup_num[2] = 4;
      recog_data.dup_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 1);
      recog_data.dup_num[3] = 5;
      break;

    case 848:  /* *rep_movsi_rex64 */
    case 847:  /* *rep_movsi */
    case 846:  /* *rep_movdi_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 1));
      ro[5] = *(ro_loc[5] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 4), 0);
      recog_data.dup_num[0] = 5;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 0), 0);
      recog_data.dup_num[1] = 3;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 1), 0);
      recog_data.dup_num[2] = 4;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0);
      recog_data.dup_num[3] = 5;
      break;

    case 845:  /* *strmovqi_rex_1 */
    case 844:  /* *strmovqi_1 */
    case 843:  /* *strmovhi_rex_1 */
    case 842:  /* *strmovhi_1 */
    case 841:  /* *strmovsi_rex_1 */
    case 840:  /* *strmovsi_1 */
    case 839:  /* *strmovdi_rex_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 824:  /* fistdi2_ceil_with_temp */
    case 813:  /* fistdi2_floor_with_temp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 4), 0));
      break;

    case 828:  /* fistsi2_ceil_with_temp */
    case 827:  /* fisthi2_ceil_with_temp */
    case 823:  /* fistdi2_ceil */
    case 817:  /* fistsi2_floor_with_temp */
    case 816:  /* fisthi2_floor_with_temp */
    case 812:  /* fistdi2_floor */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 831:  /* frndintxf2_mask_pm */
    case 829:  /* frndintxf2_trunc */
    case 822:  /* *fistdi2_ceil_1 */
    case 821:  /* *fistsi2_ceil_1 */
    case 820:  /* *fisthi2_ceil_1 */
    case 818:  /* frndintxf2_ceil */
    case 811:  /* *fistdi2_floor_1 */
    case 810:  /* *fistsi2_floor_1 */
    case 809:  /* *fisthi2_floor_1 */
    case 807:  /* frndintxf2_floor */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      break;

    case 832:  /* frndintxf2_mask_pm_i387 */
    case 830:  /* frndintxf2_trunc_i387 */
    case 826:  /* fistsi2_ceil */
    case 825:  /* fisthi2_ceil */
    case 819:  /* frndintxf2_ceil_i387 */
    case 815:  /* fistsi2_floor */
    case 814:  /* fisthi2_floor */
    case 808:  /* frndintxf2_floor_i387 */
    case 800:  /* fistdi2_with_temp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 925:  /* stack_tls_protect_set_di */
    case 924:  /* stack_tls_protect_set_si */
    case 923:  /* stack_protect_set_di */
    case 922:  /* stack_protect_set_si */
    case 806:  /* fistsi2_with_temp */
    case 805:  /* fisthi2_with_temp */
    case 799:  /* fistdi2 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 1959:  /* avx_vpermilvarv4df3 */
    case 1958:  /* avx_vpermilvarv8sf3 */
    case 1957:  /* avx_vpermilvarv2df3 */
    case 1956:  /* avx_vpermilvarv4sf3 */
    case 1955:  /* avx_vpermilv4df */
    case 1954:  /* avx_vpermilv8sf */
    case 1953:  /* avx_vpermilv2df */
    case 1952:  /* avx_vpermilv4sf */
    case 1946:  /* aeskeygenassist */
    case 1944:  /* aesdeclast */
    case 1943:  /* *avx_aesdeclast */
    case 1942:  /* aesdec */
    case 1941:  /* *avx_aesdec */
    case 1940:  /* aesenclast */
    case 1939:  /* *avx_aesenclast */
    case 1938:  /* aesenc */
    case 1937:  /* *avx_aesenc */
    case 1827:  /* sse4_1_roundpd */
    case 1826:  /* sse4_1_roundps */
    case 1825:  /* avx_roundpd256 */
    case 1824:  /* avx_roundps256 */
    case 1765:  /* sse4a_insertq */
    case 1763:  /* sse4a_extrq */
    case 1748:  /* ssse3_psignv2si3 */
    case 1747:  /* ssse3_psignv4hi3 */
    case 1746:  /* ssse3_psignv8qi3 */
    case 1745:  /* ssse3_psignv4si3 */
    case 1744:  /* ssse3_psignv8hi3 */
    case 1743:  /* ssse3_psignv16qi3 */
    case 1742:  /* *avx_psignv4si3 */
    case 1741:  /* *avx_psignv8hi3 */
    case 1740:  /* *avx_psignv16qi3 */
    case 1739:  /* ssse3_pshufbv8qi3 */
    case 1738:  /* ssse3_pshufbv16qi3 */
    case 1737:  /* *avx_pshufbv16qi3 */
    case 1696:  /* sse2_psadbw */
    case 1695:  /* *avx_psadbw */
    case 1199:  /* *ieee_smaxv2df3 */
    case 1198:  /* *ieee_smaxv4sf3 */
    case 1197:  /* *ieee_sminv2df3 */
    case 1196:  /* *ieee_sminv4sf3 */
    case 1195:  /* *avx_ieee_smaxv4df3 */
    case 1194:  /* *avx_ieee_smaxv8sf3 */
    case 1193:  /* *avx_ieee_smaxv2df3 */
    case 1192:  /* *avx_ieee_smaxv4sf3 */
    case 1191:  /* *avx_ieee_sminv4df3 */
    case 1190:  /* *avx_ieee_sminv8sf3 */
    case 1189:  /* *avx_ieee_sminv2df3 */
    case 1188:  /* *avx_ieee_sminv4sf3 */
    case 1050:  /* mmx_psadbw */
    case 962:  /* mmx_rsqit1v2sf3 */
    case 960:  /* mmx_rcpit2v2sf3 */
    case 959:  /* mmx_rcpit1v2sf3 */
    case 933:  /* sse4_2_crc32di */
    case 932:  /* sse4_2_crc32si */
    case 931:  /* sse4_2_crc32hi */
    case 930:  /* sse4_2_crc32qi */
    case 898:  /* *ieee_smaxdf3 */
    case 897:  /* *ieee_smaxsf3 */
    case 896:  /* *avx_ieee_smaxdf3 */
    case 895:  /* *avx_ieee_smaxsf3 */
    case 894:  /* *ieee_smindf3 */
    case 893:  /* *ieee_sminsf3 */
    case 892:  /* *avx_ieee_smindf3 */
    case 891:  /* *avx_ieee_sminsf3 */
    case 796:  /* sse4_1_rounddf2 */
    case 795:  /* sse4_1_roundsf2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      break;

    case 794:  /* *fscalexf4_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[1] = 2;
      break;

    case 789:  /* fyl2xp1_extenddfxf3_i387 */
    case 788:  /* fyl2xp1_extendsfxf3_i387 */
    case 786:  /* fyl2x_extenddfxf3_i387 */
    case 785:  /* fyl2x_extendsfxf3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 783:  /* fpatan_extenddfxf3_i387 */
    case 782:  /* fpatan_extendsfxf3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 929:  /* stack_tls_protect_test_di */
    case 928:  /* stack_tls_protect_test_si */
    case 927:  /* stack_protect_test_di */
    case 926:  /* stack_protect_test_si */
    case 787:  /* fyl2xp1xf3_i387 */
    case 784:  /* fyl2xxf3_i387 */
    case 781:  /* *fpatanxf3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 780:  /* fptan_extenddfxf4_i387 */
    case 779:  /* fptan_extendsfxf4_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 778:  /* fptanxf4_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 792:  /* fxtract_extenddfxf3_i387 */
    case 791:  /* fxtract_extendsfxf3_i387 */
    case 777:  /* sincos_extenddfxf3_i387 */
    case 776:  /* sincos_extendsfxf3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 0);
      recog_data.dup_num[0] = 2;
      break;

    case 790:  /* fxtractxf3_i387 */
    case 775:  /* sincosxf3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[0] = 2;
      break;

    case 768:  /* fprem1xf4_i387 */
    case 767:  /* fpremxf4_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[2] = 3;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[3] = 2;
      break;

    case 758:  /* *fop_xf_6_i387 */
    case 757:  /* *fop_xf_6_i387 */
    case 746:  /* *fop_df_6_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 756:  /* *fop_xf_5_i387 */
    case 755:  /* *fop_xf_5_i387 */
    case 752:  /* *fop_xf_3_i387 */
    case 751:  /* *fop_xf_3_i387 */
    case 745:  /* *fop_df_5_i387 */
    case 743:  /* *fop_df_3_i387 */
    case 742:  /* *fop_sf_3_i387 */
    case 741:  /* *fop_df_3_i387 */
    case 740:  /* *fop_sf_3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 754:  /* *fop_xf_4_i387 */
    case 753:  /* *fop_xf_4_i387 */
    case 750:  /* *fop_xf_2_i387 */
    case 749:  /* *fop_xf_2_i387 */
    case 744:  /* *fop_df_4_i387 */
    case 739:  /* *fop_df_2_i387 */
    case 738:  /* *fop_sf_2_i387 */
    case 737:  /* *fop_df_2_i387 */
    case 736:  /* *fop_sf_2_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 1231:  /* sse2_maskcmpv2df3 */
    case 1230:  /* sse_maskcmpv4sf3 */
    case 1229:  /* sse2_maskcmpdf3 */
    case 1228:  /* sse_maskcmpsf3 */
    case 1227:  /* *avx_maskcmpv4df3 */
    case 1226:  /* *avx_maskcmpv8sf3 */
    case 1225:  /* *avx_maskcmpv2df3 */
    case 1224:  /* *avx_maskcmpv4sf3 */
    case 748:  /* *fop_xf_1_i387 */
    case 747:  /* *fop_xf_comm_i387 */
    case 735:  /* *fop_df_1_i387 */
    case 734:  /* *fop_sf_1_i387 */
    case 733:  /* *fop_df_1_sse */
    case 732:  /* *fop_sf_1_sse */
    case 731:  /* *fop_df_1_avx */
    case 730:  /* *fop_sf_1_avx */
    case 728:  /* *fop_df_1_mixed */
    case 727:  /* *fop_sf_1_mixed */
    case 726:  /* *fop_df_1_mixed_avx */
    case 725:  /* *fop_sf_1_mixed_avx */
    case 724:  /* *fop_df_comm_i387 */
    case 723:  /* *fop_sf_comm_i387 */
    case 722:  /* *fop_df_comm_sse */
    case 721:  /* *fop_sf_comm_sse */
    case 720:  /* *fop_df_comm_avx */
    case 719:  /* *fop_sf_comm_avx */
    case 718:  /* *fop_df_comm_mixed */
    case 717:  /* *fop_sf_comm_mixed */
    case 716:  /* *fop_df_comm_mixed_avx */
    case 715:  /* *fop_sf_comm_mixed_avx */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 714:  /* *tls_dynamic_gnu2_combine_64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1));
      break;

    case 713:  /* *tls_dynamic_call_64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      break;

    case 1993:  /* avx_pd_pd256 */
    case 1992:  /* avx_ps_ps256 */
    case 1991:  /* avx_si_si256 */
    case 1990:  /* avx_pd256_pd */
    case 1989:  /* avx_ps256_ps */
    case 1988:  /* avx_si256_si */
    case 1945:  /* aesimc */
    case 1914:  /* sse5_cvtps2ph */
    case 1913:  /* sse5_cvtph2ps */
    case 1910:  /* sse5_frczv2df2 */
    case 1909:  /* sse5_frczv4sf2 */
    case 1793:  /* sse4_1_phminposuw */
    case 1784:  /* sse4_1_movntdqa */
    case 1759:  /* sse4a_movntdf */
    case 1758:  /* sse4a_movntsf */
    case 1701:  /* sse2_pmovmskb */
    case 1700:  /* sse2_movmskpd */
    case 1699:  /* sse_movmskps */
    case 1698:  /* avx_movmskpd256 */
    case 1697:  /* avx_movmskps256 */
    case 1355:  /* avx_cvtpd2dq256 */
    case 1350:  /* sse2_cvtsd2siq_2 */
    case 1348:  /* sse2_cvtsd2si_2 */
    case 1341:  /* sse2_cvtpd2pi */
    case 1336:  /* sse2_cvtps2dq */
    case 1335:  /* avx_cvtps2dq256 */
    case 1334:  /* avx_cvtps2dq */
    case 1328:  /* sse_cvtss2siq_2 */
    case 1326:  /* sse_cvtss2si_2 */
    case 1153:  /* sse_rsqrtv4sf2 */
    case 1152:  /* avx_rsqrtv8sf2 */
    case 1141:  /* sse_rcpv4sf2 */
    case 1140:  /* avx_rcpv8sf2 */
    case 1097:  /* sse3_lddqu */
    case 1096:  /* avx_lddqu */
    case 1095:  /* avx_lddqu256 */
    case 1094:  /* sse2_movntsi */
    case 1093:  /* sse2_movntv2di */
    case 1092:  /* avx_movntv2di */
    case 1091:  /* avx_movntv4di */
    case 1090:  /* sse2_movntv2df */
    case 1089:  /* sse_movntv4sf */
    case 1088:  /* avx_movntv4df */
    case 1087:  /* avx_movntv8sf */
    case 1086:  /* avx_movntv2df */
    case 1085:  /* avx_movntv4sf */
    case 1084:  /* sse2_movdqu */
    case 1083:  /* avx_movdqu */
    case 1082:  /* avx_movdqu256 */
    case 1081:  /* sse2_movupd */
    case 1080:  /* sse_movups */
    case 1078:  /* avx_movupd256 */
    case 1077:  /* avx_movups256 */
    case 1076:  /* avx_movupd */
    case 1075:  /* avx_movups */
    case 1051:  /* mmx_pmovmskb */
    case 961:  /* mmx_rsqrtv2sf2 */
    case 958:  /* mmx_rcpv2sf2 */
    case 950:  /* sse_movntdi */
    case 837:  /* fxamdf2_i387_with_temp */
    case 836:  /* fxamsf2_i387_with_temp */
    case 835:  /* fxamxf2_i387 */
    case 834:  /* fxamdf2_i387 */
    case 833:  /* fxamsf2_i387 */
    case 804:  /* fistsi2 */
    case 803:  /* fisthi2 */
    case 802:  /* *fistsi2_1 */
    case 801:  /* *fisthi2_1 */
    case 798:  /* *fistdi2_1 */
    case 797:  /* rintxf2 */
    case 793:  /* *f2xm1xf2_i387 */
    case 772:  /* *cosxf2_i387 */
    case 769:  /* *sinxf2_i387 */
    case 764:  /* *rsqrtsf2_sse */
    case 760:  /* truncxfdf2_i387_noop_unspec */
    case 759:  /* truncxfsf2_i387_noop_unspec */
    case 729:  /* *rcpsf2_sse */
    case 712:  /* *tls_dynamic_lea_64 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      break;

    case 711:  /* *tls_dynamic_gnu2_combine_32 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 2));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1));
      break;

    case 710:  /* *tls_dynamic_call_32 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      break;

    case 709:  /* *tls_dynamic_lea_32 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0, 0));
      break;

    case 708:  /* *add_tp_di */
    case 706:  /* *add_tp_si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 704:  /* *tls_local_dynamic_32_once */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0, 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 702:  /* *tls_local_dynamic_base_32_sun */
    case 701:  /* *tls_local_dynamic_base_32_gnu */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 700:  /* *tls_global_dynamic_64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XVECEXP (pat, 0, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 699:  /* *tls_global_dynamic_32_sun */
    case 698:  /* *tls_global_dynamic_32_gnu */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 696:  /* *parityhi2_cmp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      break;

    case 695:  /* paritysi2_cmp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      break;

    case 694:  /* paritydi2_cmp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      break;

    case 688:  /* bswaphi_lowpart */
    case 687:  /* *bswaphi_lowpart_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 693:  /* *bsrhi */
    case 691:  /* *bsr_rex64 */
    case 678:  /* *bsr */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 674:  /* *ffsdi_1 */
    case 673:  /* *ffssi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 1761:  /* sse4a_vmmovntv2df */
    case 1760:  /* sse4a_vmmovntv4sf */
    case 1349:  /* sse2_cvtsd2siq */
    case 1347:  /* sse2_cvtsd2si */
    case 1327:  /* sse_cvtss2siq */
    case 1325:  /* sse_cvtss2si */
    case 774:  /* *cos_extenddfxf2_i387 */
    case 773:  /* *cos_extendsfxf2_i387 */
    case 771:  /* *sin_extenddfxf2_i387 */
    case 770:  /* *sin_extendsfxf2_i387 */
    case 667:  /* set_got_offset_rex64 */
    case 666:  /* set_rip_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      break;

    case 664:  /* set_got_labelled */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      break;

    case 660:  /* return_indirect_internal */
    case 659:  /* return_pop_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 1707:  /* sse2_clflush */
    case 1704:  /* sse_ldmxcsr */
    case 662:  /* align */
    case 656:  /* prologue_use */
      ro[0] = *(ro_loc[0] = &XVECEXP (pat, 0, 0));
      break;

    case 1709:  /* *sse2_lfence */
    case 1708:  /* *sse2_mfence */
    case 1706:  /* *sse_sfence */
    case 655:  /* *memory_blockage */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0);
      recog_data.dup_num[0] = 0;
      break;

    case 1951:  /* avx_vzeroupper_rex64 */
    case 1950:  /* avx_vzeroupper */
    case 1055:  /* mmx_femms */
    case 1054:  /* mmx_emms */
    case 916:  /* trap */
    case 838:  /* cld */
    case 671:  /* leave_rex64 */
    case 670:  /* leave */
    case 661:  /* nop */
    case 658:  /* return_internal_long */
    case 657:  /* return_internal */
    case 654:  /* blockage */
      break;

    case 646:  /* *sibcall_pop_1 */
    case 645:  /* *call_pop_1 */
    case 644:  /* *call_pop_0 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      break;

    case 643:  /* *tablejump_1 */
    case 642:  /* *tablejump_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 0), 0));
      break;

    case 641:  /* *indirect_jump */
    case 640:  /* *indirect_jump */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 1));
      break;

    case 697:  /* *parityqi2_cmp */
    case 639:  /* jump */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 638:  /* *fp_jcc_8si_387 */
    case 637:  /* *fp_jcc_8hi_387 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 635:  /* *fp_jcc_6_387 */
    case 633:  /* *fp_jcc_4_387 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 636:  /* *fp_jcc_7_387 */
    case 634:  /* *fp_jcc_5_387 */
    case 632:  /* *fp_jcc_3_387 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 631:  /* *fp_jcc_2_387 */
    case 630:  /* *fp_jcc_2_sse */
    case 629:  /* *fp_jcc_2_mixed */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 2), 0));
      break;

    case 628:  /* *fp_jcc_1_387 */
    case 627:  /* *fp_jcc_1_sse */
    case 626:  /* *fp_jcc_1_mixed */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 625:  /* *jcc_btsi_mask_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 1), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 624:  /* *jcc_btsi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 623:  /* *jcc_btsi_mask */
    case 621:  /* *jcc_btdi_mask_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 2), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 2), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 622:  /* *jcc_btsi */
    case 620:  /* *jcc_btdi_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 2), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 619:  /* *jcc_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 2), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 618:  /* *jcc_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1928:  /* sse5_maskcmp_unsv2di3 */
    case 1927:  /* sse5_maskcmp_unsv4si3 */
    case 1926:  /* sse5_maskcmp_unsv8hi3 */
    case 1925:  /* sse5_maskcmp_unsv16qi3 */
    case 1924:  /* sse5_maskcmpv2di3 */
    case 1923:  /* sse5_maskcmpv4si3 */
    case 1922:  /* sse5_maskcmpv8hi3 */
    case 1921:  /* sse5_maskcmpv16qi3 */
    case 1920:  /* sse5_maskcmpv2df3 */
    case 1919:  /* sse5_maskcmpv4sf3 */
    case 617:  /* *sse5_setccdf */
    case 616:  /* *sse5_setccsf */
    case 615:  /* *sse_setccdf */
    case 614:  /* *sse_setccsf */
    case 613:  /* *avx_setccdf */
    case 612:  /* *avx_setccsf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 609:  /* *btsi */
    case 608:  /* *btdi_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      break;

    case 607:  /* *btcq */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 2));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0);
      recog_data.dup_num[0] = 0;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 2);
      recog_data.dup_num[1] = 1;
      break;

    case 606:  /* *btrq */
    case 605:  /* *btsq */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 2));
      break;

    case 592:  /* ix86_rotrdi3 */
    case 579:  /* ix86_rotldi3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 518:  /* x86_shrd */
    case 509:  /* x86_64_shrd */
    case 494:  /* x86_shld */
    case 489:  /* x86_64_shld */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0);
      recog_data.dup_num[0] = 0;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 1999:  /* *vec_concatv4df_avx */
    case 1998:  /* *vec_concatv8sf_avx */
    case 1997:  /* *vec_concatv4di_avx */
    case 1996:  /* *vec_concatv8si_avx */
    case 1995:  /* *vec_concatv16hi_avx */
    case 1994:  /* *vec_concatv32qi_avx */
    case 1896:  /* sse5_rotrv2di3 */
    case 1895:  /* sse5_rotrv4si3 */
    case 1894:  /* sse5_rotrv8hi3 */
    case 1893:  /* sse5_rotrv16qi3 */
    case 1892:  /* sse5_rotlv2di3 */
    case 1891:  /* sse5_rotlv4si3 */
    case 1890:  /* sse5_rotlv8hi3 */
    case 1889:  /* sse5_rotlv16qi3 */
    case 1690:  /* *vec_concatv2di_rex64_sse */
    case 1689:  /* *vec_concatv2di_rex64_sse4_1 */
    case 1688:  /* *vec_concatv2di_rex64_avx */
    case 1687:  /* vec_concatv2di */
    case 1686:  /* *vec_concatv2di_avx */
    case 1685:  /* *vec_concatv4si_1 */
    case 1684:  /* *vec_concatv4si_1_avx */
    case 1683:  /* *vec_concatv2si_sse */
    case 1682:  /* *vec_concatv2si_sse2 */
    case 1681:  /* *vec_concatv2si_sse4_1 */
    case 1680:  /* *vec_concatv2si_avx */
    case 1630:  /* *xortf3 */
    case 1629:  /* *iortf3 */
    case 1628:  /* *andtf3 */
    case 1627:  /* *sse2_xorv2di3 */
    case 1626:  /* *sse2_iorv2di3 */
    case 1625:  /* *sse2_andv2di3 */
    case 1624:  /* *sse2_xorv4si3 */
    case 1623:  /* *sse2_iorv4si3 */
    case 1622:  /* *sse2_andv4si3 */
    case 1621:  /* *sse2_xorv8hi3 */
    case 1620:  /* *sse2_iorv8hi3 */
    case 1619:  /* *sse2_andv8hi3 */
    case 1618:  /* *sse2_xorv16qi3 */
    case 1617:  /* *sse2_iorv16qi3 */
    case 1616:  /* *sse2_andv16qi3 */
    case 1615:  /* *avx_xorv2di3 */
    case 1614:  /* *avx_iorv2di3 */
    case 1613:  /* *avx_andv2di3 */
    case 1612:  /* *avx_xorv4si3 */
    case 1611:  /* *avx_iorv4si3 */
    case 1610:  /* *avx_andv4si3 */
    case 1609:  /* *avx_xorv8hi3 */
    case 1608:  /* *avx_iorv8hi3 */
    case 1607:  /* *avx_andv8hi3 */
    case 1606:  /* *avx_xorv16qi3 */
    case 1605:  /* *avx_iorv16qi3 */
    case 1604:  /* *avx_andv16qi3 */
    case 1603:  /* *sse_xorv2di3 */
    case 1602:  /* *sse_iorv2di3 */
    case 1601:  /* *sse_andv2di3 */
    case 1600:  /* *sse_xorv4si3 */
    case 1599:  /* *sse_iorv4si3 */
    case 1598:  /* *sse_andv4si3 */
    case 1597:  /* *sse_xorv8hi3 */
    case 1596:  /* *sse_iorv8hi3 */
    case 1595:  /* *sse_andv8hi3 */
    case 1594:  /* *sse_xorv16qi3 */
    case 1593:  /* *sse_iorv16qi3 */
    case 1592:  /* *sse_andv16qi3 */
    case 1591:  /* *avx_xorv4di3 */
    case 1590:  /* *avx_iorv4di3 */
    case 1589:  /* *avx_andv4di3 */
    case 1588:  /* *avx_xorv8si3 */
    case 1587:  /* *avx_iorv8si3 */
    case 1586:  /* *avx_andv8si3 */
    case 1585:  /* *avx_xorv16hi3 */
    case 1584:  /* *avx_iorv16hi3 */
    case 1583:  /* *avx_andv16hi3 */
    case 1582:  /* *avx_xorv32qi3 */
    case 1581:  /* *avx_iorv32qi3 */
    case 1580:  /* *avx_andv32qi3 */
    case 1562:  /* sse4_2_gtv2di3 */
    case 1561:  /* sse2_gtv4si3 */
    case 1560:  /* sse2_gtv8hi3 */
    case 1559:  /* sse2_gtv16qi3 */
    case 1558:  /* *avx_gtv2di3 */
    case 1557:  /* *avx_gtv4si3 */
    case 1556:  /* *avx_gtv8hi3 */
    case 1555:  /* *avx_gtv16qi3 */
    case 1554:  /* *sse4_1_eqv2di3 */
    case 1553:  /* *sse2_eqv4si3 */
    case 1552:  /* *sse2_eqv8hi3 */
    case 1551:  /* *sse2_eqv16qi3 */
    case 1550:  /* *avx_eqv2di3 */
    case 1549:  /* *avx_eqv4si3 */
    case 1548:  /* *avx_eqv8hi3 */
    case 1547:  /* *avx_eqv16qi3 */
    case 1546:  /* *sse4_1_uminv4si3 */
    case 1545:  /* *sse4_1_umaxv4si3 */
    case 1544:  /* *sse4_1_uminv8hi3 */
    case 1543:  /* *sse4_1_umaxv8hi3 */
    case 1542:  /* *sse4_1_sminv4si3 */
    case 1541:  /* *sse4_1_smaxv4si3 */
    case 1540:  /* *sse4_1_sminv16qi3 */
    case 1539:  /* *sse4_1_smaxv16qi3 */
    case 1538:  /* *sminv8hi3 */
    case 1537:  /* *smaxv8hi3 */
    case 1536:  /* *uminv16qi3 */
    case 1535:  /* *umaxv16qi3 */
    case 1534:  /* *avx_uminv4si3 */
    case 1533:  /* *avx_umaxv4si3 */
    case 1532:  /* *avx_sminv4si3 */
    case 1531:  /* *avx_smaxv4si3 */
    case 1530:  /* *avx_uminv8hi3 */
    case 1529:  /* *avx_umaxv8hi3 */
    case 1528:  /* *avx_sminv8hi3 */
    case 1527:  /* *avx_smaxv8hi3 */
    case 1526:  /* *avx_uminv16qi3 */
    case 1525:  /* *avx_umaxv16qi3 */
    case 1524:  /* *avx_sminv16qi3 */
    case 1523:  /* *avx_smaxv16qi3 */
    case 1522:  /* ashlv2di3 */
    case 1521:  /* ashlv4si3 */
    case 1520:  /* ashlv8hi3 */
    case 1519:  /* *avx_ashlv2di3 */
    case 1518:  /* *avx_ashlv4si3 */
    case 1517:  /* *avx_ashlv8hi3 */
    case 1516:  /* lshrv2di3 */
    case 1515:  /* lshrv4si3 */
    case 1514:  /* lshrv8hi3 */
    case 1513:  /* *avx_lshrv2di3 */
    case 1512:  /* *avx_lshrv4si3 */
    case 1511:  /* *avx_lshrv8hi3 */
    case 1510:  /* ashrv4si3 */
    case 1509:  /* ashrv8hi3 */
    case 1508:  /* *avx_ashrv4si3 */
    case 1507:  /* *avx_ashrv8hi3 */
    case 1506:  /* mulv2di3 */
    case 1505:  /* *sse2_mulv4si3 */
    case 1504:  /* *sse5_mulv4si3 */
    case 1503:  /* *sse4_1_mulv4si3 */
    case 1502:  /* *avx_mulv4si3 */
    case 1491:  /* *mulv8hi3 */
    case 1490:  /* *avx_mulv8hi3 */
    case 1489:  /* mulv16qi3 */
    case 1488:  /* *sse2_ussubv8hi3 */
    case 1487:  /* *sse2_sssubv8hi3 */
    case 1486:  /* *sse2_usaddv8hi3 */
    case 1485:  /* *sse2_ssaddv8hi3 */
    case 1484:  /* *sse2_ussubv16qi3 */
    case 1483:  /* *sse2_sssubv16qi3 */
    case 1482:  /* *sse2_usaddv16qi3 */
    case 1481:  /* *sse2_ssaddv16qi3 */
    case 1480:  /* *avx_ussubv8hi3 */
    case 1479:  /* *avx_sssubv8hi3 */
    case 1478:  /* *avx_usaddv8hi3 */
    case 1477:  /* *avx_ssaddv8hi3 */
    case 1476:  /* *avx_ussubv16qi3 */
    case 1475:  /* *avx_sssubv16qi3 */
    case 1474:  /* *avx_usaddv16qi3 */
    case 1473:  /* *avx_ssaddv16qi3 */
    case 1472:  /* *subv2di3 */
    case 1471:  /* *addv2di3 */
    case 1470:  /* *subv4si3 */
    case 1469:  /* *addv4si3 */
    case 1468:  /* *subv8hi3 */
    case 1467:  /* *addv8hi3 */
    case 1466:  /* *subv16qi3 */
    case 1465:  /* *addv16qi3 */
    case 1464:  /* *avx_subv2di3 */
    case 1463:  /* *avx_addv2di3 */
    case 1462:  /* *avx_subv4si3 */
    case 1461:  /* *avx_addv4si3 */
    case 1460:  /* *avx_subv8hi3 */
    case 1459:  /* *avx_addv8hi3 */
    case 1458:  /* *avx_subv16qi3 */
    case 1457:  /* *avx_addv16qi3 */
    case 1456:  /* *vec_concatv2df */
    case 1455:  /* *vec_concatv2df_avx */
    case 1401:  /* *vec_concatv4sf_sse */
    case 1400:  /* *vec_concatv4sf_avx */
    case 1399:  /* *vec_concatv2sf_sse */
    case 1398:  /* *vec_concatv2sf_sse4_1 */
    case 1397:  /* *vec_concatv2sf_avx */
    case 1277:  /* *xordf3 */
    case 1276:  /* *iordf3 */
    case 1275:  /* *anddf3 */
    case 1274:  /* *xorsf3 */
    case 1273:  /* *iorsf3 */
    case 1272:  /* *andsf3 */
    case 1271:  /* *avx_xordf3 */
    case 1270:  /* *avx_iordf3 */
    case 1269:  /* *avx_anddf3 */
    case 1268:  /* *avx_xorsf3 */
    case 1267:  /* *avx_iorsf3 */
    case 1266:  /* *avx_andsf3 */
    case 1261:  /* *xorv2df3 */
    case 1260:  /* *iorv2df3 */
    case 1259:  /* *andv2df3 */
    case 1258:  /* *xorv4sf3 */
    case 1257:  /* *iorv4sf3 */
    case 1256:  /* *andv4sf3 */
    case 1255:  /* *avx_xorv4df3 */
    case 1254:  /* *avx_iorv4df3 */
    case 1253:  /* *avx_andv4df3 */
    case 1252:  /* *avx_xorv8sf3 */
    case 1251:  /* *avx_iorv8sf3 */
    case 1250:  /* *avx_andv8sf3 */
    case 1249:  /* *avx_xorv2df3 */
    case 1248:  /* *avx_iorv2df3 */
    case 1247:  /* *avx_andv2df3 */
    case 1246:  /* *avx_xorv4sf3 */
    case 1245:  /* *avx_iorv4sf3 */
    case 1244:  /* *avx_andv4sf3 */
    case 1179:  /* *sminv2df3 */
    case 1178:  /* *smaxv2df3 */
    case 1177:  /* *sminv4sf3 */
    case 1176:  /* *smaxv4sf3 */
    case 1175:  /* *avx_sminv4df3 */
    case 1174:  /* *avx_smaxv4df3 */
    case 1173:  /* *avx_sminv8sf3 */
    case 1172:  /* *avx_smaxv8sf3 */
    case 1171:  /* *avx_sminv2df3 */
    case 1170:  /* *avx_smaxv2df3 */
    case 1169:  /* *avx_sminv4sf3 */
    case 1168:  /* *avx_smaxv4sf3 */
    case 1167:  /* *sminv2df3_finite */
    case 1166:  /* *smaxv2df3_finite */
    case 1165:  /* *sminv4sf3_finite */
    case 1164:  /* *smaxv4sf3_finite */
    case 1163:  /* *avx_sminv4df3_finite */
    case 1162:  /* *avx_smaxv4df3_finite */
    case 1161:  /* *avx_sminv8sf3_finite */
    case 1160:  /* *avx_smaxv8sf3_finite */
    case 1159:  /* *avx_sminv2df3_finite */
    case 1158:  /* *avx_smaxv2df3_finite */
    case 1157:  /* *avx_sminv4sf3_finite */
    case 1156:  /* *avx_smaxv4sf3_finite */
    case 1135:  /* sse2_divv2df3 */
    case 1134:  /* sse_divv4sf3 */
    case 1133:  /* *avx_divv2df3 */
    case 1132:  /* *avx_divv4sf3 */
    case 1131:  /* avx_divv4df3 */
    case 1130:  /* avx_divv8sf3 */
    case 1129:  /* avx_divv2df3 */
    case 1128:  /* avx_divv4sf3 */
    case 1123:  /* *mulv2df3 */
    case 1122:  /* *mulv4sf3 */
    case 1121:  /* *avx_mulv4df3 */
    case 1120:  /* *avx_mulv8sf3 */
    case 1119:  /* *avx_mulv2df3 */
    case 1118:  /* *avx_mulv4sf3 */
    case 1109:  /* *subv2df3 */
    case 1108:  /* *addv2df3 */
    case 1107:  /* *subv4sf3 */
    case 1106:  /* *addv4sf3 */
    case 1105:  /* *avx_subv4df3 */
    case 1104:  /* *avx_addv4df3 */
    case 1103:  /* *avx_subv8sf3 */
    case 1102:  /* *avx_addv8sf3 */
    case 1101:  /* *avx_subv2df3 */
    case 1100:  /* *avx_addv2df3 */
    case 1099:  /* *avx_subv4sf3 */
    case 1098:  /* *avx_addv4sf3 */
    case 1045:  /* *mmx_concatv2si */
    case 1029:  /* *mmx_xorv2si3 */
    case 1028:  /* *mmx_iorv2si3 */
    case 1027:  /* *mmx_andv2si3 */
    case 1026:  /* *mmx_xorv4hi3 */
    case 1025:  /* *mmx_iorv4hi3 */
    case 1024:  /* *mmx_andv4hi3 */
    case 1023:  /* *mmx_xorv8qi3 */
    case 1022:  /* *mmx_iorv8qi3 */
    case 1021:  /* *mmx_andv8qi3 */
    case 1017:  /* mmx_gtv2si3 */
    case 1016:  /* mmx_gtv4hi3 */
    case 1015:  /* mmx_gtv8qi3 */
    case 1014:  /* *mmx_eqv2si3 */
    case 1013:  /* *mmx_eqv4hi3 */
    case 1012:  /* *mmx_eqv8qi3 */
    case 1011:  /* mmx_ashlv1di3 */
    case 1010:  /* mmx_ashlv2si3 */
    case 1009:  /* mmx_ashlv4hi3 */
    case 1008:  /* mmx_lshrv1di3 */
    case 1007:  /* mmx_lshrv2si3 */
    case 1006:  /* mmx_lshrv4hi3 */
    case 1005:  /* mmx_ashrv2si3 */
    case 1004:  /* mmx_ashrv4hi3 */
    case 1003:  /* *mmx_uminv8qi3 */
    case 1002:  /* *mmx_umaxv8qi3 */
    case 1001:  /* *mmx_sminv4hi3 */
    case 1000:  /* *mmx_smaxv4hi3 */
    case 994:  /* *mmx_mulv4hi3 */
    case 993:  /* *mmx_ussubv4hi3 */
    case 992:  /* *mmx_sssubv4hi3 */
    case 991:  /* *mmx_usaddv4hi3 */
    case 990:  /* *mmx_ssaddv4hi3 */
    case 989:  /* *mmx_ussubv8qi3 */
    case 988:  /* *mmx_sssubv8qi3 */
    case 987:  /* *mmx_usaddv8qi3 */
    case 986:  /* *mmx_ssaddv8qi3 */
    case 985:  /* *mmx_subv1di3 */
    case 984:  /* *mmx_addv1di3 */
    case 983:  /* *mmx_subv2si3 */
    case 982:  /* *mmx_addv2si3 */
    case 981:  /* *mmx_subv4hi3 */
    case 980:  /* *mmx_addv4hi3 */
    case 979:  /* *mmx_subv8qi3 */
    case 978:  /* *mmx_addv8qi3 */
    case 975:  /* *mmx_concatv2sf */
    case 968:  /* mmx_gev2sf3 */
    case 967:  /* mmx_gtv2sf3 */
    case 966:  /* *mmx_eqv2sf3 */
    case 957:  /* *mmx_sminv2sf3 */
    case 956:  /* *mmx_smaxv2sf3 */
    case 955:  /* *mmx_sminv2sf3_finite */
    case 954:  /* *mmx_smaxv2sf3_finite */
    case 953:  /* *mmx_mulv2sf3 */
    case 952:  /* *mmx_subv2sf3 */
    case 951:  /* *mmx_addv2sf3 */
    case 890:  /* smindf3 */
    case 889:  /* smaxdf3 */
    case 888:  /* sminsf3 */
    case 887:  /* smaxsf3 */
    case 886:  /* *avx_smindf3 */
    case 885:  /* *avx_smaxdf3 */
    case 884:  /* *avx_sminsf3 */
    case 883:  /* *avx_smaxsf3 */
    case 546:  /* sse2_lshrti3 */
    case 545:  /* *avx_lshrti3 */
    case 487:  /* sse2_ashlti3 */
    case 486:  /* *avx_ashlti3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 685:  /* *popcountsi2_cmp_zext */
    case 481:  /* *one_cmplsi2_2_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 475:  /* copysigntf3_var */
    case 474:  /* copysigndf3_var */
    case 473:  /* copysignsf3_var */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      break;

    case 1962:  /* avx_vperm2f128v4df3 */
    case 1961:  /* avx_vperm2f128v8sf3 */
    case 1960:  /* avx_vperm2f128v8si3 */
    case 1948:  /* pclmulqdq */
    case 1947:  /* *vpclmulqdq */
    case 1936:  /* sse5_pcom_tfv2di3 */
    case 1935:  /* sse5_pcom_tfv4si3 */
    case 1934:  /* sse5_pcom_tfv8hi3 */
    case 1933:  /* sse5_pcom_tfv16qi3 */
    case 1918:  /* sse5_com_tfv2df3 */
    case 1917:  /* sse5_com_tfv4sf3 */
    case 1888:  /* sse5_permv2df */
    case 1887:  /* sse5_permv4sf */
    case 1877:  /* sse5_pperm */
    case 1790:  /* sse4_1_pblendvb */
    case 1789:  /* *avx_pblendvb */
    case 1786:  /* sse4_1_mpsadbw */
    case 1785:  /* *avx_mpsadbw */
    case 1783:  /* sse4_1_dppd */
    case 1782:  /* sse4_1_dpps */
    case 1781:  /* avx_dppd256 */
    case 1780:  /* avx_dpps256 */
    case 1779:  /* avx_dppd */
    case 1778:  /* avx_dpps */
    case 1777:  /* sse4_1_blendvpd */
    case 1776:  /* sse4_1_blendvps */
    case 1773:  /* avx_blendvpd256 */
    case 1772:  /* avx_blendvps256 */
    case 1771:  /* avx_blendvpd */
    case 1770:  /* avx_blendvps */
    case 1762:  /* sse4a_extrqi */
    case 1751:  /* ssse3_palignrdi */
    case 1750:  /* ssse3_palignrti */
    case 1749:  /* *avx_palignrti */
    case 1221:  /* avx_cmppdv4df3 */
    case 1220:  /* avx_cmppsv8sf3 */
    case 1219:  /* avx_cmppdv2df3 */
    case 1218:  /* avx_cmppsv4sf3 */
    case 472:  /* copysigntf3_const */
    case 471:  /* copysigndf3_const */
    case 470:  /* copysignsf3_const */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (pat, 1), 0, 2));
      break;

    case 457:  /* *absnegtf2_sse */
    case 456:  /* *absnegxf2_i387 */
    case 455:  /* *absnegdf2_i387 */
    case 454:  /* *absnegsf2_i387 */
    case 453:  /* *absnegdf2_sse */
    case 452:  /* *absnegsf2_sse */
    case 451:  /* *absnegdf2_mixed */
    case 450:  /* *absnegsf2_mixed */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 445:  /* *negsi2_cmpz_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 443:  /* *negsi2_1_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      break;

    case 684:  /* *popcountdi2_cmp */
    case 683:  /* *popcountsi2_cmp */
    case 682:  /* *popcounthi2_cmp */
    case 485:  /* *one_cmplqi2_2 */
    case 483:  /* *one_cmplhi2_2 */
    case 480:  /* *one_cmplsi2_2 */
    case 477:  /* *one_cmpldi2_2_rex64 */
    case 449:  /* *negqi2_cmpz */
    case 447:  /* *neghi2_cmpz */
    case 444:  /* *negsi2_cmpz */
    case 441:  /* *negdi2_cmpz_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 564:  /* *lshrsi3_cmp_zext */
    case 561:  /* *lshrsi3_cmp_one_bit_zext */
    case 422:  /* *xorsi_2_zext_imm */
    case 400:  /* *iorsi_2_zext_imm */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 913:  /* *call_value_1_rex64_ms_sysv */
    case 909:  /* *call_value_0_rex64_ms_sysv */
    case 703:  /* *tls_local_dynamic_base_64 */
    case 556:  /* *lshrsi3_1_one_bit_zext */
    case 419:  /* *xorsi_1_zext_imm */
    case 397:  /* *iorsi_1_zext_imm */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 437:  /* *xorqi_cc_ext_1_rex64 */
    case 436:  /* *xorqi_cc_ext_1 */
    case 388:  /* *andqi_ext_0_cc */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 434:  /* *xorqi_2_slp */
    case 408:  /* *iorqi_2_slp */
    case 386:  /* *andqi_2_slp */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 0), 0);
      recog_data.dup_num[0] = 0;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[1] = 0;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[2] = 1;
      break;

    case 373:  /* *testqi_ext_3_rex64 */
    case 372:  /* *testqi_ext_3 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      break;

    case 371:  /* *testqi_ext_2 */
    case 370:  /* *testqi_ext_1_rex64 */
    case 369:  /* *testqi_ext_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0));
      break;

    case 368:  /* *testqi_ext_0 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 361:  /* *udivmodsi4_noext */
    case 359:  /* *udivmoddi4_noext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 2), 0);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[2] = 2;
      break;

    case 360:  /* udivmodsi4 */
    case 358:  /* udivmoddi4 */
    case 357:  /* divmodhi4 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 362:  /* *udivmodhi_noext */
    case 356:  /* *divmodsi_noext */
    case 353:  /* *divmoddi_noext_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 2), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 355:  /* *divmodsi4_cltd */
    case 354:  /* *divmodsi4_nocltd */
    case 352:  /* *divmoddi4_cltd_rex64 */
    case 351:  /* *divmoddi4_nocltd_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 3;
      break;

    case 348:  /* *smulsi3_highpart_zext */
    case 345:  /* *umulsi3_highpart_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 347:  /* *smulsi3_highpart_insn */
    case 346:  /* *smuldi3_highpart_rex64 */
    case 344:  /* *umulsi3_highpart_insn */
    case 343:  /* *umuldi3_highpart_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 342:  /* *mulsidi3_insn */
    case 341:  /* *mulditi3_insn */
    case 340:  /* *umulsidi3_insn */
    case 339:  /* *umulditi3_insn */
    case 338:  /* *mulqihi3_insn */
    case 337:  /* *umulqihi3_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 324:  /* *subsi_3_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 318:  /* subsi3_carry_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1), 0));
      break;

    case 331:  /* *subqi_3 */
    case 327:  /* *subhi_3 */
    case 323:  /* *subsi_3 */
    case 314:  /* *subdi_3_rex63 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 317:  /* subsi3_carry */
    case 316:  /* subhi3_carry */
    case 315:  /* subqi3_carry */
    case 311:  /* subdi3_carry_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 432:  /* *xorqi_ext_2 */
    case 431:  /* *xorqi_ext_1_rex64 */
    case 430:  /* *xorqi_ext_1 */
    case 413:  /* *iorqi_ext_2 */
    case 412:  /* *iorqi_ext_1_rex64 */
    case 411:  /* *iorqi_ext_1 */
    case 391:  /* *andqi_ext_2 */
    case 390:  /* *andqi_ext_1_rex64 */
    case 389:  /* *andqi_ext_1 */
    case 308:  /* *addqi_ext_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 429:  /* *xorqi_ext_0 */
    case 410:  /* *iorqi_ext_0 */
    case 387:  /* andqi_ext_0 */
    case 307:  /* *addqi_ext_1_rex64 */
    case 306:  /* addqi_ext_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 604:  /* *rotrqi3_1_slp */
    case 602:  /* *rotrqi3_1_one_bit_slp */
    case 590:  /* *rotlqi3_1_slp */
    case 588:  /* *rotlqi3_1_one_bit_slp */
    case 574:  /* *lshrqi3_1_slp */
    case 572:  /* *lshrqi3_1_one_bit_slp */
    case 540:  /* *ashrqi3_1_slp */
    case 538:  /* *ashrqi3_1_one_bit_slp */
    case 428:  /* *xorqi_1_slp */
    case 406:  /* *iorqi_1_slp */
    case 383:  /* *andqi_1_slp */
    case 329:  /* *subqi_1_slp */
    case 301:  /* *addqi_1_slp */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 290:  /* *addsi_3_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 530:  /* *ashrsi3_cmp_zext */
    case 527:  /* *ashrsi3_one_bit_cmp_zext */
    case 499:  /* *ashlsi3_cmp_zext */
    case 421:  /* *xorsi_2_zext */
    case 399:  /* *iorsi_2_zext */
    case 379:  /* *andsi_2_zext */
    case 322:  /* *subsi_2_zext */
    case 288:  /* *addsi_2_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 598:  /* *rotrsi3_1_zext */
    case 596:  /* *rotrsi3_1_one_bit_zext */
    case 585:  /* *rotlsi3_1_zext */
    case 583:  /* *rotlsi3_1_one_bit_zext */
    case 558:  /* *lshrsi3_1_zext */
    case 524:  /* *ashrsi3_1_zext */
    case 522:  /* *ashrsi3_1_one_bit_zext */
    case 520:  /* *ashrsi3_31_zext */
    case 496:  /* *ashlsi3_1_zext */
    case 418:  /* *xorsi_1_zext */
    case 396:  /* *iorsi_1_zext */
    case 377:  /* *andsi_1_zext */
    case 334:  /* *mulsi3_1_zext */
    case 320:  /* *subsi_1_zext */
    case 286:  /* addsi_1_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      break;

    case 578:  /* *lshrqi2_cconly */
    case 576:  /* *lshrqi2_one_bit_cconly */
    case 570:  /* *lshrhi3_cconly */
    case 568:  /* *lshrhi3_one_bit_cconly */
    case 563:  /* *lshrsi3_cconly */
    case 560:  /* *lshrsi3_one_bit_cconly */
    case 553:  /* *lshrdi3_cconly_rex64 */
    case 551:  /* *lshrdi3_cconly_one_bit_rex64 */
    case 544:  /* *ashrqi3_cconly */
    case 542:  /* *ashrqi3_one_bit_cconly */
    case 536:  /* *ashrhi3_cconly */
    case 534:  /* *ashrhi3_one_bit_cconly */
    case 529:  /* *ashrsi3_cconly */
    case 526:  /* *ashrsi3_one_bit_cconly */
    case 516:  /* *ashrdi3_cconly_rex64 */
    case 514:  /* *ashrdi3_one_bit_cconly_rex64 */
    case 507:  /* *ashlqi3_cconly */
    case 503:  /* *ashlhi3_cconly */
    case 498:  /* *ashlsi3_cconly */
    case 492:  /* *ashldi3_cconly_rex64 */
    case 435:  /* *xorqi_cc_2 */
    case 426:  /* *xorhi_3 */
    case 423:  /* *xorsi_3 */
    case 416:  /* *xordi_3_rex64 */
    case 409:  /* *iorqi_3 */
    case 404:  /* *iorhi_3 */
    case 401:  /* *iorsi_3 */
    case 394:  /* *iordi_3_rex64 */
    case 305:  /* *addqi_5 */
    case 298:  /* *addhi_5 */
    case 292:  /* *addsi_5 */
    case 284:  /* *adddi_5_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      break;

    case 303:  /* *addqi_3 */
    case 296:  /* *addhi_3 */
    case 289:  /* *addsi_3 */
    case 282:  /* *adddi_3_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      break;

    case 577:  /* *lshrqi2_cmp */
    case 575:  /* *lshrqi2_one_bit_cmp */
    case 569:  /* *lshrhi3_cmp */
    case 567:  /* *lshrhi3_one_bit_cmp */
    case 562:  /* *lshrsi3_cmp */
    case 559:  /* *lshrsi3_one_bit_cmp */
    case 552:  /* *lshrdi3_cmp_rex64 */
    case 550:  /* *lshrdi3_cmp_one_bit_rex64 */
    case 543:  /* *ashrqi3_cmp */
    case 541:  /* *ashrqi3_one_bit_cmp */
    case 535:  /* *ashrhi3_cmp */
    case 533:  /* *ashrhi3_one_bit_cmp */
    case 528:  /* *ashrsi3_cmp */
    case 525:  /* *ashrsi3_one_bit_cmp */
    case 515:  /* *ashrdi3_cmp_rex64 */
    case 513:  /* *ashrdi3_one_bit_cmp_rex64 */
    case 506:  /* *ashlqi3_cmp */
    case 502:  /* *ashlhi3_cmp */
    case 497:  /* *ashlsi3_cmp */
    case 491:  /* *ashldi3_cmp_rex64 */
    case 433:  /* *xorqi_cc_1 */
    case 425:  /* *xorhi_2 */
    case 420:  /* *xorsi_2 */
    case 415:  /* *xordi_2_rex64 */
    case 407:  /* *iorqi_2 */
    case 403:  /* *iorhi_2 */
    case 398:  /* *iorsi_2 */
    case 393:  /* *iordi_2_rex64 */
    case 385:  /* *andqi_2 */
    case 384:  /* *andqi_2_maybe_si */
    case 381:  /* *andhi_2 */
    case 378:  /* *andsi_2 */
    case 375:  /* *anddi_2 */
    case 330:  /* *subqi_2 */
    case 326:  /* *subhi_2 */
    case 321:  /* *subsi_2 */
    case 313:  /* *subdi_2_rex64 */
    case 302:  /* *addqi_2 */
    case 295:  /* *addhi_2 */
    case 287:  /* *addsi_2 */
    case 281:  /* *adddi_2_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 279:  /* *lea_general_3_zext */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 278:  /* *lea_general_3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 277:  /* *lea_general_2_zext */
    case 275:  /* *lea_general_1_zext */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 1843:  /* sse5_pmacssdd */
    case 1842:  /* sse5_pmacsdd */
    case 1841:  /* sse5_pmacssww */
    case 1840:  /* sse5_pmacsww */
    case 1287:  /* sse5_fmsubv2df4 */
    case 1286:  /* sse5_fmsubv4sf4 */
    case 1285:  /* sse5_fmsubdf4 */
    case 1284:  /* sse5_fmsubsf4 */
    case 1281:  /* sse5_fmaddv2df4 */
    case 1280:  /* sse5_fmaddv4sf4 */
    case 1279:  /* sse5_fmadddf4 */
    case 1278:  /* sse5_fmaddsf4 */
    case 276:  /* *lea_general_2 */
    case 274:  /* *lea_general_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 267:  /* *addsi3_carry_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      break;

    case 263:  /* *subsi3_zext_cc_overflow */
    case 262:  /* *addsi3_zext_cc_overflow */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1);
      recog_data.dup_num[2] = 1;
      break;

    case 261:  /* *subdi3_cconly_overflow */
    case 260:  /* *subsi3_cconly_overflow */
    case 259:  /* *subhi3_cconly_overflow */
    case 258:  /* *subqi3_cconly_overflow */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 0;
      break;

    case 257:  /* *adddi3_cconly_overflow */
    case 256:  /* *addsi3_cconly_overflow */
    case 255:  /* *addhi3_cconly_overflow */
    case 254:  /* *addqi3_cconly_overflow */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 253:  /* *subdi3_cc_overflow */
    case 252:  /* *adddi3_cc_overflow */
    case 251:  /* *subsi3_cc_overflow */
    case 250:  /* *addsi3_cc_overflow */
    case 249:  /* *subhi3_cc_overflow */
    case 248:  /* *addhi3_cc_overflow */
    case 247:  /* *subqi3_cc_overflow */
    case 246:  /* *addqi3_cc_overflow */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1);
      recog_data.dup_num[2] = 1;
      break;

    case 269:  /* addqi3_cc */
    case 268:  /* *addsi3_cc */
    case 245:  /* *adddi3_cc_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 266:  /* addsi3_carry */
    case 265:  /* addhi3_carry */
    case 264:  /* addqi3_carry */
    case 244:  /* adddi3_carry_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      break;

    case 900:  /* pro_epilogue_adjust_stack_rex64 */
    case 899:  /* pro_epilogue_adjust_stack_1 */
    case 603:  /* *rotrqi3_1 */
    case 601:  /* *rotrqi3_1_one_bit */
    case 600:  /* *rotrhi3_1 */
    case 599:  /* *rotrhi3_one_bit */
    case 597:  /* *rotrsi3_1 */
    case 595:  /* *rotrsi3_1_one_bit */
    case 594:  /* *rotrdi3_1_rex64 */
    case 593:  /* *rotrdi3_1_one_bit_rex64 */
    case 591:  /* *rotlqi3_1 */
    case 589:  /* *rotlqi3_1_one_bit */
    case 587:  /* *rotlhi3_1 */
    case 586:  /* *rotlhi3_1_one_bit */
    case 584:  /* *rotlsi3_1 */
    case 582:  /* *rotlsi3_1_one_bit */
    case 581:  /* *rotldi3_1_rex64 */
    case 580:  /* *rotlsi3_1_one_bit_rex64 */
    case 573:  /* *lshrqi3_1 */
    case 571:  /* *lshrqi3_1_one_bit */
    case 566:  /* *lshrhi3_1 */
    case 565:  /* *lshrhi3_1_one_bit */
    case 557:  /* *lshrsi3_1 */
    case 555:  /* *lshrsi3_1_one_bit */
    case 554:  /* *lshrdi3_1 */
    case 549:  /* *lshrdi3_1_rex64 */
    case 548:  /* *lshrdi3_1_one_bit_rex64 */
    case 547:  /* *lshrti3_1 */
    case 539:  /* *ashrqi3_1 */
    case 537:  /* *ashrqi3_1_one_bit */
    case 532:  /* *ashrhi3_1 */
    case 531:  /* *ashrhi3_1_one_bit */
    case 523:  /* *ashrsi3_1 */
    case 521:  /* *ashrsi3_1_one_bit */
    case 519:  /* *ashrsi3_31 */
    case 517:  /* *ashrdi3_1 */
    case 512:  /* *ashrdi3_1_rex64 */
    case 511:  /* *ashrdi3_1_one_bit_rex64 */
    case 510:  /* ashrdi3_63_rex64 */
    case 508:  /* *ashrti3_1 */
    case 505:  /* *ashlqi3_1 */
    case 504:  /* *ashlqi3_1_lea */
    case 501:  /* *ashlhi3_1 */
    case 500:  /* *ashlhi3_1_lea */
    case 495:  /* *ashlsi3_1 */
    case 493:  /* *ashldi3_1 */
    case 490:  /* *ashldi3_1_rex64 */
    case 488:  /* *ashlti3_1 */
    case 427:  /* *xorqi_1 */
    case 424:  /* *xorhi_1 */
    case 417:  /* *xorsi_1 */
    case 414:  /* *xordi_1_rex64 */
    case 405:  /* *iorqi_1 */
    case 402:  /* *iorhi_1 */
    case 395:  /* *iorsi_1 */
    case 392:  /* *iordi_1_rex64 */
    case 382:  /* *andqi_1 */
    case 380:  /* *andhi_1 */
    case 376:  /* *andsi_1 */
    case 374:  /* *anddi_1_rex64 */
    case 350:  /* udivqi3 */
    case 349:  /* divqi3 */
    case 336:  /* *mulqi3_1 */
    case 335:  /* *mulhi3_1 */
    case 333:  /* *mulsi3_1 */
    case 332:  /* *muldi3_1_rex64 */
    case 328:  /* *subqi_1 */
    case 325:  /* *subhi_1 */
    case 319:  /* *subsi_1 */
    case 312:  /* *subdi_1_rex64 */
    case 310:  /* *subdi3_1 */
    case 309:  /* *subti3_1 */
    case 300:  /* *addqi_1 */
    case 299:  /* *addqi_1_lea */
    case 294:  /* *addhi_1 */
    case 293:  /* *addhi_1_lea */
    case 285:  /* *addsi_1 */
    case 280:  /* *adddi_1_rex64 */
    case 243:  /* *adddi3_1 */
    case 242:  /* *addti3_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 238:  /* floatdixf2_i387_with_xmm */
    case 237:  /* floatdidf2_i387_with_xmm */
    case 236:  /* floatdisf2_i387_with_xmm */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 170:  /* fix_truncdi_i387_with_temp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 4), 0));
      break;

    case 174:  /* fix_truncsi_i387_with_temp */
    case 173:  /* fix_trunchi_i387_with_temp */
    case 169:  /* fix_truncdi_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 241:  /* *floatunssixf2_1 */
    case 240:  /* *floatunssidf2_1 */
    case 239:  /* *floatunssisf2_1 */
    case 172:  /* fix_truncsi_i387 */
    case 171:  /* fix_trunchi_i387 */
    case 165:  /* fix_truncdi_i387_fisttp_with_temp */
    case 164:  /* fix_truncsi_i387_fisttp_with_temp */
    case 163:  /* fix_trunchi_i387_fisttp_with_temp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 152:  /* *fixuns_truncdf_1 */
    case 151:  /* *fixuns_truncsf_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 1074:  /* movdi_to_sse */
    case 672:  /* *ffs_no_cmove */
    case 229:  /* *floatdixf2_i387_with_temp */
    case 228:  /* *floatdidf2_i387_with_temp */
    case 227:  /* *floatdisf2_i387_with_temp */
    case 226:  /* *floatsixf2_i387_with_temp */
    case 225:  /* *floatsidf2_i387_with_temp */
    case 224:  /* *floatsisf2_i387_with_temp */
    case 215:  /* *floatdidf2_sse_with_temp */
    case 214:  /* *floatdisf2_sse_with_temp */
    case 213:  /* *floatsidf2_sse_with_temp */
    case 212:  /* *floatsisf2_sse_with_temp */
    case 209:  /* *floatsidf2_vector_sse_with_temp */
    case 208:  /* *floatsisf2_vector_sse_with_temp */
    case 199:  /* *floatdidf2_mixed_with_temp */
    case 198:  /* *floatdisf2_mixed_with_temp */
    case 197:  /* *floatsidf2_mixed_with_temp */
    case 196:  /* *floatsisf2_mixed_with_temp */
    case 193:  /* *floatsidf2_vector_mixed_with_temp */
    case 192:  /* *floatsisf2_vector_mixed_with_temp */
    case 182:  /* *floathixf2_i387_with_temp */
    case 181:  /* *floathidf2_i387_with_temp */
    case 180:  /* *floathisf2_i387_with_temp */
    case 162:  /* fix_truncdi_i387_fisttp */
    case 161:  /* fix_truncsi_i387_fisttp */
    case 160:  /* fix_trunchi_i387_fisttp */
    case 146:  /* *truncxfdf2_mixed */
    case 145:  /* *truncxfsf2_mixed */
    case 143:  /* *truncdfsf_i387 */
    case 142:  /* *truncdfsf_mixed */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 125:  /* *extendsidi2_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 873:  /* *x86_movsicc_0_m1_se */
    case 872:  /* x86_movsicc_0_m1 */
    case 870:  /* *x86_movdicc_0_m1_se */
    case 869:  /* x86_movdicc_0_m1_rex64 */
    case 692:  /* clzhi2_abm */
    case 690:  /* clzdi2_abm */
    case 681:  /* popcountdi2 */
    case 680:  /* popcountsi2 */
    case 679:  /* popcounthi2 */
    case 677:  /* clzsi2_abm */
    case 676:  /* ctzdi2 */
    case 675:  /* ctzsi2 */
    case 448:  /* *negqi2_1 */
    case 446:  /* *neghi2_1 */
    case 442:  /* *negsi2_1 */
    case 440:  /* *negdi2_1_rex64 */
    case 439:  /* *negdi2_1 */
    case 438:  /* *negti2_1 */
    case 168:  /* *fix_truncdi_i387_1 */
    case 167:  /* *fix_truncsi_i387_1 */
    case 166:  /* *fix_trunchi_i387_1 */
    case 121:  /* zero_extendsidi2_32 */
    case 119:  /* *zero_extendqisi2_movzbw_and */
    case 118:  /* *zero_extendqisi2_and */
    case 116:  /* *zero_extendqihi2_movzbw_and */
    case 115:  /* *zero_extendqihi2_and */
    case 113:  /* zero_extendhisi2_and */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      break;

    case 80:  /* *movqi_insv_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1816:  /* sse4_1_zero_extendv2siv2di2 */
    case 1814:  /* sse4_1_zero_extendv2hiv2di2 */
    case 1812:  /* sse4_1_zero_extendv4hiv4si2 */
    case 1810:  /* sse4_1_zero_extendv2qiv2di2 */
    case 1808:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1806:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1804:  /* sse4_1_extendv2siv2di2 */
    case 1802:  /* sse4_1_extendv2hiv2di2 */
    case 1800:  /* sse4_1_extendv4hiv4si2 */
    case 1798:  /* sse4_1_extendv2qiv2di2 */
    case 1796:  /* sse4_1_extendv4qiv4si2 */
    case 1794:  /* sse4_1_extendv8qiv8hi2 */
    case 1366:  /* sse2_cvtps2pd */
    case 1354:  /* sse2_cvtdq2pd */
    case 1352:  /* sse2_cvttsd2siq */
    case 1351:  /* sse2_cvttsd2si */
    case 1330:  /* sse_cvttss2siq */
    case 1329:  /* sse_cvttss2si */
    case 1320:  /* sse_cvttps2pi */
    case 1079:  /* sse2_movq128 */
    case 1043:  /* *vec_dupv4hi */
    case 763:  /* sqrt_extenddfxf2_i387 */
    case 762:  /* sqrt_extendsfxf2_i387 */
    case 479:  /* *one_cmplsi2_1_zext */
    case 469:  /* *negextenddfxf2 */
    case 468:  /* *absextenddfxf2 */
    case 467:  /* *negextendsfxf2 */
    case 466:  /* *absextendsfxf2 */
    case 465:  /* *negextendsfdf2 */
    case 464:  /* *absextendsfdf2 */
    case 272:  /* *lea_1_zext */
    case 133:  /* *extendqisi2_zext */
    case 130:  /* *extendhisi2_zext */
    case 76:  /* *movqi_extzv_2_rex64 */
    case 75:  /* *movqi_extzv_2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 651:  /* *call_1_rex64_ms_sysv */
    case 66:  /* *movstrictqi_xor */
    case 59:  /* *movstricthi_xor */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 112:  /* swapxf */
    case 105:  /* *swapdf */
    case 99:  /* *swapsf */
    case 92:  /* *swapdi_rex64 */
    case 64:  /* *swapqi_2 */
    case 63:  /* *swapqi_1 */
    case 57:  /* *swaphi_2 */
    case 56:  /* *swaphi_1 */
    case 50:  /* *swapsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 1);
      recog_data.dup_num[1] = 0;
      break;

    case 1757:  /* absv2si2 */
    case 1756:  /* absv4hi2 */
    case 1755:  /* absv8qi2 */
    case 1754:  /* absv4si2 */
    case 1753:  /* absv8hi2 */
    case 1752:  /* absv16qi2 */
    case 1679:  /* *vec_dupv2di */
    case 1678:  /* *vec_dupv2di_avx */
    case 1677:  /* *vec_dupv4si */
    case 1676:  /* *vec_extractv2di_1_sse */
    case 1675:  /* *vec_extractv2di_1_sse2 */
    case 1674:  /* *vec_extractv2di_1_avx */
    case 1673:  /* *vec_extractv2di_1_rex64 */
    case 1672:  /* *vec_extractv2di_1_rex64_avx */
    case 1671:  /* *sse2_storeq */
    case 1670:  /* *sse2_storeq_rex64 */
    case 1668:  /* sse2_stored */
    case 1453:  /* vec_dupv2df */
    case 1452:  /* *vec_dupv2df_sse3 */
    case 1449:  /* *vec_extractv2df_0_sse */
    case 1448:  /* *vec_extractv2df_1_sse */
    case 1443:  /* sse2_storelpd */
    case 1442:  /* sse2_storehpd */
    case 1441:  /* *avx_storehpd */
    case 1420:  /* vec_extract_hi_v32qi */
    case 1419:  /* vec_extract_lo_v32qi */
    case 1418:  /* vec_extract_hi_v16hi */
    case 1417:  /* vec_extract_lo_v16hi */
    case 1416:  /* vec_extract_hi_v8sf */
    case 1415:  /* vec_extract_hi_v8si */
    case 1414:  /* vec_extract_lo_v8sf */
    case 1413:  /* vec_extract_lo_v8si */
    case 1412:  /* vec_extract_hi_v4df */
    case 1411:  /* vec_extract_hi_v4di */
    case 1410:  /* vec_extract_lo_v4df */
    case 1409:  /* vec_extract_lo_v4di */
    case 1408:  /* *vec_extractv4sf_0 */
    case 1396:  /* *vec_dupv4sf */
    case 1395:  /* *vec_dupv4sf_avx */
    case 1390:  /* sse_storelps */
    case 1389:  /* *avx_storelps */
    case 1386:  /* sse_storehps */
    case 1365:  /* avx_cvtps2pd256 */
    case 1363:  /* avx_cvtpd2ps256 */
    case 1357:  /* avx_cvttpd2dq256 */
    case 1353:  /* avx_cvtdq2pd256 */
    case 1342:  /* sse2_cvttpd2pi */
    case 1340:  /* sse2_cvtpi2pd */
    case 1339:  /* sse2_cvttps2dq */
    case 1338:  /* avx_cvttps2dq256 */
    case 1337:  /* avx_cvttps2dq */
    case 1333:  /* sse2_cvtdq2ps */
    case 1332:  /* avx_cvtdq2ps256 */
    case 1331:  /* avx_cvtdq2ps */
    case 1147:  /* sqrtv2df2 */
    case 1146:  /* sqrtv4df2 */
    case 1145:  /* sse_sqrtv4sf2 */
    case 1144:  /* avx_sqrtv8sf2 */
    case 1047:  /* *vec_extractv2si_1 */
    case 1046:  /* *vec_extractv2si_0 */
    case 1044:  /* *vec_dupv2si */
    case 1042:  /* mmx_pswapdv2si2 */
    case 977:  /* *vec_extractv2sf_1 */
    case 976:  /* *vec_extractv2sf_0 */
    case 974:  /* *vec_dupv2sf */
    case 973:  /* mmx_pswapdv2sf2 */
    case 972:  /* mmx_floatv2si2 */
    case 969:  /* mmx_pf2id */
    case 766:  /* *sqrtdf2_sse */
    case 765:  /* *sqrtsf2_sse */
    case 761:  /* sqrtxf2 */
    case 689:  /* bswapdi2 */
    case 686:  /* *bswapsi_1 */
    case 484:  /* *one_cmplqi2_1 */
    case 482:  /* *one_cmplhi2_1 */
    case 478:  /* *one_cmplsi2_1 */
    case 476:  /* *one_cmpldi2_1_rex64 */
    case 463:  /* *negxf2_1 */
    case 462:  /* *absxf2_1 */
    case 461:  /* *negdf2_1 */
    case 460:  /* *absdf2_1 */
    case 459:  /* *negsf2_1 */
    case 458:  /* *abssf2_1 */
    case 271:  /* *lea_1_rex64 */
    case 235:  /* *floatdixf2_i387 */
    case 234:  /* *floatdidf2_i387 */
    case 233:  /* *floatdisf2_i387 */
    case 232:  /* *floatsixf2_i387 */
    case 231:  /* *floatsidf2_i387 */
    case 230:  /* *floatsisf2_i387 */
    case 223:  /* *floatdidf2_sse_nointerunit */
    case 222:  /* *floatdisf2_sse_nointerunit */
    case 221:  /* *floatsidf2_sse_nointerunit */
    case 220:  /* *floatsisf2_sse_nointerunit */
    case 219:  /* *floatdidf2_sse_interunit */
    case 218:  /* *floatdisf2_sse_interunit */
    case 217:  /* *floatsidf2_sse_interunit */
    case 216:  /* *floatsisf2_sse_interunit */
    case 211:  /* *floatsidf2_vector_sse */
    case 210:  /* *floatsisf2_vector_sse */
    case 207:  /* *floatdidf2_mixed_nointerunit */
    case 206:  /* *floatdisf2_mixed_nointerunit */
    case 205:  /* *floatsidf2_mixed_nointerunit */
    case 204:  /* *floatsisf2_mixed_nointerunit */
    case 203:  /* *floatdidf2_mixed_interunit */
    case 202:  /* *floatdisf2_mixed_interunit */
    case 201:  /* *floatsidf2_mixed_interunit */
    case 200:  /* *floatsisf2_mixed_interunit */
    case 195:  /* *floatsidf2_vector_mixed */
    case 194:  /* *floatsisf2_vector_mixed */
    case 191:  /* *floatdixf2_1 */
    case 190:  /* *floatdidf2_1 */
    case 189:  /* *floatdisf2_1 */
    case 188:  /* *floatsixf2_1 */
    case 187:  /* *floatsidf2_1 */
    case 186:  /* *floatsisf2_1 */
    case 185:  /* *floathixf2_i387 */
    case 184:  /* *floathidf2_i387 */
    case 183:  /* *floathisf2_i387 */
    case 179:  /* *floathixf2_1 */
    case 178:  /* *floathidf2_1 */
    case 177:  /* *floathisf2_1 */
    case 159:  /* fix_truncdi_fisttp_i387_1 */
    case 158:  /* fix_truncsi_fisttp_i387_1 */
    case 157:  /* fix_trunchi_fisttp_i387_1 */
    case 156:  /* fix_truncdfsi_sse */
    case 155:  /* fix_truncsfsi_sse */
    case 154:  /* fix_truncdfdi_sse */
    case 153:  /* fix_truncsfdi_sse */
    case 150:  /* *truncxfdf2_i387 */
    case 149:  /* *truncxfsf2_i387 */
    case 148:  /* truncxfdf2_i387_noop */
    case 147:  /* truncxfsf2_i387_noop */
    case 144:  /* *truncdfsf2_i387_1 */
    case 141:  /* *truncdfsf_fast_i387 */
    case 140:  /* *truncdfsf_fast_sse */
    case 139:  /* *truncdfsf_fast_mixed */
    case 138:  /* *extenddfxf2_i387 */
    case 137:  /* *extendsfxf2_i387 */
    case 136:  /* *extendsfdf2_i387 */
    case 135:  /* *extendsfdf2_sse */
    case 134:  /* *extendsfdf2_mixed */
    case 132:  /* extendqisi2 */
    case 131:  /* extendqihi2 */
    case 129:  /* extendhisi2 */
    case 128:  /* extendqidi2 */
    case 127:  /* extendhidi2 */
    case 126:  /* extendsidi2_rex64 */
    case 124:  /* zero_extendqidi2 */
    case 123:  /* zero_extendhidi2 */
    case 122:  /* zero_extendsidi2_rex64 */
    case 120:  /* *zero_extendqisi2_movzbw */
    case 117:  /* *zero_extendqihi2_movzbl */
    case 114:  /* *zero_extendhisi2_movzwl */
    case 91:  /* *movabsdi_2_rex64 */
    case 74:  /* *movsi_extzv_1 */
    case 73:  /* *movdi_extzv_1 */
    case 72:  /* *movabsqi_2_rex64 */
    case 70:  /* *movqi_extv_1_rex64 */
    case 69:  /* *movqi_extv_1 */
    case 68:  /* *movhi_extv_1 */
    case 67:  /* *movsi_extv_1 */
    case 55:  /* *movabshi_2_rex64 */
    case 49:  /* *movabssi_2_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 653:  /* *sibcall_1_rex64 */
    case 652:  /* *call_1_rex64_large */
    case 650:  /* *call_1_rex64 */
    case 649:  /* *sibcall_1 */
    case 648:  /* *call_1 */
    case 647:  /* *call_0 */
    case 611:  /* *setcc_2 */
    case 90:  /* *movabsdi_1_rex64 */
    case 79:  /* movdi_insv_1_rex64 */
    case 78:  /* *movsi_insv_1_rex64 */
    case 77:  /* movsi_insv_1 */
    case 71:  /* *movabsqi_1_rex64 */
    case 65:  /* *movstrictqi_1 */
    case 58:  /* *movstricthi_1 */
    case 54:  /* *movabshi_1_rex64 */
    case 48:  /* *movabssi_1_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      break;

    case 663:  /* set_got */
    case 85:  /* popdi1 */
    case 84:  /* *popdi1_epilogue_rex64 */
    case 44:  /* popsi1 */
    case 43:  /* *popsi1_epilogue */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      break;

    case 87:  /* *movdi_or_rex64 */
    case 86:  /* *movdi_xor_rex64 */
    case 83:  /* *pushdi2_prologue_rex64 */
    case 46:  /* *movsi_or */
    case 45:  /* *movsi_xor */
    case 42:  /* *pushsi2_prologue */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 1073:  /* *movv2df_internal */
    case 1072:  /* *movv4sf_internal */
    case 1071:  /* *movv2di_internal */
    case 1070:  /* *movv4si_internal */
    case 1069:  /* *movv8hi_internal */
    case 1068:  /* *movv16qi_internal */
    case 1067:  /* *avx_movv4df_internal */
    case 1066:  /* *avx_movv8sf_internal */
    case 1065:  /* *avx_movv4di_internal */
    case 1064:  /* *avx_movv8si_internal */
    case 1063:  /* *avx_movv16hi_internal */
    case 1062:  /* *avx_movv32qi_internal */
    case 1061:  /* *avx_movv2df_internal */
    case 1060:  /* *avx_movv4sf_internal */
    case 1059:  /* *avx_movv2di_internal */
    case 1058:  /* *avx_movv4si_internal */
    case 1057:  /* *avx_movv8hi_internal */
    case 1056:  /* *avx_movv16qi_internal */
    case 949:  /* *movv2sf_internal */
    case 948:  /* *movv2sf_internal_avx */
    case 947:  /* *movv2sf_internal_rex64 */
    case 946:  /* *movv2sf_internal_rex64_avx */
    case 945:  /* *movv1di_internal */
    case 944:  /* *movv2si_internal */
    case 943:  /* *movv4hi_internal */
    case 942:  /* *movv8qi_internal */
    case 941:  /* *movv1di_internal_avx */
    case 940:  /* *movv2si_internal_avx */
    case 939:  /* *movv4hi_internal_avx */
    case 938:  /* *movv8qi_internal_avx */
    case 937:  /* *movv1di_internal_rex64 */
    case 936:  /* *movv2si_internal_rex64 */
    case 935:  /* *movv4hi_internal_rex64 */
    case 934:  /* *movv8qi_internal_rex64 */
    case 921:  /* *prefetch_3dnow_rex */
    case 920:  /* *prefetch_3dnow */
    case 610:  /* *setcc_1 */
    case 273:  /* *lea_2_rex64 */
    case 270:  /* *lea_1 */
    case 111:  /* *pushtf_sse */
    case 110:  /* *movtf_internal */
    case 109:  /* *movxf_integer */
    case 108:  /* *movxf_nointeger */
    case 107:  /* *pushxf_integer */
    case 106:  /* *pushxf_nointeger */
    case 104:  /* *movdf_integer */
    case 103:  /* *movdf_integer_rex64 */
    case 102:  /* *movdf_nointeger */
    case 101:  /* *pushdf_integer */
    case 100:  /* *pushdf_nointeger */
    case 98:  /* *movsf_1 */
    case 97:  /* *pushsf_rex64 */
    case 96:  /* *pushsf */
    case 95:  /* *movti_rex64 */
    case 94:  /* *movti_internal */
    case 93:  /* *movoi_internal */
    case 89:  /* *movdi_1_rex64 */
    case 88:  /* *movdi_2 */
    case 82:  /* *pushdi2_rex64 */
    case 81:  /* *pushdi */
    case 62:  /* *movqi_1 */
    case 61:  /* *pushqi2_rex64 */
    case 60:  /* *pushqi2 */
    case 53:  /* *movhi_1 */
    case 52:  /* *pushhi2_rex64 */
    case 51:  /* *pushhi2 */
    case 47:  /* *movsi_1 */
    case 41:  /* *pushsi2_rex64 */
    case 40:  /* *pushsi2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      break;

    case 669:  /* eh_return_di */
    case 668:  /* eh_return_si */
    case 176:  /* x86_fldcw_1 */
    case 33:  /* x86_sahf_1 */
      ro[0] = *(ro_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0));
      break;

    case 1705:  /* sse_stmxcsr */
    case 707:  /* *load_tp_di */
    case 705:  /* *load_tp_si */
    case 665:  /* set_got_rex64 */
    case 175:  /* x86_fnstcw_1 */
    case 32:  /* x86_fnstsw_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      break;

    case 31:  /* *cmpfp_si_cc */
    case 30:  /* *cmpfp_hi_cc */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 29:  /* *cmpfp_si */
    case 28:  /* *cmpfp_hi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 304:  /* *addqi_4 */
    case 297:  /* *addhi_4 */
    case 291:  /* *addsi_4 */
    case 283:  /* *adddi_4_rex64 */
    case 27:  /* *cmpfp_u_cc */
    case 25:  /* *cmpfp_df_cc */
    case 24:  /* *cmpfp_sf_cc */
    case 21:  /* *cmpfp_xf_cc */
    case 19:  /* *cmpfp_0_cc */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 26:  /* *cmpfp_u */
    case 23:  /* *cmpfp_df */
    case 22:  /* *cmpfp_sf */
    case 20:  /* *cmpfp_xf */
    case 18:  /* *cmpfp_0 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 17:  /* *cmpqi_ext_4 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      break;

    case 16:  /* cmpqi_ext_3_insn_rex64 */
    case 15:  /* cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 13:  /* *cmpqi_ext_1_rex64 */
    case 12:  /* *cmpqi_ext_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      break;

    case 367:  /* *testqi_1 */
    case 366:  /* *testqi_1_maybe_si */
    case 365:  /* *testhi_1 */
    case 364:  /* testsi_1 */
    case 363:  /* *testdi_1_rex64 */
    case 11:  /* *cmpqi_minus_1 */
    case 7:  /* *cmphi_minus_1 */
    case 4:  /* *cmpsi_minus_1 */
    case 1:  /* *cmpdi_minus_1_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 39:  /* *cmpfp_iu_387 */
    case 38:  /* *cmpfp_iu_sse */
    case 37:  /* *cmpfp_iu_mixed */
    case 36:  /* *cmpfp_i_i387 */
    case 35:  /* *cmpfp_i_sse */
    case 34:  /* *cmpfp_i_mixed */
    case 10:  /* *cmpqi_1 */
    case 9:  /* *cmpqi_ccno_1 */
    case 8:  /* *cmphi_1 */
    case 6:  /* *cmphi_ccno_1 */
    case 5:  /* *cmpsi_1_insn */
    case 3:  /* *cmpsi_ccno_1 */
    case 2:  /* cmpdi_1_insn_rex64 */
    case 0:  /* cmpdi_ccno_1_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      break;

    }
}
