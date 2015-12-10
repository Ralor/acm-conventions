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

enum { F, B, L, R, U, D };

const char DIRS[ ] = "FBLRUD";

const pair<int, int> DELTAS[6][6] = {
  { { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } },
  { { 0, 0 }, { 0, 0 }, { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } },
  { { 0, -1 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, -1 }, { 0, -1 } },
  { { 0, 1 }, { 0, -1 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 1 } },
  { { -1, 0 }, { -1, 0 }, { -1, 0 }, { -1, 0 }, { 0, 0 }, { 0, 0 } },
  { { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 0, 0 }, { 0, 0 } },
};

const int INPUT_ORDER[ ] = { F, R, B, L, U, D };

using pos_t = tuple<pair<int, int>, pair<int, int>, pair<int, int>>;

int n;
vector<string> grid[6];
map<pos_t, pair<int, pos_t>> used;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i, j, k;
  string result;
  while (cin >> n >> ws, n) {
    for (k = 0; k < 6; k++) {
      grid[INPUT_ORDER[k]].resize(n);
      for (i = 0; i < n; i++)
        getline(cin, grid[INPUT_ORDER[k]][i]);
    }
    queue<pos_t> q;
    pos_t start( { n - 2, n - 2 }, { n - 2, n - 2 }, { n - 2, n - 2 } );
    q.emplace(start);
    used.clear();
    used.emplace(start, make_pair(-1, start));
    pos_t curPos;
    do {
      pair<int, int> p[6];
      curPos = q.front();
      q.pop();
      tie(p[F], p[L], p[U]) = curPos;
      debug << ':' << p[F].fst _ p[F].snd _ p[L].fst _ p[L].snd _ p[U].fst _ p[U].snd << '\n';
      if (curPos == pos_t( { 1, 1 }, { 1, 1 }, { 1, 1 } ))
        break;
      p[B] = make_pair(p[F].fst, n - p[F].snd - 1);
      p[R] = make_pair(p[L].fst, n - p[L].snd - 1);
      p[D] = make_pair(n - p[U].fst - 1, p[U].snd);
      for (i = 0; i < 6; i++) {
        auto& d = DELTAS[i];
        //debug << DIRS[i] << ":\n";
        pair<int, int> next[6];
        for (j = 0; j < 6; j++)
          next[j] = make_pair(p[j].fst + d[j].fst, p[j].snd + d[j].snd);
        auto nextPos = make_tuple(next[F], next[L], next[U]);
        //debug << next[F].fst _ next[F].snd _ next[L].fst _
          //next[L].snd _ next[U].fst _ next[U].snd << '\n';
        for (j = 0; j < 6; j++)
          if (grid[j][next[j].fst][next[j].snd] == 'X')
            goto nextDir;
        if (used.find(nextPos) == used.end()) {
          used.emplace(nextPos, make_pair(i, curPos));
          q.push(nextPos);
        }
      nextDir:
        ;
      }
    } while (!q.empty());
    result.clear();
    while (curPos != start) {
      auto p = used[curPos];
      result += DIRS[p.fst];
      curPos = p.snd;
    }
    for_each(result.rbegin(), result.rend(), [ ](char c) { cout << c; } );
    cout << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
