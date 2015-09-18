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
  forn(ci, cn) {
    int n,m; cin>>n>>m;
    int u,v,c;
    vector<vector<pii>> g(n);
    forn(i,m) {
      cin>>u>>v>>c;
      g[u].eb(v,c);
      g[v].eb(u,c);
    }
    queue<int> sq;
    int l = 0, r = 1001;
    while( l + 1 < r ) {
      int mid = (l+r)/2;
      sq.push(0);
      int cnt = 0;
      vi used(n);
      used[0] = 1;
      while( !sq.empty() ) {
        u = sq.front(); sq.pop();
        ++cnt;
        for(auto p : g[u]) {
          tie(v,c) = p;
          if( used[v] || c < mid ) continue;
          sq.push(v); 
          used[v] = 1;
        }
      }
      if( cnt == n )
        l = mid;
      else
        r = mid;
    }
    cout<<"Case #"<<ci+1<<": "<<l<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}