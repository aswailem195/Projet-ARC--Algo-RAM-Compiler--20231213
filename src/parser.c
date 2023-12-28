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
#line 1 "src/parser.y"

  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
  
  #include "../include/asa.h"
  #include "../include/ts.h"
  #include "semantic.h"
  #include "codegen.h"
  
  
  extern int yylex();
  static void print_file_error(char * s, char *errmsg);

  table_symb TABLE_SYMBOLES = NULL;
  struct asa * ARBRE_ABSTRAIT = NULL;
  char CTXTglo[32] = "GLOBAL";



  void yyerror(const char * s);

  char srcname[64];
  char exename[64] = "a.out";
  FILE * exefile;

#line 98 "src/parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NB = 3,                         /* NB  */
  YYSYMBOL_VRAI = 4,                       /* VRAI  */
  YYSYMBOL_FAUX = 5,                       /* FAUX  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_PROGRAMME = 7,                  /* PROGRAMME  */
  YYSYMBOL_DEBUT = 8,                      /* DEBUT  */
  YYSYMBOL_FIN = 9,                        /* FIN  */
  YYSYMBOL_VAR = 10,                       /* VAR  */
  YYSYMBOL_ECRIRE = 11,                    /* ECRIRE  */
  YYSYMBOL_LIRE = 12,                      /* LIRE  */
  YYSYMBOL_NON = 13,                       /* NON  */
  YYSYMBOL_TQ = 14,                        /* TQ  */
  YYSYMBOL_FAIRE = 15,                     /* FAIRE  */
  YYSYMBOL_FTQ = 16,                       /* FTQ  */
  YYSYMBOL_SI = 17,                        /* SI  */
  YYSYMBOL_ALORS = 18,                     /* ALORS  */
  YYSYMBOL_SINON = 19,                     /* SINON  */
  YYSYMBOL_FSI = 20,                       /* FSI  */
  YYSYMBOL_RENVOYER = 21,                  /* RENVOYER  */
  YYSYMBOL_ALGO = 22,                      /* ALGO  */
  YYSYMBOL_ALLOUER = 23,                   /* ALLOUER  */
  YYSYMBOL_AFF = 24,                       /* AFF  */
  YYSYMBOL_OU = 25,                        /* OU  */
  YYSYMBOL_ET = 26,                        /* ET  */
  YYSYMBOL_27_ = 27,                       /* '<'  */
  YYSYMBOL_28_ = 28,                       /* '>'  */
  YYSYMBOL_EGAL = 29,                      /* EGAL  */
  YYSYMBOL_SUPEGAL = 30,                   /* SUPEGAL  */
  YYSYMBOL_INFEGAL = 31,                   /* INFEGAL  */
  YYSYMBOL_DIFF = 32,                      /* DIFF  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '%'  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ','  */
  YYSYMBOL_40_ = 40,                       /* ')'  */
  YYSYMBOL_41_ = 41,                       /* '['  */
  YYSYMBOL_42_ = 42,                       /* ']'  */
  YYSYMBOL_43_ = 43,                       /* '@'  */
  YYSYMBOL_44_n_ = 44,                     /* '\n'  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_PROGRAMME_ALGO = 46,            /* PROGRAMME_ALGO  */
  YYSYMBOL_ALLOCATION = 47,                /* ALLOCATION  */
  YYSYMBOL_INDICX_RECU = 48,               /* INDICX_RECU  */
  YYSYMBOL_INDICX_SORT = 49,               /* INDICX_SORT  */
  YYSYMBOL_LIS_DEC_FON = 50,               /* LIS_DEC_FON  */
  YYSYMBOL_DEC_FON = 51,                   /* DEC_FON  */
  YYSYMBOL_PARAM_F = 52,                   /* PARAM_F  */
  YYSYMBOL_PARAM = 53,                     /* PARAM  */
  YYSYMBOL_LIST_VAR = 54,                  /* LIST_VAR  */
  YYSYMBOL_INT = 55,                       /* INT  */
  YYSYMBOL_PON = 56,                       /* PON  */
  YYSYMBOL_PROG = 57,                      /* PROG  */
  YYSYMBOL_SEP = 58,                       /* SEP  */
  YYSYMBOL_INST_RENVOYER = 59,             /* INST_RENVOYER  */
  YYSYMBOL_STRUCT_TQ = 60,                 /* STRUCT_TQ  */
  YYSYMBOL_STRUCT_SI = 61,                 /* STRUCT_SI  */
  YYSYMBOL_INST_LIRE = 62,                 /* INST_LIRE  */
  YYSYMBOL_INST_ECRIRE = 63,               /* INST_ECRIRE  */
  YYSYMBOL_DECS = 64,                      /* DECS  */
  YYSYMBOL_LIST_DECLA = 65,                /* LIST_DECLA  */
  YYSYMBOL_DECLA_VAR = 66,                 /* DECLA_VAR  */
  YYSYMBOL_DECLA_TAB = 67,                 /* DECLA_TAB  */
  YYSYMBOL_DECLA_POIN = 68,                /* DECLA_POIN  */
  YYSYMBOL_LIST_INST = 69,                 /* LIST_INST  */
  YYSYMBOL_INST = 70,                      /* INST  */
  YYSYMBOL_AFFECT = 71,                    /* AFFECT  */
  YYSYMBOL_APPFONC = 72,                   /* APPFONC  */
  YYSYMBOL_EXP = 73                        /* EXP  */
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
typedef yytype_uint8 yy_state_t;

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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   323

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


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
      44,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    37,     2,     2,
      38,    40,    35,    33,    39,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,     2,    28,     2,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
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
      25,    26,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    78,    83,    84,    88,    93,    94,    95,
      98,   108,   109,   114,   115,   117,   118,   119,   120,   124,
     126,   135,   141,   141,   146,   150,   154,   159,   165,   169,
     174,   175,   176,   179,   180,   181,   182,   183,   184,   189,
     190,   192,   194,   199,   200,   201,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   218,   219,   223,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     245,   247,   249,   251,   253,   255,   257,   259,   261,   263
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NB", "VRAI", "FAUX",
  "ID", "PROGRAMME", "DEBUT", "FIN", "VAR", "ECRIRE", "LIRE", "NON", "TQ",
  "FAIRE", "FTQ", "SI", "ALORS", "SINON", "FSI", "RENVOYER", "ALGO",
  "ALLOUER", "AFF", "OU", "ET", "'<'", "'>'", "EGAL", "SUPEGAL", "INFEGAL",
  "DIFF", "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "','", "')'", "'['",
  "']'", "'@'", "'\\n'", "$accept", "PROGRAMME_ALGO", "ALLOCATION",
  "INDICX_RECU", "INDICX_SORT", "LIS_DEC_FON", "DEC_FON", "PARAM_F",
  "PARAM", "LIST_VAR", "INT", "PON", "PROG", "SEP", "INST_RENVOYER",
  "STRUCT_TQ", "STRUCT_SI", "INST_LIRE", "INST_ECRIRE", "DECS",
  "LIST_DECLA", "DECLA_VAR", "DECLA_TAB", "DECLA_POIN", "LIST_INST",
  "INST", "AFFECT", "APPFONC", "EXP", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-104)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -7,     6,     5,    -5,   -14,    20,   -33,    -4,    24,    26,
    -104,    22,    62,   -33,   104,    67,  -104,  -104,    15,     6,
       6,     6,    33,    40,  -104,   -15,  -104,  -104,  -104,    31,
     104,   104,   104,  -104,   263,    41,  -104,  -104,  -104,  -104,
    -104,     6,    52,  -104,   104,   286,   -21,   215,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,  -104,    54,  -104,   -33,   179,  -104,   275,   286,    53,
      53,    53,    53,    53,    53,   -21,   -21,  -104,  -104,  -104,
     -33,    15,  -104,    15,    76,    85,   -33,   -33,   110,   110,
      38,    57,   104,   104,   104,    58,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,    89,   -33,  -104,  -104,   263,    92,    18,
       7,   104,   104,   166,   142,   263,    96,   -33,   110,  -104,
      44,    65,  -104,   263,  -104,    99,    66,  -104,    72,    73,
     197,   231,   -33,   -33,    79,    78,  -104,   146,    86,  -104,
    -104,     7,     7,   105,  -104,   110,   110,   104,  -104,  -104,
    -104,   152,   112,   -11,   247,    91,  -104,   263,  -104,   -33,
    -104,  -104,   110,   114,  -104
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      32,     0,     0,     9,    39,     0,     0,    33,    34,    35,
       1,     0,     0,     0,     0,     0,    42,    22,    30,     0,
       0,     0,     0,     0,     2,     8,    61,    62,    63,    64,
       0,     0,     0,    60,    40,     0,    23,    31,    36,    37,
      38,    12,     0,     7,     0,    78,    79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,    11,     0,     0,    59,    76,    77,    70,
      71,    75,    74,    73,    72,    65,    66,    67,    68,    69,
       0,    32,     6,    32,     0,     0,     0,     0,    45,    45,
      64,     0,     0,     0,     0,     0,    53,    55,    52,    50,
      51,    49,    48,     0,     0,    46,    54,    47,     0,     0,
      14,     0,     0,     0,     0,    24,     0,     0,    43,    10,
      64,     0,    57,    56,    19,     0,     0,    13,    17,    18,
       0,     0,     0,     0,     0,    21,    44,     0,     0,    20,
      58,     0,     0,     6,    29,    45,    45,     0,    28,    15,
      16,     0,     0,     0,     0,    64,     4,     5,    25,     0,
      27,     3,    45,     0,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,  -104,   -10,  -104,   111,  -104,  -104,  -104,   -84,
    -104,  -104,  -104,   -13,  -104,  -104,  -104,  -104,  -104,   -17,
      34,  -104,  -104,  -104,   -85,  -104,  -103,  -104,   -12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    96,    97,    33,    12,    13,    62,   126,   127,
     128,   129,    24,    18,    98,    99,   100,   101,   102,     3,
       6,     7,     8,     9,   103,   104,   105,   106,   107
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      25,    37,    34,     1,   108,    10,   122,    11,   159,   160,
      14,    17,     4,   124,    58,    59,    60,    11,    45,    46,
      47,    26,    27,    28,   120,     1,    16,    15,    22,    36,
     121,    30,    65,   136,   122,    19,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,     5,
     125,    81,    31,    38,    39,    40,    32,   149,   150,    36,
     152,   153,   109,    20,    84,    21,    85,    83,   137,    23,
      35,    41,    44,    88,    89,    63,   110,   163,    42,   111,
     113,   114,   115,    61,    86,    44,    56,    57,    58,    59,
      60,   118,    64,    87,    80,   112,   116,   123,   117,   130,
     131,   119,   134,   138,   135,   139,   140,    26,    27,    28,
      29,   141,   142,    26,    27,    28,    90,    30,   147,   145,
     146,    91,    36,    30,    92,   123,   148,    93,   158,   151,
       0,    94,   111,    95,   164,   154,    43,     0,    31,   157,
       0,   156,    32,     0,    31,     0,   162,     0,    32,    26,
      27,    28,   120,     0,    36,    26,    27,    28,   155,    30,
     133,     0,     0,     0,     0,    30,     0,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      31,   132,     0,     0,    32,     0,    31,     0,     0,     0,
      32,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     0,     0,     0,
       0,    82,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,     0,     0,     0,     0,   143,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,     0,    66,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     0,
       0,   144,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,     0,     0,   161,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60
};

