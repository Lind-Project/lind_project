/* Type information for integrate.c.
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
gt_ggc_mx_initial_value_struct (void *x_p)
{
  struct initial_value_struct * const x = (struct initial_value_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).num_entries); i0++) {
          gt_ggc_m_7rtx_def ((*x).entries[i0].hard_reg);
          gt_ggc_m_7rtx_def ((*x).entries[i0].pseudo);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_pch_nx_initial_value_struct (void *x_p)
{
  struct initial_value_struct * const x = (struct initial_value_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_20initial_value_struct, gt_ggc_e_20initial_value_struct))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).num_entries); i0++) {
          gt_pch_n_7rtx_def ((*x).entries[i0].hard_reg);
          gt_pch_n_7rtx_def ((*x).entries[i0].pseudo);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_20initial_value_struct, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_20initial_value_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct initial_value_struct * const x ATTRIBUTE_UNUSED = (struct initial_value_struct *)x_p;
  if ((*x).entries != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).num_entries); i0++) {
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0].hard_reg), cookie);
      if ((void *)((*x).entries) == this_obj)
        op (&((*x).entries[i0].pseudo), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).entries), cookie);
  }
}
