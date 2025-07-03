/* Type information for function.c.
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
gt_ggc_mx_temp_slot_address_entry (void *x_p)
{
  struct temp_slot_address_entry * const x = (struct temp_slot_address_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).address);
      gt_ggc_m_9temp_slot ((*x).temp_slot);
    }
}

void
gt_ggc_mx_temp_slot (void *x_p)
{
  struct temp_slot * const x = (struct temp_slot *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9temp_slot ((*x).next);
      gt_ggc_m_9temp_slot ((*x).prev);
      gt_ggc_m_7rtx_def ((*x).slot);
      gt_ggc_m_9tree_node ((*x).type);
    }
}

void
gt_ggc_m_P23temp_slot_address_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_23temp_slot_address_entry ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_pch_nx_temp_slot_address_entry (void *x_p)
{
  struct temp_slot_address_entry * const x = (struct temp_slot_address_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_23temp_slot_address_entry, gt_ggc_e_23temp_slot_address_entry))
    {
      gt_pch_n_7rtx_def ((*x).address);
      gt_pch_n_9temp_slot ((*x).temp_slot);
    }
}

void
gt_pch_nx_temp_slot (void *x_p)
{
  struct temp_slot * const x = (struct temp_slot *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9temp_slot, gt_ggc_e_9temp_slot))
    {
      gt_pch_n_9temp_slot ((*x).next);
      gt_pch_n_9temp_slot ((*x).prev);
      gt_pch_n_7rtx_def ((*x).slot);
      gt_pch_n_9tree_node ((*x).type);
    }
}

void
gt_pch_n_P23temp_slot_address_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P23temp_slot_address_entry4htab, gt_e_P23temp_slot_address_entry4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_23temp_slot_address_entry ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P23temp_slot_address_entry4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_23temp_slot_address_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct temp_slot_address_entry * const x ATTRIBUTE_UNUSED = (struct temp_slot_address_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).address), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).temp_slot), cookie);
}

void
gt_pch_p_9temp_slot (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct temp_slot * const x ATTRIBUTE_UNUSED = (struct temp_slot *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).slot), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).type), cookie);
}

void
gt_pch_p_P23temp_slot_address_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
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

const struct ggc_root_tab gt_ggc_r_gt_function_h[] = {
  {
    &initial_trampoline,
    1,
    sizeof (initial_trampoline),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &temp_slot_address_table,
    1,
    sizeof (temp_slot_address_table),
    &gt_ggc_m_P23temp_slot_address_entry4htab,
    &gt_pch_n_P23temp_slot_address_entry4htab
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_function_h[] = {
  { &next_block_index, 1, sizeof (next_block_index), NULL, NULL },
  { &funcdef_no, 1, sizeof (funcdef_no), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

