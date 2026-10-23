/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc.y"

void yyerror (char *s);
int yylex(void);
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
extern int yylineno;
/* Simplified symbol table (variable-only) is implemented below */
/* Simplified symbol table: only variables (identifiers) stored */
typedef enum {T_UNKNOWN, T_INT, T_FLOAT, T_BOOL} TypeKind;
typedef struct VarSym {
  char *name;
  double value;
  TypeKind type;
  int is_const; /* 1 if constant */
  int has_value; /* 1 if initialized */
  struct VarSym *next;
} VarSym;

static VarSym *varsym_head = NULL;

void symtab_init(void) { varsym_head = NULL; }

static VarSym *varsym_lookup(const char *name) {
  VarSym *p = varsym_head;
  while (p) {
    if (strcmp(p->name, name) == 0) return p;
    p = p->next;
  }
  return NULL;
}

/* insert variable; return 1 if inserted, 0 if already exists */
int symtab_insert_var(const char *name, TypeKind type, int is_const, double value, int has_value) {
  if (varsym_lookup(name)) return 0;
  VarSym *s = (VarSym*)malloc(sizeof(VarSym));
  s->name = strdup(name);
  s->type = type;
  s->is_const = is_const;
  s->value = value;
  s->has_value = has_value;
  s->next = varsym_head;
  varsym_head = s;
  return 1;
}

/* set variable value; returns 1 on success, 0 on failure (const or missing) */
int symtab_set_value(const char *name, double value) {
  VarSym *s = varsym_lookup(name);
  if (!s) return 0;
  if (s->is_const) return 0;
  s->value = value;
  s->has_value = 1;
  return 1;
}

/* set variable as constant (called for CONST declarations) */
void symtab_mark_const(const char *name, double value) {
  VarSym *s = varsym_lookup(name);
  if (s) { s->is_const = 1; s->value = value; s->has_value = 1; }
}

void symtab_print(void) {
  VarSym *p;
  /* count entries */
  int total = 0;
  for (p = varsym_head; p; p = p->next) total++;
  if (total == 0) return;
  printf("\nSymbols table:\n\n");

  printf("%-4s %-20s %-10s %-10s %s\t\tEntity\n", "#","Name","Value","Type","Const");
  printf("%s\n","-----------------------------------------------------------------------");
  int idx = 1;
  for (p = varsym_head; p; p = p->next) {
    const char *t = "-";
    char value_str[64];
    if (p->type == T_INT) t = "int";
    else if (p->type == T_FLOAT) t = "float";
    else if (p->type == T_BOOL) t = "bool";

    if (!p->has_value) {
      snprintf(value_str, sizeof(value_str), "NaN");
    } else if (p->type == T_FLOAT) {
      snprintf(value_str, sizeof(value_str), "%.2f", p->value);
    } else if (p->type == T_INT) {
      snprintf(value_str, sizeof(value_str), "%.0f", p->value);
    } else if (p->type == T_BOOL) {
      snprintf(value_str, sizeof(value_str), "%s", (p->value != 0.0) ? "true" : "false");
    } else {
      snprintf(value_str, sizeof(value_str), "%-g", p->value);
    }

    printf("%-4d %-20s %-10s %-10s %s \t\t\tidentifier\n", idx, p->name, value_str, t, p->is_const ? "yes" : "no");
    idx++;
  }
}
/* current declaration type used by VarDecl actions */
static TypeKind current_decl_type = T_UNKNOWN;
/* whether current declaration is CONST */
static int current_decl_is_const = 0;

#line 174 "yacc.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

