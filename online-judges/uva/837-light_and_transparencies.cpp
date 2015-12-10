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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout<<setprecision(3)<<fixed;
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int n; cin>>n;
    vector<tuple<double,int,double>> p;
    forn(i,n) {
      double x1,y1,x2,y2,r; cin>>x1>>y1>>x2>>y2>>r;
      if( eq(x1,x2) )
        continue;
      if( x1 > x2 )
        swap(x1,x2);
      p.eb(x1,0,log(r));
      p.eb(x2,1,log(r));
    }
    n = sz(p);
    sort(all(p), [] (const tuple<double,int,double>& lhs, const tuple<double,int,double>& rhs) {
      return eq(get<0>(lhs), get<0>(rhs)) ? get<1>(lhs) < get<1>(rhs) : get<0>(lhs) < get<0>(rhs);
    });
    double prev = -inf;
    double cur = 0;
    vector<tuple<double,double,double>> result;
    for(auto t : p) {
      double x,val;
      int type;
      tie(x,type,val) = t;
      if( !eq(x, prev) )
        result.eb(prev, x, exp(cur));
      prev = x;
      if( type == 1 )
        cur -= val;
      else
        cur += val;
    }
    result.eb(get<0>(p.back()), inf, 1);
    if( ci )
      cout<<"\n";
    cout<<sz(result)<<"\n";
    for(auto t : result) {
      double l,r,val;
      tie(l,r,val) = t;
      if( eq(l, -inf) )
        cout<<"-inf";
      else
        cout<<l;
      if( eq(r, inf) )
        cout<<" +inf";
      else
        cout<<" "<<r;
      cout<<" "<<val<<"\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
