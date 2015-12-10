//Bicolored Horses.
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
bitset<500> color;
int dp[501][501];//[pos][stablesLeft]

int Dyn(int pos, int stablesLeft) {
    if (!stablesLeft)
        return pos >= n ? 0 : (int)1e6;
    if (pos >= n)
        return (int)1e6;
    if (dp[pos][stablesLeft] != -1)
        return dp[pos][stablesLeft];
    int result = INT_MAX;
    int black = 0, white = 0;
    for (int i = pos; i <= n - stablesLeft; i++) {
        if (color[i])
            black++;
        else
            white++;
        result = min(result, Dyn(i + 1, stablesLeft - 1) + black * white);
    }
    return (dp[pos][stablesLeft] = result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, k;
    while (cin >> n >> k) {
        for (i = 0; i < n; i++) {
            bool b;
            cin >> b;
            color[i] = b;
        }
        memset(dp, 0xFF, sizeof dp);
        cout << Dyn(0, k) << '\n';
    }
}
