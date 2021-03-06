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

int numlen(int x) {
  int result = 0;
  while( x )
    ++result, x /= 10;
  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int ci = 1;
  int n;
  while( cin>>n, n ) {
    ++n;
    vi a(n); 
    forn(i,n) 
      cin>>a[i];
    int x; cin >> x;
    int cur = a[0], cnt = 0;
    DOUT("Starting with \"x\" : 1");
    for(int i = 1; i < n; i++) {
      cur *= x, cnt += (i > 1) ? 2 : 1;
      DOUT("Adding \"x *\" :" _ cnt);
      if( a[i] ) {
        cur += a[i], cnt += 1 + numlen(a[i]);
        DOUT("Adding" _ (1 + numlen(a[i])) _ "by \"" _ a[i] _ "+" _ "\" :" _ cnt);
      }
    }
    cout<<"Polynomial "<<ci++<<": "<<cur<<" "<<cnt+1<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}