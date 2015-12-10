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

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int,int>      pii;

void topsort(vvi& g, vi& used, vi& ts, int u) {
  if( used[u] )
    return;
  used[u] = 1;
  for(int v : g[u])
    topsort(g,used,ts,v);
  ts.eb(u);
}

void colorize(vvi& g, vi& color, vi& mem, int u, int clr) {
  mem.eb(u);
  color[u] = clr;
  for(int v : g[u]) {
    if( ~color[v] )
      continue;
    colorize(g,color,mem,v,clr);
  }
} 

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int first_test_case = 1;
  int n;
  while( cin>>n, n ) {
    if( !first_test_case )
      cout<<"\n";
    first_test_case = 0;
  
    vector<pair<int,vi>> input_data;
    map<char,int> ntoi;
    vector<char> iton;
    forn(i,n) {
      input_data.eb();
      vector<char> t(5);
      for(char& c : t)
        cin>>c;
      char c; cin>>c;
      int u;
      if( ntoi.count(c) )
        u = ntoi[c];
      else
        u = ntoi[c] = sz(iton), iton.eb(c);
      input_data.back().first = u;
      for(char& c : t) {
        int v;
        if( ntoi.count(c) )
          v = ntoi[c];
        else  
          v = ntoi[c] = sz(iton), iton.eb(c);
        if( u != v )
          input_data.back().second.eb(v);
      }
    }
    n = sz(iton);
    vvi g(n), gr(n);
    for(auto& p : input_data) {
      int u = p.first;
      for(int v : p.second)
        g[u].eb(v), gr[v].eb(u);
    }
    vi ts, used(n);
    forn(u,n)
      topsort(g,used,ts,u);
    vi color(n,-1);
    vvi comps;
    forn(i,n) {
      int u = ts[n-i-1];
      if( ~color[u] )
        continue;
      comps.eb();
      colorize(gr,color,comps.back(),u,i);
    }
    vector<string> result;
    for(vi& comp : comps) {
      vector<char> tmp;
      for(int u : comp)
        tmp.eb(iton[u]);
      sort(all(tmp));
      result.eb();
      for(char c : tmp)
        result.back() += c, result.back() += ' ';
      result.back().pop_back();
    }
    sort(all(result));
    for(string& s : result)
      cout<<s<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
