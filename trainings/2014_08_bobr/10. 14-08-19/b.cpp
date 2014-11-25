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

llong k;
int n;
string s;
string compressed;
llong dp[16];//[posInCompressed]
int firstMultiplier;

llong Dyn(int pos) {
    if (dp[pos] != -1)
        return dp[pos];
    llong result;
    if (compressed[pos] == '?') {
        int multiplier = pos == 0 ? firstMultiplier : 9;
        result = multiplier * Dyn(pos + 1);
    } else
        result = Dyn(pos + 1);
    return (dp[pos] = result);
}

void Main() {
    int len = s.length();
    bool exists[10] = { false };
    for (int start = 0, step = 2; start < len; start = start << 1 | 0x1, step <<= 1) {
        int pos = start;
        while (pos < len && s[pos] == '?')
            pos += step;
        if (pos >= len)
            compressed += '?';
        else {
            char c = s[pos];
            while (pos < len) {
                if (s[pos] != '?' && s[pos] != c) {
                    debug << "a ";
                    cout << "-1\n";
                    return;
                }
                pos += step;
            }
            compressed += c;
            if (start)
                exists[c - '0'] = true;
        }
    }
    if (compressed[0] == '0') {
        debug << "b ";
        cout << "-1\n";
        return;
    }
    firstMultiplier = 9;
    for (int i = 1; i < 10; i++)
        if (exists[i])
            firstMultiplier--;
    n = compressed.length();
    dp[n] = 1;
    Dyn(0);
    debug << "Dyn(0) = " << dp[0] << '\n';
    if (k > dp[0]) {
        debug << "c ";
        cout << "-1\n";
        return;
    }
    llong index = k - 1;
    int i = 0;
    if (compressed[0] == '?') {
        llong number = index / dp[1];
        int j;
        for (j = 1; j < 10; j++)
            if (!exists[j]) {
                number--;
                if (number < 0)
                    break;
            }
        compressed[0] = char(j + '0');
        index %= dp[1];
        i++;
    }
    for (; i < n; i++)
        if (compressed[i] == '?') {
            llong number = index / dp[i + 1];
            if (number + '0' >= compressed[0])
                number++;
            compressed[i] = char(number + '0');
            index %= dp[i + 1];
        }
    for (int i = 0, start = 0, step = 2; start < len; start = start << 1 | 0x1, step <<= 1, i++) {
        int pos = start;
        while (pos < len) {
            s[pos] = compressed[i];
            pos += step;
        }
    }
    cout << s << '\n';
}

int main() {
#   ifdef _DEBUG
        freopen("b.in", "r", stdin);
#   else
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> k, k) {
        compressed.clear();
        memset(dp, 0xFF, sizeof dp);
        cin >> s;
        Main();
        //return 0;
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
