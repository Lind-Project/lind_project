/* Type information for cp/rtti.c.
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
gt_ggc_mx_VEC_tinfo_s_gc (void *x_p)
{
  struct VEC_tinfo_s_gc * const x = (struct VEC_tinfo_s_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).base.vec[i0].type);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].vtable);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].name);
        }
      }
    }
}

void
gt_pch_nx_VEC_tinfo_s_gc (void *x_p)
{
  struct VEC_tinfo_s_gc * const x = (struct VEC_tinfo_s_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14VEC_tinfo_s_gc, gt_ggc_e_14VEC_tinfo_s_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).base.vec[i0].type);
          gt_pch_n_9tree_node ((*x).base.vec[i0].vtable);
          gt_pch_n_9tree_node ((*x).base.vec[i0].name);
        }
      }
    }
}

void
gt_pch_p_14VEC_tinfo_s_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_tinfo_s_gc * const x ATTRIBUTE_UNUSED = (struct VEC_tinfo_s_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].vtable), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].name), cookie);
    }
  }
}

/* GC roots.  */

const struct ggc_root_tab gt_ggc_r_gt_cp_rtti_h[] = {
  {
    &tinfo_descs,
    1,
    sizeof (tinfo_descs),
    &gt_ggc_mx_VEC_tinfo_s_gc,
    &gt_pch_nx_VEC_tinfo_s_gc
  },
  LAST_GGC_ROOT_TAB
};

