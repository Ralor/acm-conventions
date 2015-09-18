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



int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt", "r", stdin);
#endif
  
  int cn; cin>>cn;
  forn(ci,cn) {
    if( ci )
      cout<<"\n";
    int f,n; cin>>f>>n;
    vi fs(f);
    forn(i,f)
      cin>>fs[i], --fs[i];
    vvi g(n), len(n);
    while( cin.get() != '\n' ) { }
    while(1) {
      string s; getline(cin,s);
      if( s.empty() )
        break;
      istringstream in(s);
      int u,v,cost;
      in>>u>>v>>cost;
      --u; --v;
      g[u].eb(v); len[u].eb(cost);
      g[v].eb(u); len[v].eb(cost);
    }
    int best_start = -1, best_start_value = inf;
    forn(start,n) {
      vi used(n), dist(n,inf);
      dist[start] = 0;
      forn(i,f)
        dist[fs[i]] = 0;
      forn(iter, n) {
        int u = -1;
        forn(i,n)
          if( !used[i] && (! ~u || dist[i] < dist[u]) )
            u = i;
        used[u] = 1;
        forn(i,sz(g[u])){
          int v = g[u][i], cost = len[u][i];
          if( dist[v] > dist[u] + cost )
            dist[v] = dist[u] + cost;
        }
      }
      int value = *max_element(all(dist));
      if( best_start_value > value) {
        best_start_value = value;
        best_start = start;
      }
    }
    cout<<best_start+1<<"\n";    
  }
  
  TIMESTAMP("end");
  return 0;
}
