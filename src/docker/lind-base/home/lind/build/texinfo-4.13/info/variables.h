/* variables.h -- Description of user visible variables in Info.
   $Id: variables.h,v 1.9 2008/03/04 09:45:27 gray Exp $

   This file is part of GNU Info, a program for reading online documentation
   stored in Info format.

   Copyright (C) 1993, 1997, 2004, 2007 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Written by Brian Fox (bfox@ai.mit.edu). */

#ifndef INFO_VARIABLES_H
#define INFO_VARIABLES_H

/* A variable (in the Info sense) is an integer value with a user-visible
   name.  You may supply an array of strings to complete over when the
   variable is set; in that case, the variable is set to the index of the
   string that the user chose.  If you supply a null list, the user can
   set the variable to a numeric value. */

/* Structure describing a user visible variable. */
typedef struct {
  char *name;                   /* Polite name. */
  char *doc;                    /* Documentation string. */
  int *value;                   /* Address of value. */
  char **choices;               /* Array of strings or NULL if numeric only. */
} VARIABLE_ALIST;

/* Read the name of an Info variable in the echo area and return the
   address of a VARIABLE_ALIST member.  A return value of NULL indicates
   that no variable could be read. */
extern VARIABLE_ALIST *read_variable_name (const char *prompt, WINDOW *window);

/* Make an array of REFERENCE which actually contains the names of the
   variables available in Info. */
extern REFERENCE **make_variable_completions_array (void);

/* Set the value of an info variable. */
extern void set_variable (WINDOW *window, int count, unsigned char key);
extern void describe_variable (WINDOW *window, int count, unsigned char key);

/* The list of user-visible variables. */
extern int auto_footnotes_p;
extern int auto_tiling_p;
extern int terminal_use_visible_bell_p;
extern int info_error_rings_bell_p;
extern int gc_compressed_files;
extern int show_index_match;
extern int info_scroll_behaviour;
extern int window_scroll_step;
extern int cursor_movement_scrolls_p;
extern int ISO_Latin_p;
extern int scroll_last_node;

#endif /* not INFO_VARIABLES_H */
