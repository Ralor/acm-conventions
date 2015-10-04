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

const char* grid[ ] = {
	"rwwgwwwrwwwgwwr",
	"wbwwwywwwywwwbw",
	"wwbwwwgwgwwwbww",
	"gwwbwwwgwwwbwwg",
	"wwwwbwwwwwbwwww",
	"wywwwwwwwwwwwyw",
	"wwgwwwgwgwwwgww",
	"rwwgwwwwwwwgwwr",
	"wwgwwwgwgwwwgww",
	"wywwwwwwwwwwwyw",
	"wwwwbwwwwwbwwww",
	"gwwbwwwgwwwbwwg",
	"wwbwwwgwgwwwbww",
	"wbwwwywwwywwwbw",
	"rwwgwwwrwwwgwwr",
};

int LCOEFF[128], WCOEFF[128];

const int PRICE[32] = {
  1, 3, 2, 3, 2, 1, 5, 5, 1, 2, 2, 2, 2, 1, 1, 2, 2,
  2, 2, 3, 10, 5, 10, 5, 10, 10, 10, 5, 5, 10, 10, 3
};

bool used[15][15];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  #ifndef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  LCOEFF[int('w')] = 1;
  LCOEFF[int('g')] = 2;
  LCOEFF[int('y')] = 3;
  LCOEFF[int('b')] = 1;
  LCOEFF[int('r')] = 1;
  WCOEFF[int('w')] = 1;
  WCOEFF[int('g')] = 1;
  WCOEFF[int('y')] = 1;
  WCOEFF[int('b')] = 2;
  WCOEFF[int('r')] = 3;
  int n, m;
  while (cin >> n >> m) {
    int score[4] = { };
    int cur = 0;
    memset(used, 0x00, sizeof used);
    while (m--) {
      int w;
      cin >> w;
      int turnScore = 0;
      int lettersUsed = 0;
      while (w--) {
        int len, y, x;
        char type;
        cin >> len >> type >> x >> y;
        y--;
        x--;
        int wordScore = 0;
        int wordCoeff = 1;
        while (len--) {
          int code;
          cin >> code;
          code--;
          wordScore += PRICE[code] * LCOEFF[(uchar)grid[y][x]];
          wordCoeff *= WCOEFF[(uchar)grid[y][x]];
          if (!used[y][x]) {
            used[y][x] = true;
            lettersUsed++;
          }
          if (type == 'v')
            y++;
          else
            x++;
        }
        turnScore += wordScore * wordCoeff;
      }
      if (lettersUsed == 7)
        turnScore += 15;
      score[cur] += turnScore;
      cur = (cur + 1) % n;
    }
    for (int i = 0; i < n; i++)
      cout << score[i] << '\n';
    debug << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
