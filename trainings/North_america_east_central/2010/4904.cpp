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

int m, n;
bool grid[2][100][100];
int cur;

void Print() {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      debug << (grid[cur][i][j] ? '#' : '.');
    debug << '\n';
  }
  debug << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int caseNum = 1;
  int ring, cell;
  while (cin >> m >> n, m) {
    int k;
    cin >> k;
    memset(grid[0], 0x00, sizeof grid[0]);
    cur = 0;
    while (k--) {
      cin >> ring >> cell;
      grid[cur][ring][cell] = true;
    }
    cin >> k;
    while (Print(), k--) {
      for (ring = 0; ring < m; ring++)
        for (cell = 0; cell < n; cell++) {
          int count = 0;
          count += grid[cur][ring][(cell - 1 + n) % n];
          count += grid[cur][ring][(cell + 1) % n];
          int ring2 = ring ? ring - 1 : 0;
          int cell2 = ring ? cell : cell + (n >> 1);
          count += grid[cur][ring2][cell2 % n];
          count += grid[cur][ring2][(cell2 - 1 + n) % n];
          count += grid[cur][ring2][(cell2 + 1) % n];
          ring2 = ring < m - 1 ? ring + 1 : ring;
          cell2 = ring < m - 1 ? cell : cell + (n >> 1);
          count += grid[cur][ring2][cell2 % n];
          count += grid[cur][ring2][(cell2 - 1 + n) % n];
          count += grid[cur][ring2][(cell2 + 1) % n];
          grid[!cur][ring][cell] = count == 3 || (count == 2 && grid[cur][ring][cell]);
        }
      cur = !cur;
    }
    pair<int, int> fst(-1, -1), last(-1, -1);
    int count = 0;
    for (ring = 0; ring < m; ring++)
      for (cell = 0; cell < n; cell++)
        if (grid[cur][ring][cell]) {
          count++;
          last = make_pair(ring, cell);
          if (!~fst.fst)
            fst = last;
        }
    cout << "Case " << caseNum++ << ": " << count _ fst.fst _ fst.snd _ last.fst _ last.snd << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
