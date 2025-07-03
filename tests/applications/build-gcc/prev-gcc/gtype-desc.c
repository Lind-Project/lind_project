/* Type information for GCC.
   Copyright (C) 2004, 2007 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* This file is machine generated.  Do not edit.  */
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "varray.h"
#include "hashtab.h"
#include "splay-tree.h"
#include "obstack.h"
#include "bitmap.h"
#include "input.h"
#include "tree.h"
#include "rtl.h"
#include "function.h"
#include "insn-config.h"
#include "expr.h"
#include "hard-reg-set.h"
#include "basic-block.h"
#include "cselib.h"
#include "insn-addr.h"
#include "optabs.h"
#include "libfuncs.h"
#include "debug.h"
#include "ggc.h"
#include "cgraph.h"
#include "tree-flow.h"
#include "reload.h"
#include "cpp-id-data.h"
#include "tree-chrec.h"
#include "cfglayout.h"
#include "except.h"
#include "output.h"
#include "gimple.h"
#include "cfgloop.h"

/* See definition in function.h.  */
#undef cfun

void
gt_ggc_mx_ssa_operand_memory_d (void *x_p)
{
  struct ssa_operand_memory_d * x = (struct ssa_operand_memory_d *)x_p;
  struct ssa_operand_memory_d * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_20ssa_operand_memory_d ((*x).next);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_VEC_gimple_gc (void *x_p)
{
  struct VEC_gimple_gc * const x = (struct VEC_gimple_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_18gimple_statement_d ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_throw_stmt_node (void *x_p)
{
  struct throw_stmt_node * const x = (struct throw_stmt_node *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18gimple_statement_d ((*x).stmt);
    }
}

void
gt_ggc_mx_cgraph_asm_node (void *x_p)
{
  struct cgraph_asm_node * const x = (struct cgraph_asm_node *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15cgraph_asm_node ((*x).next);
      gt_ggc_m_9tree_node ((*x).asm_str);
    }
}

void
gt_ggc_mx_varpool_node (void *x_p)
{
  struct varpool_node * x = (struct varpool_node *)x_p;
  struct varpool_node * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_9tree_node ((*x).decl);
      gt_ggc_m_12varpool_node ((*x).next);
      gt_ggc_m_12varpool_node ((*x).next_needed);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_cgraph_edge (void *x_p)
{
  struct cgraph_edge * x = (struct cgraph_edge *)x_p;
  struct cgraph_edge * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next_caller);
  if (x != xlimit)
    for (;;)
      {
        struct cgraph_edge * const xprev = ((*x).prev_caller);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_11cgraph_node ((*x).caller);
      gt_ggc_m_11cgraph_node ((*x).callee);
      gt_ggc_m_11cgraph_edge ((*x).prev_caller);
      gt_ggc_m_11cgraph_edge ((*x).next_caller);
      gt_ggc_m_11cgraph_edge ((*x).prev_callee);
      gt_ggc_m_11cgraph_edge ((*x).next_callee);
      gt_ggc_m_18gimple_statement_d ((*x).call_stmt);
      gt_ggc_m_S ((*x).inline_failed);
      x = ((*x).next_caller);
    }
}

void
gt_ggc_mx_cgraph_node (void *x_p)
{
  struct cgraph_node * x = (struct cgraph_node *)x_p;
  struct cgraph_node * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct cgraph_node * const xprev = ((*x).previous);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_9tree_node ((*x).decl);
      gt_ggc_m_11cgraph_edge ((*x).callees);
      gt_ggc_m_11cgraph_edge ((*x).callers);
      gt_ggc_m_11cgraph_node ((*x).next);
      gt_ggc_m_11cgraph_node ((*x).previous);
      gt_ggc_m_11cgraph_node ((*x).origin);
      gt_ggc_m_11cgraph_node ((*x).nested);
      gt_ggc_m_11cgraph_node ((*x).next_nested);
      gt_ggc_m_11cgraph_node ((*x).next_needed);
      gt_ggc_m_11cgraph_node ((*x).next_clone);
      gt_ggc_m_11cgraph_node ((*x).prev_clone);
      gt_ggc_m_11cgraph_node ((*x).master_clone);
      gt_ggc_m_P11cgraph_edge4htab ((*x).call_site_hash);
      gt_ggc_m_11cgraph_node ((*x).global.inlined_to);
      gt_ggc_m_9tree_node ((*x).inline_decl);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_VEC_basic_block_gc (void *x_p)
{
  struct VEC_basic_block_gc * const x = (struct VEC_basic_block_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_15basic_block_def ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_gimple_bb_info (void *x_p)
{
  struct gimple_bb_info * const x = (struct gimple_bb_info *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_12gimple_seq_d ((*x).seq);
      gt_ggc_m_12gimple_seq_d ((*x).phi_nodes);
    }
}

void
gt_ggc_mx_rtl_bb_info (void *x_p)
{
  struct rtl_bb_info * const x = (struct rtl_bb_info *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).head_);
      gt_ggc_m_7rtx_def ((*x).end_);
      gt_ggc_m_7rtx_def ((*x).header);
      gt_ggc_m_7rtx_def ((*x).footer);
    }
}

void
gt_ggc_mx_VEC_edge_gc (void *x_p)
{
  struct VEC_edge_gc * const x = (struct VEC_edge_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_8edge_def ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_cselib_val_struct (void *x_p)
{
  struct cselib_val_struct * const x = (struct cselib_val_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).val_rtx);
      gt_ggc_m_12elt_loc_list ((*x).locs);
      gt_ggc_m_8elt_list ((*x).addr_list);
      gt_ggc_m_17cselib_val_struct ((*x).next_containing_mem);
    }
}

void
gt_ggc_mx_elt_loc_list (void *x_p)
{
  struct elt_loc_list * const x = (struct elt_loc_list *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_12elt_loc_list ((*x).next);
      gt_ggc_m_7rtx_def ((*x).loc);
      gt_ggc_m_7rtx_def ((*x).setting_insn);
    }
}

void
gt_ggc_mx_VEC_loop_p_gc (void *x_p)
{
  struct VEC_loop_p_gc * const x = (struct VEC_loop_p_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_4loop ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_loop (void *x_p)
{
  struct loop * x = (struct loop *)x_p;
  struct loop * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_15basic_block_def ((*x).header);
      gt_ggc_m_15basic_block_def ((*x).latch);
      gt_ggc_m_13VEC_loop_p_gc ((*x).superloops);
      gt_ggc_m_4loop ((*x).inner);
      gt_ggc_m_4loop ((*x).next);
      gt_ggc_m_9tree_node ((*x).nb_iterations);
      gt_ggc_m_13nb_iter_bound ((*x).bounds);
      gt_ggc_m_9loop_exit ((*x).exits);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_loop_exit (void *x_p)
{
  struct loop_exit * const x = (struct loop_exit *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_8edge_def ((*x).e);
      gt_ggc_m_9loop_exit ((*x).prev);
      gt_ggc_m_9loop_exit ((*x).next);
      gt_ggc_m_9loop_exit ((*x).next_e);
    }
}

void
gt_ggc_mx_nb_iter_bound (void *x_p)
{
  struct nb_iter_bound * x = (struct nb_iter_bound *)x_p;
  struct nb_iter_bound * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_18gimple_statement_d ((*x).stmt);
      gt_ggc_m_13nb_iter_bound ((*x).next);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_types_used_by_vars_entry (void *x_p)
{
  struct types_used_by_vars_entry * const x = (struct types_used_by_vars_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).type);
      gt_ggc_m_9tree_node ((*x).var_decl);
    }
}

void
gt_ggc_mx_loops (void *x_p)
{
  struct loops * const x = (struct loops *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_13VEC_loop_p_gc ((*x).larray);
      gt_ggc_m_P9loop_exit4htab ((*x).exits);
      gt_ggc_m_4loop ((*x).tree_root);
    }
}

void
gt_ggc_mx_control_flow_graph (void *x_p)
{
  struct control_flow_graph * const x = (struct control_flow_graph *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15basic_block_def ((*x).x_entry_block_ptr);
      gt_ggc_m_15basic_block_def ((*x).x_exit_block_ptr);
      gt_ggc_m_18VEC_basic_block_gc ((*x).x_basic_block_info);
      gt_ggc_m_18VEC_basic_block_gc ((*x).x_label_to_block_map);
    }
}

void
gt_ggc_mx_VEC_temp_slot_p_gc (void *x_p)
{
  struct VEC_temp_slot_p_gc * const x = (struct VEC_temp_slot_p_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9temp_slot ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_gimple_df (void *x_p)
{
  struct gimple_df * const x = (struct gimple_df *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_P9tree_node4htab ((*x).referenced_vars);
      gt_ggc_m_13VEC_gimple_gc ((*x).modified_noreturn_calls);
      gt_ggc_m_11VEC_tree_gc ((*x).ssa_names);
      gt_ggc_m_9tree_node ((*x).global_var);
      gt_ggc_m_9tree_node ((*x).nonlocal_all);
      gt_ggc_m_15bitmap_head_def ((*x).call_clobbered_vars);
      gt_ggc_m_15bitmap_head_def ((*x).call_used_vars);
      gt_ggc_m_15bitmap_head_def ((*x).addressable_vars);
      gt_ggc_m_9tree_node ((*x).free_ssanames);
      gt_ggc_m_P9tree_node4htab ((*x).default_defs);
      gt_ggc_m_20ssa_operand_memory_d ((*x).ssa_operands.operand_memory);
    }
}

void
gt_ggc_mx_VEC_call_site_record_gc (void *x_p)
{
  struct VEC_call_site_record_gc * const x = (struct VEC_call_site_record_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_16call_site_record ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_sequence_stack (void *x_p)
{
  struct sequence_stack * const x = (struct sequence_stack *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).first);
      gt_ggc_m_7rtx_def ((*x).last);
      gt_ggc_m_14sequence_stack ((*x).next);
    }
}

void
gt_ggc_mx_edge_def (void *x_p)
{
  struct edge_def * const x = (struct edge_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15basic_block_def ((*x).src);
      gt_ggc_m_15basic_block_def ((*x).dest);
      switch (current_ir_type () == IR_GIMPLE)
        {
        case true:
          gt_ggc_m_12gimple_seq_d ((*x).insns.g);
          break;
        case false:
          gt_ggc_m_7rtx_def ((*x).insns.r);
          break;
        default:
          break;
        }
      gt_ggc_m_9tree_node ((*x).goto_block);
    }
}

void
gt_ggc_mx_elt_list (void *x_p)
{
  struct elt_list * const x = (struct elt_list *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_8elt_list ((*x).next);
      gt_ggc_m_17cselib_val_struct ((*x).elt);
    }
}

void
gt_ggc_mx_tree_priority_map (void *x_p)
{
  struct tree_priority_map * const x = (struct tree_priority_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.from);
    }
}

void
gt_ggc_mx_tree_int_map (void *x_p)
{
  struct tree_int_map * const x = (struct tree_int_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.from);
    }
}

void
gt_ggc_mx_tree_map (void *x_p)
{
  struct tree_map * const x = (struct tree_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.from);
      gt_ggc_m_9tree_node ((*x).to);
    }
}

void
gt_ggc_mx_tree_statement_list_node (void *x_p)
{
  struct tree_statement_list_node * x = (struct tree_statement_list_node *)x_p;
  struct tree_statement_list_node * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct tree_statement_list_node * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_24tree_statement_list_node ((*x).prev);
      gt_ggc_m_24tree_statement_list_node ((*x).next);
      gt_ggc_m_9tree_node ((*x).stmt);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_varray_head_tag (void *x_p)
{
  struct varray_head_tag * const x = (struct varray_head_tag *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_S ((*x).name);
      switch ((*x).type)
        {
        case VARRAY_DATA_C:
          break;
        case VARRAY_DATA_UC:
          break;
        case VARRAY_DATA_S:
          break;
        case VARRAY_DATA_US:
          break;
        case VARRAY_DATA_I:
          break;
        case VARRAY_DATA_U:
          break;
        case VARRAY_DATA_L:
          break;
        case VARRAY_DATA_UL:
          break;
        case VARRAY_DATA_HINT:
          break;
        case VARRAY_DATA_UHINT:
          break;
        case VARRAY_DATA_GENERIC:
          gcc_unreachable ();
          break;
        case VARRAY_DATA_CPTR:
          {
            size_t i10;
            size_t l10 = (size_t)((*x).num_elements);
            for (i10 = 0; i10 != l10; i10++) {
              gt_ggc_m_S ((*x).data.vdt_cptr[i10]);
            }
          }
          break;
        case VARRAY_DATA_RTX:
          {
            size_t i11;
            size_t l11 = (size_t)((*x).num_elements);
            for (i11 = 0; i11 != l11; i11++) {
              gt_ggc_m_7rtx_def ((*x).data.vdt_rtx[i11]);
            }
          }
          break;
        case VARRAY_DATA_RTVEC:
          {
            size_t i12;
            size_t l12 = (size_t)((*x).num_elements);
            for (i12 = 0; i12 != l12; i12++) {
              gt_ggc_m_9rtvec_def ((*x).data.vdt_rtvec[i12]);
            }
          }
          break;
        case VARRAY_DATA_TREE:
          {
            size_t i13;
            size_t l13 = (size_t)((*x).num_elements);
            for (i13 = 0; i13 != l13; i13++) {
              gt_ggc_m_9tree_node ((*x).data.vdt_tree[i13]);
            }
          }
          break;
        case VARRAY_DATA_BITMAP:
          {
            size_t i14;
            size_t l14 = (size_t)((*x).num_elements);
            for (i14 = 0; i14 != l14; i14++) {
              gt_ggc_m_15bitmap_head_def ((*x).data.vdt_bitmap[i14]);
            }
          }
          break;
        case VARRAY_DATA_TE:
          {
            size_t i15;
            size_t l15 = (size_t)((*x).num_elements);
            for (i15 = 0; i15 != l15; i15++) {
              gt_ggc_m_8elt_list ((*x).data.vdt_te[i15]);
            }
          }
          break;
        case VARRAY_DATA_EDGE:
          {
            size_t i16;
            size_t l16 = (size_t)((*x).num_elements);
            for (i16 = 0; i16 != l16; i16++) {
              gt_ggc_m_8edge_def ((*x).data.vdt_e[i16]);
            }
          }
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_ptr_info_def (void *x_p)
{
  struct ptr_info_def * const x = (struct ptr_info_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15bitmap_head_def ((*x).pt_vars);
      gt_ggc_m_9tree_node ((*x).name_mem_tag);
    }
}

void
gt_ggc_mx_VEC_constructor_elt_gc (void *x_p)
{
  struct VEC_constructor_elt_gc * const x = (struct VEC_constructor_elt_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).base.vec[i0].index);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].value);
        }
      }
    }
}

void
gt_ggc_mx_tree_ann_d (void *x_p)
{
  union tree_ann_d * const x = (union tree_ann_d *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (ann_type ((tree_ann_t)&((*x))))
        {
        case TREE_ANN_COMMON:
          gt_ggc_m_18gimple_statement_d ((*x).common.stmt);
          break;
        case VAR_ANN:
          gt_ggc_m_18gimple_statement_d ((*x).vdecl.common.stmt);
          gt_ggc_m_9tree_node ((*x).vdecl.mpt);
          gt_ggc_m_9tree_node ((*x).vdecl.symbol_mem_tag);
          gt_ggc_m_9tree_node ((*x).vdecl.current_def);
          break;
        case FUNCTION_ANN:
          gt_ggc_m_18gimple_statement_d ((*x).fdecl.common.stmt);
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_VEC_tree_gc (void *x_p)
{
  struct VEC_tree_gc * const x = (struct VEC_tree_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_function (void *x_p)
{
  struct function * const x = (struct function *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9eh_status ((*x).eh);
      gt_ggc_m_18control_flow_graph ((*x).cfg);
      gt_ggc_m_12gimple_seq_d ((*x).gimple_body);
      gt_ggc_m_9gimple_df ((*x).gimple_df);
      gt_ggc_m_5loops ((*x).x_current_loops);
      gt_ggc_m_9tree_node ((*x).decl);
      gt_ggc_m_9tree_node ((*x).static_chain_decl);
      gt_ggc_m_9tree_node ((*x).nonlocal_goto_save_area);
      gt_ggc_m_9tree_node ((*x).local_decls);
      gt_ggc_m_16machine_function ((*x).machine);
      gt_ggc_m_17language_function ((*x).language);
      gt_ggc_m_P9tree_node4htab ((*x).used_types_hash);
    }
}

void
gt_ggc_mx_basic_block_def (void *x_p)
{
  struct basic_block_def * x = (struct basic_block_def *)x_p;
  struct basic_block_def * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next_bb);
  if (x != xlimit)
    for (;;)
      {
        struct basic_block_def * const xprev = ((*x).prev_bb);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_11VEC_edge_gc ((*x).preds);
      gt_ggc_m_11VEC_edge_gc ((*x).succs);
      gt_ggc_m_4loop ((*x).loop_father);
      gt_ggc_m_15basic_block_def ((*x).prev_bb);
      gt_ggc_m_15basic_block_def ((*x).next_bb);
      switch (((((*x)).flags & BB_RTL) != 0))
        {
        case 0:
          gt_ggc_m_14gimple_bb_info ((*x).il.gimple);
          break;
        case 1:
          gt_ggc_m_11rtl_bb_info ((*x).il.rtl);
          break;
        default:
          break;
        }
      x = ((*x).next_bb);
    }
}

void
gt_ggc_mx_fixed_value (void *x_p)
{
  struct fixed_value * const x = (struct fixed_value *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_real_value (void *x_p)
{
  struct real_value * const x = (struct real_value *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_VEC_rtx_gc (void *x_p)
{
  struct VEC_rtx_gc * const x = (struct VEC_rtx_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_7rtx_def ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_object_block (void *x_p)
{
  struct object_block * const x = (struct object_block *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7section ((*x).sect);
      gt_ggc_m_10VEC_rtx_gc ((*x).objects);
      gt_ggc_m_10VEC_rtx_gc ((*x).anchors);
    }
}

void
gt_ggc_mx_reg_attrs (void *x_p)
{
  struct reg_attrs * const x = (struct reg_attrs *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).decl);
    }
}

void
gt_ggc_mx_mem_attrs (void *x_p)
{
  struct mem_attrs * const x = (struct mem_attrs *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).expr);
      gt_ggc_m_7rtx_def ((*x).offset);
      gt_ggc_m_7rtx_def ((*x).size);
    }
}

void
gt_ggc_mx_bitmap_obstack (void *x_p)
{
  struct bitmap_obstack * const x = (struct bitmap_obstack *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18bitmap_element_def ((*x).elements);
      gt_ggc_m_15bitmap_head_def ((*x).heads);
    }
}

void
gt_ggc_mx_bitmap_element_def (void *x_p)
{
  struct bitmap_element_def * const x = (struct bitmap_element_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18bitmap_element_def ((*x).next);
      gt_ggc_m_18bitmap_element_def ((*x).prev);
    }
}

void
gt_ggc_mx_machine_function (void *x_p)
{
  struct machine_function * const x = (struct machine_function *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_17stack_local_entry ((*x).stack_locals);
      gt_ggc_m_S ((*x).some_ld_name);
    }
}

void
gt_ggc_mx_gimple_seq_node_d (void *x_p)
{
  struct gimple_seq_node_d * x = (struct gimple_seq_node_d *)x_p;
  struct gimple_seq_node_d * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct gimple_seq_node_d * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_18gimple_statement_d ((*x).stmt);
      gt_ggc_m_17gimple_seq_node_d ((*x).prev);
      gt_ggc_m_17gimple_seq_node_d ((*x).next);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_gimple_seq_d (void *x_p)
{
  struct gimple_seq_d * x = (struct gimple_seq_d *)x_p;
  struct gimple_seq_d * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next_free);
  while (x != xlimit)
    {
      gt_ggc_m_17gimple_seq_node_d ((*x).first);
      gt_ggc_m_17gimple_seq_node_d ((*x).last);
      gt_ggc_m_12gimple_seq_d ((*x).next_free);
      x = ((*x).next_free);
    }
}

void
gt_ggc_mx_section (void *x_p)
{
  union section * const x = (union section *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (SECTION_STYLE (&(((*x)))))
        {
        case SECTION_NAMED:
          gt_ggc_m_S ((*x).named.name);
          gt_ggc_m_9tree_node ((*x).named.decl);
          break;
        case SECTION_UNNAMED:
          gt_ggc_m_7section ((*x).unnamed.next);
          break;
        case SECTION_NOSWITCH:
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_gimple_statement_d (void *x_p)
{
  union gimple_statement_d * const x = (union gimple_statement_d *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (gimple_statement_structure (&((*x))))
        {
        case GSS_BASE:
          gt_ggc_m_15basic_block_def ((*x).gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gsbase.block);
          break;
        case GSS_WITH_OPS:
          gt_ggc_m_15basic_block_def ((*x).gsops.opbase.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gsops.opbase.gsbase.block);
          {
            size_t i0;
            size_t l0 = (size_t)(((*x).gsops).opbase.gsbase.num_ops);
            for (i0 = 0; i0 != l0; i0++) {
              gt_ggc_m_9tree_node ((*x).gsops.op[i0]);
            }
          }
          break;
        case GSS_WITH_MEM_OPS:
          gt_ggc_m_15basic_block_def ((*x).gsmem.membase.opbase.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gsmem.membase.opbase.gsbase.block);
          {
            size_t i1;
            size_t l1 = (size_t)(((*x).gsmem).membase.opbase.gsbase.num_ops);
            for (i1 = 0; i1 != l1; i1++) {
              gt_ggc_m_9tree_node ((*x).gsmem.op[i1]);
            }
          }
          break;
        case GSS_OMP:
          gt_ggc_m_15basic_block_def ((*x).omp.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).omp.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).omp.body);
          break;
        case GSS_BIND:
          gt_ggc_m_15basic_block_def ((*x).gimple_bind.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_bind.gsbase.block);
          gt_ggc_m_9tree_node ((*x).gimple_bind.vars);
          gt_ggc_m_9tree_node ((*x).gimple_bind.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_bind.body);
          break;
        case GSS_CATCH:
          gt_ggc_m_15basic_block_def ((*x).gimple_catch.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_catch.gsbase.block);
          gt_ggc_m_9tree_node ((*x).gimple_catch.types);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_catch.handler);
          break;
        case GSS_EH_FILTER:
          gt_ggc_m_15basic_block_def ((*x).gimple_eh_filter.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_eh_filter.gsbase.block);
          gt_ggc_m_9tree_node ((*x).gimple_eh_filter.types);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_eh_filter.failure);
          break;
        case GSS_PHI:
          gt_ggc_m_15basic_block_def ((*x).gimple_phi.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_phi.gsbase.block);
          gt_ggc_m_9tree_node ((*x).gimple_phi.result);
          {
            size_t i2;
            size_t l2 = (size_t)(((*x).gimple_phi).nargs);
            for (i2 = 0; i2 != l2; i2++) {
              gt_ggc_m_9tree_node ((*x).gimple_phi.args[i2].def);
            }
          }
          break;
        case GSS_RESX:
          gt_ggc_m_15basic_block_def ((*x).gimple_resx.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_resx.gsbase.block);
          break;
        case GSS_TRY:
          gt_ggc_m_15basic_block_def ((*x).gimple_try.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_try.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_try.eval);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_try.cleanup);
          break;
        case GSS_WCE:
          gt_ggc_m_15basic_block_def ((*x).gimple_wce.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_wce.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_wce.cleanup);
          break;
        case GSS_ASM:
          gt_ggc_m_15basic_block_def ((*x).gimple_asm.membase.opbase.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_asm.membase.opbase.gsbase.block);
          gt_ggc_m_S ((*x).gimple_asm.string);
          {
            size_t i3;
            size_t l3 = (size_t)(((*x).gimple_asm).membase.opbase.gsbase.num_ops);
            for (i3 = 0; i3 != l3; i3++) {
              gt_ggc_m_9tree_node ((*x).gimple_asm.op[i3]);
            }
          }
          break;
        case GSS_OMP_CRITICAL:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_critical.omp.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_critical.omp.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_omp_critical.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_critical.name);
          break;
        case GSS_OMP_FOR:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_for.omp.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_for.omp.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_omp_for.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_for.clauses);
          if ((*x).gimple_omp_for.iter != NULL) {
            size_t i4;
            for (i4 = 0; i4 != (size_t)(((*x).gimple_omp_for).collapse); i4++) {
              gt_ggc_m_9tree_node ((*x).gimple_omp_for.iter[i4].index);
              gt_ggc_m_9tree_node ((*x).gimple_omp_for.iter[i4].initial);
              gt_ggc_m_9tree_node ((*x).gimple_omp_for.iter[i4].final);
              gt_ggc_m_9tree_node ((*x).gimple_omp_for.iter[i4].incr);
            }
            ggc_mark ((*x).gimple_omp_for.iter);
          }
          gt_ggc_m_12gimple_seq_d ((*x).gimple_omp_for.pre_body);
          break;
        case GSS_OMP_PARALLEL:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_parallel.omp.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_parallel.omp.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_omp_parallel.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_parallel.clauses);
          gt_ggc_m_9tree_node ((*x).gimple_omp_parallel.child_fn);
          gt_ggc_m_9tree_node ((*x).gimple_omp_parallel.data_arg);
          break;
        case GSS_OMP_TASK:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_task.par.omp.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.par.omp.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_omp_task.par.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.par.clauses);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.par.child_fn);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.par.data_arg);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.copy_fn);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.arg_size);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.arg_align);
          break;
        case GSS_OMP_SECTIONS:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_sections.omp.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_sections.omp.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_omp_sections.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_sections.clauses);
          gt_ggc_m_9tree_node ((*x).gimple_omp_sections.control);
          break;
        case GSS_OMP_SINGLE:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_single.omp.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_single.omp.gsbase.block);
          gt_ggc_m_12gimple_seq_d ((*x).gimple_omp_single.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_single.clauses);
          break;
        case GSS_OMP_CONTINUE:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_continue.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_continue.gsbase.block);
          gt_ggc_m_9tree_node ((*x).gimple_omp_continue.control_def);
          gt_ggc_m_9tree_node ((*x).gimple_omp_continue.control_use);
          break;
        case GSS_OMP_ATOMIC_LOAD:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_atomic_load.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_atomic_load.gsbase.block);
          gt_ggc_m_9tree_node ((*x).gimple_omp_atomic_load.rhs);
          gt_ggc_m_9tree_node ((*x).gimple_omp_atomic_load.lhs);
          break;
        case GSS_OMP_ATOMIC_STORE:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_atomic_store.gsbase.bb);
          gt_ggc_m_9tree_node ((*x).gimple_omp_atomic_store.gsbase.block);
          gt_ggc_m_9tree_node ((*x).gimple_omp_atomic_store.val);
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_rtvec_def (void *x_p)
{
  struct rtvec_def * const x = (struct rtvec_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x)).num_elem);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_7rtx_def ((*x).elem[i0]);
        }
      }
    }
}