static const yytype_int16 yycheck[] =
{
      13,    18,    14,    10,    89,     0,   109,    22,    19,    20,
      24,    44,     6,     6,    35,    36,    37,    22,    30,    31,
      32,     3,     4,     5,     6,    10,     6,    41,     6,    44,
      12,    13,    44,   118,   137,    39,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    43,
      43,    64,    34,    19,    20,    21,    38,   141,   142,    44,
     145,   146,    24,    39,    81,    39,    83,    80,    24,     7,
       3,    38,    41,    86,    87,    41,    38,   162,    38,    41,
      92,    93,    94,    42,     8,    41,    33,    34,    35,    36,
      37,   104,    40,     8,    40,    38,    38,   109,     9,   111,
     112,     9,     6,    38,   117,     6,    40,     3,     4,     5,
       6,    39,    39,     3,     4,     5,     6,    13,    39,   132,
     133,    11,    44,    13,    14,   137,    40,    17,    16,    24,
      -1,    21,    41,    23,    20,   147,    25,    -1,    34,   151,
      -1,   151,    38,    -1,    34,    -1,   159,    -1,    38,     3,
       4,     5,     6,    -1,    44,     3,     4,     5,     6,    13,
      18,    -1,    -1,    -1,    -1,    13,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      34,    15,    -1,    -1,    38,    -1,    34,    -1,    -1,    -1,
      38,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    42,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    40,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    40,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    40,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    46,    64,     6,    43,    65,    66,    67,    68,
       0,    22,    50,    51,    24,    41,     6,    44,    58,    39,
      39,    39,     6,     7,    57,    58,     3,     4,     5,     6,
      13,    34,    38,    49,    73,     3,    44,    64,    65,    65,
      65,    38,    38,    50,    41,    73,    73,    73,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    42,    52,    65,    40,    73,    40,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      40,    58,    42,    58,    64,    64,     8,     8,    58,    58,
       6,    11,    14,    17,    21,    23,    47,    48,    59,    60,
      61,    62,    63,    69,    70,    71,    72,    73,    69,    24,
      38,    41,    38,    73,    73,    73,    38,     9,    58,     9,
       6,    12,    71,    73,     6,    43,    53,    54,    55,    56,
      73,    73,    15,    18,     6,    58,    69,    24,    38,     6,
      40,    39,    39,    42,    40,    58,    58,    39,    40,    54,
      54,    24,    69,    69,    73,     6,    48,    73,    16,    19,
      20,    40,    58,    69,    20
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    48,    48,    49,    50,    50,    50,
      51,    52,    52,    53,    53,    54,    54,    54,    54,    55,
      56,    57,    58,    58,    59,    60,    61,    61,    62,    63,
      64,    64,    64,    65,    65,    65,    65,    65,    65,    66,
      66,    67,    68,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    71,    71,    72,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     6,     6,     6,     4,     3,     2,     0,
      11,     1,     0,     1,     0,     3,     3,     1,     1,     1,
       2,    10,     1,     2,     2,     6,     9,     6,     5,     4,
       3,     4,     0,     1,     1,     1,     3,     3,     3,     1,
       3,     4,     2,     2,     3,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     4,     3,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2
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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* PROGRAMME_ALGO: DECS LIS_DEC_FON PROG  */
#line 73 "src/parser.y"
                        {(yyval.tree) = creer_noeudMAIN( (yyvsp[-2].tree) ,(yyvsp[-1].tree) , (yyvsp[0].tree) ); ARBRE_ABSTRAIT=(yyval.tree); }
#line 1680 "src/parser.c"
    break;

  case 3: /* ALLOCATION: ALLOUER '(' ID ',' EXP ')'  */
#line 78 "src/parser.y"
                                     {(yyval.tree) = creer_noeudALLOCATION((yyvsp[-3].id) ,(yyvsp[-1].tree) );}
#line 1686 "src/parser.c"
    break;

  case 4: /* INDICX_RECU: ID '[' EXP ']' AFF INDICX_RECU  */
#line 83 "src/parser.y"
                                             {(yyval.tree) = creer_noeudINDICX_RECU((yyvsp[-5].id) ,(yyvsp[-3].tree),(yyvsp[0].tree) );}
#line 1692 "src/parser.c"
    break;

  case 5: /* INDICX_RECU: ID '[' EXP ']' AFF EXP  */
#line 84 "src/parser.y"
                                    {(yyval.tree) = creer_noeudINDICX_RECU((yyvsp[-5].id) ,(yyvsp[-3].tree),(yyvsp[0].tree)  );}
#line 1698 "src/parser.c"
    break;

  case 6: /* INDICX_SORT: ID '[' EXP ']'  */
#line 88 "src/parser.y"
                                 {(yyval.tree) = creer_noeudINDICX_SORT((yyvsp[-3].id) ,(yyvsp[-1].tree) );}
#line 1704 "src/parser.c"
    break;

  case 7: /* LIS_DEC_FON: DEC_FON SEP LIS_DEC_FON  */
#line 93 "src/parser.y"
                                        {(yyval.tree) = creer_noeudLIS_DEC_FON((yyvsp[-2].tree) ,(yyvsp[0].tree) );}
#line 1710 "src/parser.c"
    break;

  case 8: /* LIS_DEC_FON: DEC_FON SEP  */
#line 94 "src/parser.y"
                                        {(yyval.tree) = creer_noeudLIS_DEC_FON((yyvsp[-1].tree) ,NULL );}
#line 1716 "src/parser.c"
    break;

  case 9: /* LIS_DEC_FON: %empty  */
#line 95 "src/parser.y"
          {(yyval.tree) =NULL ;}
#line 1722 "src/parser.c"
    break;

  case 10: /* DEC_FON: ALGO ID '(' PARAM_F ')' SEP DECS DEBUT SEP LIST_INST FIN  */
#line 102 "src/parser.y"
              {(yyval.tree) = creer_noeudDEC_FON((yyvsp[-9].id), (yyvsp[-7].tree), (yyvsp[-4].tree) , (yyvsp[-1].tree) );}
#line 1728 "src/parser.c"
    break;

  case 11: /* PARAM_F: LIST_DECLA  */
#line 108 "src/parser.y"
                          { (yyval.tree) = (yyvsp[0].tree);}
#line 1734 "src/parser.c"
    break;

  case 12: /* PARAM_F: %empty  */
#line 109 "src/parser.y"
                          {(yyval.tree)= NULL ;}
#line 1740 "src/parser.c"
    break;

  case 13: /* PARAM: LIST_VAR  */
#line 114 "src/parser.y"
                     {(yyval.tree) = (yyvsp[0].tree);}
#line 1746 "src/parser.c"
    break;

  case 14: /* PARAM: %empty  */
#line 115 "src/parser.y"
                        {(yyval.tree) = NULL ;}
#line 1752 "src/parser.c"
    break;

  case 15: /* LIST_VAR: INT ',' LIST_VAR  */
#line 117 "src/parser.y"
                            {(yyval.tree) = creer_noeudLIST_VAR( (yyvsp[-2].tree) ,(yyvsp[0].tree) );}
#line 1758 "src/parser.c"
    break;

  case 16: /* LIST_VAR: PON ',' LIST_VAR  */
#line 118 "src/parser.y"
                            {(yyval.tree) = creer_noeudLIST_VAR( (yyvsp[-2].tree) ,(yyvsp[0].tree) );}
#line 1764 "src/parser.c"
    break;

  case 17: /* LIST_VAR: INT  */
#line 119 "src/parser.y"
                                {(yyval.tree) = creer_noeudLIST_VAR( (yyvsp[0].tree) ,NULL );}
#line 1770 "src/parser.c"
    break;

  case 18: /* LIST_VAR: PON  */
#line 120 "src/parser.y"
                             {(yyval.tree) = creer_noeudLIST_VAR( (yyvsp[0].tree) ,NULL );}
#line 1776 "src/parser.c"
    break;

  case 19: /* INT: ID  */
#line 124 "src/parser.y"
                         {(yyval.tree) = creer_noeudINT( (yyvsp[0].id));}
#line 1782 "src/parser.c"
    break;

  case 20: /* PON: '@' ID  */
#line 126 "src/parser.y"
                          {(yyval.tree) = creer_noeudPON( (yyvsp[0].id) );}
#line 1788 "src/parser.c"
    break;

  case 21: /* PROG: PROGRAMME '(' ')' SEP DECS DEBUT SEP LIST_INST FIN SEP  */
#line 139 "src/parser.y"
          {(yyval.tree) = creer_noeudPROG( (yyvsp[-5].tree) ,(yyvsp[-2].tree) );}
#line 1794 "src/parser.c"
    break;

  case 24: /* INST_RENVOYER: RENVOYER EXP  */
#line 146 "src/parser.y"
                             {(yyval.tree) = creer_noeudRENVOYER((yyvsp[0].tree));}
#line 1800 "src/parser.c"
    break;

  case 25: /* STRUCT_TQ: TQ EXP FAIRE SEP LIST_INST FTQ  */
#line 150 "src/parser.y"
                                             {(yyval.tree) = creer_noeudSTRUCT_TQ((yyvsp[-4].tree),(yyvsp[-1].tree));}
#line 1806 "src/parser.c"
    break;

  case 26: /* STRUCT_SI: SI EXP ALORS SEP LIST_INST SINON SEP LIST_INST FSI  */
#line 158 "src/parser.y"
        {(yyval.tree) = creer_noeudSTRUCT_SI((yyvsp[-7].tree), (yyvsp[-4].tree), (yyvsp[-1].tree));}
#line 1812 "src/parser.c"
    break;

  case 27: /* STRUCT_SI: SI EXP ALORS SEP LIST_INST FSI  */
#line 161 "src/parser.y"
       {(yyval.tree) = creer_noeudSTRUCT_SI((yyvsp[-4].tree), (yyvsp[-1].tree), NULL);}
#line 1818 "src/parser.c"
    break;

  case 28: /* INST_LIRE: ID AFF LIRE '(' ')'  */
#line 165 "src/parser.y"
                                {(yyval.tree) = creer_noeudINST_LIRE((yyvsp[-4].id));}
#line 1824 "src/parser.c"
    break;

  case 29: /* INST_ECRIRE: ECRIRE '(' EXP ')'  */
#line 169 "src/parser.y"
                                {(yyval.tree) = creer_noeudINST_ECRIRE((yyvsp[-1].tree));}
#line 1830 "src/parser.c"
    break;

  case 30: /* DECS: VAR LIST_DECLA SEP  */
#line 174 "src/parser.y"
                             {(yyval.tree) = creer_noeudDECS((yyvsp[-1].tree),NULL);}
#line 1836 "src/parser.c"
    break;

  case 31: /* DECS: VAR LIST_DECLA SEP DECS  */
#line 175 "src/parser.y"
                              {(yyval.tree) = creer_noeudDECS((yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1842 "src/parser.c"
    break;

  case 32: /* DECS: %empty  */
#line 176 "src/parser.y"
                               {(yyval.tree)= NULL;}
#line 1848 "src/parser.c"
    break;

  case 33: /* LIST_DECLA: DECLA_VAR  */
#line 179 "src/parser.y"
                           {(yyval.tree) = creer_noeudLIST_DECLA((yyvsp[0].tree),NULL);}
#line 1854 "src/parser.c"
    break;

  case 34: /* LIST_DECLA: DECLA_TAB  */
#line 180 "src/parser.y"
                            {(yyval.tree) = creer_noeudLIST_DECLA((yyvsp[0].tree),NULL);}
#line 1860 "src/parser.c"
    break;

  case 35: /* LIST_DECLA: DECLA_POIN  */
#line 181 "src/parser.y"
                            {(yyval.tree) = creer_noeudLIST_DECLA((yyvsp[0].tree),NULL);}
#line 1866 "src/parser.c"
    break;

  case 36: /* LIST_DECLA: DECLA_VAR ',' LIST_DECLA  */
#line 182 "src/parser.y"
                          {(yyval.tree) = creer_noeudLIST_DECLA((yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1872 "src/parser.c"
    break;

  case 37: /* LIST_DECLA: DECLA_TAB ',' LIST_DECLA  */
#line 183 "src/parser.y"
                            {(yyval.tree) = creer_noeudLIST_DECLA((yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1878 "src/parser.c"
    break;

  case 38: /* LIST_DECLA: DECLA_POIN ',' LIST_DECLA  */
#line 184 "src/parser.y"
                             {(yyval.tree) = creer_noeudLIST_DECLA((yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1884 "src/parser.c"
    break;

  case 39: /* DECLA_VAR: ID  */
#line 189 "src/parser.y"
                 {(yyval.tree) = creer_noeudDECLA_VAR( (yyvsp[0].id)  ,NULL );}
#line 1890 "src/parser.c"
    break;

  case 40: /* DECLA_VAR: ID AFF EXP  */
#line 190 "src/parser.y"
                {(yyval.tree) = creer_noeudDECLA_VAR( (yyvsp[-2].id)  ,(yyvsp[0].tree) );}
#line 1896 "src/parser.c"
    break;

  case 41: /* DECLA_TAB: ID '[' NB ']'  */
#line 192 "src/parser.y"
                           {(yyval.tree) = creer_noeudDECLA_TAB( (yyvsp[-3].id)  ,(yyvsp[-1].nb) );}
#line 1902 "src/parser.c"
    break;

  case 42: /* DECLA_POIN: '@' ID  */
#line 194 "src/parser.y"
                      {(yyval.tree) = creer_noeudDECLA_POIN( (yyvsp[0].id) );}
#line 1908 "src/parser.c"
    break;

  case 43: /* LIST_INST: INST SEP  */
#line 199 "src/parser.y"
                     {(yyval.tree)  = creer_noeudLIST_INST( (yyvsp[-1].tree),NULL );}
#line 1914 "src/parser.c"
    break;

  case 44: /* LIST_INST: INST SEP LIST_INST  */
#line 200 "src/parser.y"
                      {(yyval.tree)  = creer_noeudLIST_INST( (yyvsp[-2].tree),(yyvsp[0].tree) );}
#line 1920 "src/parser.c"
    break;

  case 45: /* LIST_INST: %empty  */
#line 201 "src/parser.y"
                      {(yyval.tree) = NULL; }
#line 1926 "src/parser.c"
    break;

  case 46: /* INST: AFFECT  */
#line 205 "src/parser.y"
               {(yyval.tree)= (yyvsp[0].tree) ;}
#line 1932 "src/parser.c"
    break;

  case 47: /* INST: EXP  */
#line 206 "src/parser.y"
      {(yyval.tree)= (yyvsp[0].tree) ;}
#line 1938 "src/parser.c"
    break;

  case 48: /* INST: INST_ECRIRE  */
#line 207 "src/parser.y"
             {(yyval.tree)= (yyvsp[0].tree) ;}
#line 1944 "src/parser.c"
    break;

  case 49: /* INST: INST_LIRE  */
#line 208 "src/parser.y"
           {(yyval.tree)= (yyvsp[0].tree) ;}
#line 1950 "src/parser.c"
    break;

  case 50: /* INST: STRUCT_TQ  */
#line 209 "src/parser.y"
           {(yyval.tree)= (yyvsp[0].tree) ;}
#line 1956 "src/parser.c"
    break;

  case 51: /* INST: STRUCT_SI  */
#line 210 "src/parser.y"
           {(yyval.tree)= (yyvsp[0].tree) ;}
#line 1962 "src/parser.c"
    break;

  case 52: /* INST: INST_RENVOYER  */
#line 211 "src/parser.y"
                {(yyval.tree)= (yyvsp[0].tree) ;}
#line 1968 "src/parser.c"
    break;

  case 53: /* INST: ALLOCATION  */
#line 212 "src/parser.y"
              {(yyval.tree)= (yyvsp[0].tree) ;}
#line 1974 "src/parser.c"
    break;

  case 54: /* INST: APPFONC  */
#line 213 "src/parser.y"
               {(yyval.tree) = (yyvsp[0].tree);}
#line 1980 "src/parser.c"
    break;

  case 55: /* INST: INDICX_RECU  */
#line 214 "src/parser.y"
              {(yyval.tree) = (yyvsp[0].tree);}
#line 1986 "src/parser.c"
    break;

  case 56: /* AFFECT: ID AFF EXP  */
#line 218 "src/parser.y"
                        { (yyval.tree) = creer_noeudAffic((yyvsp[-2].id), (yyvsp[0].tree)); }
#line 1992 "src/parser.c"
    break;

  case 57: /* AFFECT: ID AFF AFFECT  */
#line 219 "src/parser.y"
                           { (yyval.tree) = creer_noeudAffic((yyvsp[-2].id), (yyvsp[0].tree)); }
#line 1998 "src/parser.c"
    break;

  case 58: /* APPFONC: ID '(' PARAM ')'  */
#line 223 "src/parser.y"
                           { (yyval.tree) = creer_noeudAPPFONC ((yyvsp[-3].id), (yyvsp[-1].tree)); }
#line 2004 "src/parser.c"
    break;

  case 59: /* EXP: '(' EXP ')'  */
#line 229 "src/parser.y"
                             { (yyval.tree) = (yyvsp[-1].tree); }
#line 2010 "src/parser.c"
    break;

  case 60: /* EXP: INDICX_SORT  */
#line 230 "src/parser.y"
               {(yyval.tree) = (yyvsp[0].tree);}
#line 2016 "src/parser.c"
    break;

  case 61: /* EXP: NB  */
#line 231 "src/parser.y"
                    { (yyval.tree) = creer_feuilleNB(yyval.nb); }
#line 2022 "src/parser.c"
    break;

  case 62: /* EXP: VRAI  */
#line 232 "src/parser.y"
                     { (yyval.tree) = creer_feuilleNB(1); }
#line 2028 "src/parser.c"
    break;

  case 63: /* EXP: FAUX  */
#line 233 "src/parser.y"
                        { (yyval.tree) = creer_feuilleNB(0); }
#line 2034 "src/parser.c"
    break;

  case 64: /* EXP: ID  */
#line 234 "src/parser.y"
                        { (yyval.tree) = creer_feuilleID((yyvsp[0].id)); }
#line 2040 "src/parser.c"
    break;

  case 65: /* EXP: EXP '+' EXP  */
#line 235 "src/parser.y"
                         { (yyval.tree) = creer_noeudOP('+', (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 2046 "src/parser.c"
    break;

  case 66: /* EXP: EXP '-' EXP  */
#line 236 "src/parser.y"
                         { (yyval.tree) = creer_noeudOP('-', (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 2052 "src/parser.c"
    break;

  case 67: /* EXP: EXP '*' EXP  */
#line 237 "src/parser.y"
                         { (yyval.tree) = creer_noeudOP('*', (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 2058 "src/parser.c"
    break;

  case 68: /* EXP: EXP '/' EXP  */
#line 238 "src/parser.y"
                         { (yyval.tree) = creer_noeudOP('/', (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 2064 "src/parser.c"
    break;

  case 69: /* EXP: EXP '%' EXP  */
#line 239 "src/parser.y"
                         { (yyval.tree) = creer_noeudOP('%', (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 2070 "src/parser.c"
    break;

  case 70: /* EXP: EXP '<' EXP  */
#line 245 "src/parser.y"
              {(yyval.tree) = creer_noeudOP('<',(yyvsp[-2].tree) ,(yyvsp[0].tree));}
#line 2076 "src/parser.c"
    break;

  case 71: /* EXP: EXP '>' EXP  */
#line 247 "src/parser.y"
              {(yyval.tree) = creer_noeudOP('>',(yyvsp[-2].tree) ,(yyvsp[0].tree));}
#line 2082 "src/parser.c"
    break;

  case 72: /* EXP: EXP DIFF EXP  */
#line 249 "src/parser.y"
               {(yyval.tree) = creer_noeudOP(OP_DIFF,(yyvsp[-2].tree) ,(yyvsp[0].tree));}
#line 2088 "src/parser.c"
    break;

  case 73: /* EXP: EXP INFEGAL EXP  */
#line 251 "src/parser.y"
                  {(yyval.tree) = creer_noeudOP(OP_INF_EG,(yyvsp[-2].tree) ,(yyvsp[0].tree));}
#line 2094 "src/parser.c"
    break;

  case 74: /* EXP: EXP SUPEGAL EXP  */
#line 253 "src/parser.y"
                  {(yyval.tree) = creer_noeudOP(OP_SUP_EG,(yyvsp[-2].tree) ,(yyvsp[0].tree));}
#line 2100 "src/parser.c"
    break;

  case 75: /* EXP: EXP EGAL EXP  */
#line 255 "src/parser.y"
               {(yyval.tree) = creer_noeudOP('=', (yyvsp[-2].tree) ,(yyvsp[0].tree));}
#line 2106 "src/parser.c"
    break;

  case 76: /* EXP: EXP OU EXP  */
#line 257 "src/parser.y"
             {(yyval.tree) = creer_noeudOP('|',(yyvsp[-2].tree) ,(yyvsp[0].tree));}
#line 2112 "src/parser.c"
    break;

  case 77: /* EXP: EXP ET EXP  */
#line 259 "src/parser.y"
             {(yyval.tree) = creer_noeudOP('&',(yyvsp[-2].tree) ,(yyvsp[0].tree));}
#line 2118 "src/parser.c"
    break;

  case 78: /* EXP: NON EXP  */
#line 261 "src/parser.y"
              {(yyval.tree) = creer_noeudOP('!',(yyvsp[0].tree) ,NULL);}
#line 2124 "src/parser.c"
    break;

  case 79: /* EXP: '-' EXP  */
#line 263 "src/parser.y"
              {(yyval.tree) = creer_noeudOP(M_UN,(yyvsp[0].tree) ,NULL);}
#line 2130 "src/parser.c"
    break;


#line 2134 "src/parser.c"

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 273 "src/parser.y"


int main( int argc, char * argv[] ) {
  extern FILE *yyin;
  
  if (argc > 1){
    strcpy(srcname, argv[1]);
    if ( (yyin = fopen(srcname,"r"))==NULL ){
      char errmsg[256];
      sprintf(errmsg,"fichier \x1b[1m\x1b[33m' %s '\x1b[0m introuvable",srcname);
      print_file_error(argv[0],errmsg);
      exit(1);
    }
  }  else {
    print_file_error(argv[0],"aucun fichier en entree");
    exit(1);
  }
  strcpy(exename, "out.ram");
  if (argc == 3){
    strcpy(exename, argv[2]);
  }
  
  exefile = fopen(exename,"w");
  yyparse();

  //_____________________________la on modifier 






  TABLE_SYMBOLES = ts_init_table(CTXTglo) ;
  
  semantic(ARBRE_ABSTRAIT);
  print_asa_dot( ARBRE_ABSTRAIT);
  


  

  

  
  //print_asa(ARBRE_ABSTRAIT);
  ts_print(TABLE_SYMBOLES);
  codegen(ARBRE_ABSTRAIT);
  


  






  fclose(yyin);
}



static void print_file_error(char * prog, char *errmsg){
  fprintf(stderr,
	  "\x1b[1m%s:\x1b[0m \x1b[31m\x1b[1merreur fatale:\x1b[0m %s\nechec de la compilation\n",
	  prog, errmsg);
}

void yyerror(const char * s)
{
  fprintf(stderr, "\x1b[1m%s:%d:%d:\x1b[0m %s\n", srcname, yylloc.first_line, yylloc.first_column, s);
  exit(0);
}
