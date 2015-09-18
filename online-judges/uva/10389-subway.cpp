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
  
  int another_test = 0;
  int cn; cin>>cn;
  forn(ci,cn) {
    vector<pair<int,int>> coords(2);
    cin>>coords[0].first>>coords[0].second;
    cin>>coords[1].first>>coords[1].second;
    DOUT(coords[0].first _ coords[0].second _ coords[1].first _ coords[1].second);
    vector<int> color(2);
    int clr = 1;
    while( cin.get() != '\n' ) { }
    while( 1 ) {
      string s; getline(cin,s);
      DOUT(s);
      if( s.empty() )
        break;
      istringstream in(s);
      int x,y;
      while( in>>x>>y, x != -1 ) {
        coords.eb(x,y);
        color.eb(clr);
        DOUT(x _ y _ clr);
      }
      clr++;
    }
    int n = sz(color);
    DBG(n);
    vvi g(n);
    vvd cost(n);
    for(int i = 0; i < n; i++) {
      if( i != 0 )
        g[0].eb(i), cost[0].eb(0.006 * sqrt(sqr(coords[0].first-coords[i].first) + sqr(coords[0].second-coords[i].second)));
      if( i != 1 )
        g[i].eb(1), cost[i].eb(0.006 * sqrt(sqr(coords[1].first-coords[i].first) + sqr(coords[1].second-coords[i].second)));
      if( i >= 2 && color[i] == color[i-1] ) {
        g[i].eb(i-1); cost[i].eb(0.0015 * sqrt(sqr(coords[i].first-coords[i-1].first) + sqr(coords[i].second-coords[i-1].second)));
        g[i-1].eb(i); cost[i-1].eb(0.0015 * sqrt(sqr(coords[i].first-coords[i-1].first) + sqr(coords[i].second-coords[i-1].second)));
      }
    }
    for(int i = 2; i < n; i++)
      for(int j = i+1; j < n; j++) {
        double s = sqrt(sqr(coords[i].first-coords[j].first) + sqr(coords[i].second-coords[j].second));
        g[i].eb(j), cost[i].eb(0.006 * s);
        g[j].eb(i), cost[j].eb(0.006 * s);
      }
    DOUT("input is over");
    vd dist(n, inf);
    priority_queue<pair<double,int>> q;
    q.push(mp(0,0)); dist[0] = 0;
    while( !q.empty() ) {
      int u = q.top().second;
      double d = -q.top().first;
      DBG(u);
      q.pop();
      if( dist[u] < d )
        continue;
      if( u == 1 )
        break;
      forn(i,sz(g[u])) {
        int v = g[u][i];
        double len = cost[u][i];
        if( dist[v] > dist[u] + len ) {
          dist[v] = dist[u] + len;
          q.push(mp(-dist[v],v));
          DBG(dist[v]);
          DOUT(u _ " - > " _ v);
          DOUT(" ");
        }
      }
    }
    if( another_test++ )
      cout<<"\n";
    cout<<int(round(dist[1]))<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