void
gt_ggc_mx_rtx_def (void *x_p)
{
  struct rtx_def * x = (struct rtx_def *)x_p;
  struct rtx_def * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = (RTX_NEXT (&(*xlimit)));
  if (x != xlimit)
    for (;;)
      {
        struct rtx_def * const xprev = (RTX_PREV (&(*x)));
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      switch (GET_CODE (&(*x)))
        {
        case VAR_LOCATION:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case US_TRUNCATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_TRUNCATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_MINUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_ASHIFT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_ASHIFT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_ABS:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_NEG:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_NEG:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_MINUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_PLUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_PLUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_DUPLICATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_CONCAT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_SELECT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_MERGE:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LO_SUM:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case HIGH:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ZERO_EXTRACT:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SIGN_EXTRACT:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PARITY:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POPCOUNT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CTZ:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLZ:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FFS:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case BSWAP:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SQRT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ABS:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_SAT_FRACT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SAT_FRACT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FRACT_CONVERT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FRACT_CONVERT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FIX:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FLOAT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FIX:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT_TRUNCATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT_EXTEND:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case TRUNCATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ZERO_EXTEND:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SIGN_EXTEND:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LTGT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNLT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNLE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNGT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNGE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNEQ:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ORDERED:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNORDERED:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LTU:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LEU:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GTU:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GEU:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EQ:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_MODIFY:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_MODIFY:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_INC:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_DEC:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_INC:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_DEC:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMAX:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMIN:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SMAX:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SMIN:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ROTATERT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LSHIFTRT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ASHIFTRT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ROTATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ASHIFT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NOT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case XOR:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case IOR:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case AND:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMOD:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UDIV:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MOD:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_DIV:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_DIV:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case DIV:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_MULT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_MULT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MULT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NEG:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MINUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PLUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case COMPARE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case IF_THEN_ELSE:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CC0:
          break;
        case SYMBOL_REF:
          switch (SYMBOL_REF_HAS_BLOCK_INFO_P (&(*x)))
            {
            case 1:
              gt_ggc_m_12object_block ((*x).u.block_sym.block);
              break;
            default:
              break;
            }
          switch (CONSTANT_POOL_ADDRESS_P (&(*x)))
            {
            case 1:
              gt_ggc_m_23constant_descriptor_rtx ((*x).u.fld[2].rt_constant);
              break;
            default:
              gt_ggc_m_9tree_node ((*x).u.fld[2].rt_tree);
              break;
            }
          gt_ggc_m_S ((*x).u.fld[0].rt_str);
          break;
        case LABEL_REF:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MEM:
          gt_ggc_m_9mem_attrs ((*x).u.fld[1].rt_mem);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CONCATN:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case CONCAT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case STRICT_LOW_PART:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SUBREG:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SCRATCH:
          break;
        case REG:
          gt_ggc_m_9reg_attrs ((*x).u.fld[2].rt_reg);
          break;
        case VALUE:
          break;
        case PC:
          break;
        case CONST:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CONST_STRING:
          gt_ggc_m_S ((*x).u.fld[0].rt_str);
          break;
        case CONST_VECTOR:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case CONST_DOUBLE:
          break;
        case CONST_FIXED:
          break;
        case CONST_INT:
          break;
        case RESX:
          break;
        case TRAP_IF:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case RETURN:
          break;
        case CALL:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLOBBER:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case USE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SET:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PREFETCH:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ADDR_DIFF_VEC:
          gt_ggc_m_7rtx_def ((*x).u.fld[3].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_9rtvec_def ((*x).u.fld[1].rt_rtvec);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ADDR_VEC:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case UNSPEC_VOLATILE:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case UNSPEC:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case ASM_OPERANDS:
          gt_ggc_m_9rtvec_def ((*x).u.fld[4].rt_rtvec);
          gt_ggc_m_9rtvec_def ((*x).u.fld[3].rt_rtvec);
          gt_ggc_m_S ((*x).u.fld[1].rt_str);
          gt_ggc_m_S ((*x).u.fld[0].rt_str);
          break;
        case ASM_INPUT:
          gt_ggc_m_S ((*x).u.fld[0].rt_str);
          break;
        case PARALLEL:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case COND_EXEC:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NOTE:
          switch (NOTE_KIND (&(*x)))
            {
            default:
              gt_ggc_m_S ((*x).u.fld[4].rt_str);
              break;
            case NOTE_INSN_SWITCH_TEXT_SECTIONS:
              break;
            case NOTE_INSN_BASIC_BLOCK:
              break;
            case NOTE_INSN_VAR_LOCATION:
              gt_ggc_m_7rtx_def ((*x).u.fld[4].rt_rtx);
              break;
            case NOTE_INSN_EH_REGION_END:
              break;
            case NOTE_INSN_EH_REGION_BEG:
              break;
            case NOTE_INSN_EPILOGUE_BEG:
              break;
            case NOTE_INSN_PROLOGUE_END:
              break;
            case NOTE_INSN_FUNCTION_BEG:
              break;
            case NOTE_INSN_BLOCK_END:
              gt_ggc_m_9tree_node ((*x).u.fld[4].rt_tree);
              break;
            case NOTE_INSN_BLOCK_BEG:
              gt_ggc_m_9tree_node ((*x).u.fld[4].rt_tree);
              break;
            case NOTE_INSN_DELETED_LABEL:
              break;
            case NOTE_INSN_DELETED:
              break;
            }
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case CODE_LABEL:
          gt_ggc_m_S ((*x).u.fld[7].rt_str);
          gt_ggc_m_7rtx_def ((*x).u.fld[5].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case BARRIER:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case CALL_INSN:
          gt_ggc_m_7rtx_def ((*x).u.fld[8].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[5].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case JUMP_INSN:
          gt_ggc_m_7rtx_def ((*x).u.fld[8].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[5].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case INSN:
          gt_ggc_m_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[5].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case ADDRESS:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SEQUENCE:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case INSN_LIST:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EXPR_LIST:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNKNOWN:
          break;
        default:
          break;
        }
      x = (RTX_NEXT (&(*x)));
    }
}

void
gt_ggc_mx_bitmap_head_def (void *x_p)
{
  struct bitmap_head_def * const x = (struct bitmap_head_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18bitmap_element_def ((*x).first);
      gt_ggc_m_18bitmap_element_def ((*x).current);
      gt_ggc_m_14bitmap_obstack ((*x).obstack);
    }
}

void
gt_ggc_mx_answer (void *x_p)
{
  struct answer * const x = (struct answer *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_6answer ((*x).next);
      {
        size_t i0;
        size_t l0 = (size_t)(((*x)).count);
        for (i0 = 0; i0 != l0; i0++) {
          switch (cpp_token_val_index (&((*x).first[i0])))
            {
            case CPP_TOKEN_FLD_NODE:
              {
                union tree_node * const x1 =
                  ((*x).first[i0].val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).first[i0].val.node))) : NULL;
                gt_ggc_m_9tree_node (x1);
              }
              break;
            case CPP_TOKEN_FLD_SOURCE:
              gt_ggc_m_9cpp_token ((*x).first[i0].val.source);
              break;
            case CPP_TOKEN_FLD_STR:
              gt_ggc_m_S ((*x).first[i0].val.str.text);
              break;
            case CPP_TOKEN_FLD_ARG_NO:
              break;
            case CPP_TOKEN_FLD_PRAGMA:
              break;
            default:
              break;
            }
        }
      }
    }
}

void
gt_ggc_mx_cpp_macro (void *x_p)
{
  struct cpp_macro * const x = (struct cpp_macro *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).params != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).paramc); i0++) {
          {
            union tree_node * const x1 =
              ((*x).params[i0]) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).params[i0]))) : NULL;
            gt_ggc_m_9tree_node (x1);
          }
        }
        ggc_mark ((*x).params);
      }
      switch (((*x)).traditional)
        {
        case 0:
          if ((*x).exp.tokens != NULL) {
            size_t i2;
            for (i2 = 0; i2 != (size_t)((*x).count); i2++) {
              switch (cpp_token_val_index (&((*x).exp.tokens[i2])))
                {
                case CPP_TOKEN_FLD_NODE:
                  {
                    union tree_node * const x3 =
                      ((*x).exp.tokens[i2].val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).exp.tokens[i2].val.node))) : NULL;
                    gt_ggc_m_9tree_node (x3);
                  }
                  break;
                case CPP_TOKEN_FLD_SOURCE:
                  gt_ggc_m_9cpp_token ((*x).exp.tokens[i2].val.source);
                  break;
                case CPP_TOKEN_FLD_STR:
                  gt_ggc_m_S ((*x).exp.tokens[i2].val.str.text);
                  break;
                case CPP_TOKEN_FLD_ARG_NO:
                  break;
                case CPP_TOKEN_FLD_PRAGMA:
                  break;
                default:
                  break;
                }
            }
            ggc_mark ((*x).exp.tokens);
          }
          break;
        case 1:
          gt_ggc_m_S ((*x).exp.text);
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_cpp_token (void *x_p)
{
  struct cpp_token * const x = (struct cpp_token *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (cpp_token_val_index (&((*x))))
        {
        case CPP_TOKEN_FLD_NODE:
          {
            union tree_node * const x0 =
              ((*x).val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).val.node))) : NULL;
            gt_ggc_m_9tree_node (x0);
          }
          break;
        case CPP_TOKEN_FLD_SOURCE:
          gt_ggc_m_9cpp_token ((*x).val.source);
          break;
        case CPP_TOKEN_FLD_STR:
          gt_ggc_m_S ((*x).val.str.text);
          break;
        case CPP_TOKEN_FLD_ARG_NO:
          break;
        case CPP_TOKEN_FLD_PRAGMA:
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_line_maps (void *x_p)
{
  struct line_maps * const x = (struct line_maps *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).maps != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).used); i0++) {
          gt_ggc_m_S ((*x).maps[i0].to_file);
        }
        ggc_mark ((*x).maps);
      }
    }
}

