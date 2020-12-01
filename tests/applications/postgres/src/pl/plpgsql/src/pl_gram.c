/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         plpgsql_yyparse
#define yylex           plpgsql_yylex
#define yyerror         plpgsql_yyerror
#define yydebug         plpgsql_yydebug
#define yynerrs         plpgsql_yynerrs

#define yylval          plpgsql_yylval
#define yychar          plpgsql_yychar
#define yylloc          plpgsql_yylloc

/* First part of user prologue.  */
#line 1 "pl_gram.y" /* yacc.c:337  */

/*-------------------------------------------------------------------------
 *
 * pl_gram.y			- Parser for the PL/pgSQL procedural language
 *
 * Portions Copyright (c) 1996-2020, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/pl/plpgsql/src/pl_gram.y
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include "catalog/namespace.h"
#include "catalog/pg_proc.h"
#include "catalog/pg_type.h"
#include "parser/parser.h"
#include "parser/parse_type.h"
#include "parser/scanner.h"
#include "parser/scansup.h"
#include "utils/builtins.h"

#include "plpgsql.h"


/* Location tracking support --- simpler than bison's default */
#define YYLLOC_DEFAULT(Current, Rhs, N) \
	do { \
		if (N) \
			(Current) = (Rhs)[1]; \
		else \
			(Current) = (Rhs)[0]; \
	} while (0)

/*
 * Bison doesn't allocate anything that needs to live across parser calls,
 * so we can easily have it use palloc instead of malloc.  This prevents
 * memory leaks if we error out during parsing.  Note this only works with
 * bison >= 2.0.  However, in bison 1.875 the default is to use alloca()
 * if possible, so there's not really much problem anyhow, at least if
 * you're building with gcc.
 */
#define YYMALLOC palloc
#define YYFREE   pfree


typedef struct
{
	int			location;
	int			leaderlen;
} sql_error_callback_arg;

#define parser_errposition(pos)  plpgsql_scanner_errposition(pos)

union YYSTYPE;					/* need forward reference for tok_is_keyword */

static	bool			tok_is_keyword(int token, union YYSTYPE *lval,
									   int kw_token, const char *kw_str);
static	void			word_is_not_variable(PLword *word, int location);
static	void			cword_is_not_variable(PLcword *cword, int location);
static	void			current_token_is_not_variable(int tok);
static	PLpgSQL_expr	*read_sql_construct(int until,
											int until2,
											int until3,
											const char *expected,
											const char *sqlstart,
											bool isexpression,
											bool valid_sql,
											bool trim,
											int *startloc,
											int *endtoken);
static	PLpgSQL_expr	*read_sql_expression(int until,
											 const char *expected);
static	PLpgSQL_expr	*read_sql_expression2(int until, int until2,
											  const char *expected,
											  int *endtoken);
static	PLpgSQL_expr	*read_sql_stmt(const char *sqlstart);
static	PLpgSQL_type	*read_datatype(int tok);
static	PLpgSQL_stmt	*make_execsql_stmt(int firsttoken, int location);
static	PLpgSQL_stmt_fetch *read_fetch_direction(void);
static	void			 complete_direction(PLpgSQL_stmt_fetch *fetch,
											bool *check_FROM);
static	PLpgSQL_stmt	*make_return_stmt(int location);
static	PLpgSQL_stmt	*make_return_next_stmt(int location);
static	PLpgSQL_stmt	*make_return_query_stmt(int location);
static  PLpgSQL_stmt	*make_case(int location, PLpgSQL_expr *t_expr,
								   List *case_when_list, List *else_stmts);
static	char			*NameOfDatum(PLwdatum *wdatum);
static	void			 check_assignable(PLpgSQL_datum *datum, int location);
static	void			 read_into_target(PLpgSQL_variable **target,
										  bool *strict);
static	PLpgSQL_row		*read_into_scalar_list(char *initial_name,
											   PLpgSQL_datum *initial_datum,
											   int initial_location);
static	PLpgSQL_row		*make_scalar_list1(char *initial_name,
										   PLpgSQL_datum *initial_datum,
										   int lineno, int location);
static	void			 check_sql_expr(const char *stmt, int location,
										int leaderlen);
static	void			 plpgsql_sql_error_callback(void *arg);
static	PLpgSQL_type	*parse_datatype(const char *string, int location);
static	void			 check_labels(const char *start_label,
									  const char *end_label,
									  int end_location);
static	PLpgSQL_expr	*read_cursor_args(PLpgSQL_var *cursor,
										  int until, const char *expected);
static	List			*read_raise_options(void);
static	void			check_raise_parameters(PLpgSQL_stmt_raise *stmt);


#line 194 "pl_gram.c" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "pl_gram.h".  */
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
#line 120 "pl_gram.y" /* yacc.c:352  */

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

#line 419 "pl_gram.c" /* yacc.c:352  */
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



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1465

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  138
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  258
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  342

#define YYUNDEFTOK  2
#define YYMAXUTOK   385

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   131,     2,     2,     2,     2,
     133,   134,     2,     2,   135,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   132,
       2,   136,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   137,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   363,   363,   369,   370,   373,   377,   386,   390,   394,
     400,   404,   409,   410,   413,   436,   444,   451,   460,   472,
     473,   476,   477,   481,   494,   532,   538,   537,   590,   593,
     597,   604,   610,   613,   644,   648,   654,   662,   663,   665,
     680,   695,   723,   751,   782,   783,   788,   799,   800,   805,
     810,   817,   818,   822,   824,   830,   831,   839,   840,   844,
     845,   855,   857,   859,   861,   863,   865,   867,   869,   871,
     873,   875,   877,   879,   881,   883,   885,   887,   889,   891,
     893,   895,   897,   899,   901,   903,   907,   921,   935,   952,
     967,  1030,  1033,  1037,  1043,  1047,  1053,  1066,  1110,  1121,
    1126,  1134,  1139,  1156,  1174,  1177,  1191,  1194,  1200,  1207,
    1221,  1225,  1231,  1243,  1246,  1261,  1279,  1298,  1334,  1596,
    1622,  1636,  1643,  1682,  1685,  1691,  1744,  1748,  1754,  1780,
    1925,  1949,  1967,  1971,  1975,  1985,  1997,  2061,  2139,  2169,
    2182,  2187,  2201,  2208,  2222,  2237,  2238,  2239,  2242,  2255,
    2270,  2292,  2297,  2305,  2307,  2306,  2348,  2352,  2358,  2371,
    2380,  2386,  2423,  2427,  2431,  2435,  2439,  2443,  2451,  2455,
    2463,  2466,  2473,  2475,  2482,  2486,  2490,  2499,  2500,  2501,
    2502,  2503,  2504,  2505,  2506,  2507,  2508,  2509,  2510,  2511,
    2512,  2513,  2514,  2515,  2516,  2517,  2518,  2519,  2520,  2521,
    2522,  2523,  2524,  2525,  2526,  2527,  2528,  2529,  2530,  2531,
    2532,  2533,  2534,  2535,  2536,  2537,  2538,  2539,  2540,  2541,
    2542,  2543,  2544,  2545,  2546,  2547,  2548,  2549,  2550,  2551,
    2552,  2553,  2554,  2555,  2556,  2557,  2558,  2559,  2560,  2561,
    2562,  2563,  2564,  2565,  2566,  2567,  2568,  2569,  2570,  2571,
    2572,  2573,  2574,  2575,  2576,  2577,  2578,  2579,  2580
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "UIDENT", "FCONST", "SCONST",
  "USCONST", "BCONST", "XCONST", "Op", "ICONST", "PARAM", "TYPECAST",
  "DOT_DOT", "COLON_EQUALS", "EQUALS_GREATER", "LESS_EQUALS",
  "GREATER_EQUALS", "NOT_EQUALS", "T_WORD", "T_CWORD", "T_DATUM",
  "LESS_LESS", "GREATER_GREATER", "K_ABSOLUTE", "K_ALIAS", "K_ALL",
  "K_AND", "K_ARRAY", "K_ASSERT", "K_BACKWARD", "K_BEGIN", "K_BY",
  "K_CALL", "K_CASE", "K_CHAIN", "K_CLOSE", "K_COLLATE", "K_COLUMN",
  "K_COLUMN_NAME", "K_COMMIT", "K_CONSTANT", "K_CONSTRAINT",
  "K_CONSTRAINT_NAME", "K_CONTINUE", "K_CURRENT", "K_CURSOR", "K_DATATYPE",
  "K_DEBUG", "K_DECLARE", "K_DEFAULT", "K_DETAIL", "K_DIAGNOSTICS", "K_DO",
  "K_DUMP", "K_ELSE", "K_ELSIF", "K_END", "K_ERRCODE", "K_ERROR",
  "K_EXCEPTION", "K_EXECUTE", "K_EXIT", "K_FETCH", "K_FIRST", "K_FOR",
  "K_FOREACH", "K_FORWARD", "K_FROM", "K_GET", "K_HINT", "K_IF",
  "K_IMPORT", "K_IN", "K_INFO", "K_INSERT", "K_INTO", "K_IS", "K_LAST",
  "K_LOG", "K_LOOP", "K_MESSAGE", "K_MESSAGE_TEXT", "K_MOVE", "K_NEXT",
  "K_NO", "K_NOT", "K_NOTICE", "K_NULL", "K_OPEN", "K_OPTION", "K_OR",
  "K_PERFORM", "K_PG_CONTEXT", "K_PG_DATATYPE_NAME",
  "K_PG_EXCEPTION_CONTEXT", "K_PG_EXCEPTION_DETAIL", "K_PG_EXCEPTION_HINT",
  "K_PRINT_STRICT_PARAMS", "K_PRIOR", "K_QUERY", "K_RAISE", "K_RELATIVE",
  "K_RESET", "K_RETURN", "K_RETURNED_SQLSTATE", "K_REVERSE", "K_ROLLBACK",
  "K_ROW_COUNT", "K_ROWTYPE", "K_SCHEMA", "K_SCHEMA_NAME", "K_SCROLL",
  "K_SET", "K_SLICE", "K_SQLSTATE", "K_STACKED", "K_STRICT", "K_TABLE",
  "K_TABLE_NAME", "K_THEN", "K_TO", "K_TYPE", "K_USE_COLUMN",
  "K_USE_VARIABLE", "K_USING", "K_VARIABLE_CONFLICT", "K_WARNING",
  "K_WHEN", "K_WHILE", "'#'", "';'", "'('", "')'", "','", "'='", "'['",
  "$accept", "pl_function", "comp_options", "comp_option", "option_value",
  "opt_semi", "pl_block", "decl_sect", "decl_start", "decl_stmts",
  "decl_stmt", "decl_statement", "$@1", "opt_scrollable",
  "decl_cursor_query", "decl_cursor_args", "decl_cursor_arglist",
  "decl_cursor_arg", "decl_is_for", "decl_aliasitem", "decl_varname",
  "decl_const", "decl_datatype", "decl_collate", "decl_notnull",
  "decl_defval", "decl_defkey", "assign_operator", "proc_sect",
  "proc_stmt", "stmt_perform", "stmt_call", "stmt_assign", "stmt_getdiag",
  "getdiag_area_opt", "getdiag_list", "getdiag_list_item", "getdiag_item",
  "getdiag_target", "assign_var", "stmt_if", "stmt_elsifs", "stmt_else",
  "stmt_case", "opt_expr_until_when", "case_when_list", "case_when",
  "opt_case_else", "stmt_loop", "stmt_while", "stmt_for", "for_control",
  "for_variable", "stmt_foreach_a", "foreach_slice", "stmt_exit",
  "exit_type", "stmt_return", "stmt_raise", "stmt_assert", "loop_body",
  "stmt_execsql", "stmt_dynexecute", "stmt_open", "stmt_fetch",
  "stmt_move", "opt_fetch_direction", "stmt_close", "stmt_null",
  "stmt_commit", "stmt_rollback", "opt_transaction_chain", "stmt_set",
  "cursor_variable", "exception_sect", "@2", "proc_exceptions",
  "proc_exception", "proc_conditions", "proc_condition", "expr_until_semi",
  "expr_until_rightbracket", "expr_until_then", "expr_until_loop",
  "opt_block_label", "opt_loop_label", "opt_label", "opt_exitcond",
  "any_identifier", "unreserved_keyword", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,    35,    59,    40,    41,    44,    61,    91
};
# endif

#define YYPACT_NINF -263

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-263)))

