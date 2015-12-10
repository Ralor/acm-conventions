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

#define eps 1e-8
#define inf (1000 * 1000 * 1000)
#define linf (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x) ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x) static_cast<int>((x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define mp make_pair
#define mt make_tuple
#define pb push_back

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
  double x, y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double sqr_len() const {
    return sqr(x) + sqr(y);
  }
  double len() const {
    return sqrt(sqr_len());
  }
  Point operator + (const Point& p) const {
    return Point(x + p.x, y + p.y);
  }
  Point operator - (const Point& p) const {
    return Point(x - p.x, y - p.y);
  }
  Point operator * (const double& c) const {
    return Point(x * c, y * c);
  }
};

Point operator * (const double& c, const Point& p) {
  return p * c;
}

double solve(double angle, double c, double delta_t = 1e-4) {
  angle = angle / 180 * M_PI;
  double g = 9.8;
  double v0 = 800;
  double m = 9.6;

  Point p(0, 0), v(v0 * cos(angle), v0 * sin(angle));
  do {
    p = p + v * delta_t;
    double Fr_mod = c * v.sqr_len();
    double speed = v.len();
    Point Fr(v.x / speed * Fr_mod, v.y / speed * Fr_mod);
    v = v - Point(Fr.x / m, Fr.y/m + g) * delta_t;
  } while( p.y > 0 );
  return p.x;
}

int main() {
  //freopen(TASK".in", "r", stdin);
  //freopen(TASK".out", "w", stdout);
#ifdef RALOR_PROJECT
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
#endif
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);

  /*double l = 0, r = 1;
  forn(i,50) {
    double mid = l + (r-l)/2;
    if( solve(45, mid) < 15650 )
      r = mid;
    else
      l = mid;
  }
  debug << r << "\n";*/
  double c = 0.000813697;
  double angle;
  while( cin >> angle ) {
    cout << int(solve(angle, c) + 0.5) << "\n";
  }


  return 0;
}
