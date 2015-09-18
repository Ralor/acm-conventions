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

  int cn; cin>>cn;
  forn(ci,cn) {
    int n; cin>>n;
    vector<pii> coord(n);
    forn(i,n)
      cin>>coord[i].first>>coord[i].second;
    vvi conn(n, vi(n));
    int m; cin>>m;
    forn(i,m) {
      int u,v; cin>>u>>v;
      --u; --v;
      conn[u][v] = conn[v][u] = 1;
    }
    vi dist(n, inf), used(n), par(n, -1);
    used[0] = 1;
    if( ci )
      cout<<"\n";
    bool found_smth = false;
    for(int mn, u = 0; ~u; u = mn) {
      mn = -1;
      forn(v,n) if( !used[v] ) {
        int d = conn[u][v] ?
          0 : sqr(coord[u].first - coord[v].first) + sqr(coord[u].second - coord[v].second);
        if( dist[v] > d )
          dist[v] = d, par[v] = u;
        if( mn == -1 || dist[v] < dist[mn] )
          mn = v;
      }
      if( ~mn ) {
        if( !conn[mn][par[mn]] )
          cout<<mn+1<<" "<<par[mn]+1<<"\n", found_smth = true;
        used[mn] = 1;
      }
    }
    if( !found_smth )
      cout<<"No new highways need\n";
  }
  
  TIMESTAMP("end");
  return 0;
}