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

//enum { S, P };

int n, m;
int size;
vector<pair<int, int>> numbers;//<sum, product>
bitset<40000> bad;
unsigned temp[40001];
vector<pair<int, int>> result;

void Process(bool first) {
  int pair<int, int>::*member = first ? &pair<int, int>::first : &pair<int, int>::second;
  memset(temp, 0xFF, sizeof temp);
  for (int i = 0; i < size; i++)
    if (!bad[i]) {
      if (!~temp[numbers[i].*member])
        temp[numbers[i].*member] = i;
      else
        temp[numbers[i].*member] = 0x7FFFFFFE;
    }
  debug << "\nRemoving:\n";
  for (int i = 0; i < 40001; i++)
    if (temp[i] < 0x7FFFFFFE) {
      int a = temp[i] / n + 1, b = temp[i] % n + 1;
      if (a <= b) {
        bad[temp[i]] = true;
        debug << a _ b;
        if (first)
          debug << " *" << a + b << "* " << a * b << '\n';
        else
          debug << ' ' << a + b << " *" << a * b << "*\n";
      }
    }
}

void DebugOut() {
  result.clear();
  for (int i = 0; i < size; i++)
    if (!bad[i] && i / n <= i % n)
      result.emplace_back(i / n + 1, i % n + 1);
  debug << "\nSub:\n";
  cout << result.size() << '\n';
  for (auto& p: result)
    cout << p.fst _ p.snd _ p.fst + p.snd _ p.fst * p.snd << '\n';
  debug << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i, j, k;
  while (cin >> n >> m) {
    size = n * n;
    numbers.resize(size);
    bad.reset();
    i = j = 1;
    for (k = 0; k < size; k++) {
      if (i <= j)
        numbers[k] = make_pair(i + j, i * j);
      else
        bad[k] = true;
      if (j == n) {
        j = 1;
        i++;
      } else
        j++;
    }
    bool flag = true;
    while (m--) {
      DebugOut();
      Process(flag);
      flag = !flag;
    }
    result.clear();
    for (i = 0; i < n * n; i++)
      if (!bad[i] && i / n <= i % n)
        result.emplace_back(i / n + 1, i % n + 1);
    debug << "\nResult:\n";
    cout << result.size() << '\n';
    for (auto& p: result)
      cout << p.fst _ p.snd << '\n';
    debug << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
