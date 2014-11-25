//Лестницы.
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

llong dp[502][502];//[height][left]

llong Dyn(int height, int left) {
    if (!left)
        return 1;
    if (left <= height)
        return 0;
    if (dp[height][left] != -1)
        return dp[height][left];
    llong result = 0;
    for (int next = height + 1; next <= left; next++)
        result += Dyn(next, left - next);
    return (dp[height][left] = result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        memset(dp, 0xFF, sizeof dp);
        llong result = 0;
        for (int first = 1; first < (n + 1) >> 1; first++)
            result += Dyn(first, n - first);
        cout << result << '\n';
    }
}
