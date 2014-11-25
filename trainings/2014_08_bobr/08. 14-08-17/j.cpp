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

struct Edge {
  int to;
  double fr;
  Edge() {}
  Edge(int to, double fr) : to(to), fr(fr) {}
};

struct Base {
  double gain;
  double self;
  Base() {}
  Base(double self) : gain(0), self(self), old_self(self) {

  }

  void add_gain(double d) {
    gain += d;
  }
  double get_self(double fr) {
    double result = old_self*fr;
    self -= result;
    return result;
  }
  void calc() {
    self += gain;
    gain = 0;
    old_self = self;
  }
private:
  double old_self;
};

int main() {
#   ifdef _DEBUG
        freopen("j.in", "r", stdin);
#   else
        freopen("j.in", "r", stdin);
        freopen("j.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << setprecision(6) << fixed;

    int tests; cin >> tests;
    while( tests-- ) {
      int n,m,t; cin >> n >> m >> t;
      vector<Base> bases; bases.reserve(n);
      for(int i = 0; i < n; i++) {
        double v; cin >> v; bases.push_back(Base(v));
      }
      vector< vector<Edge> > prop(n);
      vector<vi> adj(n);
      for(int i = 0; i < m; i++) {
        int from, to; double fr;
        cin >> from >> to >> fr;        
        prop[from].push_back(Edge(to,fr));
        adj[from].push_back(to); adj[to].push_back(from);
      }
      while( t-- ) {
        for(int i = 0; i < n; i++)
          for(int j = 0; j < sz(prop[i]); j++) {
            int from = i, to = prop[i][j].to;
            double fr = prop[i][j].fr;
            double how_much = bases[from].get_self(fr);
            bases[to].add_gain(how_much);
          }
        for(int i = 0; i < n; i++)
          bases[i].calc();
      }
      double result = inf;
      for(int i = 0; i < n; i++) {
        double cur = bases[i].self;
        for(int j = 0; j < sz(adj[i]); j++)
          cur += bases[adj[i][j]].self;
        result = min(result,cur);
      }
      cout << result << "\n";
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
