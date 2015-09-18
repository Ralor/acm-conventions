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
    vector<tuple<int,int,int>> edges;
    forn(i,m) {
      cin>>u>>v>>c;
      edges.eb(u,v,c);
    }
    queue<int> sq;
    int l = 0, r = 1001;
    while( l + 1 < r ) {
      int mid = (l+r)/2;
      vector<vector<pii>> g(n);
      for(auto e : edges) {
        tie(u,v,c) = e;
        g[u].eb(v,c);
        g[v].eb(u,c);
      }
      vi color(n, -1);
      sq.push(0);
      int cnt = 0;
      DBG(mid);
      forn(start, n)
        if( color[start] == -1 ) {
          color[start] = cnt++;
          sq.push(start);
          while( !sq.empty() ) {
            u = sq.front(); sq.pop();
            DBG(u);
            for(auto p : g[u]) {
              tie(v,c) = p;
              if( ~color[v] || c < mid ) continue;
              DOUT("Go to" _ v<<"("<<c<<")");
              sq.push(v); 
              color[v] = color[start];
            }
          }
        }
      if( cnt == 1 ) {
        l = mid;
        DOUT("Yes we can!");
        // remove edges with w(u,v) < mid (we can achieve cnt == 1 without them)
        cnt = 0;
        for(auto e : edges) {
          tie(u,v,c) = e;
          if( c >= mid )
            edges[cnt++] = e;
        }
        edges.resize(cnt);
        // edge deletion may produce vertexes with deg(u) = 0
        vi ntoi(n, -1);
        cnt = 0;
        for(auto& e : edges) {
          tie(u,v,c) = e;
          u = ~ntoi[u] ? ntoi[u] : ntoi[u] = cnt++;
          v = ~ntoi[v] ? ntoi[v] : ntoi[v] = cnt++;
          e = mt(u,v,c);
        }
        n = cnt;
      } else {
        r = mid;
        DOUT("We must decrease weight limit");
        // merge components into 1 vertex
        n = cnt;
        cnt = 0;
        for(auto e : edges) {
          tie(u,v,c) = e;
          if( color[u] != color[v] )
            edges[cnt++] = mt(color[u], color[v], c);
        }
        edges.resize(cnt);
      }
    }
    cout<<"Case #"<<ci+1<<": "<<l<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}