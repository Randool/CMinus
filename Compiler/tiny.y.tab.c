
/*  A Bison parser, made from TINY.Y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define alloca

#define	IF	258
#define	ELSE	259
#define	WHILE	260
#define	RETURN	261
#define	INT	262
#define	VOID	263
#define	ID	264
#define	NUM	265
#define	ASSIGN	266
#define	EQ	267
#define	NEQ	268
#define	LT	269
#define	GT	270
#define	LET	271
#define	GET	272
#define	PLUS	273
#define	MINUS	274
#define	TIMES	275
#define	OVER	276
#define	LPAREN	277
#define	RPAREN	278
#define	LSBRACKET	279
#define	RSBRACKET	280
#define	LBRACKET	281
#define	RBRACKET	282
#define	COMMA	283
#define	SEMI	284
#define	ERROR	285

#line 7 "TINY.Y"

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName[100]; /* for use in assignments */
static int savedIndex = 0;
static int savedValue;
static int savedLineNo[100];  /* ditto */
static int savedLineNoIndex = 0;
static TreeNode * savedTree; /* stores syntax tree for later return */

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		131
#define	YYFLAG		32768
#define	YYNTBASE	31

#define YYTRANSLATE(x) ((unsigned)(x) <= 285 ? yytranslate[x] : 71)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,     9,    11,    12,    17,    18,    23,
    24,    25,    34,    35,    36,    45,    46,    54,    55,    63,
    65,    67,    71,    73,    76,    79,    80,    86,    87,    93,
    98,   101,   103,   104,   107,   109,   110,   112,   114,   116,
   118,   120,   123,   125,   131,   139,   145,   148,   152,   156,
   158,   160,   161,   167,   171,   173,   175,   177,   179,   181,
   183,   185,   189,   191,   193,   195,   199,   201,   203,   205,
   209,   211,   213,   215,   216,   222,   224,   225,   229
};

static const short yyrhs[] = {    32,
     0,    32,    33,     0,    33,     0,    34,     0,    41,     0,
     0,     7,     9,    35,    29,     0,     0,     8,     9,    36,
    29,     0,     0,     0,     7,     9,    37,    24,    10,    38,
    25,    29,     0,     0,     0,     8,     9,    39,    24,    10,
    40,    25,    29,     0,     0,     7,     9,    42,    22,    44,
    23,    49,     0,     0,     8,     9,    43,    22,    44,    23,
    49,     0,    45,     0,     8,     0,    45,    28,    46,     0,
    46,     0,     7,     9,     0,     8,     9,     0,     0,     7,
     9,    47,    24,    25,     0,     0,     8,     9,    48,    24,
    25,     0,    26,    50,    51,    27,     0,    50,    34,     0,
    34,     0,     0,    51,    52,     0,    52,     0,     0,    53,
     0,    49,     0,    54,     0,    55,     0,    56,     0,    57,
    29,     0,    29,     0,     3,    22,    57,    23,    52,     0,
     3,    22,    57,    23,    52,     4,    52,     0,     5,    22,
    57,    23,    52,     0,     6,    29,     0,     6,    57,    29,
     0,    58,    11,    57,     0,    60,     0,     9,     0,     0,
     9,    59,    24,    57,    25,     0,    62,    61,    62,     0,
    62,     0,    16,     0,    14,     0,    15,     0,    17,     0,
    12,     0,    13,     0,    62,    63,    64,     0,    64,     0,
    18,     0,    19,     0,    64,    65,    66,     0,    66,     0,
    20,     0,    21,     0,    22,    57,    23,     0,    58,     0,
    67,     0,    10,     0,     0,     9,    68,    22,    69,    23,
     0,    70,     0,     0,    70,    28,    57,     0,    57,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    32,    36,    45,    48,    49,    52,    53,    56,    57,    60,
    61,    62,    67,    68,    69,    76,    77,    84,    85,    94,
    95,   101,   110,   113,   118,   123,   124,   130,   131,   139,
   146,   155,   156,   159,   168,   169,   172,   173,   174,   175,
   176,   179,   183,   186,   191,   199,   206,   207,   213,   218,
   221,   226,   227,   236,   241,   244,   245,   246,   247,   248,
   249,   252,   257,   260,   261,   264,   269,   272,   273,   276,
   277,   278,   279,   282,   283,   291,   292,   295,   304
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","IF","ELSE",
"WHILE","RETURN","INT","VOID","ID","NUM","ASSIGN","EQ","NEQ","LT","GT","LET",
"GET","PLUS","MINUS","TIMES","OVER","LPAREN","RPAREN","LSBRACKET","RSBRACKET",
"LBRACKET","RBRACKET","COMMA","SEMI","ERROR","program","declaration_list","declaration",
"var_declaration","@1","@2","@3","@4","@5","@6","fun_declaration","@7","@8",
"params","param_list","param","@9","@10","compound_stmt","local_declarations",
"statement_list","statement","expression_stmt","selection_stmt","iteration_stmt",
"return_stmt","expression","var","@11","simple_expression","relop","additive_expression",
"addop","term","mulop","factor","call","@12","args","arg_list", NULL
};
#endif

