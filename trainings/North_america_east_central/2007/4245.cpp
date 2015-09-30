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
  
  int cn; cin>>cn;
  forn(ci,cn) {
    vector<string> board(9);
    forn(i,9)
      cin>>board[i];
    if( ci ) cout<<"\n";
    bool found = false;
    vector<pii> zeros;
    forn(i,9) forn(j,9)
      if( board[i][j] == '0' )
        zeros.eb(i,j);
    set<char> line;
    bitset<10> used;
    for(int a = 1; a <= 9; a++)
      for(int b = 1; b <= 9; b++)
        for(int c = 1; c <= 9; c++)
          for(int d = 1; d <= 9; d++)
            for(int e = 1; e <= 9; e++) {
              board[zeros[0].first][zeros[0].second] = a + '0';
              board[zeros[1].first][zeros[1].second] = b + '0';
              board[zeros[2].first][zeros[2].second] = c + '0';
              board[zeros[3].first][zeros[3].second] = d + '0';
              board[zeros[4].first][zeros[4].second] = e + '0';
              bool ok = true;
              forn(i,9) {
                forn(j,9)
                  used.set(board[i][j] - '0');
                ok &= used.count() == 9;
                used.reset();
                if( !ok ) break;
              }
              if( !ok ) continue;
              forn(j,9) {
                forn(i,9)
                  used.set(board[i][j] - '0');
                ok &= used.count() == 9;
                used.reset();
                if( !ok ) break;
              }
              if( ok ) {
                found = true;
                goto global_break;
              }
            }
    global_break:;
    if( found ) {
      forn(i,9)
        cout<<board[i]<<"\n";
    } else {
      cout<<"Could not complete this grid.\n";
    }
  }
  
  
  TIMESTAMP("end");
  return 0;
}
