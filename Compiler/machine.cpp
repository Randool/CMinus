/**
读取中间代码，生成机器码
主要包括寄存器分配

假定有x个寄存器
*/
#include "code.h"
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#define MAXLINE 128
#define PAUSE_EXIT(eno) {system("pause"); exit(eno);}

char codeFile[128];
char buff[MAXLINE]; // 任意使用

struct Line {
    InstrType type;
    string p1, p2, p3;
    Line(InstrType _type, string _p1, string _p2="", string _p3="") {
        type = _type;
        p1 = _p1, p2 = _p2, p3 = _p3;
    }
};
vector<Line> instructions;
int cnt_line = 0;       // 记录每一行的地址

inline void push_instruction(InstrType type, string p1, string p2="", string p3="") {
    instructions.push_back(Line(type, p1, p2, p3));
    ++cnt_line;
}

string tmp, p1, p2, p3; // 保存四元式的参数
map<string, int> msi;   // 用于标记地址跳转
map<string, string> mss;    // 用于地址映射

InstrType instrToken(string ss) {
    if (ss == "<") return ILT;
    if (ss == ">") return IBG;
    if (ss == "<=") return ILE;
    if (ss == ">=") return IBE;
    if (ss == "==") return IEQ;
    if (ss == "!=") return INEQ;
    if (ss == "=") return IASSIGN;
    if (ss == "+") return IPLUS;
    if (ss == "-") return IMINUS;
    if (ss == "*") return IMUL;
    if (ss == "/") return IDIV;
    if (ss == "if") return IIF;
    if (ss == "Call") return ICALL;
    if (ss == "ret") return IRET;
    if (ss == "Function") return IFN;
    if (ss == "goto") return IGOTO;
    if (ss == "Para") return IPARA;
    if (ss[0] == 'L') return IADDR;  //跳转地址
    return IERROR;
}

int string2int(string s) {
    int num = 0, p = 0;
    for (string::iterator x = s.begin(); x != s.end(); ++x) {
        if (*x == '-') p = 1;
        else num = num * 10 + (*x - '0');
    }
    return p ? -num : num;
}

inline int regist_paras(string& fn_name_size, string& paras, string& vars) {
    /**
     * 函数参数获取指令
    */
    if (paras.empty() || paras == "|.void") paras.clear();

    // 添加函数声明、函数栈空间申请
    int idx = fn_name_size.find("|", 0);
    string fn_name = fn_name_size.substr(0, idx);
    string frame_size = fn_name_size.substr(idx + 1);
    push_instruction(IFN, fn_name);
    push_instruction(IMINUS_RIG, frame_size, "%esp");   // 占位

    // 增加函数名和跳转地址的映射
    sprintf(buff, "%d", instructions.size()-1);
    mss[fn_name] = string(buff);

    // 添加参数
    int cnt = 1;
    for (int i=0, len=paras.length(); i < len; ++i)
        if (paras[i] == '|') ++cnt;
    for (int idx = paras.length(), sufx=paras.length(); idx >= 0; --idx) {
        if (paras[idx] == '|') {
            sprintf(buff, "%%ebp|%d", cnt--);
            mss[paras.substr(idx+1, sufx-idx)] = string(buff);
            sufx = idx - 1;
        }
    }
    // 添加局部变量
    for (int ebp_bias = 1, pre = 0, idx = 0, len = vars.length(); idx < len; ++idx) {
        if (vars[idx] == '|') {
            sprintf(buff, "%%ebp|%d", -ebp_bias);
            int comma = vars.find(",", pre);
            string var = vars.substr(pre, comma - pre);
            if (mss[var] == "") mss[var] = string(buff);
            ebp_bias += string2int(vars.substr(comma + 1, idx - comma - 1));
            pre = idx + 1;
        }
    }
    return string2int(frame_size);
}

inline void cancel_paras(string& paras, string vars) {
    /**
     *  取消当前作用域中的变量映射   // 可能会导致全局变量的覆盖
    */
    for (int idx = paras.length(), sufx=paras.length(); idx >= 0; --idx) {
        if (paras[idx] == '|') {
            mss[paras.substr(idx+1, sufx-idx)] = "";
            sufx = idx - 1;
        }
    }
    for (int ebp_bias = 1, pre = 0, idx = 0, len = vars.length(); idx < len; ++idx) {
        if (vars[idx] == '|') {
            sprintf(buff, "%%ebp|%d", -ebp_bias);
            int comma = vars.find(",", pre);
            mss[vars.substr(pre, comma - pre)] = "";
            ebp_bias += string2int(vars.substr(comma + 1, idx - comma - 1));
            pre = idx + 1;
        }
    }
}

