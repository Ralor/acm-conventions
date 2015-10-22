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

inline int popcnt(int x) {
  int cnt = 0;
  while( x )
    x &= x - 1, ++cnt;
  return cnt;
}

void print(int n, int mask, vi& outstrip, vector<char>& bt) {
  forn(u,26) if( (1 << u) & mask ) {
    int next_mask = mask & ~outstrip[u] & ~(1<<u);
    bt.eb(u+'A');
    if( n == sz(bt) ) {
      cout<<bt[0];
      for(int i = 1; i < sz(bt); i++)
        cout<<" "<<bt[i];
      cout<<"\n";
    } else if( popcnt(next_mask) >= n - sz(bt) ) {
      print(n, next_mask, outstrip, bt);
    }
    bt.pop_back();
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int cn; cin>>cn;
  while( cin.get() != '\n' ) { }
  forn(ci,cn) {
    while( cin.get() != '\n' ) { }
    string aa; getline(cin,aa);
    string bb; getline(cin,bb);
    int n = count(all(aa), ' ') + 1;
    istringstream in(aa + " " + bb);
    int vertexes = 0;
    forn(i,n) {
      char c; in>>c;
      vertexes |= 1 << (c - 'A');
    }
    vector<int> outstrip(26);
    string edge;
    bool cycle_found = false;
    while( in>>edge ) {
      int u = edge[0] - 'A', v = edge[2] - 'A';
      if( outstrip[u] & (1<<v) ) {
        cycle_found = true;
        break;
      }
      outstrip[v] |= (1<<u) | outstrip[u];
    }
    if( ci )
      cout<<"\n";
    if( cycle_found ) {
      cout<<"NO\n";
      continue;
    }
    vector<char> backtrack;
    print(n,vertexes,outstrip,backtrack);
  }
  
  TIMESTAMP("end");
  return 0;
}
