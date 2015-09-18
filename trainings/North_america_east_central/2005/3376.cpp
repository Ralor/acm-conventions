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

void rec(int& best, int cur, int cnt, int u, vvi& a, vi& visits, vi& used) {
  if( ~best && cur > best )
    return;
  if( cnt == sz(a) && u == 0 ) {
    if( ~best )
      best = min(best, cur);
    else
      best = cur;
    return;
  }
  ++visits[u];
  used[u] = 1;
  forn(v,sz(a)) if( ~a[u][v] ) {
    int t = a[u][v];
    a[u][v] = a[v][u] = -1;
    if( !used[v] )
      rec(best,cur+t,cnt+1,v,a,visits,used);
    else
      rec(best,cur+t,cnt,v,a,visits,used);
    a[u][v] = a[v][u] = t;
  }
  --visits[u];
  if( visits[u] == 0 )
    used[u] = 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int ci = 1;
  
  int n,m;
  while( cin>>n>>m, n || m ) {
    vvi a(n, vi(n, -1));
    forn(i,m) {
      int u,v,c;
      cin>>u>>v>>c;
      --u; --v;
      a[u][v] = a[v][u] = c;
    }
    int result = -1;
    vi used(n), visits(n);
    rec(result,0,1,0,a,visits,used);
    if( ~result ) 
      cout<<"The minimal cost for test case "<<ci++<<" is "<<result<<".\n";
    else
      cout<<"There is no reliable net possible for test case "<<ci++<<".\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
