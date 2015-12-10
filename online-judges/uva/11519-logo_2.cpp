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

const double PI = atan(1) * 4;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int comms; cin>>comms;
    string qs;
    double qx,qy,qangle;
    double x = 0, y = 0, angle = 0;
    while( comms-- ) {
      string s;
      cin>>s; cin.get();
      char c;
      if( (c = cin.get()) != '?' ) {
        cin.putback(c);
        int val;
        cin>>val;
        if( s == "fd" )
          x += cos(angle) * val, y += sin(angle) * val;
        else if( s == "bk" )
          x -= cos(angle) * val, y -= sin(angle) * val;
        else if( s == "lt" )
          angle += val / 180. * PI;
        else if( s == "rt" )
          angle -= val / 180. * PI;
      } else {
        tie(qx,qy,qs) = mt(x,y,s);
      }
    }
    if( qs == "fd" || qs == "bk" ) {
      cout<<llong(hypot(x,y) + eps)<<"\n";
    } else if( qs == "lt" || qs == "rt" ) {
      double ax,ay; tie(ax,ay) = mp(-qx, -qy);
      double bx,by; tie(bx,by) = mp(x - qx, y - qy);
      angle = atan2(ax * by - ay * bx, ax * bx + ay * by);
      if( qs == "lt" )
        angle = -angle;
      if( angle < eps )
        angle = 2 * PI + angle;
      cout<<llong(angle / PI * 180 + eps)<<"\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}

