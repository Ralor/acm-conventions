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

int tenlen(int x) {
  int result = 1;
  while( x /= 10 ) 
    ++result;
  return result;
}

const int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1};
const int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1};

void dfs(vector<vector<char>>& board, vvi& result, int r, int c, char board_color, int new_color) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) || board[r][c] != board_color )
    return;
  board[r][c] = 0;
  result[r][c] = new_color;
  forn(i,8)
    dfs(board, result, r + dr[i], c + dc[i], board_color, new_color);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while( 1 ) {
    vector<vector<char>> board;
    int color = 1;
    string t;
    while( getline(cin,t) && t != "%" ) {
      board.eb();
      for(char c : t) if( c != ' ' ) 
        board.back().eb(c);
    }
    if( board.empty() )
      break;
    int n = sz(board), m = sz(board[0]);    
    color = 1;
    vvi result(n, vi(m));
    forn(r, n) forn(c, m)
      if( board[r][c] )
        dfs(board, result, r, c, board[r][c], color++);
    vi width(m);
    forn(c, m) forn(r, n)
      width[c] = max(width[c], tenlen(result[r][c]));
    forn(r, n) {
      cout<<setw(width[0])<<result[r][0];
      for(int c = 1; c < m; c++)
        cout<<" "<<setw(width[c])<<result[r][c];
      cout<<"\n";
    }
    cout<<"%\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
