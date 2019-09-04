/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

void printToken(TokenType token, const char* tokenString) {
    switch (token) {
    case IF:
    case ELSE:
    case WHILE:
    case RETURN:
    case INT:
    case VOID:
        fprintf(listening,
                "reserved word: %s\n", tokenString);
        break;
    case ASSIGN:
        fprintf(listening,"=\n");
        break;
    case LT:
        fprintf(listening,"<\n");
        break;
    case GT:
        fprintf(listening,">\n");
        break;
    case LET:
        fprintf(listening,"<=\n");
        break;
    case GET:
        fprintf(listening,">=\n");
        break;
    case EQ:
        fprintf(listening,"==\n");
        break;
    case NEQ:
        fprintf(listening,"!=\n");
        break;
    case LPAREN:
        fprintf(listening,"(\n");
        break;
    case RPAREN:
        fprintf(listening,")\n");
        break;
    case LSBRACKET:
        fprintf(listening,"[\n");
        break;
    case RSBRACKET:
        fprintf(listening,"]\n");
        break;
    case LBRACKET:
        fprintf(listening,"{\n");
        break;
    case RBRACKET:
        fprintf(listening,"}\n");
        break;
    case COMMA:
        fprintf(listening,",\n");
        break;
    case SEMI:
        fprintf(listening,";\n");
        break;
    case PLUS:
        fprintf(listening,"+\n");
        break;
    case MINUS:
        fprintf(listening,"-\n");
        break;
    case TIMES:
        fprintf(listening,"*\n");
        break;
    case OVER:
        fprintf(listening,"/\n");
        break;
    case ENDFILE:
        fprintf(listening,"EOF\n");
        break;
    case NUM:
        fprintf(listening,
                "NUM, val= %s\n",tokenString);
        break;
    case ID:
        fprintf(listening,
                "ID, name= %s\n",tokenString);
        break;
    case ERROR:
        fprintf(listening,
                "ERROR: %s\n",tokenString);
        break;
    default: /* should never happen */
        fprintf(listening,"Unknown token: %d\n",token);
    }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind) {
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL)
        fprintf(listening,"Out of memory error at line %d\n",lineno);
    else {
        for (i=0; i<MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
    }
    return t;
}

/* Function newExpNode creates a new expression
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind) {
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL)
        fprintf(listening,"Out of memory error at line %d\n",lineno);
    else {
        for (i=0; i<MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
        t->type = Void;
    }
    return t;
}

TreeNode * newDecNode(DecKind kind) {
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL)
        fprintf(listening,"Out of memory error at line %d\n",lineno);
    else {
        for (i=0; i<MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = DecK;
        t->kind.dec = kind;
        t->lineno = lineno;
        t->type = Void;
        t->num = -1;
    }
    return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char *copyString(char *s) {
    int n;
    char * t;
    if (s==NULL)
        return NULL;
    n = strlen(s)+1;
    t = (char *)malloc(n);
    if (t==NULL)
        fprintf(listening,"Out of memory error at line %d\n",lineno);
    else
        strcpy(t,s);
    return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces() {
    int i;
    for (i = 0; i < indentno; i++)
        fprintf(listening,"-");
}

void printTree(TreeNode *tree) {
    INDENT;
    while (tree != NULL) {
        printSpaces();
        if (tree->nodekind == StmtK) {
            switch (tree->kind.stmt) {
            case IfK:
                fprintf(listening,"IfK\n");
                break;
            case AssignK:
                fprintf(listening,"AssignK: =\n");
                break;
            case ComK:
                fprintf(listening, "ComK\n");
                break;
            case ExpsK:
                fprintf(listening, "ExpsK\n");
                break;
            case CallK:
                fprintf(listening,"CallK: %s\n", tree->attr.name);
                break;
            case WhileK:
                fprintf(listening,"WhileK\n");
                break;
            case ReturnK:
                fprintf(listening,"ReturnK\n");
                break;
            default:
                fprintf(listening,"Unknown ExpNode kind\n");
                break;
            }
        }
        else if (tree->nodekind == ExpK) {
            switch (tree->kind.exp) {
            case OpK:
                fprintf(listening,"OpK: ");
                printToken(tree->attr.op, "\0");
                break;
            case ConstK:
                fprintf(listening,"ConstK: %d\n",tree->attr.val);
                break;
            case IdK:
                fprintf(listening,"IdK: %s\n",tree->attr.name);
                break;
            default:
                fprintf(listening,"Unknown ExpNode kind\n");
                break;
            }
        }
        else if (tree->nodekind == DecK) {
            switch (tree->kind.dec) {
            case VarINTK:
                if (tree->num == -1)
                    fprintf(listening,"VarINTK: %s\n", tree->attr.name);
                else
                    fprintf(listening,"VarINTK: %s[%d]\n", tree->attr.name, tree->num);
                break;
            case FunINTK:
                fprintf(listening,"FunINTK: %s\n", tree->attr.name);
                break;
            case VarVOIDK:
                if (tree->num == -1)
                    fprintf(listening,"VarVOIDK: %s\n", tree->attr.name);
                else
                    fprintf(listening,"VarVOIDK: %s[%d]\n", tree->attr.name, tree->num);
                break;
            case FunVOIDK:
                fprintf(listening,"FunVOIDK: %s\n", tree->attr.name);
                break;
            case ParINTK:
                if (tree->num == -1)
                    fprintf(listening,"ParINTK: %s\n", tree->attr.name);
                else
                    fprintf(listening, "ParINTK: %s[%d]\n", tree->attr.name, tree->num);
                break;
            case ParVOIDK:
                if (tree->num == -1)
                    fprintf(listening,"ParVOIDK: %s\n", tree->attr.name);
                else
                    fprintf(listening,"ParVOIDK: %s[%d]\n", tree->attr.name, tree->num);
                break;
            case VarK:
                if (tree->num == -1)
                    fprintf(listening,"VarK: %s\n", tree->attr.name);
                else
                    fprintf(listening,"VarK: %s[%d]\n", tree->attr.name, tree->num);
                break;
            default:
                fprintf(listening,"Unknown DecNode kind\n");
                break;
            }
        }
        else
            fprintf(listening,"Unknown node kind\n");
        int i;
        for (i = 0; i < MAXCHILDREN; ++i)
            printTree(tree->child[i]);
        tree = tree->sibling;
    }
    UNINDENT;
}
