#include <cassert>
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

inline bool getb(int a, int n)
{
  return (a>>n)&1;
 } 
inline int setb(int a, int n)
{
  return a|(1 << n);
}
llong dp[ 1000 ][ 16 ][ 16 ];
int last[ 1000 ][ 16 ][ 16 ] = { };
int n,t;
llong getVal( int pos, uchar mask1, uchar mask2)
{
  //debug << int(mask1) << "\n";
  if(pos == n)
  {
    //debug << "exit";
    return 1;
    
  }
  if(mask1 >= 15)
    return  getVal(pos + 1, mask2, 0);
  
  if( last[ pos ][ mask1 ][ mask2 ] == t ) return dp[ pos ][ mask1 ][ mask2 ]; 
  llong res = 0; 
  
  for(int i = 0; i < 3; ++i)
    if(!getb(mask1, i) && !getb(mask1, i+1))
      {
        uchar nmask = uchar(setb( mask1, i ) | setb( mask1, i+1 ));
        res += getVal(pos, nmask, mask2);
        break;
      }
  if(pos < n - 1 )
    for(int i = 0; i < 4; ++i)
      if(!getb(mask1, i) && !getb(mask2, i))
        {
          uchar nmask1 = (uchar)setb( mask1, i ); 
          uchar nmask2 = (uchar)setb( mask2, i ); 
          res += getVal(pos, nmask1, nmask2);
          break;
        }
  last[ pos ][ mask1 ][ mask2 ] = t;
  return dp[ pos ][ mask1 ] [ mask2 ] = res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tn;
  cin >> tn;
  for(t = 1; t <= tn; ++t)
  {
    //memset(used ,0, sizeof(used));
    cin >> n;
    cout << t  << " " <<getVal(0, 0, 0) << "\n";
  }
  TIMESTAMP("end");
  return 0;
}