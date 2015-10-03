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

const int dr[] = {0, -1, 0, 1};
const int dc[] = {1, 0, -1, 0};

void dfs(vvi& board, vvi& used, vvi& ocean, int r, int c) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) )
    return;
  if( used[r][c] || ocean[r][c] )
    return;
  used[r][c] = 1;
  forn(i,4) 
    dfs(board,used,ocean,r+dr[i],c+dc[i]);
}

void find_ocean(vvi& board, vvi& mark, int height, int r, int c) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) )
    return;
  if( mark[r][c] || board[r][c] > height )
    return;
  mark[r][c] = 1;
  forn(i,4)
    find_ocean(board, mark, height, r + dr[i], c + dc[i]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int ci = 1;
  
  int n,m;
  while( cin>>n>>m, n || m ) {
    vvi board(n+2, vi(m+2));
    forn(i,n) forn(j,m)
      cin>>board[i+1][j+1];
    n += 2; m += 2;
    vvi ocean(n, vi(m));
    int mx = board[0][0], mxi = 0, mxj = 0;
    forn(i,n) forn(j,m)
      if( board[i][j] > mx )
        tie(mx, mxi, mxj) = mt(board[i][j], i, j);
    DOUT("max" _ mxi _ mxj);
    forn(height, 1000 + 1) {
      vvi used(n, vi(m)), ocean(n, vi(m));
      find_ocean(board, ocean, height, 0, 0);
      dfs(board, used, ocean, mxi, mxj);
      int split = 0;
      forn(i,n) forn(j,m)
        if( !used[i][j] && board[i][j] > height )
          DOUT(i _ j), split = 1;
      if( split ) {
        cout<<"Case "<<ci++<<": Island splits when ocean rises "<<height<<" feet.\n";
        goto next_case;
      }
    }
    cout<<"Case "<<ci++<<": Island never splits.\n";
    next_case:;
  }
  
  TIMESTAMP("end");
  return 0;
}
