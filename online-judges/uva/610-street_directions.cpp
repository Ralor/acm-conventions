#include <bits/stdc++.h>
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

#define TIMESTAMP(msg) debug << "[" << msg << "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n' 
#define DBG(x) debug << "[" #x "] = " << x << '\n'
#define forn(i,n) for(int i = 0; i < (n); i++)
#define eb emplace_back
#define all(x) begin(x), end(x)

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long llong;

void find_bridges(vvi& a, vvi& b, vi& tm_in, vi& tm_mn, vi& parent, int& tm, int u) {
  int n = a.size();
  tm_in[u] = tm_mn[u] = tm++;
  forn(v,n)
    if( a[u][v] ) {
      if( ! ~tm_in[v] ) {
        parent[v] = u;
        find_bridges(a,b,tm_in,tm_mn,parent,tm, v);
        tm_mn[u] = min(tm_mn[u], tm_mn[v]);
        if( tm_in[u] < tm_mn[v] )
          b[u][v] = b[v][u] = 1;
      } else if( parent[u] != v ) {
        tm_mn[u] = min(tm_mn[u], tm_in[v]);
      }
    }
}

void cut_edges(vvi& a, vvi& b, int u) {
  int n = a.size();
  forn(v,n) 
    if( a[u][v] && a[v][u] ) {
      if( !b[u][v] )
        a[v][u] = 0, cut_edges(a,b,v);
    }
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int n,m;
  int ci = 1;
  while( cin>>n>>m && (n || m) ) {
    vvi a(n, vi(n)); // adjacency matrix
    forn(edge,m) {
      int u,v;
      cin>>u>>v;
      --u;--v;
      a[u][v] = a[v][u] = 1;
    }
    vvi b(n, vi(n)); // bridge flags
    vi tm_in(n,-1), tm_mn(n), parent(n,-1);
    int tm = 0;
    find_bridges(a,b,tm_in,tm_mn,parent,tm,0);
    forn(u,n)
      cut_edges(a,b,u);
    cout<<ci++<<"\n\n";
    forn(u,n) forn(v,n)
      if( a[u][v] )
        cout<<u+1<<" "<<v+1<<"\n";
    cout<<"#\n";
  }
  
  return 0;
}
