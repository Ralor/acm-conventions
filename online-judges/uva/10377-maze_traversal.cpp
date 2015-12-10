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
  map<char,int> dir;
  dir['N'] = 0;
  dir['E'] = 1;
  dir['S'] = 2;
  dir['W'] = 3;
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int n,m; cin>>n>>m;
    while( cin.get() != '\n' ) { }
    vector<string> board(n);
    forn(i,n) getline(cin,board[i]);
    
    int r,c,d = 0; cin>>r>>c;
    --r; --c;
    
    char com;
    while( cin>>com ) {
      if( isdigit(com) ) {
        cin.putback(com);
        break;
      }
      if( com == ' ' )
        continue;
      DBG(com);
      switch( com ) {
        case 'Q':
          DOUT("quit");
          goto stop;
          break;
        case 'L':
          DOUT("turn left");
          d = (d + 3) % 4;
          break;
        case 'R':
          DOUT("turn right");
          d = (d + 1) % 4;
          break;
        case 'F': {
          int nr = r + dr[d], nc = c + dc[d];
          if( board[nr][nc] != '*' )
            r = nr, c = nc, DOUT("go to" _ r _ c);
        }
      }
      
    }
    stop:
    if( ci )
      cout<<"\n";
    cout<<r+1<<" "<<c+1<<" "<<(d==0 ? 'N' : d == 1 ? 'E' : d == 2 ? 'S' : 'W')<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
