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

int n;
vector<int> attributes;
llong dp[32];

llong Rcsv(int pos) {
    if (pos >= (int)attributes.size())
        return 1;
    if (dp[pos] != -1)
        return dp[pos];
    return (dp[pos] = Rcsv(pos + 1) * attributes[pos]);
}

int main() {
#   ifdef _DEBUG
        freopen("i.in", "r", stdin);
#   else
        freopen("i.in", "r", stdin);
        freopen("i.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    int i;
    map<string, int> typeMap;
    string s;
    while (tests--) {
        attributes.clear();
        typeMap.clear();
        memset(dp, 0xFF, sizeof dp);
        cin >> n;
        for (i = 0; i < n; i++) {
            cin >> s >> s;
            map<string, int>::iterator lb = typeMap.lower_bound(s);
            if (lb != typeMap.end() && !typeMap.key_comp()(s, lb->first))
                attributes[lb->second]++;
            else {
                typeMap.insert(lb, make_pair(s, attributes.size()));
                attributes.push_back(2);
            }
        }
        cout << Rcsv(0) - 1 << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
