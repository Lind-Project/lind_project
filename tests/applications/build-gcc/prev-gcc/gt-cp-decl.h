/* Type information for cp/decl.c.
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
gt_ggc_mx_named_label_use_entry (void *x_p)
{
  struct named_label_use_entry * const x = (struct named_label_use_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_21named_label_use_entry ((*x).next);
      gt_ggc_m_16cp_binding_level ((*x).binding_level);
      gt_ggc_m_9tree_node ((*x).names_in_scope);
    }
}

void
gt_ggc_mx_named_label_entry (void *x_p)
{
  struct named_label_entry * const x = (struct named_label_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).label_decl);
      gt_ggc_m_16cp_binding_level ((*x).binding_level);
      gt_ggc_m_9tree_node ((*x).names_in_scope);
      gt_ggc_m_9tree_node ((*x).bad_decls);
      gt_ggc_m_21named_label_use_entry ((*x).uses);
    }
}

void
gt_ggc_m_P17named_label_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_17named_label_entry ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_pch_nx_named_label_use_entry (void *x_p)
{
  struct named_label_use_entry * const x = (struct named_label_use_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_21named_label_use_entry, gt_ggc_e_21named_label_use_entry))
    {
      gt_pch_n_21named_label_use_entry ((*x).next);
      gt_pch_n_16cp_binding_level ((*x).binding_level);
      gt_pch_n_9tree_node ((*x).names_in_scope);
    }
}

void
gt_pch_nx_named_label_entry (void *x_p)
{
  struct named_label_entry * const x = (struct named_label_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17named_label_entry, gt_ggc_e_17named_label_entry))
    {
      gt_pch_n_9tree_node ((*x).label_decl);
      gt_pch_n_16cp_binding_level ((*x).binding_level);
      gt_pch_n_9tree_node ((*x).names_in_scope);
      gt_pch_n_9tree_node ((*x).bad_decls);
      gt_pch_n_21named_label_use_entry ((*x).uses);
    }
}

void
gt_pch_n_P17named_label_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P17named_label_entry4htab, gt_e_P17named_label_entry4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_17named_label_entry ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P17named_label_entry4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_21named_label_use_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct named_label_use_entry * const x ATTRIBUTE_UNUSED = (struct named_label_use_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).binding_level), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).names_in_scope), cookie);
}

void
gt_pch_p_17named_label_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct named_label_entry * const x ATTRIBUTE_UNUSED = (struct named_label_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).label_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).binding_level), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).names_in_scope), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).bad_decls), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).uses), cookie);
}

void
gt_pch_p_P17named_label_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
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

const struct ggc_root_tab gt_ggc_r_gt_cp_decl_h[] = {
  {
    &typename_htab,
    1,
    sizeof (typename_htab),
    &gt_ggc_m_P9tree_node4htab,
    &gt_pch_n_P9tree_node4htab
  },
  {
    &incomplete_vars,
    1,
    sizeof (incomplete_vars),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_cp_decl_h[] = {
  { &start_cleanup_cnt, 1, sizeof (start_cleanup_cnt), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

