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
  
  int ci = 1;
  
  int n;
  while( cin>>n, n ) {
    vvi dp(n, vi(n, inf)), par(n, vi(n, -1));
    forn(u,n) {
      dp[u][u] = 0;
      int x; cin>>x;
      while( x-- ) {
        int v; cin>>v; --v;
        cin>>dp[u][v];
        par[u][v] = u;
      }
    }
    forn(k,n) forn(u,n) if( dp[u][k] < inf ) forn(v,n) if( dp[k][v] < inf) {
      if( dp[u][v] > dp[u][k] + dp[k][v] ) {
        dp[u][v] = dp[u][k] + dp[k][v];
        par[u][v] = par[k][v];
      }
    }
    forn(u,n) {
      forn(v,n)
        debug<<setw(2)<<(~par[u][v]?par[u][v]+1:-1)<<" ";
      debug<<"\n";
    }
    
    int from, to; cin>>from>>to; --from; --to;
    int dist = dp[from][to];
    vi path;
    while( ~to )
      path.eb(to), to = par[from][to];
    cout<<"Case "<<ci++<<": Path =";
    for_each(rall(path), [](int u) {
      cout<<" "<<u+1;
    });
    cout<<"; "<<dist<<" second delay\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
