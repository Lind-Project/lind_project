/* Type information for ada/gcc-interface/trans.c.
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
gt_ggc_mx_elab_info (void *x_p)
{
  struct elab_info * x = (struct elab_info *)x_p;
  struct elab_info * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_9elab_info ((*x).next);
      gt_ggc_m_9tree_node ((*x).elab_proc);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_stmt_group (void *x_p)
{
  struct stmt_group * x = (struct stmt_group *)x_p;
  struct stmt_group * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).previous);
  while (x != xlimit)
    {
      gt_ggc_m_10stmt_group ((*x).previous);
      gt_ggc_m_9tree_node ((*x).stmt_list);
      gt_ggc_m_9tree_node ((*x).block);
      gt_ggc_m_9tree_node ((*x).cleanups);
      x = ((*x).previous);
    }
}

void
gt_ggc_mx_VEC_parm_attr_gc (void *x_p)
{
  struct VEC_parm_attr_gc * const x = (struct VEC_parm_attr_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9parm_attr ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_ggc_mx_parm_attr (void *x_p)
{
  struct parm_attr * const x = (struct parm_attr *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).first);
      gt_ggc_m_9tree_node ((*x).last);
      gt_ggc_m_9tree_node ((*x).length);
    }
}

void
gt_ggc_mx_language_function (void *x_p)
{
  struct language_function * const x = (struct language_function *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_16VEC_parm_attr_gc ((*x).parm_attr_cache);
    }
}

void
gt_pch_nx_elab_info (void *x_p)
{
  struct elab_info * x = (struct elab_info *)x_p;
  struct elab_info * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_9elab_info, gt_ggc_e_9elab_info))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_9elab_info ((*x).next);
      gt_pch_n_9tree_node ((*x).elab_proc);
      x = ((*x).next);
    }
}

void
gt_pch_nx_stmt_group (void *x_p)
{
  struct stmt_group * x = (struct stmt_group *)x_p;
  struct stmt_group * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_10stmt_group, gt_ggc_e_10stmt_group))
   xlimit = ((*xlimit).previous);
  while (x != xlimit)
    {
      gt_pch_n_10stmt_group ((*x).previous);
      gt_pch_n_9tree_node ((*x).stmt_list);
      gt_pch_n_9tree_node ((*x).block);
      gt_pch_n_9tree_node ((*x).cleanups);
      x = ((*x).previous);
    }
}

void
gt_pch_nx_VEC_parm_attr_gc (void *x_p)
{
  struct VEC_parm_attr_gc * const x = (struct VEC_parm_attr_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16VEC_parm_attr_gc, gt_ggc_e_16VEC_parm_attr_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9parm_attr ((*x).base.vec[i0]);
        }
      }
    }
}

void
gt_pch_nx_parm_attr (void *x_p)
{
  struct parm_attr * const x = (struct parm_attr *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9parm_attr, gt_ggc_e_9parm_attr))
    {
      gt_pch_n_9tree_node ((*x).first);
      gt_pch_n_9tree_node ((*x).last);
      gt_pch_n_9tree_node ((*x).length);
    }
}

void
gt_pch_nx_language_function (void *x_p)
{
  struct language_function * const x = (struct language_function *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17language_function, gt_ggc_e_17language_function))
    {
      gt_pch_n_16VEC_parm_attr_gc ((*x).parm_attr_cache);
    }
}

void
gt_pch_p_9elab_info (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct elab_info * const x ATTRIBUTE_UNUSED = (struct elab_info *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).elab_proc), cookie);
}

void
gt_pch_p_10stmt_group (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct stmt_group * const x ATTRIBUTE_UNUSED = (struct stmt_group *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).previous), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).stmt_list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).block), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).cleanups), cookie);
}

void
gt_pch_p_16VEC_parm_attr_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_parm_attr_gc * const x ATTRIBUTE_UNUSED = (struct VEC_parm_attr_gc *)x_p;
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
gt_pch_p_9parm_attr (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct parm_attr * const x ATTRIBUTE_UNUSED = (struct parm_attr *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).first), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).last), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).length), cookie);
}

void
gt_pch_p_17language_function (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct language_function * const x ATTRIBUTE_UNUSED = (struct language_function *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).parm_attr_cache), cookie);
}

/* GC roots.  */

const struct ggc_root_tab gt_ggc_r_gt_ada_trans_h[] = {
  {
    &gnat_vms_condition_handler_decl,
    1,
    sizeof (gnat_vms_condition_handler_decl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &vms_builtin_establish_handler_decl,
    1,
    sizeof (vms_builtin_establish_handler_decl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gnu_program_error_label_stack,
    1,
    sizeof (gnu_program_error_label_stack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gnu_storage_error_label_stack,
    1,
    sizeof (gnu_storage_error_label_stack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gnu_constraint_error_label_stack,
    1,
    sizeof (gnu_constraint_error_label_stack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gnu_switch_label_stack,
    1,
    sizeof (gnu_switch_label_stack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gnu_loop_label_stack,
    1,
    sizeof (gnu_loop_label_stack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gnu_return_label_stack,
    1,
    sizeof (gnu_return_label_stack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gnu_elab_proc_stack,
    1,
    sizeof (gnu_elab_proc_stack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gnu_except_ptr_stack,
    1,
    sizeof (gnu_except_ptr_stack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &elab_info_list,
    1,
    sizeof (elab_info_list),
    &gt_ggc_mx_elab_info,
    &gt_pch_nx_elab_info
  },
  {
    &current_stmt_group,
    1,
    sizeof (current_stmt_group),
    &gt_ggc_mx_stmt_group,
    &gt_pch_nx_stmt_group
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_ggc_rd_gt_ada_trans_h[] = {
  { &gnu_stack_free_list, 1, sizeof (gnu_stack_free_list), NULL, NULL },
  { &stmt_group_free_list, 1, sizeof (stmt_group_free_list), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

