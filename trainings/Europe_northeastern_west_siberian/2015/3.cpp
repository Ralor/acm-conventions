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
  double x,y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double len() const { return hypot(x, y); }
  Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  double angle_to(const Point& p) const { return atan2(*this * p, *this % p); }
  Point from_polar(double r, double a) const { return Point(r * cos(a), r * sin(a)); }
  Point rotate_around(const Point& p, double angle) const {
    Point a = *this - p;
    return p + from_polar(a.len(), atan2(a.y, a.x) + angle);
  }
  Point operator * (double m) { return Point(x * m, y * m); }
  bool operator == (const Point& p) const { return eq(x, p.x) && eq(y, p.y); }
  Point operator = (const Point& p) { tie(x,y) = mp(p.x, p.y); return *this; }
};

struct Rect {
  Point a[4], ap[4];
  Rect(double h, double w) {
    a[0].x = -w/2; a[0].y = h/2;
    ap[0].x = h; ap[0].y = 0;
    
    a[1].x = w/2; a[1].y = h/2;
    ap[1].x = 0; ap[1].y = -h;
    
    a[2].x = w/2; a[2].y = -h/2;
    ap[2].x = -w; ap[2].y = 0;
    
    a[3].x = -w/2; a[3].y = -h/2;
    ap[3].x = 0; ap[3].y = h;
  }
  bool contains(const Point& p) const {
    int s = 0;
    if( p == a[0] || p == a[1] || p == a[2] || p == a[3] )
      return true;
    forn(i,4)
      s += ap[i].angle_to(p - a[i]) < eps;
    return s >= 3;
  }
  double area() const {
    return ap[0].len() * ap[1].len();
  }
  void rand_point(Point& p) const {
    Point corner = a[0];
    double w = ap[0].len();
    double h = ap[3].len();
    p = corner + Point(rand() / (RAND_MAX + 1.0) * w, rand() / (RAND_MAX + 1.0) * h);
  }
  void rotate_around(const Point& p, double ang) {
    forn(i,4) {
      a[i] = a[i].rotate_around(p, ang); 
      ap[i] = ap[i].rotate_around(Point(0,0), ang);
    }
  }
};

double f(Rect& a, Rect& b) {
  const int test_cnt = 10 * 1000;
  int succ_cnt = 0;
  forn(test, test_cnt) {
    Point p;
    a.rand_point(p);
    if( b.contains(p) )
      ++succ_cnt;
  }
  return succ_cnt * 1.0 / test_cnt * b.area();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  cout<<setprecision(9)<<fixed;
  
  double sa,sb,sc;
  while( cin>>sa>>sb>>sc ) {
    Rect a(sa,sa), b(sb,sc);
    if( a.area() > b.area() )
      swap(a,b);
    
    double l = 0, r = PI / 2;
    DOUT(l _ r);
    forn(i, 100) {
      double x1 = l + 1.0 / 3 * (r-l);
      double x2 = l + 2.0 / 3 * (r-l);
      Rect temp = b;
      temp.rotate_around(Point(0,0), x1);
      double f1 = f(a, temp);
      temp = b;
      temp.rotate_around(Point(0,0), x2);
      double f2 = f(a, temp);
      if( f1 > f2 )
        r = x2;
      else
        l = x1;
    }
    DBG(l);
    b.rotate_around(Point(0,0), l);
    DOUT(b.a[0].x _ b.a[0].y);
    cout<<f(a,b)<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
