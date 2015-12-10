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
#define DOUT(x) debug << x << '\n'
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
  
  int another_test = 0;
  int n,m;
  while( cin>>n>>m ) {
    vvi board(n,vi(m));
    forn(i, 4*m) {
      int r,c; cin>>r>>c;
      --r; --c;
      board[r][c] = 1;
    }
    int sr, sc; cin>>sr>>sc;
    --sr; --sc;
    typedef tuple<int,int,int> Cell;
    vector<Cell> answer;
    
    const int ddr[] = {0,1,0}; // step deltas
    const int ddc[] = {-1,0,1};
    forn(i,3) {
        int nr = sr + ddr[i], nc = sc + ddc[i];
        if( nr < 0 || nc < 0 || nr >= n || nc >= m )
          continue;
        if( board[nr][nc] == 0 ) 
          answer.eb(nr,nc,1);
      }
    
    const int dr[] = {0,1,1,1,0}; // jump directions
    const int dc[] = {-1,-1,0,1,1};
    queue<Cell> q;
    vvi used(n, vi(m));
    q.push(mt(sr,sc,0));
    while( !q.empty() ) {
      Cell& u = q.front(); 
      int r = get<0>(u),
          c = get<1>(u),
          d = get<2>(u);
      q.pop();
      forn(i,5) {
        int nr = r + dr[i], nc = c + dc[i];
        if( nr < 0 || nc < 0 || nr >= n || nc >= m || board[nr][nc] == 0 )
          continue;
        nr += dr[i];
        nc += dc[i];
        if( nr < 0 || nc < 0 || nr >= n || nc >= m || used[nr][nc] || board[nr][nc] != 0)
          continue;
        used[nr][nc] = 1;
        q.push(mt(nr,nc,d+1));
        answer.eb(nr,nc,d+1);
      }
    }
    
    sort(all(answer), 
      [ ] (const Cell& lhs, const Cell& rhs) {
        return mt(-get<0>(lhs), get<1>(lhs), get<2>(lhs)) < mt(-get<0>(rhs), get<1>(rhs), get<2>(rhs));
      });
    if( another_test++ )
      cout<<"\n";
    for(Cell& c : answer)
      cout<<get<0>(c)+1<<" "<<get<1>(c)+1<<" "<<get<2>(c)<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
