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
  Point(double x, double y) : x(x), y(y) { }
  double len() const { return hypot(x,y); }
  Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator * (double m) const { return Point(x * m, y * m); }
  Point rotate() const { return Point(-y,x); }
  Point rotate(double cosa, double sina) const { return *this*cosa + this->rotate()*sina; }
  Point rotate(double ang) const { return rotate(cos(ang), sin(ang)); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout<<setprecision(4)<<fixed;
  
  int n, ellapsed;
  while( cin>>n>>ellapsed ) {
    Point prev(0,0);
    forn(i,n) {
      int r,t; cin>>r>>t;
      Point cur = prev + Point(r,0).rotate(ellapsed / double(t) * 2 * PI);
      cout<<( i ? " " : "" )<<cur.len();
      prev = cur;
    }
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
