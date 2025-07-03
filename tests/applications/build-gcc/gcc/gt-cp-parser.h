/* Type information for cp/parser.c.
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
gt_ggc_mx_cp_parser (void *x_p)
{
  struct cp_parser * const x = (struct cp_parser *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_8cp_lexer ((*x).lexer);
      gt_ggc_m_9tree_node ((*x).scope);
      gt_ggc_m_9tree_node ((*x).object_scope);
      gt_ggc_m_9tree_node ((*x).qualifying_scope);
      gt_ggc_m_17cp_parser_context ((*x).context);
      gt_ggc_m_S ((*x).type_definition_forbidden_message);
      gt_ggc_m_9tree_node ((*x).unparsed_functions_queues);
    }
}

void
gt_ggc_mx_cp_parser_context (void *x_p)
{
  struct cp_parser_context * const x = (struct cp_parser_context *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).object_type);
      gt_ggc_m_17cp_parser_context ((*x).next);
    }
}

void
gt_ggc_mx_cp_lexer (void *x_p)
{
  struct cp_lexer * const x = (struct cp_lexer *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      if ((*x).buffer != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).buffer_length); i0++) {
          switch ((((*x).buffer[i0]).type == CPP_TEMPLATE_ID) || (((*x).buffer[i0]).type == CPP_NESTED_NAME_SPECIFIER))
            {
            case 1:
              gt_ggc_m_10tree_check ((*x).buffer[i0].u.tree_check_value);
              break;
            case 0:
              gt_ggc_m_9tree_node ((*x).buffer[i0].u.value);
              break;
            default:
              break;
            }
        }
        ggc_mark ((*x).buffer);
      }
      gt_ggc_m_8cp_lexer ((*x).next);
    }
}

void
gt_ggc_mx_tree_check (void *x_p)
{
  struct tree_check * const x = (struct tree_check *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).value);
      gt_ggc_m_28VEC_deferred_access_check_gc ((*x).checks);
      gt_ggc_m_9tree_node ((*x).qualifying_scope);
    }
}

void
gt_ggc_mx_cp_token_cache (void *x_p)
{
  struct cp_token_cache * const x = (struct cp_token_cache *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_pch_nx_cp_parser (void *x_p)
{
  struct cp_parser * const x = (struct cp_parser *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9cp_parser, gt_ggc_e_9cp_parser))
    {
      gt_pch_n_8cp_lexer ((*x).lexer);
      gt_pch_n_9tree_node ((*x).scope);
      gt_pch_n_9tree_node ((*x).object_scope);
      gt_pch_n_9tree_node ((*x).qualifying_scope);
      gt_pch_n_17cp_parser_context ((*x).context);
      gt_pch_n_S ((*x).type_definition_forbidden_message);
      gt_pch_n_9tree_node ((*x).unparsed_functions_queues);
    }
}

void
gt_pch_nx_cp_parser_context (void *x_p)
{
  struct cp_parser_context * const x = (struct cp_parser_context *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17cp_parser_context, gt_ggc_e_17cp_parser_context))
    {
      gt_pch_n_9tree_node ((*x).object_type);
      gt_pch_n_17cp_parser_context ((*x).next);
    }
}

void
gt_pch_nx_cp_lexer (void *x_p)
{
  struct cp_lexer * const x = (struct cp_lexer *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8cp_lexer, gt_ggc_e_8cp_lexer))
    {
      if ((*x).buffer != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).buffer_length); i0++) {
          switch ((((*x).buffer[i0]).type == CPP_TEMPLATE_ID) || (((*x).buffer[i0]).type == CPP_NESTED_NAME_SPECIFIER))
            {
            case 1:
              gt_pch_n_10tree_check ((*x).buffer[i0].u.tree_check_value);
              break;
            case 0:
              gt_pch_n_9tree_node ((*x).buffer[i0].u.value);
              break;
            default:
              break;
            }
        }
        gt_pch_note_object ((*x).buffer, x, gt_pch_p_8cp_lexer, gt_types_enum_last);
      }
      gt_pch_n_8cp_lexer ((*x).next);
    }
}

void
gt_pch_nx_tree_check (void *x_p)
{
  struct tree_check * const x = (struct tree_check *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_10tree_check, gt_ggc_e_10tree_check))
    {
      gt_pch_n_9tree_node ((*x).value);
      gt_pch_n_28VEC_deferred_access_check_gc ((*x).checks);
      gt_pch_n_9tree_node ((*x).qualifying_scope);
    }
}

void
gt_pch_nx_cp_token_cache (void *x_p)
{
  struct cp_token_cache * const x = (struct cp_token_cache *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14cp_token_cache, gt_ggc_e_14cp_token_cache))
    {
    }
}

void
gt_pch_p_9cp_parser (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cp_parser * const x ATTRIBUTE_UNUSED = (struct cp_parser *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).lexer), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).scope), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).object_scope), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).qualifying_scope), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).context), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).type_definition_forbidden_message), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).unparsed_functions_queues), cookie);
}

void
gt_pch_p_17cp_parser_context (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cp_parser_context * const x ATTRIBUTE_UNUSED = (struct cp_parser_context *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).object_type), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_8cp_lexer (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cp_lexer * const x ATTRIBUTE_UNUSED = (struct cp_lexer *)x_p;
  if ((*x).buffer != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(((*x)).buffer_length); i0++) {
      switch ((((*x).buffer[i0]).type == CPP_TEMPLATE_ID) || (((*x).buffer[i0]).type == CPP_NESTED_NAME_SPECIFIER))
        {
        case 1:
          if ((void *)((*x).buffer) == this_obj)
            op (&((*x).buffer[i0].u.tree_check_value), cookie);
          break;
        case 0:
          if ((void *)((*x).buffer) == this_obj)
            op (&((*x).buffer[i0].u.value), cookie);
          break;
        default:
          break;
        }
    }
    if ((void *)(x) == this_obj)
      op (&((*x).buffer), cookie);
  }
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_10tree_check (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_check * const x ATTRIBUTE_UNUSED = (struct tree_check *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).checks), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).qualifying_scope), cookie);
}

void
gt_pch_p_14cp_token_cache (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cp_token_cache * const x ATTRIBUTE_UNUSED = (struct cp_token_cache *)x_p;
}

/* GC roots.  */

const struct ggc_root_tab gt_ggc_r_gt_cp_parser_h[] = {
  {
    &the_parser,
    1,
    sizeof (the_parser),
    &gt_ggc_mx_cp_parser,
    &gt_pch_nx_cp_parser
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_ggc_rd_gt_cp_parser_h[] = {
  { &cp_parser_context_free_list, 1, sizeof (cp_parser_context_free_list), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

