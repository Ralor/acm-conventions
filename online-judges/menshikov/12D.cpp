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
  llong x, y;
  Point() { }
  Point(llong x, llong y) : x(x), y(y) { }
};
struct Rect {
  Point a,b;
  Rect() { }
  Rect(Point& a, Point& b) : a(a), b(b) { init(); }
  void init() {
    if( a.x > b.x ) swap(a.x,b.x);
    if( a.y > b.y ) swap(a.y,b.y);
  }
  int diag() {
    llong dx = b.x - a.x, dy = b.y - a.y;
    while( dx )
      dy %= dx, swap(dx,dy);
    return dy + 1;
  }
};


double get_s(vector<Point>& a) {
  double s = 0;
  for(int i = 0, j = 1; i < sz(a); i++, j++, j %= sz(a))
    s += (a[i].y + a[j].y) * 1.0 * (a[j].x - a[i].x);
  return s/2;
}
double get_cnt(vector<Point>& a) {
  llong cnt = 0;
  for(int i = 0, j = 1; i < sz(a); i++, j++, j %= sz(a))
    cnt += Rect(a[i], a[j]).diag() - 1;
  return cnt;
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

  int n;
  while( cin >> n ) {
    vector<Point> a(n);
    forn(i,n) cin >> a[i].x >> a[i].y, a[i].y += 1000 * 1000;
    double s = fabs(get_s(a));
    // s = I + B/2 - 1;
    // I = s - B/2 + 1
    cout << llong(s - get_cnt(a)/2.0 + 1 + eps) << "\n";
  }


  return 0;
}
