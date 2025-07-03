/* Type information for config/i386/i386.c.
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
gt_ggc_mx_stack_local_entry (void *x_p)
{
  struct stack_local_entry * const x = (struct stack_local_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).rtl);
      gt_ggc_m_17stack_local_entry ((*x).next);
    }
}

void
gt_pch_nx_stack_local_entry (void *x_p)
{
  struct stack_local_entry * const x = (struct stack_local_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17stack_local_entry, gt_ggc_e_17stack_local_entry))
    {
      gt_pch_n_7rtx_def ((*x).rtl);
      gt_pch_n_17stack_local_entry ((*x).next);
    }
}

void
gt_pch_p_17stack_local_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct stack_local_entry * const x ATTRIBUTE_UNUSED = (struct stack_local_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).rtl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

/* GC roots.  */

const struct ggc_root_tab gt_ggc_r_gt_i386_h[] = {
  {
    &ix86_builtins_isa[0].type,
    1 * ((int) IX86_BUILTIN_MAX),
    sizeof (ix86_builtins_isa[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &ix86_builtins_isa[0].name,
    1, 
    sizeof (ix86_builtins_isa),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &ix86_builtins[0],
    1 * ((int) IX86_BUILTIN_MAX),
    sizeof (ix86_builtins[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &ix86_tls_module_base_symbol,
    1,
    sizeof (ix86_tls_module_base_symbol),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &ix86_tls_symbol,
    1,
    sizeof (ix86_tls_symbol),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &ix86_previous_fndecl,
    1,
    sizeof (ix86_previous_fndecl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &ms_va_list_type_node,
    1,
    sizeof (ms_va_list_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &sysv_va_list_type_node,
    1,
    sizeof (sysv_va_list_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_cache_tab gt_ggc_rc_gt_i386_h[] = {
  {
    &dllimport_map,
    1,
    sizeof (dllimport_map),
    &gt_ggc_mx_tree_map,
    &gt_pch_nx_tree_map,
    &tree_map_marked_p
  },
  LAST_GGC_CACHE_TAB
};

const struct ggc_root_tab gt_pch_rc_gt_i386_h[] = {
  {
    &dllimport_map,
    1,
    sizeof (dllimport_map),
    &gt_ggc_m_P8tree_map4htab,
    &gt_pch_n_P8tree_map4htab
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_i386_h[] = {
  { &ix86_builtins_isa, 1, sizeof (ix86_builtins_isa), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

