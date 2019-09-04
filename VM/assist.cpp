#include "assist.h"

#include <string>
using namespace std;

bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

bool is_digit(string c) {
    for (int idx=0, len=c.length(); idx < len; ++idx) {
        if (idx == 0 && c[idx] == '-') continue;
        if (c[idx] < '0' || c[idx] > '9') return false;
    }
    return true;
}

int string2int(string s) {
    int num = 0, p = 0;
    for (string::iterator x = s.begin(); x != s.end(); ++x) {
        if (*x == '-') p = 1;
        else num = num * 10 + (*x - '0');
    }
    return p ? -num : num;
}
