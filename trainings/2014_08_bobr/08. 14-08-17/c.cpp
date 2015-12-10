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
        freopen("c.in", "r", stdin);
#   else
        freopen("c.in", "r", stdin);
        freopen("c.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests; cin >> tests;

    while( tests-- ) {
      int n; cin >> n;
      vector<string> aa(n);
      for(int i = 0; i < n; i++)
        cin >> aa[i];
      string D,A; cin >> D >> A;
      vector<string> a;
      for(int i = 0; i < sz(aa); i++)
        if( sz(aa[i]) == sz(D) )
          a.push_back(aa[i]);
      map<char,char> glob;
      bool at_least_one = false;
      for(int i = 0; i < sz(a); i++) {
        map<char,char> check;
        bool ok = true;
        for(int j = 0; j < sz(D); j++) {
          if( check.find(a[i][j]) == check.end() ) {
            check[a[i][j]] = D[j];
          } else {
            ok &= check[a[i][j]] == D[j];
          }          
        }
        if( ok ) {
          at_least_one = true;
          for(map<char,char>::iterator it = check.begin(); it != check.end(); it++) {
            char from = it->first, to = it->second;
            if( glob.find(from) == glob.end() )
              glob[from] = to;
            else
              glob[from] = '?';
          }
        }
      }
      if( at_least_one ) {
        for(int i = 0; i < sz(A); i++)
          cout << glob[A[i]];
        cout << "\n";
      } else {
        cout << "IMPOSSIBLE" << "\n";
      }
    }
    
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
