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
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
};

bool segment_intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
  double s1 = (b - a) * (c - a), s2 = (b - a) * (d - a);
  double s3 = (d - c) * (a - c), s4 = (d - c) * (b - c);
  if( eq(0, s1 * s2) && eq(0, s3 * s4) )
    return (c - a) % (d - a) < eps || (c - b) % (d - b) < eps;
  return s1 * s2 < 0 && s3 * s4 < 0;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  while( cin>>n, n ) {
    vi prev(n+1, -1), nxt(n+1, -1);
    vector<Point> a(n+1), b(n+1);
    for(int i = 1; i <= n; i++) {
      cin>>a[i].x>>a[i].y>>b[i].x>>b[i].y;
      nxt[i] = i+1;
      prev[i] = i-1;
      nxt[i-1] = i;
      for(int j = nxt[0]; j < i; j = nxt[j])
        if( segment_intersect(a[i], b[i], a[j], b[j]) ) 
          tie(nxt[prev[j]], prev[nxt[j]]) = mp(nxt[j], prev[j]);
    }
    cout<<"Top sticks:";
    for(int j = nxt[0], cnt = 0; j <= n; j = nxt[j], ++cnt)
      cout<<( cnt ? ", " : " " )<<j;
    cout<<".\n";
  }
  
  TIMESTAMP("end");
  return 0;
}

