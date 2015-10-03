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
#define ASSERT_TL(cond) if (cond) { } else while (true) { }

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

struct Entry {
  Entry* parent = nullptr;
  const string* s = nullptr;
  char c;

  Entry(Entry* parent, char c): parent(parent), c(c) { }
  explicit Entry(const string* s): s(s), c('\0') { }

  char Print() const {
    static string st;//stack<char>
    st.clear();
    auto e = this;
    while (e->parent) {
      st += e->c;
      e = e->parent;
    }
    assert(!!e->s);
    char result = (*e->s)[0];
    cout << *e->s;
    for_each(st.rbegin(), st.rend(), [ ](char c) { cout << c; } );
    return result;
  }
};

deque<Entry> dict;
vector<string> strings;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string code;
  int caseNum = 1;
  while (cin >> code, code != "0") {
    int i, n;
    cin >> n;
    dict.clear();
    strings.clear();
    strings.resize(n);
    int len = 1, next = 10;
    for (i = 0; i < n; i++) {
      cin >> strings[i];
      dict.emplace_back(&strings[i]);
      assert((int)dict.size() == i + 1);
      if (i + 1 == next) {
        len++;
        next *= 10;
      }
    }
    int pos = 0;
    cout << "Case " << caseNum++ << ": ";
    while (pos < (int)code.length()) {
      assert(pos + len <= (int)code.length());
      int index = 0;
      for (i = 0; i < len; i++)
        index = index * 10 + code[pos + i] - '0';
      ASSERT_TL(index < (int)dict.size() - !!pos);
      char first = dict[index].Print();
      if (pos)
        dict.back().c = first;
      pos += len;
      if ((int)dict.size() == next) {
        len++;
        next *= 10;
      }
      dict.emplace_back(&dict[index], '\0');
    }
    cout << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
