/* Type information for alias.c.
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
gt_ggc_mx_VEC_alias_set_entry_gc (void *x_p)
{
  struct VEC_alias_set_entry_gc * const x = (struct VEC_alias_set_entry_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_15alias_set_entry ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_alias_set_entry (void *x_p)
{
  struct alias_set_entry * const x = (struct alias_set_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_II12splay_tree_s ((*x).children);
    }
}

void
gt_pch_nx_VEC_alias_set_entry_gc (void *x_p)
{
  struct VEC_alias_set_entry_gc * const x = (struct VEC_alias_set_entry_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_22VEC_alias_set_entry_gc, gt_ggc_e_22VEC_alias_set_entry_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_15alias_set_entry ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_alias_set_entry (void *x_p)
{
  struct alias_set_entry * const x = (struct alias_set_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15alias_set_entry, gt_ggc_e_15alias_set_entry))
    {
      gt_pch_n_II12splay_tree_s ((*x).children);
    }
}

void
gt_pch_p_22VEC_alias_set_entry_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_alias_set_entry_gc * const x ATTRIBUTE_UNUSED = (struct VEC_alias_set_entry_gc *)x_p;
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
gt_pch_p_15alias_set_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct alias_set_entry * const x ATTRIBUTE_UNUSED = (struct alias_set_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).children), cookie);
}

/* GC roots.  */

static void gt_ggc_ma_reg_known_value (void *);
static void
gt_ggc_ma_reg_known_value (ATTRIBUTE_UNUSED void *x_p)
{
  if (reg_known_value != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(reg_known_value_size); i0++) {
      gt_ggc_m_7rtx_def (reg_known_value[i0]);
    }
    ggc_mark (reg_known_value);
  }
}

static void gt_pch_pa_reg_known_value
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_reg_known_value (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (reg_known_value != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(reg_known_value_size); i0++) {
      if ((void *)(reg_known_value) == this_obj)
        op (&(reg_known_value[i0]), cookie);
    }
    if ((void *)(&reg_known_value) == this_obj)
      op (&(reg_known_value), cookie);
  }
}

static void gt_pch_na_reg_known_value (void *);
static void
gt_pch_na_reg_known_value (ATTRIBUTE_UNUSED void *x_p)
{
  if (reg_known_value != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(reg_known_value_size); i1++) {
      gt_pch_n_7rtx_def (reg_known_value[i1]);
    }
    gt_pch_note_object (reg_known_value, &reg_known_value, gt_pch_pa_reg_known_value, gt_types_enum_last);
  }
}

const struct ggc_root_tab gt_ggc_r_gt_alias_h[] = {
  {
    &alias_sets,
    1,
    sizeof (alias_sets),
    &gt_ggc_mx_VEC_alias_set_entry_gc,
    &gt_pch_nx_VEC_alias_set_entry_gc
  },
  {
    &reg_known_value,
    1,
    sizeof (reg_known_value),
    &gt_ggc_ma_reg_known_value,
    &gt_pch_na_reg_known_value
  },
  {
    &static_reg_base_value[0],
    1 * (FIRST_PSEUDO_REGISTER),
    sizeof (static_reg_base_value[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &reg_base_value,
    1,
    sizeof (reg_base_value),
    &gt_ggc_mx_VEC_rtx_gc,
    &gt_pch_nx_VEC_rtx_gc
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_ggc_rd_gt_alias_h[] = {
  { &old_reg_base_value, 1, sizeof (old_reg_base_value), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_alias_h[] = {
  { &frame_set, 1, sizeof (frame_set), NULL, NULL },
  { &varargs_set, 1, sizeof (varargs_set), NULL, NULL },
  { &reg_known_value_size, 1, sizeof (reg_known_value_size), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

