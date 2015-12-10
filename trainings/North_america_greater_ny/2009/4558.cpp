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

const double PI = atan(1) * 4;

struct Point {
  int x,y;
  double len() const { return hypot(x,y); }
  Point operator - (const Point& p) const { return {x - p.x, y - p.y}; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int cn; cin>>cn;
  while( cn-- ) {
    int ci; cin>>ci;
    int n; cin>>n;
    vector<Point> p(n);
    int start = 0;
    forn(i,n) {
      cin>>p[i].x>>p[i].y;
      if( p[start].y < p[i].y || (p[start].y == p[i].y && p[start].x > p[i].x) )
        start = i;
    }
    DBG(n);
    int cur = start;
    Point dir = {1,0};
    vector<Point> result;
    do {
      int nxt = (cur == 0 ? 1 : 0);
      result.eb(p[cur]);
      forn(i,n) 
        if( i != cur ) {
          double i_len = (p[i] - p[cur]).len();
          double i_cos = dir % (p[i] - p[cur]) / (dir.len() * i_len);
          double nxt_len = (p[nxt] - p[cur]).len();
          double nxt_cos = dir % (p[nxt] - p[cur]) / (dir.len() * nxt_len);
          if( i_cos > nxt_cos + eps || (eq(i_cos, nxt_cos) && i_len > nxt_len) )
            nxt = i;
        }
      tie(dir, cur) = mp(p[nxt] - p[cur], nxt);
    } while( cur != start );
    cout<<ci<<" "<<sz(result)<<"\n";
    for(Point p : result)
      cout<<p.x<<" "<<p.y<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
