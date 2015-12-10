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

using namespace std;

#pragma comment(linker, "/STACK:256000000")

#define eps      1e-8
#define inf      (1000 * 1000 * 1000)
#define linf     (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)   ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)    static_cast<int>((x).size())
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define mp       make_pair
#define mt       make_tuple
#define pb       push_back

#define forn(i, n) for(int i = 0; i < (n); ++i)

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_;
template<typename I> inline void in(I l,I r)
{while(l!=r)cin>>*l,++l;}
template<typename I> inline void out(I l,I r,char D=' ')
{if(l!=r){cout<<*l;while(++l!=r)cout<<D<<*l;}cout<<'\n';}

struct debug_t {
  template <typename T>
  debug_t& operator<<(const T& value) {
# ifdef VERBOSE
    cout << value;
# endif
    return *this;
  }
} debug;

// just in vs2013, I'll get it after win 8.1)
//void dbg_out(){debug<<'\n';}
//template <typename T, typename... Args>
//void dbg_out(const T& value, const Args&... args)
//{debug<<value;dbg_out(args...);}
//#define dbg(x) #x" = ",x,"; "

typedef unsigned uint;
typedef long long llong;
typedef unsigned long long ullong;
typedef long double ldouble;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;

struct Point {
  double x,y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double operator % (const Point& p) const {
    return x*p.x + y*p.y;
  }
  double operator * (const Point& p) const {
    return x*p.y - y*p.x;
  }
  double angle_to(const Point& p) const {
    return atan2(*this * p, *this % p);
  }
};

int main() {
  //freopen(TASK".in", "r", stdin);
  //freopen(TASK".out", "w", stdout);
#ifdef RALOR_PROJECT
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
#endif
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);

  cout << setprecision(2) << fixed;

  // http://i.imgbox.com/580A84Xv.jpg
  double x1,y1,r1,x2,y2,r2;
  while( cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 ) {
    double d = sqrt(sqr(x1-x2) + sqr(y1-y2));
    if( r1 > r2 ) swap(r1, r2);

    if( r1 + r2 <= d ) {
      cout << 0 << "\n"; continue;
    }
    if( r2 >= d + r1 ) {
      cout << M_PI * sqr(r1) << "\n";
      continue;
    }

    // r1 < r2
    double x = (sqr(d) + sqr(r1) - sqr(r2)) / d / 2;
    double y = sqrt(sqr(r1) - sqr(x));

    double ang1 = Point(x,-y).angle_to(Point(x,y));
    if( ang1 < 0 ) ang1 += 2*M_PI;
    double s1 = ang1/(2*M_PI) * (M_PI * sqr(r1));
    s1 += -x*y;

    double ang2 = fabs(Point(d-x,y).angle_to(Point(d-x,-y)));
    double s2 = ang2/(2*M_PI) * (M_PI * sqr(r2));
    s2 -= (d-x)*y;
    cout << s1 + s2 << "\n";
  }

  return 0;
}
