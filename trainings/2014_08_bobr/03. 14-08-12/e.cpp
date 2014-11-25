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



int main() {
#   ifdef _DEBUG
        freopen("e.in", "r", stdin);
#   else
        freopen("e.in", "r", stdin);
        freopen("e.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    while (tests--) {
        double r, b, m;
        cin >> r >> b >> m;
        r = 1. + r * .01;
        b *= 100;
        m *= 100;
        bool ok = false;
        for (int i = 0; ; i++) {
            b *= r;
            double f = floor(b + 1e-6);
            double c = ceil(b - 1e-6);
            double d1 = fabs(b - f);
            double d2 = fabs(c - b);
            if (!eq(d1, d2) && d1 < d2)
                b = f;
            else
                b = c;
            if (b <= .0) {
                cout << i << '\n';
                ok = true;
                break;
            } else if (i >= 1200)
                break;
            b -= m;
        }
        if (!ok)
            cout << "impossible\n";
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
