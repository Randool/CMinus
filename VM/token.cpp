#include "token.h"

#include <string>
using namespace std;

InstrType instrToken(string ss) {
    // 逻辑运算
    if (ss == "<")  return ILT;
    if (ss == ">")  return IBG;
    if (ss == "<=") return ILE;
    if (ss == ">=") return IBE;
    if (ss == "==") return IEQ;
    if (ss == "!=") return INEQ;
    // 赋值运算
    if (ss == "=")  return IASSIGN;
    // 算数运算
    if (ss == "+")  return IPLUS;
    if (ss == "-")  return IMINUS;
    if (ss == "*")  return IMUL;
    if (ss == "/")  return IDIV;
    // 寄存器指令集
    if (ss == "-r") return IMINUS_RIG;
    if (ss == "+r") return IPLUS_RIG;
    // 其他指令
    if (ss == "if")     return IIF;
    if (ss == "Call")   return ICALL;
    if (ss == "ret")    return IRET;
    if (ss == "Function") return IFN;
    if (ss == "goto")   return IGOTO;
    if (ss == "Para")   return IPARA;
    if (ss == "IALLOC") return IALLOC;
    if (ss[0] == 'L')   return IADDR;  //跳转地址
    return IERROR;
}

string instrMeans(InstrType type) {
    switch(type) {
    // 逻辑运算
    case ILT:   return "<";
    case IBG:   return ">";
    case ILE:   return "<=";
    case IBE:   return ">=";
    case IEQ:   return "==";
    case INEQ:  return "!=";
    // 赋值运算
    case IASSIGN:   return "=";
    case IPLUS:     return "+";
    case IMINUS:    return "-";
    case IMUL:      return "*";
    case IDIV:      return "/";
    // 寄存器指令集
    case IMINUS_RIG:    return "-r";
    case IPLUS_RIG:     return "+r";
    // 其他指令
    case IIF:   return "if";
    case ICALL: return "Call";
    case IRET:  return "ret";
    case IFN:   return "Function";
    case IGOTO: return "goto";
    case IPARA: return "Para";
    case IADDR: return "LLLL";
    case IALLOC: return "IALLOC";
    case IERROR:
    default: return "";
    }
}
