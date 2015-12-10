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
  
  int ci = 1;
  
  int n,m;
  while( cin>>n>>m, n || m ) {
    vector<vector<vector<int>>> board(n, vvi(m, vi(1)));
    forn(i,n) forn(j,m)
      cin>>board[i][j][0];
    int l = 0, r = m-1, u = 0, b = n-1;
    while( cin.get() != '\n' ) { }
    string comms; getline(cin,comms);
    for( char com : comms ) {
      DOUT(com);
      switch( com ) {
      case 'L': 
        for(int i = u; i <= b; i++)
          for(int k = sz(board[i][l]) - 1; k >= 0; k--)
            board[i][l+1].eb(-board[i][l][k]), DOUT("flipping" _ board[i][l][k]);
        ++l;
        break;
      case 'R':
        for(int i = u; i <= b; i++)
          for(int k = sz(board[i][r]) - 1; k >= 0; k--)
            board[i][r-1].eb(-board[i][r][k]), DOUT("flipping" _ board[i][r][k]);
        --r;
        break;
      case 'T':
        for(int j = l; j <= r; j++)
          for(int k = sz(board[u][j]) - 1; k >= 0; k--)
            board[u+1][j].eb(-board[u][j][k]), DOUT("flipping" _ board[u][j][k]);
        ++u;
        break;
      case 'B':
        for(int j = l; j <= r; j++)
          for(int k = sz(board[b][j]) - 1; k >= 0; k--)
            board[b-1][j].eb(-board[b][j][k]), DOUT("flipping" _ board[b][j][k]);
        --b; 
        break; 
      }
      DOUT(l _ r _ u _ b);
    }
    cout<<"Case "<<ci++<<":"; 
    for(int v : board[u][l]) 
      if( v > 0 )
        cout<<" "<<v;
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
