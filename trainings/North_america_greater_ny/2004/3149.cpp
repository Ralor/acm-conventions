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

int calc(vector<string>& board, int r, int c, char symbol) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) || board[r][c] != symbol )
    return 0;
  board[r][c] = '*';
  int result = 1;
  forn(i,8)
    result += calc(board, r + dr[i], c + dc[i], symbol);
  return result;
}
void replace_symbol(vector<string>& board, int r, int c, char from, char to) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) || board[r][c] != from )
    return;
  board[r][c] = to;
  forn(i,8)
    replace_symbol(board, r + dr[i], c + dc[i], from, to);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
    
  int n, m, mn_size;
  while( cin>>n>>m>>mn_size, n || m || mn_size ) {
    vector<string> board(n);
    forn(r,n) cin>>board[r];
    int good_cnt = 0;
    vector<string> boardd = board;
    forn(r,n) forn(c,m) if( boardd[r][c] != '.' ) {
      char symbol = boardd[r][c];
      int cnt = calc(boardd, r, c, boardd[r][c]);
      if( cnt < mn_size )
        replace_symbol(board, r, c, symbol, '.' );
      else
        ++good_cnt;
      replace_symbol(boardd, r, c, '*', '.' );
    }
    cout<<good_cnt<<"\n";
    forn(cr,n) forn(cc,m) if( board[cr][cc] != '.' ) {
      int prev_dir = 3;
      char start_symbol = board[cr][cc];
      int r = cr, c = cc;
      string contour = "";
      do {
        int dir = (prev_dir + 4 + 1) % 8;
        while( 1 ) {
          int nr = r + dr[dir], nc = c + dc[dir];
          if( nr < 0 || nc < 0 || nr >= n || nc >= m || board[nr][nc] != start_symbol )
            dir = (dir + 1)%8;
          else
            break;
        }
        contour += ds[dir];
        r += dr[dir]; c += dc[dir];
        prev_dir = dir;
      } while( mp(r,c) != mp(cr, cc) );
      cout<<r+1<<" "<<c+1<<" "<<sz(contour)<<"\n";
      for(int i = 0; i < sz(contour); i += 40)
        cout<<contour.substr(i,40)<<"\n";
      replace_symbol(board, cr, cc, board[cr][cc], '.');
    }
  }
  
  TIMESTAMP("end");
  return 0;
}

