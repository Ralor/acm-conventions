#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <fstream>
#include <bitset>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifndef _DEBUG
# undef VERBOSE
#endif
#ifdef NDEBUG
#define VERBOSE
#endif

#define eps 1e-8
#define inf (1000 * 1000 * 1000)
#define linf (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x) ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x) int((x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define mp make_pair

using namespace std;

typedef unsigned uint;
typedef long long llong;
typedef unsigned long long ullong;
typedef long double ldouble;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
struct debug_t {
  template <typename T>
  debug_t& operator<<(const T& value) {
# ifdef VERBOSE
    cout << value;
# endif
    return *this;
  }
} debug;

struct Point {
  int x,y;
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}
  bool operator<(const Point& a) const {
    return mp(x,y) < mp(a.x,a.y);
  }
  bool operator==(const Point& a) const {
    return x == a.x && y == a.y;
  }
};

struct Line {
  int coord;
  bool vert;
  Line() {}
  Line(int coord, bool vert = true) : coord(coord), vert(vert) {}
  bool operator<(const Line& l) const {
    return mp(coord, vert) < mp(l.coord, l.vert);
  }
  bool operator==(const Line& l) const {
    return coord == l.coord && vert == l.vert;
  }
};

struct Rect {
  Point lp, rp;
  Rect() : lp(Point()), rp(Point()) { }
  Rect(Point lp, Point rp)
    : lp(lp), rp(rp) {
    if( this->lp.x > this->rp.x ) swap(this->lp.x, this->rp.x);
    if( this->lp.y > this->rp.y ) swap(this->lp.y, this->rp.y);
  }
  int get_area() const {
    return (rp.x-lp.x)*(rp.y-lp.y);
  }
  bool contains(const Point& p) const {
    return lp.x <= p.x && p.x <= rp.x &&
           lp.y <= p.y && p.y <= rp.y;
  }
  bool contains(const Rect& r) const {
    bool yes = true;
    yes &= this->contains(r.lp);
    yes &= this->contains(r.rp);
    yes &= this->contains(Point(r.lp.x,r.rp.y));
    yes &= this->contains(Point(r.rp.x,r.lp.y));
    return yes;
  }
  bool intersect_strictly(const Line& l) const {
    if( l.vert )
      return lp.x < l.coord && l.coord < rp.x;
    else
      return lp.y < l.coord && l.coord < rp.y;
  }
  pair<Rect,Rect> divide(const Line& l) const {
    Rect f,s;
    if( l.vert ) {
      Point mid_up(l.coord, rp.y), mid_down(l.coord, lp.y);
      return mp(Rect(lp,mid_up), Rect(mid_down, rp));
    } else {
      Point mid_left(lp.x, l.coord), mid_right(rp.x, l.coord);
      return mp(Rect(mid_left, rp), Rect(lp, mid_right));
    }
  }
  Line get_left_bnd() const {
    return Line(lp.x, true);
  }
  Line get_right_bnd() const {
    return Line(rp.x, true);
  }
  Line get_down_bnd() const {
    return Line(lp.y, false);
  }
  Line get_up_bnd() const {
    return Line(rp.y, false);
  }
  bool operator<(const Rect& r) const {
    return mp(lp,rp) < mp(r.lp, r.rp);
  }
  bool operator==(const Rect& r) const {
    return mp(lp,rp) == mp(r.lp, r.rp);
  }
};

int main() {
  //freopen(TASK ".in", "r", stdin);
  //freopen(TASK ".out", "w", stdout);
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  while( cin >> n ) {
    vector<Rect> a;
    vector<Line> lines;
    for(int i = 0; i < n; i++) {
      int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
      Rect rect(Point(x1,y1),Point(x2,y2));
      a.push_back(rect);
      lines.push_back(rect.get_left_bnd());
      lines.push_back(rect.get_right_bnd());
      lines.push_back(rect.get_down_bnd());
      lines.push_back(rect.get_up_bnd());
    }

    for(int i = 0; i < sz(lines); i++)
      for(int j = 0; j < sz(a); j++)
        if( a[j].intersect_strictly(lines[i]) ) {
          pair<Rect, Rect> p = a[j].divide(lines[i]);
          a[j] = p.first;
          a.push_back(p.second);
        }
    set<Rect> ss(all(a));
    //sort(all(a));
    //a.resize(unique(all(a)) - a.begin());

    int result = 0;
    for(set<Rect>::iterator it = ss.begin(); it != ss.end(); it++)
      result += it->get_area();
    cout << result << "\n";
  }

  return 0;
}
