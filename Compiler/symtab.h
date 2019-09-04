#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <iostream>
using namespace std;

#include "globals.h"

#include <set>
#include <vector>
using namespace std;

/** 符号 */
struct Symbol {
    char* name;
    int type;
    bool isID;      // 是否是变量，true为变量，false为函数
    bool isArray;   // 是否是数组，true为是，false为否
    int line;
    set<int> locations; // 用到的地方

    Symbol();
    Symbol(char* name, int type, bool isID, bool isArray, int line);
    void addLocations(int line);
    void SymbolPrint();
    const char* typeToString(int type);
};

/** 作用域深度为deep下所有符号 */
struct SymTable {
    int deep;
    vector<Symbol> mSymTable;
    SymTable();
    SymTable(int deep, vector<Symbol> mSymTable);
};

extern vector<SymTable> SymTables;

/** 生成符号表 */
void createSYMTAB(TreeNode* tree);

/** 打印符号表 */
void printSYMTAB(void);

/** 检查 */
void checkNode(TreeNode* tree);

/** 查找定义 */
Type getType(const char* name, int line);
#endif
