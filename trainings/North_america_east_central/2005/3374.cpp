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

const struct {
  int dy, dx;
} DELTAS[ ] = {
  { -1, -1 },
  { -1, 0 },
  { -1, 1 },
  { 0, -1 },
  { 0, 1 },
  { 1, -1 },
  { 1, 0 },
  { 1, 1 },
};

int n, m;

int Trans(int y, int x) {
  return (y + n) % n * m + (x + m) % m;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i, k;
  int caseNum = 1;
  while (cin >> n >> m >> k, n && m) {
    int size = n * m;
    int initial = 0x0000;
    while (k--) {
      int y, x;
      cin >> y >> x;
      initial |= 1 << (y * m + x);
    }
    int result = 0;
    int neighbours[16];
    for (int mask = 0x0000; mask < 1 << size; mask++) {
      memset(neighbours, 0x00, size * sizeof(int));
      for (int i = 0; i < size; i++)
        if (mask & 1 << i)
          for (const auto& d: DELTAS)
            neighbours[Trans(i / m + d.dy, i % m + d.dx)]++;
      int next = 0x0000;
      for (i = 0; i < size; i++)
        if (neighbours[i] == 3 || (neighbours[i] == 2 && mask & 1 << i))
          next |= 1 << i;
      if (next == initial)
        result++;
    }
    cout << "Case " << caseNum++ << ": ";
    if (result)
      cout << result << " possible ancestors.\n";
    else
      cout << "Garden of Eden.\n";
  }
  TIMESTAMP("end");
  return 0;
}