void
gt_ggc_m_II17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_II17splay_tree_node_s ((*x).left);
      gt_ggc_m_II17splay_tree_node_s ((*x).right);
    }
}

void
gt_ggc_m_SP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_S ((void *)(*x).key);
      gt_ggc_m_9tree_node ((void *)(*x).value);
      gt_ggc_m_SP9tree_node17splay_tree_node_s ((*x).left);
      gt_ggc_m_SP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_ggc_m_P9tree_nodeP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((void *)(*x).key);
      gt_ggc_m_9tree_node ((void *)(*x).value);
      gt_ggc_m_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).left);
      gt_ggc_m_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_ggc_m_IP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((void *)(*x).value);
      gt_ggc_m_IP9tree_node17splay_tree_node_s ((*x).left);
      gt_ggc_m_IP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_ggc_m_P12tree_int_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_12tree_int_map ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_IP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_IP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_ggc_m_P9tree_nodeP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_ggc_m_P12varpool_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_12varpool_node ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P12object_block4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_12object_block ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P7section4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_7section ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P17tree_priority_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_17tree_priority_map ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P8tree_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_8tree_map ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P15throw_stmt_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_15throw_stmt_node ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P9reg_attrs4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_9reg_attrs ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P9mem_attrs4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_9mem_attrs ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P7rtx_def4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_7rtx_def ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_SP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_SP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_ggc_m_P11cgraph_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_11cgraph_node ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_II12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_II17splay_tree_node_s ((*x).root);
    }
}

void
gt_ggc_m_P11cgraph_edge4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_11cgraph_edge ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P9loop_exit4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_9loop_exit ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P24types_used_by_vars_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_24types_used_by_vars_entry ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P9tree_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_9tree_node ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_pch_nx_ssa_operand_memory_d (void *x_p)
{
  struct ssa_operand_memory_d * x = (struct ssa_operand_memory_d *)x_p;
  struct ssa_operand_memory_d * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_20ssa_operand_memory_d, gt_ggc_e_20ssa_operand_memory_d))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_20ssa_operand_memory_d ((*x).next);
      x = ((*x).next);
    }
}

void
gt_pch_nx_VEC_gimple_gc (void *x_p)
{
  struct VEC_gimple_gc * const x = (struct VEC_gimple_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13VEC_gimple_gc, gt_ggc_e_13VEC_gimple_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_18gimple_statement_d ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_throw_stmt_node (void *x_p)
{
  struct throw_stmt_node * const x = (struct throw_stmt_node *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15throw_stmt_node, gt_ggc_e_15throw_stmt_node))
    {
      gt_pch_n_18gimple_statement_d ((*x).stmt);
    }
}

void
gt_pch_nx_cgraph_asm_node (void *x_p)
{
  struct cgraph_asm_node * const x = (struct cgraph_asm_node *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15cgraph_asm_node, gt_ggc_e_15cgraph_asm_node))
    {
      gt_pch_n_15cgraph_asm_node ((*x).next);
      gt_pch_n_9tree_node ((*x).asm_str);
    }
}

void
gt_pch_nx_varpool_node (void *x_p)
{
  struct varpool_node * x = (struct varpool_node *)x_p;
  struct varpool_node * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_12varpool_node, gt_ggc_e_12varpool_node))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_9tree_node ((*x).decl);
      gt_pch_n_12varpool_node ((*x).next);
      gt_pch_n_12varpool_node ((*x).next_needed);
      x = ((*x).next);
    }
}

void
gt_pch_nx_cgraph_edge (void *x_p)
{
  struct cgraph_edge * x = (struct cgraph_edge *)x_p;
  struct cgraph_edge * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_11cgraph_edge, gt_ggc_e_11cgraph_edge))
   xlimit = ((*xlimit).next_caller);
  if (x != xlimit)
    for (;;)
      {
        struct cgraph_edge * const xprev = ((*x).prev_caller);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_11cgraph_edge, gt_ggc_e_11cgraph_edge);
      }
  while (x != xlimit)
    {
      gt_pch_n_11cgraph_node ((*x).caller);
      gt_pch_n_11cgraph_node ((*x).callee);
      gt_pch_n_11cgraph_edge ((*x).prev_caller);
      gt_pch_n_11cgraph_edge ((*x).next_caller);
      gt_pch_n_11cgraph_edge ((*x).prev_callee);
      gt_pch_n_11cgraph_edge ((*x).next_callee);
      gt_pch_n_18gimple_statement_d ((*x).call_stmt);
      gt_pch_n_S ((*x).inline_failed);
      x = ((*x).next_caller);
    }
}

void
gt_pch_nx_cgraph_node (void *x_p)
{
  struct cgraph_node * x = (struct cgraph_node *)x_p;
  struct cgraph_node * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_11cgraph_node, gt_ggc_e_11cgraph_node))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct cgraph_node * const xprev = ((*x).previous);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_11cgraph_node, gt_ggc_e_11cgraph_node);
      }
  while (x != xlimit)
    {
      gt_pch_n_9tree_node ((*x).decl);
      gt_pch_n_11cgraph_edge ((*x).callees);
      gt_pch_n_11cgraph_edge ((*x).callers);
      gt_pch_n_11cgraph_node ((*x).next);
      gt_pch_n_11cgraph_node ((*x).previous);
      gt_pch_n_11cgraph_node ((*x).origin);
      gt_pch_n_11cgraph_node ((*x).nested);
      gt_pch_n_11cgraph_node ((*x).next_nested);
      gt_pch_n_11cgraph_node ((*x).next_needed);
      gt_pch_n_11cgraph_node ((*x).next_clone);
      gt_pch_n_11cgraph_node ((*x).prev_clone);
      gt_pch_n_11cgraph_node ((*x).master_clone);
      gt_pch_n_P11cgraph_edge4htab ((*x).call_site_hash);
      gt_pch_n_11cgraph_node ((*x).global.inlined_to);
      gt_pch_n_9tree_node ((*x).inline_decl);
      x = ((*x).next);
    }
}

void
gt_pch_nx_VEC_basic_block_gc (void *x_p)
{
  struct VEC_basic_block_gc * const x = (struct VEC_basic_block_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18VEC_basic_block_gc, gt_ggc_e_18VEC_basic_block_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_15basic_block_def ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_gimple_bb_info (void *x_p)
{
  struct gimple_bb_info * const x = (struct gimple_bb_info *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14gimple_bb_info, gt_ggc_e_14gimple_bb_info))
    {
      gt_pch_n_12gimple_seq_d ((*x).seq);
      gt_pch_n_12gimple_seq_d ((*x).phi_nodes);
    }
}

void
gt_pch_nx_rtl_bb_info (void *x_p)
{
  struct rtl_bb_info * const x = (struct rtl_bb_info *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11rtl_bb_info, gt_ggc_e_11rtl_bb_info))
    {
      gt_pch_n_7rtx_def ((*x).head_);
      gt_pch_n_7rtx_def ((*x).end_);
      gt_pch_n_7rtx_def ((*x).header);
      gt_pch_n_7rtx_def ((*x).footer);
    }
}

void
gt_pch_nx_VEC_edge_gc (void *x_p)
{
  struct VEC_edge_gc * const x = (struct VEC_edge_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11VEC_edge_gc, gt_ggc_e_11VEC_edge_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_8edge_def ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_cselib_val_struct (void *x_p)
{
  struct cselib_val_struct * const x = (struct cselib_val_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17cselib_val_struct, gt_ggc_e_17cselib_val_struct))
    {
      gt_pch_n_7rtx_def ((*x).val_rtx);
      gt_pch_n_12elt_loc_list ((*x).locs);
      gt_pch_n_8elt_list ((*x).addr_list);
      gt_pch_n_17cselib_val_struct ((*x).next_containing_mem);
    }
}

void
gt_pch_nx_elt_loc_list (void *x_p)
{
  struct elt_loc_list * const x = (struct elt_loc_list *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12elt_loc_list, gt_ggc_e_12elt_loc_list))
    {
      gt_pch_n_12elt_loc_list ((*x).next);
      gt_pch_n_7rtx_def ((*x).loc);
      gt_pch_n_7rtx_def ((*x).setting_insn);
    }
}

void
gt_pch_nx_VEC_loop_p_gc (void *x_p)
{
  struct VEC_loop_p_gc * const x = (struct VEC_loop_p_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13VEC_loop_p_gc, gt_ggc_e_13VEC_loop_p_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_4loop ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_loop (void *x_p)
{
  struct loop * x = (struct loop *)x_p;
  struct loop * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_4loop, gt_ggc_e_4loop))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_15basic_block_def ((*x).header);
      gt_pch_n_15basic_block_def ((*x).latch);
      gt_pch_n_13VEC_loop_p_gc ((*x).superloops);
      gt_pch_n_4loop ((*x).inner);
      gt_pch_n_4loop ((*x).next);
      gt_pch_n_9tree_node ((*x).nb_iterations);
      gt_pch_n_13nb_iter_bound ((*x).bounds);
      gt_pch_n_9loop_exit ((*x).exits);
      x = ((*x).next);
    }
}

void
gt_pch_nx_loop_exit (void *x_p)
{
  struct loop_exit * const x = (struct loop_exit *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9loop_exit, gt_ggc_e_9loop_exit))
    {
      gt_pch_n_8edge_def ((*x).e);
      gt_pch_n_9loop_exit ((*x).prev);
      gt_pch_n_9loop_exit ((*x).next);
      gt_pch_n_9loop_exit ((*x).next_e);
    }
}

void
gt_pch_nx_nb_iter_bound (void *x_p)
{
  struct nb_iter_bound * x = (struct nb_iter_bound *)x_p;
  struct nb_iter_bound * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_13nb_iter_bound, gt_ggc_e_13nb_iter_bound))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_18gimple_statement_d ((*x).stmt);
      gt_pch_n_13nb_iter_bound ((*x).next);
      x = ((*x).next);
    }
}

void
gt_pch_nx_types_used_by_vars_entry (void *x_p)
{
  struct types_used_by_vars_entry * const x = (struct types_used_by_vars_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_24types_used_by_vars_entry, gt_ggc_e_24types_used_by_vars_entry))
    {
      gt_pch_n_9tree_node ((*x).type);
      gt_pch_n_9tree_node ((*x).var_decl);
    }
}

