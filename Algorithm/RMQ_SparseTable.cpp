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

template<typename T>
class SparseTable {

public:
  SparseTable(const T undef) : undef(undef) {}
  SparseTable(const T undef, const vector<T>& arr) : undef(undef) {    
    assign(arr);    
  }

  int rmq(int l, int r) {
    if( ST.empty() || 
        l < 0 || r < 0 || 
        l >= sz(ST.front()) || r >= sz(ST.front()) || 
        l > r )
      return undef;
    int k = my_log2(r-l+1);
    return min(get(k,l), get(k,r - (1 << k) + 1));
  }

  void assign(const vector<T>& arr) {
    int k = my_log2(sz(arr));
    ST.clear();
    for(int i = 0; i <= k; i++)
      ST.push_back(vector<T>(sz(arr) - (1<<i) + 1, undef));

    if( !ST.empty() )
      ST[0].assign(all(arr));
  }

private:

  int get(int k, int i) {
    if( ST[k][i] == undef )
      return ST[k][i] = min( get(k-1,i), get( k-1, i+(1<<(k-1)) ) );
    return ST[k][i];
  }

  // (int)(log(n)/log(2) + eps)
  int my_log2(int n) const {
    int k = 0;
    while( (1 << k) < n ) ++k;
    return --k;
  }

  T undef;  
  vector< vector<T> > ST;
};

int main() {
  //freopen(TASK ".in", "r", stdin);
  //freopen(TASK ".out", "w", stdout);
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);  

  int n; cin >> n;
  vector<int> arr(n);
  for(int i = 0; i < n; i++)
    cin >> arr[i];

  SparseTable<int> ST(-2*inf, arr);

  int m; cin >> m;
  for(int i = 0; i < m; i++) {
    int l,r; cin >> l >> r;
    cout << ST.rmq(l,r) << "\n";
  }

  return 0;
}
