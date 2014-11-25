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

bool check(vector<int>& a, int d, int a1, int a2 = 0, int a3 = 0) {
  bool ok = true;
  for(int i = d+1; i < sz(a); i++)
    if( d == 1 )
     ok &= a[i-1] * a1 == a[i];
    else if( d == 2 )
      ok &= a[i-2] * a1 + a[i-1] * a2 == a[i];
    else if( d == 3 )
      ok &= a[i-3] * a1 + a[i-2] * a2 + a[i-1] * a3 == a[i];      
  return ok;
}

int main() {
#   ifdef _DEBUG
        freopen("f.in", "r", stdin);
#   else
        freopen("f.in", "r", stdin);
        freopen("f.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tests; cin >> tests;
    while( tests-- ) {
      int n; cin >> n;
      vector<int> k(n+1);
      for(int i = 1; i <= n; i++)
        cin >> k[i];
      llong a1 = k[2]/k[1], a2, a3, det;
      if( check(k,1,a1) ) {
        cout << k.back() * a1 << "\n";
      } else {
        det = k[1]*k[3] - k[2]*k[2];
        a1 = k[3]*k[3] - k[2]*k[4]; if( det != 0 ) a1 /= det;
        a2 = k[1]*k[4] - k[3]*k[2]; if( det != 0 ) a2 /= det;
        if( det != 0 && check(k,2,a1,a2) ) {
          cout << k[sz(k)-2] * a1 + k[sz(k) - 1] * a2 << "\n";          
        } else {
          det = k[1]*k[3]*k[5] + k[2]*k[4]*k[3] + k[2]*k[4]*k[3] - k[3]*k[3]*k[3] - k[2]*k[2]*k[5] - k[4]*k[4]*k[1];
          a1 = k[4]*k[3]*k[5] + k[5]*k[4]*k[3] + k[2]*k[4]*k[6] - k[6]*k[3]*k[3] - k[5]*k[2]*k[5] - k[4]*k[4]*k[4];
          a1 /= det;
          a2 = k[1]*k[5]*k[5] + k[2]*k[6]*k[3] + k[4]*k[4]*k[3] - k[3]*k[5]*k[3] - k[2]*k[4]*k[5] - k[6]*k[4]*k[1];
          a2 /= det;
          a3 = k[1]*k[3]*k[6] + k[2]*k[4]*k[4] + k[2]*k[5]*k[3] - k[3]*k[3]*k[4] - k[2]*k[2]*k[6] - k[4]*k[5]*k[1];
          a3 /= det;
          cout << k[sz(k)-3] * a1 + k[sz(k)-2] * a2 + k[sz(k)-1] * a3 << "\n";
        }
      }
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
