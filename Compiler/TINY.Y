/****************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
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

%}

%token IF ELSE WHILE RETURN INT VOID
%token ID NUM 
%token ASSIGN EQ NEQ LT GT LET GET PLUS MINUS TIMES OVER LPAREN RPAREN LSBRACKET RSBRACKET LBRACKET RBRACKET COMMA SEMI
%token ERROR 

%% /* Grammar for TINY */

program           : declaration_list
                    { savedTree = $1; }
                  ;

declaration_list  : declaration_list declaration
                    { YYSTYPE t = $1;
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = $2;
                        $$ = $1; }
                        else $$ = $2;
                      }
                  | declaration { $$ = $1; }
                  ;

declaration       : var_declaration { $$ = $1; }
                  | fun_declaration { $$ = $1; }
                  ;

var_declaration   : INT ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } SEMI
                    { $$ = newDecNode(VarINTK);
                      $$->attr.name = copyString(savedName[--savedIndex]); 
                      $$->lineno = savedLineNo[--savedLineNoIndex]; }
                  | VOID ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } SEMI
                    { $$ = newDecNode(VarVOIDK);
                      $$->attr.name = copyString(savedName[--savedIndex]);
                      $$->lineno = savedLineNo[--savedLineNoIndex]; }
                  | INT ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } 
                    LSBRACKET NUM { savedValue = atoi(preTokenString);} RSBRACKET
                    SEMI
                    { $$ = newDecNode(VarINTK);
                      $$->attr.name = copyString(savedName[--savedIndex]); 
                      $$->num = savedValue;
                      $$->lineno = savedLineNo[--savedLineNoIndex]; }
                  | VOID ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } 
                    LSBRACKET NUM { savedValue = atoi(preTokenString);} RSBRACKET
                    SEMI
                    { $$ = newDecNode(VarVOIDK);
                      $$->attr.name = copyString(savedName[--savedIndex]); 
                      $$->num = savedValue;
                      $$->lineno = savedLineNo[--savedLineNoIndex]; }
                  ;

fun_declaration   : INT ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } 
                    LPAREN params RPAREN compound_stmt
                    { $$ = newDecNode(FunINTK);
                      $$->attr.name = copyString(savedName[--savedIndex]);
                      $$->child[0] = $5;
                      $$->child[1] = $7;
                      $$->lineno = savedLineNo[--savedLineNoIndex];
                    }
                  | VOID ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } 
                    LPAREN params RPAREN compound_stmt
                    { $$ = newDecNode(FunVOIDK);
                      $$->attr.name = copyString(savedName[--savedIndex]);
                      $$->child[0] = $5;
                      $$->child[1] = $7;
                      $$->lineno = savedLineNo[--savedLineNoIndex];
                    }
                  ;

params            : param_list { $$ = $1; }
                  | VOID 
                    { $$ = newDecNode(ParVOIDK); 
                      $$->attr.name = copyString(preTokenString); 
                    }
                  ;

param_list        : param_list COMMA param
                    { YYSTYPE t = $1;
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = $3;
                        $$ = $1; }
                      else $$ = $3;
                    }
                  | param { $$ = $1; }
                  ;

param             : INT ID
                    { $$ = newDecNode(ParINTK);
                      $$->attr.name = copyString(preTokenString);
                      $$->lineno = lineno;
                    }
                  | VOID ID
                    { $$ = newDecNode(ParVOIDK);
                      $$->attr.name = copyString(preTokenString);
                      $$->lineno = lineno;
                    }   
                  | INT ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; }  
                    LSBRACKET RSBRACKET
                    { $$ = newDecNode(ParINTK);
                      $$->attr.name = copyString(savedName[--savedIndex]);
                      $$->num = 0;
                      $$->lineno = savedLineNo[--savedLineNoIndex];
                    }
                  | VOID ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } 
                    LSBRACKET RSBRACKET
                    { $$ = newDecNode(ParVOIDK);
                      $$->attr.name = copyString(savedName[--savedIndex]);
                      $$->num = 0;
                      $$->lineno = savedLineNo[--savedLineNoIndex];
                    }                   
                  ;

compound_stmt     : LBRACKET local_declarations statement_list RBRACKET
                    { $$ = newStmtNode(ComK);
                      $$->child[0] = $2;
                      $$->child[1] = $3; 
                    }
                  ;

local_declarations: local_declarations var_declaration
                    { YYSTYPE t = $1;
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = $2;
                        $$ = $1; }
                      else $$ = $2;
                    }
                  | var_declaration { $$ = $1; }
                  | { $$ = NULL; }
                  ;

statement_list    : statement_list statement
                    { YYSTYPE t = $1;
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = $2;
                        $$ = $1; }
                      else $$ = $2;
                    }
                  | statement { $$ = $1; }
                  | {$$ = NULL;}
                  ;

