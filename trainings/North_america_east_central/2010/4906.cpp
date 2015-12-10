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

const int maxn = 101;
bool valid(int x, int y) {
  return x >= 0 && y >= 0 && x < maxn && y < maxn;
}
bool is_mirror(int value) {
  return value > 100000;
}
const int north = 123534225;
const int east = 524532152;
const int south = 166674634;
const int west = 553114682;
const int dx[] = {1, 0, 0, -1};
const int dy[] = {0, 1, -1, 0};
const int dc[] = {east, north, south, west};
int rot180(int code) {
  return code == north ? south : 
         code == east ? west : 
         code == south ? north : 
         code == west ? east : -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  map<char,int> dtoc;
  dtoc['E'] = east;
  dtoc['N'] = north;
  dtoc['S'] = south;
  dtoc['W'] = west;
  
  int ci = 1;
  
  int v, o, m;
  while( cin>>v>>o>>m, v || o || m ) {
    vvi board(maxn, vi(maxn, -1));
    int x,y;
    forn(i,v)
      cin>>x>>y, board[x][y] = i;
    const int mortal = 123654789;
    forn(i,o)
      cin>>x>>y, board[x][y] = mortal;
    forn(i,m) {
      char dir; int x1,y1,x2,y2;
      cin>>dir>>x1>>y1>>x2>>y2;
      if( x1 > x2 )
        swap(x1,x2);
      if( y1 > y2 )
        swap(y1, y2);
      for(x = x1; x <= x2; x++)
        for(y = y1; y <= y2; y++)
          board[x][y] = dtoc[dir];
    }
    bool at_least_one = false;
    vector<ostringstream> verdicts(v);
    cout<<"Case "<<ci++<<":\n";
    for(int vx = 0; vx < maxn; vx++)
      for(int vy = 0; vy < maxn; vy++)
        if( ~board[vx][vy] && board[vx][vy] < v ) {
          DOUT("vampire" _ board[vx][vy] + 1 _ "found in" _ vx _ vy);
          vector<bool> danger(4);
          bool any_danger = false;
          forn(dir, 4) {
            int cur_x = vx, cur_y = vy;
            while( cur_x += dx[dir], cur_y += dy[dir], valid(cur_x, cur_y) ) {
              if( board[cur_x][cur_y] == mortal )
                break;
              if( is_mirror(board[cur_x][cur_y]) ) {
                DOUT("I see mirror at" _ cur_x _ cur_y _ ":" _ board[cur_x][cur_y]);
                DOUT(rot180(board[cur_x][cur_y]) _ dc[dir]);
              }
              if( is_mirror(board[cur_x][cur_y]) ) {
                if( rot180(board[cur_x][cur_y]) == dc[dir] )
                  danger[dir] = any_danger = true;
                break;
              }
            }
          }
          if( any_danger ) {
            at_least_one = true;
            ostringstream& out = verdicts[board[vx][vy]];
            out<<"vampire "<<board[vx][vy]+1;
            if( danger[0] )
              out<<" east";
            if( danger[1] )
              out<<" north";
            if( danger[2] )
              out<<" south";
            if( danger[3] )
              out<<" west";
          }
        }
      if( !at_least_one ) {
        cout<<"none\n";
      } else {
        forn(i,v) {
          const string& result = verdicts[i].str();
          if( !result.empty() )
            cout<<result<<"\n";
        }
      }
  }
  
  TIMESTAMP("end");
  return 0;
}
