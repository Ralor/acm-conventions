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

int n, m;
char grid[1004][1004];
bool safe[1004][1004];

struct Delta {
  int dy, dx;
};

const Delta QDELTAS[8] = {
  { 1, 0 },
  { 1, 1 },
  { 0, 1 },
  { -1, 1 },
  { -1, 0 },
  { -1, -1 },
  { 0, -1 },
  { 1, -1 },
};

const Delta KDELTAS[8] = {
  { 2, 1 },
  { 1, 2 },
  { -1, 2 },
  { -2, 1 },
  { -2, -1 },
  { -1, -2 },
  { 1, -2 },
  { 2, -1 },
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int k, y, x;
  int caseNum = 1;
  while (cin >> n >> m, n && m) {
    memset(grid, ' ', sizeof grid);
    memset(safe, 0x01, sizeof safe);
    cin >> k;
    while (k--) {
      cin >> y >> x;
      grid[y + 1][x + 1] = 'Q';
    }
    cin >> k;
    while (k--) {
      cin >> y >> x;
      grid[y + 1][x + 1] = 'K';
    }
    cin >> k;
    while (k--) {
      cin >> y >> x;
      grid[y + 1][x + 1] = 'P';
    }
    for (int i = 2; i < n + 2; i++)
      for (int j = 2; j < m + 2; j++) {
        const Delta* d;
        if (grid[i][j] == 'Q')
          d = QDELTAS;
        else if (grid[i][j] == 'K')
          d = KDELTAS;
        else
          continue;
        for (k = 0; k < 8; k++) {
          y = i + d[k].dy;
          x = j + d[k].dx;
          while (y >= 0 && y < n + 2 && x >= 0 && x < m + 2 && grid[y][x] == ' ') {
            safe[y][x] = false;
            y += d[k].dy;
            x += d[k].dx;
            if (grid[i][j] == 'K')
              break;
          }
        }
      }
    int result = 0;
    for (int i = 2; i < n + 2; i++)
      for (int j = 2; j < m + 2; j++)
        if (grid[i][j] == ' ' && safe[i][j])
          result++;
    cout << "Board " << caseNum++ << " has " << result << " safe squares.\n";
  }
  TIMESTAMP("end");
  return 0;
}
