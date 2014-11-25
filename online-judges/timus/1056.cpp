#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <fstream>
#include <bitset>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifndef _DEBUG
# undef VERBOSE
#endif
#ifdef NDEBUG
#define VERBOSE
#endif

using namespace std;

#pragma comment(linker, "/STACK:256000000")

#define eps 1e-8
#define inf (1000 * 1000 * 1000)
#define linf (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x) ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x) static_cast<int>((x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define mp make_pair
#define mt make_tuple
#define pb push_back

#define forn(i, n) for(int i = 0; i < (n); ++i)

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_;
template<typename I> inline void in(I l,I r)
{while(l!=r)cin>>*l,++l;}
template<typename I> inline void out(I l,I r,char D=' ')
{if(l!=r){cout<<*l;while(++l!=r)cout<<D<<*l;}cout<<'\n';}

struct debug_t {
  template <typename T>
  debug_t& operator<<(const T& value) {
# ifdef VERBOSE
    cout << value;
# endif
    return *this;
  }
} debug;

// just in vs2013, I'll get it after win 8.1)
//void dbg_out(){debug<<'\n';}
//template <typename T, typename... Args>
//void dbg_out(const T& value, const Args&... args)
//{debug<<value;dbg_out(args...);}
//#define dbg(x) #x" = ",x,"; "

typedef unsigned uint;
typedef long long llong;
typedef unsigned long long ullong;
typedef long double ldouble;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;

struct Graph {
  vvi a,d; // adjacenty, delta
  vvi ge; // good (edges)
  vi gv, p; // good, power (vertexes)

  Graph(int n) {
    init(n);
  }
  void init(int n) {
    a.assign(n,vi());
    d.assign(n,vi());
    ge.assign(n,vi());
    gv.assign(n,0);
    p.assign(n,0);
  }
  vi& operator[](const int& index) {
    return a[index];
  }
  int size() {
    return sz(a);
  }
  void add_edge(int u, int v) {
    d[v].pb(sz(a[u])); d[u].pb(sz(a[v]));
    a[u].pb(v); a[v].pb(u);
    ge[u].pb(1); ge[v].pb(1);
    gv[u]=gv[v]=1;
    ++p[u]; ++p[v];
  }
  int ok(int v) {
    return gv[v];
  }
  int ok(int u, int i) {
    return gv[u] && gv[a[u][i]] && ge[u][i];
  }
  void del(int u, int i) {
    ge[u][i]=ge[a[u][i]][d[u][i]]=0; --p[u]; --p[a[u][i]];
  }
  void del(int v) {
    gv[v]=0;
    forn(i,sz(a[v]))
      if( ok(v,i) )
        del(v, i);
  }
};

ostream& operator << (ostream& o, Graph& g) {
  forn(i,sz(g)) if( g.ok(i) ) {
    o<<i+1<<":";
    forn(j,sz(g[i])) if( g.ok(i,j) )
      o<<" "<<(g[i][j]+1);
    o<<"\n";
  }
  return o;
}
int main() {
  //freopen(TASK".in", "r", stdin);
  //freopen(TASK".out", "w", stdout);
#ifdef RALOR_PROJECT
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
#endif
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);

  int n;
  while(cin>>n){
    Graph g(n);
    for(int i=1;i<n;++i){
      int a;cin>>a,--a;
      g.add_edge(i,a);
    }
    //cout<<g<<"\n";
    queue<int> q;
    vi d(n,-1);
    forn(i,n)
      if( sz(g[i])==1 )
        q.push(i), d[i] = 0;
    while( !q.empty() ) {
      int c = q.front(); q.pop();
      forn(i,sz(g[c])) if( g.ok(c,i) ) {
        int nxt = g[c][i];
        g.del(c,i);
        if( g.p[nxt]==1 ) {
          q.push(nxt); d[nxt]=d[c]+1;
        }
      }
      g.del(c);
    }
    int val=*max_element(all(d));
    forn(i,n)
      if( val==d[i] )
        cout<<i+1<<" ";
    cout<<"\n";
  }

  return 0;
}
