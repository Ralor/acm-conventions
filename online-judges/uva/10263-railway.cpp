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

struct Point {
  double x,y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double len() const { return hypot(x,y); }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  Point operator * (double m) const { return Point(x * m, y * m); }
  Point norm(double m = 1.0) const { return *this * (m / len()); }
  bool on_line(const Point& a, const Point& b) const { return eq(0, (*this - a) * (b-a)); }
  bool on_segment(const Point& a, const Point& b) const {
    return on_line(a,b) && (a - *this) % (b - *this) < eps;
  }
  Point getH(const Point& a, const Point& b) const {
    Point v = b - a;
    return a + v.norm(v % (*this - a) / v.len());
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout<<setprecision(4)<<fixed;
  
  Point M;
  int n;
  while( cin>>M.x>>M.y>>n ) {
    n = n + 1;
    vector<Point> p(n);
    forn(i,n) 
      cin>>p[i].x>>p[i].y;
    double mn = DBL_MAX;
    Point O;
    forn(i,n-1) {
      Point P = M.getH(p[i], p[i+1]);
      double d;
      if( P.on_segment(p[i], p[i+1]) ) {
        d = (M - P).len();
        if( mn > d )
          tie(mn, O) = mp(d, P);
      } else {
        d = (M - p[i]).len();
        if( mn > d )
          tie(mn, O) = mp(d, p[i]);
        d = (M - p[i+1]).len();
        if( mn > d )
          tie(mn, O) = mp(d, p[i+1]);
      }
    }
    cout<<O.x<<"\n"<<O.y<<"\n";
  }

  TIMESTAMP("end");
  return 0;
}
