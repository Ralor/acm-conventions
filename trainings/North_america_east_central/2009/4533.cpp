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

const char* ALGOS[ ] = {
  "AA+AA++",
  "AA+A+A+",
  "AAA++A+",
  "AAA+A++",
  "AAAA+++",
};

int arr[4], p[4] = { 0, 1, 2, 3 };
deque<int> st;
const char* algo;
set<int> result;

void Search(int pos, int i) {
  if (!algo[pos]) {
    assert(st.size() == 1);
    assert(st[0] <= (int)1e8);
    assert(st[0] >= (int)-1e8);
    result.insert(st[0]);
  } else if (algo[pos] == 'A') {
    st.push_back(arr[p[i]]);
    Search(pos + 1, i + 1);
    st.pop_back();
  } else {
    int a = st.end()[-1];
    int b = st.end()[-2];
    st.pop_back();
    st.back() = a + b;
    Search(pos + 1, i);
    st.back() = a - b;
    Search(pos + 1, i);
    st.back() = a * b;
    Search(pos + 1, i);
    if (b && !(a % b)) {
      st.back() = a / b;
      Search(pos + 1, i);
    }
    st.back() = b;
    st.push_back(a);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int caseNum = 1;
  while (cin >> arr[0] >> arr[1] >> arr[2] >> arr[3], arr[0]) {
    debug << arr[0] _ arr[1] _ arr[2] _ arr[3] << '\n';
    result.clear();
    do
      for (auto a: ALGOS) {
        algo = a;
        Search(0, 0);
      }
    while (next_permutation(p, p + 4));
    debug << "Searched\n";
    int best = 0, bestPos = 0, cur = 0;
    int prev = INT_MAX - 1;
    for (int x: result) {
      debug << x << ' ';
      if (x == prev + 1)
        cur++;
      else
        cur = 1;
      if (cur >= best) {
        best = cur;
        bestPos = x - cur + 1;
      }
      prev = x;
    }
    debug << '\n';
    cout << "Case " << caseNum++ << ": " << bestPos << " to " << bestPos + best - 1 << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
