//Метро.
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

const double SIDE_LENGTH = 100.;
const double DIAGONAL_LENGTH = SIDE_LENGTH * sqrt(2.);

int n, m;
double dp[1001][1001];
bitset<1001> diagonal[1001];

double Dyn(int i, int j) {
    if (i >= n && j >= m)
        return .0;
    if (dp[i][j] > .0)
        return dp[i][j];
    double result = DBL_MAX;
    if (i < n)
        result = min(result, Dyn(i + 1, j) + SIDE_LENGTH);
    if (j < m)
        result = min(result, Dyn(i, j + 1) + SIDE_LENGTH);
    if (diagonal[i][j])
        result = min(result, Dyn(i + 1, j + 1) + DIAGONAL_LENGTH);
    return (dp[i][j] = result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;
    while (cin >> n >> m) {
        for (i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                dp[i][j] = -1.;
            diagonal[i].reset();
        }
        int k;
        cin >> k;
        while (k--) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            diagonal[a][b] = true;
        }
        cout << lrint(Dyn(0, 0)) << '\n';
    }
}
