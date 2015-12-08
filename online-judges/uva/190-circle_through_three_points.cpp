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
  double len() const { return hypot(x,y); }
  Point rotate() const { return {-y,x}; }
  Point operator + (const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator - (const Point& p) const { return {x - p.x, y - p.y}; }
  Point operator * (double m) const { return {x * m, y * m}; }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  double angle_to(const Point& p) const { return atan2(*this * p, *this % p); }
  bool on_line(const Point& a, const Point& b) const { return eq(0, (b - a) * (*this - a)); }
};

int lines_intersection(const Point& a, const Point& b, const Point& c, const Point& d, Point& O) {
  double s1 = (d - a) * (c - a);
  double s2 = (c - b) * (d - b);
  double s = s1 + s2;
  if( eq(s, 0) ) {
    if( a.on_line(c,d) )  
      return inf;
    return 0;
  }
  O = a + (b - a) * (s1 / s);
  return 1;
}

bool circle(const Point& a, const Point& b, const Point& c, Point& O, double& r) {
  Point A = a + (b-a) * 0.5;
  Point B = A + ((b-a) * 0.5).rotate();
  Point C = a + (c-a) * 0.5;
  Point D = C + ((c-a) * 0.5).rotate();
  if( lines_intersection(A, B, C, D, O) != 1  ) 
    return false;
  r = (O - a).len();
  return true;
}

string format(double x) {
  ostringstream out;
  out<<setprecision(3)<<fixed;
  bool neg = x < 0;
  if( neg ) x = -x;
  out<<( neg ? "- " : "+ ")<<x;
  return out.str();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  cout<<setprecision(3)<<fixed;
  
  Point a,b,c;
  while( cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y ) {
    Point O;
    double r;
    if( circle(a,b,c,O,r) ) {
      cout<<"(x "<<format(-O.x)<<")^2 + (y "<<format(-O.y)<<")^2 = "<<r<<"^2\n";
      cout<<"x^2 + y^2 "<<format(-2 * O.x)<<"x "<<format(-2 * O.y)<<"y "<<format(sqr(O.x) + sqr(O.y) - sqr(r))<<" = 0\n";
    }
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
