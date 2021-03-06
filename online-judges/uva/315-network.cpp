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

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
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

int root_childs;
void find_ap(vvi& g, vi& ap, vi& tm, vi& low, int& timer, int u, int p = -1) {
  tm[u] = low[u] = timer++;  
  for(int v : g[u]) if( v != p ) {
    if( ~tm[v] ) {
      low[u] = min(low[u], tm[v]);
    } else {
      if( u == 0 )
        ++root_childs;
      find_ap(g,ap,tm,low,timer,v,u);
      low[u] = min(low[u], low[v]);
      DOUT(u _ v _ tm[u] _ low[v]);
      if( tm[u] <= low[v] )
        ap[u] = 1;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n;
  while( cin>>n, n ) {
    vvi g(n);
    int u,v;
    while( cin>>u, u ) {
      --u;
      string tmp; getline(cin, tmp);
      istringstream in(tmp);
      while( in >> v )
        --v, g[u].eb(v), g[v].eb(u);
    }
    int timer = 0;
    vi tm(n, -1), low(n), ap(n);
    root_childs = 0;
    find_ap(g,ap,tm,low,timer,0);
    ap[0] = (root_childs > 1);
    cout<<count(all(ap), 1)<<"\n";
  }
  
  
  TIMESTAMP("end");
  return 0;
}