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

int main() {
  
  int n,m;
  while( cin>>n>>m, n||m ) {
    int total = 0;
    vector<vector<pair<int,int>>> g(n);
    forn(e,m) {
      int u,v,c;
      scanf("%d%d%d",&u,&v,&c);
      g[u].eb(v,c);
      g[v].eb(u,c);
      total += c;
    }
    vi dist(n,inf), used(n);
    dist[0] = 0;
    priority_queue<pair<int,int>> pq; 
    pq.emplace(0,0);
    int mst = 0;
    while( !pq.empty() ) {
      int u = pq.top().second, ud = -pq.top().first;
      pq.pop();
      if( dist[u] < ud )
        continue;
      used[u] = 1;
      mst += dist[u];
      for(auto e : g[u]) {
        int v,c;
        tie(v,c) = e;
        if( !used[v] && dist[v] > c )
          dist[v] = c, pq.emplace(-dist[v], v);
      }
    }
    printf("%d\n",total - mst);
  }
  
  TIMESTAMP("end");
  return 0;
}
