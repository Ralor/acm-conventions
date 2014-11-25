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
  int id;
  double x,y;
  Point() {}
  Point(int id, double x, double y) : id(id), x(x), y(y) {}
  double sqr_dist(const Point& p) const {
    return sqr(x-p.x) + sqr(y-p.y);
  }
  double dist(const Point& p) const {
    return sqrt(sqr_dist(p));
  }
  bool operator<(const Point& p) const {
    return mp(id,mp(x, y)) < mp(id,mp(p.x, p.y));
  }
};

struct PointComparer {
  Point center;
  PointComparer(const Point& center) : center(center) {}
  bool operator()(const Point& lhs, const Point& rhs) const {
    return mp(center.dist(lhs), lhs) < mp(center.dist(rhs), rhs);
  }
};

struct Segment {
  Point a,b;
  Segment() {}
  Segment(Point& a, Point& b) : a(a), b(b) { }
  double len() const {
    return a.dist(b);
  }
  bool operator<(const Segment& s) const {
    return mp(this->len(),mp(a,b)) < mp(s.len(),mp(s.a,s.b));
  }
};

int main() {
#   ifdef _DEBUG
        freopen("h.in", "r", stdin);
#   else
        freopen("h.in", "r", stdin);
        freopen("h.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; 
    while( cin >> n && n != 0 ) {
      vector<Point> p(n);
      for(int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y; 
        p[i].id = i;
      }

      vector<Segment> dist;
      for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++) {
            dist.push_back(Segment(p[i], p[j]));
          }
          /*
      sort(all(dist));
      for(int i = 0; i < sz(dist); i++)
        cout << "(" << dist[i].a.id << "; " << dist[i].b.id << ") : " << dist[i].len() << "\n";     
      cout << "\n";
      for(int i = 0; i < n-2; i++)
        for(int j = i+1; j < n-1; j++)
          for(int k = j+1; k < n; k++) {
            double ij = p[i].dist(p[j]), jk = p[j].dist(p[k]), ki = p[k].dist(p[i]);
            double pp = (ij+jk+ki)/2;
            double s = sqrt(pp*(pp-ij)*(pp-jk)*(pp-ki));
            cout << "("  << i 
                 << "; " << j
                 << "; " << k 
                 << ") = " << s << "\n";
          }

      cout << "\n===============\n";*/
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
