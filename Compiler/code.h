#ifndef CODE_H
#define CODE_H

#include "globals.h"

/// 用于生成中间代码
void code_generate(TreeNode* root);
void code_dump(TreeNode* tree);

/// 用于生成机器码
void gen_machine_code(char *qcdFile);

#endif // CODE_H
