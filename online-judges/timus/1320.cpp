#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i,n) for(int i = 0; i < (n); i++)
#define pb push_back
#define mp make_pair

int count_edges(vvi& g, set<pair<int,int>>& used, int u) {
  int result = 0;
  for(int v : g[u]) {
    auto edge = mp(u,v);
    if( edge.first > edge.second )
      swap(edge.first, edge.second);
    if( !used.count(edge) ) {
      used.insert(edge);
      result += 1 + count_edges(g,used,v);
    }
  }
  return result;
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif

  vvi g(1111);
  int a,b;
  while(cin>>a>>b) {
    --a; --b;
    if( a > b ) swap(a,b);
    g[a].pb(b);
    g[b].pb(a);
  }
  set<pair<int,int>> used;
  forn(v,1111)
    if( count_edges(g,used,v) & 1 )
      cout<<"0\n", exit(0);
  cout<<"1\n";
  
  return 0;
}