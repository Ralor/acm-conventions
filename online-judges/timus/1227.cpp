#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
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
#define _ <<" "<<

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int,int>      pii;

bool cycle(vvi& a, vi& used, int u, int p = -1) {
  used[u] = 1;
  forn(v,sz(a))
    if( a[u][v] != inf && v != p ) {
      if( used[v] || cycle(a,used,v,u) )
        return true;
    }
  return false;
}
int maxpath(vvi& a, int u, int p = -1) {
  int result = 0;
  forn(v,sz(a))
    if( a[u][v] != inf && v != p )
      result = max(result, a[u][v] + maxpath(a,v,u));
  return result;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int n,m,s;
  while( cin>>n>>m>>s ) {
    vvi a(n, vi(n, inf));
    bool cycled = false;
    forn(e,m) {
      int u,v,c; cin>>u>>v>>c;
      --u; --v;
      if( a[u][v] != inf )
        cycled = true;
      else
        a[u][v] = a[v][u] = c;
    }
    vi used(n);
    forn(u,n)
      if( !used[u] && !cycled )
        cycled |= cycle(a,used,u);
    if( cycled ) {
      cout<<"YES\n";
      continue;
    }
    bool found = false;
    forn(u,n)
      if( maxpath(a,u) >= s ) {
        found = true; break;
      }
    cout<<(found ? "YES\n" : "NO\n");
  }
  
  TIMESTAMP("end");
  return 0;
}
