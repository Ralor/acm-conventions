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
typedef pair<int,int>      pii;

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

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int n;
  while( cin>>n, n ) {
    map<string,int> ntoi;
    vector<string> iton;
    vector<pair<int,vi>> input_data;
    forn(i,n) {
      input_data.eb();
      string tmp; cin>>tmp;
      int u;
      if( !ntoi.count(tmp) )
        u = ntoi[tmp] = sz(iton), iton.eb(tmp);
      else
        u = ntoi[tmp];
      input_data.back().first = u;
      getline(cin,tmp);
      istringstream in(tmp);
      while( in>>tmp ) {
        int v;
        if( !ntoi.count(tmp) )
          v = ntoi[tmp] = sz(iton), iton.eb(tmp);
        else
          v = ntoi[tmp];
        input_data.back().second.eb(v);
      }
    }
    n = sz(iton);
    vvi g(n);
    vi indeg(n);
    for(auto& p : input_data) {
      int u = p.first;
      for(int v : p.second)
        g[u].eb(v), ++indeg[v];
    }
    vector<string> result;
    queue<int> q;
    forn(u,n)
      if( !indeg[u] )
        q.push(u);
    while( !q.empty() ) {
      int u = q.front(); q.pop();
      for(int v : g[u]) {
        --indeg[v];
        if( indeg[v] == 0 )
          q.push(v);
      }
    }
    forn(u,n)
      if( indeg[u] )
        result.eb(iton[u]);
    if( result.empty() ) {
      cout<<"0\n\n";
      continue;
    }
    cout<<sz(result)<<"\n";
    sort(all(result));
    cout<<result[0];
    for(int i = 1; i < sz(result); i++)
      cout<<" "<<result[i];
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
