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

bool Compare(const string& a, const string& b) {
  int n = (int)a.length(), m = (int)b.length();
  int i = 0, j = 0;
  while (i < n || j < m) {
    for (; i < n && j < m; i++, j++)
      if (isdigit(a[i]) && isdigit(b[j]))
        break;
      else if (a[i] != b[j])
        return a[i] < b[j];
    if (i == n)
      return true;
    if (i == m)
      return false;
    int lza = 0, lzb = 0;
    while (i < n && a[i] == '0') {
      lza++;
      i++;
    }
    while (j < m && b[j] == '0') {
      lzb++;
      j++;
    }
    int cmp = 0;
    for (; i < n && j < m && isdigit(a[i]) && isdigit(b[j]); i++, j++)
      if (!cmp && a[i] != b[j])
        cmp = a[i] < b[j] ? -1 : 1;
    if (i < n && isdigit(a[i]))
      return false;
    if (j < m && isdigit(b[j]))
      return true;
    if (cmp)
      return cmp < 0;
    if (lza != lzb)
      return lza > lzb;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  vector<string> v;
  while (cin >> n) {
    v.resize(n);
    debug << Compare("b1a", "b1b") _ Compare("b1b", "b1a1") << '\n';
    for (string& s: v)
      cin >> s;
    sort(v.begin(), v.end(), Compare);
    for (const string& s: v)
      cout << s << '\n';
    debug << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
