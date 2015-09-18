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
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int n,lines;
    cin>>n>>lines;
    vvi g(n);
    vi line_cnt(n);
    forn(line,lines) {
      int u,v;
      cin>>u; --u; 
      ++line_cnt[u];
      while( cin>>v, v-- ) {
        ++line_cnt[v];
        g[u].eb(v);
        g[v].eb(u);
        u = v;
      }
    }
    forn(i,n)
      if( line_cnt[i] > 1 )
        debug<<i<<" ";
    debug<<"\n";
    int ru = -1, rsum = 0;
    forn(start,n)
      if( line_cnt[start] > 1 ) {
        vi used(n), dist(n);
        queue<int> q;
        q.push(start);
        used[start] = 1;
        int sum = 0;
        while( !q.empty() ) {
          int u = q.front(); q.pop();
          for(int v : g[u])
            if( !used[v] ) {
              used[v] = 1; 
              dist[v] = dist[u] + 1;
              q.push(v);
              if( line_cnt[v] > 1 )
                sum += dist[v];
            }
        }
        DBG(start); DBG(sum);
        if( ru == -1 || rsum > sum ) {
          rsum = sum;
          ru = start;
        }
      }
      cout<<"Krochanska is in: "<<ru+1<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