#define YYTABLE_NINF -168

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -263,    36,   -15,  -263,   367,   -68,  -263,   -89,    19,    11,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,    42,  -263,    16,   691,   -41,  -263,
    -263,  -263,  -263,   258,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  1084,  -263,   367,  -263,   258,  -263,  -263,     2,
    -263,  -263,  -263,  -263,   367,  -263,  -263,  -263,    71,    61,
    -263,  -263,  -263,  -263,  -263,  -263,   -37,  -263,  -263,  -263,
    -263,   -34,    71,  -263,  -263,  -263,  -263,    61,  -263,   -33,
    -263,  -263,  -263,  -263,  -263,   -12,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,   367,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,    43,   -28,    90,
    -263,    51,  -263,     5,  -263,    72,  -263,   104,     0,  -263,
    -263,  -263,    -2,   -19,    -1,     3,    71,  -263,  -263,    80,
    -263,    71,  -263,  -263,  -263,     4,  -263,  -263,  -263,  -263,
    -263,   -72,  -263,   367,    87,    87,  -263,  -263,  -263,   476,
    -263,  -263,    96,     8,  -263,   -54,  -263,  -263,  -263,    99,
    -263,   367,     3,  -263,    60,    91,   906,     6,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,    65,
      25,  1173,  -263,  -263,  -263,  -263,     9,  -263,    10,   585,
      55,  -263,  -263,  -263,    86,  -263,   -47,  -263,  -263,  -263,
    -263,  -263,  -263,   -62,  -263,    -9,    12,    22,  -263,  -263,
    -263,  -263,   134,    73,    67,  -263,  -263,   797,   -31,  -263,
    -263,  -263,    57,   -10,    -8,  1262,   115,   367,  -263,  -263,
      91,  -263,  -263,  -263,    93,  -263,   123,   367,   -48,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
      21,  -263,   148,  -263,  -263,  1351,  -263,    82,  -263,    23,
    -263,   797,  -263,  -263,  -263,   995,    24,  -263,  -263,  -263,
    -263,  -263
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,   166,     1,     0,     0,     4,    12,     0,    15,
     174,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,   175,     0,     0,     0,    13,
       2,    59,    18,    16,   167,     5,    10,     6,    11,     7,
       9,     8,   168,    42,     0,    22,    17,    20,    21,    44,
      43,   134,   135,   101,     0,   130,    87,   109,     0,   147,
     127,    88,   154,   136,   126,   140,    91,   164,   132,   133,
     140,     0,     0,   162,   129,   149,   128,   147,   148,     0,
      60,    75,    76,    62,    77,     0,    63,    64,    65,    66,
      67,    68,    69,   170,    70,    71,    72,    73,    74,    78,
      79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
      19,     0,    45,     0,    30,     0,    46,     0,     0,   151,
     152,   150,     0,     0,     0,     0,     0,    92,    93,     0,
      59,     0,   142,   137,    86,     0,    61,    58,    57,   163,
     162,     0,   171,   170,     0,     0,    59,   165,    23,     0,
      29,    26,    47,   169,   164,   113,   111,   141,   145,     0,
     143,     0,   155,   157,     0,     0,   168,     0,   144,   102,
      89,   162,   172,   125,    14,   120,   121,   119,    59,     0,
     123,   168,   115,    59,    39,    41,     0,    40,    32,     0,
      51,    59,    59,   110,     0,   146,     0,   160,   161,   156,
     138,    99,   100,     0,    95,     0,    98,   106,   139,   173,
     117,   118,     0,     0,     0,   116,    25,     0,     0,    48,
      50,    49,     0,     0,   168,   168,     0,     0,    59,    90,
       0,    97,    59,   164,     0,   124,     0,   170,     0,    34,
      46,    38,    37,    31,    52,    56,    53,    24,    54,    55,
       0,   159,   168,    94,    96,   168,    59,     0,   165,     0,
      33,     0,    36,    27,   108,   168,     0,    59,   131,    35,
     103,   122
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -263,  -263,  -263,  -263,  -263,  -263,   155,  -263,  -263,  -263,
      44,  -263,  -263,  -263,  -263,  -263,  -263,  -173,  -263,  -263,
    -262,  -263,  -151,  -263,  -263,  -263,  -263,  -241,   -97,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -139,  -263,  -263,  -205,
    -263,  -263,  -263,  -263,  -263,  -263,   -63,  -263,  -263,  -263,
    -263,  -263,   -49,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -232,  -263,  -263,  -263,  -263,  -263,    27,  -263,  -263,  -263,
    -263,    26,  -263,  -124,  -263,  -263,  -263,   -60,  -263,  -123,
    -178,  -263,  -213,  -153,  -263,  -263,  -203,  -263,    -4,   -96
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,   107,   100,   149,     8,   103,   116,
     117,   118,   258,   185,   333,   288,   308,   309,   313,   256,
     119,   186,   222,   260,   293,   317,   318,   210,   251,   150,
     151,   152,   153,   154,   199,   273,   274,   324,   275,   155,
     156,   277,   304,   157,   188,   225,   226,   264,   158,   159,
     160,   248,   249,   161,   283,   162,   163,   164,   165,   166,
     252,   167,   168,   169,   170,   171,   196,   172,   173,   174,
     175,   194,   176,   192,   177,   195,   232,   233,   266,   267,
     204,   239,   200,   253,     9,   178,   211,   243,   212,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      94,   108,   262,   207,   112,   207,   207,   120,     4,   197,
     244,   261,   121,   122,   123,   124,   280,   228,   203,   109,
     120,   285,   125,    96,  -166,   310,   126,   127,   181,   128,
     276,    97,   240,   129,   301,   311,     3,   130,   214,   215,
    -167,   315,  -166,    99,   182,   297,   131,   312,  -112,   -28,
    -112,   101,   319,   216,   133,   134,   135,   241,  -167,    98,
     242,   102,   136,   279,   137,   138,   104,   229,   139,   310,
     299,   105,   234,   300,   298,   224,   140,   237,   302,   303,
     198,   141,   142,   110,   111,   143,   330,   331,   183,   193,
     326,   189,   190,   191,   144,   276,   145,   146,   202,   206,
     147,   213,   217,   236,   329,   341,   148,   245,   246,   247,
     179,   271,   272,   123,   218,   184,     5,   219,   220,   221,
     187,  -112,   316,   257,   208,   209,   208,   208,   223,   224,
     227,   230,   231,   235,   259,   265,   238,   270,   278,   281,
     282,   286,   292,   287,   296,   305,   314,   306,   307,   209,
     320,   327,   328,   334,   336,   338,   340,     7,   339,   332,
     180,   323,   263,   291,   294,   295,   250,   201,   121,   122,
     123,   124,   269,   205,   321,   337,     0,     0,   125,     0,
    -166,     0,   126,   127,     0,   128,     0,     0,     0,   129,
       0,   120,     0,   130,     0,     0,     0,     0,  -166,     0,
       0,   322,   131,     0,     0,   325,  -158,     0,     0,     0,
     133,   134,   135,     0,     0,     0,     0,     0,   136,     0,
     137,   138,     0,     0,   139,     0,     0,   268,     0,   335,
       0,     0,   140,     0,     0,   120,     0,   141,   142,     0,
       0,   143,     0,     0,     0,     0,     0,     0,     0,     0,
     144,     0,   145,   146,     0,     0,   147,     0,     0,     0,
       0,     0,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -158,   113,     0,
       0,   114,     0,    12,    13,     0,    14,    15,    16,    17,
       0,     0,    18,   268,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   115,    33,
      34,    35,    36,    37,     0,    38,     0,    39,    40,    41,
       0,    42,    43,    44,     0,     0,    45,     0,    46,    47,
       0,    48,     0,    49,    50,     0,    51,    52,    53,     0,
      54,    55,    56,    57,    58,     0,    59,     0,    60,    61,
       0,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,     0,    87,    88,     0,
       0,    89,    90,    91,     0,    92,    93,    10,     0,    11,
       0,     0,    12,    13,     0,    14,    15,    16,    17,     0,
       0,    18,     0,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
      35,    36,    37,     0,    38,     0,    39,    40,    41,     0,
      42,    43,    44,     0,     0,    45,     0,    46,    47,     0,
      48,     0,    49,    50,     0,    51,    52,    53,     0,    54,
      55,    56,    57,    58,     0,    59,     0,    60,    61,     0,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,     0,    87,    88,     0,     0,
      89,    90,    91,     0,    92,    93,   254,   255,     0,     0,
       0,    12,    13,     0,    14,    15,    16,    17,     0,     0,
      18,     0,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     0,    33,    34,    35,
      36,    37,     0,    38,     0,    39,    40,    41,     0,    42,
      43,    44,     0,     0,    45,     0,    46,    47,     0,    48,
       0,    49,    50,     0,    51,    52,    53,     0,    54,    55,
      56,    57,    58,     0,    59,     0,    60,    61,     0,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,     0,    87,    88,     0,     0,    89,
      90,    91,     0,    92,    93,   289,   290,     0,     0,     0,
      12,    13,     0,    14,    15,    16,    17,     0,     0,    18,
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,    33,    34,    35,    36,
      37,     0,    38,     0,    39,    40,    41,     0,    42,    43,
      44,     0,     0,    45,     0,    46,    47,     0,    48,     0,
      49,    50,     0,    51,    52,    53,     0,    54,    55,    56,
      57,    58,     0,    59,     0,    60,    61,     0,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,     0,    87,    88,     0,     0,    89,    90,
      91,   106,    92,    93,     0,     0,    12,    13,     0,    14,
      15,    16,    17,     0,     0,    18,     0,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,    33,    34,    35,    36,    37,     0,    38,     0,
      39,    40,    41,     0,    42,    43,    44,     0,     0,    45,
       0,    46,    47,     0,    48,     0,    49,    50,     0,    51,
      52,    53,     0,    54,    55,    56,    57,    58,     0,    59,
       0,    60,    61,     0,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,     0,
      87,    88,     0,     0,    89,    90,    91,   113,    92,    93,
       0,     0,    12,    13,     0,    14,    15,    16,    17,     0,
       0,    18,     0,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
      35,    36,    37,     0,    38,     0,    39,    40,    41,     0,
      42,    43,    44,     0,     0,    45,     0,    46,    47,     0,
      48,     0,    49,    50,     0,    51,    52,    53,     0,    54,
      55,    56,    57,    58,     0,    59,     0,    60,    61,     0,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,     0,    87,    88,     0,     0,
      89,    90,    91,     0,    92,    93,   121,   122,   123,   124,
       0,     0,     0,     0,     0,     0,   125,     0,  -166,     0,
     126,   127,     0,   128,     0,     0,     0,   129,     0,     0,
       0,   130,     0,     0,     0,     0,  -166,     0,     0,     0,
     131,     0,  -104,  -104,  -104,     0,     0,     0,   133,   134,
     135,     0,     0,     0,     0,     0,   136,     0,   137,   138,
       0,     0,   139,     0,     0,     0,     0,     0,     0,     0,
     140,     0,     0,     0,     0,   141,   142,     0,     0,   143,
       0,     0,     0,     0,     0,     0,     0,     0,   144,     0,
     145,   146,     0,     0,   147,   121,   122,   123,   124,     0,
     148,     0,     0,     0,     0,   125,     0,  -166,     0,   126,
     127,     0,   128,     0,     0,     0,   129,     0,     0,     0,
     130,     0,     0,     0,     0,  -166,     0,     0,     0,   131,
       0,  -105,  -105,  -105,     0,     0,     0,   133,   134,   135,
       0,     0,     0,     0,     0,   136,     0,   137,   138,     0,
       0,   139,     0,     0,     0,     0,     0,     0,     0,   140,
       0,     0,     0,     0,   141,   142,     0,     0,   143,     0,
       0,     0,     0,     0,     0,     0,     0,   144,     0,   145,
     146,     0,     0,   147,   121,   122,   123,   124,     0,   148,
       0,     0,     0,     0,   125,     0,  -166,     0,   126,   127,
       0,   128,     0,     0,     0,   129,     0,     0,     0,   130,
       0,     0,     0,     0,  -166,     0,     0,     0,   131,     0,
       0,     0,  -153,     0,     0,   132,   133,   134,   135,     0,
       0,     0,     0,     0,   136,     0,   137,   138,     0,     0,
     139,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,     0,   141,   142,     0,     0,   143,     0,     0,
       0,     0,     0,     0,     0,     0,   144,     0,   145,   146,
       0,     0,   147,   121,   122,   123,   124,     0,   148,     0,
       0,     0,     0,   125,     0,  -166,     0,   126,   127,     0,
     128,     0,     0,     0,   129,     0,     0,     0,   130,     0,
       0,     0,     0,  -166,     0,     0,     0,   131,     0,     0,
       0,   284,     0,     0,     0,   133,   134,   135,     0,     0,
       0,     0,     0,   136,     0,   137,   138,     0,     0,   139,
       0,     0,     0,     0,     0,     0,     0,   140,     0,     0,
       0,     0,   141,   142,     0,     0,   143,     0,     0,     0,
       0,     0,     0,     0,     0,   144,     0,   145,   146,     0,
       0,   147,   121,   122,   123,   124,     0,   148,     0,     0,
       0,     0,   125,     0,  -166,     0,   126,   127,     0,   128,
       0,     0,     0,   129,     0,     0,     0,   130,     0,     0,
       0,     0,  -166,     0,     0,     0,   131,     0,     0,     0,
    -114,     0,     0,     0,   133,   134,   135,     0,     0,     0,
       0,     0,   136,     0,   137,   138,     0,     0,   139,     0,
       0,     0,     0,     0,     0,     0,   140,     0,     0,     0,
       0,   141,   142,     0,     0,   143,     0,     0,     0,     0,
       0,     0,     0,     0,   144,     0,   145,   146,     0,     0,
     147,   121,   122,   123,   124,     0,   148,     0,     0,     0,
       0,   125,     0,  -166,     0,   126,   127,     0,   128,     0,
       0,     0,   129,     0,     0,     0,   130,     0,     0,     0,
       0,  -166,     0,     0,     0,   131,     0,     0,     0,  -107,
       0,     0,     0,   133,   134,   135,     0,     0,     0,     0,
       0,   136,     0,   137,   138,     0,     0,   139,     0,     0,
       0,     0,     0,     0,     0,   140,     0,     0,     0,     0,
     141,   142,     0,     0,   143,     0,     0,     0,     0,     0,
       0,     0,     0,   144,     0,   145,   146,     0,     0,   147,
       0,     0,     0,     0,     0,   148
};

static const yytype_int16 yycheck[] =
{
       4,    97,    56,    15,   101,    15,    15,   103,    23,    46,
     213,   224,    20,    21,    22,    23,   248,    36,   142,    60,
     116,   253,    30,    91,    32,   287,    34,    35,    26,    37,
     235,    99,   210,    41,   275,    66,     0,    45,    66,    67,
      32,    51,    50,   132,    42,    92,    54,    78,    56,    47,
      58,    32,   293,    81,    62,    63,    64,   129,    50,   127,
     132,    50,    70,   241,    72,    73,    24,    86,    76,   331,
     132,    55,   196,   135,   121,   129,    84,   201,    56,    57,
     117,    89,    90,   124,   125,    93,   134,   135,    86,    28,
     303,    20,    21,    22,   102,   300,   104,   105,   132,   132,
     108,    58,   130,   200,   307,   337,   114,    20,    21,    22,
     114,    20,    21,    22,    24,   113,   131,    66,   113,    47,
     124,   129,   132,   219,   136,   137,   136,   136,    24,   129,
     132,   132,   129,    53,    38,    36,   132,    77,   132,    74,
     115,   132,    87,   133,    58,    11,    89,    74,    81,   137,
      35,    58,    29,   132,    72,   132,   132,     2,   331,   310,
     116,   300,   225,   259,   261,   262,   215,   140,    20,    21,
      22,    23,   232,   147,   297,   328,    -1,    -1,    30,    -1,
      32,    -1,    34,    35,    -1,    37,    -1,    -1,    -1,    41,
      -1,   287,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,
      -1,   298,    54,    -1,    -1,   302,    58,    -1,    -1,    -1,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      72,    73,    -1,    -1,    76,    -1,    -1,   231,    -1,   326,
      -1,    -1,    84,    -1,    -1,   331,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,   104,   105,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,    20,    -1,
      -1,    23,    -1,    25,    26,    -1,    28,    29,    30,    31,
      -1,    -1,    34,   297,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    57,    -1,    59,    60,    61,
      -1,    63,    64,    65,    -1,    -1,    68,    -1,    70,    71,
      -1,    73,    -1,    75,    76,    -1,    78,    79,    80,    -1,
      82,    83,    84,    85,    86,    -1,    88,    -1,    90,    91,
      -1,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,    -1,   119,   120,    -1,
      -1,   123,   124,   125,    -1,   127,   128,    20,    -1,    22,
      -1,    -1,    25,    26,    -1,    28,    29,    30,    31,    -1,
      -1,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    -1,    57,    -1,    59,    60,    61,    -1,
      63,    64,    65,    -1,    -1,    68,    -1,    70,    71,    -1,
      73,    -1,    75,    76,    -1,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    -1,    88,    -1,    90,    91,    -1,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    -1,   119,   120,    -1,    -1,
     123,   124,   125,    -1,   127,   128,    20,    21,    -1,    -1,
      -1,    25,    26,    -1,    28,    29,    30,    31,    -1,    -1,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    55,    -1,    57,    -1,    59,    60,    61,    -1,    63,
      64,    65,    -1,    -1,    68,    -1,    70,    71,    -1,    73,
      -1,    75,    76,    -1,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    -1,    88,    -1,    90,    91,    -1,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    -1,   119,   120,    -1,    -1,   123,
     124,   125,    -1,   127,   128,    20,    21,    -1,    -1,    -1,
      25,    26,    -1,    28,    29,    30,    31,    -1,    -1,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    -1,    51,    52,    53,    54,
      55,    -1,    57,    -1,    59,    60,    61,    -1,    63,    64,
      65,    -1,    -1,    68,    -1,    70,    71,    -1,    73,    -1,
      75,    76,    -1,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    -1,    88,    -1,    90,    91,    -1,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,    -1,   119,   120,    -1,    -1,   123,   124,
     125,    20,   127,   128,    -1,    -1,    25,    26,    -1,    28,
      29,    30,    31,    -1,    -1,    34,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    -1,    57,    -1,
      59,    60,    61,    -1,    63,    64,    65,    -1,    -1,    68,
      -1,    70,    71,    -1,    73,    -1,    75,    76,    -1,    78,
      79,    80,    -1,    82,    83,    84,    85,    86,    -1,    88,
      -1,    90,    91,    -1,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,    -1,
     119,   120,    -1,    -1,   123,   124,   125,    20,   127,   128,
      -1,    -1,    25,    26,    -1,    28,    29,    30,    31,    -1,
      -1,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    -1,    57,    -1,    59,    60,    61,    -1,
      63,    64,    65,    -1,    -1,    68,    -1,    70,    71,    -1,
      73,    -1,    75,    76,    -1,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    -1,    88,    -1,    90,    91,    -1,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    -1,   119,   120,    -1,    -1,
     123,   124,   125,    -1,   127,   128,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    -1,
      34,    35,    -1,    37,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      54,    -1,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
     104,   105,    -1,    -1,   108,    20,    21,    22,    23,    -1,
     114,    -1,    -1,    -1,    -1,    30,    -1,    32,    -1,    34,
      35,    -1,    37,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,
      -1,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,   104,
     105,    -1,    -1,   108,    20,    21,    22,    23,    -1,   114,
      -1,    -1,    -1,    -1,    30,    -1,    32,    -1,    34,    35,
      -1,    37,    -1,    -1,    -1,    41,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    72,    73,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,   104,   105,
      -1,    -1,   108,    20,    21,    22,    23,    -1,   114,    -1,
      -1,    -1,    -1,    30,    -1,    32,    -1,    34,    35,    -1,
      37,    -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    72,    73,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,    -1,   104,   105,    -1,
      -1,   108,    20,    21,    22,    23,    -1,   114,    -1,    -1,
      -1,    -1,    30,    -1,    32,    -1,    34,    35,    -1,    37,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    72,    73,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,   104,   105,    -1,    -1,
     108,    20,    21,    22,    23,    -1,   114,    -1,    -1,    -1,
      -1,    30,    -1,    32,    -1,    34,    35,    -1,    37,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    73,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,
      89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,   104,   105,    -1,    -1,   108,
      -1,    -1,    -1,    -1,    -1,   114
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   139,   140,     0,    23,   131,   141,   144,   145,   222,
      20,    22,    25,    26,    28,    29,    30,    31,    34,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    51,    52,    53,    54,    55,    57,    59,
      60,    61,    63,    64,    65,    68,    70,    71,    73,    75,
      76,    78,    79,    80,    82,    83,    84,    85,    86,    88,
      90,    91,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   119,   120,   123,
     124,   125,   127,   128,   226,   227,    91,    99,   127,   132,
     143,    32,    50,   146,    24,    55,    20,   142,   227,    60,
     124,   125,   166,    20,    23,    50,   147,   148,   149,   158,
     227,    20,    21,    22,    23,    30,    34,    35,    37,    41,
      45,    54,    61,    62,    63,    64,    70,    72,    73,    76,
      84,    89,    90,    93,   102,   104,   105,   108,   114,   144,
     167,   168,   169,   170,   171,   177,   178,   181,   186,   187,
     188,   191,   193,   194,   195,   196,   197,   199,   200,   201,
     202,   203,   205,   206,   207,   208,   210,   212,   223,   226,
     148,    26,    42,    86,   113,   151,   159,   226,   182,    20,
      21,    22,   211,    28,   209,   213,   204,    46,   117,   172,
     220,   204,   132,   211,   218,   209,   132,    15,   136,   137,
     165,   224,   226,    58,    66,    67,    81,   130,    24,    66,
     113,    47,   160,    24,   129,   183,   184,   132,    36,    86,
     132,   129,   214,   215,   211,    53,   166,   211,   132,   219,
     218,   129,   132,   225,   224,    20,    21,    22,   189,   190,
     190,   166,   198,   221,    20,    21,   157,   227,   150,    38,
     161,   220,    56,   184,   185,    36,   216,   217,   226,   215,
      77,    20,    21,   173,   174,   176,   177,   179,   132,   218,
     198,    74,   115,   192,    58,   198,   132,   133,   153,    20,
      21,   227,    87,   162,   166,   166,    58,    92,   121,   132,
     135,   165,    56,    57,   180,    11,    74,    81,   154,   155,
     158,    66,    78,   156,    89,    51,   132,   163,   164,   165,
      35,   217,   166,   174,   175,   166,   220,    58,    29,   224,
     134,   135,   160,   152,   132,   166,    72,   221,   132,   155,
     132,   198
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   138,   139,   140,   140,   141,   141,   141,   141,   141,
     142,   142,   143,   143,   144,   145,   145,   145,   146,   147,
     147,   148,   148,   148,   149,   149,   150,   149,   151,   151,
     151,   152,   153,   153,   154,   154,   155,   156,   156,   157,
     157,   157,   158,   158,   159,   159,   160,   161,   161,   161,
     161,   162,   162,   163,   163,   164,   164,   165,   165,   166,
     166,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   168,   169,   169,   170,
     171,   172,   172,   172,   173,   173,   174,   175,   176,   176,
     176,   177,   177,   178,   179,   179,   180,   180,   181,   182,
     183,   183,   184,   185,   185,   186,   187,   188,   189,   190,
     190,   190,   191,   192,   192,   193,   194,   194,   195,   196,
     197,   198,   199,   199,   199,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   209,   209,   210,   210,
     211,   211,   211,   212,   213,   212,   214,   214,   215,   216,
     216,   217,   218,   219,   220,   221,   222,   222,   223,   223,
     224,   224,   225,   225,   226,   226,   226,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     2,     3,     3,     3,     3,     3,
       1,     1,     0,     1,     6,     1,     2,     3,     1,     2,
       1,     1,     1,     3,     6,     5,     0,     7,     0,     2,
       1,     0,     0,     3,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     0,     0,     2,     2,
       2,     0,     2,     1,     1,     1,     1,     1,     1,     0,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     3,
       5,     0,     1,     1,     3,     1,     3,     0,     1,     1,
       1,     1,     3,     8,     0,     4,     0,     2,     7,     0,
       2,     1,     3,     0,     2,     3,     4,     4,     2,     1,
       1,     1,     8,     0,     2,     3,     1,     1,     1,     1,
       1,     5,     1,     1,     1,     1,     1,     2,     4,     4,
       0,     3,     2,     3,     3,     2,     3,     0,     1,     1,
       1,     1,     1,     0,     0,     3,     2,     1,     4,     3,
       1,     1,     0,     0,     0,     0,     0,     3,     0,     3,
       0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 364 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_parse_result = (PLpgSQL_stmt_block *) (yyvsp[-1].stmt);
					}
