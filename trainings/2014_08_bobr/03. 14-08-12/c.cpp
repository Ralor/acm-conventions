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

void gen(vector<double>& rnd) {
  vector<double> t(1,0); t.reserve(sz(rnd)+2);
  for(int i = 0; i < sz(rnd)-1; i++)
    t.push_back(rand() / (RAND_MAX+1.0));
  t.push_back(1);
  sort(all(t));
  for(int i = 0; i < sz(rnd); i++)
    rnd[i] = sqrt(t[i+1] - t[i]);
  int mask = rand() % (1 << sz(rnd)), ind = 0;
  while( ind < sz(rnd) ) {
    if( mask & 1 )
      rnd[ind] = -rnd[ind];
    mask >>= 1;++ind;
  }
}

int main() {
#   ifdef _DEBUG
  freopen("c.in", "r", stdin);
#   else
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#   endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  srand(0xbeef);

  const int attempts = 60*1000;

  int tests; cin >> tests;
  while( tests-- ) {
    vector<double> arr(3);
    
    int n; cin >> n;
    vector<int> a(n), b(n), c(n), yes(n,0);
    for(int i = 0; i < n; i++)
      cin >> a[i] >> b[i] >> c[i];
        
    for(int att = 0; att < attempts; ++att) {
      gen(arr);
      double mx = -inf;
      int mxi = -1;
      for(int i = 0; i < n; i++) {
        double cost = a[i]*arr[0] + b[i]*arr[1] + c[i]*arr[2]; 
        if( cost > mx ) 
          mx = cost, mxi = i;
      }
      yes[mxi] = 1;
    }
    for(int i = 0; i < n; i++)
      cout << ( (yes[i]) ? 'T' : 'F' );
    cout << "\n";
  }

#   ifdef _DEBUG
  _getch();
#   endif
  return 0;
}
