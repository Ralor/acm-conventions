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
#include <assert.h>
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
  
  vi values;
  forn(a,16) forn(b, 16) forn(c, 16) forn(d, 16) forn(e, 16) forn(f, 16)
    if( a + b + c + d + e + f == 15 ) {
      int s = 0;
      s += f;
      s += e * 16;
      s += d * 16 * 16;
      s += c * 16 * 16 * 16;
      s += b * 16 * 16 * 16 * 16;
      s += a * 16 * 16 * 16 * 16 * 16;
      values.eb(s);
    }
  
  int ci = 1;
  string com;
  while( cin>>com, com != "e" ) 
    if( com == "m" ) {
      int a,b,c,d,e,f;
      cin>>a>>b>>c>>d>>e>>f;
      int s = 0;
      s += f;
      s += e * 16;
      s += d * 16 * 16;
      s += c * 16 * 16 * 16;
      s += b * 16 * 16 * 16 * 16;
      s += a * 16 * 16 * 16 * 16 * 16;
      cout<<"Case "<<ci++<<": "<<lower_bound(all(values), s) - begin(values)<<"\n";
    } else {
      int id; cin>>id;
      int s = values[id];
      vi result;
      while( s )
        result.eb(s%16), s /= 16;
      while( sz(result) < 6 )
        result.eb(0);
      cout<<"Case "<<ci++<<":";
      for_each(rall(result), [](int v) {
        cout<<" "<<v;
      });
      cout<<"\n";
    }
  
  TIMESTAMP("end");
  return 0;
}