static const short yyr1[] = {     0,
    31,    32,    32,    33,    33,    35,    34,    36,    34,    37,
    38,    34,    39,    40,    34,    42,    41,    43,    41,    44,
    44,    45,    45,    46,    46,    47,    46,    48,    46,    49,
    50,    50,    50,    51,    51,    51,    52,    52,    52,    52,
    52,    53,    53,    54,    54,    55,    56,    56,    57,    57,
    58,    59,    58,    60,    60,    61,    61,    61,    61,    61,
    61,    62,    62,    63,    63,    64,    64,    65,    65,    66,
    66,    66,    66,    68,    67,    69,    69,    70,    70
};

static const short yyr2[] = {     0,
     1,     2,     1,     1,     1,     0,     4,     0,     4,     0,
     0,     8,     0,     0,     8,     0,     7,     0,     7,     1,
     1,     3,     1,     2,     2,     0,     5,     0,     5,     4,
     2,     1,     0,     2,     1,     0,     1,     1,     1,     1,
     1,     2,     1,     5,     7,     5,     2,     3,     3,     1,
     1,     0,     5,     3,     1,     1,     1,     1,     1,     1,
     1,     3,     1,     1,     1,     3,     1,     1,     1,     3,
     1,     1,     1,     0,     5,     1,     0,     3,     1
};

static const short yydefact[] = {     0,
     0,     0,     1,     3,     4,     5,     6,     8,     2,     0,
     0,     0,     0,     0,     0,     7,     0,     0,     9,     0,
     0,    11,     0,    21,     0,    20,    23,    14,     0,     0,
    24,    25,     0,     0,     0,     0,     0,     0,     0,    33,
    17,     0,    22,     0,    19,    12,     0,     0,     0,     0,
    32,    36,    15,    27,    29,     6,     8,     0,     0,     0,
    51,    73,     0,    43,    31,    38,     0,    35,    37,    39,
    40,    41,     0,    71,    50,    55,    63,    67,    72,     0,
     0,    47,     0,     0,     0,     0,    30,    34,    42,     0,
    60,    61,    57,    58,    56,    59,    64,    65,     0,     0,
    68,    69,     0,     0,     0,    48,     0,    77,    70,    49,
    71,    54,    62,    66,     0,     0,     0,    79,     0,    76,
    44,    46,    53,    75,     0,     0,    78,    45,     0,     0,
     0
};

static const short yydefgoto[] = {   129,
     3,     4,     5,    10,    13,    11,    30,    14,    35,     6,
    12,    15,    25,    26,    27,    38,    39,    66,    52,    67,
    68,    69,    70,    71,    72,    73,    74,    84,    75,    99,
    76,   100,    77,   103,    78,    79,    85,   119,   120
};

