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


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  static int code[22][22][22][22];
  
  const int dr[] = {-1, 0, 1, 0};
  const int dc[] = {0, 1, 0, -1};
  
  int ci = 1;
  
  int n,m;
  while( cin>>n>>m, n || m ) {
    memset(code, -1, sizeof code);
    for(int r = 1; r <= n; r++) for(int c = 1; c <= m; c++) {
      char h; cin>>h;
      if( isdigit(h) )
        h = h - '0';
      else
        h = h - 'A' + 10;
      forn(i, 4) {
        int nr = r + dr[i], nc = c + dc[i];
        int flag = h % 2 == 0;
        int& to = code[r][c][nr][nc];
        int& from = code[nr][nc][r][c];
        if( from == -1 ) 
          to = flag;
        else if( from != flag )
          to = from = 2;
        else
          to = flag;
        h >>= 1;
      }
    }
    vector<vector<string>> board(2 * n + 5, vector<string>(2 * m + 5));
    for(int r = 0; r <= n; r++) for(int c = 0; c <= m; c++)
      board[2*r][2*c] = "+";
    for(int r = 1; r <= n; r++) for(int c = 1; c <= m; c++) {
      board[2*r - 1][2*c - 1] = "   ";
      forn(i, 4) {
        int nr = r + dr[i], nc = c + dc[i];
        int real_nr = 2*r - 1 + dr[i], real_nc = 2*c - 1 + dc[i];
        if( i & 1 ) {
          board[real_nr][real_nc] = 
            code[r][c][nr][nc] == 2 ? "X" : 
            code[r][c][nr][nc] == 1 ? "|" : " ";
        } else {
          board[real_nr][real_nc] = 
            code[r][c][nr][nc] == 2 ? "xxx" : 
            code[r][c][nr][nc] == 1 ? "---" : "   ";
        }
      }
    }
    cout<<"Maze "<<ci++<<":\n\n";
    for(auto& line : board) {
      string result;
      for(string s : line)
        result += s;
      if( !result.empty() )
        cout<<result<<"\n";
    }
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
