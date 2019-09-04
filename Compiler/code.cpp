/**
用于生成中间代码
*/
#include "code.h"
#include "symtab.h"

#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

#define stringlen(n) ((char*) malloc(sizeof(char) * n))

char *integer2string(int val) {
    char *ret = stringlen(12);
    sprintf(ret, "%d", val);
    return ret;
}

static int label = 1;
static int temp = 1;

char *newtemp() {
    char *ret = stringlen(13);
    sprintf(ret, "@T%d", temp++);
    return ret;
}

char *newlabel() {
    char *ret = stringlen(13);
    ret[0] = 'L';
    ret[1] =  '\0';
    char *cval = integer2string(label++);
    strcat(ret, cval);
    return ret;
}

char *gen_qcode(TokenType op, const char *temp, const char *arg1, const char *arg2) {
    // 生成逻辑运算符和算数运算符的4元码。需要防止同时两次访问内存
    char *spill_to_m = stringlen(20);
    char *ptr1 = NULL;
    char *cal = stringlen(20);

    if (arg1[0] == '.' && arg2[0] == '.') {
        ptr1 = newtemp();
        sprintf(spill_to_m, "=\t%s\t%s\n", ptr1, arg1);
    }
    else {
        ptr1 = stringlen(20);
        strcpy(ptr1, arg1);
    }

    switch (op) {
        case LT:    sprintf(cal, "<\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case GT:    sprintf(cal, ">\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case LET:   sprintf(cal, "<=\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case GET:   sprintf(cal, ">=\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case EQ:    sprintf(cal, "==\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case NEQ:   sprintf(cal, "!=\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case PLUS:  sprintf(cal, "+\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case MINUS: sprintf(cal, "-\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case TIMES: sprintf(cal, "*\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
        case OVER:  sprintf(cal, "/\t%s\t%s\t%s\n", ptr1, arg2, temp); break;
    }

    if (arg1[0] == '.' && arg2[0] == '.')
        return strcat(spill_to_m, cal);
    else
        return cal;
}

void push_paras(TreeNode* paras) {
    // 符合栈顺序压元素
    stack<string> ST;
    while (paras) {
        ST.push(string(paras->temp));
        paras = paras->sibling;
    }
    while (!ST.empty()) {   // 逆序
        fprintf(listening, "Para\t%s\n", ST.top().data());
        ST.pop();
    }
}

int func_frame_size(TreeNode *tree, string& vars) {
    /**
     * 该函数用于获取函数帧的大小，方便后续esp的移动，
     @para vars：局部变量在vars中保存
    */
    int frame_size = 0;
    while (tree != NULL) {
        for (int i = 0; i < MAXCHILDREN; ++i) {
            frame_size += func_frame_size(tree->child[i], vars);
        }
        if (tree->nodekind == DecK && tree->kind.dec == VarINTK) {
            int size = (tree->num > 0 ? tree->num : 1);
            frame_size += size;
            sprintf(buff, ".%s,%d|", tree->attr.name, size);
            vars = vars + string(buff);
        }
        tree = tree->sibling;
    }
    return frame_size;
}

void code_generate(TreeNode* tree) {
    while (tree != NULL) {
        for (int i = 0; i < MAXCHILDREN; ++i) {
            code_generate(tree->child[i]);
        }
        if (tree->nodekind == StmtK) {
            tree->temp = NULL;
            switch (tree->kind.stmt) {
            case IfK:
                if (tree->child[2] != NULL) {
                    tree->truelist = newlabel();
                    tree->falselist = newlabel();
                    tree->next = newlabel();
                    tree->qcodes = stringlen(50);
                    sprintf(tree->qcodes, "if\t%s\tgoto\t%s\ngoto\t%s\n", tree->child[0]->temp, tree->truelist, tree->falselist);
                }
                else {
                    tree->truelist = newlabel();
                    tree->next = newlabel();
                    tree->qcodes = stringlen(50);
                    sprintf(tree->qcodes, "if\t%s\tgoto\t%s\ngoto\t%s\n", tree->child[0]->temp, tree->truelist, tree->next);
                }
                break;
            case WhileK:
                tree->truelist = newlabel();
                tree->falselist = newlabel();
                tree->next = newlabel();
                tree->qcodes = stringlen(50);
                sprintf(tree->qcodes, "if\t%s\tgoto\t%s\ngoto\t%s\n", tree->child[0]->temp, tree->truelist, tree->falselist);
                break;
            case AssignK:
                tree->qcodes = stringlen(13);
                sprintf(tree->qcodes, "=\t%s\t%s\n", tree->child[0]->temp, tree->child[1]->temp);
                break;
            case CallK:
                tree->qcodes = stringlen(20);
                if (getType(tree->attr.name, tree->lineno) == Integer) {
                    tree->temp = newtemp();
                    sprintf(tree->qcodes, "=\t%s\tCall\t%s\n", tree->temp, tree->attr.name);
                }
                else {
                    sprintf(tree->qcodes, "Call\t%s\n", tree->attr.name);
                }
                break;
            case ReturnK:
                tree->qcodes = stringlen(20);
                if (tree->child[0])
                    sprintf(tree->qcodes, "ret\t%s\n", tree->child[0]->temp);
                else
                    sprintf(tree->qcodes, "ret\n");
                break;
            case ComK:
                break;
            case ExpsK:
                tree->qcodes = tree->child[0]->qcodes;
                break;
            default:
                break;
            }
        }
        else if (tree->nodekind == ExpK) {
            switch (tree->kind.exp) {
            case OpK:
                tree->temp = newtemp();
                tree->qcodes = gen_qcode(tree->attr.op, tree->temp, tree->child[0]->temp, tree->child[1]->temp);
                break;
            case ConstK:
                tree->temp = integer2string(tree->attr.val);
                tree->qcodes = NULL;
                break;
            case IdK:
                tree->temp = tree->attr.name;
                tree->qcodes = NULL;
                break;
            default:
                break;
            }
        }
        else if (tree->nodekind == DecK) {
            string paras;   // 将所有的参数连接起来，之后使用
            string vars;    // 函数中所有的局部变量保存在此
            int frame_size = 0;
            TreeNode *getparas = NULL;
            switch (tree->kind.dec) {
            case FunINTK:
            case FunVOIDK:
                tree->qcodes = stringlen(40);
                getparas = tree->child[0];
                /// 拼接函数参数
                while (getparas) {
                    paras += "|." + string(getparas->attr.name);
                    getparas = getparas->sibling;
                }
                /// 拼接函数局部变量
                frame_size = func_frame_size(tree, vars);
                /// main函数的入口一定是L0
                if (!strcmp(tree->attr.name, "main"))
                    sprintf(tree->qcodes, "L0\nFunction\t%s|%d\t%s\t%s\n", tree->attr.name, frame_size, paras.data(), vars.data());
                else
                    sprintf(tree->qcodes, "Function\t%s|%d\t%s\t%s\n", tree->attr.name, frame_size, paras.data(), vars.data());
                break;
            case VarK:  // 纯变量 / 数组元素
                if (tree->num == -1) {
                    tree->temp = stringlen(10);
                    sprintf(tree->temp, ".%s", tree->attr.name);
                }
                else {
                    char *t1 = newtemp();
                    tree->qcodes = stringlen(10);
                    sprintf(tree->qcodes, "=\t%s\t%s\n", t1, tree->child[0]->temp);
                    tree->temp = stringlen(10);
                    sprintf(tree->temp, ".%s[%s]", tree->attr.name, t1);
                }
                break;
            case VarINTK:
            case VarVOIDK:
            case ParINTK:
            default:
                break;
            }
        }
        tree = tree->sibling;
    }
}

int ebp_bias = 0;

void _code_dump(TreeNode* tree) {
    while (tree != NULL) {
        if (tree->nodekind == StmtK) {
            switch (tree->kind.stmt) {
            case IfK:
                if (tree->child[2] != NULL) {
                    _code_dump(tree->child[0]);
                    fprintf(listening, "%s", tree->qcodes);
                    fprintf(listening, "%s\n", tree->truelist);
                    _code_dump(tree->child[1]);
                    fprintf(listening, "goto\t%s\n", tree->next);
                    fprintf(listening, "%s\n", tree->falselist);
                    _code_dump(tree->child[2]);
                    fprintf(listening, "%s\n", tree->next);
                }
                else {
                    _code_dump(tree->child[0]);
                    fprintf(listening, "%s", tree->qcodes);
                    fprintf(listening, "%s\n", tree->truelist);
                    _code_dump(tree->child[1]);
                    fprintf(listening, "%s\n", tree->next);
                }
                break;
            case WhileK:
                fprintf(listening, "%s\n", tree->next);
                _code_dump(tree->child[0]);
                fprintf(listening, "%s", tree->qcodes);
                fprintf(listening, "%s\n", tree->truelist);
                _code_dump(tree->child[1]);
                fprintf(listening, "goto\t%s\n", tree->next);
                fprintf(listening, "%s\n", tree->falselist);
                break;
            case AssignK:
                for (int i = 0; i < MAXCHILDREN; ++i)
                    _code_dump(tree->child[i]);
                fprintf(listening, "%s", tree->qcodes);
                break;
            case CallK:
                for (int i = 0; i < MAXCHILDREN; ++i)
                    _code_dump(tree->child[i]);
                if (tree->child[0]) {
                    push_paras(tree->child[0]); // 逆序压栈
                }
                fprintf(listening, "%s", tree->qcodes);
                break;
            case ReturnK:
                for (int i = 0; i < MAXCHILDREN; ++i)
                    _code_dump(tree->child[i]);
                fprintf(listening, "%s", tree->qcodes);
                break;
            case ComK:
            case ExpsK:
                for (int i = 0; i < MAXCHILDREN; ++i)
                    _code_dump(tree->child[i]);
                break;
            default:
                break;
            }
        }
        else if (tree->nodekind == ExpK) {
            switch (tree->kind.exp) {
            case OpK:
                for (int i = 0; i < MAXCHILDREN; ++i)
                    _code_dump(tree->child[i]);
                fprintf(listening, "%s", tree->qcodes);
                break;
            case ConstK:
            case IdK:
            default:
                break;
            }
        }
        else if (tree->nodekind == DecK) {
            switch (tree->kind.dec) {
            case FunINTK:
            case FunVOIDK:
                ebp_bias = 0;   // 用于局部变量参数偏移值计算
                fprintf(listening, "%s", tree->qcodes);
                for (int i = 0; i < MAXCHILDREN; ++i)
                    _code_dump(tree->child[i]);
                break;
            case VarK:
                if (tree->num != -1) {
                    _code_dump(tree->child[0]);
                    fprintf(listening, "%s", tree->qcodes);
                }
                break;
            case VarINTK:
            case VarVOIDK:
            case ParINTK:
            default:
                break;
            }
        }
        tree = tree->sibling;
    }
}

void code_dump(TreeNode *tree) {
    // 程序的入口是main函数，因此增设跳转到main函数的goto L语句
    fprintf(listening, "goto\tL\n");
    _code_dump(tree);
    fprintf(listening, "L\nCall\tmain");
}