#line 2167 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 5:
#line 374 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_DumpExecTree = true;
					}
#line 2175 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 6:
#line 378 "pl_gram.y" /* yacc.c:1652  */
    {
						if (strcmp((yyvsp[0].str), "on") == 0)
							plpgsql_curr_compile->print_strict_params = true;
						else if (strcmp((yyvsp[0].str), "off") == 0)
							plpgsql_curr_compile->print_strict_params = false;
						else
							elog(ERROR, "unrecognized print_strict_params option %s", (yyvsp[0].str));
					}
#line 2188 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 7:
#line 387 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_curr_compile->resolve_option = PLPGSQL_RESOLVE_ERROR;
					}
#line 2196 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 8:
#line 391 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_curr_compile->resolve_option = PLPGSQL_RESOLVE_VARIABLE;
					}
#line 2204 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 9:
#line 395 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_curr_compile->resolve_option = PLPGSQL_RESOLVE_COLUMN;
					}
#line 2212 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 10:
#line 401 "pl_gram.y" /* yacc.c:1652  */
    {
					(yyval.str) = (yyvsp[0].word).ident;
				}
#line 2220 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 11:
#line 405 "pl_gram.y" /* yacc.c:1652  */
    {
					(yyval.str) = pstrdup((yyvsp[0].keyword));
				}
#line 2228 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 14:
#line 414 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_block *new;

						new = palloc0(sizeof(PLpgSQL_stmt_block));

						new->cmd_type	= PLPGSQL_STMT_BLOCK;
						new->lineno		= plpgsql_location_to_lineno((yylsp[-4]));
						new->stmtid		= ++plpgsql_curr_compile->nstatements;
						new->label		= (yyvsp[-5].declhdr).label;
						new->n_initvars = (yyvsp[-5].declhdr).n_initvars;
						new->initvarnos = (yyvsp[-5].declhdr).initvarnos;
						new->body		= (yyvsp[-3].list);
						new->exceptions	= (yyvsp[-2].exception_block);

						check_labels((yyvsp[-5].declhdr).label, (yyvsp[0].str), (yylsp[0]));
						plpgsql_ns_pop();

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 2252 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 15:
#line 437 "pl_gram.y" /* yacc.c:1652  */
    {
						/* done with decls, so resume identifier lookup */
						plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[0].str);
						(yyval.declhdr).n_initvars = 0;
						(yyval.declhdr).initvarnos = NULL;
					}
#line 2264 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 16:
#line 445 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[-1].str);
						(yyval.declhdr).n_initvars = 0;
						(yyval.declhdr).initvarnos = NULL;
					}
#line 2275 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 17:
#line 452 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[-2].str);
						/* Remember variables declared in decl_stmts */
						(yyval.declhdr).n_initvars = plpgsql_add_initdatums(&((yyval.declhdr).initvarnos));
					}
#line 2286 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 18:
#line 461 "pl_gram.y" /* yacc.c:1652  */
    {
						/* Forget any variables created before block */
						plpgsql_add_initdatums(NULL);
						/*
						 * Disable scanner lookup of identifiers while
						 * we process the decl_stmts
						 */
						plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_DECLARE;
					}
#line 2300 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 22:
#line 478 "pl_gram.y" /* yacc.c:1652  */
    {
						/* We allow useless extra DECLAREs */
					}
#line 2308 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 23:
#line 482 "pl_gram.y" /* yacc.c:1652  */
    {
						/*
						 * Throw a helpful error if user tries to put block
						 * label just before BEGIN, instead of before DECLARE.
						 */
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("block label must be placed before DECLARE, not after"),
								 parser_errposition((yylsp[-2]))));
					}
#line 2323 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 24:
#line 495 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_variable	*var;

						/*
						 * If a collation is supplied, insert it into the
						 * datatype.  We assume decl_datatype always returns
						 * a freshly built struct not shared with other
						 * variables.
						 */
						if (OidIsValid((yyvsp[-2].oid)))
						{
							if (!OidIsValid((yyvsp[-3].dtype)->collation))
								ereport(ERROR,
										(errcode(ERRCODE_DATATYPE_MISMATCH),
										 errmsg("collations are not supported by type %s",
												format_type_be((yyvsp[-3].dtype)->typoid)),
										 parser_errposition((yylsp[-2]))));
							(yyvsp[-3].dtype)->collation = (yyvsp[-2].oid);
						}

						var = plpgsql_build_variable((yyvsp[-5].varname).name, (yyvsp[-5].varname).lineno,
													 (yyvsp[-3].dtype), true);
						var->isconst = (yyvsp[-4].boolean);
						var->notnull = (yyvsp[-1].boolean);
						var->default_val = (yyvsp[0].expr);

						/*
						 * The combination of NOT NULL without an initializer
						 * can't work, so let's reject it at compile time.
						 */
						if (var->notnull && var->default_val == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
									 errmsg("variable \"%s\" must have a default value, since it's declared NOT NULL",
											var->refname),
									 parser_errposition((yylsp[-1]))));
					}
#line 2365 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 25:
#line 533 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_ns_additem((yyvsp[-1].nsitem)->itemtype,
										   (yyvsp[-1].nsitem)->itemno, (yyvsp[-4].varname).name);
					}
#line 2374 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 26:
#line 538 "pl_gram.y" /* yacc.c:1652  */
    { plpgsql_ns_push((yyvsp[-2].varname).name, PLPGSQL_LABEL_OTHER); }
#line 2380 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 27:
#line 540 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_var *new;
						PLpgSQL_expr *curname_def;
						char		buf[1024];
						char		*cp1;
						char		*cp2;

						/* pop local namespace for cursor args */
						plpgsql_ns_pop();

						new = (PLpgSQL_var *)
							plpgsql_build_variable((yyvsp[-6].varname).name, (yyvsp[-6].varname).lineno,
												   plpgsql_build_datatype(REFCURSOROID,
																		  -1,
																		  InvalidOid,
																		  NULL),
												   true);

						curname_def = palloc0(sizeof(PLpgSQL_expr));

						strcpy(buf, "SELECT ");
						cp1 = new->refname;
						cp2 = buf + strlen(buf);
						/*
						 * Don't trust standard_conforming_strings here;
						 * it might change before we use the string.
						 */
						if (strchr(cp1, '\\') != NULL)
							*cp2++ = ESCAPE_STRING_SYNTAX;
						*cp2++ = '\'';
						while (*cp1)
						{
							if (SQL_STR_DOUBLE(*cp1, true))
								*cp2++ = *cp1;
							*cp2++ = *cp1++;
						}
						strcpy(cp2, "'::pg_catalog.refcursor");
						curname_def->query = pstrdup(buf);
						new->default_val = curname_def;

						new->cursor_explicit_expr = (yyvsp[0].expr);
						if ((yyvsp[-2].datum) == NULL)
							new->cursor_explicit_argrow = -1;
						else
							new->cursor_explicit_argrow = (yyvsp[-2].datum)->dno;
						new->cursor_options = CURSOR_OPT_FAST_PLAN | (yyvsp[-5].ival);
					}
#line 2432 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 28:
#line 590 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.ival) = 0;
					}
#line 2440 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 29:
#line 594 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.ival) = CURSOR_OPT_NO_SCROLL;
					}
#line 2448 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 30:
#line 598 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.ival) = CURSOR_OPT_SCROLL;
					}
#line 2456 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 31:
#line 604 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.expr) = read_sql_stmt("");
					}
#line 2464 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 32:
#line 610 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.datum) = NULL;
					}
#line 2472 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 33:
#line 614 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_row *new;
						int i;
						ListCell *l;

						new = palloc0(sizeof(PLpgSQL_row));
						new->dtype = PLPGSQL_DTYPE_ROW;
						new->refname = "(unnamed row)";
						new->lineno = plpgsql_location_to_lineno((yylsp[-2]));
						new->rowtupdesc = NULL;
						new->nfields = list_length((yyvsp[-1].list));
						new->fieldnames = palloc(new->nfields * sizeof(char *));
						new->varnos = palloc(new->nfields * sizeof(int));

						i = 0;
						foreach (l, (yyvsp[-1].list))
						{
							PLpgSQL_variable *arg = (PLpgSQL_variable *) lfirst(l);
							Assert(!arg->isconst);
							new->fieldnames[i] = arg->refname;
							new->varnos[i] = arg->dno;
							i++;
						}
						list_free((yyvsp[-1].list));

						plpgsql_adddatum((PLpgSQL_datum *) new);
						(yyval.datum) = (PLpgSQL_datum *) new;
					}
#line 2505 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 34:
#line 645 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = list_make1((yyvsp[0].datum));
					}
#line 2513 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 35:
#line 649 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].datum));
					}
#line 2521 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 36:
#line 655 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.datum) = (PLpgSQL_datum *)
							plpgsql_build_variable((yyvsp[-1].varname).name, (yyvsp[-1].varname).lineno,
												   (yyvsp[0].dtype), true);
					}
#line 2531 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 39:
#line 666 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_nsitem *nsi;

						nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
												(yyvsp[0].word).ident, NULL, NULL,
												NULL);
						if (nsi == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_UNDEFINED_OBJECT),
									 errmsg("variable \"%s\" does not exist",
											(yyvsp[0].word).ident),
									 parser_errposition((yylsp[0]))));
						(yyval.nsitem) = nsi;
					}
#line 2550 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 40:
#line 681 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_nsitem *nsi;

						nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
												(yyvsp[0].keyword), NULL, NULL,
												NULL);
						if (nsi == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_UNDEFINED_OBJECT),
									 errmsg("variable \"%s\" does not exist",
											(yyvsp[0].keyword)),
									 parser_errposition((yylsp[0]))));
						(yyval.nsitem) = nsi;
					}
#line 2569 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 41:
#line 696 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_nsitem *nsi;

						if (list_length((yyvsp[0].cword).idents) == 2)
							nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
													strVal(linitial((yyvsp[0].cword).idents)),
													strVal(lsecond((yyvsp[0].cword).idents)),
													NULL,
													NULL);
						else if (list_length((yyvsp[0].cword).idents) == 3)
							nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
													strVal(linitial((yyvsp[0].cword).idents)),
													strVal(lsecond((yyvsp[0].cword).idents)),
													strVal(lthird((yyvsp[0].cword).idents)),
													NULL);
						else
							nsi = NULL;
						if (nsi == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_UNDEFINED_OBJECT),
									 errmsg("variable \"%s\" does not exist",
											NameListToString((yyvsp[0].cword).idents)),
									 parser_errposition((yylsp[0]))));
						(yyval.nsitem) = nsi;
					}
#line 2599 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 42:
#line 724 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.varname).name = (yyvsp[0].word).ident;
						(yyval.varname).lineno = plpgsql_location_to_lineno((yylsp[0]));
						/*
						 * Check to make sure name isn't already declared
						 * in the current block.
						 */
						if (plpgsql_ns_lookup(plpgsql_ns_top(), true,
											  (yyvsp[0].word).ident, NULL, NULL,
											  NULL) != NULL)
							yyerror("duplicate declaration");

						if (plpgsql_curr_compile->extra_warnings & PLPGSQL_XCHECK_SHADOWVAR ||
							plpgsql_curr_compile->extra_errors & PLPGSQL_XCHECK_SHADOWVAR)
						{
							PLpgSQL_nsitem *nsi;
							nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
													(yyvsp[0].word).ident, NULL, NULL, NULL);
							if (nsi != NULL)
								ereport(plpgsql_curr_compile->extra_errors & PLPGSQL_XCHECK_SHADOWVAR ? ERROR : WARNING,
										(errcode(ERRCODE_DUPLICATE_ALIAS),
										 errmsg("variable \"%s\" shadows a previously defined variable",
												(yyvsp[0].word).ident),
										 parser_errposition((yylsp[0]))));
						}

					}
#line 2631 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 43:
#line 752 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.varname).name = pstrdup((yyvsp[0].keyword));
						(yyval.varname).lineno = plpgsql_location_to_lineno((yylsp[0]));
						/*
						 * Check to make sure name isn't already declared
						 * in the current block.
						 */
						if (plpgsql_ns_lookup(plpgsql_ns_top(), true,
											  (yyvsp[0].keyword), NULL, NULL,
											  NULL) != NULL)
							yyerror("duplicate declaration");

						if (plpgsql_curr_compile->extra_warnings & PLPGSQL_XCHECK_SHADOWVAR ||
							plpgsql_curr_compile->extra_errors & PLPGSQL_XCHECK_SHADOWVAR)
						{
							PLpgSQL_nsitem *nsi;
							nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
													(yyvsp[0].keyword), NULL, NULL, NULL);
							if (nsi != NULL)
								ereport(plpgsql_curr_compile->extra_errors & PLPGSQL_XCHECK_SHADOWVAR ? ERROR : WARNING,
										(errcode(ERRCODE_DUPLICATE_ALIAS),
										 errmsg("variable \"%s\" shadows a previously defined variable",
												(yyvsp[0].keyword)),
										 parser_errposition((yylsp[0]))));
						}

					}
#line 2663 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 44:
#line 782 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.boolean) = false; }
#line 2669 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 45:
#line 784 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.boolean) = true; }
#line 2675 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 46:
#line 788 "pl_gram.y" /* yacc.c:1652  */
    {
						/*
						 * If there's a lookahead token, read_datatype
						 * should consume it.
						 */
						(yyval.dtype) = read_datatype(yychar);
						yyclearin;
					}
#line 2688 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 47:
#line 799 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.oid) = InvalidOid; }
#line 2694 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 48:
#line 801 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.oid) = get_collation_oid(list_make1(makeString((yyvsp[0].word).ident)),
											   false);
					}
#line 2703 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 49:
#line 806 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.oid) = get_collation_oid(list_make1(makeString(pstrdup((yyvsp[0].keyword)))),
											   false);
					}
#line 2712 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 50:
#line 811 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.oid) = get_collation_oid((yyvsp[0].cword).idents, false);
					}
#line 2720 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 51:
#line 817 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.boolean) = false; }
#line 2726 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 52:
#line 819 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.boolean) = true; }
#line 2732 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 53:
#line 823 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 2738 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 54:
#line 825 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.expr) = read_sql_expression(';', ";");
					}
#line 2746 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 59:
#line 844 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.list) = NIL; }
#line 2752 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 60:
#line 846 "pl_gram.y" /* yacc.c:1652  */
    {
						/* don't bother linking null statements into list */
						if ((yyvsp[0].stmt) == NULL)
							(yyval.list) = (yyvsp[-1].list);
						else
							(yyval.list) = lappend((yyvsp[-1].list), (yyvsp[0].stmt));
					}
