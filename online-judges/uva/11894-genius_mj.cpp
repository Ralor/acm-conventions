#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <valarray>
#include <vector>
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define fst        first
#define snd        second
#define pb         push_back
#define mp         make_pair
#define eb         emplace_back
#define ef         emplace_front
#define mt         make_tuple
#define eps        1e-8
#define inf        int(1e9)
#define linf       llong(4e18)
using namespace std;

struct debug_t {
  template<typename T>
  debug_t& operator << (const T& o) {
#   ifdef LOCAL_DEBUG
    cout<<o<<flush;
#   endif
    return *this;
  }
} debug;

#define TIMESTAMP(msg) debug << "[" msg "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n' 
#define DBG(x) debug << "[" #x "] = " << x << '\n'
#define DOUT(x) debug << x << '\n'
#define _ << " " <<

typedef unsigned char       uchar;
typedef basic_string<uchar> ustring;
typedef long long           llong;
typedef unsigned long long  ullong;
typedef long double         ldouble;
typedef vector<int>         vi;
typedef vector<vi>          vvi;
typedef vector<double>      vd;
typedef vector<vd>          vvd;
typedef pair<int,int>       pii;

struct Point {
  int x,y;
  Point operator + (const Point& p) const { return {x + p.x, y + p.y}; }
  Point rotate() const { return {-y, x}; }
};

pii leftdown(vector<Point>& points) {
  int l = 1000, d = 1000;
  for(Point p : points)
    l = min(l, p.x), d = min(d, p.y);
  return mp(l,d);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
    
  int cn; cin>>cn;
  forn(ci,cn) {
    int n; cin>>n;
    vector<Point> pa(n), pb(n);
    forn(i,n) cin>>pa[i].x>>pa[i].y;
    forn(i,n) cin>>pb[i].x>>pb[i].y;
    sort(all(pb), [] (const Point& a, const Point& b) {
        return mp(a.x,a.y) < mp(b.x,b.y);
      });
    bool matched = false;
    forn(rot, 4) {
      sort(all(pa), [] (const Point& a, const Point& b) {
        return mp(a.x,a.y) < mp(b.x,b.y);
      });
      int la, da;
      tie(la, da) = leftdown(pa);
      int lb, db;
      tie(lb, db) = leftdown(pb);
      Point transition = {lb - la, db - da};
      forn(i,n)
        pa[i] = pa[i] + transition;
      bool ok = true;
      forn(i,n)
        ok &= mp(pa[i].x, pa[i].y) == mp(pb[i].x, pb[i].y);
      forn(i,n)
        pa[i] = pa[i].rotate();
      matched |= ok;
    }
    if( matched ) 
      cout<<"MATCHED\n";
    else
      cout<<"NOT MATCHED\n";
  }
  
  TIMESTAMP("end");
  return 0;
}

