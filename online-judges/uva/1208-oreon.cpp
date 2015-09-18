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



int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int cn; cin>>cn;
  forn(ci,cn) {
    int n; cin>>n;
    while( cin.get() != '\n' ) { }
    vvi a(n, vi(n));
    forn(i,n) {
      string tmp; getline(cin,tmp);
      for(char& c : tmp)
        if( c == ',' )
          c = ' ';
      istringstream in(tmp);
      forn(j,n)
        in>>a[i][j];
    }
    vi dist(n, inf), used(n), mst(n);
    dist[0] = 0;
    forn(iter, n) {
      int u = -1;
      forn(i,n)
        if( !used[i] && ( u == -1 || dist[u] > dist[i]) )
          u = i;
      used[u] = 1;
      forn(v,n) 
        if( a[u][v] && !used[v] && dist[v] > a[u][v] )
          dist[v] = a[u][v], mst[v] = u;
    }
    cout<<"Case "<<ci+1<<":\n";
    vector<tuple<int,char,char>> result;
    for(int i = 1; i < n; i++) {
      char u = i + 'A', v = mst[i] + 'A';
      if( u > v ) swap(u,v);
      result.eb(dist[i], u, v);
    }
    sort(all(result));
    for(auto e : result)
      cout<<get<1>(e)<<"-"<<get<2>(e)<<" "<<get<0>(e)<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
