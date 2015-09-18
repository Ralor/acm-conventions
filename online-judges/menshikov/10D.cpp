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

#define rep(i,from,to) for(int i = (from); i <= (to); ++i)
#define rrep(i,from,to) for(int i = (from); i >= (to); --i)
#define forn(i, n) for(int i = 0; i < (n); ++i)
#define foreach(iter, cont) for(auto iter = (cont).begin(); iter != (cont).end(); ++iter)


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

int gcd(int a, int b) {
  while( a )
    b %= a, swap(a,b);
  return b;
}

struct Point {
  int x,y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}
};

struct Rect {
  Point a,b;
  Rect() {}
  Rect(Point& a, Point& b) : a(a), b(b) {
    if( a.x > b.x )
      swap(this->a.x, this->b.x);
    if( a.y > b.y )
      swap(this->a.y, this->b.y);
  }
  int cnt_integer_points() {
    to_zero();
    return gcd(b.x, b.y);
  }
private:
  void to_zero() {
    b.x -= a.x; b.y -= a.y;
    a.x = 0; a.y = 0;
  }
};

int main() {
  //freopen(TASK ".in", "r", stdin);
  //freopen(TASK ".out", "w", stdout);
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
#endif
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  while( cin >> n ) {
    vector<Point> p(n);
    forn(i,n) cin >> p[i].x >> p[i].y;
    llong result = 0;
    forn(i,n)
      result += Rect(p[i], p[(i+1)%n]).cnt_integer_points();
    cout << result << "\n";
  }

  return 0;
}
