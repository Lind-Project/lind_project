/* Type information for varpool.c.
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

const struct ggc_root_tab gt_ggc_r_gt_varpool_h[] = {
  {
    &varpool_assembled_nodes_queue,
    1,
    sizeof (varpool_assembled_nodes_queue),
    &gt_ggc_mx_varpool_node,
    &gt_pch_nx_varpool_node
  },
  {
    &varpool_first_unanalyzed_node,
    1,
    sizeof (varpool_first_unanalyzed_node),
    &gt_ggc_mx_varpool_node,
    &gt_pch_nx_varpool_node
  },
  {
    &varpool_last_needed_node,
    1,
    sizeof (varpool_last_needed_node),
    &gt_ggc_mx_varpool_node,
    &gt_pch_nx_varpool_node
  },
  {
    &varpool_hash,
    1,
    sizeof (varpool_hash),
    &gt_ggc_m_P12varpool_node4htab,
    &gt_pch_n_P12varpool_node4htab
  },
  LAST_GGC_ROOT_TAB
};

