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

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int, int>     pii;

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

void topsort(vvi& g, vi& used, vi& ts, int u) {
  used[u] = 1;
  for(int v : g[u])
    if( !used[v] )
      topsort(g, used, ts, v);
  ts.eb(u);
}
void colorize(vvi& g, vi& color, int u, int clr) {
  color[u] = clr;
  for(int v : g[u]) {
    if( ! ~color[v] )
      colorize(g,color,v,clr);
  }
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int n,m;
  int ci = 1;
  while( cin>>n>>m, n || m ) {
    if( ci > 1 ) 
      cout<<"\n";
    vvi g(n), gr(n);
    int id = 0;
    map<string,int> ntoi;
    vector<string> iton(n);
    forn(call, m) {
      string a,b; cin>>a>>b;
      int u,v;
      if( ntoi.count(a) )
        u = ntoi[a];
      else
        iton[id] = a, ntoi[a] = u = id++;
      if( ntoi.count(b) )
        v = ntoi[b];
      else
        iton[id] = b, ntoi[b] = v = id++;
      g[u].eb(v);
      gr[v].eb(u);
    }
    vi used(n), ts;
    forn(u,n)
      if( !used[u] )
        topsort(g, used, ts, u);
    vi color(n,-1);
    int clr = 0;
    forn(i,n) {
      int u = ts[n-i-1];
      if( ! ~color[u] )
        colorize(gr, color, u, clr++);
    }
    cout<<"Calling circles for data set "<<ci++<<":\n";
    forn(c,clr) {
      vi component;
      forn(i,n)
        if( color[i] == c )
          component.eb(i);
      cout<<iton[component[0]];
      for(int i = 1; i < sz(component); i++)
        cout<<", "<<iton[component[i]];
      cout<<"\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
