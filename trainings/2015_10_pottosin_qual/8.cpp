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

int n, s;
struct flower
{
  flower(int t, int p)
  {
    type = t;
    price = p;
  }
  bool operator <(const flower& b) const
  {
    return type < b.type;
  }
  int type;
  int price;
};
short dp[1000 + 1][50*1000 + 1][2]; // pos, sum , was_taken

vector <flower> flow;
void fillTable()
{
  for( int sum = 0; sum <= 50 * 1000; ++sum)
    dp[ n ][ sum ][ 0 ] = dp[ n ][ sum ][ 1 ] = SHRT_MIN;
  for( int pos = 0; pos <= n; ++pos)
    dp[ pos ][ 0 ] [ 0] =  dp[ pos ][ 0 ] [ 1 ] = 0;
  for( int sum = 1; sum <= 50 * 1000; ++sum)
    for( int pos = n-1; pos >=0; --pos)
      {
        int n_type = (pos == n-1 ) || (flow[pos+1].type == flow[pos].type);
        dp[ pos ][ sum ] [ 0 ] = dp[ pos +1 ][ sum ][ 0 ];
        dp[ pos ][ sum ] [ 1 ] = dp[ pos +1 ][ sum ][ n_type ];
        if(flow[pos].price <= sum ) {
          dp[ pos ][ sum ] [ 0 ] = max( short(1 + dp[pos+1][sum - flow[pos].price][n_type]), 
                    dp[ pos ][ sum ] [ 0 ]);
          dp[ pos ][ sum ] [ 1 ] = max( short(dp[pos+1][sum - flow[pos].price][n_type]),
                                      dp[ pos ][ sum ] [ 1 ]);
        }
      }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  #ifndef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
    cin >> n >> s;
    memset(dp, -1, sizeof dp);
    forn(i,n)
    {
      int t, p;
      cin >> t >> p;
      flow.emplace_back(t, p);
    }
  sort(flow.begin(), flow.end());
  fillTable();
  int answ = dp[0][s][0];
  if(answ >0) cout << answ;
    else cout << "Impossible";
  TIMESTAMP("end");
  return 0;
}
