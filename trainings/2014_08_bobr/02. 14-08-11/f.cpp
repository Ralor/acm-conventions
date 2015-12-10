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
        freopen("f.in", "r", stdin);
#   else
        freopen("f.in", "r", stdin);
        freopen("f.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, n;
    short digits[14];
    while (cin >> n, n) {
        for (i = 0; i < n; i++)
            cin >> digits[i];
        sort(digits, digits + n);
        const short* cur = digits;
        while (!*cur)
            cur++;
        int a = *cur, b = cur[1];
        cur += 2;
        bool f = true;
        for (int i = 0; !digits[i]; i++) {
            if (f)
                a *= 10;
            else
                b *= 10;
            f = !f;
        }
        while (cur < digits + n) {
            if (f)
                a = a * 10 + *cur;
            else
                b = b * 10 + *cur;
            f = !f;
            cur++;
        }
        cout << a + b << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
