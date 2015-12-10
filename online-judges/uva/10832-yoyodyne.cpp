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
  double x,y,z;
  double len() const { return sqrt(sqr(x) + sqr(y) + sqr(z)); }
  Point operator - (const Point& p) const { return {x - p.x, y - p.y, z - p.z}; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  cout<<setprecision(2)<<fixed;
  
  int ci = 1;
  
  double f, df, dv;
  int n;
  while( cin>>f>>df>>dv>>n, !eq(f,0) || !eq(df,0) || !eq(dv,0) || n ) {
    vector<Point> p(n);
    forn(i,n) cin>>p[i].x>>p[i].y>>p[i].z;
    Point cur({0,0,1});
    vi used(n);
    double tm = 0;
    double past = 0, future = 0;
    bool success = true;
    forn(iter, n) {
      int u = -1;
      forn(i,n) if( !used[i] )
        if( u == -1 || (~u && (cur - p[u]).len() > (cur - p[i]).len()) )
          u = i;
      used[u] = 1;
      double dist = (cur - p[u]).len();
      double time_needed = dist / dv;
      double time_available = f / df;
      if( !success ) {
        future += dist;
      } else if( time_available + eps < time_needed ) {
        success = false;
        past += time_available * dv;
        future = (time_needed - time_available) * dv;
        f = 0;
      } else {
        tm += time_needed;
        past += dist;
        f -= time_needed * df;
      }
      cur = p[u];
    }
    cout<<"Mission "<<ci++<<": ";
    cout<<( success ? "SUCCESS!! " : "FAILURE!! " );
    if( success )
      cout<<"Time: "<<tm<<"  Traveled: "<<past<<"  Fuel Left: "<<f<<"\n";
    else
      cout<<"Traveled: "<<past<<"  From Home: "<<future<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}

