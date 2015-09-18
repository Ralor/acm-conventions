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

vector<pair<int,int>> result;

void find_bridges(vvi& g, vi& parent, vi& tm_in, vi& tm_mn, int& tm, int u) {
  tm_in[u] = tm_mn[u] = tm++;
  for(int v : g[u])
    if( ! ~tm_in[v] ) {
      parent[v] = u;
      find_bridges(g,parent,tm_in,tm_mn,tm,v);
      tm_mn[u] = min(tm_mn[u], tm_mn[v]);
      if( tm_in[u] < tm_mn[v] ) // wow, tm_mn[v] can't get to my parents
        result.eb(min(u,v), max(u,v));
    } else if( v != parent[u] ) {
      tm_mn[u] = min(tm_mn[u], tm_in[v]);
    }
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int n;
  while( cin>>n ) {
    while( cin.get() != '\n' ) { /* fix getline behaviour */ }
    vvi g(n);
    forn(i,n) {
      string t; getline(cin,t);
      istringstream inp(t);
      int u,v; inp>>u>>t;
      while( inp>>v )
        g[u].eb(v), g[v].eb(u);
    }
    vi tm_in(n, -1), tm_mn(n), parent(n,-1);
    int tm = 0;
    result.clear();
    forn(i,n)
      if( ! ~tm_in[i] )
        find_bridges(g,parent,tm_in,tm_mn,tm,i);
    sort(all(result));
    cout<<result.size()<<" critical links\n";
    for(auto& p : result)
      cout<<p.first<<" - "<<p.second<<"\n";
    cout<<"\n";
  }
  
  return 0;
}
