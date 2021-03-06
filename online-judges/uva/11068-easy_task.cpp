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
  double len() const { return hypot(x, y); }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  Point norm(double m = 1.0) const { m /= len(); return Point(x * m, y * m); }
};

void init_line(double A, double B, double C, Point& a, Point& b) {
  DOUT(A _ B _ C);
  if( eq(A, 0) ) {
    DOUT("horizontal line!");
    a = Point(0, -C/B);
    b = a + Point(1, 0);
  } else if( eq(B, 0) ) {
    DOUT("vertical line!");
    a = Point(-C/A, 0);
    b = a + Point(0, 1);
  } else {
    DOUT("usual line...");
    a = Point(0, -C/B);
    b = a + Point(-B, A);
  }
  DOUT("====>" _ a.x _ a.y _ b.x _ b.y);
}

bool intersects(const Point& a, const Point& b, const Point& c, const Point& d, Point& o) {
  double s1 = (c - a) * (d - a), s2 = (d - b) * (c - b);
  double s = s1 + s2;
  if( eq(s, 0) )
    return false;
  Point v = b - a;
  o = a + v.norm(v.len() * (s1 / s));
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout<<setprecision(2)<<fixed;
  
  int A1, B1, C1;
  int A2, B2, C2;
  while( cin>>A1>>B1>>C1>>A2>>B2>>C2, A1 || B1 || C1 || A2 || B2 || C2 ) {
    Point a,b,c,d;
    init_line(A1,B1,-C1,a,b);
    init_line(A2,B2,-C2,c,d);
    Point result;
    if( intersects(a,b,c,d,result) ) 
      cout<<"The fixed point is at "<<result.x<<" "<<result.y<<".\n";
    else
      cout<<"No fixed point exists.\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
