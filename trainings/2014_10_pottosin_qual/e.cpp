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
#ifdef LOCAL_PROJECT
#   include <conio.h>
#endif

#ifndef LOCAL_PROJECT
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
#define mt       make_tuple
#define pb       push_back

using namespace std;

#define forn(i, n) for(int i = 0; i < (n); ++i)

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_;
template<typename I> inline void in(I l,I r)
{while(l!=r)cin>>*l,++l;}
template<typename I> inline void out(I l,I r,char D=' ')
{if(l!=r){cout<<*l;while(++l!=r)cout<<D<<*l;}cout<<'\n';}



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
  double x,y,z;
  Point() {}
  Point(double x, double y, double z) : x(x), y(y), z(z) {}
  
  Point normalize() {
    double d = len();
    x = x/d;
    y = y/d;
    z = z/d;    
    return *this;
  }
  double sqr_len() const {
    return sqr(x) + sqr(y) + sqr(z);
  }
  double len() const {
    return sqrt(sqr_len());
  }
  Point operator + (const Point& p) const {
    return Point(x+p.x, y+p.y, z+p.z);
  }
  Point operator - (const Point& p) const {
    return Point(x-p.x, y-p.y, z-p.z);
  }
  Point operator * (const Point& p) const {
    return Point(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
  }
  Point operator * (const double& c) const {
    return Point(x*c, y*c, z*c);
  }
  double orient_area() const {
    return x+y+z;
  }
  double operator % (const Point& p) const {
    return x*p.x + y*p.y + z*p.z;
  }
  double angle_to(const Point& p) const {
    return atan2((*this * p).orient_area(), *this%p);
  }
};

struct Segment {
  Point a,b;
  Segment() { }
  Segment(Point& a, Point& b) : a(a), b(b) {}
  Point get_at(double mul) const {
    return a + (b-a) * mul;
  }
};

struct Circle {
  Point c;
  double r;
  Circle() {}
  Circle(Point& c, double r) : c(c), r(r) {}
};

double ang_delta(const Point& v, const Point& v1, const Point& v2) {
  return fabs(fabs(v.angle_to(v1)) - fabs(v.angle_to(v2)));
}

int main() {
#   ifdef LOCAL_PROJECT
        freopen("e.in", "r", stdin);
#   else
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#   endif
    
    double cx,cy,cz,cr;
    double ax,ay,az;
    double bx,by,bz;
    
    while( cin >> cx >> cy >> cz >> cr >> ax >> ay >> az >> bx >> by >> bz ) {

      Circle c(Point(cx,cy,cz),cr);
      Point a(ax,ay,az),b(bx,by,bz);
      
      a = a - c.c;
      b = b - c.c;
      c.c = Point(0,0,0);

      Segment s(a,b);  

      double l = 0, r = 1.0;
      while( l + eps < r ) {
        double len = r-l;
        double m1 = l + len * (1.0 / 3.0);
        double m2 = l + len * (2.0 / 3.0);
        Point p1 = s.get_at(m1);
        Point p2 = s.get_at(m2);
        double v1 = (a - c.c).angle_to(p1 - c.c);
        double v2 = (a - c.c).angle_to(p2 - c.c);
        if( v1 + eps < v2 )
          l = m1;
        else
          r = m2;
      }      
      Point res(s.get_at(r).normalize() * c.r);
      Point t(c.c - s.a);
      double bb = acos(c.r / t.len());
      double aa = fabs(t.angle_to(res - s.a));
      debug << aa << " " << bb << "\n";
      cout << aa/bb << "\n";
    }

#   ifdef LOCAL_PROJECT
        _getch();
#   endif
    return 0;
}