#include "yacc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_identifier = 3,                 /* identifier  */
  YYSYMBOL_int_number = 4,                 /* int_number  */
  YYSYMBOL_float_number = 5,               /* float_number  */
  YYSYMBOL_bool_literal = 6,               /* bool_literal  */
  YYSYMBOL_begin = 7,                      /* begin  */
  YYSYMBOL_end = 8,                        /* end  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_CONST = 11,                     /* CONST  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_FLOAT = 13,                     /* FLOAT  */
  YYSYMBOL_BOOL = 14,                      /* BOOL  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_EQ = 16,                        /* EQ  */
  YYSYMBOL_NE = 17,                        /* NE  */
  YYSYMBOL_LE = 18,                        /* LE  */
  YYSYMBOL_GE = 19,                        /* GE  */
  YYSYMBOL_LT = 20,                        /* LT  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_SEMI = 23,                      /* SEMI  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_LP = 25,                        /* LP  */
  YYSYMBOL_RP = 26,                        /* RP  */
  YYSYMBOL_LBRACE = 27,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 28,                    /* RBRACE  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_MINUS = 30,                     /* MINUS  */
  YYSYMBOL_MUL = 31,                       /* MUL  */
  YYSYMBOL_DIV = 32,                       /* DIV  */
  YYSYMBOL_LOWER_THAN_ELSE = 33,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_code = 35,                      /* code  */
  YYSYMBOL_Declaration = 36,               /* Declaration  */
  YYSYMBOL_DeclarationStatement = 37,      /* DeclarationStatement  */
  YYSYMBOL_38_1 = 38,                      /* $@1  */
  YYSYMBOL_39_2 = 39,                      /* $@2  */
  YYSYMBOL_Type = 40,                      /* Type  */
  YYSYMBOL_VarDecl = 41,                   /* VarDecl  */
  YYSYMBOL_VarList = 42,                   /* VarList  */
  YYSYMBOL_Program = 43,                   /* Program  */
  YYSYMBOL_Statement = 44,                 /* Statement  */
  YYSYMBOL_CompoundStatement = 45,         /* CompoundStatement  */
  YYSYMBOL_Affectation = 46,               /* Affectation  */
  YYSYMBOL_Expression = 47,                /* Expression  */
  YYSYMBOL_MatchedStatement = 48,          /* MatchedStatement  */
  YYSYMBOL_UnmatchedStatement = 49,        /* UnmatchedStatement  */
  YYSYMBOL_Condition = 50,                 /* Condition  */
  YYSYMBOL_RelOp = 51,                     /* RelOp  */
  YYSYMBOL_ForStatement = 52               /* ForStatement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   118

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  45
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  90

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   140,   142,   147,   147,   148,   148,   152,
     153,   154,   160,   161,   180,   181,   187,   189,   193,   194,
     198,   202,   225,   226,   227,   228,   229,   232,   233,   234,
     235,   240,   241,   242,   243,   244,   248,   249,   253,   257,
     257,   257,   257,   257,   257,   262
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "identifier",
  "int_number", "float_number", "bool_literal", "begin", "end", "IF",
  "FOR", "CONST", "INT", "FLOAT", "BOOL", "ELSE", "EQ", "NE", "LE", "GE",
  "LT", "GT", "ASSIGN", "SEMI", "COMMA", "LP", "RP", "LBRACE", "RBRACE",
  "PLUS", "MINUS", "MUL", "DIV", "LOWER_THAN_ELSE", "$accept", "code",
  "Declaration", "DeclarationStatement", "$@1", "$@2", "Type", "VarDecl",
  "VarList", "Program", "Statement", "CompoundStatement", "Affectation",
  "Expression", "MatchedStatement", "UnmatchedStatement", "Condition",
  "RelOp", "ForStatement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-71)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -71,    12,    71,   -71,   -71,    34,   -71,   -71,   -71,   -71,
     -71,    27,   -71,    13,     7,   -71,   -71,   -71,   -71,     9,
      17,    52,   -71,   -71,   -71,    30,   -12,   -71,   -71,   -71,
      13,    28,   -71,   -16,    52,    52,    56,   -71,    70,     0,
     -71,   -71,    52,    52,    52,    52,    88,    52,   -71,    13,
      78,    74,    47,     7,    38,   -71,   -71,    44,    44,   -71,
     -71,   -71,    78,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
      52,    35,    52,    78,   -71,    55,    57,    35,    56,   -71,
     -71,    60,    62,    63,   -71,    52,    72,    62,    82,    62
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,    16,     0,     9,    10,    11,     4,
       5,     0,     7,     0,    25,    22,    23,    24,     2,     0,
       0,     0,    16,    17,    33,     0,     0,    18,    19,    32,
       0,    12,    14,     0,     0,     0,     0,    25,     0,     0,
      34,    35,     0,     0,     0,     0,     0,     0,     6,     0,
      21,     0,     0,     0,     0,    30,    20,    26,    27,    28,
      29,     8,    13,    15,    41,    42,    43,    44,    39,    40,
       0,     0,     0,    38,    36,    18,     0,     0,     0,    31,
      37,     0,     0,     0,    45,     0,     0,     0,     0,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -71,   -71,   -71,   -71,   -71,   -71,   108,    65,    85,    94,
      46,   -71,   -35,   -21,    -8,    41,   -70,   -71,   -71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     9,    13,    30,    10,    32,    33,    11,
      23,    24,    25,    26,    27,    28,    52,    70,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      38,    54,    76,    14,    15,    16,    17,    48,    49,    19,
      20,    41,     3,    50,    51,    86,    31,    42,    43,    44,
      45,    57,    58,    59,    60,    21,    62,    22,    56,    34,
      14,    15,    16,    17,    35,    18,    19,    20,    14,    15,
      16,    17,    36,    81,    19,    20,     6,     7,     8,    73,
      47,    51,    21,    40,    22,    37,    15,    16,    17,    53,
      21,    72,    22,    75,    51,    14,    15,    16,    17,    79,
      77,    83,    20,    71,    84,    44,    45,    21,     4,    88,
      78,    79,     5,     6,     7,     8,    82,    21,    85,    22,
      64,    65,    66,    67,    68,    69,    55,    89,    87,    42,
      43,    44,    45,    42,    43,    44,    45,    42,    43,    44,
      45,    61,    49,    12,    63,    46,    39,    74,    80
};

static const yytype_int8 yycheck[] =
{
      21,    36,    72,     3,     4,     5,     6,    23,    24,     9,
      10,    23,     0,    34,    35,    85,     3,    29,    30,    31,
      32,    42,    43,    44,    45,    25,    47,    27,    28,    22,
       3,     4,     5,     6,    25,     8,     9,    10,     3,     4,
       5,     6,    25,    78,     9,    10,    12,    13,    14,    70,
      22,    72,    25,    23,    27,     3,     4,     5,     6,     3,
      25,    23,    27,    71,    85,     3,     4,     5,     6,    77,
      15,     9,    10,    26,    82,    31,    32,    25,     7,    87,
      23,    89,    11,    12,    13,    14,    26,    25,    25,    27,
      16,    17,    18,    19,    20,    21,    26,    15,    26,    29,
      30,    31,    32,    29,    30,    31,    32,    29,    30,    31,
      32,    23,    24,     5,    49,    30,    22,    71,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    35,    36,     0,     7,    11,    12,    13,    14,    37,
      40,    43,    40,    38,     3,     4,     5,     6,     8,     9,
      10,    25,    27,    44,    45,    46,    47,    48,    49,    52,
      39,     3,    41,    42,    22,    25,    25,     3,    47,    43,
      23,    23,    29,    30,    31,    32,    42,    22,    23,    24,
      47,    47,    50,     3,    46,    26,    28,    47,    47,    47,
      47,    23,    47,    41,    16,    17,    18,    19,    20,    21,
      51,    26,    23,    47,    44,    48,    50,    15,    23,    48,
      49,    46,    26,     9,    48,    25,    50,    26,    48,    15
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    38,    37,    39,    37,    40,
      40,    40,    41,    41,    42,    42,    43,    43,    44,    44,
      45,    46,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    48,    48,    48,    48,    48,    49,    49,    50,    51,
      51,    51,    51,    51,    51,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     0,     2,     0,     4,     0,     5,     1,
       1,     1,     1,     3,     1,     3,     0,     2,     1,     1,
       3,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     7,     1,     1,     2,     2,     5,     7,     3,     1,
       1,     1,     1,     1,     1,     9
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* $@1: %empty  */
#line 147 "yacc.y"
           { current_decl_type = (yyvsp[0].itype); current_decl_is_const = 0; }
