#include "token.h"
#include "assist.h"

#include <bits/stdc++.h>
using namespace std;

#define STACKSIZE 4096
#define DEBUG 0
#define PAUSE_EXIT(eno) {system("pause"); exit(eno);}

vector<Line> instructions;  // 程序加载之后放在这里，免去了栈溢出的困扰
//map<string, int> regist;    // 暂时先用map代替寄存器分配
int STACK[STACKSIZE];
int eip = 0;    // 程序指针
int ebp = STACKSIZE-1;    // 栈底指针
int esp = STACKSIZE-1;    // 栈顶指针
int eax = 0;    // eax寄存器
int tmp;

void load(string filename) {
    /** 加载文件 */
    ifstream source(filename.data());
    if (!source) {
        fprintf(stderr, "[Error]\tFile %s not found\n", filename.data());
        system("pause");
        exit(-1);
    }
    string line;
    stringstream ss;
    while (getline(source, line)) {
        ss.clear();
        ss << line;
        int type;
        string p1, p2, p3;
        ss >> type >> p1 >> p2 >> p3;
        instructions.push_back(Line((InstrType)type, p1, p2, p3));
    }
}

int regist(string &reg) {
    switch (reg[2]) {
        case 'a': return eax;
        case 'b': return ebp;
        case 's': return esp;
        default : PAUSE_EXIT(111);
    }
    return 0;
}

int read(string &x) {
    if (is_digit(x)) {
        #if DEBUG
        cout << "\t" << x << " = " << string2int(x) << endl;
        #endif // DEBUG
        return string2int(x);
    }

    int pipe = x.find('|');
    if (pipe == -1) {
        #if DEBUG
        cout << "\t" << x << " = " << regist(x) << endl;
        #endif // DEBUG
        return regist(x);
    }

    string base = x.substr(0, pipe), bias = x.substr(pipe + 1);
    int _base = 0, _bias = 0;
    switch (base[0]) {
        case '%':   _base = regist(base); break;
        case '&':   _base = string2int(base.substr(1)); break;
        default:    PAUSE_EXIT(222);
    }
    switch (bias[0]) {
        case '%': _bias = regist(bias); break;
        default:  _bias = string2int(bias); break;
    }
    #if DEBUG
    cout << "\t" << x << " = " << "STACK[" << _base << " + " << _bias << "] = " << STACK[_base + _bias] << endl;
    #endif // DEBUG
    return STACK[_base + _bias];
}

inline void write(string &x, int value) {
    int pipe = x.find('|');
    if (pipe == -1) {
        #if DEBUG
        cout << "\t" << x << " = " << value << endl;
        #endif // DEBUG
        switch (x[0]) {
            case '%':
                switch (x[2]) {
                    case 'a': eax = value; break;
                    case 'b': ebp = value; break;
                    case 's': esp = value; break;
                    default: PAUSE_EXIT(333);
                }
                break;
            case '&':
                STACK[string2int(x.substr(1))] = value;
                break;
        }
    }
    else {
        string base = x.substr(0, pipe), bias = x.substr(pipe + 1);
        int _base = 0, _bias = 0;
        switch (base[0]) {
            case '%':   _base = regist(base); break;
            case '&':   _base = string2int(base.substr(1)); break;
            default:    PAUSE_EXIT(444);
        }
        switch (bias[0]) {
            case '%': _bias = regist(bias); break;
            default:  _bias = string2int(bias); break;
        }
        #if DEBUG
        cout << "\t" << x << " = " << "STACK[" << _base << " + " << _bias << "] = " << value << endl;
        #endif // DEBUG
        STACK[_base + _bias] = value;
    }
}