string modified(string& para, int& frame_size) {
    /**
     * 1、将参数转化对应栈帧地址
     * 2、将临时寄存器转化为对应的栈帧地址
    */
    string ans = mss[para];
    if (!ans.empty()) return ans;

    int reg_idx = para.find('@');

    if (reg_idx == 0) { // 参数直接可映射
        ++frame_size;
        sprintf(buff, "%%ebp|%d", -frame_size);
        string addr = string(buff);
        mss[para] = addr;
        return addr;
    }
    if (reg_idx != -1) {
        string reg = para.substr(reg_idx, para.length() - reg_idx - 1);
        if (mss[reg].empty()) {
            ++frame_size;
            sprintf(buff, "%%ebp|%d", -frame_size);
            string addr = string(buff);
            mss[reg] = addr;
            push_instruction(IASSIGN, "%eax", addr.data());
        }
    }
    if (para[0] == '.') {   // .a[@T2]
        int lft_brkt = para.find('[');
        string var = mss[para.substr(0, lft_brkt)]; // .a ==> %ebp|xx
        string reg = mss[para.substr(lft_brkt+1, para.length()-lft_brkt-2)];    // @T2 ==> %ebp|xx
        // 分裂数组取值操作
        push_instruction(IASSIGN, "%eax", reg);
        push_instruction(IMINUS_RIG, var.substr(5), "%eax");
        push_instruction(IMINUS, "0", "%eax", "%eax");
        return string("%ebp|%eax");
    }
    return para;
}

void read_qcd(char *qcdFile) {
    /**
     * 除了读取qcd文件的任务，
     * 同时完成跳转地址的解析，
     * 解析函数参数，并完成函数参数、局部变量的地址修改
     * 完成寄存器的分配——Spill to memory
     */
    if (qcdFile == NULL) {
        fprintf(stderr, "[Error]\tThe qcd file should be specified\n");
        PAUSE_EXIT(-1);
    }

    ifstream source(qcdFile);
    if (source == NULL) {
        fprintf(stderr, "[Error]\tCannot open qcd file '%s'\n", qcdFile);
        PAUSE_EXIT(-1);
    }

    stringstream ss;    // 使用输入输出流分割参数
    string paras;       // 保存当前函数的变量
    string vars;        // 保存当前函数的局部变量
    int frame_size = 0;
    vector<int> frame_sizes;

    while (source.getline(buff, MAXLINE)) {
        ss << string(buff);
        tmp.clear(), p1.clear(), p2.clear(), p3.clear();
        ss >> tmp >> p1 >> p2 >> p3;
        ss.clear();
        if (tmp.empty()) continue;

        InstrType type = instrToken(tmp);
        switch (type) {
        case IADDR:
            // 跳转地址为辅助变量，实际上并不会插入到代码中
            msi[tmp] = cnt_line;
            break;
        case IFN:
            frame_sizes.push_back(frame_size);  // 记录上一个函数的真实帧大小
            cancel_paras(paras, vars);  // 取消上一个函数的参数映射
            paras = p2;
            vars = p3;
            frame_size = regist_paras(p1, paras, vars);  // 新增当前函数的参数映射
            break;
        default:
            // 函数参数转换
            p1 = modified(p1, frame_size);
            p2 = modified(p2, frame_size);
            p3 = modified(p3, frame_size);
            if (p2 == "Call") { // 保证函数返回值一定保存到寄存器%eax中
                push_instruction(ICALL, p3);
                push_instruction(IASSIGN, p1, "%eax");
            }
            else {
                push_instruction(type, p1, p2, p3);
            }
        }
    }
    frame_sizes.push_back(frame_size);
    source.close();
    fprintf(stderr, "[Info]\tLoading qcd file done. Total line: %d\n", instructions.size());

    // 绝对地址映射
    for (int i = 0, size = instructions.size(), fn_cnt = 1; i < size; ++i) {
        Line &line = instructions[i];
        switch (line.type) {
        case IIF:
            sprintf(buff, "%d", msi[line.p3]);
            line.p3 = string(buff);
            break;
        case IGOTO:
            sprintf(buff, "%d", msi[line.p1]);
            line.p1 = string(buff);
            break;
        case IFN:
            sprintf(buff, "%d", frame_sizes[fn_cnt++]);
            instructions[i+1].p1 = string(buff);
            break;
        default:
            break;
        }
        // 输出到stderr，防止打印出tab，使用if-else判断
//        if (line.p2.empty()) fprintf(stderr, "%3d:\t%d\t%s\n", i, line.type, line.p1.data());
//        else if (line.p3.empty()) fprintf(stderr, "%3d:\t%d\t%s\t%s\n", i, line.type, line.p1.data(), line.p2.data());
//        else fprintf(stderr, "%3d:\t%d\t%s\t%s\t%s\n", i, line.type, line.p1.data(), line.p2.data(), line.p3.data());
    }
}

void gen_machine_code(char *qcdFile) {
    // 读取并处理qcd文件
    read_qcd(qcdFile);

    // 打开写入文件
    strncpy(codeFile, pgm, strcspn(qcdFile, "."));
    strcat(codeFile, ".mc");
    listening = fopen(codeFile, "w");
    if (listening == NULL) {
        fprintf(stderr, "[Error]\tUnable to open %s\n", codeFile);
        PAUSE_EXIT(-1);
    }

    // 开始写入
    for (int i = 0, size = instructions.size(); i < size; ++i) {
        Line &line = instructions[i];
        // 输出到listening，防止打印出无用tab，使用if-else判断
        if (line.p2.empty()) fprintf(listening, "%d\t%s\n", line.type, line.p1.data());
        else if (line.p3.empty()) fprintf(listening, "%d\t%s\t%s\n", line.type, line.p1.data(), line.p2.data());
        else fprintf(listening, "%d\t%s\t%s\t%s\n", line.type, line.p1.data(), line.p2.data(), line.p3.data());
    }
    fclose(listening);
    fprintf(stderr, "[Info]\tMachine code has been written into %s.\n", codeFile);
}