#line 1269 "yacc.tab.c"
    break;

  case 6: /* DeclarationStatement: Type $@1 VarList SEMI  */
#line 147 "yacc.y"
                                                                               { current_decl_type = T_UNKNOWN; current_decl_is_const = 0; }
#line 1275 "yacc.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 148 "yacc.y"
                 { current_decl_type = (yyvsp[0].itype); current_decl_is_const = 1; }
#line 1281 "yacc.tab.c"
    break;

  case 8: /* DeclarationStatement: CONST Type $@2 VarList SEMI  */
#line 148 "yacc.y"
                                                                                     { current_decl_type = T_UNKNOWN; current_decl_is_const = 0; }
#line 1287 "yacc.tab.c"
    break;

  case 9: /* Type: INT  */
#line 152 "yacc.y"
            { (yyval.itype) = T_INT; }
#line 1293 "yacc.tab.c"
    break;

  case 10: /* Type: FLOAT  */
#line 153 "yacc.y"
            { (yyval.itype) = T_FLOAT; }
#line 1299 "yacc.tab.c"
    break;

  case 11: /* Type: BOOL  */
#line 154 "yacc.y"
            { (yyval.itype) = T_BOOL; }
#line 1305 "yacc.tab.c"
    break;

  case 12: /* VarDecl: identifier  */
