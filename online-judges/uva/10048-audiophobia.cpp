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

void dfs(vvi& g, vvi& a, vvi& d, int start, int weight, int u, int parent = -1) {
  d[start][u] = weight;
  for(int v : g[u]) 
    if( v != parent )
      dfs(g,a,d,start,max(weight,a[u][v]),v,u);
} 

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n,m,q;
  int ci = 1;
  while( cin>>n>>m>>q, n || m || q ) {
    vvi a(n, vi(n, inf));
    int u,v,c;
    forn(e,m)
      cin>>u>>v>>c, --u, --v, a[u][v] = a[v][u] = c;
    vi dist(n, inf), used(n), mst(n, -1);
    forn(start, n) {
      if( dist[start] != inf )
        continue;
      dist[start] = 0;
      forn(iter, n) {
        int u = -1;
        forn(i,n)
          if( !used[i] && (u == -1 || dist[u] > dist[i]))
            u = i;
        if( u == -1 || dist[u] == inf )
          break;
        used[u] = 1;
        forn(v,n)
          if( !used[v] && dist[v] > a[u][v] ) {
            dist[v] = a[u][v];
            mst[v] = u;
          }
      }
    }
    vvi tree(n);
    forn(u,n)
      if( ~mst[u] )
        tree[u].eb(mst[u]), tree[mst[u]].eb(u);
    vvi d(n, vi(n, inf));
    forn(u,n)
      dfs(tree,a,d,u,0,u);
    if( ci > 1 )
      cout<<"\n";
    cout<<"Case #"<<ci++<<"\n";
    forn(i,q) {
      cin>>u>>v; --u; --v;
      if( d[u][v] != inf )
        cout<<d[u][v]<<"\n";
      else
        cout<<"no path\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
