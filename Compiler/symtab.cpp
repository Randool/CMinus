#include "symtab.h"

#include <vector>
#include <set>

/** 符号 */
Symbol::Symbol() {}
Symbol::Symbol(char* name, int type, bool isID, bool isArray, int line) {
    this->name = name;
    this->type = type;
    this->isID = isID;
    this->isArray = isArray;
    this->line = line;
}
void Symbol::addLocations(int line) {
    locations.insert(line);
}
void Symbol::SymbolPrint() {
    printf("name:%-6s\ttype:%-5s\t%-5s\tisArray:%-2d\tline:%-3dlocations:",
        name, typeToString(type), (isID)?"ID":"FUNC", isArray, line
    );
    set<int>::iterator it;
    for (it = locations.begin(); it != locations.end(); it++)
        printf("%3d", *it);
    putchar('\n');
}
const char* Symbol::typeToString(int type) {
    if (type == 262)
        return "INT";
    else if (type == 263)
        return "VOID";
    return "UNDEFINED";
}

/** 作用域深度为deep下所有符号 */
SymTable::SymTable() {}
SymTable::SymTable(int deep, vector<Symbol> mSymTable) {
    this->deep = deep;
    this->mSymTable = mSymTable;
}

vector<Symbol> fieldStack[100]; // 作用域栈
vector<Symbol> lazySymbol;      // 暂存空间
vector<SymTable> SymTables;     // 符号表
int deep = 0;                   // 在哪个作用域内

/** 找到定义的位置，并加入使用的行数 */
bool findDefined(const char* name, bool isID, int deep, int line) {
    for (unsigned i = deep; i >= 0; --i) {
        for (unsigned j = 0; j < fieldStack[i].size(); ++j) {
            if (!strcmp(fieldStack[i][j].name, name) && isID == fieldStack[i][j].isID) {
                fieldStack[i][j].addLocations(line);
                return true;
            }
        }
    }
    printf("[Error] at line %d: %s is used but not be defined.\n", line, name);
    return false;
}

/** 生成符号表 */
void __createSYMTAB(TreeNode* tree) {
    int i;
    bool flag = false;
    while (tree != NULL) {
        flag = false;
        if (tree->nodekind == StmtK)
        {
            switch (tree->kind.stmt)
            {
            case ComK:
                deep++;
                flag = true;
                fieldStack[deep] = lazySymbol;
                lazySymbol.clear();
                break;
            case CallK:
                if (strcmp(tree->attr.name, "input") && strcmp(tree->attr.name, "output")) //排除掉系统函数
                    findDefined(tree->attr.name, 0, deep, tree->lineno);
                break;
            default:
                break;
            }
        }
        else if (tree->nodekind==DecK)  // 如果是声明类型
        {
            switch (tree->kind.dec)
            {
            case VarINTK:
                if (tree->num == -1)
                    fieldStack[deep].push_back(Symbol(tree->attr.name, INT, 1, 0, tree->lineno));
                else
                    fieldStack[deep].push_back(Symbol(tree->attr.name, INT, 1, 1, tree->lineno));
                break;
            case FunINTK:
                fieldStack[deep].push_back(Symbol(tree->attr.name, INT, 0, 0, tree->lineno));
                break;
            case VarVOIDK:
                if (tree->num == -1)
                    fieldStack[deep].push_back(Symbol(tree->attr.name, VOID, 1, 0, tree->lineno));
                else
                    fieldStack[deep].push_back(Symbol(tree->attr.name, VOID, 1, 1, tree->lineno));
                break;
            case FunVOIDK:
                fieldStack[deep].push_back(Symbol(tree->attr.name, VOID, 0, 0, tree->lineno));
                break;
            case ParINTK:
                if (tree->num == -1)
                    lazySymbol.push_back(Symbol(tree->attr.name, INT, 1, 0, tree->lineno));
                else
                    lazySymbol.push_back(Symbol(tree->attr.name, INT, 1, 0, tree->lineno));
                break;
            case ParVOIDK:
                if (tree->num == -1)
                    lazySymbol.push_back(Symbol(tree->attr.name, VOID, 1, 0, tree->lineno));
                else
                    lazySymbol.push_back(Symbol(tree->attr.name, VOID, 1, 1, tree->lineno));
                break;
            case VarK:
                findDefined(tree->attr.name, 1, deep, tree->lineno);
                break;
            default:
                break;
            }
        }
        for (i = 0; i < MAXCHILDREN; ++i) {
            if (tree->child[i] == NULL)
                continue;
            __createSYMTAB(tree->child[i]);
        }
        if (flag) {
            SymTables.push_back(SymTable(deep, fieldStack[deep]));
            deep--;
        }
        tree = tree->sibling;
    }
}

void createSYMTAB(TreeNode* tree) {
    __createSYMTAB(tree);
    SymTables.push_back(SymTable(0, fieldStack[0]));
}

