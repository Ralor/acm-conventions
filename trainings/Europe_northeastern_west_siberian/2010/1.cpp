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

const double PI = atan(1) * 4;

struct Point {
  double x,y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }  
  double len() const { return hypot(x, y); }
  Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  Point operator * (double m) const { return Point(x * m, y * m); }
  void from_polar(double r, double ang) {
    x = r * cos(ang);
    y = r * sin(ang);    
  }
};

double f(Point& a, Point& b, Point& v1, Point& v2, double tm) {
  return ((a + v1 * tm) - (b + v2 * tm)).len();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  cout<<setprecision(2)<<fixed;
  
  Point a,b;
  while( cin>>a.x>>a.y>>b.x>>b.y ) {
    Point v1,v2;
    double ang1, s1;
    double ang2, s2;
    cin>>ang1>>s1>>ang2>>s2;
    ang1 = ang1 / 360 * 2 * PI;
    ang2 = ang2 / 360 * 2 * PI;
    v1.from_polar(s1, ang1);
    v2.from_polar(s2, ang2);
    cin>>v1.x>>v1.y>>v2.x>>v2.y;
    DOUT(v1.x _ v1.y _ v2.x _ v2.y);
    double l = 0, r = 1000;
    double x = 0;
    forn(steps, 100) {
      double x1 = l + 1.0 / 3 * (r - l);
      double x2 = l + 2.0 / 3 * (r - l);
      double f1 = f(a,b,v1,v2,x1);
      double f2 = f(a,b,v1,v2,x2);
      DOUT(x1 _ x2 _ f1 _ f2);
      if( f1 < f2 )
        x = r = x2;
      else
        x = l = x1;
    }
    DOUT(l _ r);
    cout<<f(a,b,v1,v2,x)<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}


