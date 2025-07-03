/* Type information for c-common.c.
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
gt_ggc_mx_VEC_const_char_p_gc (void *x_p)
{
  struct VEC_const_char_p_gc * const x = (struct VEC_const_char_p_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_S ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_sorted_fields_type (void *x_p)
{
  struct sorted_fields_type * const x = (struct sorted_fields_type *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x)).len);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).elts[i0]);
        }
      }
    }
}

void
gt_pch_nx_VEC_const_char_p_gc (void *x_p)
{
  struct VEC_const_char_p_gc * const x = (struct VEC_const_char_p_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_19VEC_const_char_p_gc, gt_ggc_e_19VEC_const_char_p_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_S ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_sorted_fields_type (void *x_p)
{
  struct sorted_fields_type * const x = (struct sorted_fields_type *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18sorted_fields_type, gt_ggc_e_18sorted_fields_type))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x)).len);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).elts[i0]);
        }
      }
    }
}

void
gt_pch_p_19VEC_const_char_p_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_const_char_p_gc * const x ATTRIBUTE_UNUSED = (struct VEC_const_char_p_gc *)x_p;
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
gt_pch_p_18sorted_fields_type (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct sorted_fields_type * const x ATTRIBUTE_UNUSED = (struct sorted_fields_type *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x)).len);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).elts[i0]), cookie);
    }
  }
}

/* GC roots.  */

static void gt_ggc_ma_ridpointers (void *);
static void
gt_ggc_ma_ridpointers (ATTRIBUTE_UNUSED void *x_p)
{
  if (ridpointers != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)((int) RID_MAX); i0++) {
      gt_ggc_m_9tree_node (ridpointers[i0]);
    }
    ggc_mark (ridpointers);
  }
}

static void gt_pch_pa_ridpointers
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_ridpointers (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (ridpointers != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)((int) RID_MAX); i0++) {
      if ((void *)(ridpointers) == this_obj)
        op (&(ridpointers[i0]), cookie);
    }
    if ((void *)(&ridpointers) == this_obj)
      op (&(ridpointers), cookie);
  }
}

static void gt_pch_na_ridpointers (void *);
static void
gt_pch_na_ridpointers (ATTRIBUTE_UNUSED void *x_p)
{
  if (ridpointers != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)((int) RID_MAX); i1++) {
      gt_pch_n_9tree_node (ridpointers[i1]);
    }
    gt_pch_note_object (ridpointers, &ridpointers, gt_pch_pa_ridpointers, gt_types_enum_last);
  }
}

const struct ggc_root_tab gt_ggc_r_gt_c_common_h[] = {
  {
    &c_global_trees[0],
    1 * (CTI_MAX),
    sizeof (c_global_trees[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &ridpointers,
    1,
    sizeof (ridpointers),
    &gt_ggc_ma_ridpointers,
    &gt_pch_na_ridpointers
  },
  {
    &optimize_args,
    1,
    sizeof (optimize_args),
    &gt_ggc_mx_VEC_const_char_p_gc,
    &gt_pch_nx_VEC_const_char_p_gc
  },
  {
    &built_in_attributes[0],
    1 * ((int) ATTR_LAST),
    sizeof (built_in_attributes[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &type_hash_table,
    1,
    sizeof (type_hash_table),
    &gt_ggc_m_P9tree_node4htab,
    &gt_pch_n_P9tree_node4htab
  },
  {
    &registered_builtin_types,
    1,
    sizeof (registered_builtin_types),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_c_common_h[] = {
  { &pending_lang_change, 1, sizeof (pending_lang_change), NULL, NULL },
  { &compound_literal_number, 1, sizeof (compound_literal_number), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

