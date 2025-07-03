/* Type information for objc/objc-act.c.
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
gt_ggc_mx_interface_tuple (void *x_p)
{
  struct interface_tuple * const x = (struct interface_tuple *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).id);
      gt_ggc_m_9tree_node ((*x).class_name);
    }
}

void
gt_ggc_mx_volatilized_type (void *x_p)
{
  struct volatilized_type * const x = (struct volatilized_type *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).type);
    }
}

void
gt_ggc_mx_string_descriptor (void *x_p)
{
  struct string_descriptor * const x = (struct string_descriptor *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).literal);
      gt_ggc_m_9tree_node ((*x).constructor);
    }
}

void
gt_ggc_mx_imp_entry (void *x_p)
{
  struct imp_entry * const x = (struct imp_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9imp_entry ((*x).next);
      gt_ggc_m_9tree_node ((*x).imp_context);
      gt_ggc_m_9tree_node ((*x).imp_template);
      gt_ggc_m_9tree_node ((*x).class_decl);
      gt_ggc_m_9tree_node ((*x).meta_decl);
    }
}

void
gt_ggc_mx_hashed_attribute (void *x_p)
{
  struct hashed_attribute * const x = (struct hashed_attribute *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_16hashed_attribute ((*x).next);
      gt_ggc_m_9tree_node ((*x).value);
    }
}

void
gt_ggc_mx_hashed_entry (void *x_p)
{
  struct hashed_entry * const x = (struct hashed_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_16hashed_attribute ((*x).list);
      gt_ggc_m_12hashed_entry ((*x).next);
      gt_ggc_m_9tree_node ((*x).key);
    }
}

void
gt_ggc_m_P15interface_tuple4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_15interface_tuple ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P16volatilized_type4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_16volatilized_type ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_ggc_m_P17string_descriptor4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_ggc_m_17string_descriptor ((*x).entries[i0]);
        }
        ggc_mark ((*x).entries);
      }
    }
}

void
gt_pch_nx_interface_tuple (void *x_p)
{
  struct interface_tuple * const x = (struct interface_tuple *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15interface_tuple, gt_ggc_e_15interface_tuple))
    {
      gt_pch_n_9tree_node ((*x).id);
      gt_pch_n_9tree_node ((*x).class_name);
    }
}

void
gt_pch_nx_volatilized_type (void *x_p)
{
  struct volatilized_type * const x = (struct volatilized_type *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16volatilized_type, gt_ggc_e_16volatilized_type))
    {
      gt_pch_n_9tree_node ((*x).type);
    }
}

void
gt_pch_nx_string_descriptor (void *x_p)
{
  struct string_descriptor * const x = (struct string_descriptor *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17string_descriptor, gt_ggc_e_17string_descriptor))
    {
      gt_pch_n_9tree_node ((*x).literal);
      gt_pch_n_9tree_node ((*x).constructor);
    }
}

void
gt_pch_nx_imp_entry (void *x_p)
{
  struct imp_entry * const x = (struct imp_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9imp_entry, gt_ggc_e_9imp_entry))
    {
      gt_pch_n_9imp_entry ((*x).next);
      gt_pch_n_9tree_node ((*x).imp_context);
      gt_pch_n_9tree_node ((*x).imp_template);
      gt_pch_n_9tree_node ((*x).class_decl);
      gt_pch_n_9tree_node ((*x).meta_decl);
    }
}

void
gt_pch_nx_hashed_attribute (void *x_p)
{
  struct hashed_attribute * const x = (struct hashed_attribute *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16hashed_attribute, gt_ggc_e_16hashed_attribute))
    {
      gt_pch_n_16hashed_attribute ((*x).next);
      gt_pch_n_9tree_node ((*x).value);
    }
}

void
gt_pch_nx_hashed_entry (void *x_p)
{
  struct hashed_entry * const x = (struct hashed_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12hashed_entry, gt_ggc_e_12hashed_entry))
    {
      gt_pch_n_16hashed_attribute ((*x).list);
      gt_pch_n_12hashed_entry ((*x).next);
      gt_pch_n_9tree_node ((*x).key);
    }
}

void
gt_pch_n_P15interface_tuple4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P15interface_tuple4htab, gt_e_P15interface_tuple4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_15interface_tuple ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P15interface_tuple4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P16volatilized_type4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P16volatilized_type4htab, gt_e_P16volatilized_type4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_16volatilized_type ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P16volatilized_type4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_n_P17string_descriptor4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P17string_descriptor4htab, gt_e_P17string_descriptor4htab))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_17string_descriptor ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P17string_descriptor4htab, gt_types_enum_last);
      }
    }
}

void
gt_pch_p_15interface_tuple (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct interface_tuple * const x ATTRIBUTE_UNUSED = (struct interface_tuple *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).id), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).class_name), cookie);
}

void
gt_pch_p_16volatilized_type (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct volatilized_type * const x ATTRIBUTE_UNUSED = (struct volatilized_type *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).type), cookie);
}

void
gt_pch_p_17string_descriptor (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct string_descriptor * const x ATTRIBUTE_UNUSED = (struct string_descriptor *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).literal), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).constructor), cookie);
}

void
gt_pch_p_9imp_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct imp_entry * const x ATTRIBUTE_UNUSED = (struct imp_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).imp_context), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).imp_template), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).class_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).meta_decl), cookie);
}

void
gt_pch_p_16hashed_attribute (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct hashed_attribute * const x ATTRIBUTE_UNUSED = (struct hashed_attribute *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
}

void
gt_pch_p_12hashed_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct hashed_entry * const x ATTRIBUTE_UNUSED = (struct hashed_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).key), cookie);
}

void
gt_pch_p_P15interface_tuple4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P16volatilized_type4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P17string_descriptor4htab (ATTRIBUTE_UNUSED void *this_obj,
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

static void gt_ggc_ma_cls_method_hash_list (void *);
static void
gt_ggc_ma_cls_method_hash_list (ATTRIBUTE_UNUSED void *x_p)
{
  if (cls_method_hash_list != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(SIZEHASHTABLE); i0++) {
      gt_ggc_m_12hashed_entry (cls_method_hash_list[i0]);
    }
    ggc_mark (cls_method_hash_list);
  }
}

static void gt_pch_pa_cls_method_hash_list
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_cls_method_hash_list (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (cls_method_hash_list != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(SIZEHASHTABLE); i0++) {
      if ((void *)(cls_method_hash_list) == this_obj)
        op (&(cls_method_hash_list[i0]), cookie);
    }
    if ((void *)(&cls_method_hash_list) == this_obj)
      op (&(cls_method_hash_list), cookie);
  }
}

static void gt_pch_na_cls_method_hash_list (void *);
static void
gt_pch_na_cls_method_hash_list (ATTRIBUTE_UNUSED void *x_p)
{
  if (cls_method_hash_list != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(SIZEHASHTABLE); i1++) {
      gt_pch_n_12hashed_entry (cls_method_hash_list[i1]);
    }
    gt_pch_note_object (cls_method_hash_list, &cls_method_hash_list, gt_pch_pa_cls_method_hash_list, gt_types_enum_last);
  }
}

static void gt_ggc_ma_nst_method_hash_list (void *);
static void
gt_ggc_ma_nst_method_hash_list (ATTRIBUTE_UNUSED void *x_p)
{
  if (nst_method_hash_list != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(SIZEHASHTABLE); i0++) {
      gt_ggc_m_12hashed_entry (nst_method_hash_list[i0]);
    }
    ggc_mark (nst_method_hash_list);
  }
}

static void gt_pch_pa_nst_method_hash_list
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_nst_method_hash_list (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (nst_method_hash_list != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(SIZEHASHTABLE); i0++) {
      if ((void *)(nst_method_hash_list) == this_obj)
        op (&(nst_method_hash_list[i0]), cookie);
    }
    if ((void *)(&nst_method_hash_list) == this_obj)
      op (&(nst_method_hash_list), cookie);
  }
}

static void gt_pch_na_nst_method_hash_list (void *);
static void
gt_pch_na_nst_method_hash_list (ATTRIBUTE_UNUSED void *x_p)
{
  if (nst_method_hash_list != NULL) {
    size_t i1;
    for (i1 = 0; i1 != (size_t)(SIZEHASHTABLE); i1++) {
      gt_pch_n_12hashed_entry (nst_method_hash_list[i1]);
    }
    gt_pch_note_object (nst_method_hash_list, &nst_method_hash_list, gt_pch_pa_nst_method_hash_list, gt_types_enum_last);
  }
}

const struct ggc_root_tab gt_ggc_r_gt_objc_objc_act_h[] = {
  {
    &objc_parmlist,
    1,
    sizeof (objc_parmlist),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &interface_htab,
    1,
    sizeof (interface_htab),
    &gt_ggc_m_P15interface_tuple4htab,
    &gt_pch_n_P15interface_tuple4htab
  },
  {
    &volatilized_htab,
    1,
    sizeof (volatilized_htab),
    &gt_ggc_m_P16volatilized_type4htab,
    &gt_pch_n_P16volatilized_type4htab
  },
  {
    &string_htab,
    1,
    sizeof (string_htab),
    &gt_ggc_m_P17string_descriptor4htab,
    &gt_pch_n_P17string_descriptor4htab
  },
  {
    &objc_global_trees[0],
    1 * (OCTI_MAX),
    sizeof (objc_global_trees[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &imp_list,
    1,
    sizeof (imp_list),
    &gt_ggc_mx_imp_entry,
    &gt_pch_nx_imp_entry
  },
  {
    &cls_method_hash_list,
    1,
    sizeof (cls_method_hash_list),
    &gt_ggc_ma_cls_method_hash_list,
    &gt_pch_na_cls_method_hash_list
  },
  {
    &nst_method_hash_list,
    1,
    sizeof (nst_method_hash_list),
    &gt_ggc_ma_nst_method_hash_list,
    &gt_pch_na_nst_method_hash_list
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_objc_objc_act_h[] = {
  { &meth_var_types_idx, 1, sizeof (meth_var_types_idx), NULL, NULL },
  { &meth_var_names_idx, 1, sizeof (meth_var_names_idx), NULL, NULL },
  { &class_names_idx, 1, sizeof (class_names_idx), NULL, NULL },
  { &class_reference_idx, 1, sizeof (class_reference_idx), NULL, NULL },
  { &selector_reference_idx, 1, sizeof (selector_reference_idx), NULL, NULL },
  { &num_static_inst, 1, sizeof (num_static_inst), NULL, NULL },
  { &string_layout_checked, 1, sizeof (string_layout_checked), NULL, NULL },
  { &objc_public_flag, 1, sizeof (objc_public_flag), NULL, NULL },
  { &objc_inherit_code, 1, sizeof (objc_inherit_code), NULL, NULL },
  { &cat_count, 1, sizeof (cat_count), NULL, NULL },
  { &imp_count, 1, sizeof (imp_count), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

