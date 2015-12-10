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

const struct {
  int dx, dy;
} DELTAS[ ] = {
  { -2, 1 },
  { -1, 2 },
  { 1, 2 },
  { 2, 1 },
  { 2, -1 },
  { 1, -2 },
  { -1, -2 },
  { -2, -1 },
};

int n;

struct Point {
  int x,y;
  bool black;
  vector<Point*> adj;
  bool used = false;

  Point() { }
  Point(int x, int y, bool black = true) : x(x), y(y), black(black) { }
  Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  bool on_line(const Point& a, const Point& b) const { return eq(0, (*this-a)*(b-a)); }
  bool on_segment(const Point& a, const Point& b) const {
    return on_line(a,b) && (a - *this) % (b - *this) < eps;
  }
  bool operator == (const Point& p) const { return x == p.x && y == p.y; }

  bool CanCreateSegment(const Point& p) const {
    for (auto& d: DELTAS)
      if (x == p.x + d.dx && y == p.y + d.dy)
        return true;
    return false;
  }

  bool Dfs() {
    if (x == n)
      return true;
    if (used)
      return false;
    used = true;
    for (auto p: adj) {
      assert(black == p->black);
      if (p->Dfs())
        return true;
    }
    return false;
  }
};

struct Segment {
  Point* a;
  Point* b;

  Segment() { }
  Segment(Point* a, Point* b): a(a), b(b) { }
};

bool segments_intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
  if( a == c || a == d || b == c || b == d )
    return false;
  double s1 = (b - a) * (c - a), s2 = (b - a) * (d - a);
  double s3 = (d - c) * (a - c), s4 = (d - c) * (b - c);
  //DOUT(s1 _ s2 _ s3 _ s4);
  if( eq(s1, 0) && eq(s2, 0) && eq(s3, 0) && eq(s4, 0) )
    return a.on_segment(c, d) || b.on_segment(c, d);
  return s1 * s2 < eps && s3 * s4 < eps;
}

bool segments_intersect(const Segment& a, const Segment& b) {
  return segments_intersect(*a.a, *a.b, *b.a, *b.b);
}

deque<Point> points;
vector<Segment> segments;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  /*
  bool test1 = segments_intersect({-1,0}, {1,0}, {0, -1}, {0, 1});
  bool test2 = segments_intersect({-2,-2}, {1,1}, {-3, -3}, {-1, -1});
  bool test3 = segments_intersect({-2,-2}, {-1,-1}, {3, 3}, {-1, -1});
  bool test4 = segments_intersect({-2,-2}, {-1,-1}, {3, 3}, {0, 0});
  DBG(test1); DBG(test2); DBG(test3); DBG(test4);
  */
  int i, m;
  while (cin >> n >> m, n) {
    points.clear();
    segments.clear();
    bool black = true;
    for (i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      points.emplace_back(x, y, black);
      auto cur = &points.back();
      for (auto& p: points)
        if (&p != cur && p.black == black && cur->CanCreateSegment(p)) {
          Segment curSeg(&p, cur);
          for (auto& sg: segments)
            if (segments_intersect(sg, curSeg))
              goto nextPoint;
          segments.push_back(curSeg);
          p.adj.push_back(cur);
          cur->adj.push_back(&p);
        nextPoint:
          ;
        }
      black = !black;
    }
    for (auto& p: points)
      if (p.black && !p.x && p.Dfs()) {
        cout << "yes\n";
        goto yes;
      }
    cout << "no\n";
  yes:
    ;
  }
  TIMESTAMP("end");
  return 0;
}
