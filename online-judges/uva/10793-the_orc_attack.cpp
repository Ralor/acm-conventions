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

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int,int>      pii;


int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int n,m; cin>>n>>m;
    vvi dp(n, vi(n, inf));
    forn(edge,m) {
      int u,v,cost; cin>>u>>v>>cost;
      --u; --v;
      dp[u][v] = min(dp[u][v], cost);
      dp[v][u] = dp[u][v];
    }
    forn(i,n)
      dp[i][i] = 0;
    forn(k,n) forn(i,n) forn(j,n)
      dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    int result = inf;
    forn(u,n) {
      set<int> tmp;
      forn(v,5)
        tmp.insert(dp[u][v]);
      if( sz(tmp) == 1 ) {
        int mx = 0;
        forn(v,n)
          mx = max(mx, dp[u][v]);
        result = min(result, mx);
      }
    }
    cout<<"Map "<<ci+1<<": "<<(result == inf ? -1 : result)<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
