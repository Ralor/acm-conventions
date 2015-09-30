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
struct Rect {
  int x1,y1,x2,y2;
  Rect() { }
  Rect(int x1,int y1,int x2,int y2) : x1(x1), y1(y1), x2(x2), y2(y2) { }
  bool intersect(const Rect& r) const {
    int a=x1, b=x2, c=r.x1, d=r.x2;
    bool h = min(b,d) - max(a,c) >= 0;
    a=y1, b=y2, c=r.y1, d=r.y2;    
    bool v = min(b,d) - max(a,c) >= 0;
    return h && v;
  }
  void update(const Rect& r) {
    x1 = min(x1, r.x1);
    x2 = max(x2, r.x2);
    y1 = min(y1, r.y1);
    y2 = max(y2, r.y2);
  }
  int area() const {
    return (x2 - x1) * (y2 - y1);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int a,b;
  while( cin>>a>>b ) {
    int n; cin>>n;
    
    vector<Rect> rect;
    forn(i,n) {
      int x,y,r; cin>>x>>y>>r;
      rect.eb(x - r, y - r, x + r, y + r);
    }
    vi bad(n);
    begin:
    forn(i,n) forn(j,n) 
      if( i != j && !bad[i] && !bad[j] && rect[i].intersect(rect[j]) ) {
        DOUT("Merging" _ i _ j);
        rect[i].update(rect[j]);
        bad[j] = 1;
        goto begin;
      }
    
    int area = a * b;
    forn(i,n) if( !bad[i] )
      area -= rect[i].area();
    cout<<area<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