#line 160 "yacc.y"
                 { if (!symtab_insert_var((yyvsp[0].id), current_decl_type, current_decl_is_const, 0, 0)) { fprintf(stderr, "line %d: double declaration of '%s'\n", yylineno, (yyvsp[0].id)); } }
#line 1311 "yacc.tab.c"
    break;

  case 13: /* VarDecl: identifier ASSIGN Expression  */
#line 161 "yacc.y"
                                   {
        /* type compatibility for initializer */
        int ok = 1;
        if ((yyvsp[0].expr).etype == T_UNKNOWN) ok = 0;
        if (current_decl_type == T_INT && (yyvsp[0].expr).etype == T_FLOAT) {
          fprintf(stderr, "line %d: cannot initialize int '%s' with float\n", yylineno, (yyvsp[-2].id)); ok = 0;
        }
        if (current_decl_type == T_BOOL && (yyvsp[0].expr).etype != T_BOOL) {
          fprintf(stderr, "line %d: cannot initialize bool '%s' with non-bool\n", yylineno, (yyvsp[-2].id)); ok = 0;
        }
        if (ok) {
          if (!symtab_insert_var((yyvsp[-2].id), current_decl_type, current_decl_is_const, (yyvsp[0].expr).val, 1)) { fprintf(stderr, "line %d: double declaration of '%s'\n", yylineno, (yyvsp[-2].id)); }
        } else {
          if (!symtab_insert_var((yyvsp[-2].id), current_decl_type, current_decl_is_const, 0, 0)) { fprintf(stderr, "line %d: double declaration of '%s'\n", yylineno, (yyvsp[-2].id)); }
        }
      }
#line 1332 "yacc.tab.c"
    break;

  case 21: /* Affectation: identifier ASSIGN Expression  */
#line 202 "yacc.y"
                                   { 
        VarSym *s = varsym_lookup((yyvsp[-2].id));
        if (!s) {
          fprintf(stderr, "line %d: undeclared variable '%s'\n", yylineno, (yyvsp[-2].id));
        } else if (s->is_const) {
          fprintf(stderr, "line %d: cannot assign to constant '%s'\n", yylineno, (yyvsp[-2].id));
        } else {
          /* type compatibility checks */
          if (s->type == T_INT && (yyvsp[0].expr).etype == T_FLOAT) {
            fprintf(stderr, "line %d: cannot assign float to int variable '%s'\n", yylineno, (yyvsp[-2].id));
          } else if (s->type == T_BOOL && (yyvsp[0].expr).etype != T_BOOL) {
            fprintf(stderr, "line %d: cannot assign non-bool to bool variable '%s'\n", yylineno, (yyvsp[-2].id));
          } else {
            /* allow int->float (promotion) */
            s->value = (yyvsp[0].expr).val;
            s->has_value = 1;
          }
        }
      }
#line 1356 "yacc.tab.c"
    break;

  case 22: /* Expression: int_number  */
#line 225 "yacc.y"
                { ExprVal e; e.val = (yyvsp[0].num); e.etype = T_INT; (yyval.expr) = e; }
