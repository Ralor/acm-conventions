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

namespace DSU {
  vi parent;
  void check(int u) {
    while( sz(parent) <= u )
      parent.pb(sz(parent));
  }
  int get(int u) {
    if( parent[u] == u )
      return u;
    return parent[u] = get(parent[u]);
  }
  bool merge(int u, int v) {
    u = get(u);
    v = get(v);
    if( u == v )
      return false;
    if( rand() & 1 )
      swap(u,v);
    parent[u] = v;
    return true;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  while(1) {
    int u,v;
    bool test = false;
    int result = 0;
    DSU::parent.clear();
    while( cin>>u && u != -1 && cin>>v ) {
      test = true;
      DSU::check(u);
      DSU::check(v);
      if( !DSU::merge(u,v) )
        ++result;
    }
    if( test )
      cout<<result<<"\n";
    else
      break;
  }
  
  TIMESTAMP("end");
  return 0;
}
