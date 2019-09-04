#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <iostream>
using namespace std;

#include "globals.h"

#include <set>
#include <vector>
using namespace std;

/** ���� */
struct Symbol {
    char* name;
    int type;
    bool isID;      // �Ƿ��Ǳ�����trueΪ������falseΪ����
    bool isArray;   // �Ƿ������飬trueΪ�ǣ�falseΪ��
    int line;
    set<int> locations; // �õ��ĵط�

    Symbol();
    Symbol(char* name, int type, bool isID, bool isArray, int line);
    void addLocations(int line);
    void SymbolPrint();
    const char* typeToString(int type);
};

/** ���������Ϊdeep�����з��� */
struct SymTable {
    int deep;
    vector<Symbol> mSymTable;
    SymTable();
    SymTable(int deep, vector<Symbol> mSymTable);
};

extern vector<SymTable> SymTables;

/** ���ɷ��ű� */
void createSYMTAB(TreeNode* tree);

/** ��ӡ���ű� */
void printSYMTAB(void);

/** ��� */
void checkNode(TreeNode* tree);

/** ���Ҷ��� */
Type getType(const char* name, int line);
#endif
