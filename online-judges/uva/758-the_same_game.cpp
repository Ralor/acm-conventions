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

int cluster_size(vector<string>& board, int r, int c, char symbol) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) || board[r][c] != symbol )
    return 0;
  board[r][c] = '.';
  return 1 + 
    cluster_size(board, r+1, c, symbol) +
    cluster_size(board, r-1, c, symbol) +
    cluster_size(board, r, c+1, symbol) +
    cluster_size(board, r, c-1, symbol);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int cn; cin>>cn;
  forn(ci, cn) {
    int n = 10, m = 15;
    vector<string> board(n);
    forn(r, n) cin>>board[n-r-1], debug<<board[n-r-1]<<"\n";
    int total_score = 0, last_cluster_count;
    if( ci )
      cout<<"\n";
    cout<<"Game "<<ci+1<<":\n\n";
    int move_number = 1;
    while( 1 ) {
      vector<string> temp = board;
      int best_size = 0, best_r = 0, best_c = 0;
      last_cluster_count = 0;
      forn(c, m) forn(r, n) if( temp[r][c] != '.' ) {
        int size = cluster_size(temp, r, c, temp[r][c]);
        if( best_size < size )
          tie(best_size, best_r, best_c) = mt(size, r, c);
        ++last_cluster_count;
      }
      DOUT(best_size _ best_r _ best_c);
      if( best_size <= 1 )
        break;
      char symbol = board[best_r][best_c];
      int size = cluster_size(board, best_r, best_c, symbol);
      int score = sqr(size - 2);
      cout<<"Move "<<move_number++<<" at ("<<best_r+1<<","<<best_c+1<<"): ";
      cout<<"removed "<<size<<" balls of color "<<symbol<<", got "<<score<<" points.\n";
      total_score += score;
      
      DOUT("after deletion:"); forn(r,n) debug<<board[r]<<"\n";
      
      int new_n = 0;
      forn(c, m) { // shift up
        int ptr = 0;
        forn(r, n)
          if( board[r][c] != '.' )
            board[ptr][c] = board[r][c], ++ptr;
        new_n = max(new_n, ptr);
        while( ptr < n )
          board[ptr][c] = '.', ++ptr;
      }
      n = new_n;
      board.resize(n);
      
      int ptr = 0;
      forn(c, m) { // shift left if there are empty cols
        bool empty_column = true;
        forn(r, n)
          empty_column &= board[r][c] == '.';
        if( !empty_column ) {
          forn(r,n)
            board[r][ptr] = board[r][c];
          ++ptr;
        }
      }
      m = ptr;
      forn(r,n) board[r].resize(m);
      
      DOUT("after shift:"); forn(r,n) debug<<board[r]<<"\n";
      
    }
    if( last_cluster_count == 0 )
      total_score += 1000;
    cout<<"Final score: "<<total_score<<", with "<<last_cluster_count<<" balls remaining.\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