void
gt_pch_nx_loops (void *x_p)
{
  struct loops * const x = (struct loops *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_5loops, gt_ggc_e_5loops))
    {
      gt_pch_n_13VEC_loop_p_gc ((*x).larray);
      gt_pch_n_P9loop_exit4htab ((*x).exits);
      gt_pch_n_4loop ((*x).tree_root);
    }
}

void
gt_pch_nx_control_flow_graph (void *x_p)
{
  struct control_flow_graph * const x = (struct control_flow_graph *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18control_flow_graph, gt_ggc_e_18control_flow_graph))
    {
      gt_pch_n_15basic_block_def ((*x).x_entry_block_ptr);
      gt_pch_n_15basic_block_def ((*x).x_exit_block_ptr);
      gt_pch_n_18VEC_basic_block_gc ((*x).x_basic_block_info);
      gt_pch_n_18VEC_basic_block_gc ((*x).x_label_to_block_map);
    }
}

void
gt_pch_nx_VEC_temp_slot_p_gc (void *x_p)
{
  struct VEC_temp_slot_p_gc * const x = (struct VEC_temp_slot_p_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18VEC_temp_slot_p_gc, gt_ggc_e_18VEC_temp_slot_p_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9temp_slot ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_gimple_df (void *x_p)
{
  struct gimple_df * const x = (struct gimple_df *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9gimple_df, gt_ggc_e_9gimple_df))
    {
      gt_pch_n_P9tree_node4htab ((*x).referenced_vars);
      gt_pch_n_13VEC_gimple_gc ((*x).modified_noreturn_calls);
      gt_pch_n_11VEC_tree_gc ((*x).ssa_names);
      gt_pch_n_9tree_node ((*x).global_var);
      gt_pch_n_9tree_node ((*x).nonlocal_all);
      gt_pch_n_15bitmap_head_def ((*x).call_clobbered_vars);
      gt_pch_n_15bitmap_head_def ((*x).call_used_vars);
      gt_pch_n_15bitmap_head_def ((*x).addressable_vars);
      gt_pch_n_9tree_node ((*x).free_ssanames);
      gt_pch_n_P9tree_node4htab ((*x).default_defs);
      gt_pch_n_20ssa_operand_memory_d ((*x).ssa_operands.operand_memory);
    }
}

void
gt_pch_nx_VEC_call_site_record_gc (void *x_p)
{
  struct VEC_call_site_record_gc * const x = (struct VEC_call_site_record_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_23VEC_call_site_record_gc, gt_ggc_e_23VEC_call_site_record_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_16call_site_record ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_sequence_stack (void *x_p)
{
  struct sequence_stack * const x = (struct sequence_stack *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14sequence_stack, gt_ggc_e_14sequence_stack))
    {
      gt_pch_n_7rtx_def ((*x).first);
      gt_pch_n_7rtx_def ((*x).last);
      gt_pch_n_14sequence_stack ((*x).next);
    }
}

void
gt_pch_nx_edge_def (void *x_p)
{
  struct edge_def * const x = (struct edge_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8edge_def, gt_ggc_e_8edge_def))
    {
      gt_pch_n_15basic_block_def ((*x).src);
      gt_pch_n_15basic_block_def ((*x).dest);
      switch (current_ir_type () == IR_GIMPLE)
        {
        case true:
          gt_pch_n_12gimple_seq_d ((*x).insns.g);
          break;
        case false:
          gt_pch_n_7rtx_def ((*x).insns.r);
          break;
        default:
          break;
        }
      gt_pch_n_9tree_node ((*x).goto_block);
    }
}

void
gt_pch_nx_elt_list (void *x_p)
{
  struct elt_list * const x = (struct elt_list *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8elt_list, gt_ggc_e_8elt_list))
    {
      gt_pch_n_8elt_list ((*x).next);
      gt_pch_n_17cselib_val_struct ((*x).elt);
    }
}

void
gt_pch_nx_tree_priority_map (void *x_p)
{
  struct tree_priority_map * const x = (struct tree_priority_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17tree_priority_map, gt_ggc_e_17tree_priority_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
    }
}

void
gt_pch_nx_tree_int_map (void *x_p)
{
  struct tree_int_map * const x = (struct tree_int_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12tree_int_map, gt_ggc_e_12tree_int_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
    }
}

void
gt_pch_nx_tree_map (void *x_p)
{
  struct tree_map * const x = (struct tree_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8tree_map, gt_ggc_e_8tree_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
      gt_pch_n_9tree_node ((*x).to);
    }
}

void
gt_pch_nx_tree_statement_list_node (void *x_p)
{
  struct tree_statement_list_node * x = (struct tree_statement_list_node *)x_p;
  struct tree_statement_list_node * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_24tree_statement_list_node, gt_ggc_e_24tree_statement_list_node))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct tree_statement_list_node * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_24tree_statement_list_node, gt_ggc_e_24tree_statement_list_node);
      }
  while (x != xlimit)
    {
      gt_pch_n_24tree_statement_list_node ((*x).prev);
      gt_pch_n_24tree_statement_list_node ((*x).next);
      gt_pch_n_9tree_node ((*x).stmt);
      x = ((*x).next);
    }
}

void
gt_pch_nx_varray_head_tag (void *x_p)
{
  struct varray_head_tag * const x = (struct varray_head_tag *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15varray_head_tag, gt_ggc_e_15varray_head_tag))
    {
      gt_pch_n_S ((*x).name);
      switch ((*x).type)
        {
        case VARRAY_DATA_C:
          break;
        case VARRAY_DATA_UC:
          break;
        case VARRAY_DATA_S:
          break;
        case VARRAY_DATA_US:
          break;
        case VARRAY_DATA_I:
          break;
        case VARRAY_DATA_U:
          break;
        case VARRAY_DATA_L:
          break;
        case VARRAY_DATA_UL:
          break;
        case VARRAY_DATA_HINT:
          break;
        case VARRAY_DATA_UHINT:
          break;
        case VARRAY_DATA_GENERIC:
          gcc_unreachable ();
          break;
        case VARRAY_DATA_CPTR:
          {
            size_t i10;
            size_t l10 = (size_t)((*x).num_elements);
            for (i10 = 0; i10 != l10; i10++) {
              gt_pch_n_S ((*x).data.vdt_cptr[i10]);
            }
          }
          break;
        case VARRAY_DATA_RTX:
          {
            size_t i11;
            size_t l11 = (size_t)((*x).num_elements);
            for (i11 = 0; i11 != l11; i11++) {
              gt_pch_n_7rtx_def ((*x).data.vdt_rtx[i11]);
            }
          }
          break;
        case VARRAY_DATA_RTVEC:
          {
            size_t i12;
            size_t l12 = (size_t)((*x).num_elements);
            for (i12 = 0; i12 != l12; i12++) {
              gt_pch_n_9rtvec_def ((*x).data.vdt_rtvec[i12]);
            }
          }
          break;
        case VARRAY_DATA_TREE:
          {
            size_t i13;
            size_t l13 = (size_t)((*x).num_elements);
            for (i13 = 0; i13 != l13; i13++) {
              gt_pch_n_9tree_node ((*x).data.vdt_tree[i13]);
            }
          }
          break;
        case VARRAY_DATA_BITMAP:
          {
            size_t i14;
            size_t l14 = (size_t)((*x).num_elements);
            for (i14 = 0; i14 != l14; i14++) {
              gt_pch_n_15bitmap_head_def ((*x).data.vdt_bitmap[i14]);
            }
          }
          break;
        case VARRAY_DATA_TE:
          {
            size_t i15;
            size_t l15 = (size_t)((*x).num_elements);
            for (i15 = 0; i15 != l15; i15++) {
              gt_pch_n_8elt_list ((*x).data.vdt_te[i15]);
            }
          }
          break;
        case VARRAY_DATA_EDGE:
          {
            size_t i16;
            size_t l16 = (size_t)((*x).num_elements);
            for (i16 = 0; i16 != l16; i16++) {
              gt_pch_n_8edge_def ((*x).data.vdt_e[i16]);
            }
          }
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_ptr_info_def (void *x_p)
{
  struct ptr_info_def * const x = (struct ptr_info_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12ptr_info_def, gt_ggc_e_12ptr_info_def))
    {
      gt_pch_n_15bitmap_head_def ((*x).pt_vars);
      gt_pch_n_9tree_node ((*x).name_mem_tag);
    }
}

void
gt_pch_nx_VEC_constructor_elt_gc (void *x_p)
{
  struct VEC_constructor_elt_gc * const x = (struct VEC_constructor_elt_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_22VEC_constructor_elt_gc, gt_ggc_e_22VEC_constructor_elt_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).base.vec[i0].index);
          gt_pch_n_9tree_node ((*x).base.vec[i0].value);
        }
      }
    }
}

void
gt_pch_nx_tree_ann_d (void *x_p)
{
  union tree_ann_d * const x = (union tree_ann_d *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_10tree_ann_d, gt_ggc_e_10tree_ann_d))
    {
      switch (ann_type ((tree_ann_t)&((*x))))
        {
        case TREE_ANN_COMMON:
          gt_pch_n_18gimple_statement_d ((*x).common.stmt);
          break;
        case VAR_ANN:
          gt_pch_n_18gimple_statement_d ((*x).vdecl.common.stmt);
          gt_pch_n_9tree_node ((*x).vdecl.mpt);
          gt_pch_n_9tree_node ((*x).vdecl.symbol_mem_tag);
          gt_pch_n_9tree_node ((*x).vdecl.current_def);
          break;
        case FUNCTION_ANN:
          gt_pch_n_18gimple_statement_d ((*x).fdecl.common.stmt);
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_VEC_tree_gc (void *x_p)
{
  struct VEC_tree_gc * const x = (struct VEC_tree_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11VEC_tree_gc, gt_ggc_e_11VEC_tree_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_function (void *x_p)
{
  struct function * const x = (struct function *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8function, gt_ggc_e_8function))
    {
      gt_pch_n_9eh_status ((*x).eh);
      gt_pch_n_18control_flow_graph ((*x).cfg);
      gt_pch_n_12gimple_seq_d ((*x).gimple_body);
      gt_pch_n_9gimple_df ((*x).gimple_df);
      gt_pch_n_5loops ((*x).x_current_loops);
      gt_pch_n_9tree_node ((*x).decl);
      gt_pch_n_9tree_node ((*x).static_chain_decl);
      gt_pch_n_9tree_node ((*x).nonlocal_goto_save_area);
      gt_pch_n_9tree_node ((*x).local_decls);
      gt_pch_n_16machine_function ((*x).machine);
      gt_pch_n_17language_function ((*x).language);
      gt_pch_n_P9tree_node4htab ((*x).used_types_hash);
    }
}

void
gt_pch_nx_basic_block_def (void *x_p)
{
  struct basic_block_def * x = (struct basic_block_def *)x_p;
  struct basic_block_def * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_15basic_block_def, gt_ggc_e_15basic_block_def))
   xlimit = ((*xlimit).next_bb);
  if (x != xlimit)
    for (;;)
      {
        struct basic_block_def * const xprev = ((*x).prev_bb);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_15basic_block_def, gt_ggc_e_15basic_block_def);
      }
  while (x != xlimit)
    {
      gt_pch_n_11VEC_edge_gc ((*x).preds);
      gt_pch_n_11VEC_edge_gc ((*x).succs);
      gt_pch_n_4loop ((*x).loop_father);
      gt_pch_n_15basic_block_def ((*x).prev_bb);
      gt_pch_n_15basic_block_def ((*x).next_bb);
      switch (((((*x)).flags & BB_RTL) != 0))
        {
        case 0:
          gt_pch_n_14gimple_bb_info ((*x).il.gimple);
          break;
        case 1:
          gt_pch_n_11rtl_bb_info ((*x).il.rtl);
          break;
        default:
          break;
        }
      x = ((*x).next_bb);
    }
}

void
gt_pch_nx_fixed_value (void *x_p)
{
  struct fixed_value * const x = (struct fixed_value *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11fixed_value, gt_ggc_e_11fixed_value))
    {
    }
}

void
gt_pch_nx_real_value (void *x_p)
{
  struct real_value * const x = (struct real_value *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_10real_value, gt_ggc_e_10real_value))
    {
    }
}

void
gt_pch_nx_VEC_rtx_gc (void *x_p)
{
  struct VEC_rtx_gc * const x = (struct VEC_rtx_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_10VEC_rtx_gc, gt_ggc_e_10VEC_rtx_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_7rtx_def ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_object_block (void *x_p)
{
  struct object_block * const x = (struct object_block *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12object_block, gt_ggc_e_12object_block))
    {
      gt_pch_n_7section ((*x).sect);
      gt_pch_n_10VEC_rtx_gc ((*x).objects);
      gt_pch_n_10VEC_rtx_gc ((*x).anchors);
    }
}

void
gt_pch_nx_reg_attrs (void *x_p)
{
  struct reg_attrs * const x = (struct reg_attrs *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9reg_attrs, gt_ggc_e_9reg_attrs))
    {
      gt_pch_n_9tree_node ((*x).decl);
    }
}

void
gt_pch_nx_mem_attrs (void *x_p)
{
  struct mem_attrs * const x = (struct mem_attrs *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9mem_attrs, gt_ggc_e_9mem_attrs))
    {
      gt_pch_n_9tree_node ((*x).expr);
      gt_pch_n_7rtx_def ((*x).offset);
      gt_pch_n_7rtx_def ((*x).size);
    }
}

void
gt_pch_nx_bitmap_obstack (void *x_p)
{
  struct bitmap_obstack * const x = (struct bitmap_obstack *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14bitmap_obstack, gt_ggc_e_14bitmap_obstack))
    {
      gt_pch_n_18bitmap_element_def ((*x).elements);
      gt_pch_n_15bitmap_head_def ((*x).heads);
    }
}

void
gt_pch_nx_bitmap_element_def (void *x_p)
{
  struct bitmap_element_def * const x = (struct bitmap_element_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18bitmap_element_def, gt_ggc_e_18bitmap_element_def))
    {
      gt_pch_n_18bitmap_element_def ((*x).next);
      gt_pch_n_18bitmap_element_def ((*x).prev);
    }
}

void
gt_pch_nx_machine_function (void *x_p)
{
  struct machine_function * const x = (struct machine_function *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16machine_function, gt_ggc_e_16machine_function))
    {
      gt_pch_n_17stack_local_entry ((*x).stack_locals);
      gt_pch_n_S ((*x).some_ld_name);
    }
}

void
gt_pch_nx_gimple_seq_node_d (void *x_p)
{
  struct gimple_seq_node_d * x = (struct gimple_seq_node_d *)x_p;
  struct gimple_seq_node_d * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_17gimple_seq_node_d, gt_ggc_e_17gimple_seq_node_d))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct gimple_seq_node_d * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_17gimple_seq_node_d, gt_ggc_e_17gimple_seq_node_d);
      }
  while (x != xlimit)
    {
      gt_pch_n_18gimple_statement_d ((*x).stmt);
      gt_pch_n_17gimple_seq_node_d ((*x).prev);
      gt_pch_n_17gimple_seq_node_d ((*x).next);
      x = ((*x).next);
    }
}

void
gt_pch_nx_gimple_seq_d (void *x_p)
{
  struct gimple_seq_d * x = (struct gimple_seq_d *)x_p;
  struct gimple_seq_d * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_12gimple_seq_d, gt_ggc_e_12gimple_seq_d))
   xlimit = ((*xlimit).next_free);
  while (x != xlimit)
    {
      gt_pch_n_17gimple_seq_node_d ((*x).first);
      gt_pch_n_17gimple_seq_node_d ((*x).last);
      gt_pch_n_12gimple_seq_d ((*x).next_free);
      x = ((*x).next_free);
    }
}

