#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define pb         push_back
#define mp         make_pair
#define eb         emplace_back
#define mt         make_tuple
#define eps        1e-8
#define inf        int(1e9)
#define linf       llong(4e18)

using namespace std;

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int,int>      pii;

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

void topsort(vvi& g, vi& used, vi& ts, int u) {
  used[u] = 1;
  for(int v : g[u])
    if( !used[v] )
      topsort(g,used,ts,v);
  ts.eb(u);
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int n,m; cin>>n>>m;
    vvi g(n);
    forn(edge,m) {
      int u,v; 
      cin>>u>>v;
      --u; --v;
      g[u].eb(v);
    }
    vi ts, used(n);
    forn(u,n)
      if( !used[u] )
        topsort(g,used,ts,u);
    int cnt = 0;
    used.assign(n,0);
    forn(i,n)
      if( !used[ts[n-i-1]] )
        topsort(g,used,ts,ts[n-i-1]), ++cnt;
    cout<<cnt<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
