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

struct Point {
  double x,y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double dist(const Point& p) const {
    return sqrt(sqr(x - p.x) + sqr(y - p.y));
  }
};

void rec(int& result, vector<vector<pair<int,double>>>& g, vi& value, int cnt, int u) {
  if( cnt >= result || u > sz(g) )
    return;
  if( u == sz(g) ) {
    result = min(result, cnt);
    return;
  }
  int cur_freq = -1;
  for(int old_freq : value) if( ~old_freq && cur_freq == -1 ){
    bool ok = true;
    for(auto p : g[u]) {
      int v; double c;
      tie(v,c) = p;
      if( ~value[v] )
        ok &= abs(old_freq - value[v]) >= 2;
    }
    if( ok ) cur_freq = old_freq;
  }
  bool new_value_req = false;
  for(int new_freq = 1; cur_freq == -1; new_freq++) {
    bool ok = true;
    for(auto p : g[u]) {
      int v; double c;
      tie(v,c) = p;
      if( ~value[v] )
        ok &= abs(new_freq - value[v]) >= 2;
    }
    if( ok ) cur_freq = new_freq, new_value_req = true;
  }
  value[u] = cur_freq;
  rec(result, g, value, new_value_req ? cnt+1 : cnt, u+1);
  value[u] = -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int ci = 1;
  int n;
  while( cin>>n, n ) {
    vector<Point> points(n);
    forn(i,n)
      cin>>points[i].x>>points[i].y;
    vector<vector<pair<int,double>>> g(n);
    forn(u,n) forn(v,u) if( points[u].dist(points[v]) <= 20 ) {
      double c = points[u].dist(points[v]);
      g[u].eb(v,c);
      g[v].eb(u,c);
    }
    vi value(n, -1);
    int result = inf;
    rec(result,g,value,0,0);
    cout<<"The towers in case "<<ci++<<" can be covered in "<<result<< " frequencies.\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
