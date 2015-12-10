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

void init_arr(vi& a, int val) {
  forn(i,9)
    a[9-i-1] = val % 4, val /= 4;
}

int get_val(vi& a) {
  int val = 0;
  forn(i,9)
    val += a[i], val *= 4;
  val /= 4;
  return val;
}

bool check(vvi& a, int val) {
  static vi rot(9);
  init_arr(rot, val);
  int v1,v2,v3,v4;
  int s1,s2,s3,s4;
  v1 = a[0][(2+rot[0])%4];
  v2 = a[1][(3+rot[1])%4];
  v3 = a[3][(1+rot[3])%4];
  v4 = a[4][(0+rot[4])%4];
  s1 = v1 + v2 + v3 + v4;
  v1 = a[1][(2+rot[1])%4];
  v2 = a[2][(3+rot[2])%4];
  v3 = a[4][(1+rot[4])%4];
  v4 = a[5][(0+rot[5])%4];
  s2 = v1 + v2 + v3 + v4;
  v1 = a[3][(2+rot[3])%4];
  v2 = a[4][(3+rot[4])%4];
  v3 = a[6][(1+rot[6])%4];
  v4 = a[7][(0+rot[7])%4];
  s3 = v1 + v2 + v3 + v4;
  v1 = a[4][(2+rot[4])%4];
  v2 = a[5][(3+rot[5])%4];
  v3 = a[7][(1+rot[7])%4];
  v4 = a[8][(0+rot[8])%4];
  s4 = v1 + v2 + v3 + v4;
  return s1 == s2 && s3 == s4 && s1 == s3;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  vvi a(9, vi(4));
  
  forn(i, 9) forn(j, 4)
    cin>>a[i][j];
  
  vi used(1 + (1 << 18)), dist(1 + (1 << 18));
  queue<int> sq;
  sq.push(0); used[0] = 1;
  vi arr(9);
  while( !sq.empty() ) {
    int cur = sq.front(); sq.pop();
    if( check(a, cur) ) {
      cout<<dist[cur]<<"\n";
      goto stop;
    }
    init_arr(arr, cur);
    if( dist[cur] == 5 ) {
      forn(i,9)
        debug<<arr[i]<<" ";
      debug<<"\n";
    }
    forn(i,9) {
      int nxt, t;
      t = arr[i];
      arr[i] = (arr[i] + 1) % 4;
      nxt = get_val(arr);
      if( !used[nxt] ) {
        used[nxt] = 1;
        dist[nxt] = dist[cur] + 1;
        sq.push(nxt);
      }
      arr[i] = t;
      arr[i] = (arr[i] + 3) % 4;
      nxt = get_val(arr);
      if( !used[nxt] ) {
        used[nxt] = 1;
        dist[nxt] = dist[cur] + 1;
        sq.push(nxt);
      }
      arr[i] = t;
    }
  }
  cout<<"-1\n";
  stop:;
  
  TIMESTAMP("end");
  return 0;
}
