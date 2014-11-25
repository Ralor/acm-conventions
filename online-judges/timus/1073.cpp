//Квадратная страна.
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

int dp[60001];

int Dyn(int n) {
    if (!n)
        return 0;
    if (dp[n] != -1)
        return dp[n];
    int result = INT_MAX;
    for (int i = 1; i * i <= n; i++)
        result = min(result, Dyn(n - i * i));
    return (dp[n] = result + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        memset(dp, 0xFF, sizeof dp);
        cout << Dyn(n) << '\n';
    }
}
