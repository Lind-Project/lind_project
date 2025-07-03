/* Type information for dwarf2out.c.
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
gt_ggc_mx_var_loc_list_def (void *x_p)
{
  struct var_loc_list_def * const x = (struct var_loc_list_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_12var_loc_node ((*x).first);
    }
}

void
gt_ggc_mx_var_loc_node (void *x_p)
{
  struct var_loc_node * x = (struct var_loc_node *)x_p;
  struct var_loc_node * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_7rtx_def ((*x).var_loc_note);
      gt_ggc_m_S ((*x).label);
      gt_ggc_m_S ((*x).section_label);
      gt_ggc_m_12var_loc_node ((*x).next);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_limbo_die_struct (void *x_p)
{
  struct limbo_die_struct * const x = (struct limbo_die_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_10die_struct ((*x).die);
      gt_ggc_m_9tree_node ((*x).created_for);
      gt_ggc_m_16limbo_die_struct ((*x).next);
    }
}

void
gt_ggc_mx_VEC_pubname_entry_gc (void *x_p)
{
  struct VEC_pubname_entry_gc * const x = (struct VEC_pubname_entry_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_10die_struct ((*x).base.vec[i0].die);
          gt_ggc_m_S ((*x).base.vec[i0].name);
        }
      }
    }
}

void
gt_ggc_mx_VEC_dw_attr_node_gc (void *x_p)
{
  struct VEC_dw_attr_node_gc * const x = (struct VEC_dw_attr_node_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          switch (((*x).base.vec[i0].dw_attr_val).val_class)
            {
            case dw_val_class_addr:
              gt_ggc_m_7rtx_def ((*x).base.vec[i0].dw_attr_val.v.val_addr);
              break;
            case dw_val_class_offset:
              break;
            case dw_val_class_loc_list:
              gt_ggc_m_18dw_loc_list_struct ((*x).base.vec[i0].dw_attr_val.v.val_loc_list);
              break;
            case dw_val_class_loc:
              gt_ggc_m_19dw_loc_descr_struct ((*x).base.vec[i0].dw_attr_val.v.val_loc);
              break;
            default:
              break;
            case dw_val_class_unsigned_const:
              break;
            case dw_val_class_long_long:
              break;
            case dw_val_class_vec:
              if ((*x).base.vec[i0].dw_attr_val.v.val_vec.array != NULL) {
                size_t i1;
                for (i1 = 0; i1 != (size_t)(((*x).base.vec[i0].dw_attr_val.v.val_vec).length); i1++) {
                }
                ggc_mark ((*x).base.vec[i0].dw_attr_val.v.val_vec.array);
              }
              break;
            case dw_val_class_die_ref:
              gt_ggc_m_10die_struct ((*x).base.vec[i0].dw_attr_val.v.val_die_ref.die);
              break;
            case dw_val_class_fde_ref:
              break;
            case dw_val_class_str:
              gt_ggc_m_20indirect_string_node ((*x).base.vec[i0].dw_attr_val.v.val_str);
              break;
            case dw_val_class_lbl_id:
              gt_ggc_m_S ((*x).base.vec[i0].dw_attr_val.v.val_lbl_id);
              break;
            case dw_val_class_flag:
              break;
            case dw_val_class_file:
              gt_ggc_m_15dwarf_file_data ((*x).base.vec[i0].dw_attr_val.v.val_file);
              break;
            }
        }
      }
    }
}

void
gt_ggc_mx_dw_ranges_by_label_struct (void *x_p)
{
  struct dw_ranges_by_label_struct * const x = (struct dw_ranges_by_label_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_S ((*x).begin);
      gt_ggc_m_S ((*x).end);
    }
}

void
gt_ggc_mx_dw_ranges_struct (void *x_p)
{
  struct dw_ranges_struct * const x = (struct dw_ranges_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_dw_separate_line_info_struct (void *x_p)
{
  struct dw_separate_line_info_struct * const x = (struct dw_separate_line_info_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_dw_line_info_struct (void *x_p)
{
  struct dw_line_info_struct * const x = (struct dw_line_info_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_VEC_deferred_locations_gc (void *x_p)
{
  struct VEC_deferred_locations_gc * const x = (struct VEC_deferred_locations_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).base.vec[i0].variable);
          gt_ggc_m_10die_struct ((*x).base.vec[i0].die);
        }
      }
    }
}

void
gt_ggc_mx_dw_loc_list_struct (void *x_p)
{
  struct dw_loc_list_struct * const x = (struct dw_loc_list_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18dw_loc_list_struct ((*x).dw_loc_next);
      gt_ggc_m_S ((*x).begin);
      gt_ggc_m_S ((*x).end);
      gt_ggc_m_S ((*x).ll_symbol);
      gt_ggc_m_S ((*x).section);
      gt_ggc_m_19dw_loc_descr_struct ((*x).expr);
    }
}

void
gt_ggc_mx_dwarf_file_data (void *x_p)
{
  struct dwarf_file_data * const x = (struct dwarf_file_data *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_S ((*x).filename);
    }
}

void
gt_ggc_mx_queued_reg_save (void *x_p)
{
  struct queued_reg_save * const x = (struct queued_reg_save *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15queued_reg_save ((*x).next);
      gt_ggc_m_7rtx_def ((*x).reg);
      gt_ggc_m_7rtx_def ((*x).saved_reg);
    }
}

void
gt_ggc_mx_indirect_string_node (void *x_p)
{
  struct indirect_string_node * const x = (struct indirect_string_node *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_S ((*x).str);
      gt_ggc_m_S ((*x).label);
    }
}

void
gt_ggc_mx_dw_loc_descr_struct (void *x_p)
{
  struct dw_loc_descr_struct * const x = (struct dw_loc_descr_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_19dw_loc_descr_struct ((*x).dw_loc_next);
      switch (((*x).dw_loc_oprnd1).val_class)
        {
        case dw_val_class_addr:
          gt_ggc_m_7rtx_def ((*x).dw_loc_oprnd1.v.val_addr);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          gt_ggc_m_18dw_loc_list_struct ((*x).dw_loc_oprnd1.v.val_loc_list);
          break;
        case dw_val_class_loc:
          gt_ggc_m_19dw_loc_descr_struct ((*x).dw_loc_oprnd1.v.val_loc);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_long_long:
          break;
        case dw_val_class_vec:
          if ((*x).dw_loc_oprnd1.v.val_vec.array != NULL) {
            size_t i0;
            for (i0 = 0; i0 != (size_t)(((*x).dw_loc_oprnd1.v.val_vec).length); i0++) {
            }
            ggc_mark ((*x).dw_loc_oprnd1.v.val_vec.array);
          }
          break;
        case dw_val_class_die_ref:
          gt_ggc_m_10die_struct ((*x).dw_loc_oprnd1.v.val_die_ref.die);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          gt_ggc_m_20indirect_string_node ((*x).dw_loc_oprnd1.v.val_str);
          break;
        case dw_val_class_lbl_id:
          gt_ggc_m_S ((*x).dw_loc_oprnd1.v.val_lbl_id);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          gt_ggc_m_15dwarf_file_data ((*x).dw_loc_oprnd1.v.val_file);
          break;
        }
      switch (((*x).dw_loc_oprnd2).val_class)
        {
        case dw_val_class_addr:
          gt_ggc_m_7rtx_def ((*x).dw_loc_oprnd2.v.val_addr);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          gt_ggc_m_18dw_loc_list_struct ((*x).dw_loc_oprnd2.v.val_loc_list);
          break;
        case dw_val_class_loc:
          gt_ggc_m_19dw_loc_descr_struct ((*x).dw_loc_oprnd2.v.val_loc);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_long_long:
          break;
        case dw_val_class_vec:
          if ((*x).dw_loc_oprnd2.v.val_vec.array != NULL) {
            size_t i1;
            for (i1 = 0; i1 != (size_t)(((*x).dw_loc_oprnd2.v.val_vec).length); i1++) {
            }
            ggc_mark ((*x).dw_loc_oprnd2.v.val_vec.array);
          }
          break;
        case dw_val_class_die_ref:
          gt_ggc_m_10die_struct ((*x).dw_loc_oprnd2.v.val_die_ref.die);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          gt_ggc_m_20indirect_string_node ((*x).dw_loc_oprnd2.v.val_str);
          break;
        case dw_val_class_lbl_id:
          gt_ggc_m_S ((*x).dw_loc_oprnd2.v.val_lbl_id);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          gt_ggc_m_15dwarf_file_data ((*x).dw_loc_oprnd2.v.val_file);
          break;
        }
    }
}

void
gt_ggc_mx_dw_fde_struct (void *x_p)
{
  struct dw_fde_struct * const x = (struct dw_fde_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).decl);
      gt_ggc_m_S ((*x).dw_fde_begin);
      gt_ggc_m_S ((*x).dw_fde_current_label);
      gt_ggc_m_S ((*x).dw_fde_end);
      gt_ggc_m_S ((*x).dw_fde_hot_section_label);
      gt_ggc_m_S ((*x).dw_fde_hot_section_end_label);
      gt_ggc_m_S ((*x).dw_fde_unlikely_section_label);
      gt_ggc_m_S ((*x).dw_fde_unlikely_section_end_label);
      gt_ggc_m_13dw_cfi_struct ((*x).dw_fde_cfi);
    }
}

void
gt_ggc_mx_dw_cfi_struct (void *x_p)
{
  struct dw_cfi_struct * const x = (struct dw_cfi_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_13dw_cfi_struct ((*x).dw_cfi_next);
      switch (dw_cfi_oprnd1_desc (((*x)).dw_cfi_opc))
        {
        case dw_cfi_oprnd_reg_num:
          break;
        case dw_cfi_oprnd_offset:
          break;
        case dw_cfi_oprnd_addr:
          gt_ggc_m_S ((*x).dw_cfi_oprnd1.dw_cfi_addr);
          break;
        case dw_cfi_oprnd_loc:
          gt_ggc_m_19dw_loc_descr_struct ((*x).dw_cfi_oprnd1.dw_cfi_loc);
          break;
        default:
          break;
        }
      switch (dw_cfi_oprnd2_desc (((*x)).dw_cfi_opc))
        {
        case dw_cfi_oprnd_reg_num:
          break;
        case dw_cfi_oprnd_offset:
          break;
        case dw_cfi_oprnd_addr:
          gt_ggc_m_S ((*x).dw_cfi_oprnd2.dw_cfi_addr);
          break;
        case dw_cfi_oprnd_loc:
          gt_ggc_m_19dw_loc_descr_struct ((*x).dw_cfi_oprnd2.dw_cfi_loc);
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_die_struct (void *x_p)
{
  struct die_struct * x = (struct die_struct *)x_p;
  struct die_struct * xlimit = x;
  if (!ggc_test_and_set_mark (xlimit))
    return;
  do
   xlimit = ((*xlimit).die_sib);
  while (ggc_test_and_set_mark (xlimit));
  do
    {
      gt_ggc_m_S ((*x).die_symbol);
      gt_ggc_m_19VEC_dw_attr_node_gc ((*x).die_attr);
      gt_ggc_m_10die_struct ((*x).die_parent);
      gt_ggc_m_10die_struct ((*x).die_child);
      gt_ggc_m_10die_struct ((*x).die_sib);
      gt_ggc_m_10die_struct ((*x).die_definition);
      x = ((*x).die_sib);
    }
  while (x != xlimit);
}

void
gt_ggc_m_P16var_loc_list_def4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_16var_loc_list_def ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P10die_struct4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_10die_struct ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P15dwarf_file_data4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_15dwarf_file_data ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P20indirect_string_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_20indirect_string_node ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_pch_nx_var_loc_list_def (void *x_p)
{
  struct var_loc_list_def * const x = (struct var_loc_list_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16var_loc_list_def, gt_ggc_e_16var_loc_list_def))
    {
      gt_pch_n_12var_loc_node ((*x).first);
    }
}

void
gt_pch_nx_var_loc_node (void *x_p)
{
  struct var_loc_node * x = (struct var_loc_node *)x_p;
  struct var_loc_node * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_12var_loc_node, gt_ggc_e_12var_loc_node))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_7rtx_def ((*x).var_loc_note);
      gt_pch_n_S ((*x).label);
      gt_pch_n_S ((*x).section_label);
      gt_pch_n_12var_loc_node ((*x).next);
      x = ((*x).next);
    }
}

void
gt_pch_nx_limbo_die_struct (void *x_p)
{
  struct limbo_die_struct * const x = (struct limbo_die_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16limbo_die_struct, gt_ggc_e_16limbo_die_struct))
    {
      gt_pch_n_10die_struct ((*x).die);
      gt_pch_n_9tree_node ((*x).created_for);
      gt_pch_n_16limbo_die_struct ((*x).next);
    }
}

void
gt_pch_nx_VEC_pubname_entry_gc (void *x_p)
{
  struct VEC_pubname_entry_gc * const x = (struct VEC_pubname_entry_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_20VEC_pubname_entry_gc, gt_ggc_e_20VEC_pubname_entry_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_10die_struct ((*x).base.vec[i0].die);
          gt_pch_n_S ((*x).base.vec[i0].name);
        }
      }
    }
}

void
gt_pch_nx_VEC_dw_attr_node_gc (void *x_p)
{
  struct VEC_dw_attr_node_gc * const x = (struct VEC_dw_attr_node_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_19VEC_dw_attr_node_gc, gt_ggc_e_19VEC_dw_attr_node_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          switch (((*x).base.vec[i0].dw_attr_val).val_class)
            {
            case dw_val_class_addr:
              gt_pch_n_7rtx_def ((*x).base.vec[i0].dw_attr_val.v.val_addr);
              break;
            case dw_val_class_offset:
              break;
            case dw_val_class_loc_list:
              gt_pch_n_18dw_loc_list_struct ((*x).base.vec[i0].dw_attr_val.v.val_loc_list);
              break;
            case dw_val_class_loc:
              gt_pch_n_19dw_loc_descr_struct ((*x).base.vec[i0].dw_attr_val.v.val_loc);
              break;
            default:
              break;
            case dw_val_class_unsigned_const:
              break;
            case dw_val_class_long_long:
              break;
            case dw_val_class_vec:
              if ((*x).base.vec[i0].dw_attr_val.v.val_vec.array != NULL) {
                size_t i1;
                for (i1 = 0; i1 != (size_t)(((*x).base.vec[i0].dw_attr_val.v.val_vec).length); i1++) {
                }
                gt_pch_note_object ((*x).base.vec[i0].dw_attr_val.v.val_vec.array, x, gt_pch_p_19VEC_dw_attr_node_gc, gt_types_enum_last);
              }
              break;
            case dw_val_class_die_ref:
              gt_pch_n_10die_struct ((*x).base.vec[i0].dw_attr_val.v.val_die_ref.die);
              break;
            case dw_val_class_fde_ref:
              break;
            case dw_val_class_str:
              gt_pch_n_20indirect_string_node ((*x).base.vec[i0].dw_attr_val.v.val_str);
              break;
            case dw_val_class_lbl_id:
              gt_pch_n_S ((*x).base.vec[i0].dw_attr_val.v.val_lbl_id);
              break;
            case dw_val_class_flag:
              break;
            case dw_val_class_file:
              gt_pch_n_15dwarf_file_data ((*x).base.vec[i0].dw_attr_val.v.val_file);
              break;
            }
        }
      }
    }
}

void
gt_pch_nx_dw_ranges_by_label_struct (void *x_p)
{
  struct dw_ranges_by_label_struct * const x = (struct dw_ranges_by_label_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_25dw_ranges_by_label_struct, gt_ggc_e_25dw_ranges_by_label_struct))
    {
      gt_pch_n_S ((*x).begin);
      gt_pch_n_S ((*x).end);
    }
}

void
gt_pch_nx_dw_ranges_struct (void *x_p)
{
  struct dw_ranges_struct * const x = (struct dw_ranges_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16dw_ranges_struct, gt_ggc_e_16dw_ranges_struct))
    {
    }
}

void
gt_pch_nx_dw_separate_line_info_struct (void *x_p)
{
  struct dw_separate_line_info_struct * const x = (struct dw_separate_line_info_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_28dw_separate_line_info_struct, gt_ggc_e_28dw_separate_line_info_struct))
    {
    }
}

void
gt_pch_nx_dw_line_info_struct (void *x_p)
{
  struct dw_line_info_struct * const x = (struct dw_line_info_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_19dw_line_info_struct, gt_ggc_e_19dw_line_info_struct))
    {
    }
}

void
gt_pch_nx_VEC_deferred_locations_gc (void *x_p)
{
  struct VEC_deferred_locations_gc * const x = (struct VEC_deferred_locations_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_25VEC_deferred_locations_gc, gt_ggc_e_25VEC_deferred_locations_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).base.vec[i0].variable);
          gt_pch_n_10die_struct ((*x).base.vec[i0].die);
        }
      }
    }
}

void
gt_pch_nx_dw_loc_list_struct (void *x_p)
{
  struct dw_loc_list_struct * const x = (struct dw_loc_list_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18dw_loc_list_struct, gt_ggc_e_18dw_loc_list_struct))
    {
      gt_pch_n_18dw_loc_list_struct ((*x).dw_loc_next);
      gt_pch_n_S ((*x).begin);
      gt_pch_n_S ((*x).end);
      gt_pch_n_S ((*x).ll_symbol);
      gt_pch_n_S ((*x).section);
      gt_pch_n_19dw_loc_descr_struct ((*x).expr);
    }
}

void
gt_pch_nx_dwarf_file_data (void *x_p)
{
  struct dwarf_file_data * const x = (struct dwarf_file_data *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15dwarf_file_data, gt_ggc_e_15dwarf_file_data))
    {
      gt_pch_n_S ((*x).filename);
    }
}

void
gt_pch_nx_queued_reg_save (void *x_p)
{
  struct queued_reg_save * const x = (struct queued_reg_save *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15queued_reg_save, gt_ggc_e_15queued_reg_save))
    {
      gt_pch_n_15queued_reg_save ((*x).next);
      gt_pch_n_7rtx_def ((*x).reg);
      gt_pch_n_7rtx_def ((*x).saved_reg);
    }
}

void
gt_pch_nx_indirect_string_node (void *x_p)
{
  struct indirect_string_node * const x = (struct indirect_string_node *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_20indirect_string_node, gt_ggc_e_20indirect_string_node))
    {
      gt_pch_n_S ((*x).str);
      gt_pch_n_S ((*x).label);
    }
}

void
gt_pch_nx_dw_loc_descr_struct (void *x_p)
{
  struct dw_loc_descr_struct * const x = (struct dw_loc_descr_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_19dw_loc_descr_struct, gt_ggc_e_19dw_loc_descr_struct))
    {
      gt_pch_n_19dw_loc_descr_struct ((*x).dw_loc_next);
      switch (((*x).dw_loc_oprnd1).val_class)
        {
        case dw_val_class_addr:
          gt_pch_n_7rtx_def ((*x).dw_loc_oprnd1.v.val_addr);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          gt_pch_n_18dw_loc_list_struct ((*x).dw_loc_oprnd1.v.val_loc_list);
          break;
        case dw_val_class_loc:
          gt_pch_n_19dw_loc_descr_struct ((*x).dw_loc_oprnd1.v.val_loc);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_long_long:
          break;
        case dw_val_class_vec:
          if ((*x).dw_loc_oprnd1.v.val_vec.array != NULL) {
            size_t i0;
            for (i0 = 0; i0 != (size_t)(((*x).dw_loc_oprnd1.v.val_vec).length); i0++) {
            }
            gt_pch_note_object ((*x).dw_loc_oprnd1.v.val_vec.array, x, gt_pch_p_19dw_loc_descr_struct, gt_types_enum_last);
          }
          break;
        case dw_val_class_die_ref:
          gt_pch_n_10die_struct ((*x).dw_loc_oprnd1.v.val_die_ref.die);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          gt_pch_n_20indirect_string_node ((*x).dw_loc_oprnd1.v.val_str);
          break;
        case dw_val_class_lbl_id:
          gt_pch_n_S ((*x).dw_loc_oprnd1.v.val_lbl_id);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          gt_pch_n_15dwarf_file_data ((*x).dw_loc_oprnd1.v.val_file);
          break;
        }
      switch (((*x).dw_loc_oprnd2).val_class)
        {
        case dw_val_class_addr:
          gt_pch_n_7rtx_def ((*x).dw_loc_oprnd2.v.val_addr);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          gt_pch_n_18dw_loc_list_struct ((*x).dw_loc_oprnd2.v.val_loc_list);
          break;
        case dw_val_class_loc:
          gt_pch_n_19dw_loc_descr_struct ((*x).dw_loc_oprnd2.v.val_loc);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_long_long:
          break;
        case dw_val_class_vec:
          if ((*x).dw_loc_oprnd2.v.val_vec.array != NULL) {
            size_t i1;
            for (i1 = 0; i1 != (size_t)(((*x).dw_loc_oprnd2.v.val_vec).length); i1++) {
            }
            gt_pch_note_object ((*x).dw_loc_oprnd2.v.val_vec.array, x, gt_pch_p_19dw_loc_descr_struct, gt_types_enum_last);
          }
          break;
        case dw_val_class_die_ref:
          gt_pch_n_10die_struct ((*x).dw_loc_oprnd2.v.val_die_ref.die);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          gt_pch_n_20indirect_string_node ((*x).dw_loc_oprnd2.v.val_str);
          break;
        case dw_val_class_lbl_id:
          gt_pch_n_S ((*x).dw_loc_oprnd2.v.val_lbl_id);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          gt_pch_n_15dwarf_file_data ((*x).dw_loc_oprnd2.v.val_file);
          break;
        }
    }
}

void
gt_pch_nx_dw_fde_struct (void *x_p)
{
  struct dw_fde_struct * const x = (struct dw_fde_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13dw_fde_struct, gt_ggc_e_13dw_fde_struct))
    {
      gt_pch_n_9tree_node ((*x).decl);
      gt_pch_n_S ((*x).dw_fde_begin);
      gt_pch_n_S ((*x).dw_fde_current_label);
      gt_pch_n_S ((*x).dw_fde_end);
      gt_pch_n_S ((*x).dw_fde_hot_section_label);
      gt_pch_n_S ((*x).dw_fde_hot_section_end_label);
      gt_pch_n_S ((*x).dw_fde_unlikely_section_label);
      gt_pch_n_S ((*x).dw_fde_unlikely_section_end_label);
      gt_pch_n_13dw_cfi_struct ((*x).dw_fde_cfi);
    }
}

void
gt_pch_nx_dw_cfi_struct (void *x_p)
{
  struct dw_cfi_struct * const x = (struct dw_cfi_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13dw_cfi_struct, gt_ggc_e_13dw_cfi_struct))
    {
      gt_pch_n_13dw_cfi_struct ((*x).dw_cfi_next);
      switch (dw_cfi_oprnd1_desc (((*x)).dw_cfi_opc))
        {
        case dw_cfi_oprnd_reg_num:
          break;
        case dw_cfi_oprnd_offset:
          break;
        case dw_cfi_oprnd_addr:
          gt_pch_n_S ((*x).dw_cfi_oprnd1.dw_cfi_addr);
          break;
        case dw_cfi_oprnd_loc:
          gt_pch_n_19dw_loc_descr_struct ((*x).dw_cfi_oprnd1.dw_cfi_loc);
          break;
        default:
          break;
        }
      switch (dw_cfi_oprnd2_desc (((*x)).dw_cfi_opc))
        {
        case dw_cfi_oprnd_reg_num:
          break;
        case dw_cfi_oprnd_offset:
          break;
        case dw_cfi_oprnd_addr:
          gt_pch_n_S ((*x).dw_cfi_oprnd2.dw_cfi_addr);
          break;
        case dw_cfi_oprnd_loc:
          gt_pch_n_19dw_loc_descr_struct ((*x).dw_cfi_oprnd2.dw_cfi_loc);
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_die_struct (void *x_p)
{
  struct die_struct * x = (struct die_struct *)x_p;
  struct die_struct * xlimit = x;
  if (!gt_pch_note_object (xlimit, xlimit, gt_pch_p_10die_struct, gt_ggc_e_10die_struct))
    return;
  do
   xlimit = ((*xlimit).die_sib);
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_10die_struct, gt_ggc_e_10die_struct));
  do
    {
      gt_pch_n_S ((*x).die_symbol);
      gt_pch_n_19VEC_dw_attr_node_gc ((*x).die_attr);
      gt_pch_n_10die_struct ((*x).die_parent);
      gt_pch_n_10die_struct ((*x).die_child);
      gt_pch_n_10die_struct ((*x).die_sib);
      gt_pch_n_10die_struct ((*x).die_definition);
      x = ((*x).die_sib);
    }
  while (x != xlimit);
}

void
gt_pch_n_P16var_loc_list_def4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P16var_loc_list_def4htab, gt_e_P16var_loc_list_def4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_16var_loc_list_def ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P16var_loc_list_def4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P10die_struct4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P10die_struct4htab, gt_e_P10die_struct4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_10die_struct ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P10die_struct4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P15dwarf_file_data4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P15dwarf_file_data4htab, gt_e_P15dwarf_file_data4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_15dwarf_file_data ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P15dwarf_file_data4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P20indirect_string_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P20indirect_string_node4htab, gt_e_P20indirect_string_node4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_20indirect_string_node ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P20indirect_string_node4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_16var_loc_list_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct var_loc_list_def * const x ATTRIBUTE_UNUSED = (struct var_loc_list_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).first), cookie);
}

void
gt_pch_p_12var_loc_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct var_loc_node * const x ATTRIBUTE_UNUSED = (struct var_loc_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).var_loc_note), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).section_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_16limbo_die_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct limbo_die_struct * const x ATTRIBUTE_UNUSED = (struct limbo_die_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).die), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).created_for), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_20VEC_pubname_entry_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_pubname_entry_gc * const x ATTRIBUTE_UNUSED = (struct VEC_pubname_entry_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].die), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].name), cookie);
    }
  }
}

void
gt_pch_p_19VEC_dw_attr_node_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_dw_attr_node_gc * const x ATTRIBUTE_UNUSED = (struct VEC_dw_attr_node_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      switch (((*x).base.vec[i0].dw_attr_val).val_class)
        {
        case dw_val_class_addr:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].dw_attr_val.v.val_addr), cookie);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].dw_attr_val.v.val_loc_list), cookie);
          break;
        case dw_val_class_loc:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].dw_attr_val.v.val_loc), cookie);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_long_long:
          break;
        case dw_val_class_vec:
          if ((*x).base.vec[i0].dw_attr_val.v.val_vec.array != NULL) {
            size_t i1;
            for (i1 = 0; i1 != (size_t)(((*x).base.vec[i0].dw_attr_val.v.val_vec).length); i1++) {
            }
            if ((void *)(x) == this_obj)
              op (&((*x).base.vec[i0].dw_attr_val.v.val_vec.array), cookie);
          }
          break;
        case dw_val_class_die_ref:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].dw_attr_val.v.val_die_ref.die), cookie);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].dw_attr_val.v.val_str), cookie);
          break;
        case dw_val_class_lbl_id:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].dw_attr_val.v.val_lbl_id), cookie);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].dw_attr_val.v.val_file), cookie);
          break;
        }
    }
  }
}

void
gt_pch_p_25dw_ranges_by_label_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_ranges_by_label_struct * const x ATTRIBUTE_UNUSED = (struct dw_ranges_by_label_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).begin), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).end), cookie);
}

void
gt_pch_p_16dw_ranges_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_ranges_struct * const x ATTRIBUTE_UNUSED = (struct dw_ranges_struct *)x_p;
}

void
gt_pch_p_28dw_separate_line_info_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_separate_line_info_struct * const x ATTRIBUTE_UNUSED = (struct dw_separate_line_info_struct *)x_p;
}

void
gt_pch_p_19dw_line_info_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_line_info_struct * const x ATTRIBUTE_UNUSED = (struct dw_line_info_struct *)x_p;
}

void
gt_pch_p_25VEC_deferred_locations_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_deferred_locations_gc * const x ATTRIBUTE_UNUSED = (struct VEC_deferred_locations_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].variable), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].die), cookie);
    }
  }
}

void
gt_pch_p_18dw_loc_list_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_loc_list_struct * const x ATTRIBUTE_UNUSED = (struct dw_loc_list_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).dw_loc_next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).begin), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).end), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).ll_symbol), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).section), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).expr), cookie);
}

void
gt_pch_p_15dwarf_file_data (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dwarf_file_data * const x ATTRIBUTE_UNUSED = (struct dwarf_file_data *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).filename), cookie);
}

void
gt_pch_p_15queued_reg_save (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct queued_reg_save * const x ATTRIBUTE_UNUSED = (struct queued_reg_save *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).reg), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).saved_reg), cookie);
}

void
gt_pch_p_20indirect_string_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct indirect_string_node * const x ATTRIBUTE_UNUSED = (struct indirect_string_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).str), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).label), cookie);
}

void
gt_pch_p_19dw_loc_descr_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_loc_descr_struct * const x ATTRIBUTE_UNUSED = (struct dw_loc_descr_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).dw_loc_next), cookie);
  switch (((*x).dw_loc_oprnd1).val_class)
    {
    case dw_val_class_addr:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_addr), cookie);
      break;
    case dw_val_class_offset:
      break;
    case dw_val_class_loc_list:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_loc_list), cookie);
      break;
    case dw_val_class_loc:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_loc), cookie);
      break;
    default:
      break;
    case dw_val_class_unsigned_const:
      break;
    case dw_val_class_long_long:
      break;
    case dw_val_class_vec:
      if ((*x).dw_loc_oprnd1.v.val_vec.array != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x).dw_loc_oprnd1.v.val_vec).length); i0++) {
        }
        if ((void *)(x) == this_obj)
          op (&((*x).dw_loc_oprnd1.v.val_vec.array), cookie);
      }
      break;
    case dw_val_class_die_ref:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_die_ref.die), cookie);
      break;
    case dw_val_class_fde_ref:
      break;
    case dw_val_class_str:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_str), cookie);
      break;
    case dw_val_class_lbl_id:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_lbl_id), cookie);
      break;
    case dw_val_class_flag:
      break;
    case dw_val_class_file:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_file), cookie);
      break;
    }
  switch (((*x).dw_loc_oprnd2).val_class)
    {
    case dw_val_class_addr:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_addr), cookie);
      break;
    case dw_val_class_offset:
      break;
    case dw_val_class_loc_list:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_loc_list), cookie);
      break;
    case dw_val_class_loc:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_loc), cookie);
      break;
    default:
      break;
    case dw_val_class_unsigned_const:
      break;
    case dw_val_class_long_long:
      break;
    case dw_val_class_vec:
      if ((*x).dw_loc_oprnd2.v.val_vec.array != NULL) {
        size_t i1;
        for (i1 = 0; i1 != (size_t)(((*x).dw_loc_oprnd2.v.val_vec).length); i1++) {
        }
        if ((void *)(x) == this_obj)
          op (&((*x).dw_loc_oprnd2.v.val_vec.array), cookie);
      }
      break;
    case dw_val_class_die_ref:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_die_ref.die), cookie);
      break;
    case dw_val_class_fde_ref:
      break;
    case dw_val_class_str:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_str), cookie);
      break;
    case dw_val_class_lbl_id:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_lbl_id), cookie);
      break;
    case dw_val_class_flag:
      break;
    case dw_val_class_file:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_file), cookie);
      break;
    }
}

void
gt_pch_p_13dw_fde_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_fde_struct * const x ATTRIBUTE_UNUSED = (struct dw_fde_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_begin), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_current_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_end), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_hot_section_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_hot_section_end_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_unlikely_section_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_unlikely_section_end_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_cfi), cookie);
}

void
gt_pch_p_13dw_cfi_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_cfi_struct * const x ATTRIBUTE_UNUSED = (struct dw_cfi_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).dw_cfi_next), cookie);
  switch (dw_cfi_oprnd1_desc (((*x)).dw_cfi_opc))
    {
    case dw_cfi_oprnd_reg_num:
      break;
    case dw_cfi_oprnd_offset:
      break;
    case dw_cfi_oprnd_addr:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_cfi_oprnd1.dw_cfi_addr), cookie);
      break;
    case dw_cfi_oprnd_loc:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_cfi_oprnd1.dw_cfi_loc), cookie);
      break;
    default:
      break;
    }
  switch (dw_cfi_oprnd2_desc (((*x)).dw_cfi_opc))
    {
    case dw_cfi_oprnd_reg_num:
      break;
    case dw_cfi_oprnd_offset:
      break;
    case dw_cfi_oprnd_addr:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_cfi_oprnd2.dw_cfi_addr), cookie);
      break;
    case dw_cfi_oprnd_loc:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_cfi_oprnd2.dw_cfi_loc), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_10die_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct die_struct * const x ATTRIBUTE_UNUSED = (struct die_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).die_symbol), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).die_attr), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).die_parent), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).die_child), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).die_sib), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).die_definition), cookie);
}

void
gt_pch_p_P16var_loc_list_def4htab (ATTRIBUTE_UNUSED void *this_obj,
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
gt_pch_p_P10die_struct4htab (ATTRIBUTE_UNUSED void *this_obj,
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
gt_pch_p_P15dwarf_file_data4htab (ATTRIBUTE_UNUSED void *this_obj,
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
gt_pch_p_P20indirect_string_node4htab (ATTRIBUTE_UNUSED void *this_obj,
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

static void gt_ggc_ma_ranges_by_label (void *);
static void
gt_ggc_ma_ranges_by_label (ATTRIBUTE_UNUSED void *x_p)
{
  if (ranges_by_label != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(ranges_by_label_allocated); i0++) {
      gt_ggc_m_S (ranges_by_label[i0].begin);
      gt_ggc_m_S (ranges_by_label[i0].end);
    }
    ggc_mark (ranges_by_label);
  }
}

static void gt_pch_pa_ranges_by_label
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_ranges_by_label (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (ranges_by_label != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(ranges_by_label_allocated); i0++) {
      if ((void *)(ranges_by_label) == this_obj)
        op (&(ranges_by_label[i0].begin), cookie);
      if ((void *)(ranges_by_label) == this_obj)
        op (&(ranges_by_label[i0].end), cookie);
    }
    if ((void *)(&ranges_by_label) == this_obj)
      op (&(ranges_by_label), cookie);
  }
}

static void gt_pch_na_ranges_by_label (void *);
static void
gt_pch_na_ranges_by_label (ATTRIBUTE_UNUSED void *x_p)
{
  if (ranges_by_label != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(ranges_by_label_allocated); i1++) {
      gt_pch_n_S (ranges_by_label[i1].begin);
      gt_pch_n_S (ranges_by_label[i1].end);
    }
    gt_pch_note_object (ranges_by_label, &ranges_by_label, gt_pch_pa_ranges_by_label, gt_types_enum_last);
  }
}

static void gt_ggc_ma_ranges_table (void *);
static void
gt_ggc_ma_ranges_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (ranges_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(ranges_table_allocated); i0++) {
    }
    ggc_mark (ranges_table);
  }
}

static void gt_pch_pa_ranges_table
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_ranges_table (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (ranges_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(ranges_table_allocated); i0++) {
    }
    if ((void *)(&ranges_table) == this_obj)
      op (&(ranges_table), cookie);
  }
}

static void gt_pch_na_ranges_table (void *);
static void
gt_pch_na_ranges_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (ranges_table != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(ranges_table_allocated); i1++) {
    }
    gt_pch_note_object (ranges_table, &ranges_table, gt_pch_pa_ranges_table, gt_types_enum_last);
  }
}

static void gt_ggc_ma_arange_table (void *);
static void
gt_ggc_ma_arange_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (arange_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(arange_table_allocated); i0++) {
      gt_ggc_m_10die_struct (arange_table[i0]);
    }
    ggc_mark (arange_table);
  }
}

static void gt_pch_pa_arange_table
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_arange_table (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (arange_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(arange_table_allocated); i0++) {
      if ((void *)(arange_table) == this_obj)
        op (&(arange_table[i0]), cookie);
    }
    if ((void *)(&arange_table) == this_obj)
      op (&(arange_table), cookie);
  }
}

static void gt_pch_na_arange_table (void *);
static void
gt_pch_na_arange_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (arange_table != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(arange_table_allocated); i1++) {
      gt_pch_n_10die_struct (arange_table[i1]);
    }
    gt_pch_note_object (arange_table, &arange_table, gt_pch_pa_arange_table, gt_types_enum_last);
  }
}

static void gt_ggc_ma_separate_line_info_table (void *);
static void
gt_ggc_ma_separate_line_info_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (separate_line_info_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(separate_line_info_table_allocated); i0++) {
    }
    ggc_mark (separate_line_info_table);
  }
}

static void gt_pch_pa_separate_line_info_table
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_separate_line_info_table (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (separate_line_info_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(separate_line_info_table_allocated); i0++) {
    }
    if ((void *)(&separate_line_info_table) == this_obj)
      op (&(separate_line_info_table), cookie);
  }
}

static void gt_pch_na_separate_line_info_table (void *);
static void
gt_pch_na_separate_line_info_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (separate_line_info_table != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(separate_line_info_table_allocated); i1++) {
    }
    gt_pch_note_object (separate_line_info_table, &separate_line_info_table, gt_pch_pa_separate_line_info_table, gt_types_enum_last);
  }
}

static void gt_ggc_ma_line_info_table (void *);
static void
gt_ggc_ma_line_info_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (line_info_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(line_info_table_allocated); i0++) {
    }
    ggc_mark (line_info_table);
  }
}

static void gt_pch_pa_line_info_table
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_line_info_table (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (line_info_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(line_info_table_allocated); i0++) {
    }
    if ((void *)(&line_info_table) == this_obj)
      op (&(line_info_table), cookie);
  }
}

static void gt_pch_na_line_info_table (void *);
static void
gt_pch_na_line_info_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (line_info_table != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(line_info_table_allocated); i1++) {
    }
    gt_pch_note_object (line_info_table, &line_info_table, gt_pch_pa_line_info_table, gt_types_enum_last);
  }
}

static void gt_ggc_ma_abbrev_die_table (void *);
static void
gt_ggc_ma_abbrev_die_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (abbrev_die_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(abbrev_die_table_allocated); i0++) {
      gt_ggc_m_10die_struct (abbrev_die_table[i0]);
    }
    ggc_mark (abbrev_die_table);
  }
}

static void gt_pch_pa_abbrev_die_table
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_abbrev_die_table (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (abbrev_die_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(abbrev_die_table_allocated); i0++) {
      if ((void *)(abbrev_die_table) == this_obj)
        op (&(abbrev_die_table[i0]), cookie);
    }
    if ((void *)(&abbrev_die_table) == this_obj)
      op (&(abbrev_die_table), cookie);
  }
}

static void gt_pch_na_abbrev_die_table (void *);
static void
gt_pch_na_abbrev_die_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (abbrev_die_table != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(abbrev_die_table_allocated); i1++) {
      gt_pch_n_10die_struct (abbrev_die_table[i1]);
    }
    gt_pch_note_object (abbrev_die_table, &abbrev_die_table, gt_pch_pa_abbrev_die_table, gt_types_enum_last);
  }
}

static void gt_ggc_ma_fde_table (void *);
static void
gt_ggc_ma_fde_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (fde_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(fde_table_allocated); i0++) {
      gt_ggc_m_9tree_node (fde_table[i0].decl);
      gt_ggc_m_S (fde_table[i0].dw_fde_begin);
      gt_ggc_m_S (fde_table[i0].dw_fde_current_label);
      gt_ggc_m_S (fde_table[i0].dw_fde_end);
      gt_ggc_m_S (fde_table[i0].dw_fde_hot_section_label);
      gt_ggc_m_S (fde_table[i0].dw_fde_hot_section_end_label);
      gt_ggc_m_S (fde_table[i0].dw_fde_unlikely_section_label);
      gt_ggc_m_S (fde_table[i0].dw_fde_unlikely_section_end_label);
      gt_ggc_m_13dw_cfi_struct (fde_table[i0].dw_fde_cfi);
    }
    ggc_mark (fde_table);
  }
}

static void gt_pch_pa_fde_table
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_fde_table (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (fde_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(fde_table_allocated); i0++) {
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].decl), cookie);
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].dw_fde_begin), cookie);
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].dw_fde_current_label), cookie);
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].dw_fde_end), cookie);
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].dw_fde_hot_section_label), cookie);
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].dw_fde_hot_section_end_label), cookie);
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].dw_fde_unlikely_section_label), cookie);
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].dw_fde_unlikely_section_end_label), cookie);
      if ((void *)(fde_table) == this_obj)
        op (&(fde_table[i0].dw_fde_cfi), cookie);
    }
    if ((void *)(&fde_table) == this_obj)
      op (&(fde_table), cookie);
  }
}

static void gt_pch_na_fde_table (void *);
static void
gt_pch_na_fde_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (fde_table != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(fde_table_allocated); i1++) {
      gt_pch_n_9tree_node (fde_table[i1].decl);
      gt_pch_n_S (fde_table[i1].dw_fde_begin);
      gt_pch_n_S (fde_table[i1].dw_fde_current_label);
      gt_pch_n_S (fde_table[i1].dw_fde_end);
      gt_pch_n_S (fde_table[i1].dw_fde_hot_section_label);
      gt_pch_n_S (fde_table[i1].dw_fde_hot_section_end_label);
      gt_pch_n_S (fde_table[i1].dw_fde_unlikely_section_label);
      gt_pch_n_S (fde_table[i1].dw_fde_unlikely_section_end_label);
      gt_pch_n_13dw_cfi_struct (fde_table[i1].dw_fde_cfi);
    }
    gt_pch_note_object (fde_table, &fde_table, gt_pch_pa_fde_table, gt_types_enum_last);
  }
}

const struct ggc_root_tab gt_ggc_r_gt_dwarf2out_h[] = {
  {
    &file_table_last_lookup,
    1,
    sizeof (file_table_last_lookup),
    &gt_ggc_mx_dwarf_file_data,
    &gt_pch_nx_dwarf_file_data
  },
  {
    &last_emitted_file,
    1,
    sizeof (last_emitted_file),
    &gt_ggc_mx_dwarf_file_data,
    &gt_pch_nx_dwarf_file_data
  },
  {
    &ranges_by_label,
    1,
    sizeof (ranges_by_label),
    &gt_ggc_ma_ranges_by_label,
    &gt_pch_na_ranges_by_label
  },
  {
    &ranges_table,
    1,
    sizeof (ranges_table),
    &gt_ggc_ma_ranges_table,
    &gt_pch_na_ranges_table
  },
  {
    &arange_table,
    1,
    sizeof (arange_table),
    &gt_ggc_ma_arange_table,
    &gt_pch_na_arange_table
  },
  {
    &pubtype_table,
    1,
    sizeof (pubtype_table),
    &gt_ggc_mx_VEC_pubname_entry_gc,
    &gt_pch_nx_VEC_pubname_entry_gc
  },
  {
    &pubname_table,
    1,
    sizeof (pubname_table),
    &gt_ggc_mx_VEC_pubname_entry_gc,
    &gt_pch_nx_VEC_pubname_entry_gc
  },
  {
    &separate_line_info_table,
    1,
    sizeof (separate_line_info_table),
    &gt_ggc_ma_separate_line_info_table,
    &gt_pch_na_separate_line_info_table
  },
  {
    &line_info_table,
    1,
    sizeof (line_info_table),
    &gt_ggc_ma_line_info_table,
    &gt_pch_na_line_info_table
  },
  {
    &abbrev_die_table,
    1,
    sizeof (abbrev_die_table),
    &gt_ggc_ma_abbrev_die_table,
    &gt_pch_na_abbrev_die_table
  },
  {
    &decl_loc_table,
    1,
    sizeof (decl_loc_table),
    &gt_ggc_m_P16var_loc_list_def4htab,
    &gt_pch_n_P16var_loc_list_def4htab
  },
  {
    &common_block_die_table,
    1,
    sizeof (common_block_die_table),
    &gt_ggc_m_P10die_struct4htab,
    &gt_pch_n_P10die_struct4htab
  },
  {
    &decl_die_table,
    1,
    sizeof (decl_die_table),
    &gt_ggc_m_P10die_struct4htab,
    &gt_pch_n_P10die_struct4htab
  },
  {
    &file_table,
    1,
    sizeof (file_table),
    &gt_ggc_m_P15dwarf_file_data4htab,
    &gt_pch_n_P15dwarf_file_data4htab
  },
  {
    &limbo_die_list,
    1,
    sizeof (limbo_die_list),
    &gt_ggc_mx_limbo_die_struct,
    &gt_pch_nx_limbo_die_struct
  },
  {
    &comp_unit_die,
    1,
    sizeof (comp_unit_die),
    &gt_ggc_mx_die_struct,
    &gt_pch_nx_die_struct
  },
  {
    &deferred_locations_list,
    1,
    sizeof (deferred_locations_list),
    &gt_ggc_mx_VEC_deferred_locations_gc,
    &gt_pch_nx_VEC_deferred_locations_gc
  },
  {
    &regs_saved_in_regs[0].orig_reg,
    1 * (4),
    sizeof (regs_saved_in_regs[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &regs_saved_in_regs[0].saved_in_reg,
    1 * (4),
    sizeof (regs_saved_in_regs[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &queued_reg_saves,
    1,
    sizeof (queued_reg_saves),
    &gt_ggc_mx_queued_reg_save,
    &gt_pch_nx_queued_reg_save
  },
  {
    &cold_text_section,
    1,
    sizeof (cold_text_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_str_hash,
    1,
    sizeof (debug_str_hash),
    &gt_ggc_m_P20indirect_string_node4htab,
    &gt_pch_n_P20indirect_string_node4htab
  },
  {
    &cie_cfi_head,
    1,
    sizeof (cie_cfi_head),
    &gt_ggc_mx_dw_cfi_struct,
    &gt_pch_nx_dw_cfi_struct
  },
  {
    &fde_table,
    1,
    sizeof (fde_table),
    &gt_ggc_ma_fde_table,
    &gt_pch_na_fde_table
  },
  {
    &debug_frame_section,
    1,
    sizeof (debug_frame_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_ranges_section,
    1,
    sizeof (debug_ranges_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_str_section,
    1,
    sizeof (debug_str_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_pubtypes_section,
    1,
    sizeof (debug_pubtypes_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_pubnames_section,
    1,
    sizeof (debug_pubnames_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_loc_section,
    1,
    sizeof (debug_loc_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_line_section,
    1,
    sizeof (debug_line_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_macinfo_section,
    1,
    sizeof (debug_macinfo_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_aranges_section,
    1,
    sizeof (debug_aranges_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_abbrev_section,
    1,
    sizeof (debug_abbrev_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &debug_info_section,
    1,
    sizeof (debug_info_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &decl_scope_table,
    1,
    sizeof (decl_scope_table),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &incomplete_types,
    1,
    sizeof (incomplete_types),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &used_rtx_array,
    1,
    sizeof (used_rtx_array),
    &gt_ggc_mx_VEC_rtx_gc,
    &gt_pch_nx_VEC_rtx_gc
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_dwarf2out_h[] = {
  { &label_num, 1, sizeof (label_num), NULL, NULL },
  { &loclabel_num, 1, sizeof (loclabel_num), NULL, NULL },
  { &have_location_lists, 1, sizeof (have_location_lists), NULL, NULL },
  { &ranges_by_label_in_use, 1, sizeof (ranges_by_label_in_use), NULL, NULL },
  { &ranges_by_label_allocated, 1, sizeof (ranges_by_label_allocated), NULL, NULL },
  { &ranges_table_in_use, 1, sizeof (ranges_table_in_use), NULL, NULL },
  { &ranges_table_allocated, 1, sizeof (ranges_table_allocated), NULL, NULL },
  { &arange_table_in_use, 1, sizeof (arange_table_in_use), NULL, NULL },
  { &arange_table_allocated, 1, sizeof (arange_table_allocated), NULL, NULL },
  { &separate_line_info_table_in_use, 1, sizeof (separate_line_info_table_in_use), NULL, NULL },
  { &separate_line_info_table_allocated, 1, sizeof (separate_line_info_table_allocated), NULL, NULL },
  { &line_info_table_in_use, 1, sizeof (line_info_table_in_use), NULL, NULL },
  { &line_info_table_allocated, 1, sizeof (line_info_table_allocated), NULL, NULL },
  { &abbrev_die_table_in_use, 1, sizeof (abbrev_die_table_in_use), NULL, NULL },
  { &abbrev_die_table_allocated, 1, sizeof (abbrev_die_table_allocated), NULL, NULL },
  { &num_regs_saved_in_regs, 1, sizeof (num_regs_saved_in_regs), NULL, NULL },
  { &regs_saved_in_regs, 1, sizeof (regs_saved_in_regs), NULL, NULL },
  { &cold_text_section_used, 1, sizeof (cold_text_section_used), NULL, NULL },
  { &text_section_used, 1, sizeof (text_section_used), NULL, NULL },
  { &have_multiple_function_sections, 1, sizeof (have_multiple_function_sections), NULL, NULL },
  { &dwarf2out_cfi_label_num, 1, sizeof (dwarf2out_cfi_label_num), NULL, NULL },
  { &dw2_string_counter, 1, sizeof (dw2_string_counter), NULL, NULL },
  { &fde_table_in_use, 1, sizeof (fde_table_in_use), NULL, NULL },
  { &fde_table_allocated, 1, sizeof (fde_table_allocated), NULL, NULL },
  { &saved_do_cfi_asm, 1, sizeof (saved_do_cfi_asm), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

