#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#ifdef LOCAL_PROJECT
#   include <conio.h>
#else
#   undef VERBOSE
#endif

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define pb         push_back
#define mp         make_pair
#define eps        1e-8
#define inf        int(1e9)
#define linf       llong(4e18)

#define TIMESTAMP(msg) cerr << "[" msg "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n'

using namespace std;

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int, int>     pii;

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
#   ifdef LOCAL_PROJECT
        freopen(".in", "r", stdin);
#   else
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
#   ifdef LOCAL_PROJECT
        _getch();
#   endif
    return 0;
}