void printSYMTAB() {
    for(unsigned i = 0; i < SymTables.size(); ++i) {
        SymTable &fieldSymTable = SymTables[i];
        vector<Symbol> &symbols = fieldSymTable.mSymTable;

        printf("========Deep is %d========\n", fieldSymTable.deep);
        for(unsigned j = 0; j < symbols.size(); ++j) {
            symbols[j].SymbolPrint();
        }
    }
}

void typeError(TreeNode *t, const char *message) {
    Error = true;
    fprintf(listening, "Type error at line %d: %s\n", t->lineno, message);
}

/** 在符号表中查找，获得对应符号定义的类型 */
Type getType(const char* name, int line) {
    // 系统函数的返回值只可能为整数
    if (!strcmp(name, "input") || !strcmp(name, "output"))
        return Integer;

    for (unsigned i = 0; i < SymTables.size(); ++i) {
        SymTable &fieldSymTable = SymTables[i];
        vector<Symbol> &symbols = fieldSymTable.mSymTable;

        for(unsigned j = 0; j < symbols.size(); ++j) {
            Symbol &sym = symbols[j];

            if (!strcmp(name, sym.name)) {
                for(set<int>::iterator it = sym.locations.begin(); it != sym.locations.end(); it++) {
                    if (line == *it) {
                        if (sym.type == 262) return Integer;
                        else if (sym.type == 263) return Void;
                    }
                }
            }
        }
    }
    return TError;
}

/** 深搜找到函数返回语句 */
Type findReturnKType(TreeNode * t, int deep) {
    if (t == NULL)
        return TError;
    if (t->nodekind == StmtK && t->kind.stmt == ReturnK)
        return t->type;
    Type resultType = TError;
    for (int i = 0; i < MAXCHILDREN; ++i)
    {
        Type fieldStack = findReturnKType(t->child[i], deep+1);
        if (fieldStack != TError) {
            if (resultType == TError)
                resultType = fieldStack;          // 还未得到一个返回值
            else if (resultType != fieldStack) {  // 多个返回值类型不同
                printf("return type error.\n");
                return TError;
            }
        }
    }
    if (deep && t->sibling != NULL) {
        Type fieldStack = findReturnKType(t->sibling, deep);
        if (fieldStack != TError) {
            if (resultType == TError)
                resultType = fieldStack;          // 还未得到一个返回值
            else if (resultType != fieldStack){   // 多个返回值类型不同
                printf("return type error.\n");
                return TError;
            }
        }
    }
    return resultType;
}

void checkNode(TreeNode * t) {
    if (t == NULL)
        return;

    // 后序遍历 首先检查子结点
    for (int i = 0; i < MAXCHILDREN; ++i)
        checkNode(t->child[i]);

    Type type = TError;
    switch(t->nodekind)
    {
    case ExpK:
        switch(t->kind.exp)
        {
        case OpK: // 运算符符号，左右两边类型需要相等
            if (t->child[0]->type != t->child[1]->type)
                typeError(t, "Op applied to different type.");
            if ((t->attr.op == EQ)
                || (t->attr.op == NEQ)
                || (t->attr.op == LT)
                || (t->attr.op == LET)
                || (t->attr.op == GT)
                || (t->attr.op == GET))
                t->type = Boolean;
            else
                t->type = t->child[0]->type;
            break;
        case ConstK:
            t->type = Integer;
            break;
        default:
            break;
        }
        break;
    case StmtK:
        switch(t->kind.stmt)
        {
        case IfK:
            if (t->child[0]->type != Boolean)
                typeError(t->child[0], "If test is not Boolean.");
            break;
        case WhileK:
            if (t->child[0]->type != Boolean)
                typeError(t->child[0], "While test is not Boolean.");
            break;
        case ComK:
            t->type = findReturnKType(t, 0);
            break;
        case ReturnK:
            if (t->child[0] != NULL) //有返回值
                t->type = t->child[0]->type;
            else
                t->type = Void;
            break;
        case AssignK:
            if (t->child[0]->type != t->child[1]->type)
                typeError(t, "Assign applied to different type.");
            break;
        case CallK:
            type = getType(t->attr.name, t->lineno);
            if (type != TError)
                t->type = type;
            else
                printf("line %d: %s is used but not be defined.\n", t->lineno, t->attr.name);
            break;
        default:
            break;
        }
        break;
    case DecK:
        switch(t->kind.dec)
        {
        case VarINTK:
            t->type = Integer;
            break;
        case FunINTK:
            if (t->child[1]->type != Integer)
                typeError(t, "Integer Func's return is not Integer.");
            break;
        case VarVOIDK:
            t->type = Void;
            break;
        case FunVOIDK:
            if (t->child[1]->type != Void)
                typeError(t, "Void Func's return is not Void.");
            break;
        case ParINTK:
            t->type = Integer;
            break;
        case ParVOIDK:
            t->type = Void;
            break;
        case VarK:
            type = getType(t->attr.name, t->lineno);
            if (type != TError)
                t->type = type;
            else
                printf("line %d: %s is used but not be defined.\n", t->lineno, t->attr.name);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    if (t->sibling != NULL)
        checkNode(t->sibling);
}

