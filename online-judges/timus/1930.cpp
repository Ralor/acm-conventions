#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<pair<int,int>>> Graph;

#define forn(i,n) for(int i = 0; i < (n); i++)
#define pb push_back
#define mp make_pair
#define inf 1000*1000*1000

struct State {
  int vertex;
  int dist;
  int changes;
  int gear;
  State() { }
  State(int vertex, int dist, int changes, int gear) 
    : vertex(vertex), 
      dist(dist), 
      changes(changes), 
      gear(gear) { }
  bool operator < (const State& s) const {
    return mp(changes, dist) > mp(s.changes, s.dist);
  }
};
enum{GEAR_DOWN, GEAR_UP};

int dijkstra(Graph& g, int from, int to, int start_gear) {
  vector<int> used(g.size());
  priority_queue<State> q; 
  q.push(State(from, 0, 0, start_gear));
  while( !q.empty() ) {
    int u = q.top().vertex,
        d = q.top().dist,
        chg = q.top().changes,
        gear = q.top().gear;
    q.pop();
    if( u == to )
      return chg;
    used[u] = 1;
    for(auto p : g[u]) {
      int v = p.first, 
          chg_required = (p.second != gear);
      if( !used[v] ){
        q.push(State(v, d + 1, chg + chg_required, chg_required ? !gear : gear));
      }
    }
  }
  return inf;
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n,m;
  while( cin>>n>>m ) {
    Graph g(n); // pair<vertex, gear>
    while( m-- ) {
      int u,v;
      cin>>u>>v;
      --u; --v;
      g[u].pb(mp(v,GEAR_UP));
      g[v].pb(mp(u,GEAR_DOWN));
    }
    int from, to;
    cin>>from>>to;
    --from; --to;
    cout<<min(dijkstra(g,from,to,GEAR_DOWN), dijkstra(g,from,to,GEAR_UP))<<"\n";    
  }
  
  return 0;
}