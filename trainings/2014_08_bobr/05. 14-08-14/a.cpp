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
        freopen("a.in", "r", stdin);
#   else
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    time_t start = clock();

    const int att = 1000*1000;

    string s;
    while( cin >> s ) {
      int tt = find(all(s), '/') - s.begin();
      string aa = s.substr(0,tt+1), bb = s.substr(tt+1);
      int a = atoi(aa.c_str()), n = atoi(bb.c_str());

      int res = 0;

      ldouble x = 1.0;
      for(int i = 0; i < att; i++) {      
        ldouble t = 1 / fabs(ldouble(a)/n - 1/x);
        if( (t - int(t)) < 1e-10 )
          ++res;
        x += 1;
      }

      cout << res << "\n";
    }

    cout << (clock() - start) / CLOCKS_PER_SEC << "\n";

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