#line 1362 "yacc.tab.c"
    break;

  case 23: /* Expression: float_number  */
#line 226 "yacc.y"
                  { ExprVal e; e.val = (yyvsp[0].num); e.etype = T_FLOAT; (yyval.expr) = e; }
#line 1368 "yacc.tab.c"
    break;

  case 24: /* Expression: bool_literal  */
#line 227 "yacc.y"
                  { ExprVal e; e.val = (yyvsp[0].num); e.etype = T_BOOL; (yyval.expr) = e; }
#line 1374 "yacc.tab.c"
    break;

  case 25: /* Expression: identifier  */
#line 228 "yacc.y"
                  { VarSym *s = varsym_lookup((yyvsp[0].id)); ExprVal e; if (!s) { fprintf(stderr, "line %d: undeclared variable '%s'\n", yylineno, (yyvsp[0].id)); e.val = 0; e.etype = T_UNKNOWN; } else { if (!s->has_value) { fprintf(stderr, "line %d: variable '%s' used before initialization\n", yylineno, (yyvsp[0].id)); } e.val = s->value; e.etype = s->type; } (yyval.expr) = e; }
#line 1380 "yacc.tab.c"
    break;

  case 26: /* Expression: Expression PLUS Expression  */
#line 229 "yacc.y"
                                {
      ExprVal e; if ((yyvsp[-2].expr).etype==T_BOOL || (yyvsp[0].expr).etype==T_BOOL) { fprintf(stderr, "line %d: type error in '+' with bool\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; }
        else { e.val = (yyvsp[-2].expr).val + (yyvsp[0].expr).val; e.etype = ((yyvsp[-2].expr).etype==T_FLOAT || (yyvsp[0].expr).etype==T_FLOAT) ? T_FLOAT : T_INT; } (yyval.expr) = e; }
#line 1388 "yacc.tab.c"
    break;

  case 27: /* Expression: Expression MINUS Expression  */
#line 232 "yacc.y"
                                { ExprVal e; if ((yyvsp[-2].expr).etype==T_BOOL || (yyvsp[0].expr).etype==T_BOOL) { fprintf(stderr, "line %d: type error in '-' with bool\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; } else { e.val = (yyvsp[-2].expr).val - (yyvsp[0].expr).val; e.etype = ((yyvsp[-2].expr).etype==T_FLOAT || (yyvsp[0].expr).etype==T_FLOAT) ? T_FLOAT : T_INT; } (yyval.expr) = e; }
#line 1394 "yacc.tab.c"
    break;

  case 28: /* Expression: Expression MUL Expression  */
#line 233 "yacc.y"
                                { ExprVal e; if ((yyvsp[-2].expr).etype==T_BOOL || (yyvsp[0].expr).etype==T_BOOL) { fprintf(stderr, "line %d: type error in '*' with bool\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; } else { e.val = (yyvsp[-2].expr).val * (yyvsp[0].expr).val; e.etype = ((yyvsp[-2].expr).etype==T_FLOAT || (yyvsp[0].expr).etype==T_FLOAT) ? T_FLOAT : T_INT; } (yyval.expr) = e; }
#line 1400 "yacc.tab.c"
    break;

  case 29: /* Expression: Expression DIV Expression  */
#line 234 "yacc.y"
                                { ExprVal e; if ((yyvsp[-2].expr).etype==T_BOOL || (yyvsp[0].expr).etype==T_BOOL) { fprintf(stderr, "line %d: type error in '/' with bool\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; } else if ((yyvsp[0].expr).val == 0) { fprintf(stderr, "line %d: division by zero\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; } else { e.val = (yyvsp[-2].expr).val / (yyvsp[0].expr).val; e.etype = T_FLOAT; } (yyval.expr) = e; }
#line 1406 "yacc.tab.c"
    break;

  case 30: /* Expression: LP Expression RP  */
#line 235 "yacc.y"
                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 1412 "yacc.tab.c"
    break;


#line 1416 "yacc.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 269 "yacc.y"


int main(void){
  symtab_init();
  int r = yyparse ();
  symtab_print();
  return r;
}
void yyerror (char *s) { fprintf(stderr, "line %d: %s\n", yylineno, s); }

