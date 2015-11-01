#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <valarray>
#include <vector>
#include <assert.h>
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define fst        first
#define snd        second
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
#define _ << " " <<

typedef unsigned char       uchar;
typedef basic_string<uchar> ustring;
typedef long long           llong;
typedef unsigned long long  ullong;
typedef long double         ldouble;
typedef vector<int>         vi;
typedef vector<vi>          vvi;
typedef vector<double>      vd;
typedef vector<vd>          vvd;
typedef pair<int,int>       pii;

vector<pair<int,vi>> mem;
bool comp(int i, int j) {
  return mem[i].first != mem[j].first ? 
    mem[i].first < mem[j].first :
    lexicographical_compare(all(mem[i].second), all(mem[j].second));
}


void rec(vector<vector<pii>>& g, vi& used, vi& bt, int target, int lim, int u, int d) {
  used[u] = 1;
  bt.eb(u);
  if( u == target ) {
    mem.eb(d, bt);
    bt.pop_back();
    used[u] = 0;
    return;
  }
  for(auto p : g[u]) {
    int v = p.first, cost = p.second;
    if( d + cost > lim || used[v] )
      continue;
    rec(g, used, bt, target, lim, v, d + cost);
  }
  bt.pop_back();
  used[u] = 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int ci = 1;
  
  int n;
  while( cin>>n, ~n ) {
    int m; cin>>m;
    vector<vector<pii>> g(n);
    forn(i,m) {
      int u,v,c; cin>>u>>v>>c; --u; --v;
      g[u].eb(v,c);
      g[v].eb(u,c);
    }
    int start, target; cin>>start>>target;
    --start; --target;
    int lim; cin>>lim;
    mem.clear();
    vi backtrack, used(n);
    rec(g, used, backtrack, target, lim, start, 0);
    vi perm(sz(mem));
    forn(i,sz(mem))
      perm[i] = i;
    stable_sort(all(perm), comp);
    if( ci > 1 )
      cout<<"\n";
    cout<<"Case "<<ci++<<":\n";
    if( mem.empty() ) {
      cout<<"NO ACCEPTABLE TOURS\n";
    } else {
      forn(i,sz(mem)) {
        auto& res = mem[perm[i]];
        cout<<res.first<<":";
        for(int u : res.second)
          cout<<" "<<u+1;
        cout<<"\n";
      }
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
