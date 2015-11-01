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
  
  int ci = 1;
  
  int x;
  while( cin>>x ) {
    vvi dp(20, vi(20, inf));
    int lines = 19;
    int u = 0, v;
    while( lines-- ) {
      while( x-- )
        cin>>v, --v, DOUT(u+1 _ v+1), dp[u][v] = dp[v][u] = 1;
      ++u;
      if( lines )
        cin>>x;
    }
    forn(k,20) forn(i,20) if( dp[i][k] < inf ) forn(j,20) if( dp[k][j] < inf )
      dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    cout<<"Test Set #"<<ci++<<"\n";
    int requests; cin>>requests;
    while( requests-- ) {
      cin>>u>>v; --u; --v;
      cout<<setw(2)<<u+1<<" to "<<setw(2)<<v+1<<": "<<dp[u][v]<<"\n";
    }
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
