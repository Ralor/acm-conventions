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


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n;
  while( cin>>n, n ) {
    vi x(n), y(n);
    map<int,map<int,int>> a;
    forn(i,n)
      cin>>x[i]>>y[i], a[x[i]][y[i]] = i;
    vi color(n, -1), deg(n);
    forn(u,n) if( deg[u] < 2 ) {
      if( color[u] == -1 )
        color[u] = u;
      map<int,set<pii>> neighbours;
      forn(v,n) if( u != v && deg[v] < 2 )
        neighbours[sqr(x[u] - x[v]) + sqr(y[u] - y[v])].insert(mp(x[v], y[v]));
      set<pii>& candidates = neighbours.begin()->second;
      for(int xx = -20; xx <= 20 && deg[u] <= 2; xx++)
        for(int yy = -20; yy <= 20 && deg[u] <= 2; yy++)
          if( candidates.count(mp(xx,yy)) ) {
            int v = a[xx][yy];
            ++deg[u]; ++deg[v];
            DOUT(u _ v _ "(" _ color[u] _ color[v] _ ")");
            if( ~color[v] ) {
              if( color[u] != color[v] ) {
                int old_color = color[v];
                forn(i,n)
                  if( color[i] == old_color )
                    color[i] = color[u];
              }
            } else {
              color[v] = color[u];
            }
          }
    }
    forn(i,n)
      debug<<color[i]<<" ";
    debug<<"\n";
    if( count(all(color), color[0]) == n )
      cout<<"All stations are reachable.\n";
    else
      cout<<"There are stations that are unreachable.\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
