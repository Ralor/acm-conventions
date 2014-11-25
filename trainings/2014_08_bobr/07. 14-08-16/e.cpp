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

vector<int> parent;

bool dfs(Graph& g, vi& used, int v, int to_find) {
  used[v] = 1;
  if( v == to_find )
    return true;
  for(int i = 0; i < sz(g[v]); i++) {
    int nxt = g[v][i];     
    if( !used[nxt] ){
      parent[nxt] = v;
      if( dfs(g,used,nxt,to_find) )
        return true;
      else
        parent[nxt] = -1;
    }    
  }
  return false;
}

int rec(Graph& g, vi& used, vi& gain, int v) {
  used[v] = 1;
  int result = gain[v];
  for(int i = 0; i < sz(g[v]); i++) {
    int nxt = g[v][i];
    if( !used[nxt] )
      result += max(0, rec(g, used, gain, nxt));    
  }
  return result;
}

int main() {
#   ifdef _DEBUG
        freopen("e.in", "r", stdin);
#   else
        freopen("e.in", "r", stdin);
        freopen("e.out", "w", stdout);
#   endif
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    
    int tests; scanf("%d",&tests);

    while( tests-- ) {
      int n,t; scanf("%d%d",&n,&t); --t;
      parent.assign(n,-1); 
      vector<int> gain(n);
      for(int i = 0; i < n; i++)
        scanf("%d",&gain[i]);
      
      Graph g(n);
      for(int i = 0; i < n-1; i++) {
        int a,b; scanf("%d%d",&a,&b); --a, --b;
        g[a].push_back(b); g[b].push_back(a);
      }
      
vector<int> tt(n,0);
      dfs(g,tt,0,t);

      vector<int> path;
      for(int v = t; v != -1; v = parent[v])
        path.push_back(v);      
      parent[0] = 0; // to mark it as vertex in "path" (for "rec" function)

//#ifdef _DEBUG
//      reverse(all(path));
//      for(int i = 0; i < sz(path); i++)
//        debug << path[i]+1 << " ";
//      debug << "\n";
//      reverse(all(path));
//#endif

      
      vector<int> used(n,0);
      for(int i = 0; i < sz(path); i++)
        used[path[i]] = 1; // we can't use vertexes from "path" to heal

      int hp = 0;
      for(int i = sz(path)-1; i >= 0; --i) {
        int v = path[i];
        hp += gain[v];
        if( hp < 0 ) {
          puts("trapped");
          break;
        } else {
          int possible_heal = rec(g,used,gain,v) - gain[v];
          hp += max(0, possible_heal);
        }
      }
      if( hp >= 0 )
        puts("escaped");
    }


#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