static const short yypact[] = {    38,
    -3,     8,    38,-32768,-32768,-32768,   -20,    12,-32768,    23,
     1,    33,    35,    49,    64,-32768,    77,    55,-32768,    78,
    55,-32768,    80,    81,    68,    65,-32768,-32768,    69,    70,
    72,    73,    74,    59,    76,    74,    75,    79,    82,    61,
-32768,    81,-32768,    83,-32768,-32768,    84,    85,    89,    90,
-32768,     2,-32768,-32768,-32768,    87,    91,    86,    92,     4,
    37,-32768,    34,-32768,-32768,-32768,    13,-32768,-32768,-32768,
-32768,-32768,    88,    94,-32768,    66,    51,-32768,-32768,    34,
    34,-32768,    93,    95,    96,    71,-32768,-32768,-32768,    34,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    34,    34,
-32768,-32768,    34,    97,    98,-32768,    34,    34,-32768,-32768,
-32768,    57,    51,-32768,    48,    48,    99,-32768,   100,   101,
   103,-32768,-32768,-32768,    34,    48,-32768,-32768,   102,   113,
-32768
};

static const short yypgoto[] = {-32768,
-32768,   122,   -25,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   105,-32768,   104,-32768,-32768,    -4,-32768,-32768,
   -66,-32768,-32768,-32768,-32768,   -60,   -62,-32768,-32768,-32768,
    17,-32768,    27,-32768,    25,-32768,-32768,-32768,-32768
};


#define	YYLAST		138


static const short yytable[] = {    83,
    88,   -16,    86,   -10,    58,     7,    59,    60,    49,    50,
    61,    62,    61,    62,    51,    58,     8,    59,    60,   104,
   105,    61,    62,    63,    17,    63,    65,    40,    41,   110,
    64,    45,    82,   -18,    63,   -13,   111,   111,    40,    87,
   111,    64,    61,    62,     1,     2,   117,   118,   121,   122,
    58,    16,    59,    60,    18,    63,    61,    62,   -74,   128,
   -52,    23,    24,    19,   127,    23,    42,    49,    50,    63,
   101,   102,    20,    40,    97,    98,    64,    91,    92,    93,
    94,    95,    96,    97,    98,    21,    22,    28,    31,    32,
    33,    36,    34,   109,    37,   -26,   -28,    56,    57,    40,
    44,   130,    47,    46,    90,    48,   126,    80,    54,    55,
   -10,    53,   131,    81,   -13,   112,    89,   108,   107,   115,
   116,   106,   124,   123,     9,    29,   113,   114,   125,     0,
     0,     0,     0,     0,     0,     0,     0,    43
};

static const short yycheck[] = {    60,
    67,    22,    63,    24,     3,     9,     5,     6,     7,     8,
     9,    10,     9,    10,    40,     3,     9,     5,     6,    80,
    81,     9,    10,    22,    24,    22,    52,    26,    33,    90,
    29,    36,    29,    22,    22,    24,    99,   100,    26,    27,
   103,    29,     9,    10,     7,     8,   107,   108,   115,   116,
     3,    29,     5,     6,    22,    22,     9,    10,    22,   126,
    24,     7,     8,    29,   125,     7,     8,     7,     8,    22,
    20,    21,    24,    26,    18,    19,    29,    12,    13,    14,
    15,    16,    17,    18,    19,    22,    10,    10,     9,     9,
    23,    23,    28,    23,    25,    24,    24,     9,     9,    26,
    25,     0,    24,    29,    11,    24,     4,    22,    25,    25,
    24,    29,     0,    22,    24,    99,    29,    22,    24,    23,
    23,    29,    23,    25,     3,    21,   100,   103,    28,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		getToken()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 33 "TINY.Y"
{ savedTree = yyvsp[0]; ;
    break;}
case 2:
#line 37 "TINY.Y"
{ YYSTYPE t = yyvsp[-1];
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = yyvsp[0];
                        yyval = yyvsp[-1]; }
                        else yyval = yyvsp[0];
                      ;
    break;}
