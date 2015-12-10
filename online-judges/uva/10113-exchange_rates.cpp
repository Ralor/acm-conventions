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

int offer(map<string,int>& ntoi, vector<string>& iton, int& cnt, string& name) {
  if( ntoi.count(name) )
    return ntoi[name];
  iton[cnt] = name;
  ntoi[name] = cnt;
  return cnt++;
}

int gcd(int a, int b) {
  while( b )
    a %= b, swap(a,b);
  return a;
}

bool dfs(vvi& a, int n, vi& used, int u, int target, int num, int denom, pii& result) {
  int t = gcd(num, denom);
  num /= t; denom /= t;
  if( u == target ) {
    result = mp(num, denom);
    return true;
  }
  used[u] = 1;
  forn(v,n) if( !used[v] && ~a[u][v] ) {
    if( dfs(a, n, used, v, target, num * a[u][v], denom * a[v][u], result) )
      return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  char c;
  while( cin>>c ) { 
    cin.putback(c);
    int n = 0;
    map<string,int> ntoi;
    vector<string> iton(60);
    vvi a(60, vi(60, -1));
    while( cin>>c, c != '.' )
      if( c == '!' ) {
        string uname, vname;
        int u,v, uval, vval;
        cin>>uval>>uname>>c>>vval>>vname;
        u = offer(ntoi, iton, n, uname);
        v = offer(ntoi, iton, n, vname);
        a[u][v] = uval;
        a[v][u] = vval;
      } else {
        string uname, vname;
        cin>>uname>>c>>vname;
        int u = offer(ntoi, iton, n, uname);
        int v = offer(ntoi, iton, n, vname);
        pii result;
        vi used(n);
        if( dfs(a,n,used,u,v,1,1,result) )
          cout<<result.first<<" "<<iton[u]<<" = "<<result.second<<" "<<iton[v]<<"\n";
        else
          cout<<"? "<<iton[u]<<" = ? "<<iton[v]<<"\n";
      }
  }
  
  TIMESTAMP("end");
  return 0;
}
