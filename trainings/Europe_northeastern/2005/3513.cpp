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

enum {
  ADD = 0,
  SUB = 0,
  MUL = 1,
  DIV = 1,
  VAR = 2,
};

enum {
  REPLACE_ADD = 0x1,
  REPLACE_MUL = 0x2,
};

uchar mask;

struct Expr {
  int prio;
  char c;
  Expr* a;
  Expr* b;
  bool parenthized = false;

  Expr(int prio, char c, Expr* a = nullptr, Expr* b = nullptr): prio(prio), c(c), a(a), b(b) { }

  void Print() const {
    if (a) {
      uchar temp = mask;
      if (a->prio < prio) {
        mask = 0x0;
        cout << '(';
      }
      a->Print();
      if (a->prio < prio)
        cout << ')';
      mask = temp;
    }
    if (strchr("+-", c) && mask & REPLACE_ADD)
      cout << (c == '+' ? '-' : '+');
    else if (strchr("*/", c) && mask & REPLACE_MUL)
      cout << (c == '*' ? '/' : '*');
    else
      cout << c;
    if (b) {
      uchar temp = mask;
      if (b->parenthized) {
        if (c == '-')
          mask ^= REPLACE_ADD;
        else if (c != '+') {
          if (b->prio < MUL)
            mask = 0x0;
          else if (c == '/')
            mask ^= REPLACE_MUL;
        }
      }
      if (b->prio < prio)
        cout << '(';
      b->Print();
      if (b->prio < prio)
        cout << ')';
      mask = temp;
    }
  }
};

string s;
int pos;
deque<Expr> nodes;

Expr* ParseExpr();

Expr* ParseFactor() {
  if (s[pos] == '(') {
    pos++;
    auto e = ParseExpr();
    e->parenthized = true;
    assert(s[pos] == ')');
    pos++;
    return e;
  }
  assert(islower(s[pos]));
  nodes.emplace_back(VAR, s[pos]);
  pos++;
  return &nodes.back();
}

Expr* ParseTerm() {
  auto e = ParseFactor();
  while (pos < (int)s.length() && strchr("*/", s[pos])) {
    char c = s[pos++];
    nodes.emplace_back(c == '*' ? MUL : DIV, c, e, ParseFactor());
    e = &nodes.back();
  }
  return e;
}

Expr* ParseExpr() {
  auto e = ParseTerm();
  while (pos < (int)s.length() && strchr("+-", s[pos])) {
    char c = s[pos++];
    nodes.emplace_back(c == '+' ? ADD : SUB, c, e, ParseTerm());
    e = &nodes.back();
  }
  return e;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while (cin >> s) {
    nodes.clear();
    pos = 0;
    mask = 0x0;
    ParseExpr()->Print();
    cout << '\n';
    assert(pos == (int)s.length());
  }
  TIMESTAMP("end");
  return 0;
}
