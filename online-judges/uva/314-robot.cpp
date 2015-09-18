#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define pb         push_back
#define mp         make_pair
#define eb         emplace_back
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

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int,int>      pii;

enum { UP, LEFT, DOWN, RIGHT };
int dr[] = {-1,0,1,0};
int dc[] = {0,-1,0,1};

struct State {
  int dir, r, c, dist;
  bool valid(int n, int m) const {
    return r > 0 && c > 0 && r < n && c < m;
  }
  void rotate(int flag) {
    if( flag )
      dir = (dir + 1)%4;
    else
      dir = (dir + 4 - 1)%4;
    ++dist;
  }
  bool go(int len, vvi& board) {
    int n = board.size(), m = board.back().size();
    bool ok = true;
    while( len-- ) {
      r += dr[dir];
      c += dc[dir];
      if( !valid(n,m) )
        return false;
      ok &= board[r][c] == 0;
    }
    ++dist;
    return ok;
  }
};

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int n,m;
  while( cin>>n>>m, n || m ) {
    vvi tmp(n,vi(m));
    forn(i,n) forn(j,m) 
      cin>>tmp[i][j];
    vvi board = tmp;
    forn(i,n) forn(j,m) {
      if( i && tmp[i-1][j] )
        board[i][j] = 1;
      if( j && tmp[i][j-1] )
        board[i][j] = 1;
      if( i && j && tmp[i-1][j-1] )
        board[i][j] = 1;
    }
    
    forn(i,n) {
      forn(j,m)
        debug<<board[i][j]<<" ";
      debug<<"\n";
    }
    
    int sr,sc,tr,tc;
    string dir;
    cin>>sr>>sc>>tr>>tc>>dir;
    
    State start;
    start.r = sr;
    start.c = sc;
    start.dist = 0;
    start.dir = dir == "north" ? UP :
                dir == "west" ? LEFT :
                dir == "south" ? DOWN : 
                dir == "east" ? RIGHT : -1;
    
    queue<State> q; 
    vector<vvi> used(4,vvi(n,vi(m)));
    q.push(start);
    used[start.dir][start.r][start.c] = 1;
    
    while( !q.empty() ) {
      State cur = q.front();
      q.pop();
      if( cur.r == tr && cur.c == tc ) {
        cout<<cur.dist<<"\n";
        break;
      }
      for(int dist = 1; dist <= 3; dist++) {
        State nxt(cur);
        if( !nxt.go(dist,board) || used[nxt.dir][nxt.r][nxt.c] )
          continue;
        if( !used[nxt.dir][nxt.r][nxt.c] ) {
          used[nxt.dir][nxt.r][nxt.c] = 1;
          q.push(nxt);
        }
      }
      for(int flag = 0; flag <= 1; flag++) {
        State nxt(cur);
        nxt.rotate(flag);
        if( !used[nxt.dir][nxt.r][nxt.c] ) {
          used[nxt.dir][nxt.r][nxt.c] = 1;
          q.push(nxt);
        }
      }
    }
    if( !(used[0][tr][tc] || used[1][tr][tc] || used[2][tr][tc] || used[3][tr][tc]) )
      cout<<"-1\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
