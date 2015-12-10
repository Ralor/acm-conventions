#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i,n) for(int i = 0; i < (n); i++)

bool kuhn(vvi& g, vi& used, vi& match, int u) {
  if( used[u] )
    return false;
  used[u] = 1;
  for(int v : g[u]) 
    if( match[v] == -1 || kuhn(g,used,match,match[v]) ) {
      match[v] = u;
      return true;
    }
  return false;
}

int main() {
#ifdef RALOR_PROJECT
  freopen("input.txt","r",stdin);
#endif

  int n,m,k;
  while(cin>>n>>m>>k){
    vvi g(n);
    while(k--){
      int u,v;
      cin>>u>>v; 
      --u; --v;
      g[u].push_back(v);
    }
    vi match(m,-1);
    forn(i,n) {
      vi used(n);
      kuhn(g,used,match,i);
    }
    vi ok(n+m);
    forn(i,m)
      if( match[i] != -1 ) {
        ok[match[i]] = 1; 
        ok[n+i] = 1;
      }
    int match_size = m - count(begin(match), end(match), -1);
    int lost_edges = count(begin(ok), end(ok), 0);
    cout<<match_size + lost_edges<<"\n";
  }

  return 0;
}