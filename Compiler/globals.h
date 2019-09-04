/****************************************************/
/* File: globals.h                                  */
/* Yacc/Bison Version                               */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* Yacc/Bison generates internally its own values
 * for the tokens. Other files can access these values
 * by including the tab.h file generated using the
 * Yacc/Bison option -d ("generate header")
 *
 * The YYPARSER flag prevents inclusion of the tab.h
 * into the Yacc/Bison output itself
 */

#ifndef YYPARSER

/* the name of the following file may change */
#include "tiny.y.tab.h"

/* ENDFILE is implicitly defined by Yacc/Bison,
 * and not included in the tab.h file
 */
#define ENDFILE 0

#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

// program name
extern char pgm[128];

/// 随意使用的空间
extern char buff[128];

/* Yacc/Bison generates its own integer values
 * for tokens
 */
typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listening; /* listening output text file */
extern FILE* code; /* code text file for TM simulator */

extern int lineno; /* source line number for listening */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {
    StmtK, ExpK, DecK
} NodeKind;

typedef enum {
    IfK, RepeatK, AssignK, ReadK, WriteK,
    ComK, ExpsK, CallK, WhileK, ReturnK
} StmtKind;

typedef enum {
    OpK, ConstK, IdK
} ExpKind;

typedef enum {
    VarINTK, FunINTK, VarVOIDK,
    FunVOIDK, ParINTK, ParVOIDK, VarK
} DecKind;

/* ExpType is used for type checking */
typedef enum {
    Void, Integer, Boolean, TError
} Type;

#define MAXCHILDREN 3

typedef struct treeNode {
    struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    int lineno;
    NodeKind nodekind;
    union {
        StmtKind stmt;
        ExpKind exp;
        DecKind dec;
    } kind;
    union {
        TokenType op;
        int val;
        char *name;
    } attr;
    Type type; // 检查语义时用
    int num;

    // 中间代码
    char *qcodes;
    char *temp;
    char *truelist;
    char *falselist;
    char *next;
} TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/
extern int EchoSource;
extern int TraceScan;
extern int TraceParse;
extern int TraceAnalyze;
extern int TraceQcode;
extern int TraceMcode;
extern int Error;

extern char preTokenString[40+1];

/**************************************************/
/***********  Flags for machine code   ************/
/**************************************************/
typedef enum {
    ILT, IBG, ILE, IBE, IEQ, INEQ,  // 逻辑运算
    IASSIGN,    // 赋值
    IPLUS, IMINUS, IMUL, IDIV,  // 算数运算
    IMINUS_RIG, IPLUS_RIG,  // 寄存器指令集
    IIF, ICALL, IRET, IFN, IGOTO, IPARA, IADDR, IERROR
} InstrType;

#endif
