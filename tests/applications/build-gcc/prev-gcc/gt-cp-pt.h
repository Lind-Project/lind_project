/* Type information for cp/pt.c.
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
gt_ggc_mx_pending_template (void *x_p)
{
  struct pending_template * const x = (struct pending_template *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_16pending_template ((*x).next);
      gt_ggc_m_11tinst_level ((*x).tinst);
    }
}

void
gt_pch_nx_pending_template (void *x_p)
{
  struct pending_template * const x = (struct pending_template *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16pending_template, gt_ggc_e_16pending_template))
    {
      gt_pch_n_16pending_template ((*x).next);
      gt_pch_n_11tinst_level ((*x).tinst);
    }
}

void
gt_pch_p_16pending_template (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct pending_template * const x ATTRIBUTE_UNUSED = (struct pending_template *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).tinst), cookie);
}

/* GC roots.  */

const struct ggc_root_tab gt_ggc_r_gt_cp_pt_h[] = {
  {
    &canonical_template_parms,
    1,
    sizeof (canonical_template_parms),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &saved_access_scope,
    1,
    sizeof (saved_access_scope),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &current_tinst_level,
    1,
    sizeof (current_tinst_level),
    &gt_ggc_mx_tinst_level,
    &gt_pch_nx_tinst_level
  },
  {
    &saved_trees,
    1,
    sizeof (saved_trees),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &last_pending_template,
    1,
    sizeof (last_pending_template),
    &gt_ggc_mx_pending_template,
    &gt_pch_nx_pending_template
  },
  {
    &pending_templates,
    1,
    sizeof (pending_templates),
    &gt_ggc_mx_pending_template,
    &gt_pch_nx_pending_template
  },
  LAST_GGC_ROOT_TAB
};

