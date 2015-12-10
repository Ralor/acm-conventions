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
  int x,y;
  Point() { }
  Point(int x, int y) : x(x), y(y) { }
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  int operator * (const Point& p) const { return x * p.y - y * p.x; }
  int operator % (const Point& p) const { return x * p.x + y * p.y; }
  bool operator == (const Point& p) const { return x == p.x && y == p.y; }
  bool on_segment(const Point& a, const Point& b) const { 
    return (b - a) * (*this - a) == 0 && (*this - a) % (*this - b) <= 0; 
  }
};

bool intersects(const Point& a, const Point& b, const Point& c, const Point& d) {
  if( a.on_segment(c,d) || b.on_segment(c,d) || c.on_segment(a,b) || d.on_segment(a,b) )
    return true;
  int s1 = (b - a) * (c - a), s2 = (b - a) * (d - a);
  int s3 = (d - c) * (a - c), s4 = (d - c) * (b - c);
  return s1 * 1LL * s2 < 0 && s3 * 1LL * s4 < 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  DBG(intersects({1,1},{2,2},{2,2},{3,3}));
  DBG(intersects({1,1},{2,2},{3,3},{2,2}));
  DBG(intersects({2,2},{1,1},{2,2},{3,3}));
  DBG(intersects({2,2},{1,1},{3,3},{2,2}));
  DBG(intersects({1,2},{1,4},{1,3},{2,3}));
  DBG(intersects({1,2},{1,4},{2,3},{1,3}));
  DBG(intersects({1,4},{1,2},{1,3},{2,3}));
  DBG(intersects({1,4},{1,2},{2,3},{1,3}));
  DBG(intersects({1,1},{3,3},{2,1},{1,2}));
  DBG(intersects({3,3},{1,1},{1,2},{2,1}));
  DBG(intersects({1,1},{3,3},{1,2},{2,1}));
  DBG(intersects({3,3},{1,1},{2,1},{1,2}));
  DBG(intersects({1,1},{2,2},{3,3},{4,4}));
  DBG(intersects({1,1},{2,2},{4,4},{3,3}));
  DBG(intersects({2,2},{1,1},{3,3},{4,4}));
  DBG(intersects({2,2},{1,1},{4,4},{3,3}));
  DBG(intersects({1,1},{2,2},{3,3},{3,2}));
  DBG(intersects({1,1},{2,2},{3,2},{3,3}));
  DBG(intersects({2,2},{1,1},{3,3},{3,2}));
  DBG(intersects({2,2},{1,1},{3,2},{3,3}));
  
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int n; cin>>n;
    vector<Point> a(n), b(n);
    forn(i,n)
      cin>>a[i].x>>a[i].y>>b[i].x>>b[i].y;
    int result = 0;
    forn(i,n) {
      bool isolated = true;
      forn(j,n) if( i != j )
        isolated &= !intersects(a[i],b[i],a[j],b[j]);
      if( isolated )
        ++result;
    }
    cout<<result<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}

