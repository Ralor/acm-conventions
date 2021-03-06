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
  
  while( !isdigit(cin.peek()) ) cin.get();
  int n; cin>>n;
  vi x(n), y(n), v(n);
  forn(i,n)
    cin>>x[i]>>y[i]>>v[i];
  while( !isdigit(cin.peek()) ) cin.get();
  int balls; cin>>balls;
  forn(ball, balls) {
    int a,b,c,d,e,f,g; cin>>a>>b>>c>>d>>e>>f>>g;
    int t = 1;
    while( a * t * t + b * t + c > 0 ) 
      ++t;
    int tx = d * t + e, ty = f * t + g;
    if( tx < 0 || ty < 0 ) {
      cout<<"Ball "<<ball+1<<" was foul at ("<<tx<<","<<ty<<")\n";
      continue;
    }
    bool caught = false;
    forn(i,n) if( sqr(tx - x[i]) + sqr(ty - y[i]) <= sqr(v[i] * t) ) {
      caught = true; break;
    }
    if( caught )
      cout<<"Ball "<<ball+1<<" was caught at ("<<tx<<","<<ty<<")\n";
    else
      cout<<"Ball "<<ball+1<<" was safe at ("<<tx<<","<<ty<<")\n";
  }
  
  TIMESTAMP("end");
  return 0;
}

