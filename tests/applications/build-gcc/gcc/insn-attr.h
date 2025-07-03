/* Generated automatically by the program `genattr'
   from the machine description file `md'.  */

#ifndef GCC_INSN_ATTR_H
#define GCC_INSN_ATTR_H

#define HAVE_ATTR_alternative
#define get_attr_alternative(insn) which_alternative
#define HAVE_ATTR_cpu
enum attr_cpu {CPU_NONE, CPU_PENTIUM, CPU_PENTIUMPRO, CPU_GEODE, CPU_K6, CPU_ATHLON, CPU_K8, CPU_CORE2, CPU_GENERIC64, CPU_AMDFAM10};
extern enum attr_cpu get_attr_cpu (void);

#define HAVE_ATTR_type
enum attr_type {TYPE_OTHER, TYPE_MULTI, TYPE_ALU, TYPE_ALU1, TYPE_NEGNOT, TYPE_IMOV, TYPE_IMOVX, TYPE_LEA, TYPE_INCDEC, TYPE_ISHIFT, TYPE_ISHIFT1, TYPE_ROTATE, TYPE_ROTATE1, TYPE_IMUL, TYPE_IDIV, TYPE_ICMP, TYPE_TEST, TYPE_IBR, TYPE_SETCC, TYPE_ICMOV, TYPE_PUSH, TYPE_POP, TYPE_CALL, TYPE_CALLV, TYPE_LEAVE, TYPE_STR, TYPE_BITMANIP, TYPE_FMOV, TYPE_FOP, TYPE_FSGN, TYPE_FMUL, TYPE_FDIV, TYPE_FPSPC, TYPE_FCMOV, TYPE_FCMP, TYPE_FXCH, TYPE_FISTP, TYPE_FISTTP, TYPE_FRNDINT, TYPE_SSELOG, TYPE_SSELOG1, TYPE_SSEIADD, TYPE_SSEIADD1, TYPE_SSEISHFT, TYPE_SSEIMUL, TYPE_SSE, TYPE_SSEMOV, TYPE_SSEADD, TYPE_SSEMUL, TYPE_SSECMP, TYPE_SSECOMI, TYPE_SSECVT, TYPE_SSECVT1, TYPE_SSEICVT, TYPE_SSEDIV, TYPE_SSEINS, TYPE_SSEMULADD, TYPE_SSE4ARG, TYPE_MMX, TYPE_MMXMOV, TYPE_MMXADD, TYPE_MMXMUL, TYPE_MMXCMP, TYPE_MMXCVT, TYPE_MMXSHFT};
extern enum attr_type get_attr_type (rtx);

#define HAVE_ATTR_mode
enum attr_mode {MODE_UNKNOWN, MODE_NONE, MODE_QI, MODE_HI, MODE_SI, MODE_DI, MODE_TI, MODE_OI, MODE_SF, MODE_DF, MODE_XF, MODE_TF, MODE_V8SF, MODE_V4DF, MODE_V4SF, MODE_V2DF, MODE_V2SF, MODE_V1DF};
extern enum attr_mode get_attr_mode (rtx);

#define HAVE_ATTR_unit
enum attr_unit {UNIT_INTEGER, UNIT_I387, UNIT_SSE, UNIT_MMX, UNIT_UNKNOWN};
extern enum attr_unit get_attr_unit (rtx);

#define HAVE_ATTR_length_immediate
extern int get_attr_length_immediate (rtx);
#define HAVE_ATTR_length_address
extern int get_attr_length_address (rtx);
#define HAVE_ATTR_prefix_data16
extern int get_attr_prefix_data16 (rtx);
#define HAVE_ATTR_prefix_rep
extern int get_attr_prefix_rep (rtx);
#define HAVE_ATTR_prefix_0f
extern int get_attr_prefix_0f (rtx);
#define HAVE_ATTR_prefix_rex
extern int get_attr_prefix_rex (rtx);
#define HAVE_ATTR_prefix_extra
extern int get_attr_prefix_extra (rtx);
#define HAVE_ATTR_prefix
enum attr_prefix {PREFIX_ORIG, PREFIX_VEX, PREFIX_MAYBE_VEX};
extern enum attr_prefix get_attr_prefix (rtx);

#define HAVE_ATTR_prefix_vex_imm8
extern int get_attr_prefix_vex_imm8 (rtx);
#define HAVE_ATTR_prefix_vex_w
extern int get_attr_prefix_vex_w (rtx);
#define HAVE_ATTR_length_vex
extern int get_attr_length_vex (rtx);
#define HAVE_ATTR_modrm
extern int get_attr_modrm (rtx);
#define HAVE_ATTR_length
extern int get_attr_length (rtx);
extern void shorten_branches (rtx);
extern int insn_default_length (rtx);
extern int insn_min_length (rtx);
extern int insn_variable_length_p (rtx);
extern int insn_current_length (rtx);

#include "insn-addr.h"

#define HAVE_ATTR_memory
enum attr_memory {MEMORY_NONE, MEMORY_LOAD, MEMORY_STORE, MEMORY_BOTH, MEMORY_UNKNOWN};
extern enum attr_memory get_attr_memory (rtx);

#define HAVE_ATTR_imm_disp
enum attr_imm_disp {IMM_DISP_FALSE, IMM_DISP_TRUE, IMM_DISP_UNKNOWN};
extern enum attr_imm_disp get_attr_imm_disp (rtx);

#define HAVE_ATTR_fp_int_src
enum attr_fp_int_src {FP_INT_SRC_FALSE, FP_INT_SRC_TRUE};
extern enum attr_fp_int_src get_attr_fp_int_src (rtx);

