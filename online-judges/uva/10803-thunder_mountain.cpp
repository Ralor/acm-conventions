#include <cassert>
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
#define fst        first
#define snd        second
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout<<setprecision(4)<<fixed;
  
  int cn; cin>>cn;
  forn(ci, cn) {
    int n; cin>>n;
    vi x(n), y(n);
    forn(u,n)
      cin>>x[u]>>y[u];
    vvd dp(n, vd(n, inf));
    forn(u,n) forn(v, u) {
      double d = sqr(x[u]-x[v]) + sqr(y[u]-y[v]);
      dp[u][v] = dp[v][u] = ( d > 100 + eps ? inf : sqrt(d) );
    }
    vvd mn = dp;
    forn(k,n) forn(u,n) if( !eq(dp[u][k], inf) ) forn(v,n) if( !eq(dp[k][v], inf) ) {
      dp[u][v] = min(dp[u][v], dp[u][k] + dp[k][v]);
      mn[u][v] = min(mn[u][v], max(mn[u][k], mn[k][v]));
    }
    double worse_edge = 0, worse_cost = 0;
    forn(u,n) forn(v,u) {
      worse_edge = max(worse_edge, mn[u][v]);
      worse_cost = max(worse_cost, dp[u][v]);
    }
    cout<<"Case #"<<ci+1<<":\n";
    if( worse_edge > 10 + eps )
      cout<<"Send Kurdy\n";
    else
      cout<<worse_cost<<"\n";
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}