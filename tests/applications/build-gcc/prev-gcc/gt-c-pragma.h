/* Type information for c-pragma.c.
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
gt_ggc_mx_opt_stack (void *x_p)
{
  struct opt_stack * const x = (struct opt_stack *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9opt_stack ((*x).prev);
      gt_ggc_m_9tree_node ((*x).target_binary);
      gt_ggc_m_9tree_node ((*x).target_strings);
      gt_ggc_m_9tree_node ((*x).optimize_binary);
      gt_ggc_m_9tree_node ((*x).optimize_strings);
    }
}

void
gt_ggc_mx_align_stack (void *x_p)
{
  struct align_stack * const x = (struct align_stack *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).id);
      gt_ggc_m_11align_stack ((*x).prev);
    }
}

void
gt_pch_nx_opt_stack (void *x_p)
{
  struct opt_stack * const x = (struct opt_stack *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9opt_stack, gt_ggc_e_9opt_stack))
    {
      gt_pch_n_9opt_stack ((*x).prev);
      gt_pch_n_9tree_node ((*x).target_binary);
      gt_pch_n_9tree_node ((*x).target_strings);
      gt_pch_n_9tree_node ((*x).optimize_binary);
      gt_pch_n_9tree_node ((*x).optimize_strings);
    }
}

void
gt_pch_nx_align_stack (void *x_p)
{
  struct align_stack * const x = (struct align_stack *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11align_stack, gt_ggc_e_11align_stack))
    {
      gt_pch_n_9tree_node ((*x).id);
      gt_pch_n_11align_stack ((*x).prev);
    }
}

void
gt_pch_p_9opt_stack (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct opt_stack * const x ATTRIBUTE_UNUSED = (struct opt_stack *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).target_binary), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).target_strings), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).optimize_binary), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).optimize_strings), cookie);
}

void
gt_pch_p_11align_stack (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct align_stack * const x ATTRIBUTE_UNUSED = (struct align_stack *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).id), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
}

/* GC roots.  */

const struct ggc_root_tab gt_ggc_r_gt_c_pragma_h[] = {
  {
    &options_stack,
    1,
    sizeof (options_stack),
    &gt_ggc_mx_opt_stack,
    &gt_pch_nx_opt_stack
  },
  {
    &pragma_extern_prefix,
    1,
    sizeof (pragma_extern_prefix),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &pending_redefine_extname,
    1,
    sizeof (pending_redefine_extname),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &pending_weaks,
    1,
    sizeof (pending_weaks),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &alignment_stack,
    1,
    sizeof (alignment_stack),
    &gt_ggc_mx_align_stack,
    &gt_pch_nx_align_stack
  },
  LAST_GGC_ROOT_TAB
};

