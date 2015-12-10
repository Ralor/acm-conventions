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


struct Point {
  double x,y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double dist(const Point& p) const {
    return sqrt(sqr(x-p.x) + sqr(y-p.y));
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  #ifndef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  cout<<setprecision(9)<<fixed;
  
  int n,m,k;
  double v_byc, v_foot;
  while( cin>>n>>m>>k>>v_byc>>v_foot ) {
    vector<Point> p(n);
    forn(i,n)
      cin>>p[i].x>>p[i].y;
    vvi g(n);
    forn(i,m) {
      int u,v; cin>>u>>v;
      --u; --v;
      g[u].eb(v);
      g[v].eb(u);
    }
    vi to_visit(k+1);
    forn(i,k)
      cin>>to_visit[i], --to_visit[i];
    to_visit[k] = n-1;
    int start = 0;
    vi path;
    double total_distance = 0;
    for(int target : to_visit) {
      vector<double> dist(n, 1e14);
      vi par(n, -1), used(n);
      dist[start] = 0;
      forn(iter, n) {
        int u = -1;
        forn(i,n) if( !used[i] ) {
          if( u == -1 || (~u && dist[i] < dist[u]) )
            u = i;
        }
        if( u == target ) 
          break;
        used[u] = 1;
        for(int v : g[u]) if( !used[v] ){
          double t = p[u].dist(p[v]) / v_byc;
          if( dist[v] > dist[u] + t ) {
            dist[v] = dist[u] + t;
            par[v] = u;
          }
        }
        forn(v,n) if( !used[v] ) {
          double t = p[u].dist(p[v]) / v_foot;
          if( dist[v] > dist[u] + t ) {
            dist[v] = dist[u] + t;
            par[v] = u;
          }
        }
      }
      vi cur_path;
      for(int u = target; ~u; u = par[u])
        cur_path.eb(u);
      debug<<"Path from "<<start+1<<" to "<<target+1<<":\n";
      reverse(all(cur_path));
      for(int i = 0; i < sz(cur_path) - 1; i++)
        path.eb(cur_path[i]),debug<<cur_path[i]+1<<" ";
      debug<<"\n";
      total_distance += dist[target];
      start = target;
    }
    DBG(n);
    path.eb(n-1);
    cout<<total_distance<<"\n";
    for(int u : path)
      cout<<u+1<<" ";
    cout<<"\n";
    debug<<"===\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
