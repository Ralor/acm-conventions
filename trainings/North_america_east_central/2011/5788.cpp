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
  double len() const { return sqrt(sqr(x) + sqr(y)); }
  double dist(const Point& p) const { return (p - *this).len(); }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  double angle_to(const Point& p) const { return atan2(*this * p, *this % p); }
};

bool intersect(const Point& af, const Point& as, const Point& bf, const Point& bs) {
  double v1 = (bs - bf).angle_to(af - bf), v2 = (bs - bf).angle_to(as - bf);
  double v3 = (as - af).angle_to(bf - af), v4 = (as - af).angle_to(bs - af);
  int s1 = fabs(v1) < eps ? 0 : v1 > 0 ? 1 : -1;
  int s2 = fabs(v2) < eps ? 0 : v2 > 0 ? 1 : -1;
  int s3 = fabs(v3) < eps ? 0 : v3 > 0 ? 1 : -1;
  int s4 = fabs(v4) < eps ? 0 : v4 > 0 ? 1 : -1;
  if( s1 != s2 && s3 != s4 )
    return true;
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  cout<<setprecision(3)<<fixed;
  int ci = 1;
  int ax,ay,bx,by;
  int fx,fy,sx,sy;
  while( cin>>ax>>ay>>bx>>by>>fx>>fy>>sx>>sy ) {
    cout<<"Case "<<ci++<<": ";
    if( !intersect(Point(ax,ay), Point(bx,by), Point(fx,fy), Point(sx,sy)) ) {
      cout<<Point(ax,ay).dist(Point(bx,by)) / 2<<"\n";
    } else {
      double dist1 = sqrt(sqr(ax-fx) + sqr(ay-fy)) + sqrt(sqr(bx-fx) + sqr(by-fy));
      double dist2 = sqrt(sqr(ax-sx) + sqr(ay-sy)) + sqrt(sqr(bx-sx) + sqr(by-sy));
      cout<<min(dist1, dist2) / 2<<"\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
