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

const int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
const char ds[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
int dd[128];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
    
  forn(i,8)
    dd[(int)ds[i]] = i;
  
  int ci = 0;
  
  int n,m,cnt;
  while( cin>>n>>m>>cnt, n || m || cnt ) {
    if( ci++ )
      cout<<"\n";
    vector<string> board(n, string(m, '.'));
    vvi paint(n, vi(m));
    while( cnt-- ) {
      vector<string> t = board;
      vvi tp = paint;
      char symbol; cin>>symbol;
      int r,c; cin>>r>>c; --r; --c;
      int sr,sc; tie(sr,sc) = mp(r,c);
      int comms; cin>>comms;
      string commands; cin>>commands;
      for(char com : commands) {
        int dir = dd[(int)com];
        r += dr[dir]; c += dc[dir];
        if( r < 0 || c < 0 || r >= n || c >= m ) {
          cout<<"REGION "<<symbol<<" GOES OUTSIDE THE ARRAY\n";
          goto next_contour;
        }
        if( board[r][c] != '.' ) {
          cout<<"REGION "<<symbol<<" BOUNDARY INTERSECTS REGION "<<board[r][c]<<"\n";
          goto next_contour;
        }
        ++tp[r][c];
        t[r][c] = symbol;
      }
      if( mp(sr,sc) != mp(r,c) ) {
        cout<<"REGION "<<symbol<<" BOUNDARY IS NOT CLOSED\n";
        goto next_contour;
      }
      board = t;
      paint = tp;
      next_contour:;
    }
    
    forn(r,n) {
      char symbol = -1;
      bool flag = false;
      forn(c,n) 
        if( board[r][c] != '.' ) {
          symbol = board[r][c];
          if( paint[r][c] & 1 )
            flag = !flag;
        } else {
          if( flag )
            board[r][c] = symbol;
        }
    }
    
    forn(r,n)
      cout<<board[r]<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}