#line 2764 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 61:
#line 856 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 2770 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 62:
#line 858 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2776 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 63:
#line 860 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2782 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 64:
#line 862 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2788 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 65:
#line 864 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2794 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 66:
#line 866 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2800 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 67:
#line 868 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2806 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 68:
#line 870 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2812 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 69:
#line 872 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2818 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 70:
#line 874 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2824 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 71:
#line 876 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2830 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 72:
#line 878 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2836 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 73:
#line 880 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2842 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 74:
#line 882 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2848 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 75:
#line 884 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2854 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 76:
#line 886 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2860 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 77:
#line 888 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2866 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 78:
#line 890 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2872 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 79:
#line 892 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2878 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 80:
#line 894 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2884 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 81:
#line 896 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2890 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 82:
#line 898 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2896 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 83:
#line 900 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2902 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 84:
#line 902 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2908 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 85:
#line 904 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2914 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 86:
#line 908 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_perform *new;

						new = palloc0(sizeof(PLpgSQL_stmt_perform));
						new->cmd_type = PLPGSQL_STMT_PERFORM;
						new->lineno   = plpgsql_location_to_lineno((yylsp[-1]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->expr  = (yyvsp[0].expr);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 2930 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 87:
#line 922 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_call *new;

						new = palloc0(sizeof(PLpgSQL_stmt_call));
						new->cmd_type = PLPGSQL_STMT_CALL;
						new->lineno = plpgsql_location_to_lineno((yylsp[0]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->expr = read_sql_stmt("CALL ");
						new->is_call = true;

						(yyval.stmt) = (PLpgSQL_stmt *)new;

					}
#line 2948 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 88:
#line 936 "pl_gram.y" /* yacc.c:1652  */
    {
						/* use the same structures as for CALL, for simplicity */
						PLpgSQL_stmt_call *new;

						new = palloc0(sizeof(PLpgSQL_stmt_call));
						new->cmd_type = PLPGSQL_STMT_CALL;
						new->lineno = plpgsql_location_to_lineno((yylsp[0]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->expr = read_sql_stmt("DO ");
						new->is_call = false;

						(yyval.stmt) = (PLpgSQL_stmt *)new;

					}
#line 2967 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 89:
#line 953 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_assign *new;

						new = palloc0(sizeof(PLpgSQL_stmt_assign));
						new->cmd_type = PLPGSQL_STMT_ASSIGN;
						new->lineno   = plpgsql_location_to_lineno((yylsp[-2]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->varno = (yyvsp[-2].datum)->dno;
						new->expr  = (yyvsp[0].expr);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 2984 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 90:
#line 968 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_getdiag	 *new;
						ListCell		*lc;

						new = palloc0(sizeof(PLpgSQL_stmt_getdiag));
						new->cmd_type = PLPGSQL_STMT_GETDIAG;
						new->lineno   = plpgsql_location_to_lineno((yylsp[-4]));
						new->stmtid	  = ++plpgsql_curr_compile->nstatements;
						new->is_stacked = (yyvsp[-3].boolean);
						new->diag_items = (yyvsp[-1].list);

						/*
						 * Check information items are valid for area option.
						 */
						foreach(lc, new->diag_items)
						{
							PLpgSQL_diag_item *ditem = (PLpgSQL_diag_item *) lfirst(lc);

							switch (ditem->kind)
							{
								/* these fields are disallowed in stacked case */
								case PLPGSQL_GETDIAG_ROW_COUNT:
									if (new->is_stacked)
										ereport(ERROR,
												(errcode(ERRCODE_SYNTAX_ERROR),
												 errmsg("diagnostics item %s is not allowed in GET STACKED DIAGNOSTICS",
														plpgsql_getdiag_kindname(ditem->kind)),
												 parser_errposition((yylsp[-4]))));
									break;
								/* these fields are disallowed in current case */
								case PLPGSQL_GETDIAG_ERROR_CONTEXT:
								case PLPGSQL_GETDIAG_ERROR_DETAIL:
								case PLPGSQL_GETDIAG_ERROR_HINT:
								case PLPGSQL_GETDIAG_RETURNED_SQLSTATE:
								case PLPGSQL_GETDIAG_COLUMN_NAME:
								case PLPGSQL_GETDIAG_CONSTRAINT_NAME:
								case PLPGSQL_GETDIAG_DATATYPE_NAME:
								case PLPGSQL_GETDIAG_MESSAGE_TEXT:
								case PLPGSQL_GETDIAG_TABLE_NAME:
								case PLPGSQL_GETDIAG_SCHEMA_NAME:
									if (!new->is_stacked)
										ereport(ERROR,
												(errcode(ERRCODE_SYNTAX_ERROR),
												 errmsg("diagnostics item %s is not allowed in GET CURRENT DIAGNOSTICS",
														plpgsql_getdiag_kindname(ditem->kind)),
												 parser_errposition((yylsp[-4]))));
									break;
								/* these fields are allowed in either case */
								case PLPGSQL_GETDIAG_CONTEXT:
									break;
								default:
									elog(ERROR, "unrecognized diagnostic item kind: %d",
										 ditem->kind);
									break;
							}
						}

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 3048 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1030 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.boolean) = false;
					}
#line 3056 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1034 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.boolean) = false;
					}
#line 3064 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1038 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.boolean) = true;
					}
#line 3072 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1044 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].diagitem));
					}
#line 3080 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1048 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = list_make1((yyvsp[0].diagitem));
					}
#line 3088 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 96:
#line 1054 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_diag_item *new;

						new = palloc(sizeof(PLpgSQL_diag_item));
						new->target = (yyvsp[-2].datum)->dno;
						new->kind = (yyvsp[0].ival);

						(yyval.diagitem) = new;
					}
#line 3102 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 97:
#line 1066 "pl_gram.y" /* yacc.c:1652  */
    {
						int	tok = yylex();

						if (tok_is_keyword(tok, &yylval,
										   K_ROW_COUNT, "row_count"))
							(yyval.ival) = PLPGSQL_GETDIAG_ROW_COUNT;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_CONTEXT, "pg_context"))
							(yyval.ival) = PLPGSQL_GETDIAG_CONTEXT;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_DETAIL, "pg_exception_detail"))
							(yyval.ival) = PLPGSQL_GETDIAG_ERROR_DETAIL;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_HINT, "pg_exception_hint"))
							(yyval.ival) = PLPGSQL_GETDIAG_ERROR_HINT;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_CONTEXT, "pg_exception_context"))
							(yyval.ival) = PLPGSQL_GETDIAG_ERROR_CONTEXT;
						else if (tok_is_keyword(tok, &yylval,
												K_COLUMN_NAME, "column_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_COLUMN_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_CONSTRAINT_NAME, "constraint_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_CONSTRAINT_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_DATATYPE_NAME, "pg_datatype_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_DATATYPE_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_MESSAGE_TEXT, "message_text"))
							(yyval.ival) = PLPGSQL_GETDIAG_MESSAGE_TEXT;
						else if (tok_is_keyword(tok, &yylval,
												K_TABLE_NAME, "table_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_TABLE_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_SCHEMA_NAME, "schema_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_SCHEMA_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_RETURNED_SQLSTATE, "returned_sqlstate"))
							(yyval.ival) = PLPGSQL_GETDIAG_RETURNED_SQLSTATE;
						else
							yyerror("unrecognized GET DIAGNOSTICS item");
					}
#line 3149 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 98:
#line 1111 "pl_gram.y" /* yacc.c:1652  */
    {
						if ((yyvsp[0].datum)->dtype == PLPGSQL_DTYPE_ROW ||
							(yyvsp[0].datum)->dtype == PLPGSQL_DTYPE_REC)
							ereport(ERROR,
									(errcode(ERRCODE_SYNTAX_ERROR),
									 errmsg("\"%s\" is not a scalar variable",
											((PLpgSQL_variable *) (yyvsp[0].datum))->refname),
									 parser_errposition((yylsp[0]))));
						(yyval.datum) = (yyvsp[0].datum);
					}
#line 3164 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 99:
#line 1122 "pl_gram.y" /* yacc.c:1652  */
    {
						/* just to give a better message than "syntax error" */
						word_is_not_variable(&((yyvsp[0].word)), (yylsp[0]));
					}
#line 3173 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 100:
#line 1127 "pl_gram.y" /* yacc.c:1652  */
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[0].cword)), (yylsp[0]));
					}
#line 3182 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 101:
#line 1135 "pl_gram.y" /* yacc.c:1652  */
    {
						check_assignable((yyvsp[0].wdatum).datum, (yylsp[0]));
						(yyval.datum) = (yyvsp[0].wdatum).datum;
					}
#line 3191 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 102:
#line 1140 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_arrayelem	*new;

						new = palloc0(sizeof(PLpgSQL_arrayelem));
						new->dtype		= PLPGSQL_DTYPE_ARRAYELEM;
						new->subscript	= (yyvsp[0].expr);
						new->arrayparentno = (yyvsp[-2].datum)->dno;
						/* initialize cached type data to "not valid" */
						new->parenttypoid = InvalidOid;

						plpgsql_adddatum((PLpgSQL_datum *) new);

						(yyval.datum) = (PLpgSQL_datum *) new;
					}
#line 3210 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 103:
#line 1157 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_if *new;

						new = palloc0(sizeof(PLpgSQL_stmt_if));
						new->cmd_type	= PLPGSQL_STMT_IF;
						new->lineno		= plpgsql_location_to_lineno((yylsp[-7]));
						new->stmtid		= ++plpgsql_curr_compile->nstatements;
						new->cond		= (yyvsp[-6].expr);
						new->then_body	= (yyvsp[-5].list);
						new->elsif_list = (yyvsp[-4].list);
						new->else_body  = (yyvsp[-3].list);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 3229 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1174 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = NIL;
					}
#line 3237 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1178 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_if_elsif *new;

						new = palloc0(sizeof(PLpgSQL_if_elsif));
						new->lineno = plpgsql_location_to_lineno((yylsp[-2]));
						new->cond   = (yyvsp[-1].expr);
						new->stmts  = (yyvsp[0].list);

						(yyval.list) = lappend((yyvsp[-3].list), new);
					}
#line 3252 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1191 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = NIL;
					}
#line 3260 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1195 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = (yyvsp[0].list);
					}
#line 3268 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1201 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.stmt) = make_case((yylsp[-6]), (yyvsp[-5].expr), (yyvsp[-4].list), (yyvsp[-3].list));
					}
#line 3276 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1207 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_expr *expr = NULL;
						int	tok = yylex();

						if (tok != K_WHEN)
						{
							plpgsql_push_back_token(tok);
							expr = read_sql_expression(K_WHEN, "WHEN");
						}
						plpgsql_push_back_token(K_WHEN);
						(yyval.expr) = expr;
					}
#line 3293 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1222 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = lappend((yyvsp[-1].list), (yyvsp[0].casewhen));
					}
#line 3301 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1226 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = list_make1((yyvsp[0].casewhen));
					}
#line 3309 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1232 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_case_when *new = palloc(sizeof(PLpgSQL_case_when));

						new->lineno	= plpgsql_location_to_lineno((yylsp[-2]));
						new->expr	= (yyvsp[-1].expr);
						new->stmts	= (yyvsp[0].list);
						(yyval.casewhen) = new;
					}
#line 3322 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1243 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.list) = NIL;
					}
#line 3330 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1247 "pl_gram.y" /* yacc.c:1652  */
    {
						/*
						 * proc_sect could return an empty list, but we
						 * must distinguish that from not having ELSE at all.
						 * Simplest fix is to return a list with one NULL
						 * pointer, which make_case() must take care of.
						 */
						if ((yyvsp[0].list) != NIL)
							(yyval.list) = (yyvsp[0].list);
						else
							(yyval.list) = list_make1(NULL);
					}
#line 3347 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1262 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_loop *new;

						new = palloc0(sizeof(PLpgSQL_stmt_loop));
						new->cmd_type = PLPGSQL_STMT_LOOP;
						new->lineno   = plpgsql_location_to_lineno((yylsp[-1]));
						new->stmtid   = ++plpgsql_curr_compile->nstatements;
						new->label	  = (yyvsp[-2].str);
						new->body	  = (yyvsp[0].loop_body).stmts;

						check_labels((yyvsp[-2].str), (yyvsp[0].loop_body).end_label, (yyvsp[0].loop_body).end_label_location);
						plpgsql_ns_pop();

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 3367 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1280 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_while *new;

						new = palloc0(sizeof(PLpgSQL_stmt_while));
						new->cmd_type = PLPGSQL_STMT_WHILE;
						new->lineno   = plpgsql_location_to_lineno((yylsp[-2]));
						new->stmtid	  = ++plpgsql_curr_compile->nstatements;
						new->label	  = (yyvsp[-3].str);
						new->cond	  = (yyvsp[-1].expr);
						new->body	  = (yyvsp[0].loop_body).stmts;

						check_labels((yyvsp[-3].str), (yyvsp[0].loop_body).end_label, (yyvsp[0].loop_body).end_label_location);
						plpgsql_ns_pop();

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 3388 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1299 "pl_gram.y" /* yacc.c:1652  */
    {
						/* This runs after we've scanned the loop body */
						if ((yyvsp[-1].stmt)->cmd_type == PLPGSQL_STMT_FORI)
						{
							PLpgSQL_stmt_fori		*new;

							new = (PLpgSQL_stmt_fori *) (yyvsp[-1].stmt);
							new->lineno   = plpgsql_location_to_lineno((yylsp[-2]));
							new->stmtid	  = ++plpgsql_curr_compile->nstatements;
							new->label	  = (yyvsp[-3].str);
							new->body	  = (yyvsp[0].loop_body).stmts;
							(yyval.stmt) = (PLpgSQL_stmt *) new;
						}
						else
						{
							PLpgSQL_stmt_forq		*new;

							Assert((yyvsp[-1].stmt)->cmd_type == PLPGSQL_STMT_FORS ||
								   (yyvsp[-1].stmt)->cmd_type == PLPGSQL_STMT_FORC ||
								   (yyvsp[-1].stmt)->cmd_type == PLPGSQL_STMT_DYNFORS);
							/* forq is the common supertype of all three */
							new = (PLpgSQL_stmt_forq *) (yyvsp[-1].stmt);
							new->lineno   = plpgsql_location_to_lineno((yylsp[-2]));
							new->stmtid	  = ++plpgsql_curr_compile->nstatements;
							new->label	  = (yyvsp[-3].str);
							new->body	  = (yyvsp[0].loop_body).stmts;
							(yyval.stmt) = (PLpgSQL_stmt *) new;
						}

						check_labels((yyvsp[-3].str), (yyvsp[0].loop_body).end_label, (yyvsp[0].loop_body).end_label_location);
						/* close namespace started in opt_loop_label */
						plpgsql_ns_pop();
					}
#line 3426 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1335 "pl_gram.y" /* yacc.c:1652  */
    {
						int			tok = yylex();
						int			tokloc = yylloc;

						if (tok == K_EXECUTE)
						{
							/* EXECUTE means it's a dynamic FOR loop */
							PLpgSQL_stmt_dynfors	*new;
							PLpgSQL_expr			*expr;
							int						term;

							expr = read_sql_expression2(K_LOOP, K_USING,
														"LOOP or USING",
														&term);

							new = palloc0(sizeof(PLpgSQL_stmt_dynfors));
							new->cmd_type = PLPGSQL_STMT_DYNFORS;
							new->stmtid	  = ++plpgsql_curr_compile->nstatements;
							if ((yyvsp[-1].forvariable).row)
							{
								new->var = (PLpgSQL_variable *) (yyvsp[-1].forvariable).row;
								check_assignable((yyvsp[-1].forvariable).row, (yylsp[-1]));
							}
							else if ((yyvsp[-1].forvariable).scalar)
							{
								/* convert single scalar to list */
								new->var = (PLpgSQL_variable *)
									make_scalar_list1((yyvsp[-1].forvariable).name, (yyvsp[-1].forvariable).scalar,
													  (yyvsp[-1].forvariable).lineno, (yylsp[-1]));
								/* make_scalar_list1 did check_assignable */
							}
							else
							{
								ereport(ERROR,
										(errcode(ERRCODE_DATATYPE_MISMATCH),
										 errmsg("loop variable of loop over rows must be a record variable or list of scalar variables"),
										 parser_errposition((yylsp[-1]))));
							}
							new->query = expr;

							if (term == K_USING)
							{
								do
								{
									expr = read_sql_expression2(',', K_LOOP,
																", or LOOP",
																&term);
									new->params = lappend(new->params, expr);
								} while (term == ',');
							}

							(yyval.stmt) = (PLpgSQL_stmt *) new;
						}
						else if (tok == T_DATUM &&
								 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_VAR &&
								 ((PLpgSQL_var *) yylval.wdatum.datum)->datatype->typoid == REFCURSOROID)
						{
							/* It's FOR var IN cursor */
							PLpgSQL_stmt_forc	*new;
							PLpgSQL_var			*cursor = (PLpgSQL_var *) yylval.wdatum.datum;

							new = (PLpgSQL_stmt_forc *) palloc0(sizeof(PLpgSQL_stmt_forc));
							new->cmd_type = PLPGSQL_STMT_FORC;
							new->stmtid = ++plpgsql_curr_compile->nstatements;
							new->curvar = cursor->dno;

							/* Should have had a single variable name */
							if ((yyvsp[-1].forvariable).scalar && (yyvsp[-1].forvariable).row)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 errmsg("cursor FOR loop must have only one target variable"),
										 parser_errposition((yylsp[-1]))));

							/* can't use an unbound cursor this way */
							if (cursor->cursor_explicit_expr == NULL)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 errmsg("cursor FOR loop must use a bound cursor variable"),
										 parser_errposition(tokloc)));

							/* collect cursor's parameters if any */
							new->argquery = read_cursor_args(cursor,
															 K_LOOP,
															 "LOOP");

							/* create loop's private RECORD variable */
							new->var = (PLpgSQL_variable *)
								plpgsql_build_record((yyvsp[-1].forvariable).name,
													 (yyvsp[-1].forvariable).lineno,
													 NULL,
													 RECORDOID,
													 true);

							(yyval.stmt) = (PLpgSQL_stmt *) new;
						}
						else
						{
							PLpgSQL_expr	*expr1;
							int				expr1loc;
							bool			reverse = false;

							/*
							 * We have to distinguish between two
							 * alternatives: FOR var IN a .. b and FOR
							 * var IN query. Unfortunately this is
							 * tricky, since the query in the second
							 * form needn't start with a SELECT
							 * keyword.  We use the ugly hack of
							 * looking for two periods after the first
							 * token. We also check for the REVERSE
							 * keyword, which means it must be an
							 * integer loop.
							 */
							if (tok_is_keyword(tok, &yylval,
											   K_REVERSE, "reverse"))
								reverse = true;
							else
								plpgsql_push_back_token(tok);

							/*
							 * Read tokens until we see either a ".."
							 * or a LOOP. The text we read may not
							 * necessarily be a well-formed SQL
							 * statement, so we need to invoke
							 * read_sql_construct directly.
							 */
							expr1 = read_sql_construct(DOT_DOT,
													   K_LOOP,
													   0,
													   "LOOP",
													   "SELECT ",
													   true,
													   false,
													   true,
													   &expr1loc,
													   &tok);

							if (tok == DOT_DOT)
							{
								/* Saw "..", so it must be an integer loop */
								PLpgSQL_expr		*expr2;
								PLpgSQL_expr		*expr_by;
								PLpgSQL_var			*fvar;
								PLpgSQL_stmt_fori	*new;

								/* Check first expression is well-formed */
								check_sql_expr(expr1->query, expr1loc, 7);

								/* Read and check the second one */
								expr2 = read_sql_expression2(K_LOOP, K_BY,
															 "LOOP",
															 &tok);

								/* Get the BY clause if any */
								if (tok == K_BY)
									expr_by = read_sql_expression(K_LOOP,
																  "LOOP");
								else
									expr_by = NULL;

								/* Should have had a single variable name */
								if ((yyvsp[-1].forvariable).scalar && (yyvsp[-1].forvariable).row)
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("integer FOR loop must have only one target variable"),
											 parser_errposition((yylsp[-1]))));

								/* create loop's private variable */
								fvar = (PLpgSQL_var *)
									plpgsql_build_variable((yyvsp[-1].forvariable).name,
														   (yyvsp[-1].forvariable).lineno,
														   plpgsql_build_datatype(INT4OID,
																				  -1,
																				  InvalidOid,
																				  NULL),
														   true);

								new = palloc0(sizeof(PLpgSQL_stmt_fori));
								new->cmd_type = PLPGSQL_STMT_FORI;
								new->stmtid	  = ++plpgsql_curr_compile->nstatements;
								new->var	  = fvar;
								new->reverse  = reverse;
								new->lower	  = expr1;
								new->upper	  = expr2;
								new->step	  = expr_by;

								(yyval.stmt) = (PLpgSQL_stmt *) new;
							}
							else
							{
								/*
								 * No "..", so it must be a query loop. We've
								 * prefixed an extra SELECT to the query text,
								 * so we need to remove that before performing
								 * syntax checking.
								 */
								char				*tmp_query;
								PLpgSQL_stmt_fors	*new;

								if (reverse)
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("cannot specify REVERSE in query FOR loop"),
											 parser_errposition(tokloc)));

								Assert(strncmp(expr1->query, "SELECT ", 7) == 0);
								tmp_query = pstrdup(expr1->query + 7);
								pfree(expr1->query);
								expr1->query = tmp_query;

								check_sql_expr(expr1->query, expr1loc, 0);

								new = palloc0(sizeof(PLpgSQL_stmt_fors));
								new->cmd_type = PLPGSQL_STMT_FORS;
								new->stmtid = ++plpgsql_curr_compile->nstatements;
								if ((yyvsp[-1].forvariable).row)
								{
									new->var = (PLpgSQL_variable *) (yyvsp[-1].forvariable).row;
									check_assignable((yyvsp[-1].forvariable).row, (yylsp[-1]));
								}
								else if ((yyvsp[-1].forvariable).scalar)
								{
									/* convert single scalar to list */
									new->var = (PLpgSQL_variable *)
										make_scalar_list1((yyvsp[-1].forvariable).name, (yyvsp[-1].forvariable).scalar,
														  (yyvsp[-1].forvariable).lineno, (yylsp[-1]));
									/* make_scalar_list1 did check_assignable */
								}
								else
								{
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("loop variable of loop over rows must be a record variable or list of scalar variables"),
											 parser_errposition((yylsp[-1]))));
								}

								new->query = expr1;
								(yyval.stmt) = (PLpgSQL_stmt *) new;
							}
						}
					}
