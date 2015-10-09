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
struct changing
{
  int type; // 0 - reset, 1 - set;
  int pos;
};
vi price;

bool comp(changing a, changing b)
{
  if(a.type == b.type)
  {
    if(a.type == 0) return price[a.pos] > price[b.pos];
    else return price[a.pos] < price[b.pos];
  }
  else
   return a.type < b.type;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  int tnum = 0;
  while(cin >> n && n != 0)
  {
    ++tnum;
    price.assign(n,0);
    vector <bool> curmask(n, false), resmask(n, false);
    string str;
    cin >> str;
    forn(i,n)
      if(str[ i ] == '1') curmask[ i ] =  true;
    cin >> str;
    forn(i,n)
      if(str[ i ] == '1') resmask[ i ] =  true;
    forn(i, n)
      cin >> price[ i ];
    vector < changing > ch;
    int cursum = 0;
    int sm = 0, fm  =0;
    forn(i,n)
    {
      if(curmask[i]) sm += price[i];
      if(resmask[i]) fm += price[i];
      if(curmask[i] && (curmask[i] != resmask[i])) cursum += price[i];
      if(curmask[i] != resmask[i])
      {
        changing curch;
        curch.type = resmask[i];
        curch.pos = i;
        ch.pb( curch );
      }
    }
    sort(ch.begin(), ch.end(), comp);
    int res = 0;
    forn(i, sz(ch))
    {
      if(ch[i].type == 0)
      {
        cursum -= price[ch[ i ].pos];
        res += cursum;
      }
      else
      {
        cursum += price[ch[ i ].pos];
        res += cursum;
      }
      //debug << res << "\n";
    }
   
    forn(i, n)
      if(curmask[i] && (curmask[i] == resmask[i]))
      {
        int was_reset = sm - price[i] + res + fm;
        int stayed_set = res + sz(ch) * price[i];
        res = min(was_reset, stayed_set);
      }
    cout << "Case " << tnum<< ": " << res << "\n";
  }
  TIMESTAMP("end");
  return 0;
}