int main(int argc, char *argv[]) {
    fprintf(stderr, "==== Welcome to TM ====\n");

    string pgm;
    if (argc == 1) {
        fprintf(stderr, "File > ");
        cin >> pgm;
    }
    else if (argc >= 2) {
        pgm = string(argv[1]);
    }

    load(pgm); /** 打开并加载程序 */

    /** 图灵机模拟 */
    int len = instructions.size();
    for (eip = 0; eip < len; ) {
        Line& line = instructions[eip];
        InstrType type = line.type;
        string &p1 = line.p1, &p2 = line.p2, &p3 = line.p3;
        if (p1.empty()) break;  // 程序终止

#if DEBUG
        fprintf(stderr, "%4d>\t%s\t%s\t%s\t%s\n", eip, instrMeans(type).data(), p1.data(), p2.data(), p3.data());
#endif // DEBUG

        if (type == IGOTO) eip = string2int(line.p1);
        else {
            switch(type) {  // 指令集真是麻烦
            /// 逻辑运算    < a b T1
            case ILT:   write(p3, (int)(read(p1) < read(p2))); ++eip; break;
            case IBG:   write(p3, (int)(read(p1) > read(p2))); ++eip; break;
            case ILE:   write(p3, (int)(read(p1) <= read(p2))); ++eip; break;
            case IBE:   write(p3, (int)(read(p1) >= read(p2))); ++eip; break;
            case IEQ:   write(p3, (int)(read(p1) == read(p2))); ++eip; break;
            case INEQ:  write(p3, (int)(read(p1) != read(p2))); ++eip; break;
            /// 赋值
            case IASSIGN:   write(p1, read(p2)); ++eip; break;
            /// 算数运算
            case IPLUS:     write(p3, read(p1) + read(p2)); ++eip; break;
            case IMINUS:    write(p3, read(p1) - read(p2)); ++eip; break;
            case IMUL:      write(p3, read(p1) * read(p2)); ++eip; break;
            case IDIV:      write(p3, read(p1) / read(p2)); ++eip; break;
            /// 寄存器指令集
            case IMINUS_RIG:    // -r   n   %x
                switch (p2[2]) {
                case 'a':   eax -= string2int(p1); break;
                case 'b':   ebp -= string2int(p1); break;
                case 's':   esp -= string2int(p1); break;
                default:    break;
                }
                ++eip;
                break;
            case IPLUS_RIG:
                switch (p2[2]) {
                case 'a':   eax += string2int(p1); break;
                case 'b':   ebp += string2int(p1); break;
                case 's':   esp += string2int(p1); break;
                default:    break;
                }
                ++eip;
                break;
            /// 其他指令
            case IIF:       // 判断并跳转
                if (!read(p1)) ++eip;
                else eip = string2int(p3);
                break;
            case ICALL:     // 函数调用，需要将被调用者压栈
                if (p1 == "input") {
                    printf("input >>> ");
                    scanf("%d", &eax);
                    ++eip;
                }
                else if (p1 == "output") {
                    printf("output >>> %d\n", STACK[esp++]);
                    ++eip;
                }
                else {  // 正常的函数调用
                    STACK[--esp] = eip;
                    STACK[--esp] = ebp;
                    ebp = esp;
                    eip = string2int(p1);
                }
                break;
            case IRET:      // 函数返回，需要将被调用者退栈
                if (!p1.empty()) eax = read(p1);
                esp = ebp;
                ebp = STACK[ebp];
                eip = STACK[++esp] + 1; // 返回调用之后的下一条指令
                ++esp;
                break;
            case IFN:       // 函数提示而已
                ++eip; break;
            case IPARA:     // 压入参数
                if (is_digit(p1))
                    STACK[--esp] = string2int(p1);
                else if (p1[0] == '&')
                    STACK[--esp] = string2int(p1.substr(1));
                else
                    STACK[--esp] = read(p1);
                ++eip;
                break;
            case IALLOC:
                esp -= string2int(p1);
                ebp -= string2int(p1);
                ++eip;
                break;
            default:
                break;
            }
        }
    }
    fprintf(stderr, "==== Program terminated ====\n");

    return 0;
}
