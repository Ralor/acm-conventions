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

void dfs(vvi& a, vvi& mx, int start, int cur_mx, int u, int p = -1) {
  mx[start][u] = cur_mx;
  forn(v, sz(a)) if( v != p && a[u][v] != inf )
    dfs(a, mx, start, max(cur_mx,a[u][v]), v, u);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int cn; cin>>cn;
  forn(ci, cn) {
    int n,m; cin>>n>>m;
    vvi a(n, vi(n, inf));
    vector<tuple<int,int,int>> edges; edges.reserve(m);
    forn(i,m) {
      int u,v,c; cin>>u>>v>>c;
      --u; --v;
      a[u][v] = a[v][u] = min(a[u][v], c);
      edges.eb(u,v,c);
    }
    vi used(n), dist(n, inf), par(n, -1);
    dist[0] = 0; used[0] = 1;
    vvi mst(n, vi(n, inf));
    int mst_cost = 0;
    for(int mn, u = 0; ~u; u = mn) {
      mn = -1;
      forn(v, n) if( !used[v] ) {
        if( dist[v] > a[u][v] )
          par[v] = u, dist[v] = a[u][v];
        if( mn == -1 || dist[mn] > dist[v] )
          mn = v;
      }
      if( ~mn ) {
        used[mn] = 1;
        if( ~par[mn] ) {
          mst[mn][par[mn]] = mst[par[mn]][mn] = dist[mn];
          mst_cost += dist[mn];
        }
      }
    }
    vvi mx(n, vi(n, inf));
    forn(u, n)
      dfs(mst,mx,u,0,u);
    int best_replace = inf;
    for(auto e : edges) {
      int u,v,c;
      tie(u,v,c) = e;
      if( a[u][v] != inf && mst[u][v] == inf )
        best_replace = min(best_replace, mst_cost - mx[u][v] + a[u][v]);
    }
    cout<<mst_cost<<" "<<best_replace<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}