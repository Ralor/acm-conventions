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

  int cn; cin>>cn;
  forn(ci,cn) {
    int n,m,d1,d2; cin>>n>>m>>d1>>d2;
    const int dr[] = {d1,d2,-d1,d2,d1,-d2,-d1,-d2};
    const int dc[] = {d2,d1,d2,-d1,-d2,d1,-d2,-d1};
    const int dsz = sizeof(dr) / sizeof(dr[0]);
    vvi used(n, vi(m));
    int w,r,c; cin>>w;
    forn(i,w)
      cin>>r>>c, used[r][c] = 2;
    queue<pii> sq; 
    sq.emplace(0,0);
    used[0][0] = 1;
    int even = 0, odd = 0;
    while( !sq.empty() ) {
      tie(r,c) = sq.front(); sq.pop();
      set<pii> nbr;
      forn(i,dsz) {
        int nr = r + dr[i], nc = c + dc[i];
        if( nr < 0 || nc < 0 || nr >= n || nc >= m || used[nr][nc] == 2 )
          continue;
        nbr.emplace(r + dr[i], c + dc[i]);
        if( used[nr][nc] )
          continue;
        sq.emplace(nr,nc); used[nr][nc] = 1;
      }
      odd += sz(nbr) % 2;
      even += sz(nbr) % 2 == 0;
    }
    cout<<"Case "<<ci+1<<": "<<even<<" "<<odd<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
