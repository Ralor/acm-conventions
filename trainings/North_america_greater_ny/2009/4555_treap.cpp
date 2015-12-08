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

struct Node;

extern vector<Node> nodes;

struct Node {
  int key, prio;
  int size = 1;
  Node* left = nullptr;
  Node* right = nullptr;

  explicit Node(int key): key(key), prio(rand() << 15 ^ rand()) { }

  static int GetSize(Node* t) {
    return t ? t->size : 0;
  }

  static void Recalc(Node* t) {
    if (t)
      t->size = GetSize(t->left) + GetSize(t->right) + 1;
  }

  static void Split(Node* t, int x, Node*& l, Node*& r) {
    if (!t)
      l = r = nullptr;
    else {
      if (x < t->key) {
        Split(t->left, x, l, t->left);
        r = t;
      } else {
        Split(t->right, x, t->right, r);
        l = t;
      }
      Recalc(l);
      Recalc(r);
    }
  }

  static void Merge(Node* l, Node* r, Node*& t) {
    if (!l)
      t = r;
    else if (!r)
      t = l;
    else {
      if (l->prio < r->prio) {
        Merge(l, r->left, r->left);
        Recalc(r->left);
        t = r;
      } else {
        Merge(l->right, r, l->right);
        Recalc(l->right);
        t = l;
      }
      Recalc(t);
    }
  }

  int GetNth(int n) {
    auto t = this;
    while (true) {
      int size = (int)GetSize(t->left);
      if (n == size)
        return t->key;
      if (n < size)
        t = t->left;
      else {
        n -= size + 1;
        t = t->right;
      }
    }
  }

  static void Insert(Node*& t, int x) {
    Node* r;
    Split(t, x, t, r);
    nodes.emplace_back(x);
    Merge(t, &nodes.back(), t);
    Merge(t, r, t);
  }
};

vector<Node> nodes;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
# ifndef LOCAL_DEBUG
    srand((unsigned)time(nullptr));
# endif
  int tests;
  cin >> tests;
  while (tests--) {
    int ci, n;
    cin >> ci >> n;
    cout << ci _ (n >> 1) + 1 << '\n';
    nodes.clear();
    nodes.reserve(n);
    Node* root = nullptr;
    int output = 0;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      Node::Insert(root, x);
      if (!(i & 0x1)) {
        if (output)
          cout << ' ';
        cout << root->GetNth(i >> 1);
        if (++output == 10) {
          cout << '\n';
          output = 0;
        }
      }
    }
    if (output)
      cout << '\n';
    debug << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
