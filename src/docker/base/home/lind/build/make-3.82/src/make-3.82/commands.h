/* Definition of data structures describing shell commands for GNU Make.
Copyright (C) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997,
1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
2010 Free Software Foundation, Inc.
This file is part of GNU Make.

GNU Make is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

GNU Make is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* Structure that gives the commands to make a file
   and information about where these commands came from.  */

struct commands
  {
    struct floc fileinfo;	/* Where commands were defined.  */
    char *commands;		/* Commands text.  */
    unsigned int ncommand_lines;/* Number of command lines.  */
    char **command_lines;	/* Commands chopped up into lines.  */
    char *lines_flags;		/* One set of flag bits for each line.  */
    int any_recurse;		/* Nonzero if any `lines_recurse' elt has */
				/* the COMMANDS_RECURSE bit set.  */
  };

/* Bits in `lines_flags'.  */
#define	COMMANDS_RECURSE	1 /* Recurses: + or $(MAKE).  */
#define	COMMANDS_SILENT		2 /* Silent: @.  */
#define	COMMANDS_NOERROR	4 /* No errors: -.  */

void execute_file_commands (struct file *file);
void print_commands (const struct commands *cmds);
void delete_child_targets (struct child *child);
void chop_commands (struct commands *cmds);
void set_file_variables (struct file *file);
