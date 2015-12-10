//Научная конференция.
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

struct Report {
    int start, end;

    Report() { }
    Report(int a, int b): start(a), end(b) { }
};

int n;
vector<Report> v;
int dp[100000];//[pos]

int Dyn(int pos) {
    if (pos >= n)
        return 0;
    if (dp[pos] != -1)
        return dp[pos];
    int result = Dyn(pos + 1);
    result = max(result,
        Dyn(upper_bound(begin(v) + pos, end(v), v[pos].end,
            [ ](int a, const Report& b) {
                return a < b.start;
            }
        ) - begin(v)) + 1
    );
    return (dp[pos] = result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n) {
        v.clear();
        v.resize(n);
        memset(dp, 0xFF, sizeof dp);
        for (auto& r: v)
            cin >> r.start >> r.end;
        sort(begin(v), end(v),
            [ ](const Report& a, const Report& b) {
                return a.start < b.start;
            }
        );
        cout << Dyn(0) << '\n';
    }
}
