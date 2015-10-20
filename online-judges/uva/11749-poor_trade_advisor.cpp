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
#include <assert.h>
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
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);

  int n,m;
  while( scanf("%d%d",&n,&m), n || m ) {
    vector<tuple<int,int,int>> edges;
    int u,v,c, mx = INT_MIN;
    forn(edge, m) {
      scanf("%d%d%d",&u,&v,&c);
      --u; --v;
      if( mx < c )
        mx = c, edges.clear();
      if( mx == c )
        edges.eb(u,v,c);
    }
    vvi g(n);
    DOUT("Used edges:");
    for(auto e : edges) {
      tie(u,v,c) = e;
      DOUT(u+1 _ v+1);
      g[u].eb(v); g[v].eb(u);
    }
    int result = 0;
    vi used(n);
    forn(start,n) if( !used[start] ) {
      DOUT("Start at" _ start + 1);
      int size = 0;
      queue<int> sq;
      used[start] = 1;
      sq.push(start);
      while( !sq.empty() ) {
        u = sq.front(); sq.pop();
        ++size;
        forn(i,sz(g[u])) {
          v = g[u][i];
          if( used[v] ) continue;
          sq.push(v); used[v] = 1;
        }
      }
      DOUT("Component size:" _ size);
      result = max(result, size);
    }
    printf("%d\n",result);
  }
  
  TIMESTAMP("end");
  return 0;
}
