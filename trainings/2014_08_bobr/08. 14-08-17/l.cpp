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
#ifdef _DEBUG
#   include <conio.h>
#endif

#ifndef _DEBUG
#   undef VERBOSE
#endif

#define eps      1e-8
#define inf      (1000 * 1000 * 1000)
#define linf     (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)   ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)    int((x).size())
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define mp       make_pair

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;

struct DpResult {
    bool valid;
    int min;
    int max;
};

DpResult dp[1001][1001];

int main() {
#   ifdef _DEBUG
        freopen("l.in", "r", stdin);
#   else
        freopen("l.in", "r", stdin);
        freopen("l.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    int i, j, k, n;
    while (cin >> s) {
        n = s.length();
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                dp[i][j].valid = false;
        for (i = n - 1; i >= 0; i--)
            switch (s[i]) {
                case '+': {
                    for (j = i + 2; j < n; j++) {
                        int mn = INT_MAX;
                        int mx = INT_MIN;
                        for (k = i + 1; k < j; k++)
                            if (dp[i + 1][k].valid && dp[k + 1][j].valid) {
                                mn = min(mn, dp[i + 1][k].min + dp[k + 1][j].min);
                                mx = max(mx, dp[i + 1][k].max + dp[k + 1][j].max);
                            }
                        if (mn != INT_MAX) {
                            dp[i][j].valid = true;
                            dp[i][j].min = mn;
                            dp[i][j].max = mx;
                        }
                    }
                    break;
                }
                case '-': {
                    //Unary minus with single digit.
                    if (i + 1 < n && dp[i + 1][i + 1].valid) {
                        dp[i][i + 1].valid = true;
                        dp[i][i + 1].min = dp[i][i + 1].max = -dp[i + 1][i + 1].min;
                    }
                    for (j = i + 2; j < n; j++) {
                        int mn = INT_MAX;
                        int mx = INT_MIN;
                        //Unary.
                        if (dp[i + 1][j].valid) {
                            mn = -dp[i + 1][j].max;
                            mx = -dp[i + 1][j].min;
                        }
                        //Binary.
                        for (k = i + 1; k < j; k++)
                            if (dp[i + 1][k].valid && dp[k + 1][j].valid) {
                                mn = min(mn, dp[i + 1][k].min - dp[k + 1][j].max);
                                mx = max(mx, dp[i + 1][k].max - dp[k + 1][j].min);
                            }
                        if (mn != INT_MAX) {
                            dp[i][j].valid = true;
                            dp[i][j].min = mn;
                            dp[i][j].max = mx;
                        }
                    }
                    break;
                }
                case '0': {
                    dp[i][i].valid = true;
                    dp[i][i].min = dp[i][i].max = 0;
                    break;
                }
                default: {
                    int lim = min(i + 9, n);
                    int value = 0;
                    for (j = i; j < lim && s[j] != '+' && s[j] != '-'; j++) {
                        value = value * 10 + s[j] - '0';
                        dp[i][j].valid = true;
                        dp[i][j].min = dp[i][j].max = value;
                    }
                }
            }
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                if (dp[i][j].valid)
                    debug << '(' << dp[i][j].min << ',' << dp[i][j].max << ")\t";
                else
                    debug << "(*,*)\t";
            debug << '\n';
        }
        cout << dp[0][n - 1].min << ' ' << dp[0][n - 1].max << '\n';
        debug << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
