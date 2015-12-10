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
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  cout<<setprecision(3)<<fixed;
  int n; int ci = 1;
  while( cin>>n, n ) {
    vector<pair<double,double>> a(n);
    forn(i,n)
      cin>>a[i].first>>a[i].second;
    vd dist(n,inf);
    vi used(n), parent(n,-1);
    dist[0] = 0;
    forn(iter, n) {
      int u = -1;
      forn(i,n)
        if( !used[i] && (u == -1 || dist[u] > dist[i]) )
          u = i;
      if( u == 1 )
        break;
      used[u] = 1;
      forn(v,n) if( !used[v] ) {
        double dv = sqr(a[u].first - a[v].first) + sqr(a[u].second - a[v].second);
        if( dist[v] > dv + eps )
          dist[v] = dv, parent[v] = u;
      }
    }
    double result = 0;
    for(int u = 1; u != 0; u = parent[u])
      result = max(result, dist[u]);
    cout<<"Scenario #"<<ci++<<"\n";
    cout<<"Frog Distance = "<<sqrt(result)<<"\n";
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
