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
#define pb push_back

typedef vector<int> vi;
typedef vector<vi> vvi;

void colorize(vvi& g, vi& color, int u, int value) {
  if( ~color[u] )
    return;
  color[u] = value;
  for(int v : g[u])
    colorize(g, color, v, !value);
}

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
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int n;
  while( cin>>n ) {
    enum { STATEMENT, DATA, DUAL };
    map<int,vector<pair<int,int>>> rtom; // <rang,<id,type>>
    vector<string> iton(n); // <id,name>
    vi itot(n); // <id,type>
    forn(id,n) {
      string name, type;
      int rang;
      cin>>name>>type>>rang;
      iton[id] = name;
      itot[id] = type == "anything" ? DUAL : type == "statements" ? STATEMENT : DATA;
      rtom[rang].emplace_back(id, itot[id]);
    }
    vvi g(n);
    for(auto& p : rtom) {
      int rang = p.first;
      for(auto& vertex : p.second) {
        int u = vertex.first, utype = vertex.second;
        for(int delta = -2; delta <= 2; delta += 4)
          if( rtom.count(rang+delta) ) {
            vector<pair<int,int>>& neighbours = rtom[rang+delta];
            for(auto& neighbour : neighbours) {
              int v = neighbour.first, vtype = neighbour.second;
              if( utype != vtype || utype == DUAL )
                g[u].pb(v), g[v].pb(u);
            }
          }
      }
    }
    vi color(n, -1);
    forn(i,n)
      colorize(g,color,i,0);
    vi match(n, -1);
    forn(i,n) 
      if( color[i] == 0 ) {
        vi used(n,0);
        kuhn(g,used,match,i);
      }
    vector<pair<int,int>> result;
    forn(i,n)
      if( color[i] == 1 && ~match[i]) {
        result.emplace_back(match[i], i);
      }
    cout<<result.size()<<"\n";
    for(auto& p : result)
      if( itot[p.first] == STATEMENT || itot[p.second] == DATA )
        cout<<iton[p.first]<<" "<<iton[p.second]<<"\n";
      else
        cout<<iton[p.second]<<" "<<iton[p.first]<<"\n";
  }
  
  return 0;
}