statement         : expression_stmt { $$ = $1; } 
                  | compound_stmt { $$ = $1; } 
                  | selection_stmt { $$ = $1; }
                  | iteration_stmt { $$ = $1; }
                  | return_stmt { $$ = $1; }
                  ;

expression_stmt   : expression SEMI 
                    { $$ = newStmtNode(ExpsK); 
                      $$->child[0] = $1; 
                    }
                  | SEMI { $$ = NULL; }
                  ;                 

selection_stmt    : IF LPAREN expression RPAREN statement
                    { $$ = newStmtNode(IfK);
                      $$->child[0] = $3;
                      $$->child[1] = $5;
                    }
                  | IF LPAREN expression RPAREN statement ELSE statement
                    { $$ = newStmtNode(IfK);
                      $$->child[0] = $3;
                      $$->child[1] = $5;
                      $$->child[2] = $7;
                    }
                  ;

iteration_stmt    : WHILE LPAREN expression RPAREN statement
                    { $$ = newStmtNode(WhileK);
                      $$->child[0] = $3;
                      $$->child[1] = $5;
                    }
                  ;

return_stmt       : RETURN SEMI { $$ = newStmtNode(ReturnK); }
                  | RETURN expression SEMI 
                    { $$ = newStmtNode(ReturnK); 
                      $$->child[0] = $2; 
                  }
                  ;

expression        : var ASSIGN expression
                    { $$ = newStmtNode(AssignK);
                      $$->child[0] = $1;
                      $$->child[1] = $3;
                    }
                  | simple_expression { $$ = $1; }
                  ;

var               : ID 
                    { $$ = newDecNode(VarK);
                      $$->attr.name = copyString(preTokenString); 
                      $$->lineno = lineno;
                    }
                  | ID { savedName[savedIndex++]= copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } 
                    LSBRACKET expression RSBRACKET
                    { $$ = newDecNode(VarK);
                      $$->attr.name = copyString(savedName[--savedIndex]);
                      $$->num = 0;
                      $$->child[0] = $4;
                      $$->lineno = savedLineNo[--savedLineNoIndex];
                    }
                  ;

simple_expression : additive_expression relop additive_expression
                    { $$ = $2;
                      $$->child[0] = $1;
                      $$->child[1] = $3;
                    }
                  | additive_expression { $$ = $1; }
                  ;

relop             : LET { $$ = newExpNode(OpK); $$->attr.op = LET; }
                  | LT { $$ = newExpNode(OpK); $$->attr.op = LT; }   
                  | GT { $$ = newExpNode(OpK); $$->attr.op = GT; }
                  | GET { $$ = newExpNode(OpK); $$->attr.op = GET; }
                  | EQ { $$ = newExpNode(OpK); $$->attr.op = EQ; }
                  | NEQ { $$ = newExpNode(OpK); $$->attr.op = NEQ; }
                  ;

additive_expression: additive_expression addop term
                      { $$ = $2;
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                      }
                    | term { $$ = $1; }  
                    ;

addop             : PLUS { $$ = newExpNode(OpK); $$->attr.op = PLUS; }
                  | MINUS { $$ = newExpNode(OpK); $$->attr.op = MINUS; }
                  ;

term              : term mulop factor
                    { $$ = $2;
                      $$->child[0] = $1;
                      $$->child[1] = $3;
                    }
                  | factor { $$ = $1; }
                  ;

mulop             : TIMES { $$ = newExpNode(OpK); $$->attr.op = TIMES; }
                  | OVER { $$ = newExpNode(OpK); $$->attr.op = OVER; }
                  ;

factor            : LPAREN expression RPAREN { $$ = $2; }
                  | var { $$ = $1; }
                  | call { $$ = $1; }
                  | NUM { $$ = newExpNode(ConstK); $$->attr.val = atoi(preTokenString); }
                  ;

call              : ID { savedName[savedIndex++] = copyString(preTokenString); savedLineNo[savedLineNoIndex++] = lineno; } 
                    LPAREN args RPAREN
                    { $$ = newStmtNode(CallK);
                      $$->attr.name = savedName[--savedIndex];
                      $$->child[0] = $4; 
                      $$->lineno = savedLineNo[--savedLineNoIndex];
                    }
                  ;

args              : arg_list { $$ = $1; }
                  | { $$ = NULL; }
                  ;

arg_list          : arg_list COMMA expression
                    { YYSTYPE t = $1;
                      if (t != NULL)
                      { while (t->sibling != NULL)
                          t = t->sibling;
                        t->sibling = $3;
                        $$ = $1;}
                      else $$ = $3;
                    }
                  | expression { $$ = $1; }
                  ;

%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
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

