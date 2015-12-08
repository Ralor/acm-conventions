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

const struct {
  int a, c, d, b;
} DELTAS[ ] = {
  { 0, 0, 0, 4 },
  { 0, 1, 0, 3 },
  { 0, 2, 0, 2 },
  { 0, 3, 0, 1 },
  { 1, 1, 3, 2 },
  { 1, 2, 3, 5 },
  { 1, 3, 1, 4 },
  { 2, 1, 3, 3 },
  { 2, 2, 0, 5 },
  { 3, 1, 3, 4 },
  { 3, 2, 1, 5 },
  { 4, 2, 2, 5 },
};

struct Node {
  char value;
  int dir;
  pair<char, int> adj[4];
} nodes[6];

void Set(int a, int b, int c, int d) {
  nodes[a].adj[(c - nodes[a].dir + 4) & 0x3] = { nodes[b].value, (d - nodes[b].dir + 4) & 0x3 };
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tests;
  cin >> tests;
  int i;
  char cube[13];
  for (int ci = 1; ci <= tests; ci++) {
    cin >> cube;
    for (i = 0; i < 6; i++) {
      nodes[i].value = cube[i << 1];
      nodes[i].dir = cube[i << 1 | 0x1] - '1';
    }
    for (const auto& d: DELTAS) {
      Set(d.a, d.b, d.c, d.d);
      Set(d.b, d.a, d.d, d.c);
    }
    for (i = 0; i < 6; i++) {
      debug << i << ": " << nodes[i].value << " (" << nodes[i].dir << "):\n";
      for (auto p: nodes[i].adj)
        debug << "  " << p.fst _ p.snd << '\n';
    }
    debug << '\n';
    int count = 0;
    int mask = 0x00;
    for (int q = 1; q < 1 << 5; q <<= 1) {
      cin >> cube;
      char a = cube[0], b = cube[2], c = cube[4];
      int ad = cube[1] - '1', bd = cube[3] - '1', cd = cube[5] - '1';
      for (i = 0; i < 6; i++) {
        bool ok = nodes[i].value == a;
        ok = ok && nodes[i].adj[(4 - ad) & 0x3] == make_pair(c, 3 - cd);
        ok = ok && nodes[i].adj[3 - ad] == make_pair(b, (4 - bd) & 0x3);
        if (ok) {
          count++;
          mask |= q;
          break;
        }
      }
    }
    cout << ci _ count;
    for (i = 1; i < 1 << 5; i <<= 1)
      cout << (mask & i ? " Y" : " N");
    cout << '\n';
    debug << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
