#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <fstream>
#include <bitset>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifndef _DEBUG
# undef VERBOSE
#endif
#ifdef NDEBUG
#define VERBOSE
#endif

#define eps 1e-8
#define inf (1000 * 1000 * 1000)
#define linf (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x) ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x) int((x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define mp make_pair
#define FOR(i, n) for(int (i) = 0; (i) < (n); ++(i))
#define FORN(i, n) for(int (i) = 1; (i) <= (n); ++(i))
#define REP(i,from,to) for(int (i) = (from); (i) <= (to); ++(i))
#define RREP(i,from,to) for(int (i) = (from); (i) >= (to); --(i))
#define FOREACH(iter, cont) for(__typeof(cont)::iterator it = (cont).begin(); (it) != (cont).end(); ++(it))


using namespace std;

typedef unsigned uint;
typedef long long llong;
typedef unsigned long long ullong;
typedef long double ldouble;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
struct debug_t {
  template <typename T>
  debug_t& operator<<(const T& value) {
# ifdef VERBOSE
    cout << value;
# endif
    return *this;
  }
} debug;



int main() {
  //freopen(TASK ".in", "r", stdin);
  //freopen(TASK ".out", "w", stdout);
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  while( cin >> n ) {
    vi a(n);
    FOR(i, n)
      cin >> a[i];
    sort(all(a));

    if( a[0] != 1 ) {
      cout << "1" << "\n";
    } else {
      llong s = 1;
      REP(i,1,n-1) {
        if( a[i] > s+1 )
          break;
        s += a[i];
      }
      cout << s+1 << "\n";
    }
  }

  return 0;
}
