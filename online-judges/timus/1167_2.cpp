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

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int,int>      pii;

int color[555];
int dp[555][333];
int rec(int horse, int stable) {
  if( stable == 0 )
    return horse == 0 ? 0 : inf;
  if( horse == 0 )
    return inf;
  if( ~dp[horse][stable] ) 
    return dp[horse][stable];
  int result = inf;
  int white = 0, black = 0; // you can calucalte prefix sums instead
  for(int skip = 1; horse-skip >= 0 && horse-skip >= stable-1; skip++) {
      white += color[horse-skip+1] == 0;
      black += color[horse-skip+1] == 1;
      result = min(result, white * black + rec(horse-skip, stable-1)); 
  }
  return dp[horse][stable] = result;
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int n,k;
  while( cin>>n>>k ) {
    forn(i,n) 
      cin>>color[i+1];
    memset(dp,-1,sizeof dp);
    cout<<rec(n, k)<<"\n";
  }
  
  
  TIMESTAMP("end");
  return 0;
}
