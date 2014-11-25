//K-ичные числа.
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

int n, k;
llong dp[17][2];//[pos][prevZero]

llong Dyn(int pos, bool zero) {
    if (pos >= n)
        return 1;
    llong result = (k - 1) * Dyn(pos + 1, false);
    if (!zero)
        result += Dyn(pos + 1, true);
    return (dp[pos][zero] = result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n >> k) {
        memset(dp, 0x00, sizeof dp);
        cout << Dyn(0, true) << '\n';
    }
}
