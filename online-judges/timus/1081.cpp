//Двоичная последовательность.
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

llong dp[45][2];

llong SizeDyn(int n, bool prevZero = true) {
    if (!n)
        return 1;
    if (dp[n][prevZero] != -1)
        return dp[n][prevZero];
    llong result = SizeDyn(n - 1, true);
    if (prevZero)
        result += SizeDyn(n - 1, false);
    return (dp[n][prevZero] = result);
}

int n;

void Print(int k) {
    if (k >= SizeDyn(n)) {
        cout << "-1\n";
        return;
    }
    for (int i = n - 1; i >= 0; i--)
        if (k < SizeDyn(i))
            cout << '0';
        else {
            cout << '1';
            k -= SizeDyn(i);
        }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    while (cin >> n >> k) {
        k--;
        memset(dp, 0xFF, sizeof dp);
#       ifdef _DEBUG
            for (int i = 0; i <= k; i++)
                Print(i);
            debug << '\n';
#       else
            Print(k);
#       endif
    }
}
