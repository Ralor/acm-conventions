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

  int m;
  while( cin>>m, m ) {
    vvi ay(26, vi(26, inf)), am(26, vi(26, inf));
    forn(edge, m) {
      char type, dir;
      char u,v;
      int cost;
      cin>>type>>dir>>u>>v>>cost;
      u -= 'A'; v -= 'A';
      vvi& a = (type == 'Y' ? ay : am);
      if( dir == 'B' )
        a[u][v] = a[v][u] = cost;
      else
        a[u][v] = cost;
    }
    forn(u, 26)
      ay[u][u] = am[u][u] = 0;
    forn(k, 26) forn(i, 26) forn(j, 26) {
      ay[i][j] = min(ay[i][j], ay[i][k] + ay[k][j]);
      am[i][j] = min(am[i][j], am[i][k] + am[k][j]);
    }
    char me, prof; cin>>me>>prof;
    me -= 'A'; prof -= 'A';
    int result_cost = inf;
    vi result_vertexes;
    forn(u, 26) {
      int cost = ay[me][u] + am[prof][u];
      if( cost < inf && result_cost == cost )
        result_vertexes.eb(u);
      if( result_cost > cost )
        tie(result_cost, result_vertexes) = mp(cost, vi({u}));
    }
    if( !result_vertexes.empty() ) {
      cout<<result_cost;
      for(int u : result_vertexes)
        cout<<" "<<char('A' + u);
      cout<<"\n";
    } else {
      cout<<"You will never meet.\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}