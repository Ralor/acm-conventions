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
  freopen("input.txt","r",stdin);
#endif
  
  int n,k;
  while( cin>>n>>k ) {
    vi speed(n);
    forn(i,n)
      cin>>speed[i];
    while( cin.get() != '\n' ) { }
    // [id] -> <height, elevator number>
    vector<pii> iton; 
    // [elevator number] -> <ids, heights>
    vector<pair<vi,vi>> input_data; { 
      map<pii,int> ntoi;
      forn(elev,n) {
        string s; getline(cin,s);
        istringstream in(s);
        input_data.eb();
        pii tmp(-1,elev);
        while( in >> tmp.first ) {
          int u;
          if( ntoi.count(tmp) )
            u = ntoi[tmp];
          else
            u = ntoi[tmp] = sz(iton), iton.eb(tmp);
          input_data.back().first.eb(u);
          input_data.back().second.eb(tmp.first);
        }
      }
    }
    
    n = sz(iton);
    vector<vector<pii>> g(n);
    for(auto& t : input_data) {
      vi& arr = t.first;
      for(int i = 1; i < sz(arr); i++) {
        int v = arr[i], u = arr[i-1], len = iton[v].first - iton[u].first;
        g[u].eb(v, len * speed[iton[v].second]);
        g[v].eb(u, len * speed[iton[u].second]);
        u = v;
      }
    }
    
    forn(aa,sz(input_data)) forn(bb,sz(input_data)) if( aa != bb ) {
      vi& av = input_data[aa].first;
      vi& ah = input_data[aa].second;
      vi& bv = input_data[bb].first;
      vi& bh = input_data[bb].second;
      forn(i,sz(av)) {
        int u = av[i];
        int pos = find(all(bh), ah[i]) - begin(bh);
        if( pos < sz(bh) && ah[i] == bh[pos] ) {
          int v = bv[pos];
          g[u].eb(v,60);
        }
      }
    }
    
    vi dist(n,inf);
    priority_queue<pii> q;
    forn(u,n)
      if( iton[u].first == 0 ) {
        dist[u] = 0;
        q.emplace(0,u);
      }
      
    while( !q.empty() ) {
      int u = q.top().second, d = -q.top().first;
      q.pop();
      if( d > dist[u] )
        continue;
      forn(i,sz(g[u])) {
        int v = g[u][i].first, len = g[u][i].second;
        if( dist[v] > dist[u] + len ) {
          dist[v] = dist[u] + len;
          q.emplace(-dist[v], v);
        }
      } 
    }
    
    int mn = inf;
    forn(u,n)
      if( iton[u].first == k )
        mn = min(mn, dist[u]);
    if( mn == inf )
      cout<<"IMPOSSIBLE\n";
    else
      cout<<mn<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
