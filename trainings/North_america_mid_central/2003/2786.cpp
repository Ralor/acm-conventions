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

void click(vector<string>& board, vector<string>& target, int r, int c) {
  int cnt = 0;
  forn(i,8) {
    int nr = r + dr[i], nc = c + dc[i];
    if( nr < 0 || nc < 0 || nr >= sz(board) || nc >= sz(board[0]) )
      continue;
    if( board[nr][nc] == 'M' )
      ++cnt;
  }
  target[r][c] = char('0' + cnt);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n,m;
  while( cin>>n>>m, n || m ) {
    vector<string> board(n);
    forn(i,n)
      cin>>board[i];
    int result = inf;
    forn(sr,n) forn(sc,m) if( board[sr][sc] == '.' ) {
      vector<string> t = vector<string>(n, string(m, '.'));
      click(board, t, sr, sc);
      bool smth;
      do {
        smth = false;
        forn(r,n) forn(c,m) if( isdigit(t[r][c]) ) {
          int empty = 0, flags = 0, bombs = t[r][c] - '0';
          forn(i,8) {
            int nr = r + dr[i], nc = c + dc[i];
            if( nr < 0 || nc < 0 || nr >= n || nc >= m )
              continue;
            if( t[nr][nc] == '.' )
              ++empty;
            else if( t[nr][nc] == 'F' )
              ++flags;
          }
          if( !empty ) continue;
          if( bombs == flags ) {
            forn(i,8) {
              int nr = r + dr[i], nc = c + dc[i];
              if( nr < 0 || nc < 0 || nr >= n || nc >= m )
                continue;
              if( t[nr][nc] == '.' )
                smth = true, click(board, t, nr, nc);
            }
          } else if( empty + flags == bombs ) {
            forn(i,8) {
              int nr = r + dr[i], nc = c + dc[i];
              if( nr < 0 || nc < 0 || nr >= n || nc >= m )
                continue;
              if( t[nr][nc] == '.' )
                smth = true, t[nr][nc] = 'F';
            }
          }
        }
      } while( smth );
      int cur_result = 0;
      forn(r,n) forn(c,m)
        if( t[r][c] == '.' && board[r][c] != 'M' )
          ++cur_result;
      result = min(result, cur_result);
    }
    cout<<result<<"\n";
  }

  TIMESTAMP("end");
  return 0;
}
