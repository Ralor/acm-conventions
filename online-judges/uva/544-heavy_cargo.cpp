#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define pb         push_back
#define mp         make_pair
#define eb         emplace_back
#define ef         emplace_front
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

namespace Trie {
  const int maxn = 20 * 1000 * 30;
  struct Node {
    int id;
    map<char,int> nxt;
    bool leaf;
  } nodes[maxn];
  int node_cnt;
  int name_cnt;
  void init() {
    name_cnt = 0;
    node_cnt = 1;
    forn(i,maxn) {
      nodes[i].nxt.clear();
      nodes[i].leaf = false;
    }
  }
  int offer(const string& s) {
    int cur = 0;
    for(char c : s)
      if( nodes[cur].nxt.count(c) )
        cur = nodes[cur].nxt[c];
      else
        cur = nodes[cur].nxt[c] = node_cnt++;
    if( nodes[cur].leaf )
      return nodes[cur].id;
    nodes[cur].leaf = true;
    return nodes[cur].id = name_cnt++;
  }
}

int parent[200];
int dsu_get(int v) {
  if( parent[v] == v )
    return v;
  return parent[v] = dsu_get(parent[v]);
}
bool dsu_merge(int u, int v) {
  u = dsu_get(u);
  v = dsu_get(v);
  if( u == v )
    return true;
  if( rand() & 1 )
    swap(u,v);
  parent[u] = v;
  return true;
}
typedef tuple<int,int,int> Edge;
bool comp(const Edge& a, const Edge& b) {
  return get<2>(a) > get<2>(b);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int n,m;
  int ci = 1;
  while( cin>>n>>m, n||m ) {
    forn(i,n)
      parent[i] = i;
    Trie::init();
    vector<Edge> edge; edge.reserve(m);
    int u,v,c;
    forn(i,m) {
      string a,b; cin>>a>>b>>c;
      u = Trie::offer(a), v = Trie::offer(b);
      edge.eb(u,v,c);
    }
    string a,b; cin>>a>>b;
    int start = Trie::offer(a), target = Trie::offer(b);
    sort(all(edge),comp);
    for(Edge e : edge) {
      tie(u,v,c) = e;
      if( dsu_merge(u,v) && dsu_get(start) == dsu_get(target) ) {
        cout<<"Scenario #"<<ci++<<"\n"<<c<<" tons\n\n";
        break;
      }
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
