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
  
  int m;
  while( cin>>m, m ) {
    string from,to;
    cin>>from>>to;
    if( from == to ) while(1) { }
    vector<tuple<int,int,string>> input_data; { // old edges <u,v,word>
      int old_size = 0;
      map<string,int> ntoi;
      ntoi[from] = 0; 
      ntoi[to] = 1;
      old_size = 2;
      forn(i,m) {
        string a,b; cin>>a>>b;
        string word; cin>>word;
        int u;
        if( ntoi.count(a) ) 
          u = ntoi[a];
        else
          u = ntoi[a] = old_size++;
        int v;
        if( ntoi.count(b) )
          v = ntoi[b];
        else
          v = ntoi[b] = old_size++;
        input_data.eb(u,v,word);
      }
      
      for(auto& e : input_data) {
        int u = get<0>(e), v = get<1>(e);
        string& s = get<2>(e);
        DOUT(u _ v _ s);
      } 
    }
    
    int n;
    int start, stop;
    vector<tuple<int,int,int>> edges; { // new edges <u,v,cost> that formes messy directed graph
      map<string,int> etoi;
      int new_size = 0;
      forn(i, sz(input_data)) forn(j, sz(input_data)) if( i != j ) {
        int u1 = get<0>(input_data[i]), v1 = get<1>(input_data[i]);
        string& word1 = get<2>(input_data[i]);
        int u2 = get<0>(input_data[j]), v2 = get<1>(input_data[j]);
        string& word2 = get<2>(input_data[j]);
        bool adj = u1 == u2 || u1 == v2 || v1 == u2 || v1 == v2;
        if( adj && word1[0] != word2[0] ) {
          DOUT(u1 _ v1 _ word1 _ u2 _ v2 _ word2);
          int u;
          if( etoi.count(word1) )
            u = etoi[word1];
          else
            u = etoi[word1] = new_size++;
          int v;
          if( etoi.count(word2) )
            v = etoi[word2];
          else
            v = etoi[word2] = new_size++;
          edges.eb(u,v,sz(word2));
        }
      }
      forn(i, sz(input_data)) {
        string& word = get<2>(input_data[i]);
        if( !etoi.count(word) ) // some edges (u,v) may be not connected to anything at all, but it shouldn't disappear
          etoi[word] = new_size++;
      }
      
      start = new_size++;
      stop = new_size++;
      n = new_size;
      forn(i, sz(input_data)) {
        int u = get<0>(input_data[i]), v = get<1>(input_data[i]);
        string& word = get<2>(input_data[i]);
        if( (u == 0 || v == 0) && etoi.count(word) ) {
          edges.eb(start, etoi[word], sz(word));
          DOUT("start vertex directed to" _ "(" << u << ";" << v << ")" _ sz(word));
        } 
        if( (u == 1 || v == 1) && etoi.count(word) ) {
          edges.eb(etoi[word], stop, 0);
          DOUT("stop vertex covered by" _ "(" << u << ";" << v << ")");
        } 
      }
    }
    DBG(n);
    vvi g(n), cost(n);
    for(auto& e : edges) {
      int u = get<0>(e), v = get<1>(e), len = get<2>(e);
      g[u].eb(v); cost[u].eb(len);
      DOUT(u _ v _ len);
    }
    vi dist(n,inf);
    priority_queue<pair<int,int>> q;
    q.emplace(0, start);
    dist[start] = 0;
    while( !q.empty() ) {
      int u = q.top().second, d = -q.top().first;
      q.pop();
      if( d > dist[u] )
        continue;
      forn(i,sz(g[u])) {
        int v = g[u][i], len = cost[u][i];
        if( dist[v] > dist[u] + len ) {
          dist[v] = dist[u] + len;
          q.emplace(-dist[v], v);
        }
      }
    }
    if( dist[stop] == inf )
      cout<<"impossivel\n";
    else
      cout<<dist[stop]<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
