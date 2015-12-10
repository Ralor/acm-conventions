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

struct Point {
  int x,y;
  Point() {}
  int dist(const Point& p) const {
    return abs(p.x - x) + abs(p.y - y);
  }
};

void dfs(vector<vi>& g, vi& used, int v) {
  used[v] = 1;
  for(int i = 0; i < sz(g[v]); i++)
    if( !used[g[v][i]] )
      dfs(g,used,g[v][i]);
}

int main() {
#   ifdef _DEBUG
        freopen("d.in", "r", stdin);
#   else
        freopen("d.in", "r", stdin);
        freopen("d.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tests; cin >> tests;
    while( tests-- ) {
      int n; cin >> n;
      
      vector<Point> a(n+2);
      int start = 0, stop = sz(a)-1;
      for(int i = 0; i < n+2; i++)
        cin >> a[i].x >> a[i].y;

      vector<vi> g(sz(a));
      for(int i = 0; i < sz(a); i++)
        for(int j = 0; j < sz(a); j++)
          if( i != j ) {
            int dist = a[i].dist(a[j]);
            if( dist <= 1000 )
              g[i].push_back(j), g[j].push_back(i);
          }

      vector<int> used(sz(a),0);
      dfs(g,used,start);
      if( used[stop] )
        cout << "happy" << "\n";
      else
        cout << "sad" << "\n";
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
