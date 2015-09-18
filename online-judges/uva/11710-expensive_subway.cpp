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
  
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int n,m;
  while( cin>>n>>m, n || m ) {
    map<string,int> ntoi;
    forn(i,n) { 
      string tmp; cin>>tmp; 
      ntoi[tmp] = i; 
    }
    vector<vector<pair<int,int>>> g(n);
    forn(edge,m) {
      string a,b; cin>>a>>b;
      int u = ntoi[a], v = ntoi[b];
      int cost; cin>>cost;
      g[u].eb(v, cost);
      g[v].eb(u, cost);
    }
    string home; cin>>home;
    int start = ntoi[home];
    vi dist(n,inf), used(n);
    dist[start] = 0;
    int result = 0;
    forn(iter, n) {
      int u = -1;
      forn(i,n)
        if( !used[i] && (u == -1 || dist[u] > dist[i]) )
          u = i;
      if( dist[u] == inf ) {
        result = -1;
        break;
      }
      used[u] = 1;
      result += dist[u];
      for(auto e : g[u]) {
        int v = e.first, cost = e.second;
        if( !used[v] && dist[v] > cost )
          dist[v] = cost;
      }
    }
    if( ~result )
      cout<<result<<"\n";
    else
      cout<<"Impossible\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
