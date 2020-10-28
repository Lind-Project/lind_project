/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_PLPGSQL_YY_PL_GRAM_H_INCLUDED
# define YY_PLPGSQL_YY_PL_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int plpgsql_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENT = 258,
    UIDENT = 259,
    FCONST = 260,
    SCONST = 261,
    USCONST = 262,
    BCONST = 263,
    XCONST = 264,
    Op = 265,
    ICONST = 266,
    PARAM = 267,
    TYPECAST = 268,
    DOT_DOT = 269,
    COLON_EQUALS = 270,
    EQUALS_GREATER = 271,
    LESS_EQUALS = 272,
    GREATER_EQUALS = 273,
    NOT_EQUALS = 274,
    T_WORD = 275,
    T_CWORD = 276,
    T_DATUM = 277,
    LESS_LESS = 278,
    GREATER_GREATER = 279,
    K_ABSOLUTE = 280,
    K_ALIAS = 281,
    K_ALL = 282,
    K_AND = 283,
    K_ARRAY = 284,
    K_ASSERT = 285,
    K_BACKWARD = 286,
    K_BEGIN = 287,
    K_BY = 288,
    K_CALL = 289,
    K_CASE = 290,
    K_CHAIN = 291,
    K_CLOSE = 292,
    K_COLLATE = 293,
    K_COLUMN = 294,
    K_COLUMN_NAME = 295,
    K_COMMIT = 296,
    K_CONSTANT = 297,
    K_CONSTRAINT = 298,
    K_CONSTRAINT_NAME = 299,
    K_CONTINUE = 300,
    K_CURRENT = 301,
    K_CURSOR = 302,
    K_DATATYPE = 303,
    K_DEBUG = 304,
    K_DECLARE = 305,
    K_DEFAULT = 306,
    K_DETAIL = 307,
    K_DIAGNOSTICS = 308,
    K_DO = 309,
    K_DUMP = 310,
    K_ELSE = 311,
    K_ELSIF = 312,
    K_END = 313,
    K_ERRCODE = 314,
    K_ERROR = 315,
    K_EXCEPTION = 316,
    K_EXECUTE = 317,
    K_EXIT = 318,
    K_FETCH = 319,
    K_FIRST = 320,
    K_FOR = 321,
    K_FOREACH = 322,
    K_FORWARD = 323,
    K_FROM = 324,
    K_GET = 325,
    K_HINT = 326,
    K_IF = 327,
    K_IMPORT = 328,
    K_IN = 329,
    K_INFO = 330,
    K_INSERT = 331,
    K_INTO = 332,
    K_IS = 333,
    K_LAST = 334,
    K_LOG = 335,
    K_LOOP = 336,
    K_MESSAGE = 337,
    K_MESSAGE_TEXT = 338,
    K_MOVE = 339,
    K_NEXT = 340,
    K_NO = 341,
    K_NOT = 342,
    K_NOTICE = 343,
    K_NULL = 344,
    K_OPEN = 345,
    K_OPTION = 346,
    K_OR = 347,
    K_PERFORM = 348,
    K_PG_CONTEXT = 349,
    K_PG_DATATYPE_NAME = 350,
    K_PG_EXCEPTION_CONTEXT = 351,
    K_PG_EXCEPTION_DETAIL = 352,
    K_PG_EXCEPTION_HINT = 353,
    K_PRINT_STRICT_PARAMS = 354,
    K_PRIOR = 355,
    K_QUERY = 356,
    K_RAISE = 357,
    K_RELATIVE = 358,
    K_RESET = 359,
    K_RETURN = 360,
    K_RETURNED_SQLSTATE = 361,
    K_REVERSE = 362,
    K_ROLLBACK = 363,
    K_ROW_COUNT = 364,
    K_ROWTYPE = 365,
    K_SCHEMA = 366,
    K_SCHEMA_NAME = 367,
    K_SCROLL = 368,
    K_SET = 369,
    K_SLICE = 370,
    K_SQLSTATE = 371,
    K_STACKED = 372,
    K_STRICT = 373,
    K_TABLE = 374,
    K_TABLE_NAME = 375,
    K_THEN = 376,
    K_TO = 377,
    K_TYPE = 378,
    K_USE_COLUMN = 379,
    K_USE_VARIABLE = 380,
    K_USING = 381,
    K_VARIABLE_CONFLICT = 382,
    K_WARNING = 383,
    K_WHEN = 384,
    K_WHILE = 385
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 120 "pl_gram.y" /* yacc.c:1921  */

		core_YYSTYPE			core_yystype;
		/* these fields must match core_YYSTYPE: */
		int						ival;
		char					*str;
		const char				*keyword;

		PLword					word;
		PLcword					cword;
		PLwdatum				wdatum;
		bool					boolean;
		Oid						oid;
		struct
		{
			char *name;
			int  lineno;
		}						varname;
		struct
		{
			char *name;
			int  lineno;
			PLpgSQL_datum   *scalar;
			PLpgSQL_datum   *row;
		}						forvariable;
		struct
		{
			char *label;
			int  n_initvars;
			int  *initvarnos;
		}						declhdr;
		struct
		{
			List *stmts;
			char *end_label;
			int   end_label_location;
		}						loop_body;
		List					*list;
		PLpgSQL_type			*dtype;
		PLpgSQL_datum			*datum;
		PLpgSQL_var				*var;
		PLpgSQL_expr			*expr;
		PLpgSQL_stmt			*stmt;
		PLpgSQL_condition		*condition;
		PLpgSQL_exception		*exception;
		PLpgSQL_exception_block	*exception_block;
		PLpgSQL_nsitem			*nsitem;
		PLpgSQL_diag_item		*diagitem;
		PLpgSQL_stmt_fetch		*fetch;
		PLpgSQL_case_when		*casewhen;

#line 240 "pl_gram.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE plpgsql_yylval;
extern YYLTYPE plpgsql_yylloc;
int plpgsql_yyparse (void);

#endif /* !YY_PLPGSQL_YY_PL_GRAM_H_INCLUDED  */
