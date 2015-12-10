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
#define FOR(i, n) for(int (i) = 0; (i) < (n); ++(i))
#define FORN(i, n) for(int (i) = 1; (i) <= (n); ++(i))
#define REP(i,from,to) for(int (i) = (from); (i) <= (to); ++(i))
#define RREP(i,from,to) for(int (i) = (from); (i) >= (to); --(i))
#define FOREACH(iter, cont) for(__typeof(cont)::iterator it = (cont).begin(); (it) != (cont).end(); ++(it))


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
  double a,b,r;
  double x,y,z;

  Point() {}
  Point(double a, double b, double r, bool polar = false) : a(a), b(b), r(r){
    if( polar )
      gen_dec();
    else
      x = a, y = b, z = r, gen_polar();
  }

  double get_angle(Point& p) {
    return atan2((*this / p).r, (*this % p));
  }

  double operator%(const Point& p) const {
    return x*p.x + y*p.y + z*p.z;
  }
  Point operator/(const Point& p) const {
    return Point(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
  }

private:
  void gen_polar() {
    r = sqrt(sqr(x) + sqr(y) + sqr(z));
    b = acos(z/r);
    a = acos(x/r/sin(b));
  }
  void gen_dec() {
    x = r*cos(a)*sin(b);
    y = r*sin(a)*sin(b);
    z = r*cos(b);
  }
};

int main() {
  //freopen(TASK ".in", "r", stdin);
  //freopen(TASK ".out", "w", stdout);
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout << setprecision(2) << fixed;
  double r,H1,W1,H2,W2;
  while( cin >> r >> H1 >> W1 >> H2 >> W2 ) {
    //W1 -= 180; W2 -= 180;
    H1 += 90; H2 += 90;
    H1 = H1/180*M_PI;
    H2 = H2/180*M_PI;
    W1 = W1/360*M_PI*2;
    W2 = W2/360*M_PI*2;
    Point a(W1,H1,r,true), b(W2,H2,r,true);
    double frac = a.get_angle(b);
    cout << frac * r << "\n";
  }


  return 0;
}
