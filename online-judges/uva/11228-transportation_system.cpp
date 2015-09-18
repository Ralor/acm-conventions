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

bool eq(double a, double b) {
  return fabs(a-b) <= eps;
}
bool le(double a, double b) {
  return a < b || eq(a,b);
}

int main() {
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int n;
    double r;
    cin>>n>>r;
    vector<pair<double,double>> a(n);
    forn(i,n) 
      cin>>a[i].first>>a[i].second;
    vd dist(n,DBL_MAX);
    vi used(n);
    dist[0] = 0; 
    r = sqr(r);
    double road = 0, railroad = 0;
    int railroads = 0;
    forn(iter, n) {
      int u = -1;
      forn(i,n)
        if( !used[i] && (u == -1 || dist[u] > dist[i]) )
          u = i;
      used[u] = 1;
      if( u ) {
        if( le(dist[u],r) )
          road += sqrt(dist[u]);
        else
          railroad += sqrt(dist[u]), ++railroads;
      }
      forn(v,n) if( !used[v] ) {
        double d = sqr(a[u].first - a[v].first) + sqr(a[u].second - a[v].second);
        if( dist[v] > d )
          dist[v] = d;
      }
    }
    cout<<"Case #"<<ci+1<<": "<<railroads+1<<" "<<llong(road+0.5)<<" "<<llong(railroad+0.5)<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
