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

struct Box {
  int a, b, c;
} boxes[10];

int n;
int gResult;
int phase = 0;
pair<int, int> initial[10], sorted[10];
int dp[10][21][21];//[pos][height][width]
int lastUsed[10][21][21] = { };

int Dyn(int pos, int height, int width) {
  if (pos == n)
    return 0;
  if (lastUsed[pos][height][width] == phase)
    return dp[pos][height][width];
  int result = Dyn(pos + 1, height, width);
  if (height >= sorted[pos].fst && width >= sorted[pos].snd)
    result = max(result, Dyn(pos + 1, sorted[pos].fst, sorted[pos].snd) + 1);
  lastUsed[pos][height][width] = phase;
  return (dp[pos][height][width] = result);
}

void Search(int pos) {
  if (pos == n) {
    for (int i = 0; i < n; i++)
      sorted[i] = initial[i];
    sort(sorted, sorted + n, greater<pair<int, int>>());
    phase++;
    gResult = max(gResult, Dyn(0, 20, 20));
  } else {
    initial[pos] = { boxes[pos].a, boxes[pos].b };
    if (initial[pos].fst > initial[pos].snd)
      swap(initial[pos].fst, initial[pos].snd);
    Search(pos + 1);
    initial[pos] = { boxes[pos].a, boxes[pos].c };
    if (initial[pos].fst > initial[pos].snd)
      swap(initial[pos].fst, initial[pos].snd);
    Search(pos + 1);
    initial[pos] = { boxes[pos].b, boxes[pos].c };
    if (initial[pos].fst > initial[pos].snd)
      swap(initial[pos].fst, initial[pos].snd);
    Search(pos + 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int ci = 1;
  while (cin >> n, n) {
    for (int i = 0; i < n; i++)
      cin >> boxes[i].a >> boxes[i].b >> boxes[i].c;
    gResult = 0;
    Search(0);
    cout << "Case " << ci++ << ": " << gResult << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