#line 3672 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1597 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.forvariable).name = NameOfDatum(&((yyvsp[0].wdatum)));
						(yyval.forvariable).lineno = plpgsql_location_to_lineno((yylsp[0]));
						if ((yyvsp[0].wdatum).datum->dtype == PLPGSQL_DTYPE_ROW ||
							(yyvsp[0].wdatum).datum->dtype == PLPGSQL_DTYPE_REC)
						{
							(yyval.forvariable).scalar = NULL;
							(yyval.forvariable).row = (yyvsp[0].wdatum).datum;
						}
						else
						{
							int			tok;

							(yyval.forvariable).scalar = (yyvsp[0].wdatum).datum;
							(yyval.forvariable).row = NULL;
							/* check for comma-separated list */
							tok = yylex();
							plpgsql_push_back_token(tok);
							if (tok == ',')
								(yyval.forvariable).row = (PLpgSQL_datum *)
									read_into_scalar_list((yyval.forvariable).name,
														  (yyval.forvariable).scalar,
														  (yylsp[0]));
						}
					}
#line 3702 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1623 "pl_gram.y" /* yacc.c:1652  */
    {
						int			tok;

						(yyval.forvariable).name = (yyvsp[0].word).ident;
						(yyval.forvariable).lineno = plpgsql_location_to_lineno((yylsp[0]));
						(yyval.forvariable).scalar = NULL;
						(yyval.forvariable).row = NULL;
						/* check for comma-separated list */
						tok = yylex();
						plpgsql_push_back_token(tok);
						if (tok == ',')
							word_is_not_variable(&((yyvsp[0].word)), (yylsp[0]));
					}
#line 3720 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1637 "pl_gram.y" /* yacc.c:1652  */
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[0].cword)), (yylsp[0]));
					}
#line 3729 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1644 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_foreach_a *new;

						new = palloc0(sizeof(PLpgSQL_stmt_foreach_a));
						new->cmd_type = PLPGSQL_STMT_FOREACH_A;
						new->lineno = plpgsql_location_to_lineno((yylsp[-6]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->label = (yyvsp[-7].str);
						new->slice = (yyvsp[-4].ival);
						new->expr = (yyvsp[-1].expr);
						new->body = (yyvsp[0].loop_body).stmts;

						if ((yyvsp[-5].forvariable).row)
						{
							new->varno = (yyvsp[-5].forvariable).row->dno;
							check_assignable((yyvsp[-5].forvariable).row, (yylsp[-5]));
						}
						else if ((yyvsp[-5].forvariable).scalar)
						{
							new->varno = (yyvsp[-5].forvariable).scalar->dno;
							check_assignable((yyvsp[-5].forvariable).scalar, (yylsp[-5]));
						}
						else
						{
							ereport(ERROR,
									(errcode(ERRCODE_SYNTAX_ERROR),
									 errmsg("loop variable of FOREACH must be a known variable or list of variables"),
											 parser_errposition((yylsp[-5]))));
						}

						check_labels((yyvsp[-7].str), (yyvsp[0].loop_body).end_label, (yyvsp[0].loop_body).end_label_location);
						plpgsql_ns_pop();

						(yyval.stmt) = (PLpgSQL_stmt *) new;
					}
#line 3769 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1682 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.ival) = 0;
					}
#line 3777 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1686 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.ival) = (yyvsp[0].ival);
					}
#line 3785 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1692 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_exit *new;

						new = palloc0(sizeof(PLpgSQL_stmt_exit));
						new->cmd_type = PLPGSQL_STMT_EXIT;
						new->stmtid	  = ++plpgsql_curr_compile->nstatements;
						new->is_exit  = (yyvsp[-2].boolean);
						new->lineno	  = plpgsql_location_to_lineno((yylsp[-2]));
						new->label	  = (yyvsp[-1].str);
						new->cond	  = (yyvsp[0].expr);

						if ((yyvsp[-1].str))
						{
							/* We have a label, so verify it exists */
							PLpgSQL_nsitem *label;

							label = plpgsql_ns_lookup_label(plpgsql_ns_top(), (yyvsp[-1].str));
							if (label == NULL)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 errmsg("there is no label \"%s\" "
												"attached to any block or loop enclosing this statement",
												(yyvsp[-1].str)),
										 parser_errposition((yylsp[-1]))));
							/* CONTINUE only allows loop labels */
							if (label->itemno != PLPGSQL_LABEL_LOOP && !new->is_exit)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 errmsg("block label \"%s\" cannot be used in CONTINUE",
												(yyvsp[-1].str)),
										 parser_errposition((yylsp[-1]))));
						}
						else
						{
							/*
							 * No label, so make sure there is some loop (an
							 * unlabeled EXIT does not match a block, so this
							 * is the same test for both EXIT and CONTINUE)
							 */
							if (plpgsql_ns_find_nearest_loop(plpgsql_ns_top()) == NULL)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 new->is_exit ?
										 errmsg("EXIT cannot be used outside a loop, unless it has a label") :
										 errmsg("CONTINUE cannot be used outside a loop"),
										 parser_errposition((yylsp[-2]))));
						}

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 3840 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1745 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.boolean) = true;
					}
#line 3848 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1749 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.boolean) = false;
					}
#line 3856 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1755 "pl_gram.y" /* yacc.c:1652  */
    {
						int	tok;

						tok = yylex();
						if (tok == 0)
							yyerror("unexpected end of function definition");

						if (tok_is_keyword(tok, &yylval,
										   K_NEXT, "next"))
						{
							(yyval.stmt) = make_return_next_stmt((yylsp[0]));
						}
						else if (tok_is_keyword(tok, &yylval,
												K_QUERY, "query"))
						{
							(yyval.stmt) = make_return_query_stmt((yylsp[0]));
						}
						else
						{
							plpgsql_push_back_token(tok);
							(yyval.stmt) = make_return_stmt((yylsp[0]));
						}
					}
#line 3884 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1781 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_raise		*new;
						int	tok;

						new = palloc(sizeof(PLpgSQL_stmt_raise));

						new->cmd_type	= PLPGSQL_STMT_RAISE;
						new->lineno		= plpgsql_location_to_lineno((yylsp[0]));
						new->stmtid		= ++plpgsql_curr_compile->nstatements;
						new->elog_level = ERROR;	/* default */
						new->condname	= NULL;
						new->message	= NULL;
						new->params		= NIL;
						new->options	= NIL;

						tok = yylex();
						if (tok == 0)
							yyerror("unexpected end of function definition");

						/*
						 * We could have just RAISE, meaning to re-throw
						 * the current error.
						 */
						if (tok != ';')
						{
							/*
							 * First is an optional elog severity level.
							 */
							if (tok_is_keyword(tok, &yylval,
											   K_EXCEPTION, "exception"))
							{
								new->elog_level = ERROR;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_WARNING, "warning"))
							{
								new->elog_level = WARNING;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_NOTICE, "notice"))
							{
								new->elog_level = NOTICE;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_INFO, "info"))
							{
								new->elog_level = INFO;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_LOG, "log"))
							{
								new->elog_level = LOG;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_DEBUG, "debug"))
							{
								new->elog_level = DEBUG1;
								tok = yylex();
							}
							if (tok == 0)
								yyerror("unexpected end of function definition");

							/*
							 * Next we can have a condition name, or
							 * equivalently SQLSTATE 'xxxxx', or a string
							 * literal that is the old-style message format,
							 * or USING to start the option list immediately.
							 */
							if (tok == SCONST)
							{
								/* old style message and parameters */
								new->message = yylval.str;
								/*
								 * We expect either a semi-colon, which
								 * indicates no parameters, or a comma that
								 * begins the list of parameter expressions,
								 * or USING to begin the options list.
								 */
								tok = yylex();
								if (tok != ',' && tok != ';' && tok != K_USING)
									yyerror("syntax error");

								while (tok == ',')
								{
									PLpgSQL_expr *expr;

									expr = read_sql_construct(',', ';', K_USING,
															  ", or ; or USING",
															  "SELECT ",
															  true, true, true,
															  NULL, &tok);
									new->params = lappend(new->params, expr);
								}
							}
							else if (tok != K_USING)
							{
								/* must be condition name or SQLSTATE */
								if (tok_is_keyword(tok, &yylval,
												   K_SQLSTATE, "sqlstate"))
								{
									/* next token should be a string literal */
									char   *sqlstatestr;

									if (yylex() != SCONST)
										yyerror("syntax error");
									sqlstatestr = yylval.str;

									if (strlen(sqlstatestr) != 5)
										yyerror("invalid SQLSTATE code");
									if (strspn(sqlstatestr, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ") != 5)
										yyerror("invalid SQLSTATE code");
									new->condname = sqlstatestr;
								}
								else
								{
									if (tok == T_WORD)
										new->condname = yylval.word.ident;
									else if (plpgsql_token_is_unreserved_keyword(tok))
										new->condname = pstrdup(yylval.keyword);
									else
										yyerror("syntax error");
									plpgsql_recognize_err_condition(new->condname,
																	false);
								}
								tok = yylex();
								if (tok != ';' && tok != K_USING)
									yyerror("syntax error");
							}

							if (tok == K_USING)
								new->options = read_raise_options();
						}

						check_raise_parameters(new);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 4031 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1926 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_assert		*new;
						int	tok;

						new = palloc(sizeof(PLpgSQL_stmt_assert));

						new->cmd_type	= PLPGSQL_STMT_ASSERT;
						new->lineno		= plpgsql_location_to_lineno((yylsp[0]));
						new->stmtid		= ++plpgsql_curr_compile->nstatements;

						new->cond = read_sql_expression2(',', ';',
														 ", or ;",
														 &tok);

						if (tok == ',')
							new->message = read_sql_expression(';', ";");
						else
							new->message = NULL;

						(yyval.stmt) = (PLpgSQL_stmt *) new;
					}
#line 4057 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1950 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.loop_body).stmts = (yyvsp[-4].list);
						(yyval.loop_body).end_label = (yyvsp[-1].str);
						(yyval.loop_body).end_label_location = (yylsp[-1]);
					}
#line 4067 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1968 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.stmt) = make_execsql_stmt(K_IMPORT, (yylsp[0]));
					}
#line 4075 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1972 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.stmt) = make_execsql_stmt(K_INSERT, (yylsp[0]));
					}
#line 4083 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1976 "pl_gram.y" /* yacc.c:1652  */
    {
						int			tok;

						tok = yylex();
						plpgsql_push_back_token(tok);
						if (tok == '=' || tok == COLON_EQUALS || tok == '[')
							word_is_not_variable(&((yyvsp[0].word)), (yylsp[0]));
						(yyval.stmt) = make_execsql_stmt(T_WORD, (yylsp[0]));
					}
#line 4097 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1986 "pl_gram.y" /* yacc.c:1652  */
    {
						int			tok;

						tok = yylex();
						plpgsql_push_back_token(tok);
						if (tok == '=' || tok == COLON_EQUALS || tok == '[')
							cword_is_not_variable(&((yyvsp[0].cword)), (yylsp[0]));
						(yyval.stmt) = make_execsql_stmt(T_CWORD, (yylsp[0]));
					}