case 3:
#line 45 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 4:
#line 48 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 5:
#line 49 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 6:
#line 52 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 7:
#line 53 "TINY.Y"
{ yyval = newDecNode(VarINTK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->lineno = savedLineNo[--savedLineNoIndex]; ;
    break;}
case 8:
#line 56 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 9:
#line 57 "TINY.Y"
{ yyval = newDecNode(VarVOIDK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->lineno = savedLineNo[--savedLineNoIndex]; ;
    break;}
case 10:
#line 60 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 11:
#line 61 "TINY.Y"
{ savedValue = atoi(preTokenString);;
    break;}
case 12:
#line 63 "TINY.Y"
{ yyval = newDecNode(VarINTK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->num = savedValue;
                      yyval->lineno = savedLineNo[--savedLineNoIndex]; ;
    break;}
case 13:
#line 67 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 14:
#line 68 "TINY.Y"
{ savedValue = atoi(preTokenString);;
    break;}
case 15:
#line 70 "TINY.Y"
{ yyval = newDecNode(VarVOIDK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->num = savedValue;
                      yyval->lineno = savedLineNo[--savedLineNoIndex]; ;
    break;}
case 16:
#line 76 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 17:
#line 78 "TINY.Y"
{ yyval = newDecNode(FunINTK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->child[0] = yyvsp[-2];
                      yyval->child[1] = yyvsp[0];
                      yyval->lineno = savedLineNo[--savedLineNoIndex];
                    ;
    break;}
case 18:
#line 84 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 19:
#line 86 "TINY.Y"
{ yyval = newDecNode(FunVOIDK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->child[0] = yyvsp[-2];
                      yyval->child[1] = yyvsp[0];
                      yyval->lineno = savedLineNo[--savedLineNoIndex];
                    ;
    break;}
case 20:
#line 94 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 21:
#line 96 "TINY.Y"
{ yyval = newDecNode(ParVOIDK);
                      yyval->attr.name = copyString(preTokenString);
                    ;
    break;}
case 22:
#line 102 "TINY.Y"
{ YYSTYPE t = yyvsp[-2];
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = yyvsp[0];
                        yyval = yyvsp[-2]; }
                      else yyval = yyvsp[0];
                    ;
    break;}
case 23:
#line 110 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 24:
#line 114 "TINY.Y"
{ yyval = newDecNode(ParINTK);
                      yyval->attr.name = copyString(preTokenString);
                      yyval->lineno = lineno;
                    ;
    break;}
case 25:
#line 119 "TINY.Y"
{ yyval = newDecNode(ParVOIDK);
                      yyval->attr.name = copyString(preTokenString);
                      yyval->lineno = lineno;
                    ;
    break;}
case 26:
#line 123 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 27:
#line 125 "TINY.Y"
{ yyval = newDecNode(ParINTK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->num = 0;
                      yyval->lineno = savedLineNo[--savedLineNoIndex];
                    ;
    break;}
case 28:
#line 130 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 29:
#line 132 "TINY.Y"
{ yyval = newDecNode(ParVOIDK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->num = 0;
                      yyval->lineno = savedLineNo[--savedLineNoIndex];
                    ;
    break;}
case 30:
#line 140 "TINY.Y"
{ yyval = newStmtNode(ComK);
                      yyval->child[0] = yyvsp[-2];
                      yyval->child[1] = yyvsp[-1];
                    ;
    break;}
case 31:
#line 147 "TINY.Y"
{ YYSTYPE t = yyvsp[-1];
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = yyvsp[0];
                        yyval = yyvsp[-1]; }
                      else yyval = yyvsp[0];
                    ;
    break;}
case 32:
#line 155 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 33:
#line 156 "TINY.Y"
{ yyval = NULL; ;
    break;}
case 34:
#line 160 "TINY.Y"
{ YYSTYPE t = yyvsp[-1];
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = yyvsp[0];
                        yyval = yyvsp[-1]; }
                      else yyval = yyvsp[0];
                    ;
    break;}
case 35:
#line 168 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 36:
#line 169 "TINY.Y"
{yyval = NULL;;
    break;}
case 37:
#line 172 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 38:
#line 173 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 39:
#line 174 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 40:
#line 175 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 41:
#line 176 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 42:
#line 180 "TINY.Y"
{ yyval = newStmtNode(ExpsK);
                      yyval->child[0] = yyvsp[-1];
                    ;
    break;}
case 43:
#line 183 "TINY.Y"
{ yyval = NULL; ;
    break;}
case 44:
#line 187 "TINY.Y"
{ yyval = newStmtNode(IfK);
                      yyval->child[0] = yyvsp[-2];
                      yyval->child[1] = yyvsp[0];
                    ;
    break;}
case 45:
#line 192 "TINY.Y"
{ yyval = newStmtNode(IfK);
                      yyval->child[0] = yyvsp[-4];
                      yyval->child[1] = yyvsp[-2];
                      yyval->child[2] = yyvsp[0];
                    ;
    break;}
case 46:
#line 200 "TINY.Y"
{ yyval = newStmtNode(WhileK);
                      yyval->child[0] = yyvsp[-2];
                      yyval->child[1] = yyvsp[0];
                    ;
    break;}
case 47:
#line 206 "TINY.Y"
{ yyval = newStmtNode(ReturnK); ;
    break;}
case 48:
#line 208 "TINY.Y"
{ yyval = newStmtNode(ReturnK);
                      yyval->child[0] = yyvsp[-1];
                  ;
    break;}
case 49:
#line 214 "TINY.Y"
{ yyval = newStmtNode(AssignK);
                      yyval->child[0] = yyvsp[-2];
                      yyval->child[1] = yyvsp[0];
                    ;
    break;}
case 50:
#line 218 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 51:
#line 222 "TINY.Y"
{ yyval = newDecNode(VarK);
                      yyval->attr.name = copyString(preTokenString);
                      yyval->lineno = lineno;
                    ;
    break;}
case 52:
#line 226 "TINY.Y"
{ savedName[savedIndex++]= copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 53:
#line 228 "TINY.Y"
{ yyval = newDecNode(VarK);
                      yyval->attr.name = copyString(savedName[--savedIndex]);
                      yyval->num = 0;
                      yyval->child[0] = yyvsp[-1];
                      yyval->lineno = savedLineNo[--savedLineNoIndex];
                    ;
    break;}
case 54:
#line 237 "TINY.Y"
{ yyval = yyvsp[-1];
                      yyval->child[0] = yyvsp[-2];
                      yyval->child[1] = yyvsp[0];
                    ;
    break;}
case 55:
#line 241 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 56:
#line 244 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = LET; ;
    break;}
case 57:
#line 245 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = LT; ;
    break;}
case 58:
#line 246 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = GT; ;
    break;}
case 59:
#line 247 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = GET; ;
    break;}
case 60:
#line 248 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = EQ; ;
    break;}
case 61:
#line 249 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = NEQ; ;
    break;}
