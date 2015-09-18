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

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int cnt;
  while( cin>>cnt, cnt ) {
    vector<pair<int,int>> a(cnt);
    forn(i, cnt) 
      cin>>a[i].second>>a[i].first; // y,x; doesn't matter))
    cin>>cnt;
    vector<pair<int,int>> b(cnt);
    forn(i, cnt)
      cin>>b[i].second>>b[i].first;
    
    vvi board(2222,vi(2222));
    vvi dist(2222,vi(2222));
    queue<pair<int,int>> q;
    for(int i = 0, j = 1; i < sz(a); i++, j++, j %= sz(a)) {
      int dx = a[j].first - a[i].first;
      int dy = a[j].second - a[i].second;
      if( dx ) dx /= abs(dx);
      if( dy ) dy /= abs(dy);
      int x = a[i].first, y = a[i].second;
      while( x != a[j].first || y != a[j].second ) {
        DBG(x); DBG(y);
        q.push(mp(x,y));
        board[x][y] = 1;
        x += dx, y += dy;
      }
    }
    for(int i = 0, j = 1; i < sz(b); i++, j++, j %= sz(b)) {
      int dx = b[j].first - b[i].first;
      int dy = b[j].second - b[i].second;
      if( dx ) dx /= abs(dx);
      if( dy ) dy /= abs(dy);
      int x = b[i].first, y = b[i].second;
      while( x != b[j].first || y != b[j].second ) {
        DBG(x); DBG(y);
        q.push(mp(x,y));
        board[x][y] = 2;
        x += dx, y += dy;
      }
    }
    
    int dx[] = {-1,0,1,0};
    int dy[] = {0,1,0,-1};
    while( !q.empty() ) {
      int x = q.front().first,
          y = q.front().second;
      q.pop();
      debug<<"("<<x<<" "<<y<<")\n";
      forn(i,4) {
        int nx = x + dx[i], ny = y + dy[i];
        if( nx < 0 || ny < 0 || nx > 2000 || ny > 2000 )
          continue;
        if( board[nx][ny] == board[x][y] )
          continue;
        if( board[nx][ny] && board[x][y] != board[nx][ny] ) {
          debug<<"("<<x<<" "<<y<<") -> ("<<nx<<" "<<ny<<") can't do that\n";
          cout<<dist[x][y] + dist[nx][ny] + 1<<"\n";
          goto next_test;
        }
        board[nx][ny] = board[x][y];
        dist[nx][ny] = dist[x][y] + 1;
        q.push(mp(nx,ny));
      }
    }
    next_test:;
  }
  
  TIMESTAMP("end");
  return 0;
}
