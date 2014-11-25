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

int n;
int cost[20];
ldouble prop[20];
ldouble dp[20][20][1111]; // dp[pos][succ][money];

ldouble rec(int pos, int succ_left, int money) {
  if( succ_left == 0)
    return 1;
  if( pos == n )
    return 0;
  if( dp[pos][succ_left][money] != -1 )
    return dp[pos][succ_left][money];
  ldouble take_it = 0;
  if( money >= cost[pos] ) {
    take_it += prop[pos] * rec(pos+1,succ_left-1,money-cost[pos]);
    take_it += (1-prop[pos]) * rec(pos+1, succ_left, money-cost[pos]);
  }
  ldouble leave_it = rec(pos+1, succ_left, money);
  return (dp[pos][succ_left][money] = max(take_it, leave_it));
}

int main() {
#   ifdef _DEBUG
        freopen("b.in", "r", stdin);
#   else
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << setprecision(6) << fixed;

    int tests; cin >> tests;
    while( tests-- ) {
      int cnt, money; cin >> n >> cnt >> money;
      for(int i = 0; i < n; i++)
        cin >> cost[i] >> prop[i], prop[i] /= 100;
      for(int i = 0; i < 20; i++)
        for(int j = 0; j < 20; j++)
          for(int k = 0; k < 1111; k++)
            dp[i][j][k] = -1;
      cout << rec(0, cnt, money) << "\n";
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
