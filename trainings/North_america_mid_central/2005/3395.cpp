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

bool check(vi& a, int g, int cnt) {
  static vi t(500);
  int n = sz(a);
  t.resize(n);
  forn(i,n) {
    t[i] = 50 * cnt - a[i];
    debug<<t[i]<<" ";
    if( t[i] < 0 ) {
      debug<<"\n";
      return false;
    }
  }
  debug<<"\n";
  bool found_smth = true;
  while( found_smth && g > 0 ) {
    found_smth = false;
    partial_sort(begin(t), begin(t)+3, end(t), [] (int a, int b) { return a > b; });
    if( t[2] > 0 )
      --t[0], --t[1], --t[2], --g, found_smth = true;
  }
  return g == 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n; 
  while( cin>>n, n ) {
    vi a(n); int g;
    forn(i,n) cin>>a[i];
    forn(i,n) debug<<a[i]<<" "; debug<<"\n";
    cin>>g;
    int l = -1, r = 500;
    DBG(g);
    while( r - l > 1 ) {
      int mid = l + (r-l)/2;
      DBG(mid);
      if( check(a,g,mid) )
        r = mid;
      else
        l = mid;
    }
    cout<<r<<"\n";
  }

  TIMESTAMP("end");
  return 0;
}