#line 4111 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1998 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_dynexecute *new;
						PLpgSQL_expr *expr;
						int endtoken;

						expr = read_sql_construct(K_INTO, K_USING, ';',
												  "INTO or USING or ;",
												  "SELECT ",
												  true, true, true,
												  NULL, &endtoken);

						new = palloc(sizeof(PLpgSQL_stmt_dynexecute));
						new->cmd_type = PLPGSQL_STMT_DYNEXECUTE;
						new->lineno = plpgsql_location_to_lineno((yylsp[0]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->query = expr;
						new->into = false;
						new->strict = false;
						new->target = NULL;
						new->params = NIL;

						/*
						 * We loop to allow the INTO and USING clauses to
						 * appear in either order, since people easily get
						 * that wrong.  This coding also prevents "INTO foo"
						 * from getting absorbed into a USING expression,
						 * which is *really* confusing.
						 */
						for (;;)
						{
							if (endtoken == K_INTO)
							{
								if (new->into)			/* multiple INTO */
									yyerror("syntax error");
								new->into = true;
								read_into_target(&new->target, &new->strict);
								endtoken = yylex();
							}
							else if (endtoken == K_USING)
							{
								if (new->params)		/* multiple USING */
									yyerror("syntax error");
								do
								{
									expr = read_sql_construct(',', ';', K_INTO,
															  ", or ; or INTO",
															  "SELECT ",
															  true, true, true,
															  NULL, &endtoken);
									new->params = lappend(new->params, expr);
								} while (endtoken == ',');
							}
							else if (endtoken == ';')
								break;
							else
								yyerror("syntax error");
						}

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 4176 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 137:
#line 2062 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_open *new;
						int				  tok;

						new = palloc0(sizeof(PLpgSQL_stmt_open));
						new->cmd_type = PLPGSQL_STMT_OPEN;
						new->lineno = plpgsql_location_to_lineno((yylsp[-1]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->curvar = (yyvsp[0].var)->dno;
						new->cursor_options = CURSOR_OPT_FAST_PLAN;

						if ((yyvsp[0].var)->cursor_explicit_expr == NULL)
						{
							/* be nice if we could use opt_scrollable here */
							tok = yylex();
							if (tok_is_keyword(tok, &yylval,
											   K_NO, "no"))
							{
								tok = yylex();
								if (tok_is_keyword(tok, &yylval,
												   K_SCROLL, "scroll"))
								{
									new->cursor_options |= CURSOR_OPT_NO_SCROLL;
									tok = yylex();
								}
							}
							else if (tok_is_keyword(tok, &yylval,
													K_SCROLL, "scroll"))
							{
								new->cursor_options |= CURSOR_OPT_SCROLL;
								tok = yylex();
							}

							if (tok != K_FOR)
								yyerror("syntax error, expected \"FOR\"");

							tok = yylex();
							if (tok == K_EXECUTE)
							{
								int		endtoken;

								new->dynquery =
									read_sql_expression2(K_USING, ';',
														 "USING or ;",
														 &endtoken);

								/* If we found "USING", collect argument(s) */
								if (endtoken == K_USING)
								{
									PLpgSQL_expr *expr;

									do
									{
										expr = read_sql_expression2(',', ';',
																	", or ;",
																	&endtoken);
										new->params = lappend(new->params,
															  expr);
									} while (endtoken == ',');
								}
							}
							else
							{
								plpgsql_push_back_token(tok);
								new->query = read_sql_stmt("");
							}
						}
						else
						{
							/* predefined cursor query, so read args */
							new->argquery = read_cursor_args((yyvsp[0].var), ';', ";");
						}

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 4256 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 138:
#line 2140 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_fetch *fetch = (yyvsp[-2].fetch);
						PLpgSQL_variable *target;

						/* We have already parsed everything through the INTO keyword */
						read_into_target(&target, NULL);

						if (yylex() != ';')
							yyerror("syntax error");

						/*
						 * We don't allow multiple rows in PL/pgSQL's FETCH
						 * statement, only in MOVE.
						 */
						if (fetch->returns_multiple_rows)
							ereport(ERROR,
									(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
									 errmsg("FETCH statement cannot return multiple rows"),
									 parser_errposition((yylsp[-3]))));

						fetch->lineno = plpgsql_location_to_lineno((yylsp[-3]));
						fetch->target	= target;
						fetch->curvar	= (yyvsp[-1].var)->dno;
						fetch->is_move	= false;

						(yyval.stmt) = (PLpgSQL_stmt *)fetch;
					}
#line 4288 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 139:
#line 2170 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_fetch *fetch = (yyvsp[-2].fetch);

						fetch->lineno = plpgsql_location_to_lineno((yylsp[-3]));
						fetch->curvar	= (yyvsp[-1].var)->dno;
						fetch->is_move	= true;

						(yyval.stmt) = (PLpgSQL_stmt *)fetch;
					}
#line 4302 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 140:
#line 2182 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.fetch) = read_fetch_direction();
					}
#line 4310 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 141:
#line 2188 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_close *new;

						new = palloc(sizeof(PLpgSQL_stmt_close));
						new->cmd_type = PLPGSQL_STMT_CLOSE;
						new->lineno = plpgsql_location_to_lineno((yylsp[-2]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->curvar = (yyvsp[-1].var)->dno;

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 4326 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 142:
#line 2202 "pl_gram.y" /* yacc.c:1652  */
    {
						/* We do not bother building a node for NULL */
						(yyval.stmt) = NULL;
					}
#line 4335 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 143:
#line 2209 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_commit *new;

						new = palloc(sizeof(PLpgSQL_stmt_commit));
						new->cmd_type = PLPGSQL_STMT_COMMIT;
						new->lineno = plpgsql_location_to_lineno((yylsp[-2]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->chain = (yyvsp[-1].ival);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 4351 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 144:
#line 2223 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_rollback *new;

						new = palloc(sizeof(PLpgSQL_stmt_rollback));
						new->cmd_type = PLPGSQL_STMT_ROLLBACK;
						new->lineno = plpgsql_location_to_lineno((yylsp[-2]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->chain = (yyvsp[-1].ival);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 4367 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 145:
#line 2237 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.ival) = true; }
#line 4373 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 146:
#line 2238 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.ival) = false; }
#line 4379 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 147:
#line 2239 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.ival) = false; }
#line 4385 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 148:
#line 2243 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_set *new;

						new = palloc0(sizeof(PLpgSQL_stmt_set));
						new->cmd_type = PLPGSQL_STMT_SET;
						new->lineno = plpgsql_location_to_lineno((yylsp[0]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;

						new->expr = read_sql_stmt("SET ");

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 4402 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 149:
#line 2256 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_stmt_set *new;

						new = palloc0(sizeof(PLpgSQL_stmt_set));
						new->cmd_type = PLPGSQL_STMT_SET;
						new->lineno = plpgsql_location_to_lineno((yylsp[0]));
						new->stmtid = ++plpgsql_curr_compile->nstatements;
						new->expr = read_sql_stmt("RESET ");

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
#line 4418 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 150:
#line 2271 "pl_gram.y" /* yacc.c:1652  */
    {
						/*
						 * In principle we should support a cursor_variable
						 * that is an array element, but for now we don't, so
						 * just throw an error if next token is '['.
						 */
						if ((yyvsp[0].wdatum).datum->dtype != PLPGSQL_DTYPE_VAR ||
							plpgsql_peek() == '[')
							ereport(ERROR,
									(errcode(ERRCODE_DATATYPE_MISMATCH),
									 errmsg("cursor variable must be a simple variable"),
									 parser_errposition((yylsp[0]))));

						if (((PLpgSQL_var *) (yyvsp[0].wdatum).datum)->datatype->typoid != REFCURSOROID)
							ereport(ERROR,
									(errcode(ERRCODE_DATATYPE_MISMATCH),
									 errmsg("variable \"%s\" must be of type cursor or refcursor",
											((PLpgSQL_var *) (yyvsp[0].wdatum).datum)->refname),
									 parser_errposition((yylsp[0]))));
						(yyval.var) = (PLpgSQL_var *) (yyvsp[0].wdatum).datum;
					}
#line 4444 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 151:
#line 2293 "pl_gram.y" /* yacc.c:1652  */
    {
						/* just to give a better message than "syntax error" */
						word_is_not_variable(&((yyvsp[0].word)), (yylsp[0]));
					}
#line 4453 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 152:
#line 2298 "pl_gram.y" /* yacc.c:1652  */
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[0].cword)), (yylsp[0]));
					}
#line 4462 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 153:
#line 2305 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.exception_block) = NULL; }
#line 4468 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 154:
#line 2307 "pl_gram.y" /* yacc.c:1652  */
    {
						/*
						 * We use a mid-rule action to add these
						 * special variables to the namespace before
						 * parsing the WHEN clauses themselves.  The
						 * scope of the names extends to the end of the
						 * current block.
						 */
						int			lineno = plpgsql_location_to_lineno((yylsp[0]));
						PLpgSQL_exception_block *new = palloc(sizeof(PLpgSQL_exception_block));
						PLpgSQL_variable *var;

						var = plpgsql_build_variable("sqlstate", lineno,
													 plpgsql_build_datatype(TEXTOID,
																			-1,
																			plpgsql_curr_compile->fn_input_collation,
																			NULL),
													 true);
						var->isconst = true;
						new->sqlstate_varno = var->dno;

						var = plpgsql_build_variable("sqlerrm", lineno,
													 plpgsql_build_datatype(TEXTOID,
																			-1,
																			plpgsql_curr_compile->fn_input_collation,
																			NULL),
													 true);
						var->isconst = true;
						new->sqlerrm_varno = var->dno;

						(yyval.exception_block) = new;
					}
#line 4505 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 155:
#line 2340 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_exception_block *new = (yyvsp[-1].exception_block);
						new->exc_list = (yyvsp[0].list);

						(yyval.exception_block) = new;
					}
#line 4516 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 156:
#line 2349 "pl_gram.y" /* yacc.c:1652  */
    {
							(yyval.list) = lappend((yyvsp[-1].list), (yyvsp[0].exception));
						}
#line 4524 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 157:
#line 2353 "pl_gram.y" /* yacc.c:1652  */
    {
							(yyval.list) = list_make1((yyvsp[0].exception));
						}
#line 4532 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 158:
#line 2359 "pl_gram.y" /* yacc.c:1652  */
    {
						PLpgSQL_exception *new;

						new = palloc0(sizeof(PLpgSQL_exception));
						new->lineno = plpgsql_location_to_lineno((yylsp[-3]));
						new->conditions = (yyvsp[-2].condition);
						new->action = (yyvsp[0].list);

						(yyval.exception) = new;
					}
#line 4547 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 159:
#line 2372 "pl_gram.y" /* yacc.c:1652  */
    {
							PLpgSQL_condition	*old;

							for (old = (yyvsp[-2].condition); old->next != NULL; old = old->next)
								/* skip */ ;
							old->next = (yyvsp[0].condition);
							(yyval.condition) = (yyvsp[-2].condition);
						}
#line 4560 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 160:
#line 2381 "pl_gram.y" /* yacc.c:1652  */
    {
							(yyval.condition) = (yyvsp[0].condition);
						}
#line 4568 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 161:
#line 2387 "pl_gram.y" /* yacc.c:1652  */
    {
							if (strcmp((yyvsp[0].str), "sqlstate") != 0)
							{
								(yyval.condition) = plpgsql_parse_err_condition((yyvsp[0].str));
							}
							else
							{
								PLpgSQL_condition *new;
								char   *sqlstatestr;

								/* next token should be a string literal */
								if (yylex() != SCONST)
									yyerror("syntax error");
								sqlstatestr = yylval.str;

								if (strlen(sqlstatestr) != 5)
									yyerror("invalid SQLSTATE code");
								if (strspn(sqlstatestr, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ") != 5)
									yyerror("invalid SQLSTATE code");

								new = palloc(sizeof(PLpgSQL_condition));
								new->sqlerrstate =
									MAKE_SQLSTATE(sqlstatestr[0],
												  sqlstatestr[1],
												  sqlstatestr[2],
												  sqlstatestr[3],
												  sqlstatestr[4]);
								new->condname = sqlstatestr;
								new->next = NULL;

								(yyval.condition) = new;
							}
						}
#line 4606 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 162:
#line 2423 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.expr) = read_sql_expression(';', ";"); }
#line 4612 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 163:
#line 2427 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.expr) = read_sql_expression(']', "]"); }
#line 4618 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 164:
#line 2431 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.expr) = read_sql_expression(K_THEN, "THEN"); }
#line 4624 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 165:
#line 2435 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.expr) = read_sql_expression(K_LOOP, "LOOP"); }
#line 4630 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 166:
#line 2439 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_ns_push(NULL, PLPGSQL_LABEL_BLOCK);
						(yyval.str) = NULL;
					}
#line 4639 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 167:
#line 2444 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_ns_push((yyvsp[-1].str), PLPGSQL_LABEL_BLOCK);
						(yyval.str) = (yyvsp[-1].str);
					}
#line 4648 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 168:
#line 2451 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_ns_push(NULL, PLPGSQL_LABEL_LOOP);
						(yyval.str) = NULL;
					}
#line 4657 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 169:
#line 2456 "pl_gram.y" /* yacc.c:1652  */
    {
						plpgsql_ns_push((yyvsp[-1].str), PLPGSQL_LABEL_LOOP);
						(yyval.str) = (yyvsp[-1].str);
					}
#line 4666 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 170:
#line 2463 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.str) = NULL;
					}
#line 4674 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 171:
#line 2467 "pl_gram.y" /* yacc.c:1652  */
    {
						/* label validity will be checked by outer production */
						(yyval.str) = (yyvsp[0].str);
					}
#line 4683 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 172:
#line 2474 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 4689 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 173:
#line 2476 "pl_gram.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 4695 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 174:
#line 2483 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.str) = (yyvsp[0].word).ident;
					}
#line 4703 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 175:
#line 2487 "pl_gram.y" /* yacc.c:1652  */
    {
						(yyval.str) = pstrdup((yyvsp[0].keyword));
					}
#line 4711 "pl_gram.c" /* yacc.c:1652  */
    break;

  case 176:
#line 2491 "pl_gram.y" /* yacc.c:1652  */
    {
						if ((yyvsp[0].wdatum).ident == NULL) /* composite name not OK */
							yyerror("syntax error");
						(yyval.str) = (yyvsp[0].wdatum).ident;
					}
#line 4721 "pl_gram.c" /* yacc.c:1652  */
    break;


#line 4725 "pl_gram.c" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2583 "pl_gram.y" /* yacc.c:1918  */


/*
 * Check whether a token represents an "unreserved keyword".
 * We have various places where we want to recognize a keyword in preference
 * to a variable name, but not reserve that keyword in other contexts.
 * Hence, this kluge.
 */
static bool
tok_is_keyword(int token, union YYSTYPE *lval,
			   int kw_token, const char *kw_str)
{
	if (token == kw_token)
	{
		/* Normal case, was recognized by scanner (no conflicting variable) */
		return true;
	}
	else if (token == T_DATUM)
	{
		/*
		 * It's a variable, so recheck the string name.  Note we will not
		 * match composite names (hence an unreserved word followed by "."
		 * will not be recognized).
		 */
		if (!lval->wdatum.quoted && lval->wdatum.ident != NULL &&
			strcmp(lval->wdatum.ident, kw_str) == 0)
			return true;
	}
	return false;				/* not the keyword */
}

/*
 * Convenience routine to complain when we expected T_DATUM and got T_WORD,
 * ie, unrecognized variable.
 */
static void
word_is_not_variable(PLword *word, int location)
{
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("\"%s\" is not a known variable",
					word->ident),
			 parser_errposition(location)));
}

/* Same, for a CWORD */
static void
cword_is_not_variable(PLcword *cword, int location)
{
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("\"%s\" is not a known variable",
					NameListToString(cword->idents)),
			 parser_errposition(location)));
}

/*
 * Convenience routine to complain when we expected T_DATUM and got
 * something else.  "tok" must be the current token, since we also
 * look at yylval and yylloc.
 */
static void
current_token_is_not_variable(int tok)
{
	if (tok == T_WORD)
		word_is_not_variable(&(yylval.word), yylloc);
	else if (tok == T_CWORD)
		cword_is_not_variable(&(yylval.cword), yylloc);
	else
		yyerror("syntax error");
}

/* Convenience routine to read an expression with one possible terminator */
static PLpgSQL_expr *
read_sql_expression(int until, const char *expected)
{
	return read_sql_construct(until, 0, 0, expected,
							  "SELECT ", true, true, true, NULL, NULL);
}

/* Convenience routine to read an expression with two possible terminators */
static PLpgSQL_expr *
read_sql_expression2(int until, int until2, const char *expected,
					 int *endtoken)
{
	return read_sql_construct(until, until2, 0, expected,
							  "SELECT ", true, true, true, NULL, endtoken);
}

/* Convenience routine to read a SQL statement that must end with ';' */
static PLpgSQL_expr *
read_sql_stmt(const char *sqlstart)
{
	return read_sql_construct(';', 0, 0, ";",
							  sqlstart, false, true, true, NULL, NULL);
}

/*
 * Read a SQL construct and build a PLpgSQL_expr for it.
 *
 * until:		token code for expected terminator
 * until2:		token code for alternate terminator (pass 0 if none)
 * until3:		token code for another alternate terminator (pass 0 if none)
 * expected:	text to use in complaining that terminator was not found
 * sqlstart:	text to prefix to the accumulated SQL text
 * isexpression: whether to say we're reading an "expression" or a "statement"
 * valid_sql:   whether to check the syntax of the expr (prefixed with sqlstart)
 * trim:		trim trailing whitespace
 * startloc:	if not NULL, location of first token is stored at *startloc
 * endtoken:	if not NULL, ending token is stored at *endtoken
 *				(this is only interesting if until2 or until3 isn't zero)
 */
static PLpgSQL_expr *
read_sql_construct(int until,
				   int until2,
				   int until3,
				   const char *expected,
				   const char *sqlstart,
				   bool isexpression,
				   bool valid_sql,
				   bool trim,
				   int *startloc,
				   int *endtoken)
{
	int					tok;
	StringInfoData		ds;
	IdentifierLookup	save_IdentifierLookup;
	int					startlocation = -1;
	int					parenlevel = 0;
	PLpgSQL_expr		*expr;

	initStringInfo(&ds);
	appendStringInfoString(&ds, sqlstart);

	/* special lookup mode for identifiers within the SQL text */
	save_IdentifierLookup = plpgsql_IdentifierLookup;
	plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;

	for (;;)
	{
		tok = yylex();
		if (startlocation < 0)			/* remember loc of first token */
			startlocation = yylloc;
		if (tok == until && parenlevel == 0)
			break;
		if (tok == until2 && parenlevel == 0)
			break;
		if (tok == until3 && parenlevel == 0)
			break;
		if (tok == '(' || tok == '[')
			parenlevel++;
		else if (tok == ')' || tok == ']')
		{
			parenlevel--;
			if (parenlevel < 0)
				yyerror("mismatched parentheses");
		}
		/*
		 * End of function definition is an error, and we don't expect to
		 * hit a semicolon either (unless it's the until symbol, in which
		 * case we should have fallen out above).
		 */
		if (tok == 0 || tok == ';')
		{
			if (parenlevel != 0)
				yyerror("mismatched parentheses");
			if (isexpression)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("missing \"%s\" at end of SQL expression",
								expected),
						 parser_errposition(yylloc)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("missing \"%s\" at end of SQL statement",
								expected),
						 parser_errposition(yylloc)));
		}
	}

	plpgsql_IdentifierLookup = save_IdentifierLookup;

	if (startloc)
		*startloc = startlocation;
	if (endtoken)
		*endtoken = tok;

	/* give helpful complaint about empty input */
	if (startlocation >= yylloc)
	{
		if (isexpression)
			yyerror("missing expression");
		else
			yyerror("missing SQL statement");
	}

	plpgsql_append_source_text(&ds, startlocation, yylloc);

	/* trim any trailing whitespace, for neatness */
	if (trim)
	{
		while (ds.len > 0 && scanner_isspace(ds.data[ds.len - 1]))
			ds.data[--ds.len] = '\0';
	}

	expr = palloc0(sizeof(PLpgSQL_expr));
	expr->query			= pstrdup(ds.data);
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->rwparam		= -1;
	expr->ns			= plpgsql_ns_top();
	pfree(ds.data);

	if (valid_sql)
		check_sql_expr(expr->query, startlocation, strlen(sqlstart));

	return expr;
}

static PLpgSQL_type *
read_datatype(int tok)
{
	StringInfoData		ds;
	char			   *type_name;
	int					startlocation;
	PLpgSQL_type		*result;
	int					parenlevel = 0;

	/* Should only be called while parsing DECLARE sections */
	Assert(plpgsql_IdentifierLookup == IDENTIFIER_LOOKUP_DECLARE);

	/* Often there will be a lookahead token, but if not, get one */
	if (tok == YYEMPTY)
		tok = yylex();

	startlocation = yylloc;

	/*
	 * If we have a simple or composite identifier, check for %TYPE
	 * and %ROWTYPE constructs.
	 */
	if (tok == T_WORD)
	{
		char   *dtname = yylval.word.ident;

		tok = yylex();
		if (tok == '%')
		{
			tok = yylex();
			if (tok_is_keyword(tok, &yylval,
							   K_TYPE, "type"))
			{
				result = plpgsql_parse_wordtype(dtname);
				if (result)
					return result;
			}
			else if (tok_is_keyword(tok, &yylval,
									K_ROWTYPE, "rowtype"))
			{
				result = plpgsql_parse_wordrowtype(dtname);
				if (result)
					return result;
			}
		}
	}
	else if (plpgsql_token_is_unreserved_keyword(tok))
	{
		char   *dtname = pstrdup(yylval.keyword);

		tok = yylex();
		if (tok == '%')
		{
			tok = yylex();
			if (tok_is_keyword(tok, &yylval,
							   K_TYPE, "type"))
			{
				result = plpgsql_parse_wordtype(dtname);
				if (result)
					return result;
			}
			else if (tok_is_keyword(tok, &yylval,
									K_ROWTYPE, "rowtype"))
			{
				result = plpgsql_parse_wordrowtype(dtname);
				if (result)
					return result;
			}
		}
	}
	else if (tok == T_CWORD)
	{
		List   *dtnames = yylval.cword.idents;

		tok = yylex();
		if (tok == '%')
		{
			tok = yylex();
			if (tok_is_keyword(tok, &yylval,
							   K_TYPE, "type"))
			{
				result = plpgsql_parse_cwordtype(dtnames);
				if (result)
					return result;
			}
			else if (tok_is_keyword(tok, &yylval,
									K_ROWTYPE, "rowtype"))
			{
				result = plpgsql_parse_cwordrowtype(dtnames);
				if (result)
					return result;
			}
		}
	}

	while (tok != ';')
	{
		if (tok == 0)
		{
			if (parenlevel != 0)
				yyerror("mismatched parentheses");
			else
				yyerror("incomplete data type declaration");
		}
		/* Possible followers for datatype in a declaration */
		if (tok == K_COLLATE || tok == K_NOT ||
			tok == '=' || tok == COLON_EQUALS || tok == K_DEFAULT)
			break;
		/* Possible followers for datatype in a cursor_arg list */
		if ((tok == ',' || tok == ')') && parenlevel == 0)
			break;
		if (tok == '(')
			parenlevel++;
		else if (tok == ')')
			parenlevel--;

		tok = yylex();
	}

	/* set up ds to contain complete typename text */
	initStringInfo(&ds);
	plpgsql_append_source_text(&ds, startlocation, yylloc);
	type_name = ds.data;

	if (type_name[0] == '\0')
		yyerror("missing data type declaration");

	result = parse_datatype(type_name, startlocation);

	pfree(ds.data);

	plpgsql_push_back_token(tok);

	return result;
}

