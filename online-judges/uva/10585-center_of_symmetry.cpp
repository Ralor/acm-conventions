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
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  bool operator == (const Point& p) const { return eq(x, p.x) && eq(y, p.y); }
  bool operator != (const Point& p) const { return !(*this == p); }
};
struct Comparer {
  Comparer(const Point& c) : c(c) { }
  bool operator() (const Point& a, const Point& b) const {
    double a1 = atan2(a.y - c.y, a.x - c.x);
    double a2 = atan2(b.y - c.y, b.x - c.x);
    if( eq(a1, a2) )
      return sqr(a.y - c.y) + sqr(a.x - c.x) < sqr(b.y - c.y) + sqr(b.x - c.x);
    return a1 < a2;
  }
private:
  Point c;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int cn; cin>>cn;
  forn(ci,cn) {
    int n; cin>>n;
    vector<Point> p(n);
    double mx = 0, my = 0;
    forn(i,n) cin>>p[i].x>>p[i].y, mx += p[i].x / n, my += p[i].y / n;
    Point center(mx, my);
    if( n & 1 )
      forn(i,n)
        if( p[i] == center )
          p.erase(begin(p) + i, begin(p) + i + 1), --n;
    sort(all(p), Comparer(center));
    forn(i,n/2)
      if( p[i] - center != center - p[i+n/2] ) {
        cout<<"no\n";
        goto next_case;
      }
    cout<<"yes\n";
next_case:;
  }
  
  TIMESTAMP("end");
  return 0;
}


