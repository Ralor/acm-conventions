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
  Point operator - (const Point& p) const {
    return Point(x - p.x, y - p.y);
  }
  double operator * (const Point& p) const {
    return x * p.y - y * p.x;
  }
  double operator % (const Point& p) const {
    return x * p.x + y * p.y;
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

  int x1,y1,x2,y2,dx,dy;
  while( cin >> x1 >> y1 >> x2 >> y2 >> dx >> dy ) {
    vector<int> x,y;
    forn(i,111)
      x.pb(x1 * i), y.pb(y1 * i);
    vector<int> nxt_x, nxt_y;
    int xx = dx, yy = dy;
    forn(i,111)
      if( xx < x[i] ) {
        nxt_x.pb(xx); xx += x2; --i;
      } else {
        nxt_x.pb(x[i]); if( xx == x[i] ) xx += x2;
      }
    forn(i,111)
      if( yy < y[i] ) {
        nxt_y.pb(yy); yy += y2; --i;
      } else {
        nxt_y.pb(y[i]); if( yy == y[i] ) yy += y2;
      }
    set<int> areas;
    for(int i = 1; i < sz(nxt_x); i++)
      for(int j = 1; j < sz(nxt_y); j++) {
        areas.insert((nxt_x[i] - nxt_x[i-1]) * (nxt_y[j] - nxt_y[j-1]));
      }
    if( areas.empty() )
      cout << "0\n";
    else
      cout << sz(areas) << "\n";
    for(set<int>::iterator it = areas.begin(); it != areas.end(); it++)
      cout << *it << "\n";
  }

  return 0;
}
