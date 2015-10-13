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

const int dr[] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int dc[] = {1, 1, 1, 0, -1, -1, -1, 0};

int dfs_cnt(vector<string>& board, int r, int c, int n, int m) {
  if( r < 0 || c < 0 || r >= n || c >= m || board[r][c] != 'W' )
    return 0;
  board[r][c] = '.';
  int result = 1;
  forn(i,8)
    result += dfs_cnt(board, r + dr[i], c + dc[i], n, m);
  return result;
}

void dfs_set(vector<string>& board, vvi& result, int value, int r, int c, int n, int m) {
  if( r < 0 || c < 0 || r >= n || c >= m || board[r][c] != '.' )
    return;
  board[r][c] = 'L';
  result[r][c] = value;
  forn(i,8)
    dfs_set(board, result, value, r + dr[i], c + dc[i], n, m);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int cn; cin>>cn;
  while( cin.get() != '\n' ) { }
  string t;
  getline(cin,t);
  forn(ci,cn) {
    vector<string> board;
    do {
      board.eb(""), getline(cin,board.back());
    } while( board.back()[0] == 'L' || board.back()[0] == 'W' );
    t = board.back(); board.pop_back();
    int n = sz(board), m = sz(board[0]);
    vvi result(n, vi(m, -1));
    forn(i,n) forn(j,m)
      if( board[i][j] == 'W' ) {
        int cnt = dfs_cnt(board, i, j, n, m);
        dfs_set(board, result, cnt, i, j, n, m);
      }
    if( ci )
      cout<<"\n";
    do {
      istringstream in(t);
      int r,c; in>>r>>c;
      cout<<result[r-1][c-1]<<"\n";
    } while( getline(cin,t) && !t.empty() );
  }
  
  TIMESTAMP("end");
  return 0;
}

