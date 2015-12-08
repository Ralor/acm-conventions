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



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tests;
  cin >> tests;
  vector<int> a, result;
  for (int ci = 1; ci <= tests; ci++) {
    int n;
    cin >> n;
    a.resize(n);
    for (int& x: a)
      cin >> x;
    result.clear();
    int left = n;
    while (left > 1) {
      int index = max_element(a.begin(), a.begin() + left,
        [ ](int a, int b) {
          return abs(a) < abs(b);
        }
      ) - a.begin();
      if (index != left - 1 || a[index] < 0) {
        if (index) {
          result.push_back(index + 1);
          reverse(a.begin(), a.begin() + index + 1);
          for (int i = 0; i <= index; i++)
            a[i] = -a[i];
        }
        if (a[0] > 0) {
          result.push_back(1);
          a[0] = -a[0];
        }
        result.push_back(left);
        reverse(a.begin(), a.begin() + left);
        for (int i = 0; i < left; i++)
          a[i] = -a[i];
      }
      left--;
    }
    if (a[0] < 0) {
      result.push_back(1);
      a[0] = -a[0];
    }
    assert((int)result.size() <= 3 * n - 2);
    assert(is_sorted(a.begin(), a.end()));
    for (int i = 0; i < n; i++)
      assert(a[i] > 0);
    cout << ci _ result.size();
    for (int x: result)
      cout << ' ' << x;
    cout << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
