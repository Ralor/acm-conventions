#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i,n) for(int i = 0; i < (n); i++)
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())

void colorize(vvi& g, vi& color, int u, int value) {
  color[u] = value;  
  for(int v : g[u])
    if( color[v] != color[u] ) 
      colorize(g,color,v,value);
}

bool bruteforce_component_ages(vvi& g, vi& color, vi& age, int comp_color, int start_age = 1, int delta = 1) {
  int n = sz(g);
  vi comp;
  forn(i,n)
    if( color[i] == comp_color )
      comp.push_back(i);
  int mx_diff = -1;
  vi mx_age(n);
  for(int first_vertex : comp) { // choose first vertex for bfs
    vi used(n);
    queue<int> q;
    q.push(first_vertex); 
    used[first_vertex] = 1; 
    age[first_vertex] = start_age;
    while( !q.empty() ) {
      int u = q.front(); q.pop();
      for(int v : g[u]) {
        if( used[v] && abs(delta) != abs(age[u] - age[v]) )
          // in case when bfs failed to set ages to pilots, there 
          // is no way to do that, no matter what first_vertex is
          return false; 
        if( !used[v] ) {
          used[v] = 1;
          age[v] = age[u] + delta;
          q.push(v);
        } 
      }
    }
    int comp_mx = 0, comp_mn = 55;
    for(int v : comp){
      comp_mx = max(comp_mx, age[v]);
      comp_mn = min(comp_mn, age[v]);
    }
    int diff = comp_mx - comp_mn;
    if( mx_diff < diff ) {
      mx_diff = diff;
      mx_age.assign(all(age));
    }
  }
  for(int vertex : comp)
    age[vertex] = mx_age[vertex];
  return true;
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int m,n;
  while( cin>>m>>n ) { 
    vvi g(n);
    vi color(n, -1);
    forn(i,m) {
      int u,v;
      cin>>u>>v;
      --u;--v;
      g[u].push_back(v);
      g[v].push_back(u);
      colorize(g,color,u,i);
    }
    vi age(n,-1);
    bool ok = true;
    forn(i,n)
      if( age[i] == -1 )
        ok &= bruteforce_component_ages(g,color,age,color[i]);
    if( !ok ) {
      cout<<"-1\n"; 
      continue;
    }
    int random_component_size = 
      count(all(color), m-1);
    bool several_components = 
      random_component_size < n;
    if( several_components )
      bruteforce_component_ages(g,color,age,m-1,50,-1);
    cout<<*max_element(all(age)) - *min_element(all(age))<<"\n";
    forn(i,n)
      cout<<age[i]<<" ";
    cout<<"\n";
  }
  
  return 0;
}