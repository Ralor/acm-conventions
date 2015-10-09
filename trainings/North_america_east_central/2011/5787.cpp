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

llong Gcd(llong a, llong b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

struct Fraction {
  llong num, denom;

  Fraction() { }

  /*implicit*/ Fraction(llong a, llong b = 1): num(a), denom(b) {
    Reduce();
  }

  void Reduce() {
    if (num && denom) {
      llong g = Gcd(num, denom);
      num /= g;
      denom /= g;
    }
  }

  Fraction operator*(const Fraction& rhs) const {
    return { num * rhs.num, denom * rhs.denom };
  }

  Fraction operator/(const Fraction& rhs) const {
    return { num * rhs.denom, denom * rhs.num };
  }

  Fraction operator+(const Fraction& rhs) const {
    assert(denom && rhs.denom);
    llong d = denom / Gcd(denom, rhs.denom) * rhs.denom;
    return { num * (d / denom) + rhs.num * (d / rhs.denom), d };
  }
};

struct Node;

struct Edge {
  llong length = 0;
  Node* node = nullptr;

  Edge() { }
  Edge(llong len, Node* node): length(len), node(node) { }
};

struct Node {
  Node* parent = nullptr;
  Edge left, right;
  Fraction result;

  void Calc() {
    if (!left.node)
      assert(!right.node);
    else {
      assert(!!right.node);
      Fraction k(left.length, right.length);
      left.node->result = result / (Fraction(1) + k);
      right.node->result = left.node->result * k;
      left.node->Calc();
      right.node->Calc();
    }
  }

  void Print() {
    debug << '(' << left.length;
    if (left.node)
      left.node->Print();
    debug << ")(" << right.length;
    if (right.node)
      right.node->Print();
    debug << ')';
  }
};

int n;
deque<Node> nodes;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i;
  int caseNum = 1;
  while (cin >> n, n) {
    nodes.clear();
    nodes.resize(n);
    for (i = 0; i < n; i++) {
      char tl, tr;
      int dl, dr, nl, nr;
      cin >> dl >> dr >> tl >> tr >> nl >> nr;
      nl--;
      nr--;
      if (tl == 'W') {
        nl += n;
        if (nl >= (int)nodes.size())
          nodes.resize(nl + 1);
      }
      nodes[i].left = { dl, &nodes[nl] };
      nodes[nl].parent = &nodes[i];
      if (tr == 'W') {
        nr += n;
        if (nr >= (int)nodes.size())
          nodes.resize(nr + 1);
      }
      nodes[i].right = { dr, &nodes[nr] };
      nodes[nr].parent = &nodes[i];
    }
    int id;
    llong weight;
    cin >> id >> weight;
    id--;
    id += n;
    auto node = &nodes[id];
    node->result = weight;
    while (auto p = node->parent) {
      auto e1 = node == p->left.node ? p->left : p->right;
      auto e2 = node == p->left.node ? p->right : p->left;
      assert(node == e1.node);
      e2.node->result = node->result * Fraction(e1.length, e2.length);
      e2.node->Calc();
      p->result = node->result + e2.node->result;
      node = p;
    }
    llong a = 1;
    Fraction s = 0;
    for (i = n; i < (int)nodes.size(); i++) {
      a = a / Gcd(a, nodes[i].result.denom) * nodes[i].result.denom;
      debug << nodes[i].result.num << '/' << nodes[i].result.denom << '\n';
      s = s + nodes[i].result;
    }
    debug << "a = " << a << '\n';
    for (i = n; i < (int)nodes.size(); i++) {
      nodes[i].result.num *= a;
      nodes[i].result.Reduce();
    }
    llong b = nodes[n].result.num;
    for (i = n + 1; i < (int)nodes.size(); i++)
      b = Gcd(b, nodes[i].result.num);
    llong sum = 0;
    for (i = n; i < (int)nodes.size(); i++)
      sum += nodes[i].result.num /= b;
    debug << "sum = " << sum << '\n';
    debug << "weight = " << weight << '\n';
    debug << "nodes[id].result = " << nodes[id].result.num << '/' << nodes[id].result.denom << '\n';
    sum *= (nodes[id].result.num + weight - 1) / nodes[id].result.num;
    cout << "Case " << caseNum++ << ": " << sum << '\n';
    /*
    debug << "s = " << s.num << '/' << s.denom << '\n';
    debug << "last: " << node->result.num << '/' << node->result.denom << '\n';
    int sum = 0;
    for (i = n; i < (int)nodes.size(); i++)
      sum += a / nodes[i].result.denom * nodes[i].result.num;
    cout << "Case " << caseNum++ << ": " << sum << '\n';
    */
  }
  TIMESTAMP("end");
  return 0;
}