void
gt_pch_nx_section (void *x_p)
{
  union section * const x = (union section *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_7section, gt_ggc_e_7section))
    {
      switch (SECTION_STYLE (&(((*x)))))
        {
        case SECTION_NAMED:
          gt_pch_n_S ((*x).named.name);
          gt_pch_n_9tree_node ((*x).named.decl);
          break;
        case SECTION_UNNAMED:
          gt_pch_n_7section ((*x).unnamed.next);
          break;
        case SECTION_NOSWITCH:
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_gimple_statement_d (void *x_p)
{
  union gimple_statement_d * const x = (union gimple_statement_d *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18gimple_statement_d, gt_ggc_e_18gimple_statement_d))
    {
      switch (gimple_statement_structure (&((*x))))
        {
        case GSS_BASE:
          gt_pch_n_15basic_block_def ((*x).gsbase.bb);
          gt_pch_n_9tree_node ((*x).gsbase.block);
          break;
        case GSS_WITH_OPS:
          gt_pch_n_15basic_block_def ((*x).gsops.opbase.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gsops.opbase.gsbase.block);
          {
            size_t i0;
            size_t l0 = (size_t)(((*x).gsops).opbase.gsbase.num_ops);
            for (i0 = 0; i0 != l0; i0++) {
              gt_pch_n_9tree_node ((*x).gsops.op[i0]);
            }
          }
          break;
        case GSS_WITH_MEM_OPS:
          gt_pch_n_15basic_block_def ((*x).gsmem.membase.opbase.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gsmem.membase.opbase.gsbase.block);
          {
            size_t i1;
            size_t l1 = (size_t)(((*x).gsmem).membase.opbase.gsbase.num_ops);
            for (i1 = 0; i1 != l1; i1++) {
              gt_pch_n_9tree_node ((*x).gsmem.op[i1]);
            }
          }
          break;
        case GSS_OMP:
          gt_pch_n_15basic_block_def ((*x).omp.gsbase.bb);
          gt_pch_n_9tree_node ((*x).omp.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).omp.body);
          break;
        case GSS_BIND:
          gt_pch_n_15basic_block_def ((*x).gimple_bind.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_bind.gsbase.block);
          gt_pch_n_9tree_node ((*x).gimple_bind.vars);
          gt_pch_n_9tree_node ((*x).gimple_bind.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_bind.body);
          break;
        case GSS_CATCH:
          gt_pch_n_15basic_block_def ((*x).gimple_catch.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_catch.gsbase.block);
          gt_pch_n_9tree_node ((*x).gimple_catch.types);
          gt_pch_n_12gimple_seq_d ((*x).gimple_catch.handler);
          break;
        case GSS_EH_FILTER:
          gt_pch_n_15basic_block_def ((*x).gimple_eh_filter.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_eh_filter.gsbase.block);
          gt_pch_n_9tree_node ((*x).gimple_eh_filter.types);
          gt_pch_n_12gimple_seq_d ((*x).gimple_eh_filter.failure);
          break;
        case GSS_PHI:
          gt_pch_n_15basic_block_def ((*x).gimple_phi.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_phi.gsbase.block);
          gt_pch_n_9tree_node ((*x).gimple_phi.result);
          {
            size_t i2;
            size_t l2 = (size_t)(((*x).gimple_phi).nargs);
            for (i2 = 0; i2 != l2; i2++) {
              gt_pch_n_9tree_node ((*x).gimple_phi.args[i2].def);
            }
          }
          break;
        case GSS_RESX:
          gt_pch_n_15basic_block_def ((*x).gimple_resx.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_resx.gsbase.block);
          break;
        case GSS_TRY:
          gt_pch_n_15basic_block_def ((*x).gimple_try.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_try.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_try.eval);
          gt_pch_n_12gimple_seq_d ((*x).gimple_try.cleanup);
          break;
        case GSS_WCE:
          gt_pch_n_15basic_block_def ((*x).gimple_wce.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_wce.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_wce.cleanup);
          break;
        case GSS_ASM:
          gt_pch_n_15basic_block_def ((*x).gimple_asm.membase.opbase.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_asm.membase.opbase.gsbase.block);
          gt_pch_n_S ((*x).gimple_asm.string);
          {
            size_t i3;
            size_t l3 = (size_t)(((*x).gimple_asm).membase.opbase.gsbase.num_ops);
            for (i3 = 0; i3 != l3; i3++) {
              gt_pch_n_9tree_node ((*x).gimple_asm.op[i3]);
            }
          }
          break;
        case GSS_OMP_CRITICAL:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_critical.omp.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_critical.omp.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_omp_critical.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_critical.name);
          break;
        case GSS_OMP_FOR:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_for.omp.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_for.omp.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_omp_for.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_for.clauses);
          if ((*x).gimple_omp_for.iter != NULL) {
            size_t i4;
            for (i4 = 0; i4 != (size_t)(((*x).gimple_omp_for).collapse); i4++) {
              gt_pch_n_9tree_node ((*x).gimple_omp_for.iter[i4].index);
              gt_pch_n_9tree_node ((*x).gimple_omp_for.iter[i4].initial);
              gt_pch_n_9tree_node ((*x).gimple_omp_for.iter[i4].final);
              gt_pch_n_9tree_node ((*x).gimple_omp_for.iter[i4].incr);
            }
            gt_pch_note_object ((*x).gimple_omp_for.iter, x, gt_pch_p_18gimple_statement_d, gt_types_enum_last);
          }
          gt_pch_n_12gimple_seq_d ((*x).gimple_omp_for.pre_body);
          break;
        case GSS_OMP_PARALLEL:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_parallel.omp.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_parallel.omp.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_omp_parallel.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_parallel.clauses);
          gt_pch_n_9tree_node ((*x).gimple_omp_parallel.child_fn);
          gt_pch_n_9tree_node ((*x).gimple_omp_parallel.data_arg);
          break;
        case GSS_OMP_TASK:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_task.par.omp.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.par.omp.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_omp_task.par.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.par.clauses);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.par.child_fn);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.par.data_arg);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.copy_fn);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.arg_size);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.arg_align);
          break;
        case GSS_OMP_SECTIONS:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_sections.omp.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_sections.omp.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_omp_sections.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_sections.clauses);
          gt_pch_n_9tree_node ((*x).gimple_omp_sections.control);
          break;
        case GSS_OMP_SINGLE:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_single.omp.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_single.omp.gsbase.block);
          gt_pch_n_12gimple_seq_d ((*x).gimple_omp_single.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_single.clauses);
          break;
        case GSS_OMP_CONTINUE:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_continue.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_continue.gsbase.block);
          gt_pch_n_9tree_node ((*x).gimple_omp_continue.control_def);
          gt_pch_n_9tree_node ((*x).gimple_omp_continue.control_use);
          break;
        case GSS_OMP_ATOMIC_LOAD:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_atomic_load.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_atomic_load.gsbase.block);
          gt_pch_n_9tree_node ((*x).gimple_omp_atomic_load.rhs);
          gt_pch_n_9tree_node ((*x).gimple_omp_atomic_load.lhs);
          break;
        case GSS_OMP_ATOMIC_STORE:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_atomic_store.gsbase.bb);
          gt_pch_n_9tree_node ((*x).gimple_omp_atomic_store.gsbase.block);
          gt_pch_n_9tree_node ((*x).gimple_omp_atomic_store.val);
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_rtvec_def (void *x_p)
{
  struct rtvec_def * const x = (struct rtvec_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9rtvec_def, gt_ggc_e_9rtvec_def))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x)).num_elem);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_7rtx_def ((*x).elem[i0]);
        }
      }
    }
}

void
gt_pch_nx_rtx_def (void *x_p)
{
  struct rtx_def * x = (struct rtx_def *)x_p;
  struct rtx_def * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_7rtx_def, gt_ggc_e_7rtx_def))
   xlimit = (RTX_NEXT (&(*xlimit)));
  if (x != xlimit)
    for (;;)
      {
        struct rtx_def * const xprev = (RTX_PREV (&(*x)));
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_7rtx_def, gt_ggc_e_7rtx_def);
      }
  while (x != xlimit)
    {
      switch (GET_CODE (&(*x)))
        {
        case VAR_LOCATION:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case US_TRUNCATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_TRUNCATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_MINUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_ASHIFT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_ASHIFT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_ABS:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_NEG:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_NEG:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_MINUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_PLUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_PLUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_DUPLICATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_CONCAT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_SELECT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_MERGE:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LO_SUM:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case HIGH:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ZERO_EXTRACT:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SIGN_EXTRACT:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PARITY:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POPCOUNT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CTZ:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLZ:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FFS:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case BSWAP:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SQRT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ABS:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_SAT_FRACT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SAT_FRACT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FRACT_CONVERT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FRACT_CONVERT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FIX:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FLOAT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FIX:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT_TRUNCATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT_EXTEND:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case TRUNCATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ZERO_EXTEND:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SIGN_EXTEND:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LTGT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNLT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNLE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNGT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNGE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNEQ:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ORDERED:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNORDERED:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LTU:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LEU:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GTU:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GEU:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EQ:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_MODIFY:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_MODIFY:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_INC:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_DEC:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_INC:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_DEC:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMAX:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMIN:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SMAX:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SMIN:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ROTATERT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LSHIFTRT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ASHIFTRT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ROTATE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ASHIFT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NOT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case XOR:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case IOR:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case AND:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMOD:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UDIV:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MOD:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_DIV:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_DIV:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case DIV:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_MULT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_MULT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MULT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NEG:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MINUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PLUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case COMPARE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case IF_THEN_ELSE:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CC0:
          break;
        case SYMBOL_REF:
          switch (SYMBOL_REF_HAS_BLOCK_INFO_P (&(*x)))
            {
            case 1:
              gt_pch_n_12object_block ((*x).u.block_sym.block);
              break;
            default:
              break;
            }
          switch (CONSTANT_POOL_ADDRESS_P (&(*x)))
            {
            case 1:
              gt_pch_n_23constant_descriptor_rtx ((*x).u.fld[2].rt_constant);
              break;
            default:
              gt_pch_n_9tree_node ((*x).u.fld[2].rt_tree);
              break;
            }
          gt_pch_n_S ((*x).u.fld[0].rt_str);
          break;
        case LABEL_REF:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MEM:
          gt_pch_n_9mem_attrs ((*x).u.fld[1].rt_mem);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CONCATN:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case CONCAT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case STRICT_LOW_PART:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SUBREG:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SCRATCH:
          break;
        case REG:
          gt_pch_n_9reg_attrs ((*x).u.fld[2].rt_reg);
          break;
        case VALUE:
          break;
        case PC:
          break;
        case CONST:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CONST_STRING:
          gt_pch_n_S ((*x).u.fld[0].rt_str);
          break;
        case CONST_VECTOR:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case CONST_DOUBLE:
          break;
        case CONST_FIXED:
          break;
        case CONST_INT:
          break;
        case RESX:
          break;
        case TRAP_IF:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case RETURN:
          break;
        case CALL:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLOBBER:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case USE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SET:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PREFETCH:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ADDR_DIFF_VEC:
          gt_pch_n_7rtx_def ((*x).u.fld[3].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_9rtvec_def ((*x).u.fld[1].rt_rtvec);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ADDR_VEC:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case UNSPEC_VOLATILE:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case UNSPEC:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case ASM_OPERANDS:
          gt_pch_n_9rtvec_def ((*x).u.fld[4].rt_rtvec);
          gt_pch_n_9rtvec_def ((*x).u.fld[3].rt_rtvec);
          gt_pch_n_S ((*x).u.fld[1].rt_str);
          gt_pch_n_S ((*x).u.fld[0].rt_str);
          break;
        case ASM_INPUT:
          gt_pch_n_S ((*x).u.fld[0].rt_str);
          break;
        case PARALLEL:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case COND_EXEC:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NOTE:
          switch (NOTE_KIND (&(*x)))
            {
            default:
              gt_pch_n_S ((*x).u.fld[4].rt_str);
              break;
            case NOTE_INSN_SWITCH_TEXT_SECTIONS:
              break;
            case NOTE_INSN_BASIC_BLOCK:
              break;
            case NOTE_INSN_VAR_LOCATION:
              gt_pch_n_7rtx_def ((*x).u.fld[4].rt_rtx);
              break;
            case NOTE_INSN_EH_REGION_END:
              break;
            case NOTE_INSN_EH_REGION_BEG:
              break;
            case NOTE_INSN_EPILOGUE_BEG:
              break;
            case NOTE_INSN_PROLOGUE_END:
              break;
            case NOTE_INSN_FUNCTION_BEG:
              break;
            case NOTE_INSN_BLOCK_END:
              gt_pch_n_9tree_node ((*x).u.fld[4].rt_tree);
              break;
            case NOTE_INSN_BLOCK_BEG:
              gt_pch_n_9tree_node ((*x).u.fld[4].rt_tree);
              break;
            case NOTE_INSN_DELETED_LABEL:
              break;
            case NOTE_INSN_DELETED:
              break;
            }
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case CODE_LABEL:
          gt_pch_n_S ((*x).u.fld[7].rt_str);
          gt_pch_n_7rtx_def ((*x).u.fld[5].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case BARRIER:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case CALL_INSN:
          gt_pch_n_7rtx_def ((*x).u.fld[8].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[5].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case JUMP_INSN:
          gt_pch_n_7rtx_def ((*x).u.fld[8].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[5].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case INSN:
          gt_pch_n_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[5].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case ADDRESS:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SEQUENCE:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case INSN_LIST:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EXPR_LIST:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNKNOWN:
          break;
        default:
          break;
        }
      x = (RTX_NEXT (&(*x)));
    }
}

void
gt_pch_nx_bitmap_head_def (void *x_p)
{
  struct bitmap_head_def * const x = (struct bitmap_head_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15bitmap_head_def, gt_ggc_e_15bitmap_head_def))
    {
      gt_pch_n_18bitmap_element_def ((*x).first);
      gt_pch_n_18bitmap_element_def ((*x).current);
      gt_pch_n_14bitmap_obstack ((*x).obstack);
    }
}

void
gt_pch_nx_answer (void *x_p)
{
  struct answer * const x = (struct answer *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_6answer, gt_ggc_e_6answer))
    {
      gt_pch_n_6answer ((*x).next);
      {
        size_t i0;
        size_t l0 = (size_t)(((*x)).count);
        for (i0 = 0; i0 != l0; i0++) {
          switch (cpp_token_val_index (&((*x).first[i0])))
            {
            case CPP_TOKEN_FLD_NODE:
              {
                union tree_node * const x1 =
                  ((*x).first[i0].val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).first[i0].val.node))) : NULL;
                gt_pch_n_9tree_node (x1);
              }
              break;
            case CPP_TOKEN_FLD_SOURCE:
              gt_pch_n_9cpp_token ((*x).first[i0].val.source);
              break;
            case CPP_TOKEN_FLD_STR:
              gt_pch_n_S ((*x).first[i0].val.str.text);
              break;
            case CPP_TOKEN_FLD_ARG_NO:
              break;
            case CPP_TOKEN_FLD_PRAGMA:
              break;
            default:
              break;
            }
        }
      }
    }
}

