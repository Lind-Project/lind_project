/* Type information for java/class.c.
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

/* GC roots.  */

const struct ggc_root_tab gt_ggc_r_gt_java_class_h[] = {
  {
    &utf8_decl_list,
    1,
    sizeof (utf8_decl_list),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &this_classdollar,
    1,
    sizeof (this_classdollar),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &registered_class,
    1,
    sizeof (registered_class),
    &gt_ggc_mx_VEC_tree_gc,
    &gt_pch_nx_VEC_tree_gc
  },
  {
    &class_roots[0],
    1 * (4),
    sizeof (class_roots[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

const struct ggc_root_tab gt_pch_rs_gt_java_class_h[] = {
  { &alias_labelno, 1, sizeof (alias_labelno), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

