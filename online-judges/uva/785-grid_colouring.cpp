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

void dfs(vector<string>& board, vvi& used, int r, int c, char symbol, char wall) {
  if( r<0 || c<0 || r>=sz(board) || c>=sz(board[r]) || used[r][c] || board[r][c] == wall )
    return;
  board[r][c] = symbol;
  used[r][c] = 1;
  dfs(board, used, r+1, c, symbol, wall);
  dfs(board, used, r-1, c, symbol, wall);
  dfs(board, used, r, c-1, symbol, wall);
  dfs(board, used, r, c+1, symbol, wall);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  vector<string> board;
  do board.eb(""); while( getline(cin, board.back()) );
  board.pop_back();
  int n = sz(board);
  vvi used(n);
  forn(i,n)
    used[i].resize(sz(board[i]));
  char wall = -1;
  forn(i,n) forn(j,sz(board[i])) 
    if( board[i][j] == '_' )
      wall = -1;
    else if( ! ~wall && board[i][j] != ' ' )
      wall = board[i][j]; 
    else if( ~wall && board[i][j] != ' ' && board[i][j] != wall )
      DOUT(i _ j _ wall _ board[i][j]), dfs(board, used, i, j, board[i][j], wall);
  forn(i,n)
    cout<<board[i]<<"\n";
  
  TIMESTAMP("end");
  return 0;
}

