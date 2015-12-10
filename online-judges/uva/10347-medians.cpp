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
  
  double ma,mb,mc;
  while( cin>>ma>>mb>>mc ) {
    // 1. use cosine theorem to get mc^2 = -1/4 * a^2 + 1/2 * b^2 + 1/2 * c^2 and others
    // 2. use gaussian elemination to get formulas below
    double c = sqrt((8. / 9.) * sqr(ma) + (8. / 9.) * sqr(mb) - (4. / 9.) * sqr(mc));
    double b = sqrt((8. / 9.) * sqr(ma) + (8. / 9.) * sqr(mc) - (4. / 9.) * sqr(mb));
    double a = sqrt((8. / 9.) * sqr(mb) + (8. / 9.) * sqr(mc) - (4. / 9.) * sqr(ma));
    double p = (a+b+c)/2;
    if( c != c || b != b || a != a || p < a + eps || p < b + eps || p < c + eps ) {
      cout<<"-1.000\n";
      continue;
    }
    cout<<sqrt((p - a)*(p - b)*(p - c)*p)<<"\n";
    // btw 4/3 sqrt((p-ma)(p-mb)(p-mc)p) is also ok
  }
  
  TIMESTAMP("end");
  return 0;
}
