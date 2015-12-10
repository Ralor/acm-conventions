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

enum { N, E, S, W };

const struct {
  int dy, dx;
} DELTAS[ ] = {
  { -1, 0 },
  { 0, 1 },
  { 1, 0 },
  { 0, -1 },
};

int h, w;
bool grid[20][20];
bool used[20][20];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tests;
  cin >> tests;
  for (int ci = 1; ci <= tests; ci++) {
    cin >> h >> w;
    char c = (char)cin.get();
    assert(c == ' ');
    int y = 0, x = 0;
    memset(grid, 0x00, sizeof grid);
    while (cin.get(c) && c != '\n') {
      grid[y][x] = c == '1';
      if (++x == w) {
        x = 0;
        y++;
      }
    }
    cout << ci << ' ';
    y = x = 0;
    int d = E;
    memset(used, 0x00, sizeof used);
    int ch = 0x00, sp = 0;
    for (int pos = 0; pos < h * w; pos++) {
      ch = ch << 1 | grid[y][x];
      used[y][x] = true;
      int ny = y + DELTAS[d].dy, nx = x + DELTAS[d].dx;
      if (ny < 0 || ny >= h || nx < 0 || nx >= w || used[ny][nx]) {
        d = (d + 1) & 0x3;
        ny = y + DELTAS[d].dy;
        nx = x + DELTAS[d].dx;
      }
      y = ny;
      x = nx;
      if (pos % 5 == 4) {
        if (ch) {
          for (int i = 0; i < sp; i++)
            cout << ' ';
          sp = 0;
          cout << char(ch + ('A' - 1));
          ch = 0x00;
        } else
          sp++;
      }
    }
    cout << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
