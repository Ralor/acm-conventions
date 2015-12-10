//Malevich Strikes Back!
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
vector<vector<bool>> canvas;
vector<vector<int>> seq;

int Seq(int i, int j) {
    if (i >= n || j >= n)
        return 0;
    if (j == n - 1)
        return canvas[i][j] ? 1 : -1;
    if (seq[i][j])
        return seq[i][j];
    int next = Seq(i, j + 1);
    int result;
    if (canvas[i][j])
        if (next > 0)
            result = next + 1;
        else
            result = 1;
    else
        if (next < 0)
            result = next - 1;
        else
            result = -1;
    return (seq[i][j] = result);
}

int Check(int y, int x) {
    int first = Seq(y, x);
    int side = (first << 1) + 1;
    if (first <= 0)
        return 0;
    if (Seq(y, x + first) != -1)
        return 0;
    if (Seq(y, x + first + 1) < first)
        return 0;
    for (int k = first - 1, i = 1; k; k--, i++) {
        if (Seq(y + i, x) != k)
            return 0;
        if (Seq(y + i, x + k) != -((i << 1) + 1))
            return 0;
        if (Seq(y + i, x + side - k) < k)
            return 0;
    }
    if (Seq(y + first, x) > -side)
        return 0;
    for (int k = 1; k <= first; k++) {
        if (Seq(y + first + k, x) != k)
            return 0;
        if (Seq(y + first + k, x + k) != -(side - (k << 1)))
            return 0;
        if (Seq(y + first + k, x + side - k) < k)
            return 0;
    }
    return side;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n, n) {
        canvas.resize(n);
        seq.assign(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            canvas[i].resize(n);
            for (int j = 0; j < n; j++) {
                bool b;
                cin >> b;
                canvas[i][j] = b;
            }
        }
        int result = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result = max(result, Check(i, j));
        if (result)
            cout << result << '\n';
        else
            cout << "No solution\n";
    }
}
