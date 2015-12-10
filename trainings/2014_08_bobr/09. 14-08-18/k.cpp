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

typedef vector<vi> Graph;

map<string,int> name_to_index;
vector<string> index_to_name;

void add_edge(Graph& g, const string& from, const string& to) {
  static int vertex_id = 0;
  int f,t;
  map<string,int>::iterator lb;
  lb = name_to_index.lower_bound(from);
  if( lb != name_to_index.end() && lb->first == from ) {
    f = lb->second;
  } else {
    f = vertex_id; name_to_index.insert(lb,mp(from,vertex_id)); index_to_name.push_back(from);
    ++vertex_id;
  }
  lb = name_to_index.lower_bound(to);
  if( lb != name_to_index.end() && lb->first == to ) {
    t = lb->second;
  } else {
    t = vertex_id; name_to_index.insert(lb,mp(to,vertex_id)); index_to_name.push_back(to);
    ++vertex_id;
  }
  while( sz(g) < vertex_id )
    g.push_back(vi());
  g[f].push_back(t); g[t].push_back(f);
}

int main() {
#   ifdef _DEBUG
        freopen("k.in", "r", stdin);
#   else
        freopen("k.in", "r", stdin);
        freopen("k.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tests; cin >> tests;
    while( tests-- ) {
      int k,n,m; cin >> k >> n >> m;
      Graph g;
      string a,b;
      for(int i = 0; i < m+n+3*k-2; i++) {
        cin >> a >> b; 
        add_edge(g,a,b);
      }


    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
