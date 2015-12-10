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

vector<int> a;

struct Node {
  int id;
  int teamId;
  int time;
  Node* left = nullptr;
  Node* right = nullptr;

  Node(int id, int teamId): id(id), teamId(teamId) { }

  void Traverse() {
    if (left)
      left->Traverse();
    time = (int)a.size();
    a.push_back(id);
    if (right)
      right->Traverse();
  }
};

struct SegTree {
  int t[4 << 19];

  static int L(int i) { return i << 1 | 0x1; }
  static int R(int i) { return (i << 1) + 2; }

  void Build(int i, int left, int right) {
    if (left + 1 == right)
      t[i] = a[left];
    else {
      int mid = (left + right) >> 1;
      Build(L(i), left, mid);
      Build(R(i), mid, right);
      t[i] = max(t[L(i)], t[R(i)]);
    }
  }

  int GetMax(int i, int left, int right, int lq, int rq) {
    if (lq >= rq)
      return INT_MIN;
    if (left + 1 == right)
      return t[i];
    int mid = (left + right) >> 1;
    return max(
      GetMax(L(i), left, mid, lq, min(mid, rq)),
      GetMax(R(i), mid, right, max(lq, mid), rq)
    );
  }
};

map<string, int> teams;
vector<Node> nodes;
SegTree sgt;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  #ifndef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int i, n;
  string s;
  while (cin >> n) {
    teams.clear();
    nodes.clear();
    nodes.reserve((1 << (n + 1)) - 1);
    for (i = 0; i < 1 << n; i++) {
      cin >> s;
      teams[s] = i;
      nodes.emplace_back(i, i);
    }
    cin >> s;
    int x = 0, y = 1;
    for (char c: s) {
      nodes.emplace_back((int)nodes.size(), nodes[c == 'W' ? x : y].teamId);
      nodes.back().left = &nodes[x];
      nodes.back().right = &nodes[y];
      x += 2;
      y += 2;
    }
    for (auto& node: nodes)
      debug << node.teamId << ' ';
    debug << '\n';
    a.clear();
    nodes.back().Traverse();
    sgt.Build(0, 0, (int)a.size());
    for (int x: a)
      debug << x << ' ';
    debug << '\n';
    int q;
    cin >> q;
    while (q--) {
      cin >> s;
      int x = teams[s];
      cin >> s;
      int y = teams[s];
      assert(x != y);
      int lq = nodes[x].time, rq = nodes[y].time;
      if (lq > rq)
        swap(lq, rq);
      debug << lq _ rq << '\n';
      debug << a[lq] _ a[rq] << '\n';
      int p = sgt.GetMax(0, 0, (int)a.size(), lq, rq + 1);
      int winner = nodes[p].teamId;
      debug << p _ winner << '\n';
      if (winner == x)
        cout << "Win\n";
      else if (winner == y)
        cout << "Lose\n";
      else
        cout << "Unknown\n";
    }
    debug << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
