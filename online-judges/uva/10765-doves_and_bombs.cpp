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

int find_bigeons(vvi& g, vi& bigeon, vi& init_time, int& timer, int u, int parent) {
  int mn_time = init_time[u] = timer++;
  int children = 0;
  for(int v : g[u]) {
    if( parent == v )
      continue;
    if( ~init_time[v] ) {
      mn_time = min(mn_time, init_time[v]);
    } else {
      int nxt_mn_time = find_bigeons(g, bigeon, init_time, timer, v, u);
      mn_time = min(mn_time, nxt_mn_time);
      if( ~parent && init_time[u] <= nxt_mn_time )
        ++bigeon[u];
      ++children;
    }
  }
  if( ! ~parent )
    bigeon[u] = children;
  return mn_time;
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int n,m;
  while( cin>>n>>m, (n || m) ) {
    vvi g(n);
    int aa, bb;
    while( cin>>aa>>bb, ~aa && ~bb ) {
      g[aa].eb(bb);
      g[bb].eb(aa);
    }
    
    vi init_time(n,-1);
    vi bigeon(n,1);
    int timer = 0;
    find_bigeons(g, bigeon, init_time, timer, 0, -1);
    
    vector<pair<int,int>> result;
    forn(u,n)
      result.eb(-bigeon[u], u);
    sort(all(result));
    result.resize(m);
    for(auto& p : result)
      cout<<p.second<<" "<<bigeon[p.second]<<"\n";
    cout<<"\n";
  }
  
  return 0;
}