static PLpgSQL_stmt *
make_execsql_stmt(int firsttoken, int location)
{
	StringInfoData		ds;
	IdentifierLookup	save_IdentifierLookup;
	PLpgSQL_stmt_execsql *execsql;
	PLpgSQL_expr		*expr;
	PLpgSQL_variable	*target = NULL;
	int					tok;
	int					prev_tok;
	bool				have_into = false;
	bool				have_strict = false;
	int					into_start_loc = -1;
	int					into_end_loc = -1;

	initStringInfo(&ds);

	/* special lookup mode for identifiers within the SQL text */
	save_IdentifierLookup = plpgsql_IdentifierLookup;
	plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;

	/*
	 * Scan to the end of the SQL command.  Identify any INTO-variables
	 * clause lurking within it, and parse that via read_into_target().
	 *
	 * Because INTO is sometimes used in the main SQL grammar, we have to be
	 * careful not to take any such usage of INTO as a PL/pgSQL INTO clause.
	 * There are currently three such cases:
	 *
	 * 1. SELECT ... INTO.  We don't care, we just override that with the
	 * PL/pgSQL definition.
	 *
	 * 2. INSERT INTO.  This is relatively easy to recognize since the words
	 * must appear adjacently; but we can't assume INSERT starts the command,
	 * because it can appear in CREATE RULE or WITH.  Unfortunately, INSERT is
	 * *not* fully reserved, so that means there is a chance of a false match;
	 * but it's not very likely.
	 *
	 * 3. IMPORT FOREIGN SCHEMA ... INTO.  This is not allowed in CREATE RULE
	 * or WITH, so we just check for IMPORT as the command's first token.
	 * (If IMPORT FOREIGN SCHEMA returned data someone might wish to capture
	 * with an INTO-variables clause, we'd have to work much harder here.)
	 *
	 * Fortunately, INTO is a fully reserved word in the main grammar, so
	 * at least we need not worry about it appearing as an identifier.
	 *
	 * Any future additional uses of INTO in the main grammar will doubtless
	 * break this logic again ... beware!
	 */
	tok = firsttoken;
	for (;;)
	{
		prev_tok = tok;
		tok = yylex();
		if (have_into && into_end_loc < 0)
			into_end_loc = yylloc;		/* token after the INTO part */
		if (tok == ';')
			break;
		if (tok == 0)
			yyerror("unexpected end of function definition");
		if (tok == K_INTO)
		{
			if (prev_tok == K_INSERT)
				continue;		/* INSERT INTO is not an INTO-target */
			if (firsttoken == K_IMPORT)
				continue;		/* IMPORT ... INTO is not an INTO-target */
			if (have_into)
				yyerror("INTO specified more than once");
			have_into = true;
			into_start_loc = yylloc;
			plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
			read_into_target(&target, &have_strict);
			plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;
		}
	}

	plpgsql_IdentifierLookup = save_IdentifierLookup;

	if (have_into)
	{
		/*
		 * Insert an appropriate number of spaces corresponding to the
		 * INTO text, so that locations within the redacted SQL statement
		 * still line up with those in the original source text.
		 */
		plpgsql_append_source_text(&ds, location, into_start_loc);
		appendStringInfoSpaces(&ds, into_end_loc - into_start_loc);
		plpgsql_append_source_text(&ds, into_end_loc, yylloc);
	}
	else
		plpgsql_append_source_text(&ds, location, yylloc);

	/* trim any trailing whitespace, for neatness */
	while (ds.len > 0 && scanner_isspace(ds.data[ds.len - 1]))
		ds.data[--ds.len] = '\0';

	expr = palloc0(sizeof(PLpgSQL_expr));
	expr->query			= pstrdup(ds.data);
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->rwparam		= -1;
	expr->ns			= plpgsql_ns_top();
	pfree(ds.data);

	check_sql_expr(expr->query, location, 0);

	execsql = palloc(sizeof(PLpgSQL_stmt_execsql));
	execsql->cmd_type = PLPGSQL_STMT_EXECSQL;
	execsql->lineno  = plpgsql_location_to_lineno(location);
	execsql->stmtid  = ++plpgsql_curr_compile->nstatements;
	execsql->sqlstmt = expr;
	execsql->into	 = have_into;
	execsql->strict	 = have_strict;
	execsql->target	 = target;

	return (PLpgSQL_stmt *) execsql;
}


/*
 * Read FETCH or MOVE direction clause (everything through FROM/IN).
 */
static PLpgSQL_stmt_fetch *
read_fetch_direction(void)
{
	PLpgSQL_stmt_fetch *fetch;
	int			tok;
	bool		check_FROM = true;

	/*
	 * We create the PLpgSQL_stmt_fetch struct here, but only fill in
	 * the fields arising from the optional direction clause
	 */
	fetch = (PLpgSQL_stmt_fetch *) palloc0(sizeof(PLpgSQL_stmt_fetch));
	fetch->cmd_type = PLPGSQL_STMT_FETCH;
	fetch->stmtid	= ++plpgsql_curr_compile->nstatements;
	/* set direction defaults: */
	fetch->direction = FETCH_FORWARD;
	fetch->how_many  = 1;
	fetch->expr		 = NULL;
	fetch->returns_multiple_rows = false;

	tok = yylex();
	if (tok == 0)
		yyerror("unexpected end of function definition");

	if (tok_is_keyword(tok, &yylval,
					   K_NEXT, "next"))
	{
		/* use defaults */
	}
	else if (tok_is_keyword(tok, &yylval,
							K_PRIOR, "prior"))
	{
		fetch->direction = FETCH_BACKWARD;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_FIRST, "first"))
	{
		fetch->direction = FETCH_ABSOLUTE;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_LAST, "last"))
	{
		fetch->direction = FETCH_ABSOLUTE;
		fetch->how_many  = -1;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_ABSOLUTE, "absolute"))
	{
		fetch->direction = FETCH_ABSOLUTE;
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		check_FROM = false;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_RELATIVE, "relative"))
	{
		fetch->direction = FETCH_RELATIVE;
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		check_FROM = false;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_ALL, "all"))
	{
		fetch->how_many = FETCH_ALL;
		fetch->returns_multiple_rows = true;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_FORWARD, "forward"))
	{
		complete_direction(fetch, &check_FROM);
	}
	else if (tok_is_keyword(tok, &yylval,
							K_BACKWARD, "backward"))
	{
		fetch->direction = FETCH_BACKWARD;
		complete_direction(fetch, &check_FROM);
	}
	else if (tok == K_FROM || tok == K_IN)
	{
		/* empty direction */
		check_FROM = false;
	}
	else if (tok == T_DATUM)
	{
		/* Assume there's no direction clause and tok is a cursor name */
		plpgsql_push_back_token(tok);
		check_FROM = false;
	}
	else
	{
		/*
		 * Assume it's a count expression with no preceding keyword.
		 * Note: we allow this syntax because core SQL does, but we don't
		 * document it because of the ambiguity with the omitted-direction
		 * case.  For instance, "MOVE n IN c" will fail if n is a variable.
		 * Perhaps this can be improved someday, but it's hardly worth a
		 * lot of work.
		 */
		plpgsql_push_back_token(tok);
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		fetch->returns_multiple_rows = true;
		check_FROM = false;
	}

	/* check FROM or IN keyword after direction's specification */
	if (check_FROM)
	{
		tok = yylex();
		if (tok != K_FROM && tok != K_IN)
			yyerror("expected FROM or IN");
	}

	return fetch;
}

/*
 * Process remainder of FETCH/MOVE direction after FORWARD or BACKWARD.
 * Allows these cases:
 *   FORWARD expr,  FORWARD ALL,  FORWARD
 *   BACKWARD expr, BACKWARD ALL, BACKWARD
 */
static void
complete_direction(PLpgSQL_stmt_fetch *fetch,  bool *check_FROM)
{
	int			tok;

	tok = yylex();
	if (tok == 0)
		yyerror("unexpected end of function definition");

	if (tok == K_FROM || tok == K_IN)
	{
		*check_FROM = false;
		return;
	}

	if (tok == K_ALL)
	{
		fetch->how_many = FETCH_ALL;
		fetch->returns_multiple_rows = true;
		*check_FROM = true;
		return;
	}

	plpgsql_push_back_token(tok);
	fetch->expr = read_sql_expression2(K_FROM, K_IN,
									   "FROM or IN",
									   NULL);
	fetch->returns_multiple_rows = true;
	*check_FROM = false;
}


static PLpgSQL_stmt *
make_return_stmt(int location)
{
	PLpgSQL_stmt_return *new;

	new = palloc0(sizeof(PLpgSQL_stmt_return));
	new->cmd_type = PLPGSQL_STMT_RETURN;
	new->lineno   = plpgsql_location_to_lineno(location);
	new->stmtid	  = ++plpgsql_curr_compile->nstatements;
	new->expr	  = NULL;
	new->retvarno = -1;

	if (plpgsql_curr_compile->fn_retset)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN cannot have a parameter in function returning set"),
					 errhint("Use RETURN NEXT or RETURN QUERY."),
					 parser_errposition(yylloc)));
	}
	else if (plpgsql_curr_compile->fn_rettype == VOIDOID)
	{
		if (yylex() != ';')
		{
			if (plpgsql_curr_compile->fn_prokind == PROKIND_PROCEDURE)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("RETURN cannot have a parameter in a procedure"),
						 parser_errposition(yylloc)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("RETURN cannot have a parameter in function returning void"),
						 parser_errposition(yylloc)));
		}
	}
	else if (plpgsql_curr_compile->out_param_varno >= 0)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN cannot have a parameter in function with OUT parameters"),
					 parser_errposition(yylloc)));
		new->retvarno = plpgsql_curr_compile->out_param_varno;
	}
	else
	{
		/*
		 * We want to special-case simple variable references for efficiency.
		 * So peek ahead to see if that's what we have.
		 */
		int		tok = yylex();

		if (tok == T_DATUM && plpgsql_peek() == ';' &&
			(yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_VAR ||
			 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_PROMISE ||
			 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_ROW ||
			 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_REC))
		{
			new->retvarno = yylval.wdatum.datum->dno;
			/* eat the semicolon token that we only peeked at above */
			tok = yylex();
			Assert(tok == ';');
		}
		else
		{
			/*
			 * Not (just) a variable name, so treat as expression.
			 *
			 * Note that a well-formed expression is _required_ here;
			 * anything else is a compile-time error.
			 */
			plpgsql_push_back_token(tok);
			new->expr = read_sql_expression(';', ";");
		}
	}

	return (PLpgSQL_stmt *) new;
}


static PLpgSQL_stmt *
make_return_next_stmt(int location)
{
	PLpgSQL_stmt_return_next *new;

	if (!plpgsql_curr_compile->fn_retset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("cannot use RETURN NEXT in a non-SETOF function"),
				 parser_errposition(location)));

	new = palloc0(sizeof(PLpgSQL_stmt_return_next));
	new->cmd_type	= PLPGSQL_STMT_RETURN_NEXT;
	new->lineno		= plpgsql_location_to_lineno(location);
	new->stmtid		= ++plpgsql_curr_compile->nstatements;
	new->expr		= NULL;
	new->retvarno	= -1;

	if (plpgsql_curr_compile->out_param_varno >= 0)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN NEXT cannot have a parameter in function with OUT parameters"),
					 parser_errposition(yylloc)));
		new->retvarno = plpgsql_curr_compile->out_param_varno;
	}
	else
	{
		/*
		 * We want to special-case simple variable references for efficiency.
		 * So peek ahead to see if that's what we have.
		 */
		int		tok = yylex();

		if (tok == T_DATUM && plpgsql_peek() == ';' &&
			(yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_VAR ||
			 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_PROMISE ||
			 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_ROW ||
			 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_REC))
		{
			new->retvarno = yylval.wdatum.datum->dno;
			/* eat the semicolon token that we only peeked at above */
			tok = yylex();
			Assert(tok == ';');
		}
		else
		{
			/*
			 * Not (just) a variable name, so treat as expression.
			 *
			 * Note that a well-formed expression is _required_ here;
			 * anything else is a compile-time error.
			 */
			plpgsql_push_back_token(tok);
			new->expr = read_sql_expression(';', ";");
		}
	}

	return (PLpgSQL_stmt *) new;
}


static PLpgSQL_stmt *
make_return_query_stmt(int location)
{
	PLpgSQL_stmt_return_query *new;
	int			tok;

	if (!plpgsql_curr_compile->fn_retset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("cannot use RETURN QUERY in a non-SETOF function"),
				 parser_errposition(location)));

	new = palloc0(sizeof(PLpgSQL_stmt_return_query));
	new->cmd_type = PLPGSQL_STMT_RETURN_QUERY;
	new->lineno = plpgsql_location_to_lineno(location);
	new->stmtid = ++plpgsql_curr_compile->nstatements;

	/* check for RETURN QUERY EXECUTE */
	if ((tok = yylex()) != K_EXECUTE)
	{
		/* ordinary static query */
		plpgsql_push_back_token(tok);
		new->query = read_sql_stmt("");
	}
	else
	{
		/* dynamic SQL */
		int		term;

		new->dynquery = read_sql_expression2(';', K_USING, "; or USING",
											 &term);
		if (term == K_USING)
		{
			do
			{
				PLpgSQL_expr *expr;

				expr = read_sql_expression2(',', ';', ", or ;", &term);
				new->params = lappend(new->params, expr);
			} while (term == ',');
		}
	}

	return (PLpgSQL_stmt *) new;
}


/* convenience routine to fetch the name of a T_DATUM */
static char *
NameOfDatum(PLwdatum *wdatum)
{
	if (wdatum->ident)
		return wdatum->ident;
	Assert(wdatum->idents != NIL);
	return NameListToString(wdatum->idents);
}

static void
check_assignable(PLpgSQL_datum *datum, int location)
{
	switch (datum->dtype)
	{
		case PLPGSQL_DTYPE_VAR:
		case PLPGSQL_DTYPE_PROMISE:
		case PLPGSQL_DTYPE_REC:
			if (((PLpgSQL_variable *) datum)->isconst)
				ereport(ERROR,
						(errcode(ERRCODE_ERROR_IN_ASSIGNMENT),
						 errmsg("variable \"%s\" is declared CONSTANT",
								((PLpgSQL_variable *) datum)->refname),
						 parser_errposition(location)));
			break;
		case PLPGSQL_DTYPE_ROW:
			/* always assignable; member vars were checked at compile time */
			break;
		case PLPGSQL_DTYPE_RECFIELD:
			/* assignable if parent record is */
			check_assignable(plpgsql_Datums[((PLpgSQL_recfield *) datum)->recparentno],
							 location);
			break;
		case PLPGSQL_DTYPE_ARRAYELEM:
			/* assignable if parent array is */
			check_assignable(plpgsql_Datums[((PLpgSQL_arrayelem *) datum)->arrayparentno],
							 location);
			break;
		default:
			elog(ERROR, "unrecognized dtype: %d", datum->dtype);
			break;
	}
}

/*
 * Read the argument of an INTO clause.  On entry, we have just read the
 * INTO keyword.
 */
static void
read_into_target(PLpgSQL_variable **target, bool *strict)
{
	int			tok;

	/* Set default results */
	*target = NULL;
	if (strict)
		*strict = false;

	tok = yylex();
	if (strict && tok == K_STRICT)
	{
		*strict = true;
		tok = yylex();
	}

	/*
	 * Currently, a row or record variable can be the single INTO target,
	 * but not a member of a multi-target list.  So we throw error if there
	 * is a comma after it, because that probably means the user tried to
	 * write a multi-target list.  If this ever gets generalized, we should
	 * probably refactor read_into_scalar_list so it handles all cases.
	 */
	switch (tok)
	{
		case T_DATUM:
			if (yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_ROW ||
				yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_REC)
			{
				check_assignable(yylval.wdatum.datum, yylloc);
				*target = (PLpgSQL_variable *) yylval.wdatum.datum;

				if ((tok = yylex()) == ',')
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("record variable cannot be part of multiple-item INTO list"),
							 parser_errposition(yylloc)));
				plpgsql_push_back_token(tok);
			}
			else
			{
				*target = (PLpgSQL_variable *)
					read_into_scalar_list(NameOfDatum(&(yylval.wdatum)),
										  yylval.wdatum.datum, yylloc);
			}
			break;

		default:
			/* just to give a better message than "syntax error" */
			current_token_is_not_variable(tok);
	}
}

/*
 * Given the first datum and name in the INTO list, continue to read
 * comma-separated scalar variables until we run out. Then construct
 * and return a fake "row" variable that represents the list of
 * scalars.
 */
