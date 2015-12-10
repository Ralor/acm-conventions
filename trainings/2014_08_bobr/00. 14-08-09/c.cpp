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

llong gcd(llong a, llong b) {
  while( a )
    b %= a, swap(a,b);
  return b;
}

map<llong, int> mem;
llong solve(int pos, int len, llong cur_gcd, vector<int> &a) {
  if( pos == sz(a)-1 )
    return len * cur_gcd;
  map<llong,int>::iterator lb = mem.lower_bound(cur_gcd);
  if( lb->first == cur_gcd ) {
    if( lb->second < len )
      lb->second = len;
    return len * cur_gcd;
  } else {
    mem.insert(lb,mp(cur_gcd,len));
  }
  return max( solve(pos+1, len+1, gcd(cur_gcd, a[pos]), a), 
              solve(pos+1, len,   cur_gcd,              a));
}

int main() {
#   ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);  
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   endif
    
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
    
    int cn; cin >> cn;
    for(int ci = 0; ci < cn; ci++) {
      int n; cin >> n;
      vector<llong> a(n);
      

      cout << solve(0,---,a) * n << "\n";
    }

    return 0;
}
