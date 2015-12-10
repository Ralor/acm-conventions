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



int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int another_test = 0;
  int cn; cin>>cn;
  forn(ci,cn) {
    int n,target,timer,m;
    cin>>n>>target>>timer>>m;
    --target;
    vvi g(n), cost(n);
    forn(i,m) {
      int u,v,w;
      cin>>u>>v>>w;
      --u; --v;
      g[v].eb(u); cost[v].eb(w);
    } 
    vi dist(n, inf), used(n);
    dist[target] = 0;
    forn(iter, n) {
      int u = -1;
      forn(i,n)
        if( !used[i] && (u == -1 || dist[u] > dist[i]) )
          u = i;
      if( dist[u] == inf )
        break;
      used[u] = 1;    
      forn(i,sz(g[u])) {
        int v = g[u][i], len = cost[u][i];
        if( dist[v] > dist[u] + len )
          dist[v] = dist[u] + len;
      }
    }
    int result = 0;
    forn(u,n)
      result += dist[u] <= timer;
    if( another_test++) 
      cout<<"\n";
    cout<<result<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
