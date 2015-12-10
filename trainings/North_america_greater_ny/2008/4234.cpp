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

vector<string> vertical(int h, int m, int s) {
  vector<string> result;
  forn(i,6) {
    string st;
    st += '0' + h%2; h /= 2;
    st += '0' + m%2; m /= 2;
    st += '0' + s%2; s /= 2;
    result.eb(st);
  }
  reverse(all(result));
  return result;
}
vector<string> horizontal(int h, int m, int s) {
  vector<string> result;
  string st;
  st = "";
  forn(i,6)
    st += '0' + h%2, h /= 2;
  reverse(all(st));
  result.eb(st);
  st = "";
  forn(i,6)
    st += '0' + m%2, m /= 2;
  reverse(all(st));
  result.eb(st);
  st = "";
  forn(i,6)
    st += '0' + s%2, s /= 2;
  reverse(all(st));
  result.eb(st);
  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int cn; cin>>cn;
  forn(ci, cn) {
    int h,m,s;
    char c;
    cin>>h>>c>>m>>c>>s;
    vector<string> vert = vertical(h,m,s);
    cout<<ci+1<<" ";
    forn(i,6)
      cout<<vert[i];
    cout<<" ";
    vector<string> horiz = horizontal(h,m,s);
    forn(i,3)
      cout<<horiz[i];
    cout<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
