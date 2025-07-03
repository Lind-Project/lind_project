(define_conditions [
  (-1 "TARGET_AES")
  (-1 "TARGET_64BIT && ix86_check_movabs (insn, 1)")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (PLUS, HImode, operands)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, QImode, operands)")
  (-1 "TARGET_SSE3 && reload_completed")
  (0 "0")
  (-1 "ix86_binary_operator_ok (ROTATERT, SImode, operands)")
  (-1 "TARGET_SSE
   && (register_operand (operands[0], V8HImode)
       || register_operand (operands[1], V8HImode))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode)
   && ix86_binary_operator_ok (MULT, V4DFmode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (MINUS, DImode, operands)")
  (-1 "TARGET_SSE5
   && (register_operand (operands[1], V16QImode)
       || register_operand (operands[2], V16QImode))")
  (-1 "TARGET_USE_FANCY_MATH_387
   && (!(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && flag_unsafe_math_optimizations")
  (-1 "reload_completed
    && QI_REG_P (operands[0])
    && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
    && !(INTVAL (operands[2]) & ~(255 << 8))
    && GET_MODE (operands[0]) != QImode")
  (-1 "((GET_MODE (operands[0]) == QImode || GET_MODE (operands[0]) == HImode
    || (TARGET_64BIT && GET_MODE (operands[0]) == SImode))
   && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && GET_MODE (operands[0]) == GET_MODE (operands[1])
   && GET_MODE (operands[0]) == GET_MODE (operands[2])
   && (GET_MODE (operands[0]) == GET_MODE (operands[3])
       || GET_MODE (operands[3]) == VOIDmode)) && ( reload_completed)")
  (-1 "AVX_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (IOR, V8HImode, operands)")
  (-1 "(TARGET_MMX || (TARGET_SSE2 && V8QImode == V1DImode))
   && ix86_binary_operator_ok (MINUS, V8QImode, operands)")
  (-1 "TARGET_80387 && !(TARGET_SSE2 && TARGET_SSE_MATH)")
  (-1 "(GET_MODE (operands[0]) == QImode || GET_MODE (operands[0]) == HImode
    || (TARGET_64BIT && GET_MODE (operands[0]) == SImode))
   && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && GET_MODE (operands[0]) == GET_MODE (operands[1])
   && (GET_MODE (operands[0]) == GET_MODE (operands[3])
       || GET_MODE (operands[3]) == VOIDmode)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (US_PLUS, V16QImode, operands)")
  (-1 "!(MEM_P (operands[0]) && MEM_P (operands[1]))
   && (reload_in_progress || reload_completed
       || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
       || (!TARGET_SSE_MATH && optimize_function_for_size_p (cfun)
	   && standard_80387_constant_p (operands[1]))
       || GET_CODE (operands[1]) != CONST_DOUBLE
       || memory_operand (operands[0], SFmode))")
  (-1 "TARGET_PREFETCH_SSE || TARGET_3DNOW")
  (-1 "TARGET_64BIT
   && INTVAL (operands[4]) + X86_64_SSE_REGPARM_MAX * 16 - 16 < 128
   && INTVAL (operands[4]) + INTVAL (operands[2]) * 16 >= -128")
  (-1 "TARGET_SSE
   && (register_operand (operands[0], V4SFmode)
       || register_operand (operands[1], V4SFmode))")
  (-1 "TARGET_64BIT")
  (-1 "(optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_FLAG_REG_STALL)
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "AVX_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V32QImode)
       || register_operand (operands[1], V32QImode))")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCZmode)
   && ix86_binary_operator_ok (PLUS, SImode, operands)
   /* Current assemblers are broken and do not allow @GOTOFF in
      ought but a memory context.  */
   && ! pic_symbolic_operand (operands[2], VOIDmode)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_SAHF && !TARGET_CMOVE
   && (TARGET_USE_HIMODE_FIOP || optimize_function_for_size_p (cfun))
   && (GET_MODE (operands [3]) == GET_MODE (operands[1]))")
  (-1 "TARGET_64BIT && ix86_check_movabs (insn, 0)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (XOR, V2DImode, operands)")
  (-1 "AVX256_VEC_FLOAT_MODE_P (V8SFmode)")
  (-1 "TARGET_MIX_SSE_I387")
  (-1 "(optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_FLAG_REG_STALL)
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (LSHIFTRT, HImode, operands)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "reload_completed
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))
   && GET_MODE (operands[0]) == XFmode
   && ! (ANY_FP_REG_P (operands[0]) ||
	 (GET_CODE (operands[0]) == SUBREG
	  && ANY_FP_REG_P (SUBREG_REG (operands[0]))))
   && ! (ANY_FP_REG_P (operands[1]) ||
	 (GET_CODE (operands[1]) == SUBREG
	  && ANY_FP_REG_P (SUBREG_REG (operands[1]))))")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (SMAX, V4SImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (US_PLUS, V16QImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (SS_PLUS, V8HImode, operands)")
  (-1 "TARGET_MMX || (TARGET_SSE2 && V2SImode == V1DImode)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (MINUS, SImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (MINUS, V4SFmode, operands)")
  (-1 "!TARGET_ZERO_EXTEND_WITH_AND
   || optimize_function_for_size_p (cfun)")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH && TARGET_64BIT
   && !flag_trapping_math")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (MINUS, V16QImode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (XOR, V2DFmode, operands)")
  (-1 "!(MEM_P (operands[0]) && MEM_P (operands[1]))
   && ((optimize_function_for_size_p (cfun)
       || !TARGET_INTEGER_DFMODE_MOVES) && !TARGET_64BIT)
   && (reload_in_progress || reload_completed
       || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
       || (!(TARGET_SSE2 && TARGET_SSE_MATH)
           && optimize_function_for_size_p (cfun)
           && !memory_operand (operands[0], DFmode)
	   && standard_80387_constant_p (operands[1]))
       || GET_CODE (operands[1]) != CONST_DOUBLE
       || ((optimize_function_for_size_p (cfun)
            || !TARGET_MEMORY_MISMATCH_STALL
	    || reload_in_progress || reload_completed)
 	   && memory_operand (operands[0], DFmode)))")
  (-1 "ix86_binary_operator_ok (LSHIFTRT, HImode, operands)")
  (-1 "(TARGET_USE_FANCY_MATH_387
   && flag_unsafe_math_optimizations
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, HImode, operands)")
  (-1 "((SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
   || (TARGET_SSE2 && (DFmode == TFmode))) && ( reload_completed)")
  (-1 "!TARGET_64BIT && TARGET_SSE")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (IOR, V8HImode, operands)")
  (-1 "optimize_function_for_size_p (cfun)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))
   && (reload_in_progress || reload_completed
       || standard_80387_constant_p (operands[1])
       || GET_CODE (operands[1]) != CONST_DOUBLE
       || memory_operand (operands[0], XFmode))")
  (-1 "optimize_insn_for_speed_p ()
   && ((TARGET_NOT_UNPAIRABLE
        && (!MEM_P (operands[0])
            || !memory_displacement_operand (operands[0], SImode)))
       || (TARGET_NOT_VECTORMODE && long_memory_operand (operands[0], SImode)))
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (SS_MINUS, V16QImode, operands)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCmode)")
  (-1 "(TARGET_80387 && TARGET_CMOVE)
   || (SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)")
  (-1 "(TARGET_CMPXCHG) && (TARGET_64BIT && TARGET_CMPXCHG16B)")
  (-1 "!TARGET_64BIT && flag_pic")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (PLUS, QImode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (IOR, V2DFmode, operands)")
  (-1 "optimize_insn_for_size_p () || !TARGET_ADD_ESP_8")
  (-1 "(TARGET_USE_FANCY_MATH_387
    && (!(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
	|| TARGET_MIX_SSE_I387)
    && flag_unsafe_math_optimizations)
   || (SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
       && !flag_trapping_math)")
  (-1 "TARGET_MMX || (TARGET_SSE2 && V8QImode == V1DImode)")
  (-1 "ix86_binary_operator_ok (XOR, HImode, operands)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode)
   && ix86_binary_operator_ok (MINUS, V4DFmode, operands)")
  (-1 "(((TARGET_80387
     && (!((DImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((DImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
	&& ((DImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "(! TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "optimize_insn_for_speed_p ()
   && (INTVAL (operands[2]) == 3
       || INTVAL (operands[2]) == 5
       || INTVAL (operands[2]) == 9)")
  (-1 "! TARGET_PARTIAL_REG_STALL && reload_completed
   && (GET_MODE (operands[0]) == HImode
       || (GET_MODE (operands[0]) == QImode
	   && (TARGET_PROMOTE_QImode
	       || optimize_insn_for_size_p ())))")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (UMIN, V8HImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (XOR, V4SImode, operands)")
  (-1 "ix86_binary_operator_ok (PLUS, QImode, operands)")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && ((SImode != DImode) || TARGET_64BIT)
   && !flag_trapping_math && !flag_rounding_math")
  (-1 "TARGET_SSE3 && !TARGET_64BIT")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_3DNOW && !TARGET_64BIT")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (LSHIFTRT, HImode, operands)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && !flag_trapping_math && !flag_rounding_math")
  (-1 "TARGET_SSE
   && (register_operand (operands[0], V4SImode)
       || register_operand (operands[1], V4SImode))")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_SAHF && !TARGET_CMOVE
   && (TARGET_USE_SIMODE_FIOP || optimize_function_for_size_p (cfun))
   && (GET_MODE (operands [3]) == GET_MODE (operands[1]))) && ( reload_completed)")
  (-1 "TARGET_80387
   || ((DImode != DImode || TARGET_64BIT)
       && SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_unary_operator_ok (NOT, QImode, operands)")
  (-1 "TARGET_64BIT && reload_completed")
  (-1 "TARGET_64BIT
   && ix86_match_ccmode (insn, CCZmode)
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))
   /* Current assemblers are broken and do not allow @GOTOFF in
      ought but a memory context.  */
   && ! pic_symbolic_operand (operands[2], VOIDmode)")
  (-1 "TARGET_SSE
   && (register_operand (operands[0], V2DFmode)
       || register_operand (operands[1], V2DFmode))")
  (-1 "TARGET_64BIT
   && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_SSE4A")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH")
  (-1 "AVX_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_80387 || (SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_SSE4_1")
  (-1 "(TARGET_CMOVE && !TARGET_PARTIAL_REG_STALL) && ( reload_completed)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH && TARGET_64BIT
   && !flag_trapping_math")
  (-1 "(TARGET_SSE2) && (Pmode == SImode)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && ((SImode != DImode) || TARGET_64BIT)
   && !flag_trapping_math && !flag_rounding_math")
  (-1 "TARGET_SLOW_IMUL_IMM8 && optimize_insn_for_speed_p ()")
  (-1 "SSE_FLOAT_MODE_P (SFmode)
   && (!TARGET_FISTTP || TARGET_SSE_MATH)")
  (-1 "ix86_binary_operator_ok (MINUS, SImode, operands)")
  (-1 "TARGET_64BIT && !TARGET_USE_BT")
  (-1 "TARGET_64BIT && TARGET_80387 && TARGET_CMOVE
   && !(MEM_P (operands[2]) && MEM_P (operands[3]))")
  (-1 "TARGET_SSE2 && TARGET_MIX_SSE_I387 && flag_unsafe_math_optimizations")
  (-1 "TARGET_SSE2 && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "!TARGET_64BIT && ix86_binary_operator_ok (MINUS, DImode, operands)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCmode)
   && ix86_binary_operator_ok (MINUS, SImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (MULT, V4SImode, operands)")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)")
  (-1 "ix86_match_ccmode (insn, CCZmode)
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "(GET_MODE (operands[0]) == QImode
    || GET_MODE (operands[0]) == HImode)
   && (! TARGET_USE_MOV0 || optimize_insn_for_size_p ())
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (IOR, V4SImode, operands)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ASHIFTRT, HImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (PLUS, SImode, operands)
   /* Current assemblers are broken and do not allow @GOTOFF in
      ought but a memory context.  */
   && ! pic_symbolic_operand (operands[2], VOIDmode)")
  (-1 "TARGET_3DNOW && ix86_binary_operator_ok (PLUS, V2SFmode, operands)")
  (-1 "(optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_FLAG_REG_STALL)
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (LSHIFTRT, QImode, operands)")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && reload_completed")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (XOR, V16QImode, operands)")
  (-1 "TARGET_64BIT
   &&  ix86_match_ccmode (insn, CCGCmode)")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && !(reload_completed || reload_in_progress)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (IOR, V4SFmode, operands)")
  (-1 "TARGET_SSE5
   && (register_operand (operands[1], V4SImode)
       || register_operand (operands[2], V16QImode))")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (IOR, V16QImode, operands)")
  (-1 "TARGET_3DNOW && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_64BIT && optimize_function_for_speed_p (cfun) && !TARGET_USE_CLTD")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (MINUS, SImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCmode)
   && ix86_binary_operator_ok (MINUS, QImode, operands)")
  (-1 "!(MEM_P (operands[0]) && MEM_P (operands[1]))
    && ix86_match_ccmode (insn, CCmode)")
  (-1 "AVX_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && !COMMUTATIVE_ARITH_P (operands[3])")
  (-1 "TARGET_80387
   && (reload_completed
       || !(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH))")
  (-1 "TARGET_80387
    && (!(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
        || TARGET_MIX_SSE_I387)
    && reload_completed")
  (-1 "(TARGET_SSE2) && (Pmode == DImode)")
  (-1 "TARGET_USE_FANCY_MATH_387
   && (!TARGET_SSE_MATH || TARGET_MIX_SSE_I387)
   && flag_unsafe_math_optimizations")
  (-1 "TARGET_80387 || (TARGET_SSE2 && TARGET_SSE_MATH)")
  (-1 "TARGET_80387
   && !(SSE_FLOAT_MODE_P (SFmode) && (!TARGET_FISTTP || TARGET_SSE_MATH))")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (UMAX, V4SImode, operands)")
  (-1 "!(TARGET_64BIT || TARGET_SSE2)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (SMIN, V8HImode, operands)")
  (-1 "TARGET_SSE2 && TARGET_MIX_SSE_I387")
  (-1 "!(MEM_P (operands[0]) && MEM_P (operands[1]))
    && ix86_match_ccmode (insn,
 			 CONST_INT_P (operands[1])
 			 && INTVAL (operands[1]) >= 0 ? CCNOmode : CCZmode)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (AND, V4SFmode, operands)")
  (-1 "TARGET_PARTIAL_REG_STALL")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (IOR, V2DImode, operands)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && TARGET_INTER_UNIT_CONVERSIONS
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_64BIT
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_3DNOW && flag_finite_math_only
   && ix86_binary_operator_ok (SMIN, V2SFmode, operands)")
  (-1 "ix86_binary_operator_ok (AND, SImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (AND, V16QImode, operands)")
  (-1 "TARGET_USE_FANCY_MATH_387
   || (SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)")
  (-1 "!TARGET_64BIT
   && ((TARGET_80387 && TARGET_SSE)
       || (SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH))")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SS_MINUS, V8HImode, operands)")
  (-1 "AVX_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_64BIT
   && ix86_match_ccmode (insn, CCNOmode)
   && INTVAL (operands[1]) > 0
   && INTVAL (operands[2]) >= 0
   /* Ensure that resulting mask is zero or sign extended operand.  */
   && (INTVAL (operands[1]) + INTVAL (operands[2]) <= 32
       || (INTVAL (operands[1]) + INTVAL (operands[2]) == 64
	   && INTVAL (operands[1]) > 32))
   && (GET_MODE (operands[0]) == SImode
       || GET_MODE (operands[0]) == DImode
       || GET_MODE (operands[0]) == HImode
       || GET_MODE (operands[0]) == QImode)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_SSE2 && TARGET_SSE_MATH
   && TARGET_USE_VECTOR_CONVERTS && optimize_function_for_speed_p (cfun)
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_SSE2 && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "(TARGET_XADD) && (TARGET_64BIT)")
  (-1 "((TARGET_80387
     && (!((DImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((DImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH
	&& ((DImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_80387
   || ((DImode != DImode || TARGET_64BIT)
       && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATE, SImode, operands)")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V16QImode)
       || register_operand (operands[1], V16QImode))")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && !COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_MMX || (TARGET_SSE2 && V4HImode == V1DImode)")
  (-1 "reload_completed
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))
   && ! (ANY_FP_REG_P (operands[0]) ||
	 (GET_CODE (operands[0]) == SUBREG
	  && ANY_FP_REG_P (SUBREG_REG (operands[0]))))
   && ! (ANY_FP_REG_P (operands[1]) ||
	 (GET_CODE (operands[1]) == SUBREG
	  && ANY_FP_REG_P (SUBREG_REG (operands[1]))))")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (EQ, V8QImode, operands)")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_SAHF && !TARGET_CMOVE
   && GET_MODE (operands[1]) == GET_MODE (operands[2])) && ( reload_completed)")
  (-1 "reload_completed
    && ANY_QI_REG_P (operands[0])
    && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
    && !(~INTVAL (operands[2]) & ~255)
    && !(INTVAL (operands[2]) & 128)
    && GET_MODE (operands[0]) != QImode")
  (-1 "SSE_FLOAT_MODE_P (SFmode)")
  (-1 "TARGET_64BIT
   && reload_completed
   && operands[1] == constm1_rtx")
  (-1 "ix86_binary_operator_ok (ASHIFT, SImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (MULT, V4SFmode, operands)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SMIN, V4SImode, operands)")
  (-1 "TARGET_64BIT && TARGET_CMOVE
   && !(MEM_P (operands[2]) && MEM_P (operands[3]))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode)")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && !TARGET_FISTTP
   && !(SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || SImode != DImode))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "TARGET_64BIT
   && ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (XOR, DImode, operands)")
  (-1 "TARGET_80387
   && !COMMUTATIVE_ARITH_P (operands[3])")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (MINUS, SImode, operands)")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V4DImode)
       || register_operand (operands[1], V4DImode))")
  (-1 "ix86_binary_operator_ok (PLUS, SImode, operands)")
  (-1 "TARGET_64BIT && (TARGET_USE_BT || optimize_function_for_size_p (cfun))")
  (-1 "!TARGET_64BIT
   && TARGET_80387 && TARGET_SSE
   && reload_completed")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && !TARGET_SSE5")
  (-1 "TARGET_SSE && TARGET_64BIT")
  (-1 "TARGET_80387 && (TARGET_USE_SIMODE_FIOP || optimize_function_for_size_p (cfun))")
  (-1 "ix86_binary_operator_ok (ROTATERT, HImode, operands)")
  (-1 "TARGET_SSE && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_SSE2 && !TARGET_SSE4_1 && !TARGET_SSE5
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_SSE
   && (register_operand (operands[0], V16QImode)
       || register_operand (operands[1], V16QImode))")
  (-1 "REGNO (operands[0]) != REGNO (operands[1])")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && ((SImode != DImode) || TARGET_64BIT)")
  (-1 "!TARGET_64BIT && ix86_match_ccmode (insn, CCmode)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (MULT, V2DFmode, operands)")
  (-1 "!TARGET_64BIT
   && ((TARGET_80387 && TARGET_SSE)
       || (SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH))")
  (-1 "(optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_REG_STALL) && reload_completed")
  (-1 "TARGET_80387
   && (reload_completed
       || !(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH))")
  (-1 "TARGET_SSE || TARGET_3DNOW_A")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode)
   && ix86_binary_operator_ok (IOR, V8SFmode, operands)")
  (-1 "TARGET_ABM")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && TARGET_INTER_UNIT_CONVERSIONS
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (AND, SImode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (PLUS, V4SFmode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (ASHIFTRT, DImode, operands)")
  (-1 "(((!TARGET_FUSE_CMP_AND_BRANCH || optimize_size)
     && incdec_operand (operands[3], GET_MODE (operands[3])))
    || (!TARGET_FUSE_CMP_AND_BRANCH
	&& INTVAL (operands[3]) == 128))
   && ix86_match_ccmode (insn, CCGCmode)
   && peep2_reg_dead_p (1, operands[2])")
  (-1 "ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "TARGET_SSE2 && reload_completed")
  (-1 "(TARGET_SSE5 && ix86_sse5_valid_op_p (operands, insn, 4, false, -1, true)) && ( (reload_completed
       || (!reg_mentioned_p (operands[0], operands[1])
	   && !reg_mentioned_p (operands[0], operands[2]))))")
  (-1 "!SIBLING_CALL_P (insn) && TARGET_64BIT")
  (-1 "TARGET_64BIT && TARGET_AVX
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (SS_PLUS, V4HImode, operands)")
  (-1 "TARGET_80387
   && TARGET_SAHF && !TARGET_CMOVE")
  (-1 "!TARGET_64BIT && TARGET_CMPXCHG8B && !flag_pic")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (SS_MINUS, V8QImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (AND, V4SImode, operands)")
  (-1 "TARGET_AVOID_VECTOR_DECODE && optimize_insn_for_speed_p ()")
  (-1 "ix86_binary_operator_ok (AND, QImode, operands)
   && ix86_match_ccmode (insn,
			 CONST_INT_P (operands[2])
			 && INTVAL (operands[2]) >= 0 ? CCNOmode : CCZmode)")
  (-1 "TARGET_SHORTEN_X87_SSE
   && peep2_reg_dead_p (2, operands[0])")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (MINUS, QImode, operands)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (IOR, V2SImode, operands)")
  (-1 "TARGET_SSE2 && !TARGET_SSE5
   && ix86_binary_operator_ok (EQ, V16QImode, operands)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SS_PLUS, V8HImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (IOR, V16QImode, operands)")
  (-1 "ix86_binary_operator_ok (PLUS, HImode, operands)")
  (-1 "TARGET_PARTIAL_REG_STALL
   && ix86_binary_operator_ok (PLUS, QImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (MULT, V2DFmode, operands)")
  (-1 "optimize_insn_for_speed_p () && ix86_match_ccmode (insn, CCNOmode)")
  (-1 "ix86_match_ccmode (insn, CCGCmode)
   && (INTVAL (operands[2]) & 0xffffffff) != 0x80000000")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V2DFmode)
       || register_operand (operands[1], V2DFmode))")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && ((DImode != DImode) || TARGET_64BIT)
   && !flag_trapping_math && !flag_rounding_math")
  (-1 "!TARGET_PARTIAL_REG_STALL
   && ix86_binary_operator_ok (ASHIFT, HImode, operands)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_MMX && !TARGET_SSE")
  (-1 "TARGET_3DNOW_A")
  (-1 "!(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 3
   /* Validate MODE for lea.  */
   && ((!TARGET_PARTIAL_REG_STALL
	&& (GET_MODE (operands[0]) == QImode
	    || GET_MODE (operands[0]) == HImode))
       || GET_MODE (operands[0]) == SImode
       || (TARGET_64BIT && GET_MODE (operands[0]) == DImode))
   /* We reorder load and the shift.  */
   && !rtx_equal_p (operands[1], operands[3])
   && !reg_overlap_mentioned_p (operands[0], operands[4])
   /* Last PLUS must consist of operand 0 and 3.  */
   && !rtx_equal_p (operands[0], operands[3])
   && (rtx_equal_p (operands[3], operands[6])
       || rtx_equal_p (operands[3], operands[7]))
   && (rtx_equal_p (operands[0], operands[6])
       || rtx_equal_p (operands[0], operands[7]))
   /* The intermediate operand 0 must die or be same as output.  */
   && (rtx_equal_p (operands[0], operands[5])
       || peep2_reg_dead_p (3, operands[0]))")
  (-1 "TARGET_64BIT && SSE_FLOAT_MODE_P (SFmode)
   && (!TARGET_FISTTP || TARGET_SSE_MATH)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (US_MINUS, V4HImode, operands)")
  (-1 "ix86_binary_operator_ok (IOR, HImode, operands)")
  (-1 "!(MEM_P (operands[0]) && MEM_P (operands[1]))
   && ix86_match_ccmode (insn, CCNOmode)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || HImode != DImode))
	&& TARGET_SSE_MATH)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || DImode != DImode))
	&& TARGET_SSE_MATH)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (AND, V4SFmode, operands)")
  (-1 "TARGET_SSE3 && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && !TARGET_FISTTP
   && !(SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || HImode != DImode))
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_PARTIAL_REG_STALL
   && ix86_binary_operator_ok (ASHIFT, QImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (IOR, TFmode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMAX, V4SFmode, operands)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_SSSE3 && ix86_binary_operator_ok (MULT, V4HImode, operands)")
  (-1 "(optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_FLAG_REG_STALL)
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, QImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (AND, V4DImode, operands)")
  (-1 "TARGET_80387 && (!TARGET_SSE_MATH || TARGET_MIX_SSE_I387)")
  (-1 "(TARGET_POPCNT && ix86_match_ccmode (insn, CCZmode)) && (TARGET_64BIT)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (XOR, V4SFmode, operands)")
  (-1 "TARGET_3DNOW && ix86_binary_operator_ok (MULT, V2SFmode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode) && !TARGET_SSE5")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (UMAX, V4SImode, operands)")
  (-1 "TARGET_64BIT && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "(((TARGET_80387
     && (!((SImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((SImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
	&& ((SImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
   || (TARGET_SSE2 && (DFmode == TFmode))")
  (-1 "(TARGET_SSE && !(MEM_P (operands[0]) && MEM_P (operands[1]))) && ( reload_completed)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && GET_MODE (operands[1]) == GET_MODE (operands[2])
   && ix86_fp_jump_nontrivial_p (GET_CODE (operands[0]))")
  (-1 "ix86_binary_operator_ok (XOR, QImode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (PLUS, TImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCGCmode)
   && (INTVAL (operands[2]) & 0xff) != 0x80")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (AND, SImode, operands)")
  (-1 "TARGET_64BIT && ix86_unary_operator_ok (NEG, SImode, operands)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (LSHIFTRT, HImode, operands)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (XOR, V8QImode, operands)")
  (-1 "TARGET_USE_FANCY_MATH_387
   && TARGET_C99_FUNCTIONS
   && !(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)")
  (-1 "optimize_insn_for_speed_p () && ! TARGET_READ_MODIFY_WRITE")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH")
  (-1 "TARGET_QIMODE_MATH")
  (-1 "!TARGET_64BIT
   && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_80387 || (TARGET_64BIT && SSE_FLOAT_MODE_P (DFmode))")
  (-1 "TARGET_MIX_SSE_I387
   && SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
   && GET_MODE (operands[1]) == GET_MODE (operands[2])
   && ix86_fp_jump_nontrivial_p (GET_CODE (operands[0]))")
  (-1 "optimize_function_for_speed_p (cfun)")
  (-1 "!TARGET_64BIT && ((optimize > 0 && flag_peephole2)
		     ? epilogue_completed : reload_completed)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (IOR, HImode, operands)")
  (-1 "!(MEM_P (operands[0]) && MEM_P (operands[1]))
   && optimize_function_for_speed_p (cfun)
   && TARGET_INTEGER_DFMODE_MOVES
   && (reload_in_progress || reload_completed
       || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
       || (!(TARGET_SSE2 && TARGET_SSE_MATH)
           && optimize_function_for_size_p (cfun)
	   && standard_80387_constant_p (operands[1]))
       || GET_CODE (operands[1]) != CONST_DOUBLE
       || memory_operand (operands[0], DFmode))")
  (-1 "(TARGET_80387
   && (!(SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (XOR, V2DImode, operands)")
  (-1 "ix86_binary_operator_ok (ROTATE, QImode, operands)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCGOCmode)")
  (-1 "TARGET_SSE5 && ix86_sse5_valid_op_p (operands, insn, 3, true, 1, false)")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V8HImode)
       || register_operand (operands[1], V8HImode))")
  (-1 "((SSE_FLOAT_MODE_P (TFmode) && TARGET_SSE_MATH)
    || (TARGET_SSE2 && (TFmode == TFmode)))
   && reload_completed")
  (-1 "ix86_binary_operator_ok (ROTATERT, QImode, operands)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (UMIN, V4SImode, operands)")
  (-1 "optimize_insn_for_size_p () || !TARGET_ADD_ESP_4")
  (-1 "! TARGET_PARTIAL_REG_STALL
   && ix86_match_ccmode (insn, CCNOmode)
   && true_regnum (operands[2]) != AX_REG
   && peep2_reg_dead_p (1, operands[2])")
  (-1 "(TARGET_64BIT && (TARGET_USE_BT || optimize_function_for_size_p (cfun))
   && (INTVAL (operands[3]) & 0x3f) == 0x3f) && ( 1)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)
   && ix86_unary_operator_ok (NOT, DImode, operands)")
  (-1 "TARGET_ROUND")
  (-1 "TARGET_64BIT && !symbolic_operand (operands[1], DImode)
   && !x86_64_immediate_operand (operands[1], DImode) && 1")
  (-1 "TARGET_ZERO_EXTEND_WITH_AND && optimize_function_for_speed_p (cfun)")
  (-1 "!TARGET_64BIT && TARGET_AVX")
  (-1 "(((TARGET_80387
     && (!((SImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((SImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
	&& ((SImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (US_MINUS, V8QImode, operands)")
  (-1 "(TARGET_MMX || (TARGET_SSE2 && V2SImode == V1DImode))
   && ix86_binary_operator_ok (PLUS, V2SImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode)
   && ix86_binary_operator_ok (XOR, V4DFmode, operands)")
  (-1 "reload_completed
    && ANY_QI_REG_P (operands[0])
    && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
    && !(INTVAL (operands[2]) & ~255)
    && (INTVAL (operands[2]) & 128)
    && GET_MODE (operands[0]) != QImode")
  (-1 "!(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (AND, V16HImode, operands)")
  (-1 "TARGET_64BIT && (TARGET_USE_BT || optimize_function_for_size_p (cfun))
   && (INTVAL (operands[3]) & 0x3f) == 0x3f")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (SS_PLUS, V8QImode, operands)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && ((DImode != DImode) || TARGET_64BIT)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (MINUS, V2DImode, operands)")
  (-1 "!TARGET_64BIT
   && TARGET_SSE2 && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "ix86_binary_operator_ok (LSHIFTRT, QImode, operands)")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (UMIN, V4SImode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (PLUS, DImode, operands)")
  (-1 "AVX_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && !COMMUTATIVE_ARITH_P (operands[3])")
  (-1 "(!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))")
  (-1 "((SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
    || (TARGET_SSE2 && (DFmode == TFmode)))
   && reload_completed")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (AND, V8HImode, operands)")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (US_MINUS, V8HImode, operands)")
  (-1 "(peep2_reg_dead_p (3, operands[1])
    || operands_match_p (operands[1], operands[3]))
   && ! reg_overlap_mentioned_p (operands[3], operands[0])")
  (-1 "(TARGET_USE_FANCY_MATH_387
    && (!(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
	|| TARGET_MIX_SSE_I387)
    && flag_unsafe_math_optimizations)
   || (SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
       && !flag_trapping_math)")
  (-1 "(TARGET_MMX || (TARGET_SSE2 && V2SImode == V1DImode))
   && ix86_binary_operator_ok (MINUS, V2SImode, operands)")
  (-1 "(ix86_binary_operator_ok (MINUS, DImode, operands)) && (TARGET_64BIT)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (UMAX, V8HImode, operands)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "reload_completed
   && operands[1] == constm1_rtx")
  (-1 "TARGET_SSE5")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (EQ, V2DImode, operands)")
  (-1 "(GET_MODE (operands[0]) == HImode
    || GET_MODE (operands[0]) == SImode
    || (GET_MODE (operands[0]) == DImode && TARGET_64BIT))
   && (optimize_insn_for_size_p () || TARGET_MOVE_M1_VIA_OR)
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "TARGET_80387 && TARGET_SSE2 && TARGET_INTER_UNIT_MOVES
   && !TARGET_64BIT && optimize_function_for_speed_p (cfun)
   && reload_completed
   && FP_REG_P (operands[0])")
  (-1 "TARGET_QIMODE_MATH
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_AVX && !TARGET_64BIT")
  (-1 "!TARGET_64BIT && TARGET_80387 && TARGET_CMOVE
   && !(MEM_P (operands[2]) && MEM_P (operands[3]))")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && INTVAL (operands[1]) > 0
   && INTVAL (operands[2]) >= 0
   && INTVAL (operands[1]) + INTVAL (operands[2]) <= 32
   && (GET_MODE (operands[0]) == SImode
       || (TARGET_64BIT && GET_MODE (operands[0]) == DImode)
       || GET_MODE (operands[0]) == HImode
       || GET_MODE (operands[0]) == QImode)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (MINUS, V8HImode, operands)")
  (-1 "TARGET_MIX_SSE_I387 && SSE_FLOAT_MODE_P (SFmode)")
  (-1 "TARGET_SSE2 && TARGET_SSE_MATH
   && TARGET_USE_VECTOR_CONVERTS && optimize_function_for_speed_p (cfun)")
  (-1 "(TARGET_80387
   && (!(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "peep2_regno_dead_p (0, FLAGS_REG) && REGNO (operands[0]) == REGNO (operands[1])")
  (-1 "TARGET_80387
   && reload_completed
   && FP_REG_P (operands[0])")
  (-1 "!TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "(TARGET_CMPXCHG) && (TARGET_64BIT || TARGET_CMPXCHG8B)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (UMAX, V16QImode, operands)")
  (-1 "TARGET_80387 || SSE_FLOAT_MODE_P (SFmode)")
  (-1 "((SSE_FLOAT_MODE_P (TFmode) && TARGET_SSE_MATH)
   || (TARGET_SSE2 && (TFmode == TFmode))) && ( reload_completed)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "INTVAL (operands[2]) == 3
   || INTVAL (operands[2]) == 5
   || INTVAL (operands[2]) == 9")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (PLUS, V16QImode, operands)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ASHIFTRT, QImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "!TARGET_64BIT && TARGET_CMPXCHG8B && flag_pic")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
   && (TARGET_USE_HIMODE_FIOP || optimize_function_for_size_p (cfun))")
  (-1 "(TARGET_80387
   && TARGET_SAHF && !TARGET_CMOVE) && ( reload_completed)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (IOR, SImode, operands)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || SImode != DImode))
	&& TARGET_SSE_MATH)
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (AND, V4HImode, operands)")
  (-1 "TARGET_64BIT && ix86_unary_operator_ok (NEG, DImode, operands)")
  (-1 "TARGET_SSE2 && TARGET_64BIT")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (IOR, V4HImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode)
   && ix86_binary_operator_ok (AND, V8SFmode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMIN, V2DFmode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_SSE5 && ix86_sse5_valid_op_p (operands, insn, 4, false, 1, true)")
  (-1 "TARGET_64BIT
   && (optimize_function_for_size_p (cfun)
       || !TARGET_PARTIAL_FLAG_REG_STALL
       || (operands[2] == const1_rtx
	   && (TARGET_SHIFT1
	       || (TARGET_DOUBLE_WITH_ADD && REG_P (operands[0])))))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, DImode, operands)")
  (-1 "TARGET_USE_FANCY_MATH_387
   && !(SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (IOR, V8SImode, operands)")
  (-1 "TARGET_64BIT && ix86_unary_operator_ok (NOT, DImode, operands)")
  (-1 "reload_completed
   && ANY_QI_REG_P (operands[0])
   && (TARGET_ZERO_EXTEND_WITH_AND
       && optimize_function_for_speed_p (cfun))
   && !reg_overlap_mentioned_p (operands[0], operands[1])")
  (-1 "TARGET_USE_FANCY_MATH_387
   && !(reload_completed || reload_in_progress)")
  (-1 "! TARGET_PARTIAL_REG_STALL && reload_completed
   && ((GET_MODE (operands[0]) == HImode
	&& ((optimize_function_for_speed_p (cfun) && !TARGET_FAST_PREFIX)
            /* ??? next two lines just !satisfies_constraint_K (...) */
	    || !CONST_INT_P (operands[2])
	    || satisfies_constraint_K (operands[2])))
       || (GET_MODE (operands[0]) == QImode
	   && (TARGET_PROMOTE_QImode || optimize_function_for_size_p (cfun))))")
  (-1 "(TARGET_SSE) && ( reload_completed
   && (TARGET_INTER_UNIT_MOVES
       || MEM_P (operands [0])
       || !GENERAL_REGNO_P (true_regnum (operands [0]))))")
  (-1 "TARGET_USE_VECTOR_FP_CONVERTS
   && optimize_insn_for_speed_p ()
   && reload_completed && SSE_REG_P (operands[0])")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (PLUS, V8HImode, operands)")
  (-1 "!TARGET_64BIT && reload_completed
   && (!MMX_REG_P (operands[0]) && !SSE_REG_P (operands[0]))
   && (!MMX_REG_P (operands[1]) && !SSE_REG_P (operands[1]))")
  (-1 "(TARGET_MMX || (TARGET_SSE2 && V8QImode == V1DImode))
   && ix86_binary_operator_ok (PLUS, V8QImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (AND, V32QImode, operands)")
  (-1 "!TARGET_64BIT && reload_completed
   && true_regnum (operands[0]) == true_regnum (operands[1])")
  (-1 "ix86_binary_operator_ok (AND, HImode, operands)")
  (-1 "TARGET_USE_BT || optimize_function_for_size_p (cfun)")
  (-1 "(TARGET_64BIT && (TARGET_USE_BT || optimize_function_for_size_p (cfun))) && ( 1)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATERT, QImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (SS_PLUS, V16QImode, operands)")
  (-1 "TARGET_SSE5
   && !ix86_sse5_valid_op_p (operands, insn, 4, true, 1, false)
   && ix86_sse5_valid_op_p (operands, insn, 4, true, 2, false)
   && !reg_mentioned_p (operands[0], operands[1])
   && !reg_mentioned_p (operands[0], operands[2])
   && !reg_mentioned_p (operands[0], operands[3])")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (MINUS, V4SImode, operands)")
  (-1 "AVX_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH")
  (-1 "(optimize_function_for_size_p (cfun)
    || !TARGET_PARTIAL_FLAG_REG_STALL
    || (operands[2] == const1_rtx
	&& (TARGET_SHIFT1
	    || TARGET_DOUBLE_WITH_ADD)))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, SImode, operands)")
  (-1 "TARGET_CMOVE
   && !(MEM_P (operands[2]) && MEM_P (operands[3]))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "AVX_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && !COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_SSE2 && !TARGET_SSE5
   && ix86_binary_operator_ok (EQ, V4SImode, operands)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (LSHIFTRT, QImode, operands)")
  (-1 "TARGET_POPCNT")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "(SSE_FLOAT_MODE_P (V2DFmode) || SSE_VEC_FLOAT_MODE_P (V2DFmode))
   && !TARGET_SSE5")
  (-1 "(TARGET_SSE5) && ( (reload_completed
       || (!reg_mentioned_p (operands[0], operands[1])
	   && !reg_mentioned_p (operands[0], operands[2]))))")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (PLUS, V2DImode, operands)")
  (-1 "!TARGET_64BIT && TARGET_SSE2 && TARGET_SSE_MATH
   && optimize_function_for_speed_p (cfun)")
  (-1 "ix86_unary_operator_ok (NEG, QImode, operands)")
  (-1 "TARGET_AVX && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
   && (TARGET_USE_SIMODE_FIOP || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (MINUS, V16QImode, operands)")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (UMAX, V8HImode, operands)")
  (-1 "TARGET_USE_FANCY_MATH_387
   && (!(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && flag_unsafe_math_optimizations
   && standard_80387_constant_p (operands[3]) == 2")
  (-1 "TARGET_USE_FANCY_MATH_387
   && flag_unsafe_math_optimizations")
  (-1 "(TARGET_SSE && !TARGET_SSE2)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && !TARGET_FISTTP
   && !(SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || DImode != DImode))
   && !(reload_completed || reload_in_progress)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMIN, V2DFmode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (ROTATERT, SImode, operands)")
  (-1 "TARGET_MIX_SSE_I387 && SSE_FLOAT_MODE_P (DFmode)")
  (-1 "(TARGET_USE_BT || optimize_function_for_size_p (cfun)) && ( 1)")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATERT, SImode, operands)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (XOR, SImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMIN, V4DFmode, operands)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "ix86_unary_operator_ok (NOT, HImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (IOR, V16HImode, operands)")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && !TARGET_FISTTP
   && !(SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || HImode != DImode))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (EQ, V16QImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (XOR, V8HImode, operands)")
  (-1 "Pmode == SImode")
  (-1 "TARGET_USE_FANCY_MATH_387
   && flag_unsafe_math_optimizations
   && !(reload_completed || reload_in_progress)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "(TARGET_80387
   && (!(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "(!TARGET_64BIT && TARGET_SSE2 && TARGET_SSE_MATH
   && optimize_function_for_speed_p (cfun)) && ( reload_completed)")
  (-1 "(! TARGET_POPCNT) && ( reload_completed)")
  (-1 "TARGET_64BIT
   && (optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_FLAG_REG_STALL)
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)")
  (-1 "(optimize_function_for_size_p (cfun)
    || !TARGET_PARTIAL_FLAG_REG_STALL
    || (operands[2] == const1_rtx
	&& (TARGET_SHIFT1
	    || (TARGET_DOUBLE_WITH_ADD && REG_P (operands[0])))))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, HImode, operands)")
  (-1 "reload_completed
   && !(SSE_REG_P (operands[0]) || SSE_REG_P (operands[1]))")
  (-1 "TARGET_64BIT
   && (optimize_function_for_size_p (cfun)
       || !TARGET_PARTIAL_FLAG_REG_STALL
       || (operands[2] == const1_rtx
	   && (TARGET_SHIFT1
	       || TARGET_DOUBLE_WITH_ADD)))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, SImode, operands)")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && !(reload_completed || reload_in_progress)")
  (-1 "(TARGET_SSE2 && !TARGET_SSE4_1 && !TARGET_SSE5
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "optimize_function_for_speed_p (cfun)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))
   && (reload_in_progress || reload_completed
       || GET_CODE (operands[1]) != CONST_DOUBLE
       || memory_operand (operands[0], XFmode))")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SS_MINUS, V16QImode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (MINUS, V2DFmode, operands)")
  (-1 "TARGET_64BIT && TARGET_GNU2_TLS")
  (-1 "(TARGET_SSE2) && (TARGET_SSE4_2 || TARGET_SSE5)")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (AND, V2DImode, operands)")
  (-1 "TARGET_64BIT
   && (optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_FLAG_REG_STALL)
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, DImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (IOR, V4SImode, operands)")
  (-1 "reload_completed
   && ANY_QI_REG_P (operands[0])
   && (ANY_QI_REG_P (operands[1]) || MEM_P (operands[1]))
   && (TARGET_ZERO_EXTEND_WITH_AND && optimize_function_for_speed_p (cfun))
   && !reg_overlap_mentioned_p (operands[0], operands[1])")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (XOR, TFmode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (AND, TFmode, operands)")
  (-1 "TARGET_SLOW_IMUL_IMM8 && optimize_insn_for_speed_p ()
   && satisfies_constraint_K (operands[2])")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (XOR, QImode, operands)")
  (-1 "optimize_insn_for_speed_p ()
   && TARGET_SPLIT_LONG_MOVES
   && get_attr_length (insn) >= ix86_cur_cost ()->large_insn")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	&& (TARGET_64BIT || HImode != DImode))
	&& TARGET_SSE_MATH)")
  (-1 "reload_completed
   && true_regnum (operands[0]) == true_regnum (operands[1])")
  (-1 "TARGET_64BIT && TARGET_CMPXCHG16B")
  (-1 "TARGET_64BIT && INTVAL (operands[2]) == 63
   && (TARGET_USE_CLTD || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ASHIFTRT, DImode, operands)")
  (-1 "TARGET_SSE2 && TARGET_SSE_MATH")
  (-1 "TARGET_SSE5
   && !ix86_sse5_valid_op_p (operands, insn, 4, false, 1, true)
   && ix86_sse5_valid_op_p (operands, insn, 4, false, 2, true)
   && !reg_mentioned_p (operands[0], operands[1])
   && !reg_mentioned_p (operands[0], operands[2])
   && !reg_mentioned_p (operands[0], operands[3])")
  (-1 "(GET_MODE (operands[0]) == QImode || GET_MODE (operands[0]) == HImode
    || (TARGET_64BIT && GET_MODE (operands[0]) == SImode))
   && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && GET_MODE (operands[0]) == GET_MODE (operands[1])
   && GET_MODE (operands[0]) == GET_MODE (operands[2])
   && (GET_MODE (operands[0]) == GET_MODE (operands[3])
       || GET_MODE (operands[3]) == VOIDmode)")
  (-1 "TARGET_80387
   || ((SImode != DImode || TARGET_64BIT)
       && SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)")
  (-1 "ix86_binary_operator_ok (ROTATE, SImode, operands)")
  (-1 "!TARGET_64BIT && TARGET_GNU2_TLS")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (AND, V16QImode, operands)")
  (-1 "TARGET_80387 && flag_unsafe_math_optimizations")
  (-1 "(! TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SS_PLUS, V16QImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (AND, V2DFmode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (PLUS, SImode, operands)")
  (-1 "((TARGET_USE_BT || optimize_function_for_size_p (cfun))
   && (INTVAL (operands[3]) & 0x1f) == 0x1f) && ( 1)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode)")
  (-1 "TARGET_64BIT
   && ix86_unary_operator_ok (NEG, TImode, operands)")
  (-1 "ix86_binary_operator_ok (IOR, QImode, operands)")
  (-1 "TARGET_PCLMUL && TARGET_AVX")
  (-1 "peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && reload_completed")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && ((SImode != DImode) || TARGET_64BIT)")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)")
  (-1 "TARGET_AVX
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATERT, SImode, operands)")
  (-1 "(TARGET_80387 && TARGET_CMOVE)
   || (SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)")
  (-1 "ix86_match_ccmode (insn, CCmode)
   && ix86_binary_operator_ok (MINUS, HImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (IOR, V2DFmode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (ROTATE, DImode, operands)")
  (-1 "TARGET_64BIT && TARGET_SSE_MATH")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH")
  (-1 "TARGET_80387
   || ((SImode != DImode || TARGET_64BIT)
       && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (MINUS, V4SImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCmode)
   && ix86_binary_operator_ok (MINUS, SImode, operands)")
  (-1 "(TARGET_SSE || TARGET_3DNOW_A)
   && ix86_binary_operator_ok (PLUS, V4HImode, operands)")
  (-1 "TARGET_3DNOW && flag_finite_math_only
   && ix86_binary_operator_ok (SMAX, V2SFmode, operands)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_CMOVE
   && GET_MODE (operands[1]) == GET_MODE (operands[2])
   && ix86_fp_jump_nontrivial_p (GET_CODE (operands[0]))")
  (-1 "TARGET_80387
   && (reload_completed
       || !(SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH))")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || SImode != DImode))
	&& TARGET_SSE_MATH)
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "(TARGET_CMPXCHG) && (TARGET_64BIT)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMIN, V8SFmode, operands)")
  (-1 "TARGET_SSE5 && ix86_sse5_valid_op_p (operands, insn, 4, false, 2, true)")
  (-1 "AVX_FLOAT_MODE_P (DFmode)")
  (-1 "!TARGET_64BIT && !SIBLING_CALL_P (insn)")
  (-1 "TARGET_80387
   && !(TARGET_SSE2 && TARGET_SSE_MATH)
   && !TARGET_MIX_SSE_I387")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && !flag_trapping_math")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ASHIFTRT, DImode, operands)")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
   && !COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_USE_FANCY_MATH_387
   && !(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)")
  (-1 "(TARGET_80387 && TARGET_CMOVE)
   || (SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)")
  (-1 "reload_completed
   && (!TARGET_ZERO_EXTEND_WITH_AND || optimize_function_for_size_p (cfun))
   && (!REG_P (operands[1]) || ANY_QI_REG_P (operands[1]))")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && !TARGET_FISTTP
   && !SSE_FLOAT_MODE_P (GET_MODE (operands[1]))")
  (-1 "TARGET_64BIT && SSE_FLOAT_MODE_P (DFmode)
   && (!TARGET_FISTTP || TARGET_SSE_MATH)")
  (-1 "TARGET_USE_FANCY_MATH_387
   && (!(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && flag_unsafe_math_optimizations
   && standard_80387_constant_p (operands[3]) == 2")
  (-1 "TARGET_80387
   && (GET_MODE (operands[1]) == SFmode || GET_MODE (operands[1]) == DFmode)
   && GET_MODE (operands[1]) == GET_MODE (operands[2])
   && !ix86_use_fcomi_compare (GET_CODE (operands[0]))
   && SELECT_CC_MODE (GET_CODE (operands[0]),
		      operands[1], operands[2]) == CCFPmode
   && ix86_fp_jump_nontrivial_p (GET_CODE (operands[0]))")
  (-1 "(TARGET_SSE || TARGET_3DNOW_A)
   && ix86_binary_operator_ok (UMIN, V8QImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (MULT, V8HImode, operands)")
  (-1 "(SSE_FLOAT_MODE_P (V4SFmode) || SSE_VEC_FLOAT_MODE_P (V4SFmode))
   && !TARGET_SSE5")
  (-1 "!TARGET_64BIT
   && ix86_unary_operator_ok (NEG, DImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (PLUS, V2DFmode, operands)")
  (-1 "optimize_insn_for_size_p () || !TARGET_SUB_ESP_4")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (XOR, V32QImode, operands)")
  (-1 "TARGET_80387
   && !(SSE_FLOAT_MODE_P (XFmode) && (!TARGET_FISTTP || TARGET_SSE_MATH))")
  (-1 "TARGET_MMX && reload_completed")
  (-1 "TARGET_SSE_MATH
   && SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
   && GET_MODE (operands[1]) == GET_MODE (operands[2])
   && ix86_fp_jump_nontrivial_p (GET_CODE (operands[0]))")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (AND, V2DImode, operands)")
  (-1 "TARGET_SSE2 && !TARGET_SSE5
   && ix86_binary_operator_ok (EQ, V8HImode, operands)")
  (-1 "TARGET_CMOVE && !TARGET_PARTIAL_REG_STALL")
  (-1 "reload_completed
   && X87_FLOAT_MODE_P (GET_MODE (operands[0]))")
  (-1 "reload_completed
   && (GET_MODE (operands[0]) == XFmode
       || GET_MODE (operands[0]) == DFmode)
   && !ANY_FP_REG_P (operands[1])")
  (-1 "! TARGET_PARTIAL_REG_STALL && reload_completed
   && optimize_insn_for_speed_p ()
   && ((GET_MODE (operands[1]) == HImode && ! TARGET_FAST_PREFIX)
       || (GET_MODE (operands[1]) == QImode && TARGET_PROMOTE_QImode))
   /* Ensure that the operand will remain sign-extended immediate.  */
   && ix86_match_ccmode (insn, INTVAL (operands[4]) >= 0 ? CCNOmode : CCZmode)")
  (-1 "TARGET_80387 && !(TARGET_SSE2 && TARGET_SSE_MATH)
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
   && (TARGET_USE_HIMODE_FIOP || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_MIX_SSE_I387
   && SSE_FLOAT_MODE_P (GET_MODE (operands[0]))
   && GET_MODE (operands[0]) == GET_MODE (operands[1])")
  (-1 "reload_completed || TARGET_80387")
  (-1 "TARGET_80387
   && !(SSE_FLOAT_MODE_P (DFmode) && (!TARGET_FISTTP || TARGET_SSE_MATH))")
  (-1 "TARGET_64BIT
   && optimize_insn_for_speed_p ()
   && (INTVAL (operands[2]) == 3
       || INTVAL (operands[2]) == 5
       || INTVAL (operands[2]) == 9)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (US_PLUS, V8HImode, operands)")
  (-1 "TARGET_SSE4_2")
  (-1 "optimize_function_for_size_p (cfun)")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "!TARGET_64BIT && TARGET_CMOVE")
  (-1 "TARGET_64BIT
   && ix86_binary_operator_ok (IOR, DImode, operands)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (EQ, V4SImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (AND, V8SImode, operands)")
  (-1 "TARGET_BSWAP")
  (-1 "!TARGET_64BIT && ix86_binary_operator_ok (PLUS, DImode, operands)")
  (-1 "(TARGET_SSE || TARGET_3DNOW_A)
   && ix86_binary_operator_ok (SMAX, V4HImode, operands)")
  (-1 "TARGET_80387
    && (!(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
        || TARGET_MIX_SSE_I387)
    && reload_completed")
  (-1 "reload_completed
    && QI_REG_P (operands[2])
    && GET_MODE (operands[2]) != QImode
    && ((ix86_match_ccmode (insn, CCZmode)
    	 && !(INTVAL (operands[3]) & ~(255 << 8)))
	|| (ix86_match_ccmode (insn, CCNOmode)
	    && !(INTVAL (operands[3]) & ~(127 << 8))))")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (MULT, V4SImode, operands)")
  (-1 "TARGET_80387 && TARGET_CMOVE")
  (-1 "TARGET_USE_FANCY_MATH_387
   && flag_unsafe_math_optimizations
   && standard_80387_constant_p (operands[3]) == 2")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (XOR, V2DFmode, operands)")
  (-1 "((SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
   || (TARGET_SSE2 && (SFmode == TFmode))) && ( reload_completed)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (LSHIFTRT, HImode, operands)")
  (-1 "ix86_unary_operator_ok (NEG, HImode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (AND, DImode, operands)")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V4SImode)
       || register_operand (operands[1], V4SImode))")
  (-1 "TARGET_MMX || (TARGET_SSE2 && V1DImode == V1DImode)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (EQ, V4HImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (IOR, V2DImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (PLUS, V4SFmode, operands)")
  (-1 "(!TARGET_64BIT) && ( reload_completed)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (PLUS, SImode, operands)
   /* Current assemblers are broken and do not allow @GOTOFF in
      ought but a memory context.  */
   && ! pic_symbolic_operand (operands[2], VOIDmode)")
  (-1 "(((TARGET_80387
     && (!((DImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((DImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH
	&& ((DImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (UNKNOWN, V4SFmode, operands)")
  (-1 "TARGET_SSE_MATH")
  (-1 "GET_MODE_SIZE (GET_MODE (operands[0])) <= UNITS_PER_WORD
   && (! TARGET_USE_MOV0 || optimize_insn_for_size_p ())
   && GENERAL_REG_P (operands[0])
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode) && !TARGET_SSE5")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (SS_MINUS, V8HImode, operands)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && TARGET_INTER_UNIT_CONVERSIONS
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_80387 && (TARGET_USE_HIMODE_FIOP || optimize_function_for_size_p (cfun))")
  (-1 "reload_completed
    && QI_REG_P (operands[0])
    && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
    && !(~INTVAL (operands[2]) & ~(255 << 8))
    && GET_MODE (operands[0]) != QImode")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && !TARGET_FISTTP
   && !(SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || DImode != DImode))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_3DNOW && ix86_binary_operator_ok (MULT, V4HImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (AND, HImode, operands)")
  (-1 "!TARGET_64BIT && reload_completed
   && !SSE_REG_P (operands[0]) && !MMX_REG_P (operands[0])")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCmode)
   && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
   && (TARGET_USE_SIMODE_FIOP || optimize_function_for_size_p (cfun))")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && GET_MODE (operands[1]) == GET_MODE (operands[2])
   && !ix86_use_fcomi_compare (GET_CODE (operands[0]))
   && SELECT_CC_MODE (GET_CODE (operands[0]),
		      operands[1], operands[2]) == CCFPmode
   && ix86_fp_jump_nontrivial_p (GET_CODE (operands[0]))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMIN, V4SFmode, operands)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && !TARGET_FISTTP
   && !(SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || SImode != DImode))
   && !(reload_completed || reload_in_progress)")
  (-1 "optimize_insn_for_speed_p () && ! TARGET_READ_MODIFY")
  (-1 "(TARGET_MMX && !(MEM_P (operands[0]) && MEM_P (operands[1]))) && ( reload_completed)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (PLUS, V2DFmode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode)
   && ix86_binary_operator_ok (PLUS, V4DFmode, operands)")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (SMIN, V4SImode, operands)")
  (-1 "(TARGET_USE_FANCY_MATH_387
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (XOR, V8HImode, operands)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATE, SImode, operands)")
  (-1 "TARGET_80387 || SSE_FLOAT_MODE_P (DFmode)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (XOR, V4HImode, operands)")
  (-1 "!TARGET_64BIT && TARGET_STACK_PROBE")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (PLUS, V4SImode, operands)")
  (-1 "TARGET_SLOW_IMUL_IMM32_MEM && optimize_insn_for_speed_p ()
   && !satisfies_constraint_K (operands[2])")
  (-1 "AVX_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && !COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, DImode, operands)")
  (-1 "(optimize_function_for_size_p (cfun)
    || !TARGET_PARTIAL_FLAG_REG_STALL
    || (operands[2] == const1_rtx
	&& (TARGET_SHIFT1
	    || TARGET_DOUBLE_WITH_ADD)))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, HImode, operands)")
  (-1 "!TARGET_64BIT
   && ((TARGET_80387 && TARGET_SSE)
       || (SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH))")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (IOR, SImode, operands)")
  (-1 "TARGET_64BIT
   && TARGET_AVX
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_AVX
   && (INTVAL (operands[3]) == (INTVAL (operands[7]) - 4)
       && INTVAL (operands[4]) == (INTVAL (operands[8]) - 4)
       && INTVAL (operands[5]) == (INTVAL (operands[9]) - 4)
       && INTVAL (operands[6]) == (INTVAL (operands[10]) - 4))")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (XOR, V2DImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (AND, QImode, operands)")
  (-1 "(TARGET_SSE || TARGET_3DNOW)
   && ix86_binary_operator_ok (PLUS, V8QImode, operands)")
  (-1 "TARGET_80387 && TARGET_CMOVE
   && !(MEM_P (operands[2]) && MEM_P (operands[3]))")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)")
  (-1 "reload_completed
   && MEM_P (operands[1])
   && (GET_MODE (operands[0]) == TFmode
       || GET_MODE (operands[0]) == XFmode
       || GET_MODE (operands[0]) == SFmode
       || GET_MODE (operands[0]) == DFmode)
   && (operands[2] = find_constant_src (insn))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMAX, V2DFmode, operands)")
  (-1 "TARGET_SSE2
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "(reload_completed) && (Pmode == SImode)")
  (-1 "reload_completed
    && GET_MODE (operands[2]) != QImode
    && (!REG_P (operands[2]) || ANY_QI_REG_P (operands[2]))
    && ((ix86_match_ccmode (insn, CCZmode)
	 && !(INTVAL (operands[3]) & ~255))
	|| (ix86_match_ccmode (insn, CCNOmode)
	    && !(INTVAL (operands[3]) & ~127)))")
  (-1 "TARGET_SSE")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V2DImode)
       || register_operand (operands[1], V2DImode))")
  (-1 "(TARGET_SSE || TARGET_3DNOW_A) && TARGET_64BIT")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V4DFmode)
       || register_operand (operands[1], V4DFmode))")
  (-1 "Pmode == DImode")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (PLUS, DImode, operands)
   /* Current assemblers are broken and do not allow @GOTOFF in
      ought but a memory context.  */
   && ! pic_symbolic_operand (operands[2], VOIDmode)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (ASHIFT, SImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (PLUS, V2DImode, operands)")
  (-1 "TARGET_64BIT && !SIBLING_CALL_P (insn)
   && ix86_cmodel != CM_LARGE && ix86_cmodel != CM_LARGE_PIC")
  (-1 "TARGET_MMX
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SMIN, V16QImode, operands)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (MINUS, V8HImode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (ROTATERT, DImode, operands)")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || HImode != DImode))
	&& TARGET_SSE_MATH)
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "ix86_unary_operator_ok (NOT, SImode, operands)")
  (-1 "(optimize_function_for_size_p (cfun)
     || !TARGET_PARTIAL_FLAG_REG_STALL
     || (operands[2] == const1_rtx
	 && (TARGET_SHIFT1
	     || (TARGET_DOUBLE_WITH_ADD && REG_P (operands[0])))))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, SImode, operands)")
  (-1 "TARGET_STACK_PROBE")
  (-1 "((TARGET_80387
     && (!((SImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((SImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
	&& ((SImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)")
  (-1 "(TARGET_SSE || TARGET_3DNOW_A)
   && ix86_binary_operator_ok (UMAX, V8QImode, operands)")
  (-1 "TARGET_SSE4_2
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (US_MINUS, V16QImode, operands)")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (UMIN, V8HImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode)
   && ix86_binary_operator_ok (IOR, V4DFmode, operands)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (XOR, V2SImode, operands)")
  (-1 "find_regno_note (insn, REG_UNUSED, REGNO (operands[1]))
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (ROTATE, SImode, operands)")
  (-1 "! TARGET_PARTIAL_REG_STALL && TARGET_CMOVE
   && (GET_MODE (operands[0]) == HImode
       || (GET_MODE (operands[0]) == QImode
	   && (TARGET_PROMOTE_QImode
	       || optimize_insn_for_size_p ())))")
  (-1 "(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
   || (TARGET_SSE2 && (SFmode == TFmode))")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (AND, V16QImode, operands)")
  (-1 "exact_log2 (INTVAL (operands[2])) >= 0
   && REGNO (operands[0]) == REGNO (operands[1])
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "TARGET_USE_FANCY_MATH_387
   && !(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_64BIT
   && (optimize_function_for_size_p (cfun)
       || !TARGET_PARTIAL_FLAG_REG_STALL
       || (operands[2] == const1_rtx
	   && (TARGET_SHIFT1
	       || TARGET_DOUBLE_WITH_ADD)))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, DImode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMAX, V8SFmode, operands)")
  (-1 "TARGET_SSE
   && reload_completed
   && (TARGET_INTER_UNIT_MOVES
       || MEM_P (operands [0])
       || !GENERAL_REGNO_P (true_regnum (operands [0])))")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && GET_MODE (operands[1]) == GET_MODE (operands[2])")
  (-1 "TARGET_64BIT || TARGET_SSE2")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "optimize_insn_for_speed_p ()
   && ! TARGET_USE_MOV0
   && TARGET_SPLIT_LONG_MOVES
   && get_attr_length (insn) >= ix86_cur_cost ()->large_insn
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "ix86_can_use_return_insn_p ()")
  (-1 "!(MEM_P (operands[0]) && MEM_P (operands[1]))
   && ix86_match_ccmode (insn, CCmode)")
  (-1 "optimize_insn_for_speed_p ()
   && ((TARGET_NOT_UNPAIRABLE
        && (!MEM_P (operands[0])
            || !memory_displacement_operand (operands[0], HImode)))
       || (TARGET_NOT_VECTORMODE && long_memory_operand (operands[0], HImode)))
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "(TARGET_MMX || (TARGET_SSE2 && V4HImode == V1DImode))
   && ix86_binary_operator_ok (MINUS, V4HImode, operands)")
  (-1 "((TARGET_80387
     && (!((SImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((SImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
	&& ((SImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (LSHIFTRT, HImode, operands)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)
   && ix86_unary_operator_ok (NOT, SImode, operands)")
  (-1 "TARGET_64BIT && reload_completed
   && true_regnum (operands[0]) != true_regnum (operands[1])")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || DImode != DImode))
	&& TARGET_SSE_MATH)
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "reload_completed && TARGET_ZERO_EXTEND_WITH_AND
   && optimize_function_for_speed_p (cfun)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (MULT, V8HImode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (ASHIFT, DImode, operands)")
  (-1 "!TARGET_64BIT
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SMAX, V16QImode, operands)")
  (-1 "TARGET_XADD")
  (-1 "!TARGET_PARTIAL_REG_STALL
   && ix86_binary_operator_ok (PLUS, HImode, operands)")
  (-1 "((GET_MODE (operands[0]) == QImode || GET_MODE (operands[0]) == HImode
    || (TARGET_64BIT && GET_MODE (operands[0]) == SImode))
   && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && GET_MODE (operands[0]) == GET_MODE (operands[1])
   && (GET_MODE (operands[0]) == GET_MODE (operands[3])
       || GET_MODE (operands[3]) == VOIDmode)) && ( reload_completed)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && !COMMUTATIVE_ARITH_P (operands[3])")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (XOR, V16QImode, operands)")
  (-1 "!TARGET_64BIT && !TARGET_INTEGER_DFMODE_MOVES")
  (-1 "TARGET_SSE2
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (AND, V4SImode, operands)")
  (-1 "TARGET_80387
    && (!(SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
        || TARGET_MIX_SSE_I387)
    && reload_completed")
  (-1 "TARGET_64BIT && !symbolic_operand (operands[1], DImode)
   && !x86_64_immediate_operand (operands[1], DImode)")
  (-1 "(SSE_FLOAT_MODE_P (SFmode) || SSE_VEC_FLOAT_MODE_P (SFmode))
   && !TARGET_SSE5")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (AND, V8HImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (UMAX, V16QImode, operands)")
  (-1 "TARGET_80387 || (SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (PLUS, V16QImode, operands)")
  (-1 "INTVAL (operands[2]) == 31
   && (TARGET_USE_CLTD || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "optimize_function_for_size_p (cfun) || TARGET_USE_CLTD")
  (-1 "exact_log2 (INTVAL (operands[1])) >= 0
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "(optimize_function_for_size_p (cfun)
    || !TARGET_PARTIAL_FLAG_REG_STALL
    || (operands[2] == const1_rtx
	&& (TARGET_SHIFT1
	    || TARGET_DOUBLE_WITH_ADD)))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, QImode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (AND, V2DFmode, operands)")
  (-1 "((SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
    || (TARGET_SSE2 && (SFmode == TFmode)))
   && reload_completed")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	&& (TARGET_64BIT || SImode != DImode))
	&& TARGET_SSE_MATH)")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && !COMMUTATIVE_ARITH_P (operands[3])")
  (-1 "(! TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCNOmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (AND, V2DImode, operands)")
  (-1 "(TARGET_SSE || TARGET_3DNOW_A)
   && ix86_binary_operator_ok (SMIN, V4HImode, operands)")
  (-1 "TARGET_PARTIAL_REG_STALL
   && ix86_binary_operator_ok (ASHIFT, HImode, operands)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (AND, DImode, operands)")
  (-1 "!TARGET_ZERO_EXTEND_WITH_AND || optimize_function_for_size_p (cfun)")
  (-1 "peep2_reg_dead_p (4, operands[7]) && peep2_reg_dead_p (4, operands[8])")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (MINUS, V2DImode, operands)")
  (-1 "TARGET_SSE5
   && !ix86_sse5_valid_op_p (operands, insn, 4, true, 1, true)
   && ix86_sse5_valid_op_p (operands, insn, 4, true, 2, true)
   && !reg_mentioned_p (operands[0], operands[1])
   && !reg_mentioned_p (operands[0], operands[2])
   && !reg_mentioned_p (operands[0], operands[3])")
  (-1 "TARGET_SSE5
   && (register_operand (operands[1], V8HImode)
       || register_operand (operands[2], V16QImode))")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SMIN, V8HImode, operands)")
  (-1 "TARGET_SSE2")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "ix86_binary_operator_ok (MINUS, HImode, operands)")
  (-1 "(! TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ASHIFTRT, QImode, operands)")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && !COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_80387 && TARGET_SSE2 && TARGET_INTER_UNIT_MOVES
   && !TARGET_64BIT && optimize_function_for_speed_p (cfun)")
  (-1 "(SSE_FLOAT_MODE_P (DFmode) || SSE_VEC_FLOAT_MODE_P (DFmode))
   && !TARGET_SSE5")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (MULT, V4HImode, operands)")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && reload_completed")
  (-1 "TARGET_SSE2 && !TARGET_64BIT")
  (-1 "TARGET_SSE5 && ix86_sse5_valid_op_p (operands, insn, 4, false, -1, true)")
  (-1 "TARGET_SSE5 && ix86_sse5_valid_op_p (operands, insn, 4, true, 1, true)")
  (-1 "TARGET_80387
   && COMMUTATIVE_ARITH_P (operands[3])")
  (-1 "!TARGET_64BIT && reload_completed")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (XOR, V8SImode, operands)")
  (-1 "!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun)")
  (-1 "TARGET_POPCNT && ix86_match_ccmode (insn, CCZmode)")
  (-1 "(TARGET_SSE || TARGET_3DNOW_A) && !TARGET_64BIT")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V8SFmode)
       || register_operand (operands[1], V8SFmode))")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "TARGET_80387 || TARGET_SSE_MATH")
  (-1 "TARGET_64BIT && ((optimize > 0 && flag_peephole2)
		    ? epilogue_completed : reload_completed)
   && !symbolic_operand (operands[1], DImode)
   && !x86_64_immediate_operand (operands[1], DImode)")
  (-1 "(TARGET_MMX || (TARGET_SSE2 && V1DImode == V1DImode))
   && ix86_binary_operator_ok (PLUS, V1DImode, operands)")
  (-1 "(ix86_binary_operator_ok (PLUS, DImode, operands)) && (TARGET_64BIT)")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (AND, V8HImode, operands)")
  (-1 "reload_completed
   && true_regnum (operands[0]) != true_regnum (operands[1])
   && GET_MODE_SIZE (GET_MODE (operands[0])) <= 4")
  (-1 "TARGET_SAHF")
  (-1 "TARGET_SSE
   && (register_operand (operands[0], V2DImode)
       || register_operand (operands[1], V2DImode))")
  (-1 "ix86_binary_operator_ok (ASHIFTRT, QImode, operands)")
  (-1 "TARGET_80387 && reload_completed")
  (-1 "TARGET_64BIT && ix86_unary_operator_ok (NOT, SImode, operands)")
  (-1 "(!TARGET_ZERO_EXTEND_WITH_AND || optimize_function_for_size_p (cfun))
   && reload_completed")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (IOR, V32QImode, operands)")
  (-1 "(!TARGET_64BIT && TARGET_SSE2 && TARGET_INTER_UNIT_MOVES) && ( reload_completed)")
  (-1 "!TARGET_64BIT && TARGET_SSE2 && TARGET_INTER_UNIT_MOVES")
  (-1 "TARGET_64BIT && TARGET_MMX
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "optimize_function_for_size_p (cfun) || (TARGET_FAST_PREFIX && !TARGET_PARTIAL_REG_STALL)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMAX, V4DFmode, operands)")
  (-1 "TARGET_SSSE3 && ix86_binary_operator_ok (MULT, V8HImode, operands)")
  (-1 "TARGET_SSE5 && ix86_sse5_valid_op_p (operands, insn, 4, true, 1, false)")
  (-1 "find_regno_note (insn, REG_UNUSED, REGNO (operands[0]))
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_64BIT && SIBLING_CALL_P (insn)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode)")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (IOR, V16QImode, operands)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (US_PLUS, V4HImode, operands)")
  (-1 "TARGET_CMPXCHG")
  (-1 "TARGET_SSE2 && reload_completed
   && !SSE_REG_P (operands[1])")
  (-1 "ix86_match_ccmode (insn, CCGCmode)
   && (INTVAL (operands[2]) & 0xffff) != 0x8000")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode)
   && ix86_binary_operator_ok (AND, V4DFmode, operands)")
  (-1 "TARGET_AVX && TARGET_SSE_MATH")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (EQ, V8HImode, operands)")
  (-1 "TARGET_80387
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "ix86_match_ccmode (insn, CCNOmode)")
  (-1 "(X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_SAHF && !TARGET_CMOVE
   && (TARGET_USE_HIMODE_FIOP || optimize_function_for_size_p (cfun))
   && (GET_MODE (operands [3]) == GET_MODE (operands[1]))) && ( reload_completed)")
  (-1 "TARGET_SSE || TARGET_64BIT")
  (-1 "TARGET_80387")
  (-1 "TARGET_HIMODE_MATH")
  (-1 "TARGET_64BIT && TARGET_POPCNT && ix86_match_ccmode (insn, CCZmode)")
  (-1 "TARGET_USE_FANCY_MATH_387
   || (SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)")
  (-1 "(TARGET_USE_BT || optimize_function_for_size_p (cfun))
   && (INTVAL (operands[3]) & 0x1f) == 0x1f")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (XOR, V8HImode, operands)")
  (-1 "REGNO (operands[0]) != REGNO (operands[1])
   && GENERAL_REGNO_P (REGNO (operands[0]))
   && GENERAL_REGNO_P (REGNO (operands[1]))")
  (-1 "TARGET_64BIT
   && reload_completed")
  (-1 "TARGET_AES && TARGET_AVX")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (XOR, V16HImode, operands)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (US_PLUS, V8QImode, operands)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[0]))
   && TARGET_CMOVE
   && !(SSE_FLOAT_MODE_P (GET_MODE (operands[0])) && TARGET_SSE_MATH)
   && GET_MODE (operands[0]) == GET_MODE (operands[1])")
  (-1 "TARGET_SSE3 && TARGET_64BIT")
  (-1 "TARGET_USE_FANCY_MATH_387")
  (-1 "TARGET_USE_XCHGB || optimize_function_for_size_p (cfun)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (MULT, V4SImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_unary_operator_ok (NEG, HImode, operands)")
  (-1 "TARGET_64BIT && !SIBLING_CALL_P (insn)")
  (-1 "(((TARGET_80387
     && (!((DImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((DImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
	&& ((DImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "TARGET_80387 || (SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)")
  (-1 "ix86_binary_operator_ok (ROTATE, HImode, operands)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && ((DImode != DImode) || TARGET_64BIT)
   && !flag_trapping_math && !flag_rounding_math")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && ((DImode != DImode) || TARGET_64BIT)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (XOR, V4SImode, operands)")
  (-1 "(reload_completed
    && dead_or_set_p (insn, operands[1])
    && !reg_mentioned_p (operands[1], operands[0]))")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && !TARGET_FISTTP
   && !(TARGET_64BIT && SSE_FLOAT_MODE_P (GET_MODE (operands[1])))")
  (-1 "reload_completed && !SSE_REG_P (operands[0])
   && !SSE_REG_P (operands[1])")
  (-1 "TARGET_64BIT
   && ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (IOR, DImode, operands)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "!TARGET_64BIT && TARGET_SUN_TLS")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode)
   && ix86_binary_operator_ok (MINUS, V8SFmode, operands)")
  (-1 "TARGET_SSE4_1 && TARGET_64BIT")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_unary_operator_ok (NOT, SImode, operands)")
  (-1 "!TARGET_PARTIAL_REG_STALL
   && ix86_binary_operator_ok (ASHIFT, QImode, operands)")
  (-1 "TARGET_64BIT
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "SSE_FLOAT_MODE_P (DFmode)
   && (!TARGET_FISTTP || TARGET_SSE_MATH)")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATE, DImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (XOR, SImode, operands)")
  (-1 "TARGET_USE_FANCY_MATH_387
   && TARGET_C99_FUNCTIONS
   && !(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && !flag_trapping_math")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode)")
  (-1 "ix86_match_ccmode (insn, CCmode)")
  (-1 "(TARGET_64BIT) && ( reload_completed)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || SImode != DImode))
	&& TARGET_SSE_MATH)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4SFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMAX, V4SFmode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (MINUS, TImode, operands)")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
   && !COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "!TARGET_SSE2 && TARGET_SSE
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_3DNOW")
  (-1 "(TARGET_MMX || (TARGET_SSE2 && V4HImode == V1DImode))
   && ix86_binary_operator_ok (PLUS, V4HImode, operands)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (XOR, V4DImode, operands)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && COMMUTATIVE_ARITH_P (operands[3])
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (MINUS, V4SFmode, operands)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_SSE && reload_completed")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && (true_regnum (operands[2]) != AX_REG
       || satisfies_constraint_K (operands[3]))
   && peep2_reg_dead_p (1, operands[2])")
  (-1 "!TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || DImode != DImode))
	&& TARGET_SSE_MATH)
   && !(reload_completed || reload_in_progress)")
  (-1 "!TARGET_CMOVE")
  (-1 "TARGET_PARTIAL_REG_STALL
   && ix86_binary_operator_ok (PLUS, HImode, operands)")
  (-1 "(reload_completed) && (Pmode == DImode)")
  (-1 "AVX_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH")
  (-1 "REGNO (operands[0]) != REGNO (operands[1])
   && ((MMX_REG_P (operands[0]) && MMX_REG_P (operands[1])) 
       || (SSE_REG_P (operands[0]) && SSE_REG_P (operands[1])))")
  (-1 "TARGET_SSE && ix86_binary_operator_ok (UNKNOWN, V4SFmode, operands)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && TARGET_INTER_UNIT_CONVERSIONS
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode)
   && ix86_binary_operator_ok (MULT, V8SFmode, operands)")
  (-1 "ix86_unary_operator_ok (NEG, SImode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (AND, SImode, operands)")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (PLUS, V4SImode, operands)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_SSE5 && TARGET_FUSED_MADD
   && ix86_sse5_valid_op_p (operands, insn, 4, true, 1, false)")
  (-1 "SSE_FLOAT_MODE_P (DFmode)")
  (-1 "ix86_unary_operator_ok (NOT, QImode, operands)")
  (-1 "reload_completed && FP_REGNO_P (REGNO (operands[0]))
   && (standard_80387_constant_p (operands[1]) == 8
       || standard_80387_constant_p (operands[1]) == 9)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "ix86_binary_operator_ok (XOR, SImode, operands)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_80387 || TARGET_SSE")
  (-1 "TARGET_SSE || TARGET_3DNOW")
  (-1 "optimize_insn_for_speed_p () && !TARGET_PUSH_MEMORY
   && !RTX_FRAME_RELATED_P (peep2_next_insn (0))")
  (-1 "TARGET_3DNOW && TARGET_64BIT")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (UMIN, V16QImode, operands)")
  (-1 "TARGET_64BIT && (TARGET_USE_CLTD || optimize_function_for_size_p (cfun))
   && INTVAL (operands[2]) == 31
   && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "(SSE_FLOAT_MODE_P (TFmode) && TARGET_SSE_MATH)
   || (TARGET_SSE2 && (TFmode == TFmode))")
  (-1 "!TARGET_64BIT && TARGET_GNU_TLS")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (MULT, V2SImode, operands)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (EQ, V2DImode, operands)")
  (-1 "AVX256_VEC_FLOAT_MODE_P (V4DFmode)")
  (-1 "TARGET_64BIT
   && (optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_FLAG_REG_STALL)
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (LSHIFTRT, HImode, operands)")
  (-1 "TARGET_64BIT && !(MEM_P (operands[0]) && MEM_P (operands[1]))
   && (reload_in_progress || reload_completed
       || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
       || (!(TARGET_SSE2 && TARGET_SSE_MATH)
           && optimize_function_for_size_p (cfun)
	   && standard_80387_constant_p (operands[1]))
       || GET_CODE (operands[1]) != CONST_DOUBLE
       || memory_operand (operands[0], DFmode))")
  (-1 "TARGET_64BIT && TARGET_AVX")
  (-1 "! TARGET_PARTIAL_REG_STALL && reload_completed
   && ! TARGET_FAST_PREFIX
   && optimize_insn_for_speed_p ()
   /* Ensure that the operand will remain sign-extended immediate.  */
   && ix86_match_ccmode (insn, INTVAL (operands[3]) >= 0 ? CCNOmode : CCZmode)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SMAX, V4SImode, operands)")
  (-1 "(TARGET_SSE2
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (LSHIFTRT, QImode, operands)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && (TARGET_USE_SIMODE_FIOP || optimize_function_for_size_p (cfun))
   && (GET_MODE (operands [3]) == GET_MODE (operands[1]))")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V8SImode)
       || register_operand (operands[1], V8SImode))")
  (-1 "ix86_binary_operator_ok (MINUS, QImode, operands)")
  (-1 "((GET_MODE (operands[0]) == QImode || GET_MODE (operands[0]) == HImode
    || (TARGET_64BIT && GET_MODE (operands[0]) == SImode))
   && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && GET_MODE (operands[0]) == GET_MODE (operands[1])
   && GET_MODE (operands[0]) == GET_MODE (operands[3])) && ( reload_completed)")
  (-1 "TARGET_64BIT
   && ix86_binary_operator_ok (XOR, DImode, operands)")
  (-1 "TARGET_PCLMUL")
  (-1 "ix86_binary_operator_ok (ASHIFTRT, HImode, operands)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[3]))
   && (TARGET_USE_SIMODE_FIOP || optimize_function_for_size_p (cfun))
   && GET_MODE (operands[1]) == GET_MODE (operands[3])
   && !ix86_use_fcomi_compare (swap_condition (GET_CODE (operands[0])))
   && ix86_fp_compare_mode (swap_condition (GET_CODE (operands[0]))) == CCFPmode
   && ix86_fp_jump_nontrivial_p (swap_condition (GET_CODE (operands[0])))")
  (-1 "(TARGET_POPCNT) && (TARGET_64BIT)")
  (-1 "ix86_binary_operator_ok (AND, QImode, operands)")
  (-1 "TARGET_80387 && !(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMIN, V4SFmode, operands)")
  (-1 "(optimize_function_for_size_p (cfun) || !TARGET_PARTIAL_FLAG_REG_STALL)
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFTRT, HImode, operands)")
  (-1 "AVX128_VEC_FLOAT_MODE_P (V4SFmode)")
  (-1 "!TARGET_64BIT && TARGET_SSE2 && TARGET_SSE_MATH")
  (-1 "TARGET_MMX")
  (-1 "(TARGET_SSE && !TARGET_SSE2)
   && ix86_binary_operator_ok (AND, V4SImode, operands)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && (TARGET_USE_HIMODE_FIOP || optimize_function_for_size_p (cfun))
   && (GET_MODE (operands [3]) == GET_MODE (operands[1]))")
  (-1 "TARGET_PREFETCH_SSE && TARGET_64BIT")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_PREFETCH_SSE && !TARGET_64BIT")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "reload_completed
   && MEM_P (operands[1])
   && (operands[2] = find_constant_src (insn))")
  (-1 "TARGET_SSE4_2 && TARGET_64BIT")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (MULT, V4SFmode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (IOR, V4SFmode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (XOR, SImode, operands)")
  (-1 "!TARGET_PARTIAL_REG_STALL
   && ix86_binary_operator_ok (PLUS, QImode, operands)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_SAHF && !TARGET_CMOVE
   && GET_MODE (operands[1]) == GET_MODE (operands[2])")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && (TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_64BIT
   && ix86_match_ccmode (insn, CCGOCmode)
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))
   /* Current assemblers are broken and do not allow @GOTOFF in
      ought but a memory context.  */
   && ! pic_symbolic_operand (operands[2], VOIDmode)")
  (-1 "optimize_function_for_speed_p (cfun) && !TARGET_USE_CLTD")
  (-1 "reload_completed")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATE, QImode, operands)")
  (-1 "optimize_insn_for_size_p () || !TARGET_SUB_ESP_8")
  (-1 "TARGET_64BIT && TARGET_SSE")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (IOR, V4DImode, operands)")
  (-1 "!TARGET_64BIT && SIBLING_CALL_P (insn)")
  (-1 "(TARGET_SSE4_2
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (XOR, V16QImode, operands)")
  (-1 "TARGET_SSE && !TARGET_64BIT
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "reload_completed
   && (!TARGET_ZERO_EXTEND_WITH_AND
       || optimize_function_for_size_p (cfun))
   && (!REG_P (operands[1]) || ANY_QI_REG_P (operands[1]))")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (LSHIFTRT, HImode, operands)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_MIX_SSE_I387")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode)
   && ix86_binary_operator_ok (XOR, V8SFmode, operands)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (SS_MINUS, V4HImode, operands)")
  (-1 "!TARGET_64BIT")
  (-1 "!TARGET_64BIT && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && !TARGET_SSE5")
  (-1 "TARGET_USE_FANCY_MATH_387
   && (!(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && flag_unsafe_math_optimizations")
  (-1 "ix86_binary_operator_ok (IOR, SImode, operands)")
  (-1 "!TARGET_64BIT && reload_completed
   && (! MMX_REG_P (operands[1]) && !SSE_REG_P (operands[1]))")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_SAHF && !TARGET_CMOVE
   && (TARGET_USE_SIMODE_FIOP || optimize_function_for_size_p (cfun))
   && (GET_MODE (operands [3]) == GET_MODE (operands[1]))")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (EQ, V2SImode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V2DFmode) && flag_finite_math_only
   && ix86_binary_operator_ok (SMAX, V2DFmode, operands)")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (AND, V2SImode, operands)")
  (-1 "SSE_VEC_FLOAT_MODE_P (V4SFmode)
   && ix86_binary_operator_ok (XOR, V4SFmode, operands)")
  (-1 "(GET_MODE (operands[0]) == QImode || GET_MODE (operands[0]) == HImode
    || (TARGET_64BIT && GET_MODE (operands[0]) == SImode))
   && (!TARGET_PARTIAL_REG_STALL || optimize_function_for_size_p (cfun))
   && GET_MODE (operands[0]) == GET_MODE (operands[1])
   && GET_MODE (operands[0]) == GET_MODE (operands[3])")
  (-1 "AVX128_VEC_FLOAT_MODE_P (V2DFmode)")
  (-1 "(TARGET_64BIT || TARGET_KEEPS_VECTOR_ALIGNED_STACK)
   && TARGET_SSE2 && TARGET_SSE_MATH")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (PLUS, V8HImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (SMAX, V8HImode, operands)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (XOR, HImode, operands)")
  (-1 "AVX_FLOAT_MODE_P (SFmode)")
  (-1 "TARGET_CMOVE")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATERT, DImode, operands)")
  (-1 "((TARGET_80387
     && (!((DImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((DImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
	&& ((DImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (US_PLUS, V8HImode, operands)")
  (-1 "TARGET_AVX && TARGET_64BIT")
  (-1 "TARGET_USE_FANCY_MATH_387
   && TARGET_C99_FUNCTIONS")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V16HImode)
       || register_operand (operands[1], V16HImode))")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (US_MINUS, V8HImode, operands)")
  (-1 "TARGET_SSE && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "AVX_VEC_FLOAT_MODE_P (V2DFmode)
   && ix86_binary_operator_ok (MINUS, V2DFmode, operands)")
  (-1 "AVX_VEC_FLOAT_MODE_P (V4DFmode)")
  (-1 "TARGET_64BIT && (optimize_function_for_size_p (cfun) || TARGET_USE_CLTD)")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (MINUS, HImode, operands)")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (SMIN, V16QImode, operands)")
  (-1 "TARGET_SSE4_1 && ix86_binary_operator_ok (SMAX, V16QImode, operands)")
  (-1 "TARGET_64BIT && ix86_match_ccmode (insn, CCNOmode)
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "optimize_insn_for_speed_p ()
   && ((TARGET_NOT_UNPAIRABLE
        && (!MEM_P (operands[0])
            || !memory_displacement_operand (operands[0], QImode)))
       || (TARGET_NOT_VECTORMODE && long_memory_operand (operands[0], QImode)))
   && peep2_regno_dead_p (0, FLAGS_REG)")
  (-1 "TARGET_SSE5 && TARGET_FUSED_MADD
   && ix86_sse5_valid_op_p (operands, insn, 4, true, 2, true)")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_MIX_SSE_I387")
  (-1 "!TARGET_64BIT
   && TARGET_AVX
   && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_64BIT
   && (TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ASHIFTRT, SImode, operands)")
  (-1 "reload_completed
   && true_regnum (operands[0]) != true_regnum (operands[1])")
  (-1 "TARGET_AVX && !(MEM_P (operands[1]) && MEM_P (operands[2]))")
  (-1 "ix86_match_ccmode (insn, CCZmode)
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))
   /* Current assemblers are broken and do not allow @GOTOFF in
      ought but a memory context.  */
   && ! pic_symbolic_operand (operands[2], VOIDmode)")
  (-1 "SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (UMIN, V16QImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (IOR, V2DImode, operands)")
  (-1 "TARGET_3DNOW && ix86_binary_operator_ok (EQ, V2SFmode, operands)")
  (-1 "(TARGET_SSE || TARGET_3DNOW_A)
   && ix86_binary_operator_ok (MULT, V4HImode, operands)")
  (-1 "TARGET_64BIT && TARGET_SSE4_1")
  (-1 "TARGET_64BIT
   && (INTVAL (operands[2]) == 3
       || INTVAL (operands[2]) == 5
       || INTVAL (operands[2]) == 9)")
  (-1 "TARGET_MMX && !(MEM_P (operands[0]) && MEM_P (operands[1]))")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (AND, V8QImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (XOR, V4SImode, operands)")
  (-1 "TARGET_SSE2 && ix86_binary_operator_ok (IOR, V8HImode, operands)")
  (-1 "TARGET_80387
   || ((DImode != DImode || TARGET_64BIT)
       && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_SSE3")
  (-1 "TARGET_SSE5 && TARGET_FUSED_MADD
   && ix86_sse5_valid_op_p (operands, insn, 4, true, 1, true)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (US_MINUS, V16QImode, operands)")
  (-1 "TARGET_64BIT && ((optimize > 0 && flag_peephole2)
		    ? epilogue_completed : reload_completed)")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "TARGET_80387
   || ((SImode != DImode || TARGET_64BIT)
       && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH)")
  (-1 "TARGET_AVX
   && (register_operand (operands[0], V4SFmode)
       || register_operand (operands[1], V4SFmode))")
  (-1 "TARGET_MMX && ix86_binary_operator_ok (IOR, V8QImode, operands)")
  (-1 "TARGET_AVX")
  (-1 "TARGET_SSE2 && !TARGET_SSE5")
  (-1 "TARGET_64BIT || TARGET_INTEGER_DFMODE_MOVES")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATERT, HImode, operands)")
  (-1 "TARGET_AVX && ix86_binary_operator_ok (SMAX, V8HImode, operands)")
  (-1 "TARGET_SSSE3")
  (-1 "AVX_VEC_FLOAT_MODE_P (V8SFmode)
   && ix86_binary_operator_ok (PLUS, V8SFmode, operands)")
  (-1 "optimize_insn_for_size_p ()")
  (-1 "TARGET_80387 || (TARGET_64BIT && SSE_FLOAT_MODE_P (SFmode))")
  (-1 "(DImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))")
  (-1 "TARGET_SSE2 && TARGET_MIX_SSE_I387
   && TARGET_USE_VECTOR_CONVERTS && optimize_function_for_speed_p (cfun)")
  (-1 "((TARGET_80387
     && (!((SImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((SImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH
	&& ((SImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)")
  (-1 "ix86_match_ccmode (insn, CCNOmode)
   && ix86_binary_operator_ok (IOR, QImode, operands)")
  (-1 "TARGET_SSE5 && TARGET_FUSED_MADD
   && ix86_sse5_valid_op_p (operands, insn, 4, true, 2, false)")
  (-1 "!TARGET_64BIT
   && TARGET_80387 && TARGET_SSE")
  (-1 "(SImode != DImode || TARGET_64BIT)
   && SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && !(TARGET_INTER_UNIT_CONVERSIONS || optimize_function_for_size_p (cfun))
   && reload_completed
   && (SSE_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && SSE_REG_P (operands[0])))")
  (-1 "reload_completed && SSE_REG_P (operands[0])")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (MINUS, DImode, operands)")
  (-1 "TARGET_64BIT && ix86_binary_operator_ok (IOR, SImode, operands)")
  (-1 "(TARGET_MMX || (TARGET_SSE2 && V1DImode == V1DImode))
   && ix86_binary_operator_ok (MINUS, V1DImode, operands)")
  (-1 "TARGET_64BIT && TARGET_ABM")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	 && (TARGET_64BIT || HImode != DImode))
	&& TARGET_SSE_MATH)
   && !(reload_completed || reload_in_progress)")
  (-1 "(TARGET_SHIFT1 || optimize_function_for_size_p (cfun))
   && ix86_binary_operator_ok (ROTATE, HImode, operands)")
  (-1 "((TARGET_80387
     && (!((DImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((DImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH
	&& ((DImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[3]))
   && (TARGET_USE_HIMODE_FIOP || optimize_function_for_size_p (cfun))
   && GET_MODE (operands[1]) == GET_MODE (operands[3])
   && !ix86_use_fcomi_compare (swap_condition (GET_CODE (operands[0])))
   && ix86_fp_compare_mode (swap_condition (GET_CODE (operands[0]))) == CCFPmode
   && ix86_fp_jump_nontrivial_p (swap_condition (GET_CODE (operands[0])))")
  (-1 "TARGET_80387
   && (!(SSE_FLOAT_MODE_P (DFmode) && TARGET_SSE_MATH)
       || TARGET_MIX_SSE_I387)
   && !(reload_completed || reload_in_progress)")
  (-1 "TARGET_64BIT && (TARGET_USE_BT || reload_completed)")
  (-1 "! TARGET_POPCNT")
  (-1 "ix86_match_ccmode (insn, CCGOCmode)
   && !(MEM_P (operands[1]) && MEM_P (operands[2]))
   /* Current assemblers are broken and do not allow @GOTOFF in
      ought but a memory context.  */
   && ! pic_symbolic_operand (operands[2], VOIDmode)")
  (-1 "TARGET_AVX
   && ix86_binary_operator_ok (IOR, V4SImode, operands)")
  (-1 "(optimize_function_for_size_p (cfun)
    || !TARGET_PARTIAL_FLAG_REG_STALL
    || (operands[2] == const1_rtx
	&& (TARGET_SHIFT1
	    || (TARGET_DOUBLE_WITH_ADD && REG_P (operands[0])))))
   && ix86_match_ccmode (insn, CCGOCmode)
   && ix86_binary_operator_ok (ASHIFT, QImode, operands)")
  (-1 "(((TARGET_80387
     && (!((SImode != DImode || TARGET_64BIT)
	   && SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH)
	 || TARGET_MIX_SSE_I387))
    || ((SImode != DImode || TARGET_64BIT)
	&& SSE_FLOAT_MODE_P (XFmode) && TARGET_SSE_MATH
	&& ((SImode == SImode
	     && TARGET_SSE2 && TARGET_USE_VECTOR_CONVERTS
	     && optimize_function_for_speed_p (cfun)
	     && flag_trapping_math)
	    || !(TARGET_INTER_UNIT_CONVERSIONS
	         || optimize_function_for_size_p (cfun)))))
   && !(reload_completed || reload_in_progress)) && ( 1)")
  (-1 "X87_FLOAT_MODE_P (GET_MODE (operands[1]))
   && TARGET_FISTTP
   && !((SSE_FLOAT_MODE_P (GET_MODE (operands[1]))
	&& (TARGET_64BIT || DImode != DImode))
	&& TARGET_SSE_MATH)")
  (-1 "SSE_FLOAT_MODE_P (SFmode) && TARGET_SSE_MATH
   && !flag_trapping_math && !flag_rounding_math")
  (-1 "TARGET_64BIT && TARGET_STACK_PROBE")
  (-1 "TARGET_SSE_MATH
   && SSE_FLOAT_MODE_P (GET_MODE (operands[0]))
   && GET_MODE (operands[0]) == GET_MODE (operands[1])")
  (-1 "(!TARGET_CMOVE) && ( reload_completed)")
])
