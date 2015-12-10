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


typedef vector<string> Board;

void remove_white(Board& board, int r, int c) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) || board[r][c] != '0' )
    return;
  board[r][c] = '*';
  remove_white(board, r+1, c);
  remove_white(board, r-1, c);
  remove_white(board, r, c+1);
  remove_white(board, r, c-1);
}
int count_holes(Board& board, int r, int c) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) )
    return 0;
  if( board[r][c] == '0' ) {
    remove_white(board, r, c);
    return 1;
  }
  if( board[r][c] != '1' )
    return 0;
  board[r][c] = '*';
  return count_holes(board, r+1, c) + 
         count_holes(board, r-1, c) + 
         count_holes(board, r, c+1) + 
         count_holes(board, r, c-1);
}

int fromhex(char digit) {
  if( isdigit(digit) )
    return digit - '0';
  return digit - 'a' + 10;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  // testcase for "A K W":
  //
  // 6 2
  // f8
  // 00
  // ef
  // ab
  // ed
  // 0f
  //
  // same as
  //
  // 11111000
  // 00000000
  // 11101111
  // 10101011
  // 11101101
  // 00001111
  
  const char codes[] = {'W', 'A', 'K', 'J', 'S', 'D'};
  int ci = 1;
  
  int n,m;
  while( cin>>n>>m, n || m ) {
    Board board(n+2);
    forn(i,n) {
      board[i+1] = "0";
      string temp; cin>>temp;
      for(char c : temp) {
        int mask = isdigit(c) ? c - '0' : c - 'a' + 10;
        string mask_s;
        forn(k,4)
          mask_s += mask & (1<<k) ? '1' : '0';
        reverse(all(mask_s));
        board[i+1] += mask_s;
      }
      board[i+1] += '0';
    }    
    n = sz(board);
    m = sz(board[1]);
    board[0] = board[n-1] = string(m, '0');
    forn(i,n)
      debug<<board[i]<<"\n";
    remove_white(board, 0, 0);
    vector<char> result;
    forn(i,n) forn(j,m) if( board[i][j] == '1' ) {
      int cnt = count_holes(board, i, j);
      result.eb(codes[cnt]);
    }
    sort(all(result));
    cout<<"Case "<<ci++<<": ";
    for(char c : result)
      cout<<c;
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
