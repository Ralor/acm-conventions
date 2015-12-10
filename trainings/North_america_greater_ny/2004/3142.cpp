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



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector < pair<double, double> > p1(3);
  vector < pair<double, double> > p2(3);
  while(cin >> p1[0].first >> p1[0].second && fabs(p1[0].first + 100) > 1e-4)
  {
    for(int i = 1; i < 3; ++i)
      cin >> p1[ i ].first >> p1[ i ].second;
    for(int i = 0; i < 3; ++i)
      cin >> p2[ i ].first >> p2[ i ].second;
    int sum1  =0, sum2  =0;
    for(int i = 0; i < 3; ++i)
    {
      double r = sqrt( sqr( p1[ i ].first) + sqr(p1[ i ].second) );
      if(r <= 3) 
        sum1 += 100;
      else if( r <= 6)
        sum1 += 80;
      else if( r <= 9)
        sum1 += 60;
      else if( r <= 12)
        sum1 += 40;
      else if( r <= 15)
        sum1 += 20;
    }
    for(int i = 0; i < 3; ++i)
    {
      double r = sqrt( sqr( p2[ i ].first) + sqr(p2[ i ].second) );
      if(r <= 3) 
        sum2 += 100;
      else if( r <= 6)
        sum2 += 80;
      else if( r <= 9)
        sum2 += 60;
      else if( r <= 12)
        sum2 += 40;
      else if( r <= 15)
        sum2 += 20;
    }  
    cout <<"SCORE: " <<sum1 << " to " << sum2;
    if(sum1 == sum2) cout << ", TIE.\n";
    else 
    {
      int pid = int(sum2 > sum1) + 1;
      cout << ", PLAYER " << pid << " WINS.\n";
    }
  }
  
  TIMESTAMP("end");
  return 0;
}
