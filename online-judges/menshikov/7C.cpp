#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifndef _DEBUG
#   undef VERBOSE
#endif

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    const char* stanWins = "Stan wins.\n";
    const char* wins = stanWins + 4;
    const char* ollie = "Ollie";
    uint n;
    while (cin >> n) {
        int f = 9;
        while (n > 1) {
            bool b = n % f;
            n /= f;
            if (b)
                n++;
            f = f == 9 ? 2 : 9;
        }
        if (f == 2)
            cout << stanWins;
        else
            cout << ollie << wins;
    }
}
