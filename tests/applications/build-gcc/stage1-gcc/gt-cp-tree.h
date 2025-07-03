/* Type information for cp/tree.c.
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

void
gt_ggc_mx_VEC_deferred_access_check_gc (void *x_p)
{
  struct VEC_deferred_access_check_gc * const x = (struct VEC_deferred_access_check_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).base.vec[i0].binfo);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].decl);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].diag_decl);
        }
      }
    }
}

void
gt_ggc_mx_tinst_level (void *x_p)
{
  struct tinst_level * const x = (struct tinst_level *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_11tinst_level ((*x).next);
      gt_ggc_m_9tree_node ((*x).decl);
    }
}

void
gt_ggc_mx_VEC_tree_pair_s_gc (void *x_p)
{
  struct VEC_tree_pair_s_gc * const x = (struct VEC_tree_pair_s_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).base.vec[i0].purpose);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].value);
        }
      }
    }
}

void
gt_ggc_mx_saved_scope (void *x_p)
{
  struct saved_scope * const x = (struct saved_scope *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_24VEC_cxx_saved_binding_gc ((*x).old_bindings);
      gt_ggc_m_9tree_node ((*x).old_namespace);
      gt_ggc_m_9tree_node ((*x).decl_ns_list);
      gt_ggc_m_9tree_node ((*x).class_name);
      gt_ggc_m_9tree_node ((*x).class_type);
      gt_ggc_m_9tree_node ((*x).access_specifier);
      gt_ggc_m_9tree_node ((*x).function_decl);
      gt_ggc_m_11VEC_tree_gc ((*x).lang_base);
      gt_ggc_m_9tree_node ((*x).lang_name);
      gt_ggc_m_9tree_node ((*x).template_parms);
      gt_ggc_m_16cp_binding_level ((*x).x_previous_class_level);
      gt_ggc_m_9tree_node ((*x).x_saved_tree);
      gt_ggc_m_9tree_node ((*x).x_stmt_tree.x_cur_stmt_list);
      gt_ggc_m_16cp_binding_level ((*x).class_bindings);
      gt_ggc_m_16cp_binding_level ((*x).bindings);
      gt_ggc_m_11saved_scope ((*x).prev);
    }
}

void
gt_ggc_mx_cxx_int_tree_map (void *x_p)
{
  struct cxx_int_tree_map * const x = (struct cxx_int_tree_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).to);
    }
}

void
gt_ggc_mx_language_function (void *x_p)
{
  struct language_function * const x = (struct language_function *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.x_stmt_tree.x_cur_stmt_list);
      gt_ggc_m_9tree_node ((*x).x_cdtor_label);
      gt_ggc_m_9tree_node ((*x).x_current_class_ptr);
      gt_ggc_m_9tree_node ((*x).x_current_class_ref);
      gt_ggc_m_9tree_node ((*x).x_eh_spec_block);
      gt_ggc_m_9tree_node ((*x).x_in_charge_parm);
      gt_ggc_m_9tree_node ((*x).x_vtt_parm);
      gt_ggc_m_9tree_node ((*x).x_return_value);
      gt_ggc_m_P17named_label_entry4htab ((*x).x_named_labels);
      gt_ggc_m_16cp_binding_level ((*x).bindings);
      gt_ggc_m_11VEC_tree_gc ((*x).x_local_names);
      gt_ggc_m_P16cxx_int_tree_map4htab ((*x).extern_decl_map);
    }
}

void
gt_ggc_mx_lang_tree_node (void *x_p)
{
  union lang_tree_node * x = (union lang_tree_node *)x_p;
  union lang_tree_node * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((union lang_tree_node *)TREE_CHAIN (&(*xlimit).generic));
  while (x != xlimit)
    {
      switch (cp_tree_node_structure (&((*x))))
        {
        case TS_CP_GENERIC:
          switch (tree_node_structure (&((*x).generic)))
            {
            case TS_BASE:
              gt_ggc_m_10tree_ann_d ((*x).generic.base.ann);
              break;
            case TS_COMMON:
              gt_ggc_m_10tree_ann_d ((*x).generic.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.common.type);
              break;
            case TS_INT_CST:
              gt_ggc_m_10tree_ann_d ((*x).generic.int_cst.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.int_cst.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.int_cst.common.type);
              break;
            case TS_REAL_CST:
              gt_ggc_m_10tree_ann_d ((*x).generic.real_cst.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.real_cst.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.real_cst.common.type);
              gt_ggc_m_10real_value ((*x).generic.real_cst.real_cst_ptr);
              break;
            case TS_FIXED_CST:
              gt_ggc_m_10tree_ann_d ((*x).generic.fixed_cst.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.fixed_cst.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.fixed_cst.common.type);
              gt_ggc_m_11fixed_value ((*x).generic.fixed_cst.fixed_cst_ptr);
              break;
            case TS_VECTOR:
              gt_ggc_m_10tree_ann_d ((*x).generic.vector.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.vector.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.vector.common.type);
              gt_ggc_m_9tree_node ((*x).generic.vector.elements);
              break;
            case TS_STRING:
              gt_ggc_m_10tree_ann_d ((*x).generic.string.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.string.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.string.common.type);
              break;
            case TS_COMPLEX:
              gt_ggc_m_10tree_ann_d ((*x).generic.complex.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.complex.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.complex.common.type);
              gt_ggc_m_9tree_node ((*x).generic.complex.real);
              gt_ggc_m_9tree_node ((*x).generic.complex.imag);
              break;
            case TS_IDENTIFIER:
              gt_ggc_m_10tree_ann_d ((*x).generic.identifier.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.identifier.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.identifier.common.type);
              gt_ggc_m_S ((*x).generic.identifier.id.str);
              break;
            case TS_DECL_MINIMAL:
              gt_ggc_m_10tree_ann_d ((*x).generic.decl_minimal.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.decl_minimal.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_minimal.common.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_minimal.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_minimal.context);
              break;
            case TS_DECL_COMMON:
              gt_ggc_m_10tree_ann_d ((*x).generic.decl_common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.size);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.initial);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.decl_common.lang_specific);
              break;
            case TS_DECL_WRTL:
              gt_ggc_m_10tree_ann_d ((*x).generic.decl_with_rtl.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.size);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.decl_with_rtl.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.decl_with_rtl.rtl);
              break;
            case TS_DECL_NON_COMMON:
              gt_ggc_m_10tree_ann_d ((*x).generic.decl_non_common.common.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.decl_non_common.common.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.decl_non_common.common.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.section_name);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.saved_tree);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.arguments);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.result);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.vindex);
              break;
            case TS_PARM_DECL:
              gt_ggc_m_10tree_ann_d ((*x).generic.parm_decl.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.parm_decl.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.parm_decl.common.rtl);
              gt_ggc_m_7rtx_def ((*x).generic.parm_decl.incoming_rtl);
              break;
            case TS_DECL_WITH_VIS:
              gt_ggc_m_10tree_ann_d ((*x).generic.decl_with_vis.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.decl_with_vis.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.decl_with_vis.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.section_name);
              break;
            case TS_VAR_DECL:
              gt_ggc_m_10tree_ann_d ((*x).generic.var_decl.common.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.var_decl.common.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.var_decl.common.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.section_name);
              break;
            case TS_FIELD_DECL:
              gt_ggc_m_10tree_ann_d ((*x).generic.field_decl.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.size);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.field_decl.common.lang_specific);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.offset);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.bit_field_type);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.qualifier);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.bit_offset);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.fcontext);
              break;
            case TS_LABEL_DECL:
              gt_ggc_m_10tree_ann_d ((*x).generic.label_decl.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.label_decl.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.label_decl.common.rtl);
              break;
            case TS_RESULT_DECL:
              gt_ggc_m_10tree_ann_d ((*x).generic.result_decl.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.result_decl.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.result_decl.common.rtl);
              break;
            case TS_CONST_DECL:
              gt_ggc_m_10tree_ann_d ((*x).generic.const_decl.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.const_decl.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.const_decl.common.rtl);
              break;
            case TS_TYPE_DECL:
              gt_ggc_m_10tree_ann_d ((*x).generic.type_decl.common.common.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.type_decl.common.common.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.type_decl.common.common.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.section_name);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.saved_tree);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.arguments);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.result);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.vindex);
              break;
            case TS_FUNCTION_DECL:
              gt_ggc_m_10tree_ann_d ((*x).generic.function_decl.common.common.common.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.function_decl.common.common.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.function_decl.common.common.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.section_name);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.saved_tree);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.arguments);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.result);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.vindex);
              gt_ggc_m_8function ((*x).generic.function_decl.f);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.function_specific_target);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.function_specific_optimization);
              break;
            case TS_TYPE:
              gt_ggc_m_10tree_ann_d ((*x).generic.type.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.type.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.type.common.type);
              gt_ggc_m_9tree_node ((*x).generic.type.values);
              gt_ggc_m_9tree_node ((*x).generic.type.size);
              gt_ggc_m_9tree_node ((*x).generic.type.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.type.attributes);
              gt_ggc_m_9tree_node ((*x).generic.type.pointer_to);
              gt_ggc_m_9tree_node ((*x).generic.type.reference_to);
              switch (debug_hooks == &sdb_debug_hooks ? 1 : debug_hooks == &dwarf2_debug_hooks ? 2 : 0)
                {
                case 0:
                  break;
                case 1:
                  gt_ggc_m_S ((*x).generic.type.symtab.pointer);
                  break;
                case 2:
                  gt_ggc_m_10die_struct ((*x).generic.type.symtab.die);
                  break;
                default:
                  break;
                }
              gt_ggc_m_9tree_node ((*x).generic.type.name);
              gt_ggc_m_9tree_node ((*x).generic.type.minval);
              gt_ggc_m_9tree_node ((*x).generic.type.maxval);
              gt_ggc_m_9tree_node ((*x).generic.type.next_variant);
              gt_ggc_m_9tree_node ((*x).generic.type.main_variant);
              gt_ggc_m_9tree_node ((*x).generic.type.binfo);
              gt_ggc_m_9tree_node ((*x).generic.type.context);
              gt_ggc_m_9tree_node ((*x).generic.type.canonical);
              gt_ggc_m_9lang_type ((*x).generic.type.lang_specific);
              break;
            case TS_LIST:
              gt_ggc_m_10tree_ann_d ((*x).generic.list.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.list.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.list.common.type);
              gt_ggc_m_9tree_node ((*x).generic.list.purpose);
              gt_ggc_m_9tree_node ((*x).generic.list.value);
              break;
            case TS_VEC:
              gt_ggc_m_10tree_ann_d ((*x).generic.vec.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.vec.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.vec.common.type);
              {
                size_t i1;
                size_t l1 = (size_t)(TREE_VEC_LENGTH ((tree)&((*x).generic.vec)));
                for (i1 = 0; i1 != l1; i1++) {
                  gt_ggc_m_9tree_node ((*x).generic.vec.a[i1]);
                }
              }
              break;
            case TS_EXP:
              gt_ggc_m_10tree_ann_d ((*x).generic.exp.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.exp.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.exp.common.type);
              gt_ggc_m_9tree_node ((*x).generic.exp.block);
              switch (TREE_CODE ((tree) &(*x)))
                {
                default:
                  {
                    size_t i2;
                    size_t l2 = (size_t)(TREE_OPERAND_LENGTH ((tree) &(*x)));
                    for (i2 = 0; i2 != l2; i2++) {
                      gt_ggc_m_9tree_node ((*x).generic.exp.operands[i2]);
                    }
                  }
                  break;
                }
              break;
            case TS_SSA_NAME:
              gt_ggc_m_10tree_ann_d ((*x).generic.ssa_name.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.ssa_name.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.ssa_name.common.type);
              gt_ggc_m_9tree_node ((*x).generic.ssa_name.var);
              gt_ggc_m_18gimple_statement_d ((*x).generic.ssa_name.def_stmt);
              gt_ggc_m_12ptr_info_def ((*x).generic.ssa_name.ptr_info);
              gt_ggc_m_9tree_node ((*x).generic.ssa_name.value_handle);
              break;
            case TS_BLOCK:
              gt_ggc_m_10tree_ann_d ((*x).generic.block.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.block.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.block.common.type);
              gt_ggc_m_9tree_node ((*x).generic.block.vars);
              gt_ggc_m_11VEC_tree_gc ((*x).generic.block.nonlocalized_vars);
              gt_ggc_m_9tree_node ((*x).generic.block.subblocks);
              gt_ggc_m_9tree_node ((*x).generic.block.supercontext);
              gt_ggc_m_9tree_node ((*x).generic.block.abstract_origin);
              gt_ggc_m_9tree_node ((*x).generic.block.fragment_origin);
              gt_ggc_m_9tree_node ((*x).generic.block.fragment_chain);
              break;
            case TS_BINFO:
              gt_ggc_m_10tree_ann_d ((*x).generic.binfo.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.binfo.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.binfo.common.type);
              gt_ggc_m_9tree_node ((*x).generic.binfo.offset);
              gt_ggc_m_9tree_node ((*x).generic.binfo.vtable);
              gt_ggc_m_9tree_node ((*x).generic.binfo.virtuals);
              gt_ggc_m_9tree_node ((*x).generic.binfo.vptr_field);
              gt_ggc_m_11VEC_tree_gc ((*x).generic.binfo.base_accesses);
              gt_ggc_m_9tree_node ((*x).generic.binfo.inheritance);
              gt_ggc_m_9tree_node ((*x).generic.binfo.vtt_subvtt);
              gt_ggc_m_9tree_node ((*x).generic.binfo.vtt_vptr);
              {
                size_t i3;
                size_t l3 = (size_t)(((*x).generic.binfo.base_binfos.base).num);
                for (i3 = 0; i3 != l3; i3++) {
                  gt_ggc_m_9tree_node ((*x).generic.binfo.base_binfos.base.vec[i3]);
                }
              }
              break;
            case TS_STATEMENT_LIST:
              gt_ggc_m_10tree_ann_d ((*x).generic.stmt_list.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.stmt_list.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.stmt_list.common.type);
              gt_ggc_m_24tree_statement_list_node ((*x).generic.stmt_list.head);
              gt_ggc_m_24tree_statement_list_node ((*x).generic.stmt_list.tail);
              break;
            case TS_CONSTRUCTOR:
              gt_ggc_m_10tree_ann_d ((*x).generic.constructor.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.constructor.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.constructor.common.type);
              gt_ggc_m_22VEC_constructor_elt_gc ((*x).generic.constructor.elts);
              break;
            case TS_MEMORY_TAG:
              gt_ggc_m_10tree_ann_d ((*x).generic.mtag.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.mtag.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.mtag.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.mtag.common.name);
              gt_ggc_m_9tree_node ((*x).generic.mtag.common.context);
              break;
            case TS_OMP_CLAUSE:
              gt_ggc_m_10tree_ann_d ((*x).generic.omp_clause.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.omp_clause.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.omp_clause.common.type);
              gt_ggc_m_12gimple_seq_d ((*x).generic.omp_clause.gimple_reduction_init);
              gt_ggc_m_12gimple_seq_d ((*x).generic.omp_clause.gimple_reduction_merge);
              {
                size_t i4;
                size_t l4 = (size_t)(omp_clause_num_ops[OMP_CLAUSE_CODE ((tree)&((*x).generic.omp_clause))]);
                for (i4 = 0; i4 != l4; i4++) {
                  gt_ggc_m_9tree_node ((*x).generic.omp_clause.ops[i4]);
                }
              }
              break;
            case TS_MEMORY_PARTITION_TAG:
              gt_ggc_m_10tree_ann_d ((*x).generic.mpt.common.common.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.mpt.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.mpt.common.common.common.type);
              gt_ggc_m_9tree_node ((*x).generic.mpt.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.mpt.common.common.context);
              gt_ggc_m_15bitmap_head_def ((*x).generic.mpt.symbols);
              break;
            case TS_OPTIMIZATION:
              gt_ggc_m_10tree_ann_d ((*x).generic.optimization.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.optimization.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.optimization.common.type);
              break;
            case TS_TARGET_OPTION:
              gt_ggc_m_10tree_ann_d ((*x).generic.target_option.common.base.ann);
              gt_ggc_m_9tree_node ((*x).generic.target_option.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.target_option.common.type);
              break;
            default:
              break;
            }
          break;
        case TS_CP_TPI:
          gt_ggc_m_10tree_ann_d ((*x).tpi.common.base.ann);
          gt_ggc_m_9tree_node ((*x).tpi.common.chain);
          gt_ggc_m_9tree_node ((*x).tpi.common.type);
          gt_ggc_m_9tree_node ((*x).tpi.decl);
          break;
        case TS_CP_PTRMEM:
          gt_ggc_m_10tree_ann_d ((*x).ptrmem.common.base.ann);
          gt_ggc_m_9tree_node ((*x).ptrmem.common.chain);
          gt_ggc_m_9tree_node ((*x).ptrmem.common.type);
          gt_ggc_m_7rtx_def ((*x).ptrmem.rtl);
          gt_ggc_m_9tree_node ((*x).ptrmem.member);
          break;
        case TS_CP_OVERLOAD:
          gt_ggc_m_10tree_ann_d ((*x).overload.common.base.ann);
          gt_ggc_m_9tree_node ((*x).overload.common.chain);
          gt_ggc_m_9tree_node ((*x).overload.common.type);
          gt_ggc_m_9tree_node ((*x).overload.function);
          break;
        case TS_CP_BASELINK:
          gt_ggc_m_10tree_ann_d ((*x).baselink.common.base.ann);
          gt_ggc_m_9tree_node ((*x).baselink.common.chain);
          gt_ggc_m_9tree_node ((*x).baselink.common.type);
          gt_ggc_m_9tree_node ((*x).baselink.binfo);
          gt_ggc_m_9tree_node ((*x).baselink.functions);
          gt_ggc_m_9tree_node ((*x).baselink.access_binfo);
          break;
        case TS_CP_DEFAULT_ARG:
          gt_ggc_m_10tree_ann_d ((*x).default_arg.common.base.ann);
          gt_ggc_m_9tree_node ((*x).default_arg.common.chain);
          gt_ggc_m_9tree_node ((*x).default_arg.common.type);
          gt_ggc_m_14cp_token_cache ((*x).default_arg.tokens);
          gt_ggc_m_11VEC_tree_gc ((*x).default_arg.instantiations);
          break;
        case TS_CP_IDENTIFIER:
          gt_ggc_m_10tree_ann_d ((*x).identifier.c_common.common.base.ann);
          gt_ggc_m_9tree_node ((*x).identifier.c_common.common.chain);
          gt_ggc_m_9tree_node ((*x).identifier.c_common.common.type);
          gt_ggc_m_S ((*x).identifier.c_common.node.ident.str);
          switch (CPP_HASHNODE_VALUE_IDX (((*x).identifier.c_common.node)))
            {
            case NTV_MACRO:
              gt_ggc_m_9cpp_macro ((*x).identifier.c_common.node.value.macro);
              break;
            case NTV_ANSWER:
              gt_ggc_m_6answer ((*x).identifier.c_common.node.value.answers);
              break;
            case NTV_BUILTIN:
              break;
            case NTV_ARGUMENT:
              break;
            default:
              break;
            }
          gt_ggc_m_11cxx_binding ((*x).identifier.namespace_bindings);
          gt_ggc_m_11cxx_binding ((*x).identifier.bindings);
          gt_ggc_m_9tree_node ((*x).identifier.class_template_info);
          gt_ggc_m_9tree_node ((*x).identifier.label_value);
          break;
        case TS_CP_STATIC_ASSERT:
          gt_ggc_m_10tree_ann_d ((*x).static_assertion.common.base.ann);
          gt_ggc_m_9tree_node ((*x).static_assertion.common.chain);
          gt_ggc_m_9tree_node ((*x).static_assertion.common.type);
          gt_ggc_m_9tree_node ((*x).static_assertion.condition);
          gt_ggc_m_9tree_node ((*x).static_assertion.message);
          break;
        case TS_CP_ARGUMENT_PACK_SELECT:
          gt_ggc_m_10tree_ann_d ((*x).argument_pack_select.common.base.ann);
          gt_ggc_m_9tree_node ((*x).argument_pack_select.common.chain);
          gt_ggc_m_9tree_node ((*x).argument_pack_select.common.type);
          gt_ggc_m_9tree_node ((*x).argument_pack_select.argument_pack);
          break;
        case TS_CP_TRAIT_EXPR:
          gt_ggc_m_10tree_ann_d ((*x).trait_expression.common.base.ann);
          gt_ggc_m_9tree_node ((*x).trait_expression.common.chain);
          gt_ggc_m_9tree_node ((*x).trait_expression.common.type);
          gt_ggc_m_9tree_node ((*x).trait_expression.type1);
          gt_ggc_m_9tree_node ((*x).trait_expression.type2);
          break;
        default:
          break;
        }
      x = ((union lang_tree_node *)TREE_CHAIN (&(*x).generic));
    }
}

void
gt_ggc_mx_lang_decl (void *x_p)
{
  struct lang_decl * const x = (struct lang_decl *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (((*x).decl_flags).u1sel)
        {
        case 0:
          gt_ggc_m_9tree_node ((*x).decl_flags.u.template_info);
          break;
        case 1:
          gt_ggc_m_16cp_binding_level ((*x).decl_flags.u.level);
          break;
        default:
          break;
        }
      switch (((*x).decl_flags).u2sel)
        {
        case 0:
          gt_ggc_m_9tree_node ((*x).decl_flags.u2.access);
          break;
        case 1:
          break;
        default:
          break;
        }
      switch (((*x)).decl_flags.can_be_full)
        {
        case 1:
          gt_ggc_m_9tree_node ((*x).u.f.befriending_classes);
          gt_ggc_m_9tree_node ((*x).u.f.context);
          switch ((*x).decl_flags.thunk_p)
            {
            case 0:
              gt_ggc_m_9tree_node ((*x).u.f.u5.cloned_function);
              break;
            case 1:
              break;
            default:
              break;
            }
          switch (((*x).u.f).u3sel + ((*x).u.f).pending_inline_p)
            {
            case 0:
              gt_ggc_m_18sorted_fields_type ((*x).u.f.u.sorted_fields);
              break;
            case 2:
              gt_ggc_m_14cp_token_cache ((*x).u.f.u.pending_inline_info);
              break;
            case 1:
              gt_ggc_m_17language_function ((*x).u.f.u.saved_language_function);
              break;
            default:
              break;
            }
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_lang_type (void *x_p)
{
  struct lang_type * const x = (struct lang_type *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (((*x).u).h.is_lang_type_class)
        {
        case 1:
          gt_ggc_m_9tree_node ((*x).u.c.primary_base);
          gt_ggc_m_18VEC_tree_pair_s_gc ((*x).u.c.vcall_indices);
          gt_ggc_m_9tree_node ((*x).u.c.vtables);
          gt_ggc_m_9tree_node ((*x).u.c.typeinfo_var);
          gt_ggc_m_11VEC_tree_gc ((*x).u.c.vbases);
          gt_ggc_m_15binding_table_s ((*x).u.c.nested_udts);
          gt_ggc_m_9tree_node ((*x).u.c.as_base);
          gt_ggc_m_11VEC_tree_gc ((*x).u.c.pure_virtuals);
          gt_ggc_m_9tree_node ((*x).u.c.friend_classes);
          gt_ggc_m_11VEC_tree_gc ((*x).u.c.methods);
          gt_ggc_m_9tree_node ((*x).u.c.key_method);
          gt_ggc_m_9tree_node ((*x).u.c.decl_list);
          gt_ggc_m_9tree_node ((*x).u.c.template_info);
          gt_ggc_m_9tree_node ((*x).u.c.befriending_classes);
          gt_ggc_m_9tree_node ((*x).u.c.objc_info);
          break;
        case 0:
          gt_ggc_m_9tree_node ((*x).u.ptrmem.record);
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_m_P16cxx_int_tree_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_16cxx_int_tree_map ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_pch_nx_VEC_deferred_access_check_gc (void *x_p)
{
  struct VEC_deferred_access_check_gc * const x = (struct VEC_deferred_access_check_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_28VEC_deferred_access_check_gc, gt_ggc_e_28VEC_deferred_access_check_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).base.vec[i0].binfo);
          gt_pch_n_9tree_node ((*x).base.vec[i0].decl);
          gt_pch_n_9tree_node ((*x).base.vec[i0].diag_decl);
        }
      }
    }
}

void
gt_pch_nx_tinst_level (void *x_p)
{
  struct tinst_level * const x = (struct tinst_level *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11tinst_level, gt_ggc_e_11tinst_level))
    {
      gt_pch_n_11tinst_level ((*x).next);
      gt_pch_n_9tree_node ((*x).decl);
    }
}

void
gt_pch_nx_VEC_tree_pair_s_gc (void *x_p)
{
  struct VEC_tree_pair_s_gc * const x = (struct VEC_tree_pair_s_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18VEC_tree_pair_s_gc, gt_ggc_e_18VEC_tree_pair_s_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).base.vec[i0].purpose);
          gt_pch_n_9tree_node ((*x).base.vec[i0].value);
        }
      }
    }
}

void
gt_pch_nx_saved_scope (void *x_p)
{
  struct saved_scope * const x = (struct saved_scope *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11saved_scope, gt_ggc_e_11saved_scope))
    {
      gt_pch_n_24VEC_cxx_saved_binding_gc ((*x).old_bindings);
      gt_pch_n_9tree_node ((*x).old_namespace);
      gt_pch_n_9tree_node ((*x).decl_ns_list);
      gt_pch_n_9tree_node ((*x).class_name);
      gt_pch_n_9tree_node ((*x).class_type);
      gt_pch_n_9tree_node ((*x).access_specifier);
      gt_pch_n_9tree_node ((*x).function_decl);
      gt_pch_n_11VEC_tree_gc ((*x).lang_base);
      gt_pch_n_9tree_node ((*x).lang_name);
      gt_pch_n_9tree_node ((*x).template_parms);
      gt_pch_n_16cp_binding_level ((*x).x_previous_class_level);
      gt_pch_n_9tree_node ((*x).x_saved_tree);
      gt_pch_n_9tree_node ((*x).x_stmt_tree.x_cur_stmt_list);
      gt_pch_n_16cp_binding_level ((*x).class_bindings);
      gt_pch_n_16cp_binding_level ((*x).bindings);
      gt_pch_n_11saved_scope ((*x).prev);
    }
}

void
gt_pch_nx_cxx_int_tree_map (void *x_p)
{
  struct cxx_int_tree_map * const x = (struct cxx_int_tree_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16cxx_int_tree_map, gt_ggc_e_16cxx_int_tree_map))
    {
      gt_pch_n_9tree_node ((*x).to);
    }
}

void
gt_pch_nx_language_function (void *x_p)
{
  struct language_function * const x = (struct language_function *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17language_function, gt_ggc_e_17language_function))
    {
      gt_pch_n_9tree_node ((*x).base.x_stmt_tree.x_cur_stmt_list);
      gt_pch_n_9tree_node ((*x).x_cdtor_label);
      gt_pch_n_9tree_node ((*x).x_current_class_ptr);
      gt_pch_n_9tree_node ((*x).x_current_class_ref);
      gt_pch_n_9tree_node ((*x).x_eh_spec_block);
      gt_pch_n_9tree_node ((*x).x_in_charge_parm);
      gt_pch_n_9tree_node ((*x).x_vtt_parm);
      gt_pch_n_9tree_node ((*x).x_return_value);
      gt_pch_n_P17named_label_entry4htab ((*x).x_named_labels);
      gt_pch_n_16cp_binding_level ((*x).bindings);
      gt_pch_n_11VEC_tree_gc ((*x).x_local_names);
      gt_pch_n_P16cxx_int_tree_map4htab ((*x).extern_decl_map);
    }
}

void
gt_pch_nx_lang_tree_node (void *x_p)
{
  union lang_tree_node * x = (union lang_tree_node *)x_p;
  union lang_tree_node * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_14lang_tree_node, gt_ggc_e_14lang_tree_node))
   xlimit = ((union lang_tree_node *)TREE_CHAIN (&(*xlimit).generic));
  while (x != xlimit)
    {
      switch (cp_tree_node_structure (&((*x))))
        {
        case TS_CP_GENERIC:
          switch (tree_node_structure (&((*x).generic)))
            {
            case TS_BASE:
              gt_pch_n_10tree_ann_d ((*x).generic.base.ann);
              break;
            case TS_COMMON:
              gt_pch_n_10tree_ann_d ((*x).generic.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.common.chain);
              gt_pch_n_9tree_node ((*x).generic.common.type);
              break;
            case TS_INT_CST:
              gt_pch_n_10tree_ann_d ((*x).generic.int_cst.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.int_cst.common.chain);
              gt_pch_n_9tree_node ((*x).generic.int_cst.common.type);
              break;
            case TS_REAL_CST:
              gt_pch_n_10tree_ann_d ((*x).generic.real_cst.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.real_cst.common.chain);
              gt_pch_n_9tree_node ((*x).generic.real_cst.common.type);
              gt_pch_n_10real_value ((*x).generic.real_cst.real_cst_ptr);
              break;
            case TS_FIXED_CST:
              gt_pch_n_10tree_ann_d ((*x).generic.fixed_cst.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.fixed_cst.common.chain);
              gt_pch_n_9tree_node ((*x).generic.fixed_cst.common.type);
              gt_pch_n_11fixed_value ((*x).generic.fixed_cst.fixed_cst_ptr);
              break;
            case TS_VECTOR:
              gt_pch_n_10tree_ann_d ((*x).generic.vector.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.vector.common.chain);
              gt_pch_n_9tree_node ((*x).generic.vector.common.type);
              gt_pch_n_9tree_node ((*x).generic.vector.elements);
              break;
            case TS_STRING:
              gt_pch_n_10tree_ann_d ((*x).generic.string.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.string.common.chain);
              gt_pch_n_9tree_node ((*x).generic.string.common.type);
              break;
            case TS_COMPLEX:
              gt_pch_n_10tree_ann_d ((*x).generic.complex.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.complex.common.chain);
              gt_pch_n_9tree_node ((*x).generic.complex.common.type);
              gt_pch_n_9tree_node ((*x).generic.complex.real);
              gt_pch_n_9tree_node ((*x).generic.complex.imag);
              break;
            case TS_IDENTIFIER:
              gt_pch_n_10tree_ann_d ((*x).generic.identifier.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.identifier.common.chain);
              gt_pch_n_9tree_node ((*x).generic.identifier.common.type);
              gt_pch_n_S ((*x).generic.identifier.id.str);
              break;
            case TS_DECL_MINIMAL:
              gt_pch_n_10tree_ann_d ((*x).generic.decl_minimal.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.decl_minimal.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_minimal.common.type);
              gt_pch_n_9tree_node ((*x).generic.decl_minimal.name);
              gt_pch_n_9tree_node ((*x).generic.decl_minimal.context);
              break;
            case TS_DECL_COMMON:
              gt_pch_n_10tree_ann_d ((*x).generic.decl_common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.decl_common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.decl_common.common.name);
              gt_pch_n_9tree_node ((*x).generic.decl_common.common.context);
              gt_pch_n_9tree_node ((*x).generic.decl_common.size);
              gt_pch_n_9tree_node ((*x).generic.decl_common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.decl_common.initial);
              gt_pch_n_9tree_node ((*x).generic.decl_common.attributes);
              gt_pch_n_9tree_node ((*x).generic.decl_common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.decl_common.lang_specific);
              break;
            case TS_DECL_WRTL:
              gt_pch_n_10tree_ann_d ((*x).generic.decl_with_rtl.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.size);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.initial);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.decl_with_rtl.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.decl_with_rtl.rtl);
              break;
            case TS_DECL_NON_COMMON:
              gt_pch_n_10tree_ann_d ((*x).generic.decl_non_common.common.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.decl_non_common.common.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.decl_non_common.common.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.section_name);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.saved_tree);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.arguments);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.result);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.vindex);
              break;
            case TS_PARM_DECL:
              gt_pch_n_10tree_ann_d ((*x).generic.parm_decl.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.parm_decl.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.parm_decl.common.rtl);
              gt_pch_n_7rtx_def ((*x).generic.parm_decl.incoming_rtl);
              break;
            case TS_DECL_WITH_VIS:
              gt_pch_n_10tree_ann_d ((*x).generic.decl_with_vis.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.decl_with_vis.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.decl_with_vis.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.section_name);
              break;
            case TS_VAR_DECL:
              gt_pch_n_10tree_ann_d ((*x).generic.var_decl.common.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.var_decl.common.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.var_decl.common.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.section_name);
              break;
            case TS_FIELD_DECL:
              gt_pch_n_10tree_ann_d ((*x).generic.field_decl.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.size);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.initial);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.field_decl.common.lang_specific);
              gt_pch_n_9tree_node ((*x).generic.field_decl.offset);
              gt_pch_n_9tree_node ((*x).generic.field_decl.bit_field_type);
              gt_pch_n_9tree_node ((*x).generic.field_decl.qualifier);
              gt_pch_n_9tree_node ((*x).generic.field_decl.bit_offset);
              gt_pch_n_9tree_node ((*x).generic.field_decl.fcontext);
              break;
            case TS_LABEL_DECL:
              gt_pch_n_10tree_ann_d ((*x).generic.label_decl.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.label_decl.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.label_decl.common.rtl);
              break;
            case TS_RESULT_DECL:
              gt_pch_n_10tree_ann_d ((*x).generic.result_decl.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.result_decl.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.result_decl.common.rtl);
              break;
            case TS_CONST_DECL:
              gt_pch_n_10tree_ann_d ((*x).generic.const_decl.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.const_decl.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.const_decl.common.rtl);
              break;
            case TS_TYPE_DECL:
              gt_pch_n_10tree_ann_d ((*x).generic.type_decl.common.common.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.type_decl.common.common.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.type_decl.common.common.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.section_name);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.saved_tree);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.arguments);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.result);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.vindex);
              break;
            case TS_FUNCTION_DECL:
              gt_pch_n_10tree_ann_d ((*x).generic.function_decl.common.common.common.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.function_decl.common.common.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.function_decl.common.common.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.section_name);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.saved_tree);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.arguments);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.result);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.vindex);
              gt_pch_n_8function ((*x).generic.function_decl.f);
              gt_pch_n_9tree_node ((*x).generic.function_decl.function_specific_target);
              gt_pch_n_9tree_node ((*x).generic.function_decl.function_specific_optimization);
              break;
            case TS_TYPE:
              gt_pch_n_10tree_ann_d ((*x).generic.type.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.type.common.chain);
              gt_pch_n_9tree_node ((*x).generic.type.common.type);
              gt_pch_n_9tree_node ((*x).generic.type.values);
              gt_pch_n_9tree_node ((*x).generic.type.size);
              gt_pch_n_9tree_node ((*x).generic.type.size_unit);
              gt_pch_n_9tree_node ((*x).generic.type.attributes);
              gt_pch_n_9tree_node ((*x).generic.type.pointer_to);
              gt_pch_n_9tree_node ((*x).generic.type.reference_to);
              switch (debug_hooks == &sdb_debug_hooks ? 1 : debug_hooks == &dwarf2_debug_hooks ? 2 : 0)
                {
                case 0:
                  break;
                case 1:
                  gt_pch_n_S ((*x).generic.type.symtab.pointer);
                  break;
                case 2:
                  gt_pch_n_10die_struct ((*x).generic.type.symtab.die);
                  break;
                default:
                  break;
                }
              gt_pch_n_9tree_node ((*x).generic.type.name);
              gt_pch_n_9tree_node ((*x).generic.type.minval);
              gt_pch_n_9tree_node ((*x).generic.type.maxval);
              gt_pch_n_9tree_node ((*x).generic.type.next_variant);
              gt_pch_n_9tree_node ((*x).generic.type.main_variant);
              gt_pch_n_9tree_node ((*x).generic.type.binfo);
              gt_pch_n_9tree_node ((*x).generic.type.context);
              gt_pch_n_9tree_node ((*x).generic.type.canonical);
              gt_pch_n_9lang_type ((*x).generic.type.lang_specific);
              break;
            case TS_LIST:
              gt_pch_n_10tree_ann_d ((*x).generic.list.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.list.common.chain);
              gt_pch_n_9tree_node ((*x).generic.list.common.type);
              gt_pch_n_9tree_node ((*x).generic.list.purpose);
              gt_pch_n_9tree_node ((*x).generic.list.value);
              break;
            case TS_VEC:
              gt_pch_n_10tree_ann_d ((*x).generic.vec.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.vec.common.chain);
              gt_pch_n_9tree_node ((*x).generic.vec.common.type);
              {
                size_t i1;
                size_t l1 = (size_t)(TREE_VEC_LENGTH ((tree)&((*x).generic.vec)));
                for (i1 = 0; i1 != l1; i1++) {
                  gt_pch_n_9tree_node ((*x).generic.vec.a[i1]);
                }
              }
              break;
            case TS_EXP:
              gt_pch_n_10tree_ann_d ((*x).generic.exp.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.exp.common.chain);
              gt_pch_n_9tree_node ((*x).generic.exp.common.type);
              gt_pch_n_9tree_node ((*x).generic.exp.block);
              switch (TREE_CODE ((tree) &(*x)))
                {
                default:
                  {
                    size_t i2;
                    size_t l2 = (size_t)(TREE_OPERAND_LENGTH ((tree) &(*x)));
                    for (i2 = 0; i2 != l2; i2++) {
                      gt_pch_n_9tree_node ((*x).generic.exp.operands[i2]);
                    }
                  }
                  break;
                }
              break;
            case TS_SSA_NAME:
              gt_pch_n_10tree_ann_d ((*x).generic.ssa_name.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.ssa_name.common.chain);
              gt_pch_n_9tree_node ((*x).generic.ssa_name.common.type);
              gt_pch_n_9tree_node ((*x).generic.ssa_name.var);
              gt_pch_n_18gimple_statement_d ((*x).generic.ssa_name.def_stmt);
              gt_pch_n_12ptr_info_def ((*x).generic.ssa_name.ptr_info);
              gt_pch_n_9tree_node ((*x).generic.ssa_name.value_handle);
              break;
            case TS_BLOCK:
              gt_pch_n_10tree_ann_d ((*x).generic.block.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.block.common.chain);
              gt_pch_n_9tree_node ((*x).generic.block.common.type);
              gt_pch_n_9tree_node ((*x).generic.block.vars);
              gt_pch_n_11VEC_tree_gc ((*x).generic.block.nonlocalized_vars);
              gt_pch_n_9tree_node ((*x).generic.block.subblocks);
              gt_pch_n_9tree_node ((*x).generic.block.supercontext);
              gt_pch_n_9tree_node ((*x).generic.block.abstract_origin);
              gt_pch_n_9tree_node ((*x).generic.block.fragment_origin);
              gt_pch_n_9tree_node ((*x).generic.block.fragment_chain);
              break;
            case TS_BINFO:
              gt_pch_n_10tree_ann_d ((*x).generic.binfo.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.binfo.common.chain);
              gt_pch_n_9tree_node ((*x).generic.binfo.common.type);
              gt_pch_n_9tree_node ((*x).generic.binfo.offset);
              gt_pch_n_9tree_node ((*x).generic.binfo.vtable);
              gt_pch_n_9tree_node ((*x).generic.binfo.virtuals);
              gt_pch_n_9tree_node ((*x).generic.binfo.vptr_field);
              gt_pch_n_11VEC_tree_gc ((*x).generic.binfo.base_accesses);
              gt_pch_n_9tree_node ((*x).generic.binfo.inheritance);
              gt_pch_n_9tree_node ((*x).generic.binfo.vtt_subvtt);
              gt_pch_n_9tree_node ((*x).generic.binfo.vtt_vptr);
              {
                size_t i3;
                size_t l3 = (size_t)(((*x).generic.binfo.base_binfos.base).num);
                for (i3 = 0; i3 != l3; i3++) {
                  gt_pch_n_9tree_node ((*x).generic.binfo.base_binfos.base.vec[i3]);
                }
              }
              break;
            case TS_STATEMENT_LIST:
              gt_pch_n_10tree_ann_d ((*x).generic.stmt_list.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.stmt_list.common.chain);
              gt_pch_n_9tree_node ((*x).generic.stmt_list.common.type);
              gt_pch_n_24tree_statement_list_node ((*x).generic.stmt_list.head);
              gt_pch_n_24tree_statement_list_node ((*x).generic.stmt_list.tail);
              break;
            case TS_CONSTRUCTOR:
              gt_pch_n_10tree_ann_d ((*x).generic.constructor.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.constructor.common.chain);
              gt_pch_n_9tree_node ((*x).generic.constructor.common.type);
              gt_pch_n_22VEC_constructor_elt_gc ((*x).generic.constructor.elts);
              break;
            case TS_MEMORY_TAG:
              gt_pch_n_10tree_ann_d ((*x).generic.mtag.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.mtag.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.mtag.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.mtag.common.name);
              gt_pch_n_9tree_node ((*x).generic.mtag.common.context);
              break;
            case TS_OMP_CLAUSE:
              gt_pch_n_10tree_ann_d ((*x).generic.omp_clause.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.omp_clause.common.chain);
              gt_pch_n_9tree_node ((*x).generic.omp_clause.common.type);
              gt_pch_n_12gimple_seq_d ((*x).generic.omp_clause.gimple_reduction_init);
              gt_pch_n_12gimple_seq_d ((*x).generic.omp_clause.gimple_reduction_merge);
              {
                size_t i4;
                size_t l4 = (size_t)(omp_clause_num_ops[OMP_CLAUSE_CODE ((tree)&((*x).generic.omp_clause))]);
                for (i4 = 0; i4 != l4; i4++) {
                  gt_pch_n_9tree_node ((*x).generic.omp_clause.ops[i4]);
                }
              }
              break;
            case TS_MEMORY_PARTITION_TAG:
              gt_pch_n_10tree_ann_d ((*x).generic.mpt.common.common.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.mpt.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.mpt.common.common.common.type);
              gt_pch_n_9tree_node ((*x).generic.mpt.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.mpt.common.common.context);
              gt_pch_n_15bitmap_head_def ((*x).generic.mpt.symbols);
              break;
            case TS_OPTIMIZATION:
              gt_pch_n_10tree_ann_d ((*x).generic.optimization.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.optimization.common.chain);
              gt_pch_n_9tree_node ((*x).generic.optimization.common.type);
              break;
            case TS_TARGET_OPTION:
              gt_pch_n_10tree_ann_d ((*x).generic.target_option.common.base.ann);
              gt_pch_n_9tree_node ((*x).generic.target_option.common.chain);
              gt_pch_n_9tree_node ((*x).generic.target_option.common.type);
              break;
            default:
              break;
            }
          break;
        case TS_CP_TPI:
          gt_pch_n_10tree_ann_d ((*x).tpi.common.base.ann);
          gt_pch_n_9tree_node ((*x).tpi.common.chain);
          gt_pch_n_9tree_node ((*x).tpi.common.type);
          gt_pch_n_9tree_node ((*x).tpi.decl);
          break;
        case TS_CP_PTRMEM:
          gt_pch_n_10tree_ann_d ((*x).ptrmem.common.base.ann);
          gt_pch_n_9tree_node ((*x).ptrmem.common.chain);
          gt_pch_n_9tree_node ((*x).ptrmem.common.type);
          gt_pch_n_7rtx_def ((*x).ptrmem.rtl);
          gt_pch_n_9tree_node ((*x).ptrmem.member);
          break;
        case TS_CP_OVERLOAD:
          gt_pch_n_10tree_ann_d ((*x).overload.common.base.ann);
          gt_pch_n_9tree_node ((*x).overload.common.chain);
          gt_pch_n_9tree_node ((*x).overload.common.type);
          gt_pch_n_9tree_node ((*x).overload.function);
          break;
        case TS_CP_BASELINK:
          gt_pch_n_10tree_ann_d ((*x).baselink.common.base.ann);
          gt_pch_n_9tree_node ((*x).baselink.common.chain);
          gt_pch_n_9tree_node ((*x).baselink.common.type);
          gt_pch_n_9tree_node ((*x).baselink.binfo);
          gt_pch_n_9tree_node ((*x).baselink.functions);
          gt_pch_n_9tree_node ((*x).baselink.access_binfo);
          break;
        case TS_CP_DEFAULT_ARG:
          gt_pch_n_10tree_ann_d ((*x).default_arg.common.base.ann);
          gt_pch_n_9tree_node ((*x).default_arg.common.chain);
          gt_pch_n_9tree_node ((*x).default_arg.common.type);
          gt_pch_n_14cp_token_cache ((*x).default_arg.tokens);
          gt_pch_n_11VEC_tree_gc ((*x).default_arg.instantiations);
          break;
        case TS_CP_IDENTIFIER:
          gt_pch_n_10tree_ann_d ((*x).identifier.c_common.common.base.ann);
          gt_pch_n_9tree_node ((*x).identifier.c_common.common.chain);
          gt_pch_n_9tree_node ((*x).identifier.c_common.common.type);
          gt_pch_n_S ((*x).identifier.c_common.node.ident.str);
          switch (CPP_HASHNODE_VALUE_IDX (((*x).identifier.c_common.node)))
            {
            case NTV_MACRO:
              gt_pch_n_9cpp_macro ((*x).identifier.c_common.node.value.macro);
              break;
            case NTV_ANSWER:
              gt_pch_n_6answer ((*x).identifier.c_common.node.value.answers);
              break;
            case NTV_BUILTIN:
              break;
            case NTV_ARGUMENT:
              break;
            default:
              break;
            }
          gt_pch_n_11cxx_binding ((*x).identifier.namespace_bindings);
          gt_pch_n_11cxx_binding ((*x).identifier.bindings);
          gt_pch_n_9tree_node ((*x).identifier.class_template_info);
          gt_pch_n_9tree_node ((*x).identifier.label_value);
          break;
        case TS_CP_STATIC_ASSERT:
          gt_pch_n_10tree_ann_d ((*x).static_assertion.common.base.ann);
          gt_pch_n_9tree_node ((*x).static_assertion.common.chain);
          gt_pch_n_9tree_node ((*x).static_assertion.common.type);
          gt_pch_n_9tree_node ((*x).static_assertion.condition);
          gt_pch_n_9tree_node ((*x).static_assertion.message);
          break;
        case TS_CP_ARGUMENT_PACK_SELECT:
          gt_pch_n_10tree_ann_d ((*x).argument_pack_select.common.base.ann);
          gt_pch_n_9tree_node ((*x).argument_pack_select.common.chain);
          gt_pch_n_9tree_node ((*x).argument_pack_select.common.type);
          gt_pch_n_9tree_node ((*x).argument_pack_select.argument_pack);
          break;
        case TS_CP_TRAIT_EXPR:
          gt_pch_n_10tree_ann_d ((*x).trait_expression.common.base.ann);
          gt_pch_n_9tree_node ((*x).trait_expression.common.chain);
          gt_pch_n_9tree_node ((*x).trait_expression.common.type);
          gt_pch_n_9tree_node ((*x).trait_expression.type1);
          gt_pch_n_9tree_node ((*x).trait_expression.type2);
          break;
        default:
          break;
        }
      x = ((union lang_tree_node *)TREE_CHAIN (&(*x).generic));
    }
}

void
gt_pch_nx_lang_decl (void *x_p)
{
  struct lang_decl * const x = (struct lang_decl *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9lang_decl, gt_ggc_e_9lang_decl))
    {
      switch (((*x).decl_flags).u1sel)
        {
        case 0:
          gt_pch_n_9tree_node ((*x).decl_flags.u.template_info);
          break;
        case 1:
          gt_pch_n_16cp_binding_level ((*x).decl_flags.u.level);
          break;
        default:
          break;
        }
      switch (((*x).decl_flags).u2sel)
        {
        case 0:
          gt_pch_n_9tree_node ((*x).decl_flags.u2.access);
          break;
        case 1:
          break;
        default:
          break;
        }
      switch (((*x)).decl_flags.can_be_full)
        {
        case 1:
          gt_pch_n_9tree_node ((*x).u.f.befriending_classes);
          gt_pch_n_9tree_node ((*x).u.f.context);
          switch ((*x).decl_flags.thunk_p)
            {
            case 0:
              gt_pch_n_9tree_node ((*x).u.f.u5.cloned_function);
              break;
            case 1:
              break;
            default:
              break;
            }
          switch (((*x).u.f).u3sel + ((*x).u.f).pending_inline_p)
            {
            case 0:
              gt_pch_n_18sorted_fields_type ((*x).u.f.u.sorted_fields);
              gt_pch_note_reorder ((*x).u.f.u.sorted_fields, (*x).u.f.u.sorted_fields, resort_sorted_fields);
              break;
            case 2:
              gt_pch_n_14cp_token_cache ((*x).u.f.u.pending_inline_info);
              break;
            case 1:
              gt_pch_n_17language_function ((*x).u.f.u.saved_language_function);
              break;
            default:
              break;
            }
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_lang_type (void *x_p)
{
  struct lang_type * const x = (struct lang_type *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9lang_type, gt_ggc_e_9lang_type))
    {
      switch (((*x).u).h.is_lang_type_class)
        {
        case 1:
          gt_pch_n_9tree_node ((*x).u.c.primary_base);
          gt_pch_n_18VEC_tree_pair_s_gc ((*x).u.c.vcall_indices);
          gt_pch_n_9tree_node ((*x).u.c.vtables);
          gt_pch_n_9tree_node ((*x).u.c.typeinfo_var);
          gt_pch_n_11VEC_tree_gc ((*x).u.c.vbases);
          gt_pch_n_15binding_table_s ((*x).u.c.nested_udts);
          gt_pch_n_9tree_node ((*x).u.c.as_base);
          gt_pch_n_11VEC_tree_gc ((*x).u.c.pure_virtuals);
          gt_pch_n_9tree_node ((*x).u.c.friend_classes);
          gt_pch_n_11VEC_tree_gc ((*x).u.c.methods);
          gt_pch_note_reorder ((*x).u.c.methods, (*x).u.c.methods, resort_type_method_vec);
          gt_pch_n_9tree_node ((*x).u.c.key_method);
          gt_pch_n_9tree_node ((*x).u.c.decl_list);
          gt_pch_n_9tree_node ((*x).u.c.template_info);
          gt_pch_n_9tree_node ((*x).u.c.befriending_classes);
          gt_pch_n_9tree_node ((*x).u.c.objc_info);
          break;
        case 0:
          gt_pch_n_9tree_node ((*x).u.ptrmem.record);
          break;
        default:
          break;
        }
    }
}

void
gt_pch_n_P16cxx_int_tree_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P16cxx_int_tree_map4htab, gt_e_P16cxx_int_tree_map4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_16cxx_int_tree_map ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P16cxx_int_tree_map4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_28VEC_deferred_access_check_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_deferred_access_check_gc * const x ATTRIBUTE_UNUSED = (struct VEC_deferred_access_check_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].binfo), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].decl), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].diag_decl), cookie);
    }
  }
}

void
gt_pch_p_11tinst_level (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tinst_level * const x ATTRIBUTE_UNUSED = (struct tinst_level *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
}

void
gt_pch_p_18VEC_tree_pair_s_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_tree_pair_s_gc * const x ATTRIBUTE_UNUSED = (struct VEC_tree_pair_s_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].purpose), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].value), cookie);
    }
  }
}

void
gt_pch_p_11saved_scope (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct saved_scope * const x ATTRIBUTE_UNUSED = (struct saved_scope *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).old_bindings), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).old_namespace), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).decl_ns_list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).class_name), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).class_type), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).access_specifier), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).function_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).lang_base), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).lang_name), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).template_parms), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_previous_class_level), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_saved_tree), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_stmt_tree.x_cur_stmt_list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).class_bindings), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).bindings), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
}

void
gt_pch_p_16cxx_int_tree_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cxx_int_tree_map * const x ATTRIBUTE_UNUSED = (struct cxx_int_tree_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).to), cookie);
}

void
gt_pch_p_17language_function (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct language_function * const x ATTRIBUTE_UNUSED = (struct language_function *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.x_stmt_tree.x_cur_stmt_list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_cdtor_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_current_class_ptr), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_current_class_ref), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_eh_spec_block), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_in_charge_parm), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_vtt_parm), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_return_value), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_named_labels), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).bindings), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_local_names), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).extern_decl_map), cookie);
}

void
gt_pch_p_14lang_tree_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  union lang_tree_node * const x ATTRIBUTE_UNUSED = (union lang_tree_node *)x_p;
  switch (cp_tree_node_structure (&((*x))))
    {
    case TS_CP_GENERIC:
      switch (tree_node_structure (&((*x).generic)))
        {
        case TS_BASE:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.base.ann), cookie);
          break;
        case TS_COMMON:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.common.type), cookie);
          break;
        case TS_INT_CST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.int_cst.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.int_cst.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.int_cst.common.type), cookie);
          break;
        case TS_REAL_CST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.real_cst.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.real_cst.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.real_cst.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.real_cst.real_cst_ptr), cookie);
          break;
        case TS_FIXED_CST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.fixed_cst.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.fixed_cst.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.fixed_cst.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.fixed_cst.fixed_cst_ptr), cookie);
          break;
        case TS_VECTOR:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.vector.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.vector.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.vector.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.vector.elements), cookie);
          break;
        case TS_STRING:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.string.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.string.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.string.common.type), cookie);
          break;
        case TS_COMPLEX:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.complex.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.complex.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.complex.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.complex.real), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.complex.imag), cookie);
          break;
        case TS_IDENTIFIER:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.identifier.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.identifier.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.identifier.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.identifier.id.str), cookie);
          break;
        case TS_DECL_MINIMAL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.context), cookie);
          break;
        case TS_DECL_COMMON:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.lang_specific), cookie);
          break;
        case TS_DECL_WRTL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.rtl), cookie);
          break;
        case TS_DECL_NON_COMMON:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.section_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.saved_tree), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.arguments), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.result), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.vindex), cookie);
          break;
        case TS_PARM_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.incoming_rtl), cookie);
          break;
        case TS_DECL_WITH_VIS:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.section_name), cookie);
          break;
        case TS_VAR_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.section_name), cookie);
          break;
        case TS_FIELD_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.offset), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.bit_field_type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.qualifier), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.bit_offset), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.fcontext), cookie);
          break;
        case TS_LABEL_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.rtl), cookie);
          break;
        case TS_RESULT_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.rtl), cookie);
          break;
        case TS_CONST_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.rtl), cookie);
          break;
        case TS_TYPE_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.section_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.saved_tree), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.arguments), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.result), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.vindex), cookie);
          break;
        case TS_FUNCTION_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.section_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.saved_tree), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.arguments), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.result), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.vindex), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.f), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.function_specific_target), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.function_specific_optimization), cookie);
          break;
        case TS_TYPE:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.values), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.pointer_to), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.reference_to), cookie);
          switch (debug_hooks == &sdb_debug_hooks ? 1 : debug_hooks == &dwarf2_debug_hooks ? 2 : 0)
            {
            case 0:
              break;
            case 1:
              if ((void *)(x) == this_obj)
                op (&((*x).generic.type.symtab.pointer), cookie);
              break;
            case 2:
              if ((void *)(x) == this_obj)
                op (&((*x).generic.type.symtab.die), cookie);
              break;
            default:
              break;
            }
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.minval), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.maxval), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.next_variant), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.main_variant), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.binfo), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.canonical), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type.lang_specific), cookie);
          break;
        case TS_LIST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.purpose), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.value), cookie);
          break;
        case TS_VEC:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.vec.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.vec.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.vec.common.type), cookie);
          {
            size_t i1;
            size_t l1 = (size_t)(TREE_VEC_LENGTH ((tree)&((*x).generic.vec)));
            for (i1 = 0; i1 != l1; i1++) {
              if ((void *)(x) == this_obj)
                op (&((*x).generic.vec.a[i1]), cookie);
            }
          }
          break;
        case TS_EXP:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.exp.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.exp.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.exp.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.exp.block), cookie);
          switch (TREE_CODE ((tree) &(*x)))
            {
            default:
              {
                size_t i2;
                size_t l2 = (size_t)(TREE_OPERAND_LENGTH ((tree) &(*x)));
                for (i2 = 0; i2 != l2; i2++) {
                  if ((void *)(x) == this_obj)
                    op (&((*x).generic.exp.operands[i2]), cookie);
                }
              }
              break;
            }
          break;
        case TS_SSA_NAME:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.var), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.def_stmt), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.ptr_info), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.value_handle), cookie);
          break;
        case TS_BLOCK:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.vars), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.nonlocalized_vars), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.subblocks), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.supercontext), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.fragment_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.fragment_chain), cookie);
          break;
        case TS_BINFO:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.offset), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.vtable), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.virtuals), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.vptr_field), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.base_accesses), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.inheritance), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.vtt_subvtt), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.vtt_vptr), cookie);
          {
            size_t i3;
            size_t l3 = (size_t)(((*x).generic.binfo.base_binfos.base).num);
            for (i3 = 0; i3 != l3; i3++) {
              if ((void *)(x) == this_obj)
                op (&((*x).generic.binfo.base_binfos.base.vec[i3]), cookie);
            }
          }
          break;
        case TS_STATEMENT_LIST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.stmt_list.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.stmt_list.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.stmt_list.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.stmt_list.head), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.stmt_list.tail), cookie);
          break;
        case TS_CONSTRUCTOR:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.constructor.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.constructor.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.constructor.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.constructor.elts), cookie);
          break;
        case TS_MEMORY_TAG:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mtag.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mtag.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mtag.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mtag.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mtag.common.context), cookie);
          break;
        case TS_OMP_CLAUSE:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.omp_clause.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.omp_clause.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.omp_clause.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.omp_clause.gimple_reduction_init), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.omp_clause.gimple_reduction_merge), cookie);
          {
            size_t i4;
            size_t l4 = (size_t)(omp_clause_num_ops[OMP_CLAUSE_CODE ((tree)&((*x).generic.omp_clause))]);
            for (i4 = 0; i4 != l4; i4++) {
              if ((void *)(x) == this_obj)
                op (&((*x).generic.omp_clause.ops[i4]), cookie);
            }
          }
          break;
        case TS_MEMORY_PARTITION_TAG:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mpt.common.common.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mpt.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mpt.common.common.common.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mpt.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mpt.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.mpt.symbols), cookie);
          break;
        case TS_OPTIMIZATION:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.optimization.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.optimization.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.optimization.common.type), cookie);
          break;
        case TS_TARGET_OPTION:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.target_option.common.base.ann), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.target_option.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.target_option.common.type), cookie);
          break;
        default:
          break;
        }
      break;
    case TS_CP_TPI:
      if ((void *)(x) == this_obj)
        op (&((*x).tpi.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).tpi.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).tpi.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).tpi.decl), cookie);
      break;
    case TS_CP_PTRMEM:
      if ((void *)(x) == this_obj)
        op (&((*x).ptrmem.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).ptrmem.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).ptrmem.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).ptrmem.rtl), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).ptrmem.member), cookie);
      break;
    case TS_CP_OVERLOAD:
      if ((void *)(x) == this_obj)
        op (&((*x).overload.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).overload.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).overload.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).overload.function), cookie);
      break;
    case TS_CP_BASELINK:
      if ((void *)(x) == this_obj)
        op (&((*x).baselink.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).baselink.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).baselink.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).baselink.binfo), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).baselink.functions), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).baselink.access_binfo), cookie);
      break;
    case TS_CP_DEFAULT_ARG:
      if ((void *)(x) == this_obj)
        op (&((*x).default_arg.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).default_arg.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).default_arg.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).default_arg.tokens), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).default_arg.instantiations), cookie);
      break;
    case TS_CP_IDENTIFIER:
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.c_common.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.c_common.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.c_common.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.c_common.node.ident.str), cookie);
      switch (CPP_HASHNODE_VALUE_IDX (((*x).identifier.c_common.node)))
        {
        case NTV_MACRO:
          if ((void *)(x) == this_obj)
            op (&((*x).identifier.c_common.node.value.macro), cookie);
          break;
        case NTV_ANSWER:
          if ((void *)(x) == this_obj)
            op (&((*x).identifier.c_common.node.value.answers), cookie);
          break;
        case NTV_BUILTIN:
          break;
        case NTV_ARGUMENT:
          break;
        default:
          break;
        }
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.namespace_bindings), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.bindings), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.class_template_info), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.label_value), cookie);
      break;
    case TS_CP_STATIC_ASSERT:
      if ((void *)(x) == this_obj)
        op (&((*x).static_assertion.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).static_assertion.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).static_assertion.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).static_assertion.condition), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).static_assertion.message), cookie);
      break;
    case TS_CP_ARGUMENT_PACK_SELECT:
      if ((void *)(x) == this_obj)
        op (&((*x).argument_pack_select.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).argument_pack_select.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).argument_pack_select.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).argument_pack_select.argument_pack), cookie);
      break;
    case TS_CP_TRAIT_EXPR:
      if ((void *)(x) == this_obj)
        op (&((*x).trait_expression.common.base.ann), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).trait_expression.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).trait_expression.common.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).trait_expression.type1), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).trait_expression.type2), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_9lang_decl (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct lang_decl * const x ATTRIBUTE_UNUSED = (struct lang_decl *)x_p;
  switch (((*x).decl_flags).u1sel)
    {
    case 0:
      if ((void *)(x) == this_obj)
        op (&((*x).decl_flags.u.template_info), cookie);
      break;
    case 1:
      if ((void *)(x) == this_obj)
        op (&((*x).decl_flags.u.level), cookie);
      break;
    default:
      break;
    }
  switch (((*x).decl_flags).u2sel)
    {
    case 0:
      if ((void *)(x) == this_obj)
        op (&((*x).decl_flags.u2.access), cookie);
      break;
    case 1:
      break;
    default:
      break;
    }
  switch (((*x)).decl_flags.can_be_full)
    {
    case 1:
      if ((void *)(x) == this_obj)
        op (&((*x).u.f.befriending_classes), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.f.context), cookie);
      switch ((*x).decl_flags.thunk_p)
        {
        case 0:
          if ((void *)(x) == this_obj)
            op (&((*x).u.f.u5.cloned_function), cookie);
          break;
        case 1:
          break;
        default:
          break;
        }
      switch (((*x).u.f).u3sel + ((*x).u.f).pending_inline_p)
        {
        case 0:
          if ((void *)(x) == this_obj)
            op (&((*x).u.f.u.sorted_fields), cookie);
          break;
        case 2:
          if ((void *)(x) == this_obj)
            op (&((*x).u.f.u.pending_inline_info), cookie);
          break;
        case 1:
          if ((void *)(x) == this_obj)
            op (&((*x).u.f.u.saved_language_function), cookie);
          break;
        default:
          break;
        }
      break;
    default:
      break;
    }
}

void
gt_pch_p_9lang_type (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct lang_type * const x ATTRIBUTE_UNUSED = (struct lang_type *)x_p;
  switch (((*x).u).h.is_lang_type_class)
    {
    case 1:
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.primary_base), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.vcall_indices), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.vtables), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.typeinfo_var), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.vbases), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.nested_udts), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.as_base), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.pure_virtuals), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.friend_classes), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.methods), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.key_method), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.decl_list), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.template_info), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.befriending_classes), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.c.objc_info), cookie);
      break;
    case 0:
      if ((void *)(x) == this_obj)
        op (&((*x).u.ptrmem.record), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_P16cxx_int_tree_map4htab (ATTRIBUTE_UNUSED void *this_obj,
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

const struct ggc_root_tab gt_ggc_r_gt_cp_tree_h[] = {
  {
    &list_hash_table,
    1,
    sizeof (list_hash_table),
    &gt_ggc_m_P9tree_node4htab,
    &gt_pch_n_P9tree_node4htab
  },
  {
    &cplus_array_htab,
    1,
    sizeof (cplus_array_htab),
    &gt_ggc_m_P9tree_node4htab,
    &gt_pch_n_P9tree_node4htab
  },
  {
    &unemitted_tinfo_decls,
    1,
    sizeof (unemitted_tinfo_decls),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &deferred_mark_used_calls,
    1,
    sizeof (deferred_mark_used_calls),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &assignment_operator_name_info[0].identifier,
    1 * ((int) MAX_TREE_CODES),
    sizeof (assignment_operator_name_info[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &assignment_operator_name_info[0].name,
    1, 
    sizeof (assignment_operator_name_info),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &assignment_operator_name_info[0].mangled_name,
    1, 
    sizeof (assignment_operator_name_info),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &operator_name_info[0].identifier,
    1 * ((int) MAX_TREE_CODES),
    sizeof (operator_name_info[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &operator_name_info[0].name,
    1, 
    sizeof (operator_name_info),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &operator_name_info[0].mangled_name,
    1, 
    sizeof (operator_name_info),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &static_aggregates,
    1,
    sizeof (static_aggregates),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &local_classes,
    1,
    sizeof (local_classes),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &integer_three_node,
    1,
    sizeof (integer_three_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &integer_two_node,
    1,
    sizeof (integer_two_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &scope_chain,
    1,
    sizeof (scope_chain),
    &gt_ggc_mx_saved_scope,
    &gt_pch_nx_saved_scope
  },
  {
    &cp_global_trees[0],
    1 * (CPTI_MAX),
    sizeof (cp_global_trees[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_cp_tree_h[] = {
  { &assignment_operator_name_info, 1, sizeof (assignment_operator_name_info), NULL, NULL },
  { &operator_name_info, 1, sizeof (operator_name_info), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

