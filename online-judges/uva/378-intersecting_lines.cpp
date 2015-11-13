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
  Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  Point operator * (double m) const { return Point(x * m, y * m); }
  Point normalize(double norm = 1.0) const { norm /= len(); return *this * norm; }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  bool on_line(const Point& a, const Point& b) const { return eq(0, (a - *this) * (b - *this)); }
};



int intersect(const Point& a, const Point& b, const Point& c, const Point& d, Point& o) {
  double s1 = (d - b) * (c - b), s2 = (c - a) * (d - a);
  double s = s1 + s2;
  if( eq(s, 0) )
    return a.on_line(c,d) ? -1 : 0;
  Point v = b - a;
  o = a + v.normalize(v.len() * (s2 / s));
  return 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout<<setprecision(2)<<fixed;
  
  cout<<"INTERSECTING LINES OUTPUT\n";
  Point a,b,c,d;
  int cn; cin>>cn;
  forn(ci,cn) {
    cin>>a.x>>a.y>>b.x>>b.y;
    cin>>c.x>>c.y>>d.x>>d.y;
    Point result;
    int code = intersect(a,b,c,d,result);
    if( code == 0 )
      cout<<"NONE\n";
    else if( code == 1 )
      cout<<"POINT "<<result.x<<" "<<result.y<<"\n";
    else
      cout<<"LINE\n";
  }
  cout<<"END OF OUTPUT\n";
  
  TIMESTAMP("end");
  return 0;
}