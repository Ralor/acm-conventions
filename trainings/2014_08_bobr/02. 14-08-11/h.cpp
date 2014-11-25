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

int order[256];

bool cmp(const string& a, const string& b) {
    int len = min(a.length(), b.length());
    for (int i = 0; i < len; i++)
        if (order[a[i]] != order[b[i]])
            return order[a[i]] < order[b[i]];
    return a.length() < b.length();
}

int main() {
#   ifdef _DEBUG
        freopen("h.in", "r", stdin);
#   else
        freopen("h.in", "r", stdin);
        freopen("h.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, n, test = 1;
    string alph;
    string words[20];
    while (cin >> n, n) {
        cin >> alph;
        for (i = 0; i < (int)alph.length(); i++)
            order[alph[i]] = i;
        for (i = 0; i < n; i++)
            cin >> words[i];
        sort(words, words + n, cmp);
        cout << "year " << test++ << '\n';
        for (i = 0; i < n; i++)
            cout << words[i] << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
