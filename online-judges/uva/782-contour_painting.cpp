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

bool dfs(vector<vector<char>>& board, int r, int c, char wall) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) )
    return false;
  if( board[r][c] == wall )
    return true;
  if( board[r][c] != ' ' )
    return false;
  board[r][c] = '-';
  bool colored = false; // be careful with dfs() || dfs() || dfs() 
  colored |= dfs(board, r+1, c, wall);
  colored |= dfs(board, r-1, c, wall);
  colored |= dfs(board, r, c+1, wall);
  colored |= dfs(board, r, c-1, wall);
  if( colored )
    board[r][c] = '#';
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int cn; cin>>cn;
  while( cin.get() != '\n' ) { }
  forn(ci, cn) {
    vector<vector<char>> board;
    int n = 0, m = 0;
    char wall = -1;
    while( 1 ) {
      string t; getline(cin, t);
      board.eb();
      board[n++].assign(all(t));
      if( wall == -1 )
        for(char c : t)
          if( c != '_' && c != ' ' && c != '*' )
            wall = c;
      m = max(m, sz(t) + 1);
      if( !t.empty() && t[0] == '_' )
        break;
    }
    forn(r, n)
      board[r].resize(m, ' ');
    forn(r, n) forn(c, m) if( board[r][c] == '*' ) {
      board[r][c] = ' ';
      dfs(board, r, c, wall);      
      goto output;
    }
    output:;
    forn(r, n) forn(c, m)
      if( board[r][c] == '-' )
        board[r][c] = ' ';
    forn(r, n) {
      while( !board[r].empty() && board[r].back() == ' ' )
        board[r].pop_back();
      cout<<string(all(board[r]))<<"\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
