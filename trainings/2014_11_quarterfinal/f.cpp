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
#ifdef LOCAL_PROJECT
#   include <conio.h>
#endif

#ifndef LOCAL_PROJECT
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
#define mt       make_tuple
#define pb       push_back

using namespace std;

#define forn(i, n) for(int i = 0; i < (n); ++i)

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_;
template<typename I> inline void in(I l,I r)
{while(l!=r)cin>>*l,++l;}
template<typename I> inline void out(I l,I r,char D=' ')
{if(l!=r){cout<<*l;while(++l!=r)cout<<D<<*l;}cout<<'\n';}



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
#   ifdef LOCAL_PROJECT
        freopen("f.in", "r", stdin);
#   else
#   endif
    
    int hh,mm,ss; char c;
    while( cin >> hh >> c >> mm >> c >> ss ) {
      // ss += 60*60*hh + 60*mm;
      if( hh >= 12 ) hh -= 12;
      double h = (1.0 / 12.0) * hh * 360;
      double m = (1.0 / 60.0) * mm * 360;

      //h += (1.0 / 3600.0) * (1.0 / 12.0) * ss * 360; // 360 / 12 / 3600 * ss;
      m += (1.0 / 60.0) * (1.0 / 60.0) * ss * 360;
      h += (1.0 / 60.0) * (1.0 / 12.0) * mm * 360 + (1.0 / 3600.0) * (1.0 / 12.0) * ss * 360;      
      double tmp = fabs(h-m);
      if( tmp > 180 ) {
        tmp = 360 - tmp;
      }

      double ang = tmp;
      ang += eps;

      int deg = int(ang);
      ang -= deg;
      int minutes = int(ang * 60 + eps);
      ang -= 1.0 / 60.0 * minutes;
      int seconds = int(ang * 3600 + eps);

      cout << deg << " " << minutes << " " << seconds << "\n";
    }

#   ifdef LOCAL_PROJECT
        _getch();
#   endif
    return 0;
}