case 62:
#line 253 "TINY.Y"
{ yyval = yyvsp[-1];
                        yyval->child[0] = yyvsp[-2];
                        yyval->child[1] = yyvsp[0];
                      ;
    break;}
case 63:
#line 257 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 64:
#line 260 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = PLUS; ;
    break;}
case 65:
#line 261 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = MINUS; ;
    break;}
case 66:
#line 265 "TINY.Y"
{ yyval = yyvsp[-1];
                      yyval->child[0] = yyvsp[-2];
                      yyval->child[1] = yyvsp[0];
                    ;
    break;}
case 67:
#line 269 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 68:
#line 272 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = TIMES; ;
    break;}
case 69:
#line 273 "TINY.Y"
{ yyval = newExpNode(OpK); yyval->attr.op = OVER; ;
    break;}
case 70:
#line 276 "TINY.Y"
{ yyval = yyvsp[-1]; ;
    break;}
case 71:
#line 277 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 72:
#line 278 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 73:
#line 279 "TINY.Y"
{ yyval = newExpNode(ConstK); yyval->attr.val = atoi(preTokenString); ;
    break;}
case 74:
#line 282 "TINY.Y"
{ savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; ;
    break;}
case 75:
#line 284 "TINY.Y"
{ yyval = newStmtNode(CallK);
                      yyval->attr.name = savedName[--savedIndex];
                      yyval->child[0] = yyvsp[-1];
                      yyval->lineno = savedLineNo[--savedLineNoIndex];
                    ;
    break;}
case 76:
#line 291 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
case 77:
#line 292 "TINY.Y"
{ yyval = NULL; ;
    break;}
case 78:
#line 296 "TINY.Y"
{ YYSTYPE t = yyvsp[-2];
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = yyvsp[0];
                        yyval = yyvsp[-2];}
                      else yyval = yyvsp[0];
                    ;
    break;}
case 79:
#line 304 "TINY.Y"
{ yyval = yyvsp[0]; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 307 "TINY.Y"


int yyerror(char * message)
{ fprintf(listening,"[Error]\tSyntax error at line %d: %s\n",lineno,message);
  fprintf(listening,"\tCurrent token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