void
gt_pch_nx_cpp_macro (void *x_p)
{
  struct cpp_macro * const x = (struct cpp_macro *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9cpp_macro, gt_ggc_e_9cpp_macro))
    {
      if ((*x).params != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).paramc); i0++) {
          {
            union tree_node * const x1 =
              ((*x).params[i0]) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).params[i0]))) : NULL;
            gt_pch_n_9tree_node (x1);
          }
        }
        gt_pch_note_object ((*x).params, x, gt_pch_p_9cpp_macro, gt_types_enum_last);
      }
      switch (((*x)).traditional)
        {
        case 0:
          if ((*x).exp.tokens != NULL) {
            size_t i2;
            for (i2 = 0; i2 != (size_t)((*x).count); i2++) {
              switch (cpp_token_val_index (&((*x).exp.tokens[i2])))
                {
                case CPP_TOKEN_FLD_NODE:
                  {
                    union tree_node * const x3 =
                      ((*x).exp.tokens[i2].val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).exp.tokens[i2].val.node))) : NULL;
                    gt_pch_n_9tree_node (x3);
                  }
                  break;
                case CPP_TOKEN_FLD_SOURCE:
                  gt_pch_n_9cpp_token ((*x).exp.tokens[i2].val.source);
                  break;
                case CPP_TOKEN_FLD_STR:
                  gt_pch_n_S ((*x).exp.tokens[i2].val.str.text);
                  break;
                case CPP_TOKEN_FLD_ARG_NO:
                  break;
                case CPP_TOKEN_FLD_PRAGMA:
                  break;
                default:
                  break;
                }
            }
            gt_pch_note_object ((*x).exp.tokens, x, gt_pch_p_9cpp_macro, gt_types_enum_last);
          }
          break;
        case 1:
          gt_pch_n_S ((*x).exp.text);
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_cpp_token (void *x_p)
{
  struct cpp_token * const x = (struct cpp_token *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9cpp_token, gt_ggc_e_9cpp_token))
    {
      switch (cpp_token_val_index (&((*x))))
        {
        case CPP_TOKEN_FLD_NODE:
          {
            union tree_node * const x0 =
              ((*x).val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).val.node))) : NULL;
            gt_pch_n_9tree_node (x0);
          }
          break;
        case CPP_TOKEN_FLD_SOURCE:
          gt_pch_n_9cpp_token ((*x).val.source);
          break;
        case CPP_TOKEN_FLD_STR:
          gt_pch_n_S ((*x).val.str.text);
          break;
        case CPP_TOKEN_FLD_ARG_NO:
          break;
        case CPP_TOKEN_FLD_PRAGMA:
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_line_maps (void *x_p)
{
  struct line_maps * const x = (struct line_maps *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9line_maps, gt_ggc_e_9line_maps))
    {
      if ((*x).maps != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).used); i0++) {
          gt_pch_n_S ((*x).maps[i0].to_file);
        }
        gt_pch_note_object ((*x).maps, x, gt_pch_p_9line_maps, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_II17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_II17splay_tree_node_s, gt_types_enum_last))
    {
      gt_pch_n_II17splay_tree_node_s ((*x).left);
      gt_pch_n_II17splay_tree_node_s ((*x).right);
    }
}

void
gt_pch_n_SP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_SP9tree_node17splay_tree_node_s, gt_types_enum_last))
    {
      gt_pch_n_S ((void *)(*x).key);
      gt_pch_n_9tree_node ((void *)(*x).value);
      gt_pch_n_SP9tree_node17splay_tree_node_s ((*x).left);
      gt_pch_n_SP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_pch_n_P9tree_nodeP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9tree_nodeP9tree_node17splay_tree_node_s, gt_types_enum_last))
    {
      gt_pch_n_9tree_node ((void *)(*x).key);
      gt_pch_n_9tree_node ((void *)(*x).value);
      gt_pch_n_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).left);
      gt_pch_n_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_pch_n_IP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_IP9tree_node17splay_tree_node_s, gt_types_enum_last))
    {
      gt_pch_n_9tree_node ((void *)(*x).value);
      gt_pch_n_IP9tree_node17splay_tree_node_s ((*x).left);
      gt_pch_n_IP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_pch_n_P12tree_int_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P12tree_int_map4htab, gt_e_P12tree_int_map4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_12tree_int_map ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P12tree_int_map4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_IP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_IP9tree_node12splay_tree_s, gt_types_enum_last))
    {
      gt_pch_n_IP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_pch_n_P9tree_nodeP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9tree_nodeP9tree_node12splay_tree_s, gt_types_enum_last))
    {
      gt_pch_n_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_pch_n_P12varpool_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P12varpool_node4htab, gt_e_P12varpool_node4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_12varpool_node ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P12varpool_node4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P12object_block4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P12object_block4htab, gt_e_P12object_block4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_12object_block ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P12object_block4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P7section4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P7section4htab, gt_e_P7section4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_7section ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P7section4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P17tree_priority_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P17tree_priority_map4htab, gt_e_P17tree_priority_map4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_17tree_priority_map ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P17tree_priority_map4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P8tree_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P8tree_map4htab, gt_e_P8tree_map4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_8tree_map ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P8tree_map4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P15throw_stmt_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P15throw_stmt_node4htab, gt_e_P15throw_stmt_node4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_15throw_stmt_node ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P15throw_stmt_node4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P9reg_attrs4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9reg_attrs4htab, gt_e_P9reg_attrs4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_9reg_attrs ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P9reg_attrs4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P9mem_attrs4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9mem_attrs4htab, gt_e_P9mem_attrs4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_9mem_attrs ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P9mem_attrs4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P7rtx_def4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P7rtx_def4htab, gt_e_P7rtx_def4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_7rtx_def ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P7rtx_def4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_SP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_SP9tree_node12splay_tree_s, gt_types_enum_last))
    {
      gt_pch_n_SP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_pch_n_P11cgraph_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P11cgraph_node4htab, gt_e_P11cgraph_node4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_11cgraph_node ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P11cgraph_node4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_II12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_II12splay_tree_s, gt_types_enum_last))
    {
      gt_pch_n_II17splay_tree_node_s ((*x).root);
    }
}

void
gt_pch_n_P11cgraph_edge4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P11cgraph_edge4htab, gt_e_P11cgraph_edge4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_11cgraph_edge ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P11cgraph_edge4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P9loop_exit4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9loop_exit4htab, gt_e_P9loop_exit4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_9loop_exit ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P9loop_exit4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P24types_used_by_vars_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P24types_used_by_vars_entry4htab, gt_e_P24types_used_by_vars_entry4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_24types_used_by_vars_entry ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P24types_used_by_vars_entry4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P9tree_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9tree_node4htab, gt_e_P9tree_node4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_9tree_node ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P9tree_node4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_20ssa_operand_memory_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct ssa_operand_memory_d * const x ATTRIBUTE_UNUSED = (struct ssa_operand_memory_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_13VEC_gimple_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_gimple_gc * const x ATTRIBUTE_UNUSED = (struct VEC_gimple_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0]), cookie);
    }
  }
}

void
gt_pch_p_15throw_stmt_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct throw_stmt_node * const x ATTRIBUTE_UNUSED = (struct throw_stmt_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).stmt), cookie);
}

void
gt_pch_p_15cgraph_asm_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cgraph_asm_node * const x ATTRIBUTE_UNUSED = (struct cgraph_asm_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).asm_str), cookie);
}

void
gt_pch_p_12varpool_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct varpool_node * const x ATTRIBUTE_UNUSED = (struct varpool_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_needed), cookie);
}

void
gt_pch_p_11cgraph_edge (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cgraph_edge * const x ATTRIBUTE_UNUSED = (struct cgraph_edge *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).caller), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).callee), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_caller), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_caller), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_callee), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_callee), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).call_stmt), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).inline_failed), cookie);
}

void
gt_pch_p_11cgraph_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cgraph_node * const x ATTRIBUTE_UNUSED = (struct cgraph_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).callees), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).callers), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).previous), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).origin), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).nested), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_nested), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_needed), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_clone), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_clone), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).master_clone), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).call_site_hash), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).global.inlined_to), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).inline_decl), cookie);
}

void
gt_pch_p_18VEC_basic_block_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_basic_block_gc * const x ATTRIBUTE_UNUSED = (struct VEC_basic_block_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0]), cookie);
    }
  }
}

void
gt_pch_p_14gimple_bb_info (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct gimple_bb_info * const x ATTRIBUTE_UNUSED = (struct gimple_bb_info *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).seq), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).phi_nodes), cookie);
}

void
gt_pch_p_11rtl_bb_info (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct rtl_bb_info * const x ATTRIBUTE_UNUSED = (struct rtl_bb_info *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).head_), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).end_), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).header), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).footer), cookie);
}

void
gt_pch_p_11VEC_edge_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_edge_gc * const x ATTRIBUTE_UNUSED = (struct VEC_edge_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0]), cookie);
    }
  }
}

void
gt_pch_p_17cselib_val_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cselib_val_struct * const x ATTRIBUTE_UNUSED = (struct cselib_val_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).val_rtx), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).locs), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).addr_list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_containing_mem), cookie);
}

void
gt_pch_p_12elt_loc_list (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct elt_loc_list * const x ATTRIBUTE_UNUSED = (struct elt_loc_list *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).loc), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).setting_insn), cookie);
}

void
gt_pch_p_13VEC_loop_p_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_loop_p_gc * const x ATTRIBUTE_UNUSED = (struct VEC_loop_p_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0]), cookie);
    }
  }
}

void
gt_pch_p_4loop (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct loop * const x ATTRIBUTE_UNUSED = (struct loop *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).header), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).latch), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).superloops), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).inner), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).nb_iterations), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).bounds), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).exits), cookie);
}

void
gt_pch_p_9loop_exit (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct loop_exit * const x ATTRIBUTE_UNUSED = (struct loop_exit *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).e), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_e), cookie);
}

void
gt_pch_p_13nb_iter_bound (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct nb_iter_bound * const x ATTRIBUTE_UNUSED = (struct nb_iter_bound *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).stmt), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_24types_used_by_vars_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct types_used_by_vars_entry * const x ATTRIBUTE_UNUSED = (struct types_used_by_vars_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).type), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).var_decl), cookie);
}

void
gt_pch_p_5loops (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct loops * const x ATTRIBUTE_UNUSED = (struct loops *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).larray), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).exits), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).tree_root), cookie);
}

void
gt_pch_p_18control_flow_graph (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct control_flow_graph * const x ATTRIBUTE_UNUSED = (struct control_flow_graph *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).x_entry_block_ptr), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_exit_block_ptr), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_basic_block_info), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_label_to_block_map), cookie);
}

void
gt_pch_p_18VEC_temp_slot_p_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_temp_slot_p_gc * const x ATTRIBUTE_UNUSED = (struct VEC_temp_slot_p_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0]), cookie);
    }
  }
}

void
gt_pch_p_9gimple_df (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct gimple_df * const x ATTRIBUTE_UNUSED = (struct gimple_df *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).referenced_vars), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).modified_noreturn_calls), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).ssa_names), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).global_var), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).nonlocal_all), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).call_clobbered_vars), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).call_used_vars), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).addressable_vars), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).free_ssanames), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).default_defs), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).ssa_operands.operand_memory), cookie);
}

void
gt_pch_p_23VEC_call_site_record_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_call_site_record_gc * const x ATTRIBUTE_UNUSED = (struct VEC_call_site_record_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0]), cookie);
    }
  }
}

void
gt_pch_p_14sequence_stack (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct sequence_stack * const x ATTRIBUTE_UNUSED = (struct sequence_stack *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).first), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).last), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_8edge_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct edge_def * const x ATTRIBUTE_UNUSED = (struct edge_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).src), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dest), cookie);
  switch (current_ir_type () == IR_GIMPLE)
    {
    case true:
      if ((void *)(x) == this_obj)
        op (&((*x).insns.g), cookie);
      break;
    case false:
      if ((void *)(x) == this_obj)
        op (&((*x).insns.r), cookie);
      break;
    default:
      break;
    }
  if ((void *)(x) == this_obj)
    op (&((*x).goto_block), cookie);
}

void
gt_pch_p_8elt_list (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct elt_list * const x ATTRIBUTE_UNUSED = (struct elt_list *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).elt), cookie);
}

void
gt_pch_p_17tree_priority_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_priority_map * const x ATTRIBUTE_UNUSED = (struct tree_priority_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.from), cookie);
}

void
gt_pch_p_12tree_int_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_int_map * const x ATTRIBUTE_UNUSED = (struct tree_int_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.from), cookie);
}

void
gt_pch_p_8tree_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_map * const x ATTRIBUTE_UNUSED = (struct tree_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.from), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).to), cookie);
}

void
gt_pch_p_24tree_statement_list_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_statement_list_node * const x ATTRIBUTE_UNUSED = (struct tree_statement_list_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).stmt), cookie);
}

void
gt_pch_p_15varray_head_tag (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct varray_head_tag * const x ATTRIBUTE_UNUSED = (struct varray_head_tag *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).name), cookie);
  switch ((*x).type)
    {
    case VARRAY_DATA_C:
      break;
    case VARRAY_DATA_UC:
      break;
    case VARRAY_DATA_S:
      break;
    case VARRAY_DATA_US:
      break;
    case VARRAY_DATA_I:
      break;
    case VARRAY_DATA_U:
      break;
    case VARRAY_DATA_L:
      break;
    case VARRAY_DATA_UL:
      break;
    case VARRAY_DATA_HINT:
      break;
    case VARRAY_DATA_UHINT:
      break;
    case VARRAY_DATA_GENERIC:
      gcc_unreachable ();
      break;
    case VARRAY_DATA_CPTR:
      {
        size_t i10;
        size_t l10 = (size_t)((*x).num_elements);
        for (i10 = 0; i10 != l10; i10++) {
          if ((void *)(x) == this_obj)
            op (&((*x).data.vdt_cptr[i10]), cookie);
        }
      }
      break;
    case VARRAY_DATA_RTX:
      {
        size_t i11;
        size_t l11 = (size_t)((*x).num_elements);
        for (i11 = 0; i11 != l11; i11++) {
          if ((void *)(x) == this_obj)
            op (&((*x).data.vdt_rtx[i11]), cookie);
        }
      }
      break;
    case VARRAY_DATA_RTVEC:
      {
        size_t i12;
        size_t l12 = (size_t)((*x).num_elements);
        for (i12 = 0; i12 != l12; i12++) {
          if ((void *)(x) == this_obj)
            op (&((*x).data.vdt_rtvec[i12]), cookie);
        }
      }
      break;
    case VARRAY_DATA_TREE:
      {
        size_t i13;
        size_t l13 = (size_t)((*x).num_elements);
        for (i13 = 0; i13 != l13; i13++) {
          if ((void *)(x) == this_obj)
            op (&((*x).data.vdt_tree[i13]), cookie);
        }
      }
      break;
    case VARRAY_DATA_BITMAP:
      {
        size_t i14;
        size_t l14 = (size_t)((*x).num_elements);
        for (i14 = 0; i14 != l14; i14++) {
          if ((void *)(x) == this_obj)
            op (&((*x).data.vdt_bitmap[i14]), cookie);
        }
      }
      break;
    case VARRAY_DATA_TE:
      {
        size_t i15;
        size_t l15 = (size_t)((*x).num_elements);
        for (i15 = 0; i15 != l15; i15++) {
          if ((void *)(x) == this_obj)
            op (&((*x).data.vdt_te[i15]), cookie);
        }
      }
      break;
    case VARRAY_DATA_EDGE:
      {
        size_t i16;
        size_t l16 = (size_t)((*x).num_elements);
        for (i16 = 0; i16 != l16; i16++) {
          if ((void *)(x) == this_obj)
            op (&((*x).data.vdt_e[i16]), cookie);
        }
      }
      break;
    default:
      break;
    }
}

void
gt_pch_p_12ptr_info_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct ptr_info_def * const x ATTRIBUTE_UNUSED = (struct ptr_info_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).pt_vars), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).name_mem_tag), cookie);
}

void
gt_pch_p_22VEC_constructor_elt_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_constructor_elt_gc * const x ATTRIBUTE_UNUSED = (struct VEC_constructor_elt_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].index), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].value), cookie);
    }
  }
}