static PLpgSQL_row *
read_into_scalar_list(char *initial_name,
					  PLpgSQL_datum *initial_datum,
					  int initial_location)
{
	int				 nfields;
	char			*fieldnames[1024];
	int				 varnos[1024];
	PLpgSQL_row		*row;
	int				 tok;

	check_assignable(initial_datum, initial_location);
	fieldnames[0] = initial_name;
	varnos[0]	  = initial_datum->dno;
	nfields		  = 1;

	while ((tok = yylex()) == ',')
	{
		/* Check for array overflow */
		if (nfields >= 1024)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("too many INTO variables specified"),
					 parser_errposition(yylloc)));

		tok = yylex();
		switch (tok)
		{
			case T_DATUM:
				check_assignable(yylval.wdatum.datum, yylloc);
				if (yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_ROW ||
					yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_REC)
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("\"%s\" is not a scalar variable",
									NameOfDatum(&(yylval.wdatum))),
							 parser_errposition(yylloc)));
				fieldnames[nfields] = NameOfDatum(&(yylval.wdatum));
				varnos[nfields++]	= yylval.wdatum.datum->dno;
				break;

			default:
				/* just to give a better message than "syntax error" */
				current_token_is_not_variable(tok);
		}
	}

	/*
	 * We read an extra, non-comma token from yylex(), so push it
	 * back onto the input stream
	 */
	plpgsql_push_back_token(tok);

	row = palloc0(sizeof(PLpgSQL_row));
	row->dtype = PLPGSQL_DTYPE_ROW;
	row->refname = "(unnamed row)";
	row->lineno = plpgsql_location_to_lineno(initial_location);
	row->rowtupdesc = NULL;
	row->nfields = nfields;
	row->fieldnames = palloc(sizeof(char *) * nfields);
	row->varnos = palloc(sizeof(int) * nfields);
	while (--nfields >= 0)
	{
		row->fieldnames[nfields] = fieldnames[nfields];
		row->varnos[nfields] = varnos[nfields];
	}

	plpgsql_adddatum((PLpgSQL_datum *)row);

	return row;
}

/*
 * Convert a single scalar into a "row" list.  This is exactly
 * like read_into_scalar_list except we never consume any input.
 *
 * Note: lineno could be computed from location, but since callers
 * have it at hand already, we may as well pass it in.
 */
static PLpgSQL_row *
make_scalar_list1(char *initial_name,
				  PLpgSQL_datum *initial_datum,
				  int lineno, int location)
{
	PLpgSQL_row		*row;

	check_assignable(initial_datum, location);

	row = palloc0(sizeof(PLpgSQL_row));
	row->dtype = PLPGSQL_DTYPE_ROW;
	row->refname = "(unnamed row)";
	row->lineno = lineno;
	row->rowtupdesc = NULL;
	row->nfields = 1;
	row->fieldnames = palloc(sizeof(char *));
	row->varnos = palloc(sizeof(int));
	row->fieldnames[0] = initial_name;
	row->varnos[0] = initial_datum->dno;

	plpgsql_adddatum((PLpgSQL_datum *)row);

	return row;
}

/*
 * When the PL/pgSQL parser expects to see a SQL statement, it is very
 * liberal in what it accepts; for example, we often assume an
 * unrecognized keyword is the beginning of a SQL statement. This
 * avoids the need to duplicate parts of the SQL grammar in the
 * PL/pgSQL grammar, but it means we can accept wildly malformed
 * input. To try and catch some of the more obviously invalid input,
 * we run the strings we expect to be SQL statements through the main
 * SQL parser.
 *
 * We only invoke the raw parser (not the analyzer); this doesn't do
 * any database access and does not check any semantic rules, it just
 * checks for basic syntactic correctness. We do this here, rather
 * than after parsing has finished, because a malformed SQL statement
 * may cause the PL/pgSQL parser to become confused about statement
 * borders. So it is best to bail out as early as we can.
 *
 * It is assumed that "stmt" represents a copy of the function source text
 * beginning at offset "location", with leader text of length "leaderlen"
 * (typically "SELECT ") prefixed to the source text.  We use this assumption
 * to transpose any error cursor position back to the function source text.
 * If no error cursor is provided, we'll just point at "location".
 */
static void
check_sql_expr(const char *stmt, int location, int leaderlen)
{
	sql_error_callback_arg cbarg;
	ErrorContextCallback  syntax_errcontext;
	MemoryContext oldCxt;

	if (!plpgsql_check_syntax)
		return;

	cbarg.location = location;
	cbarg.leaderlen = leaderlen;

	syntax_errcontext.callback = plpgsql_sql_error_callback;
	syntax_errcontext.arg = &cbarg;
	syntax_errcontext.previous = error_context_stack;
	error_context_stack = &syntax_errcontext;

	oldCxt = MemoryContextSwitchTo(plpgsql_compile_tmp_cxt);
	(void) raw_parser(stmt);
	MemoryContextSwitchTo(oldCxt);

	/* Restore former ereport callback */
	error_context_stack = syntax_errcontext.previous;
}

static void
plpgsql_sql_error_callback(void *arg)
{
	sql_error_callback_arg *cbarg = (sql_error_callback_arg *) arg;
	int			errpos;

	/*
	 * First, set up internalerrposition to point to the start of the
	 * statement text within the function text.  Note this converts
	 * location (a byte offset) to a character number.
	 */
	parser_errposition(cbarg->location);

	/*
	 * If the core parser provided an error position, transpose it.
	 * Note we are dealing with 1-based character numbers at this point.
	 */
	errpos = geterrposition();
	if (errpos > cbarg->leaderlen)
	{
		int		myerrpos = getinternalerrposition();

		if (myerrpos > 0)		/* safety check */
			internalerrposition(myerrpos + errpos - cbarg->leaderlen - 1);
	}

	/* In any case, flush errposition --- we want internalerrposition only */
	errposition(0);
}

/*
 * Parse a SQL datatype name and produce a PLpgSQL_type structure.
 *
 * The heavy lifting is done elsewhere.  Here we are only concerned
 * with setting up an errcontext link that will let us give an error
 * cursor pointing into the plpgsql function source, if necessary.
 * This is handled the same as in check_sql_expr(), and we likewise
 * expect that the given string is a copy from the source text.
 */
static PLpgSQL_type *
parse_datatype(const char *string, int location)
{
	TypeName   *typeName;
	Oid			type_id;
	int32		typmod;
	sql_error_callback_arg cbarg;
	ErrorContextCallback  syntax_errcontext;

	cbarg.location = location;
	cbarg.leaderlen = 0;

	syntax_errcontext.callback = plpgsql_sql_error_callback;
	syntax_errcontext.arg = &cbarg;
	syntax_errcontext.previous = error_context_stack;
	error_context_stack = &syntax_errcontext;

	/* Let the main parser try to parse it under standard SQL rules */
	typeName = typeStringToTypeName(string);
	typenameTypeIdAndMod(NULL, typeName, &type_id, &typmod);

	/* Restore former ereport callback */
	error_context_stack = syntax_errcontext.previous;

	/* Okay, build a PLpgSQL_type data structure for it */
	return plpgsql_build_datatype(type_id, typmod,
								  plpgsql_curr_compile->fn_input_collation,
								  typeName);
}

/*
 * Check block starting and ending labels match.
 */
static void
check_labels(const char *start_label, const char *end_label, int end_location)
{
	if (end_label)
	{
		if (!start_label)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("end label \"%s\" specified for unlabeled block",
							end_label),
					 parser_errposition(end_location)));

		if (strcmp(start_label, end_label) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("end label \"%s\" differs from block's label \"%s\"",
							end_label, start_label),
					 parser_errposition(end_location)));
	}
}

/*
 * Read the arguments (if any) for a cursor, followed by the until token
 *
 * If cursor has no args, just swallow the until token and return NULL.
 * If it does have args, we expect to see "( arg [, arg ...] )" followed
 * by the until token, where arg may be a plain expression, or a named
 * parameter assignment of the form argname := expr. Consume all that and
 * return a SELECT query that evaluates the expression(s) (without the outer
 * parens).
 */
static PLpgSQL_expr *
read_cursor_args(PLpgSQL_var *cursor, int until, const char *expected)
{
	PLpgSQL_expr *expr;
	PLpgSQL_row *row;
	int			tok;
	int			argc;
	char	  **argv;
	StringInfoData ds;
	char	   *sqlstart = "SELECT ";
	bool		any_named = false;

	tok = yylex();
	if (cursor->cursor_explicit_argrow < 0)
	{
		/* No arguments expected */
		if (tok == '(')
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("cursor \"%s\" has no arguments",
							cursor->refname),
					 parser_errposition(yylloc)));

		if (tok != until)
			yyerror("syntax error");

		return NULL;
	}

	/* Else better provide arguments */
	if (tok != '(')
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("cursor \"%s\" has arguments",
						cursor->refname),
				 parser_errposition(yylloc)));

	/*
	 * Read the arguments, one by one.
	 */
	row = (PLpgSQL_row *) plpgsql_Datums[cursor->cursor_explicit_argrow];
	argv = (char **) palloc0(row->nfields * sizeof(char *));

	for (argc = 0; argc < row->nfields; argc++)
	{
		PLpgSQL_expr *item;
		int		endtoken;
		int		argpos;
		int		tok1,
				tok2;
		int		arglocation;

		/* Check if it's a named parameter: "param := value" */
		plpgsql_peek2(&tok1, &tok2, &arglocation, NULL);
		if (tok1 == IDENT && tok2 == COLON_EQUALS)
		{
			char   *argname;
			IdentifierLookup save_IdentifierLookup;

			/* Read the argument name, ignoring any matching variable */
			save_IdentifierLookup = plpgsql_IdentifierLookup;
			plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_DECLARE;
			yylex();
			argname = yylval.str;
			plpgsql_IdentifierLookup = save_IdentifierLookup;

			/* Match argument name to cursor arguments */
			for (argpos = 0; argpos < row->nfields; argpos++)
			{
				if (strcmp(row->fieldnames[argpos], argname) == 0)
					break;
			}
			if (argpos == row->nfields)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("cursor \"%s\" has no argument named \"%s\"",
								cursor->refname, argname),
						 parser_errposition(yylloc)));

			/*
			 * Eat the ":=". We already peeked, so the error should never
			 * happen.
			 */
			tok2 = yylex();
			if (tok2 != COLON_EQUALS)
				yyerror("syntax error");

			any_named = true;
		}
		else
			argpos = argc;

		if (argv[argpos] != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("value for parameter \"%s\" of cursor \"%s\" specified more than once",
							row->fieldnames[argpos], cursor->refname),
					 parser_errposition(arglocation)));

		/*
		 * Read the value expression. To provide the user with meaningful
		 * parse error positions, we check the syntax immediately, instead of
		 * checking the final expression that may have the arguments
		 * reordered. Trailing whitespace must not be trimmed, because
		 * otherwise input of the form (param -- comment\n, param) would be
		 * translated into a form where the second parameter is commented
		 * out.
		 */
		item = read_sql_construct(',', ')', 0,
								  ",\" or \")",
								  sqlstart,
								  true, true,
								  false, /* do not trim */
								  NULL, &endtoken);

		argv[argpos] = item->query + strlen(sqlstart);

		if (endtoken == ')' && !(argc == row->nfields - 1))
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("not enough arguments for cursor \"%s\"",
							cursor->refname),
					 parser_errposition(yylloc)));

		if (endtoken == ',' && (argc == row->nfields - 1))
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("too many arguments for cursor \"%s\"",
							cursor->refname),
					 parser_errposition(yylloc)));
	}

	/* Make positional argument list */
	initStringInfo(&ds);
	appendStringInfoString(&ds, sqlstart);
	for (argc = 0; argc < row->nfields; argc++)
	{
		Assert(argv[argc] != NULL);

		/*
		 * Because named notation allows permutated argument lists, include
		 * the parameter name for meaningful runtime errors.
		 */
		appendStringInfoString(&ds, argv[argc]);
		if (any_named)
			appendStringInfo(&ds, " AS %s",
							 quote_identifier(row->fieldnames[argc]));
		if (argc < row->nfields - 1)
			appendStringInfoString(&ds, ", ");
	}
	appendStringInfoChar(&ds, ';');

	expr = palloc0(sizeof(PLpgSQL_expr));
	expr->query			= pstrdup(ds.data);
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->rwparam		= -1;
	expr->ns            = plpgsql_ns_top();
	pfree(ds.data);

	/* Next we'd better find the until token */
	tok = yylex();
	if (tok != until)
		yyerror("syntax error");

	return expr;
}

/*
 * Parse RAISE ... USING options
 */
static List *
read_raise_options(void)
{
	List	   *result = NIL;

	for (;;)
	{
		PLpgSQL_raise_option *opt;
		int		tok;

		if ((tok = yylex()) == 0)
			yyerror("unexpected end of function definition");

		opt = (PLpgSQL_raise_option *) palloc(sizeof(PLpgSQL_raise_option));

		if (tok_is_keyword(tok, &yylval,
						   K_ERRCODE, "errcode"))
			opt->opt_type = PLPGSQL_RAISEOPTION_ERRCODE;
		else if (tok_is_keyword(tok, &yylval,
								K_MESSAGE, "message"))
			opt->opt_type = PLPGSQL_RAISEOPTION_MESSAGE;
		else if (tok_is_keyword(tok, &yylval,
								K_DETAIL, "detail"))
			opt->opt_type = PLPGSQL_RAISEOPTION_DETAIL;
		else if (tok_is_keyword(tok, &yylval,
								K_HINT, "hint"))
			opt->opt_type = PLPGSQL_RAISEOPTION_HINT;
		else if (tok_is_keyword(tok, &yylval,
								K_COLUMN, "column"))
			opt->opt_type = PLPGSQL_RAISEOPTION_COLUMN;
		else if (tok_is_keyword(tok, &yylval,
								K_CONSTRAINT, "constraint"))
			opt->opt_type = PLPGSQL_RAISEOPTION_CONSTRAINT;
		else if (tok_is_keyword(tok, &yylval,
								K_DATATYPE, "datatype"))
			opt->opt_type = PLPGSQL_RAISEOPTION_DATATYPE;
		else if (tok_is_keyword(tok, &yylval,
								K_TABLE, "table"))
			opt->opt_type = PLPGSQL_RAISEOPTION_TABLE;
		else if (tok_is_keyword(tok, &yylval,
								K_SCHEMA, "schema"))
			opt->opt_type = PLPGSQL_RAISEOPTION_SCHEMA;
		else
			yyerror("unrecognized RAISE statement option");

		tok = yylex();
		if (tok != '=' && tok != COLON_EQUALS)
			yyerror("syntax error, expected \"=\"");

		opt->expr = read_sql_expression2(',', ';', ", or ;", &tok);

		result = lappend(result, opt);

		if (tok == ';')
			break;
	}

	return result;
}

/*
 * Check that the number of parameter placeholders in the message matches the
 * number of parameters passed to it, if a message was given.
 */
static void
check_raise_parameters(PLpgSQL_stmt_raise *stmt)
{
	char	   *cp;
	int			expected_nparams = 0;

	if (stmt->message == NULL)
		return;

	for (cp = stmt->message; *cp; cp++)
	{
		if (cp[0] == '%')
		{
			/* ignore literal % characters */
			if (cp[1] == '%')
				cp++;
			else
				expected_nparams++;
		}
	}

	if (expected_nparams < list_length(stmt->params))
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				errmsg("too many parameters specified for RAISE")));
	if (expected_nparams > list_length(stmt->params))
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				errmsg("too few parameters specified for RAISE")));
}

/*
 * Fix up CASE statement
 */
static PLpgSQL_stmt *
make_case(int location, PLpgSQL_expr *t_expr,
		  List *case_when_list, List *else_stmts)
{
	PLpgSQL_stmt_case	*new;

	new = palloc(sizeof(PLpgSQL_stmt_case));
	new->cmd_type = PLPGSQL_STMT_CASE;
	new->lineno = plpgsql_location_to_lineno(location);
	new->stmtid = ++plpgsql_curr_compile->nstatements;
	new->t_expr = t_expr;
	new->t_varno = 0;
	new->case_when_list = case_when_list;
	new->have_else = (else_stmts != NIL);
	/* Get rid of list-with-NULL hack */
	if (list_length(else_stmts) == 1 && linitial(else_stmts) == NULL)
		new->else_stmts = NIL;
	else
		new->else_stmts = else_stmts;

	/*
	 * When test expression is present, we create a var for it and then
	 * convert all the WHEN expressions to "VAR IN (original_expression)".
	 * This is a bit klugy, but okay since we haven't yet done more than
	 * read the expressions as text.  (Note that previous parsing won't
	 * have complained if the WHEN ... THEN expression contained multiple
	 * comma-separated values.)
	 */
	if (t_expr)
	{
		char	varname[32];
		PLpgSQL_var *t_var;
		ListCell *l;

		/* use a name unlikely to collide with any user names */
		snprintf(varname, sizeof(varname), "__Case__Variable_%d__",
				 plpgsql_nDatums);

		/*
		 * We don't yet know the result datatype of t_expr.  Build the
		 * variable as if it were INT4; we'll fix this at runtime if needed.
		 */
		t_var = (PLpgSQL_var *)
			plpgsql_build_variable(varname, new->lineno,
								   plpgsql_build_datatype(INT4OID,
														  -1,
														  InvalidOid,
														  NULL),
								   true);
		new->t_varno = t_var->dno;

		foreach(l, case_when_list)
		{
			PLpgSQL_case_when *cwt = (PLpgSQL_case_when *) lfirst(l);
			PLpgSQL_expr *expr = cwt->expr;
			StringInfoData	ds;

			/* copy expression query without SELECT keyword (expr->query + 7) */
			Assert(strncmp(expr->query, "SELECT ", 7) == 0);

			/* And do the string hacking */
			initStringInfo(&ds);

			appendStringInfo(&ds, "SELECT \"%s\" IN (%s)",
							 varname, expr->query + 7);

			pfree(expr->query);
			expr->query = pstrdup(ds.data);
			/* Adjust expr's namespace to include the case variable */
			expr->ns = plpgsql_ns_top();

			pfree(ds.data);
		}
	}

	return (PLpgSQL_stmt *) new;
}
