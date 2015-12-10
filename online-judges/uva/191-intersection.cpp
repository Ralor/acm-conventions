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
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  double angle_to(const Point& p) const { return atan2(*this * p, *this % p); }
  bool on_segment(const Point& a, const Point& b) const {
    return eq((b - a).len(), (*this - a).len() + (*this - b).len());
  }
};

bool intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
  if( eq(0, (b - a) * (d - c)) )
    return a.on_segment(d, c) || b.on_segment(d, c);
  double s1 = (b - a).angle_to(c - a), s2 = (b - a).angle_to(d - a);
  double s3 = (d - c).angle_to(a - c), s4 = (d - c).angle_to(b - c);
  return s1 * s2 < eps && s3 * s4 < eps;
}
bool contains(const Point& a, const Point& b, const Point& c, const Point& d, const Point& p) {
  double s = 0;
  s += fabs((b - a) * (p - a));
  s += fabs((c - b) * (p - b));
  s += fabs((d - c) * (p - c));
  s += fabs((a - d) * (p - d));
  double area = fabs((b - a) * (c - a));
  return eq(s/2, area);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Point a,b;
  double l,u,r,d;
  int cn; cin>>cn;
  forn(ci, cn) {
    cin>>a.x>>a.y>>b.x>>b.y>>l>>u>>r>>d;
    if( l > r ) swap(l,r);
    if( d > u ) swap(d,u);
    bool yes = false;
    yes |= intersect(a, b, Point(l,u), Point(r,u));
    yes |= intersect(a, b, Point(r,u), Point(r,d));
    yes |= intersect(a, b, Point(l,d), Point(r,d));
    yes |= intersect(a, b, Point(l,d), Point(l,u));
    yes |= contains(Point(l, u), Point(r, u), Point(r, d), Point(l, d), a);
    yes |= contains(Point(l, u), Point(r, u), Point(r, d), Point(l, d), b);
    cout<<( yes ? "T\n" : "F\n" );
  }
  
  TIMESTAMP("end");
  return 0;
}