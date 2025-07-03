/* Type information for cp/name-lookup.c.
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
gt_ggc_mx_VEC_cp_class_binding_gc (void *x_p)
{
  struct VEC_cp_class_binding_gc * const x = (struct VEC_cp_class_binding_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_11cxx_binding ((*x).base.vec[i0].base.previous);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].base.value);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].base.type);
          gt_ggc_m_16cp_binding_level ((*x).base.vec[i0].base.scope);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].identifier);
        }
      }
    }
}

void
gt_ggc_mx_VEC_cxx_saved_binding_gc (void *x_p)
{
  struct VEC_cxx_saved_binding_gc * const x = (struct VEC_cxx_saved_binding_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).base.vec[i0].identifier);
          gt_ggc_m_11cxx_binding ((*x).base.vec[i0].binding);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].real_type_value);
        }
      }
    }
}

void
gt_ggc_mx_cp_binding_level (void *x_p)
{
  struct cp_binding_level * const x = (struct cp_binding_level *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).names);
      gt_ggc_m_9tree_node ((*x).namespaces);
      gt_ggc_m_11VEC_tree_gc ((*x).static_decls);
      gt_ggc_m_9tree_node ((*x).usings);
      gt_ggc_m_9tree_node ((*x).using_directives);
      gt_ggc_m_23VEC_cp_class_binding_gc ((*x).class_shadowed);
      gt_ggc_m_9tree_node ((*x).type_shadowed);
      gt_ggc_m_9tree_node ((*x).shadowed_labels);
      gt_ggc_m_9tree_node ((*x).blocks);
      gt_ggc_m_9tree_node ((*x).this_entity);
      gt_ggc_m_16cp_binding_level ((*x).level_chain);
      gt_ggc_m_9tree_node ((*x).dead_vars_from_for);
      gt_ggc_m_9tree_node ((*x).statement_list);
    }
}

void
gt_ggc_mx_cxx_binding (void *x_p)
{
  struct cxx_binding * const x = (struct cxx_binding *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_11cxx_binding ((*x).previous);
      gt_ggc_m_9tree_node ((*x).value);
      gt_ggc_m_9tree_node ((*x).type);
      gt_ggc_m_16cp_binding_level ((*x).scope);
    }
}

void
gt_ggc_mx_binding_entry_s (void *x_p)
{
  struct binding_entry_s * const x = (struct binding_entry_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15binding_entry_s ((*x).chain);
      gt_ggc_m_9tree_node ((*x).name);
      gt_ggc_m_9tree_node ((*x).type);
    }
}

void
gt_ggc_mx_binding_table_s (void *x_p)
{
  struct binding_table_s * const x = (struct binding_table_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).chain != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).chain_count); i0++) {
          gt_ggc_m_15binding_entry_s ((*x).chain[i0]);
        }
        ggc_mark ((*x).chain);
      }
    }
}

void
gt_pch_nx_VEC_cp_class_binding_gc (void *x_p)
{
  struct VEC_cp_class_binding_gc * const x = (struct VEC_cp_class_binding_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_23VEC_cp_class_binding_gc, gt_ggc_e_23VEC_cp_class_binding_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_11cxx_binding ((*x).base.vec[i0].base.previous);
          gt_pch_n_9tree_node ((*x).base.vec[i0].base.value);
          gt_pch_n_9tree_node ((*x).base.vec[i0].base.type);
          gt_pch_n_16cp_binding_level ((*x).base.vec[i0].base.scope);
          gt_pch_n_9tree_node ((*x).base.vec[i0].identifier);
        }
      }
    }
}

void
gt_pch_nx_VEC_cxx_saved_binding_gc (void *x_p)
{
  struct VEC_cxx_saved_binding_gc * const x = (struct VEC_cxx_saved_binding_gc *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_24VEC_cxx_saved_binding_gc, gt_ggc_e_24VEC_cxx_saved_binding_gc))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).base.vec[i0].identifier);
          gt_pch_n_11cxx_binding ((*x).base.vec[i0].binding);
          gt_pch_n_9tree_node ((*x).base.vec[i0].real_type_value);
        }
      }
    }
}

void
gt_pch_nx_cp_binding_level (void *x_p)
{
  struct cp_binding_level * const x = (struct cp_binding_level *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16cp_binding_level, gt_ggc_e_16cp_binding_level))
    {
      gt_pch_n_9tree_node ((*x).names);
      gt_pch_n_9tree_node ((*x).namespaces);
      gt_pch_n_11VEC_tree_gc ((*x).static_decls);
      gt_pch_n_9tree_node ((*x).usings);
      gt_pch_n_9tree_node ((*x).using_directives);
      gt_pch_n_23VEC_cp_class_binding_gc ((*x).class_shadowed);
      gt_pch_n_9tree_node ((*x).type_shadowed);
      gt_pch_n_9tree_node ((*x).shadowed_labels);
      gt_pch_n_9tree_node ((*x).blocks);
      gt_pch_n_9tree_node ((*x).this_entity);
      gt_pch_n_16cp_binding_level ((*x).level_chain);
      gt_pch_n_9tree_node ((*x).dead_vars_from_for);
      gt_pch_n_9tree_node ((*x).statement_list);
    }
}

void
gt_pch_nx_cxx_binding (void *x_p)
{
  struct cxx_binding * const x = (struct cxx_binding *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11cxx_binding, gt_ggc_e_11cxx_binding))
    {
      gt_pch_n_11cxx_binding ((*x).previous);
      gt_pch_n_9tree_node ((*x).value);
      gt_pch_n_9tree_node ((*x).type);
      gt_pch_n_16cp_binding_level ((*x).scope);
    }
}

void
gt_pch_nx_binding_entry_s (void *x_p)
{
  struct binding_entry_s * const x = (struct binding_entry_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15binding_entry_s, gt_ggc_e_15binding_entry_s))
    {
      gt_pch_n_15binding_entry_s ((*x).chain);
      gt_pch_n_9tree_node ((*x).name);
      gt_pch_n_9tree_node ((*x).type);
    }
}

void
gt_pch_nx_binding_table_s (void *x_p)
{
  struct binding_table_s * const x = (struct binding_table_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15binding_table_s, gt_ggc_e_15binding_table_s))
    {
      if ((*x).chain != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).chain_count); i0++) {
          gt_pch_n_15binding_entry_s ((*x).chain[i0]);
        }
        gt_pch_note_object ((*x).chain, x, gt_pch_p_15binding_table_s, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_23VEC_cp_class_binding_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_cp_class_binding_gc * const x ATTRIBUTE_UNUSED = (struct VEC_cp_class_binding_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].base.previous), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].base.value), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].base.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].base.scope), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].identifier), cookie);
    }
  }
}

void
gt_pch_p_24VEC_cxx_saved_binding_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_cxx_saved_binding_gc * const x ATTRIBUTE_UNUSED = (struct VEC_cxx_saved_binding_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).num);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].identifier), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].binding), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).base.vec[i0].real_type_value), cookie);
    }
  }
}

void
gt_pch_p_16cp_binding_level (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cp_binding_level * const x ATTRIBUTE_UNUSED = (struct cp_binding_level *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).names), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).namespaces), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).static_decls), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).usings), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).using_directives), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).class_shadowed), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).type_shadowed), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).shadowed_labels), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).blocks), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).this_entity), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).level_chain), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dead_vars_from_for), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).statement_list), cookie);
}

void
gt_pch_p_11cxx_binding (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cxx_binding * const x ATTRIBUTE_UNUSED = (struct cxx_binding *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).previous), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).type), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).scope), cookie);
}

void
gt_pch_p_15binding_entry_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct binding_entry_s * const x ATTRIBUTE_UNUSED = (struct binding_entry_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).chain), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).name), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).type), cookie);
}

void
gt_pch_p_15binding_table_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct binding_table_s * const x ATTRIBUTE_UNUSED = (struct binding_table_s *)x_p;
  if ((*x).chain != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).chain_count); i0++) {
      if ((void *)((*x).chain) == this_obj)
        op (&((*x).chain[i0]), cookie);
    }
    if ((void *)(x) == this_obj)
      op (&((*x).chain), cookie);
  }
}

/* GC roots.  */

const struct ggc_root_tab gt_ggc_r_gt_cp_name_lookup_h[] = {
  {
    &anonymous_namespace_name,
    1,
    sizeof (anonymous_namespace_name),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &global_type_node,
    1,
    sizeof (global_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &global_scope_name,
    1,
    sizeof (global_scope_name),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &global_namespace,
    1,
    sizeof (global_namespace),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_ggc_rd_gt_cp_name_lookup_h[] = {
  { &free_binding_level, 1, sizeof (free_binding_level), NULL, NULL },
  { &free_bindings, 1, sizeof (free_bindings), NULL, NULL },
  { &free_binding_entry, 1, sizeof (free_binding_entry), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_cp_name_lookup_h[] = {
  { &anon_cnt, 1, sizeof (anon_cnt), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

