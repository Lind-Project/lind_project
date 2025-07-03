/* Type information for ada/gcc-interface/utils.c.
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
gt_ggc_mx_gnat_binding_level (void *x_p)
{
  struct gnat_binding_level * x = (struct gnat_binding_level *)x_p;
  struct gnat_binding_level * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).chain);
  while (x != xlimit)
    {
      gt_ggc_m_18gnat_binding_level ((*x).chain);
      gt_ggc_m_9tree_node ((*x).block);
      gt_ggc_m_9tree_node ((*x).jmpbuf_decl);
      x = ((*x).chain);
    }
}

void
gt_pch_nx_gnat_binding_level (void *x_p)
{
  struct gnat_binding_level * x = (struct gnat_binding_level *)x_p;
  struct gnat_binding_level * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_18gnat_binding_level, gt_ggc_e_18gnat_binding_level))
   xlimit = ((*xlimit).chain);
  while (x != xlimit)
    {
      gt_pch_n_18gnat_binding_level ((*x).chain);
      gt_pch_n_9tree_node ((*x).block);
      gt_pch_n_9tree_node ((*x).jmpbuf_decl);
      x = ((*x).chain);
    }
}

void
gt_pch_p_18gnat_binding_level (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct gnat_binding_level * const x ATTRIBUTE_UNUSED = (struct gnat_binding_level *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).chain), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).block), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).jmpbuf_decl), cookie);
}

/* GC roots.  */

static void gt_ggc_ma_dummy_node_table (void *);
static void
gt_ggc_ma_dummy_node_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (dummy_node_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(max_gnat_nodes); i0++) {
      gt_ggc_m_9tree_node (dummy_node_table[i0]);
    }
    ggc_mark (dummy_node_table);
  }
}

static void gt_pch_pa_dummy_node_table
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_dummy_node_table (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (dummy_node_table != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(max_gnat_nodes); i0++) {
      if ((void *)(dummy_node_table) == this_obj)
        op (&(dummy_node_table[i0]), cookie);
    }
    if ((void *)(&dummy_node_table) == this_obj)
      op (&(dummy_node_table), cookie);
  }
}

static void gt_pch_na_dummy_node_table (void *);
static void
gt_pch_na_dummy_node_table (ATTRIBUTE_UNUSED void *x_p)
{
  if (dummy_node_table != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(max_gnat_nodes); i1++) {
      gt_pch_n_9tree_node (dummy_node_table[i1]);
    }
    gt_pch_note_object (dummy_node_table, &dummy_node_table, gt_pch_pa_dummy_node_table, gt_types_enum_last);
  }
}

static void gt_ggc_ma_associate_gnat_to_gnu (void *);
static void
gt_ggc_ma_associate_gnat_to_gnu (ATTRIBUTE_UNUSED void *x_p)
{
  if (associate_gnat_to_gnu != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(max_gnat_nodes); i0++) {
      gt_ggc_m_9tree_node (associate_gnat_to_gnu[i0]);
    }
    ggc_mark (associate_gnat_to_gnu);
  }
}

static void gt_pch_pa_associate_gnat_to_gnu
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_associate_gnat_to_gnu (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (associate_gnat_to_gnu != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(max_gnat_nodes); i0++) {
      if ((void *)(associate_gnat_to_gnu) == this_obj)
        op (&(associate_gnat_to_gnu[i0]), cookie);
    }
    if ((void *)(&associate_gnat_to_gnu) == this_obj)
      op (&(associate_gnat_to_gnu), cookie);
  }
}

static void gt_pch_na_associate_gnat_to_gnu (void *);
static void
gt_pch_na_associate_gnat_to_gnu (ATTRIBUTE_UNUSED void *x_p)
{
  if (associate_gnat_to_gnu != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(max_gnat_nodes); i1++) {
      gt_pch_n_9tree_node (associate_gnat_to_gnu[i1]);
    }
    gt_pch_note_object (associate_gnat_to_gnu, &associate_gnat_to_gnu, gt_pch_pa_associate_gnat_to_gnu, gt_types_enum_last);
  }
}

const struct ggc_root_tab gt_ggc_r_gt_ada_utils_h[] = {
  {
    &built_in_attributes[0],
    1 * ((int) ATTR_LAST),
    sizeof (built_in_attributes[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &builtin_types[0],
    1 * ((int) BT_LAST + 1),
    sizeof (builtin_types[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &global_renaming_pointers,
    1,
    sizeof (global_renaming_pointers),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &builtin_decls,
    1,
    sizeof (builtin_decls),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &global_decls,
    1,
    sizeof (global_decls),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &current_binding_level,
    1,
    sizeof (current_binding_level),
    &gt_ggc_mx_gnat_binding_level,
    &gt_pch_nx_gnat_binding_level
  },
  {
    &float_types[0],
    1 * (NUM_MACHINE_MODES),
    sizeof (float_types[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &signed_and_unsigned_types[0][0],
    1 * (2 * MAX_BITS_PER_WORD + 1) * (2),
    sizeof (signed_and_unsigned_types[0][0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &dummy_node_table,
    1,
    sizeof (dummy_node_table),
    &gt_ggc_ma_dummy_node_table,
    &gt_pch_na_dummy_node_table
  },
  {
    &associate_gnat_to_gnu,
    1,
    sizeof (associate_gnat_to_gnu),
    &gt_ggc_ma_associate_gnat_to_gnu,
    &gt_pch_na_associate_gnat_to_gnu
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_ggc_rd_gt_ada_utils_h[] = {
  { &free_block_chain, 1, sizeof (free_block_chain), NULL, NULL },
  { &free_binding_level, 1, sizeof (free_binding_level), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

