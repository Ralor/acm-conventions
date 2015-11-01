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

int n;
string s;
int dp[101][101];
int dp2[100][1 << 16];

int Dyn(int left, int right) {
  if (right - left <= 1)
    return right - left;
  assert(left < right);
  assert(left >= 0 && left < n);
  assert(right > 0 && right <= n);
  if (s[left] == s[right - 1])
    return 0;
  if (~dp[left][right])
    return dp[left][right];
  int result = INT_MAX;
  for (int i = left + 1; i < right; i++)
    result = min(result, Dyn(left, i) + Dyn(i, right));
  return (dp[left][right] = result);
}

int Dyn2(int pos, int mask, int indent = 0) {
  for (int j = 0; j < indent; j++)
    debug << "    ";
  debug << "-> " << pos _ bitset<15>(mask) << '\n';
  if (pos == n)
    return 0;
  if (pos == n - 1)
    return mask & 1 << (s[pos] - 'a') ? INT_MIN : 1;
  if (~dp2[pos][mask])
    return dp2[pos][mask];
  char c = s[pos];
  int result = INT_MIN;
  bool ok = true;
  int nextMask = mask | 1 << (s[pos] - 'a');
  for (int i = pos + 1; i < n; i++)
    if (s[i] == c) {
      for (int j = 0; j <= indent; j++)
        debug << "    ";
      debug << "match\n";
      int x = Dyn2(i + 1, mask, indent + 1);
      result = max(result, x);
      for (int j = 0; j <= indent; j++)
        debug << "    ";
      debug << "<- " << x _ result << '\n';
      ok = false;
    } else if (ok) {
      nextMask |= 1 << (s[i - 1] - 'a');
      if (nextMask & 1 << (s[i] - 'a')) {
        ok = false;
        continue;
      }
      int x = Dyn2(i, nextMask, indent + 1);
      result = max(result, i - pos + x);
      for (int j = 0; j <= indent; j++)
        debug << "    ";
      debug << "<- " << x _ result << '\n';
    }
  return (dp2[pos][mask] = result);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while (cin >> n >> s) {
    memset(dp, 0xFF, sizeof dp);
    memset(dp2, 0xFF, sizeof dp2);
    cout << Dyn(0, n) _ Dyn2(0, 0x00) << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
