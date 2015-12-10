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
#define _ <<" "<<


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
  
  int dr[] = {-1,0,1,0};
  int dc[] = {0,1,0,-1};
  
  int n,m;
  while( cin>>m>>n ) {
    vector<vvi> bad(4, vvi(n, vi(m)));
    int rest; cin>>rest;
    forn(ololo,rest) {
      int r1,c1,r2,c2; cin>>c1>>r1>>c2>>r2;
      forn(i,4)
        if( r1 + dr[i] == r2 && c1 + dc[i] == c2 )
          bad[i][r1][c1] = 1;
    }
    set<tuple<int,int,int>> cam; 
    int cams; cin>>cams;
    forn(ololo,cams) {
      int t,r,c; cin>>t>>c>>r;
      cam.insert(mt(t,r,c));
    }
    queue<tuple<int,int,int>> q;
    vvi used(n,vi(m));
    q.push(mt(0,0,0));
    used[0][0] = 1;
    while( !q.empty() ) {
      auto& u = q.front(); 
      int t = get<0>(u), r = get<1>(u), c = get<2>(u);
      debug << t _ r _ c << "\n";
      q.pop();
      if( r == n-1 && c == m-1 ) {
        cout<<t<<"\n";
        break;
      }
      forn(i,4) 
        if( !bad[i][r][c] ) {
          int nr = r + dr[i], nc = c + dc[i];
          if( nr < 0 || nc < 0 || nr >= n || nc >= m || used[nr][nc] )
            continue;
          if( cam.count(mt(t + 1, nr, nc)) ) {
            q.push(mt(t + 1, r, c));
          } else {
            used[nr][nc] = 1;
            q.push(mt(t + 1, nr, nc));
          }
        }
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
