#include "globals.h"

#define NO_PARSE    false
#define NO_ANALYZE  false
#define NO_CODE     false
#define PAUSE_EXIT(eno) {system("pause"); exit(eno);}

extern "C" {
#include "util.h"
#include "parse.h"
}

#include "symtab.h"
#include "code.h"

/* allocate global variables */
int lineno = 0;
FILE *source;
FILE *listening;
FILE *code;

/* allocate and set tracing flags */
int TraceScan   = false;
int TraceParse  = false;
int TraceTable  = false;
int TraceQcode  = false;
//int TraceMcode  = true;
int Error       = false;

char pgm[128];      // c minus file
char qcdFile[128];  // 中间代码（qcd）文件

TreeNode *syntaxTree;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("File > ");
        scanf("%s", pgm);
    }
    else if (argc >= 2) {
        strcpy(pgm, argv[1]);
    }

    if (strchr(pgm, '.') == NULL)
        strcat(pgm, ".c");

    /** 尝试打开文件 */
    source = fopen(pgm, "r");
    if (source == NULL) {
        fprintf(stderr, "[Error]\tFile %s not found\n", pgm);
        PAUSE_EXIT(-1);
    }
    listening = stdout;
    fprintf(stderr, "[Info]\tCMinus COMPILATION: %s\n", pgm);
    syntaxTree = parse();
    fclose(source);

    if (Error) {
        PAUSE_EXIT(-2);
    }

    if (TraceParse) {
        fprintf(stderr, "[Info]\tSyntax tree:\n");
        printTree(syntaxTree);
    }

    fprintf(stderr, "[Info]\tCreating symbol tables...\n");
    createSYMTAB(syntaxTree);

    if (Error) {
        PAUSE_EXIT(-3);
    }

    if (TraceTable) printSYMTAB();

    fprintf(stderr, "[Info]\tChecking nodes...\n");
    checkNode(syntaxTree);

    if (Error) {
        PAUSE_EXIT(-4);
    }

    /** 构建语法树 */
    fprintf(stderr, "[Info]\tGenerating qcd codes...\n");
    code_generate(syntaxTree);

    /** 中间代码生成 */
    fprintf(stderr, "[Info]\tWriting qcd code into file or console...\n");
    int fnlen = 0;
    if (!TraceQcode) {  // 直接输出到文件
        fnlen = strcspn(pgm, ".");
        strncpy(qcdFile, pgm, fnlen);
        strcat(qcdFile, ".qcd");
        listening = fopen(qcdFile, "w");
        if (listening == NULL) {
            fprintf(stderr, "[Error]\tUnable to open %s\n", qcdFile);
            PAUSE_EXIT(-1);
        }
        code_dump(syntaxTree);
        fclose(listening);
    }
    else {
        listening = stdout;
        code_dump(syntaxTree);
        printf("\n\n");
    }

    /** 目标代码生成 */
    fprintf(stderr, "[Info]\tWriting machine code into file or console...\n");
    gen_machine_code(qcdFile);

    system("pause");
    return 0;
}

