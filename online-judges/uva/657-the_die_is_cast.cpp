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

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void color_cubes(vector<string>& board, vvi& mark, int clr, int r, int c) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) || board[r][c] == '.' || mark[r][c] )
    return;
  mark[r][c] = clr;
  forn(i,4)
    color_cubes(board,mark,clr,r+dr[i],c+dc[i]);
}
void remove_point(vector<string>& board, int r, int c) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) || board[r][c] != 'X' )
    return;
  board[r][c] = '.';
  forn(i,4)
    remove_point(board,r+dr[i],c+dc[i]);
}
void count_points(vector<string>& board, vvi& mark, int& result, int clr, int r, int c) {
  if( r < 0 || c < 0 || r >= sz(board) || c >= sz(board[0]) || mark[r][c] != clr )
    return;
  if( board[r][c] == 'X' )
    ++result, remove_point(board, r, c);
  mark[r][c] = 0;
  board[r][c] = '.';
  forn(i,4)
    count_points(board, mark, result, clr, r+dr[i], c+dc[i]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int ci = 1;
  
  int n,m;
  while( cin>>m>>n, n || m ) {
    vector<string> board(n);
    forn(i,n) cin>>board[i];
    vvi mark(n, vi(m));
    int color = 1;
    forn(i,n) forn(j,m)
      if( !mark[i][j] )
        color_cubes(board, mark, color++, i, j);
    vi result;
    forn(i,n) forn(j,m)
      if( mark[i][j] ) {
        result.push_back(0);
        count_points(board, mark, result.back(), mark[i][j], i, j);
      }
    sort(all(result));
    cout<<"Throw "<<ci++<<"\n";
    cout<<result[0];
    for(int i = 1; i < sz(result); i++)
      cout<<" "<<result[i];
    cout<<"\n\n"<<flush;
  }
  
  TIMESTAMP("end");
  return 0;
}