void
gt_pch_p_10tree_ann_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  union tree_ann_d * const x ATTRIBUTE_UNUSED = (union tree_ann_d *)x_p;
  switch (ann_type ((tree_ann_t)&((*x))))
    {
    case TREE_ANN_COMMON:
      if ((void *)(x) == this_obj)
        op (&((*x).common.stmt), cookie);
      break;
    case VAR_ANN:
      if ((void *)(x) == this_obj)
        op (&((*x).vdecl.common.stmt), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).vdecl.mpt), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).vdecl.symbol_mem_tag), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).vdecl.current_def), cookie);
      break;
    case FUNCTION_ANN:
      if ((void *)(x) == this_obj)
        op (&((*x).fdecl.common.stmt), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_11VEC_tree_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_tree_gc * const x ATTRIBUTE_UNUSED = (struct VEC_tree_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0]), cookie);
    }
  }
}

void
gt_pch_p_8function (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct function * const x ATTRIBUTE_UNUSED = (struct function *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).eh), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).cfg), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).gimple_body), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).gimple_df), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_current_loops), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).static_chain_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).nonlocal_goto_save_area), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).local_decls), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).machine), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).language), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).used_types_hash), cookie);
}

void
gt_pch_p_15basic_block_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct basic_block_def * const x ATTRIBUTE_UNUSED = (struct basic_block_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).preds), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).succs), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).loop_father), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_bb), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_bb), cookie);
  switch (((((*x)).flags & BB_RTL) != 0))
    {
    case 0:
      if ((void *)(x) == this_obj)
        op (&((*x).il.gimple), cookie);
      break;
    case 1:
      if ((void *)(x) == this_obj)
        op (&((*x).il.rtl), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_11fixed_value (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct fixed_value * const x ATTRIBUTE_UNUSED = (struct fixed_value *)x_p;
}

void
gt_pch_p_10real_value (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct real_value * const x ATTRIBUTE_UNUSED = (struct real_value *)x_p;
}

void
gt_pch_p_10VEC_rtx_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_rtx_gc * const x ATTRIBUTE_UNUSED = (struct VEC_rtx_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0]), cookie);
    }
  }
}

void
gt_pch_p_12object_block (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct object_block * const x ATTRIBUTE_UNUSED = (struct object_block *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).sect), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).objects), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).anchors), cookie);
}

void
gt_pch_p_9reg_attrs (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct reg_attrs * const x ATTRIBUTE_UNUSED = (struct reg_attrs *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
}

void
gt_pch_p_9mem_attrs (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct mem_attrs * const x ATTRIBUTE_UNUSED = (struct mem_attrs *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).expr), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).offset), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).size), cookie);
}

void
gt_pch_p_14bitmap_obstack (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct bitmap_obstack * const x ATTRIBUTE_UNUSED = (struct bitmap_obstack *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).elements), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).heads), cookie);
}

void
gt_pch_p_18bitmap_element_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct bitmap_element_def * const x ATTRIBUTE_UNUSED = (struct bitmap_element_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
}

void
gt_pch_p_16machine_function (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct machine_function * const x ATTRIBUTE_UNUSED = (struct machine_function *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).stack_locals), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).some_ld_name), cookie);
}

void
gt_pch_p_17gimple_seq_node_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct gimple_seq_node_d * const x ATTRIBUTE_UNUSED = (struct gimple_seq_node_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).stmt), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_12gimple_seq_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct gimple_seq_d * const x ATTRIBUTE_UNUSED = (struct gimple_seq_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).first), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).last), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_free), cookie);
}

void
gt_pch_p_7section (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  union section * const x ATTRIBUTE_UNUSED = (union section *)x_p;
  switch (SECTION_STYLE (&(((*x)))))
    {
    case SECTION_NAMED:
      if ((void *)(x) == this_obj)
        op (&((*x).named.name), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).named.decl), cookie);
      break;
    case SECTION_UNNAMED:
      if ((void *)(x) == this_obj)
        op (&((*x).unnamed.next), cookie);
      break;
    case SECTION_NOSWITCH:
      break;
    default:
      break;
    }
}

void
gt_pch_p_18gimple_statement_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  union gimple_statement_d * const x ATTRIBUTE_UNUSED = (union gimple_statement_d *)x_p;
  switch (gimple_statement_structure (&((*x))))
    {
    case GSS_BASE:
      if ((void *)(x) == this_obj)
        op (&((*x).gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gsbase.block), cookie);
      break;
    case GSS_WITH_OPS:
      if ((void *)(x) == this_obj)
        op (&((*x).gsops.opbase.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gsops.opbase.gsbase.block), cookie);
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).gsops).opbase.gsbase.num_ops);
        for (i0 = 0; i0 != l0; i0++) {
          if ((void *)(x) == this_obj)
            op (&((*x).gsops.op[i0]), cookie);
        }
      }
      break;
    case GSS_WITH_MEM_OPS:
      if ((void *)(x) == this_obj)
        op (&((*x).gsmem.membase.opbase.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gsmem.membase.opbase.gsbase.block), cookie);
      {
        size_t i1;
        size_t l1 = (size_t)(((*x).gsmem).membase.opbase.gsbase.num_ops);
        for (i1 = 0; i1 != l1; i1++) {
          if ((void *)(x) == this_obj)
            op (&((*x).gsmem.op[i1]), cookie);
        }
      }
      break;
    case GSS_OMP:
      if ((void *)(x) == this_obj)
        op (&((*x).omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).omp.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).omp.body), cookie);
      break;
    case GSS_BIND:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.vars), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.body), cookie);
      break;
    case GSS_CATCH:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_catch.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_catch.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_catch.types), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_catch.handler), cookie);
      break;
    case GSS_EH_FILTER:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_filter.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_filter.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_filter.types), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_filter.failure), cookie);
      break;
    case GSS_PHI:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_phi.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_phi.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_phi.result), cookie);
      {
        size_t i2;
        size_t l2 = (size_t)(((*x).gimple_phi).nargs);
        for (i2 = 0; i2 != l2; i2++) {
          if ((void *)(x) == this_obj)
            op (&((*x).gimple_phi.args[i2].def), cookie);
        }
      }
      break;
    case GSS_RESX:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_resx.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_resx.gsbase.block), cookie);
      break;
    case GSS_TRY:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_try.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_try.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_try.eval), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_try.cleanup), cookie);
      break;
    case GSS_WCE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_wce.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_wce.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_wce.cleanup), cookie);
      break;
    case GSS_ASM:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_asm.membase.opbase.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_asm.membase.opbase.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_asm.string), cookie);
      {
        size_t i3;
        size_t l3 = (size_t)(((*x).gimple_asm).membase.opbase.gsbase.num_ops);
        for (i3 = 0; i3 != l3; i3++) {
          if ((void *)(x) == this_obj)
            op (&((*x).gimple_asm.op[i3]), cookie);
        }
      }
      break;
    case GSS_OMP_CRITICAL:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_critical.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_critical.omp.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_critical.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_critical.name), cookie);
      break;
    case GSS_OMP_FOR:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_for.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_for.omp.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_for.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_for.clauses), cookie);
      if ((*x).gimple_omp_for.iter != NULL) {
        size_t i4;
        for (i4 = 0; i4 != (size_t)(((*x).gimple_omp_for).collapse); i4++) {
          if ((void *)((*x).gimple_omp_for.iter) == this_obj)
            op (&((*x).gimple_omp_for.iter[i4].index), cookie);
          if ((void *)((*x).gimple_omp_for.iter) == this_obj)
            op (&((*x).gimple_omp_for.iter[i4].initial), cookie);
          if ((void *)((*x).gimple_omp_for.iter) == this_obj)
            op (&((*x).gimple_omp_for.iter[i4].final), cookie);
          if ((void *)((*x).gimple_omp_for.iter) == this_obj)
            op (&((*x).gimple_omp_for.iter[i4].incr), cookie);
        }
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_omp_for.iter), cookie);
      }
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_for.pre_body), cookie);
      break;
    case GSS_OMP_PARALLEL:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.omp.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.clauses), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.child_fn), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.data_arg), cookie);
      break;
    case GSS_OMP_TASK:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.omp.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.clauses), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.child_fn), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.data_arg), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.copy_fn), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.arg_size), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.arg_align), cookie);
      break;
    case GSS_OMP_SECTIONS:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.omp.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.clauses), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.control), cookie);
      break;
    case GSS_OMP_SINGLE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_single.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_single.omp.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_single.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_single.clauses), cookie);
      break;
    case GSS_OMP_CONTINUE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_continue.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_continue.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_continue.control_def), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_continue.control_use), cookie);
      break;
    case GSS_OMP_ATOMIC_LOAD:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_load.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_load.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_load.rhs), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_load.lhs), cookie);
      break;
    case GSS_OMP_ATOMIC_STORE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_store.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_store.gsbase.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_store.val), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_9rtvec_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct rtvec_def * const x ATTRIBUTE_UNUSED = (struct rtvec_def *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x)).num_elem);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).elem[i0]), cookie);
    }
  }
}

void
gt_pch_p_7rtx_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct rtx_def * const x ATTRIBUTE_UNUSED = (struct rtx_def *)x_p;
  switch (GET_CODE (&(*x)))
    {
    case VAR_LOCATION:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_tree), cookie);
      break;
    case US_TRUNCATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_TRUNCATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_MINUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_ASHIFT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_ASHIFT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_ABS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_NEG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_NEG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_MINUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_PLUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_PLUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case VEC_DUPLICATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case VEC_CONCAT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case VEC_SELECT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case VEC_MERGE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LO_SUM:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case HIGH:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ZERO_EXTRACT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SIGN_EXTRACT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PARITY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case POPCOUNT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CTZ:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CLZ:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FFS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case BSWAP:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SQRT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ABS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNSIGNED_SAT_FRACT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SAT_FRACT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNSIGNED_FRACT_CONVERT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FRACT_CONVERT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNSIGNED_FIX:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNSIGNED_FLOAT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FIX:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FLOAT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FLOAT_TRUNCATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FLOAT_EXTEND:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case TRUNCATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ZERO_EXTEND:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SIGN_EXTEND:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LTGT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNLT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNLE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNGT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNGE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNEQ:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ORDERED:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNORDERED:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LTU:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LEU:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case GTU:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case GEU:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case GT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case GE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case EQ:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case NE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case POST_MODIFY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PRE_MODIFY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case POST_INC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case POST_DEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PRE_INC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PRE_DEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UMAX:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UMIN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SMAX:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SMIN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ROTATERT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LSHIFTRT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ASHIFTRT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ROTATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ASHIFT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case NOT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case XOR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case IOR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case AND:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UMOD:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UDIV:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case MOD:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_DIV:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_DIV:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case DIV:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_MULT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_MULT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case MULT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case NEG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case MINUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PLUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case COMPARE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case IF_THEN_ELSE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CC0:
      break;
    case SYMBOL_REF:
      switch (SYMBOL_REF_HAS_BLOCK_INFO_P (&(*x)))
        {
        case 1:
          if ((void *)(x) == this_obj)
            op (&((*x).u.block_sym.block), cookie);
          break;
        default:
          break;
        }
      switch (CONSTANT_POOL_ADDRESS_P (&(*x)))
        {
        case 1:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[2].rt_constant), cookie);
          break;
        default:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[2].rt_tree), cookie);
          break;
        }
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_str), cookie);
      break;
    case LABEL_REF:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case MEM:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_mem), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CONCATN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case CONCAT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case STRICT_LOW_PART:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SUBREG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SCRATCH:
      break;
    case REG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_reg), cookie);
      break;
    case VALUE:
      break;
    case PC:
      break;
    case CONST:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CONST_STRING:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_str), cookie);
      break;
    case CONST_VECTOR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case CONST_DOUBLE:
      break;
    case CONST_FIXED:
      break;
    case CONST_INT:
      break;
    case RESX:
      break;
    case TRAP_IF:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case RETURN:
      break;
    case CALL:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CLOBBER:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case USE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SET:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PREFETCH:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ADDR_DIFF_VEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtvec), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ADDR_VEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case UNSPEC_VOLATILE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case UNSPEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case ASM_OPERANDS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[4].rt_rtvec), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_rtvec), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_str), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_str), cookie);
      break;
    case ASM_INPUT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_str), cookie);
      break;
    case PARALLEL:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case COND_EXEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case NOTE:
      switch (NOTE_KIND (&(*x)))
        {
        default:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_str), cookie);
          break;
        case NOTE_INSN_SWITCH_TEXT_SECTIONS:
          break;
        case NOTE_INSN_BASIC_BLOCK:
          break;
        case NOTE_INSN_VAR_LOCATION:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_rtx), cookie);
          break;
        case NOTE_INSN_EH_REGION_END:
          break;
        case NOTE_INSN_EH_REGION_BEG:
          break;
        case NOTE_INSN_EPILOGUE_BEG:
          break;
        case NOTE_INSN_PROLOGUE_END:
          break;
        case NOTE_INSN_FUNCTION_BEG:
          break;
        case NOTE_INSN_BLOCK_END:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_tree), cookie);
          break;
        case NOTE_INSN_BLOCK_BEG:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_tree), cookie);
          break;
        case NOTE_INSN_DELETED_LABEL:
          break;
        case NOTE_INSN_DELETED:
          break;
        }
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case CODE_LABEL:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_str), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[5].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case BARRIER:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case CALL_INSN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[8].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[5].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case JUMP_INSN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[8].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[5].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case INSN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[5].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case ADDRESS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SEQUENCE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case INSN_LIST:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case EXPR_LIST:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNKNOWN:
      break;
    default:
      break;
    }
}

void
gt_pch_p_15bitmap_head_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct bitmap_head_def * const x ATTRIBUTE_UNUSED = (struct bitmap_head_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).first), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).current), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).obstack), cookie);
}

void
gt_pch_p_6answer (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct answer * const x ATTRIBUTE_UNUSED = (struct answer *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  {
    size_t i0;
    size_t l0 = (size_t)(((*x)).count);
    for (i0 = 0; i0 != l0; i0++) {
      switch (cpp_token_val_index (&((*x).first[i0])))
        {
        case CPP_TOKEN_FLD_NODE:
          {
            union tree_node * x1 =
              ((*x).first[i0].val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).first[i0].val.node))) : NULL;
            if ((void *)(x) == this_obj)
              op (&(x1), cookie);
            (*x).first[i0].val.node = (x1) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x1))) : NULL;
          }
          break;
        case CPP_TOKEN_FLD_SOURCE:
          if ((void *)(x) == this_obj)
            op (&((*x).first[i0].val.source), cookie);
          break;
        case CPP_TOKEN_FLD_STR:
          if ((void *)(x) == this_obj)
            op (&((*x).first[i0].val.str.text), cookie);
          break;
        case CPP_TOKEN_FLD_ARG_NO:
          break;
        case CPP_TOKEN_FLD_PRAGMA:
          break;
        default:
          break;
        }
    }
  }
}

