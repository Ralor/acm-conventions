//Кривые зеркала.
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

int n;
int v[20];
int dp[1 << 20];//[mask] = damage

int Count(int mask) {
    int result = 0;
    for (int i = 0; i < n; i++)
        if (mask & (1 << i))
            result += v[i];
    return result;
}

int Dyn(int mask) {
    if (!mask)
        return 0;
    if (dp[mask] != -1)
        return dp[mask];
    int result = dp[mask] = 100000;
    int next;
    for (int i = 0; i < n - 2; i++) {
        next = mask & ~(0x7 << i);
        result = min(result, Dyn(next) + Count(next));
    }
    next = mask & ~(0x1 | 0x3 << (n - 2));
    result = min(result, Dyn(next) + Count(next));
    next = mask & ~(0x3 | 0x1 << (n - 1));
    result = min(result, Dyn(next) + Count(next));
    return (dp[mask] = result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n) {
        for (int i = 0; i < n; i++)
            cin >> v[i];
        memset(dp, 0xFF, sizeof dp);
        cout << Dyn((1 << n) - 1) << '\n';
    }
}
