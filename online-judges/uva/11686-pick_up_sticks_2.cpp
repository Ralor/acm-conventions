#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <valarray>
#include <vector>
#include <assert.h>
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define fst        first
#define snd        second
#define pb         push_back
#define mp         make_pair
#define eb         emplace_back
#define ef         emplace_front
#define mt         make_tuple
#define eps        1e-8
#define inf        int(1e9)
#define linf       llong(4e18)
using namespace std;

struct debug_t {
  template<typename T>
  debug_t& operator << (const T& o) {
#   ifdef LOCAL_DEBUG
    cout<<o<<flush;
#   endif
    return *this;
  }
} debug;

#define TIMESTAMP(msg) debug << "[" msg "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n' 
#define DBG(x) debug << "[" #x "] = " << x << '\n'
#define DOUT(x) debug << x << '\n'
#define _ << " " <<

typedef unsigned char       uchar;
typedef basic_string<uchar> ustring;
typedef long long           llong;
typedef unsigned long long  ullong;
typedef long double         ldouble;
typedef vector<int>         vi;
typedef vector<vi>          vvi;
typedef vector<double>      vd;
typedef vector<vd>          vvd;
typedef pair<int,int>       pii;

inline int next_int() {
  char c;
  while( !isdigit(c = getchar()) ) { }
  int result = c - '0';
  while( isdigit(c = getchar()) )
    result = result * 10 + c - '0';
  return result;
}

bool topsort(vvi& g, vector<char>& color, vi& ts, int u) {
  color[u] = 1;
  for(int v : g[u]) {
    if( color[v] == 2 )
      continue;
    if( color[v] == 1 || !topsort(g,color,ts,v) )
      return false;
  }
  ts.eb(u);
  color[u] = 2;
  return true;
}

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  
  int n,m;
  while( n = next_int(), m = next_int(), n || m ) {
    vvi g(n);
    forn(i,m) {
      int u = next_int() - 1;
      int v = next_int() - 1;
      g[u].eb(v);
    }
    vector<char> color(n);
    vi ts;
    bool cycle = false;
    forn(u,n)
      if( color[u] == 0 && !topsort(g,color,ts,u) ) {
        cycle = true;
        break;
      }
    if( cycle )
      printf("IMPOSSIBLE\n");
    else
      for_each(rall(ts), [](int u) { printf("%d\n",u+1); });
  }
  
  TIMESTAMP("end");
  return 0;
}
