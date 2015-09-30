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

const char A[20][4] = {
  "000",
  "002",
  "004",
  "006",
  "030",
  "032",
  "034",
  "036",
  "040",
  "042",
  "044",
  "046",
  "050",
  "052",
  "054",
  "056",
  "060",
  "062",
  "064",
  "066",
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  vector<int> v;
  while (cin >> n, n) {
    v.clear();
    do
      v.push_back(n % 20);
    while (n /= 20);
    ostringstream ss;
    for (int i = (int)v.size() - 1; i; i--) {
      ss << A[v[i]] << ',';
      if (i == 7)
        ss << "000,000,";
    }
    ss << A[v[0]];
    string s = ss.str();
    auto p = s.c_str();
    while (*p == '0')
      p++;
    cout << p << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
