#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
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
#ifdef _DEBUG
#   include <conio.h>
#endif

#ifndef _DEBUG
#   undef VERBOSE
#endif

#define eps      1e-8
#define inf      (1000 * 1000 * 1000)
#define linf     (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)   ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)    int((x).size())
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define mp       make_pair

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;

struct Point {
  double x,y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  double size() const {
    return sqrt(size_sqr());
  }
  double size_sqr() const {
    return sqr(x) + sqr(y);
  }
  void normalize(double len = 1.0) {
    double s = size();
    x /= s; y /= s;
    x *= len; y *= len;
  }
  Point& operator=(const Point& p) {
    x = p.x; y = p.y;
    return *this;
  }
  bool operator==(const Point& p) const {
    return p.x == x && p.y == y;
  }
};

namespace Geo {
  Point get_center(Point& p1, Point& p2) {
    return Point((p1.x+p2.x)/2,(p1.y+p2.y)/2);
  }

  double get_hull_s(Point& p1, Point& p2) {
    return (p2.x-p1.x) * ((p1.y + p2.y)/2);
  }

  double dec_get_r(Point& p) {
    return p.size();
  }
  double dec_get_a(Point& p) {
    return acos(p.x/p.size());
  }
  double pol_get_x(double r, double a) {
    return r * cos(a);
  }
  double pol_get_y(double r, double a) {
    return r * sin(a);
  }
  void rotate_vector(Point& v, double angle) {    
    double r = dec_get_r(v);
    double a = dec_get_a(v) + angle;    
    v.x = pol_get_x(r,a);
    v.y = pol_get_y(r,a);
  }
  double get_vectors_s(Point& a, Point& b) {
    return a.x*b.y - a.y*b.x;
  }
  int is_vec_line_intersect(Point& vec, Point& p1, Point& p2) {
    
    return false;
  }
  Point get_vec_line_intersect(Point& vec, Point& p1, Point& p2) {
    vec.normalize();
    int code = is_vec_line_intersect(vec,p1,p2);
    if( code == 0 )
      return Point(-1,-1);
    if( code == 1 )
      return p1;
    if( code == 2 )
      return p2;

    int init_sign = get_vectors_s(Point(

  }
}

double get_convex_s(vector<Point>& p) {
  double result = 0;
  Point prev = p[0];
  int cnt = sz(p), ind = 1;
  while( cnt-- ) {
    Point& cur = p[ind]; ++ind; ind %= sz(p);
    result += Geo::get_hull_s(prev,cur);
    prev = cur;
  }
  return fabs(result);
}



int main() {
#   ifdef _DEBUG
        freopen("l.in", "r", stdin);
#   else
        freopen("l.in", "r", stdin);
        freopen("l.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tests; cin >> tests;

    while( tests-- ) {
      int n; cin >> n;
      double mnx = -1, mny = -1;
      vector<Point> p(n);
      for(int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].x += 10*1000+1;
        p[i].y += 10*1000+1;
      }
      
      Point cam(Geo::get_center(p[0],p[1]));
      Point beam1(cam.x - p[0].x, cam.y - p[0].y);
      beam1.normalize();
      Point beam2(cam.x - p[1].x, cam.y - p[1].y);
      beam2.normalize();

    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
