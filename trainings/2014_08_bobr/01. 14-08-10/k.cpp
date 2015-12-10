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

typedef vector< vector<int> > Graph;

inline bool check(const Graph& g, int mask) {
  int used = 0x00;
  int n = sz(g);
  if (mask >= 1 << n)
    return false;
  
  int v = 0;
  while( mask ) {
    if( mask & 1 ) {
      for(int i = 0; i < sz(g[v]); i++)
        used |= 1 << g[v][i];
      used |= 1 << v;
    }
    mask >>= 1; ++v;
  }

  return used == (1 << n) - 1;
}

bool cmp(const pair<int,int>& lhs, const pair<int,int>& rhs) {
  return lhs.first < rhs.first;
}

int main() {
#   ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);  
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   else
        freopen("k.in", "r", stdin);
        freopen("k.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
    int tests;

    const int maxN = 1<<20;
    vector<pair<int,int> > masks; masks.reserve(maxN);
    for(int i = 0; i < maxN; i++) {
      int popcnt = 0, tmp = i;
      while( tmp ) popcnt += tmp & 1, tmp >>= 1;
      masks.push_back(mp(popcnt,i));
    }
    sort(all(masks), cmp);

    cin >> tests;
    Graph g;
    while (tests--) {      

      int n; cin >> n;
      g.clear();
      g.resize(n);
      for(int i = 0; i < n; i++) {
        int cnt; cin >> cnt;
        int a;
        for(int j = 0; j < cnt; j++)
          cin >> a, g[i].push_back(a-1), g[a-1].push_back(i);
      }

      for(int i = 0; i < sz(masks); ++i) {
        if( check(g, masks[i].second) ) {            
          cout << masks[i].first << "\n";         
          break;
        }
      }
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
