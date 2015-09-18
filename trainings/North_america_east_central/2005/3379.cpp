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

int a[1111];
int dp[1111][1111];
int rec(int l, int r) {
  if( l > r )
    return 0;
  if( ~dp[l][r] )
    return dp[l][r];
  int new_l, new_r, best;
  if( a[l+1] < a[r] )
    best = a[r], new_l = l+1, new_r = r-1;
  else
    best = a[l+1], new_l = l+2, new_r = r;
  int take_left = a[l] - best + rec(new_l, new_r);
  if( a[l] < a[r-1] )
    best = a[r-1], new_l = l, new_r = r-2;
  else
    best = a[l], new_l = l+1, new_r = r-1;
  int take_right = a[r] - best + rec(new_l, new_r);
  return dp[l][r] = max(take_left, take_right);
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int ci = 1;
  int n;
  while( cin>>n, n ) {
    forn(i,n) cin>>a[i];
    memset(dp, -1, sizeof dp);
    int p = rec(0,n-1);
    cout<<"In game "<<ci++<<", the greedy strategy might lose by as many as "<<p<<" points.\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
