#include <string>

using namespace std;

typedef enum {
    ILT, IBG, ILE, IBE, IEQ, INEQ,  // 逻辑运算
    IASSIGN,    // 赋值
    IPLUS, IMINUS, IMUL, IDIV,  // 算数运算
    IMINUS_RIG, IPLUS_RIG,  // 寄存器指令集
    IIF, ICALL, IRET, IFN, IGOTO, IPARA, IADDR, IALLOC, IERROR
} InstrType;

struct Line {   // 指令单元
    InstrType type;
    string p1, p2, p3;
    Line(InstrType _type, string _p1, string _p2="", string _p3="") {
        type = _type;
        p1 = _p1, p2 = _p2, p3 = _p3;
    }
};

// token标识和名称的互相转换
InstrType instrToken(string ss);
string instrMeans(InstrType type);
