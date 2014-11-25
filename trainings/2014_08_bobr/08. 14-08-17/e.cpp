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

double a,b;
double r(double h) {
  return a*pow(M_E,-sqr(h)) + b*sqrt(h);
}

int main() {
#   ifdef _DEBUG
        freopen("e.in", "r", stdin);
#   else
        freopen("e.in", "r", stdin);
        freopen("e.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double V; int n; cin >> V >> n;

    double best_ind = 0, best_eps = 1e20;

    for(int i = 0; i < n; i++) {
       double h; 
       cin >> a >> b >> h;
       double step = h / 1e6;
       double h1 = 0, h2 = step;
       double cur_v = 0;
       while( h2 < h ) {
         double r1 = r(h1), r2 = r(h2);
         cur_v += step * M_PI * sqr((r2+r1)/2);
         h1 += step; h2 += step;
       }
       double cur_eps = fabs(V - cur_v);
       if( cur_eps < best_eps )
         best_ind = i, best_eps = cur_eps;
    }

    cout << best_ind << "\n";

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