void
gt_pch_p_9cpp_macro (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cpp_macro * const x ATTRIBUTE_UNUSED = (struct cpp_macro *)x_p;
  if ((*x).params != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).paramc); i0++) {
      {
        union tree_node * x1 =
          ((*x).params[i0]) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).params[i0]))) : NULL;
        if ((void *)((*x).params) == this_obj)
          op (&(x1), cookie);
        (*x).params[i0] = (x1) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x1))) : NULL;
      }
    }
    if ((void *)(x) == this_obj)
      op (&((*x).params), cookie);
  }
  switch (((*x)).traditional)
    {
    case 0:
      if ((*x).exp.tokens != NULL) {
        size_t i2;
        for (i2 = 0; i2 != (size_t)((*x).count); i2++) {
          switch (cpp_token_val_index (&((*x).exp.tokens[i2])))
            {
            case CPP_TOKEN_FLD_NODE:
              {
                union tree_node * x3 =
                  ((*x).exp.tokens[i2].val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).exp.tokens[i2].val.node))) : NULL;
                if ((void *)((*x).exp.tokens) == this_obj)
                  op (&(x3), cookie);
                (*x).exp.tokens[i2].val.node = (x3) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x3))) : NULL;
              }
              break;
            case CPP_TOKEN_FLD_SOURCE:
              if ((void *)((*x).exp.tokens) == this_obj)
                op (&((*x).exp.tokens[i2].val.source), cookie);
              break;
            case CPP_TOKEN_FLD_STR:
              if ((void *)((*x).exp.tokens) == this_obj)
                op (&((*x).exp.tokens[i2].val.str.text), cookie);
              break;
            case CPP_TOKEN_FLD_ARG_NO:
              break;
            case CPP_TOKEN_FLD_PRAGMA:
              break;
            default:
              break;
            }
        }
        if ((void *)(x) == this_obj)
          op (&((*x).exp.tokens), cookie);
      }
      break;
    case 1:
      if ((void *)(x) == this_obj)
        op (&((*x).exp.text), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_9cpp_token (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cpp_token * const x ATTRIBUTE_UNUSED = (struct cpp_token *)x_p;
  switch (cpp_token_val_index (&((*x))))
    {
    case CPP_TOKEN_FLD_NODE:
      {
        union tree_node * x0 =
          ((*x).val.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).val.node))) : NULL;
        if ((void *)(x) == this_obj)
          op (&(x0), cookie);
        (*x).val.node = (x0) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x0))) : NULL;
      }
      break;
    case CPP_TOKEN_FLD_SOURCE:
      if ((void *)(x) == this_obj)
        op (&((*x).val.source), cookie);
      break;
    case CPP_TOKEN_FLD_STR:
      if ((void *)(x) == this_obj)
        op (&((*x).val.str.text), cookie);
      break;
    case CPP_TOKEN_FLD_ARG_NO:
      break;
    case CPP_TOKEN_FLD_PRAGMA:
      break;
    default:
      break;
    }
}

void
gt_pch_p_9line_maps (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct line_maps * const x ATTRIBUTE_UNUSED = (struct line_maps *)x_p;
  if ((*x).maps != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).used); i0++) {
      if ((void *)((*x).maps) == this_obj)
        op (&((*x).maps[i0].to_file), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).maps), cookie);
  }
}

void
gt_pch_p_II17splay_tree_node_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_node_s * const x ATTRIBUTE_UNUSED = (struct splay_tree_node_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).left), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).right), cookie);
}

void
gt_pch_p_SP9tree_node17splay_tree_node_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_node_s * const x ATTRIBUTE_UNUSED = (struct splay_tree_node_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).key), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).left), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).right), cookie);
}

void
gt_pch_p_P9tree_nodeP9tree_node17splay_tree_node_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_node_s * const x ATTRIBUTE_UNUSED = (struct splay_tree_node_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).key), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).left), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).right), cookie);
}

void
gt_pch_p_IP9tree_node17splay_tree_node_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_node_s * const x ATTRIBUTE_UNUSED = (struct splay_tree_node_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).left), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).right), cookie);
}

void
gt_pch_p_P12tree_int_map4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_IP9tree_node12splay_tree_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_s * const x ATTRIBUTE_UNUSED = (struct splay_tree_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).root), cookie);
}

void
gt_pch_p_P9tree_nodeP9tree_node12splay_tree_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_s * const x ATTRIBUTE_UNUSED = (struct splay_tree_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).root), cookie);
}

void
gt_pch_p_P12varpool_node4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P12object_block4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P7section4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P17tree_priority_map4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P8tree_map4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P15throw_stmt_node4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P9reg_attrs4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P9mem_attrs4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P7rtx_def4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_SP9tree_node12splay_tree_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_s * const x ATTRIBUTE_UNUSED = (struct splay_tree_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).root), cookie);
}

void
gt_pch_p_P11cgraph_node4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_II12splay_tree_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_s * const x ATTRIBUTE_UNUSED = (struct splay_tree_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).root), cookie);
}

void
gt_pch_p_P11cgraph_edge4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P9loop_exit4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P24types_used_by_vars_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

void
gt_pch_p_P9tree_node4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * const x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}

/* GC roots.  */

static void gt_ggc_ma_reg_equiv_init (void *);
static void
gt_ggc_ma_reg_equiv_init (ATTRIBUTE_UNUSED void *x_p)
{
  if (reg_equiv_init != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(reg_equiv_init_size); i0++) {
      gt_ggc_m_7rtx_def (reg_equiv_init[i0]);
    }
    ggc_mark (reg_equiv_init);
  }
}

static void gt_pch_pa_reg_equiv_init
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_reg_equiv_init (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (reg_equiv_init != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(reg_equiv_init_size); i0++) {
      if ((void *)(reg_equiv_init) == this_obj)
        op (&(reg_equiv_init[i0]), cookie);
    }
    if ((void *)(&reg_equiv_init) == this_obj)
      op (&(reg_equiv_init), cookie);
  }
}

static void gt_pch_na_reg_equiv_init (void *);
static void
gt_pch_na_reg_equiv_init (ATTRIBUTE_UNUSED void *x_p)
{
  if (reg_equiv_init != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(reg_equiv_init_size); i1++) {
      gt_pch_n_7rtx_def (reg_equiv_init[i1]);
    }
    gt_pch_note_object (reg_equiv_init, &reg_equiv_init, gt_pch_pa_reg_equiv_init, gt_types_enum_last);
  }
}

static void gt_ggc_ma_regno_reg_rtx (void *);
static void
gt_ggc_ma_regno_reg_rtx (ATTRIBUTE_UNUSED void *x_p)
{
  if (regno_reg_rtx != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(crtl->emit.x_reg_rtx_no); i0++) {
      gt_ggc_m_7rtx_def (regno_reg_rtx[i0]);
    }
    ggc_mark (regno_reg_rtx);
  }
}

static void gt_pch_pa_regno_reg_rtx
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_regno_reg_rtx (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (regno_reg_rtx != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(crtl->emit.x_reg_rtx_no); i0++) {
      if ((void *)(regno_reg_rtx) == this_obj)
        op (&(regno_reg_rtx[i0]), cookie);
    }
    if ((void *)(&regno_reg_rtx) == this_obj)
      op (&(regno_reg_rtx), cookie);
  }
}

static void gt_pch_na_regno_reg_rtx (void *);
static void
gt_pch_na_regno_reg_rtx (ATTRIBUTE_UNUSED void *x_p)
{
  if (regno_reg_rtx != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(crtl->emit.x_reg_rtx_no); i1++) {
      gt_pch_n_7rtx_def (regno_reg_rtx[i1]);
    }
    gt_pch_note_object (regno_reg_rtx, &regno_reg_rtx, gt_pch_pa_regno_reg_rtx, gt_types_enum_last);
  }
}

const struct ggc_root_tab gt_ggc_r_gtype_desc_c[] = {
  {
    &chrec_known,
    1,
    sizeof (chrec_known),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &chrec_dont_know,
    1,
    sizeof (chrec_dont_know),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &cfg_layout_function_header,
    1,
    sizeof (cfg_layout_function_header),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &cfg_layout_function_footer,
    1,
    sizeof (cfg_layout_function_footer),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &block_clear_fn,
    1,
    sizeof (block_clear_fn),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &reg_equiv_init,
    1,
    sizeof (reg_equiv_init),
    &gt_ggc_ma_reg_equiv_init,
    &gt_pch_na_reg_equiv_init
  },
  {
    &reg_equiv_memory_loc_vec,
    1,
    sizeof (reg_equiv_memory_loc_vec),
    &gt_ggc_mx_VEC_rtx_gc,
    &gt_pch_nx_VEC_rtx_gc
  },
  {
    &varpool_nodes,
    1,
    sizeof (varpool_nodes),
    &gt_ggc_mx_varpool_node,
    &gt_pch_nx_varpool_node
  },
  {
    &varpool_nodes_queue,
    1,
    sizeof (varpool_nodes_queue),
    &gt_ggc_mx_varpool_node,
    &gt_pch_nx_varpool_node
  },
  {
    &cgraph_asm_nodes,
    1,
    sizeof (cgraph_asm_nodes),
    &gt_ggc_mx_cgraph_asm_node,
    &gt_pch_nx_cgraph_asm_node
  },
  {
    &cgraph_new_nodes,
    1,
    sizeof (cgraph_new_nodes),
    &gt_ggc_mx_cgraph_node,
    &gt_pch_nx_cgraph_node
  },
  {
    &cgraph_nodes_queue,
    1,
    sizeof (cgraph_nodes_queue),
    &gt_ggc_mx_cgraph_node,
    &gt_pch_nx_cgraph_node
  },
  {
    &cgraph_nodes,
    1,
    sizeof (cgraph_nodes),
    &gt_ggc_mx_cgraph_node,
    &gt_pch_nx_cgraph_node
  },
  {
    &in_section,
    1,
    sizeof (in_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &bss_noswitch_section,
    1,
    sizeof (bss_noswitch_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &lcomm_section,
    1,
    sizeof (lcomm_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &comm_section,
    1,
    sizeof (comm_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &tls_comm_section,
    1,
    sizeof (tls_comm_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &eh_frame_section,
    1,
    sizeof (eh_frame_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &exception_section,
    1,
    sizeof (exception_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &sbss_section,
    1,
    sizeof (sbss_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &bss_section,
    1,
    sizeof (bss_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &dtors_section,
    1,
    sizeof (dtors_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &ctors_section,
    1,
    sizeof (ctors_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &sdata_section,
    1,
    sizeof (sdata_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &readonly_data_section,
    1,
    sizeof (readonly_data_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &data_section,
    1,
    sizeof (data_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &text_section,
    1,
    sizeof (text_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &types_used_by_cur_var_decl,
    1,
    sizeof (types_used_by_cur_var_decl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &types_used_by_vars_hash,
    1,
    sizeof (types_used_by_vars_hash),
    &gt_ggc_m_P24types_used_by_vars_entry4htab,
    &gt_pch_n_P24types_used_by_vars_entry4htab
  },
  {
    &cfun,
    1,
    sizeof (cfun),
    &gt_ggc_mx_function,
    &gt_pch_nx_function
  },
  {
    &x_rtl.expr.x_saveregs_value,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.expr.x_apply_args_value,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.expr.x_forced_labels,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.emit.x_first_insn,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.emit.x_last_insn,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.emit.sequence_stack,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_sequence_stack,
    &gt_pch_nx_sequence_stack
  },
  {
    &x_rtl.varasm.pool,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_constant_pool,
    &gt_pch_nx_rtx_constant_pool
  },
  {
    &x_rtl.args.arg_offset_rtx,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.args.internal_arg_pointer,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.subsections.hot_section_label,
    1, 
    sizeof (x_rtl),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.subsections.cold_section_label,
    1, 
    sizeof (x_rtl),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.subsections.hot_section_end_label,
    1, 
    sizeof (x_rtl),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.subsections.cold_section_end_label,
    1, 
    sizeof (x_rtl),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.subsections.unlikely_text_section_name,
    1, 
    sizeof (x_rtl),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.eh.filter,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.exc_ptr,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.ehr_stackadj,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.ehr_handler,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.ehr_label,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.sjlj_fc,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.sjlj_exit_after,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.exception_handler_label_map,
    1,
    sizeof (x_rtl),
    &gt_ggc_m_P13ehl_map_entry4htab,
    &gt_pch_n_P13ehl_map_entry4htab
  },
  {
    &x_rtl.eh.ttype_data,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &x_rtl.eh.ehspec_data,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_varray_head_tag,
    &gt_pch_nx_varray_head_tag
  },
  {
    &x_rtl.eh.action_record_data,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_varray_head_tag,
    &gt_pch_nx_varray_head_tag
  },
  {
    &x_rtl.eh.call_site_record,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_VEC_call_site_record_gc,
    &gt_pch_nx_VEC_call_site_record_gc
  },
  {
    &x_rtl.return_rtx,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.hard_reg_initial_vals,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_initial_value_struct,
    &gt_pch_nx_initial_value_struct
  },
  {
    &x_rtl.stack_protect_guard,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &x_rtl.x_nonlocal_goto_handler_labels,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_return_label,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_naked_return_label,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_stack_slot_list,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_stack_check_probe_note,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_arg_pointer_save_area,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.drap_reg,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_parm_birth_insn,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_used_temp_slots,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_VEC_temp_slot_p_gc,
    &gt_pch_nx_VEC_temp_slot_p_gc
  },
  {
    &x_rtl.x_avail_temp_slots,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_temp_slot,
    &gt_pch_nx_temp_slot
  },
  {
    &x_rtl.epilogue_delay_list,
    1,
    sizeof (x_rtl),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &regno_reg_rtx,
    1,
    sizeof (regno_reg_rtx),
    &gt_ggc_ma_regno_reg_rtx,
    &gt_pch_na_regno_reg_rtx
  },
  {
    &libfunc_table[0],
    1 * (LTI_MAX),
    sizeof (libfunc_table[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &memory_identifier_string,
    1,
    sizeof (memory_identifier_string),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &current_function_func_begin_label,
    1, 
    sizeof (current_function_func_begin_label),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &current_function_decl,
    1,
    sizeof (current_function_decl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &sizetype_tab[0],
    1 * ((int) TYPE_KIND_LAST),
    sizeof (sizetype_tab[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &integer_types[0],
    1 * (itk_none),
    sizeof (integer_types[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &global_trees[0],
    1 * (TI_MAX),
    sizeof (global_trees[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &implicit_built_in_decls[0],
    1 * ((int) END_BUILTINS),
    sizeof (implicit_built_in_decls[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &built_in_decls[0],
    1 * ((int) END_BUILTINS),
    sizeof (built_in_decls[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &stack_limit_rtx,
    1,
    sizeof (stack_limit_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &return_address_pointer_rtx,
    1,
    sizeof (return_address_pointer_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &static_chain_incoming_rtx,
    1,
    sizeof (static_chain_incoming_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &static_chain_rtx,
    1,
    sizeof (static_chain_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &pic_offset_table_rtx,
    1,
    sizeof (pic_offset_table_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &global_rtl[0],
    1 * (GR_MAX),
    sizeof (global_rtl[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &const_tiny_rtx[0][0],
    1 * (3) * ((int) MAX_MACHINE_MODE),
    sizeof (const_tiny_rtx[0][0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &const_true_rtx,
    1,
    sizeof (const_true_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &const_int_rtx[0],
    1 * (MAX_SAVED_CONST_INT * 2 + 1),
    sizeof (const_int_rtx[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &line_table,
    1,
    sizeof (line_table),
    &gt_ggc_mx_line_maps,
    &gt_pch_nx_line_maps
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gtype_desc_c[] = {
  { &reg_equiv_init_size, 1, sizeof (reg_equiv_init_size), NULL, NULL },
  { &cgraph_order, 1, sizeof (cgraph_order), NULL, NULL },
  { &cgraph_max_pid, 1, sizeof (cgraph_max_pid), NULL, NULL },
  { &cgraph_edge_max_uid, 1, sizeof (cgraph_edge_max_uid), NULL, NULL },
  { &cgraph_max_uid, 1, sizeof (cgraph_max_uid), NULL, NULL },
  { &cgraph_n_nodes, 1, sizeof (cgraph_n_nodes), NULL, NULL },
  { &in_cold_section_p, 1, sizeof (in_cold_section_p), NULL, NULL },
  { &x_rtl, 1, sizeof (x_rtl), NULL, NULL },
  LAST_GGC_ROOT_TAB
};


/* Used to implement the RTX_NEXT macro.  */
const unsigned char rtx_next[NUM_RTX_CODE] = {
  0,
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  0,
  0,
  0,
  0,
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  0,
  0,
  0,
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  0,
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
};
