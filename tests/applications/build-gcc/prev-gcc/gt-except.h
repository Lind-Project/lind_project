/* Type information for except.c.
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
gt_ggc_mx_VEC_eh_region_gc (void *x_p)
{
  struct VEC_eh_region_gc * const x = (struct VEC_eh_region_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9eh_region ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_eh_region (void *x_p)
{
  struct eh_region * const x = (struct eh_region *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9eh_region ((*x).outer);
      gt_ggc_m_9eh_region ((*x).inner);
      gt_ggc_m_9eh_region ((*x).next_peer);
      gt_ggc_m_15bitmap_head_def ((*x).aka);
      switch ((*x).type)
        {
        case ERT_TRY:
          gt_ggc_m_9eh_region ((*x).u.eh_try.eh_catch);
          gt_ggc_m_9eh_region ((*x).u.eh_try.last_catch);
          break;
        case ERT_CATCH:
          gt_ggc_m_9eh_region ((*x).u.eh_catch.next_catch);
          gt_ggc_m_9eh_region ((*x).u.eh_catch.prev_catch);
          gt_ggc_m_9tree_node ((*x).u.eh_catch.type_list);
          gt_ggc_m_9tree_node ((*x).u.eh_catch.filter_list);
          break;
        case ERT_ALLOWED_EXCEPTIONS:
          gt_ggc_m_9tree_node ((*x).u.allowed.type_list);
          break;
        case ERT_THROW:
          gt_ggc_m_9tree_node ((*x).u.eh_throw.type);
          break;
        case ERT_CLEANUP:
          gt_ggc_m_9eh_region ((*x).u.cleanup.prev_try);
          break;
        default:
          break;
        }
      gt_ggc_m_7rtx_def ((*x).label);
      gt_ggc_m_9tree_node ((*x).tree_label);
      gt_ggc_m_7rtx_def ((*x).landing_pad);
      gt_ggc_m_7rtx_def ((*x).post_landing_pad);
      gt_ggc_m_7rtx_def ((*x).resume);
    }
}

void
gt_ggc_mx_eh_status (void *x_p)
{
  struct eh_status * const x = (struct eh_status *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9eh_region ((*x).region_tree);
      gt_ggc_m_16VEC_eh_region_gc ((*x).region_array);
      gt_ggc_m_P15throw_stmt_node4htab ((*x).throw_stmt_table);
    }
}

void
gt_ggc_mx_ehl_map_entry (void *x_p)
{
  struct ehl_map_entry * const x = (struct ehl_map_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).label);
      gt_ggc_m_9eh_region ((*x).region);
    }
}

void
gt_ggc_mx_call_site_record (void *x_p)
{
  struct call_site_record * const x = (struct call_site_record *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).landing_pad);
    }
}

void
gt_ggc_m_P13ehl_map_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_13ehl_map_entry ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_pch_nx_VEC_eh_region_gc (void *x_p)
{
  struct VEC_eh_region_gc * const x = (struct VEC_eh_region_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16VEC_eh_region_gc, gt_ggc_e_16VEC_eh_region_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9eh_region ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_eh_region (void *x_p)
{
  struct eh_region * const x = (struct eh_region *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9eh_region, gt_ggc_e_9eh_region))
    {
      gt_pch_n_9eh_region ((*x).outer);
      gt_pch_n_9eh_region ((*x).inner);
      gt_pch_n_9eh_region ((*x).next_peer);
      gt_pch_n_15bitmap_head_def ((*x).aka);
      switch ((*x).type)
        {
        case ERT_TRY:
          gt_pch_n_9eh_region ((*x).u.eh_try.eh_catch);
          gt_pch_n_9eh_region ((*x).u.eh_try.last_catch);
          break;
        case ERT_CATCH:
          gt_pch_n_9eh_region ((*x).u.eh_catch.next_catch);
          gt_pch_n_9eh_region ((*x).u.eh_catch.prev_catch);
          gt_pch_n_9tree_node ((*x).u.eh_catch.type_list);
          gt_pch_n_9tree_node ((*x).u.eh_catch.filter_list);
          break;
        case ERT_ALLOWED_EXCEPTIONS:
          gt_pch_n_9tree_node ((*x).u.allowed.type_list);
          break;
        case ERT_THROW:
          gt_pch_n_9tree_node ((*x).u.eh_throw.type);
          break;
        case ERT_CLEANUP:
          gt_pch_n_9eh_region ((*x).u.cleanup.prev_try);
          break;
        default:
          break;
        }
      gt_pch_n_7rtx_def ((*x).label);
      gt_pch_n_9tree_node ((*x).tree_label);
      gt_pch_n_7rtx_def ((*x).landing_pad);
      gt_pch_n_7rtx_def ((*x).post_landing_pad);
      gt_pch_n_7rtx_def ((*x).resume);
    }
}

void
gt_pch_nx_eh_status (void *x_p)
{
  struct eh_status * const x = (struct eh_status *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9eh_status, gt_ggc_e_9eh_status))
    {
      gt_pch_n_9eh_region ((*x).region_tree);
      gt_pch_n_16VEC_eh_region_gc ((*x).region_array);
      gt_pch_n_P15throw_stmt_node4htab ((*x).throw_stmt_table);
    }
}

void
gt_pch_nx_ehl_map_entry (void *x_p)
{
  struct ehl_map_entry * const x = (struct ehl_map_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13ehl_map_entry, gt_ggc_e_13ehl_map_entry))
    {
      gt_pch_n_7rtx_def ((*x).label);
      gt_pch_n_9eh_region ((*x).region);
    }
}

void
gt_pch_nx_call_site_record (void *x_p)
{
  struct call_site_record * const x = (struct call_site_record *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16call_site_record, gt_ggc_e_16call_site_record))
    {
      gt_pch_n_7rtx_def ((*x).landing_pad);
    }
}

void
gt_pch_n_P13ehl_map_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P13ehl_map_entry4htab, gt_e_P13ehl_map_entry4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_13ehl_map_entry ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P13ehl_map_entry4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_16VEC_eh_region_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_eh_region_gc * const x ATTRIBUTE_UNUSED = (struct VEC_eh_region_gc *)x_p;
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
gt_pch_p_9eh_region (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct eh_region * const x ATTRIBUTE_UNUSED = (struct eh_region *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).outer), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).inner), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_peer), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).aka), cookie);
  switch ((*x).type)
    {
    case ERT_TRY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_try.eh_catch), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_try.last_catch), cookie);
      break;
    case ERT_CATCH:
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_catch.next_catch), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_catch.prev_catch), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_catch.type_list), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_catch.filter_list), cookie);
      break;
    case ERT_ALLOWED_EXCEPTIONS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.allowed.type_list), cookie);
      break;
    case ERT_THROW:
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_throw.type), cookie);
      break;
    case ERT_CLEANUP:
      if ((void *)(x) == this_obj)
        op (&((*x).u.cleanup.prev_try), cookie);
      break;
    default:
      break;
    }
  if ((void *)(x) == this_obj)
    op (&((*x).label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).tree_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).landing_pad), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).post_landing_pad), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).resume), cookie);
}

void
gt_pch_p_9eh_status (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct eh_status * const x ATTRIBUTE_UNUSED = (struct eh_status *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).region_tree), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).region_array), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).throw_stmt_table), cookie);
}

void
gt_pch_p_13ehl_map_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct ehl_map_entry * const x ATTRIBUTE_UNUSED = (struct ehl_map_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).region), cookie);
}

void
gt_pch_p_16call_site_record (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct call_site_record * const x ATTRIBUTE_UNUSED = (struct call_site_record *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).landing_pad), cookie);
}

void
gt_pch_p_P13ehl_map_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
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

const struct ggc_root_tab gt_ggc_r_gt_except_h[] = {
  {
    &sjlj_fc_type_node,
    1,
    sizeof (sjlj_fc_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &type_to_runtime_map,
    1,
    sizeof (type_to_runtime_map),
    &gt_ggc_m_P9tree_node4htab,
    &gt_pch_n_P9tree_node4htab
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_except_h[] = {
  { &call_site_base, 1, sizeof (call_site_base), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

