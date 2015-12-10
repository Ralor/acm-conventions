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

const int maxn = 1000*1000+1;
static int comp[maxn] = { };

int a,b,d;
bool rec(int cnt, vi& result, vi& pref, vi& used) {
  if( !cnt )
    return true;
  for(int val = a; val <= b; val++) if( !used[val] ) {
    bool good = true;
    result.eb(val);
    pref.eb(val + ( pref.empty() ? 0 : pref.back() ));
    for(int len = 2; len <= min(sz(pref),d); len++) {
      int r = sz(pref) - 1;
      int l = sz(pref) - len;
      good &= comp[pref[r] - ( l ? pref[l-1] : 0)];
    }
    if( good ) {
      used[val] = 1;
      if( rec(cnt-1, result, pref, used) )
        return true;
      used[val] = 0;
    }
    result.pop_back();
    pref.pop_back();
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  for(int i = 2; i < maxn; i++) 
    if( !comp[i] )
      for(llong j = i*1LL*i; j < maxn; j += i)
        comp[j] = 1;
  
  while( cin>>a>>b>>d, a || b || d ) {
    vi used(b+1), result, pref; 
    result.reserve(b-a+1);
    pref.reserve(b-a+1);
    if( rec(b-a+1,result,pref,used) ) {
      cout<<result[0];
      for(int i = 1; i < sz(result); i++)
        cout<<","<<result[i];
      cout<<"\n";
    } else {
      cout<<"No anti-prime sequence exists.\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
