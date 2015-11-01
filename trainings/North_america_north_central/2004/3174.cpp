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
  
  const int dr[] = {-1, 0, 1, 0};
  const int dc[] = {0, 1, 0, -1};
  
  int ci = 1;
  
  int l,h,m;
  while( cin>>l>>h>>m, l || h || m ) {
    vector<tuple<int,int,int>> request;
    request.eb(l, h, m);
    while( cin>>l>>h>>m, l || h || m )
      request.eb(l, h, m);
    vvi board(10, vi(10));
    forn(i,10) forn(j,10) 
      cin>>board[i][j];
    if( ci > 1 )
      cout<<"\n";
    cout<<"Case "<<ci++<<":\n";
    bool alarm_found = false;
    forn(req, sz(request)) {
      tie(l,h,m) = request[req];
      vvi used(10, vi(10));
      int result = 0;
      forn(i,10) forn(j,10) if( !used[i][j] && l <= board[i][j] && board[i][j] <= h ) {
        queue<pii> sq;
        sq.emplace(i,j);
        used[i][j] = 1;
        int sum = 0;
        while( !sq.empty() ) {
          pii cur = sq.front(); sq.pop();
          sum += board[cur.first][cur.second];
          forn(k,4) {
            pii nxt(cur.first + dr[k], cur.second + dc[k]);
            if( nxt.first < 0 || nxt.second < 0 ||
                nxt.first >= 10 || nxt.second >= 10 || 
                used[nxt.first][nxt.second] )
                  continue;
            if( l <= board[nxt.first][nxt.second] && board[nxt.first][nxt.second] <= h ) 
              sq.push(nxt), used[nxt.first][nxt.second] = 1;            
          }
        }
        if( sum >= m )
          ++result;
      }
      if( result ) {
        alarm_found = true;
        cout<<"    "<<result<<" alarm"<<(result > 1 ? "s" : "")<<" of type "<<req+1<<"\n";
      }
    }
    if( !alarm_found )
      cout<<"    No alarms generated\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