#define HAVE_ATTR_i387_cw
enum attr_i387_cw {I387_CW_TRUNC, I387_CW_FLOOR, I387_CW_CEIL, I387_CW_MASK_PM, I387_CW_UNINITIALIZED, I387_CW_ANY};
extern enum attr_i387_cw get_attr_i387_cw (rtx);

#define HAVE_ATTR_pent_prefix
enum attr_pent_prefix {PENT_PREFIX_FALSE, PENT_PREFIX_TRUE};
extern enum attr_pent_prefix get_attr_pent_prefix (rtx);

#define HAVE_ATTR_pent_pair
enum attr_pent_pair {PENT_PAIR_UV, PENT_PAIR_PU, PENT_PAIR_PV, PENT_PAIR_NP};
extern enum attr_pent_pair get_attr_pent_pair (rtx);

#define HAVE_ATTR_athlon_decode
enum attr_athlon_decode {ATHLON_DECODE_DIRECT, ATHLON_DECODE_VECTOR, ATHLON_DECODE_DOUBLE};
extern enum attr_athlon_decode get_attr_athlon_decode (rtx);

#define HAVE_ATTR_amdfam10_decode
enum attr_amdfam10_decode {AMDFAM10_DECODE_DIRECT, AMDFAM10_DECODE_VECTOR, AMDFAM10_DECODE_DOUBLE};
extern enum attr_amdfam10_decode get_attr_amdfam10_decode (rtx);


#define INSN_SCHEDULING

/* DFA based pipeline interface.  */
#ifndef AUTOMATON_ALTS
#define AUTOMATON_ALTS 0
#endif


#ifndef AUTOMATON_STATE_ALTS
#define AUTOMATON_STATE_ALTS 0
#endif

#ifndef CPU_UNITS_QUERY
#define CPU_UNITS_QUERY 0
#endif

/* Internal insn code number used by automata.  */
extern int internal_dfa_insn_code (rtx);

/* Insn latency time defined in define_insn_reservation. */
extern int insn_default_latency (rtx);

/* Return nonzero if there is a bypass for given insn
   which is a data producer.  */
extern int bypass_p (rtx);

/* Insn latency time on data consumed by the 2nd insn.
   Use the function if bypass_p returns nonzero for
   the 1st insn. */
extern int insn_latency (rtx, rtx);

/* Maximal insn latency time possible of all bypasses for this insn.
   Use the function if bypass_p returns nonzero for
   the 1st insn. */
extern int maximal_insn_latency (rtx);


#if AUTOMATON_ALTS
/* The following function returns number of alternative
   reservations of given insn.  It may be used for better
   insns scheduling heuristics. */
extern int insn_alts (rtx);

#endif

/* Maximal possible number of insns waiting results being
   produced by insns whose execution is not finished. */
extern const int max_insn_queue_index;

/* Pointer to data describing current state of DFA.  */
typedef void *state_t;

/* Size of the data in bytes.  */
extern int state_size (void);

/* Initiate given DFA state, i.e. Set up the state
   as all functional units were not reserved.  */
extern void state_reset (state_t);
/* The following function returns negative value if given
   insn can be issued in processor state described by given
   DFA state.  In this case, the DFA state is changed to
   reflect the current and future reservations by given
   insn.  Otherwise the function returns minimal time
   delay to issue the insn.  This delay may be zero
   for superscalar or VLIW processors.  If the second
   parameter is NULL the function changes given DFA state
   as new processor cycle started.  */
extern int state_transition (state_t, rtx);

#if AUTOMATON_STATE_ALTS
/* The following function returns number of possible
   alternative reservations of given insn in given
   DFA state.  It may be used for better insns scheduling
   heuristics.  By default the function is defined if
   macro AUTOMATON_STATE_ALTS is defined because its
   implementation may require much memory.  */
extern int state_alts (state_t, rtx);
#endif

extern int min_issue_delay (state_t, rtx);
/* The following function returns nonzero if no one insn
   can be issued in current DFA state. */
extern int state_dead_lock_p (state_t);
/* The function returns minimal delay of issue of the 2nd
   insn after issuing the 1st insn in given DFA state.
   The 1st insn should be issued in given state (i.e.
    state_transition should return negative value for
    the insn and the state).  Data dependencies between
    the insns are ignored by the function.  */
extern int min_insn_conflict_delay (state_t, rtx, rtx);
/* The following function outputs reservations for given
   insn as they are described in the corresponding
   define_insn_reservation.  */
extern void print_reservation (FILE *, rtx);

#if CPU_UNITS_QUERY
/* The following function returns code of functional unit
   with given name (see define_cpu_unit). */
extern int get_cpu_unit_code (const char *);
/* The following function returns nonzero if functional
   unit with given code is currently reserved in given
   DFA state.  */
extern int cpu_unit_reservation_p (state_t, int);
#endif

/* The following function returns true if insn
   has a dfa reservation.  */
extern bool insn_has_dfa_reservation_p (rtx);

/* Clean insn code cache.  It should be called if there
   is a chance that condition value in a
   define_insn_reservation will be changed after
   last call of dfa_start.  */
extern void dfa_clean_insn_cache (void);

extern void dfa_clear_single_insn_cache (rtx);

/* Initiate and finish work with DFA.  They should be
   called as the first and the last interface
   functions.  */
extern void dfa_start (void);
extern void dfa_finish (void);

#define ATTR_FLAG_forward	0x1
#define ATTR_FLAG_backward	0x2
#define ATTR_FLAG_likely	0x4
#define ATTR_FLAG_very_likely	0x8
#define ATTR_FLAG_unlikely	0x10
#define ATTR_FLAG_very_unlikely	0x20

#endif /* GCC_INSN_ATTR_H */
