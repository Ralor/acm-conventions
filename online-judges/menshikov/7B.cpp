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

const int radix = 1000*1000*1000;

void add(vi& a, const vi& b) {
  int len = max(sz(a),sz(b));
  for(int i = 0, carry = 0; i < len || carry; i++) {
    if( i == sz(a) )
      a.push_back(0);
    a[i] += carry + ((i<sz(b))? b[i] : 0);
    carry = (a[i] > radix);
    if( carry ) a[i] -= radix;
  }
}

string s;
int jump_ok[111];
vi dp[111]; // dp[pos];

vi rec(int pos) {
  if( dp[pos][0] != -1 )
    return dp[pos];
  vi result;
  add(result, rec(pos+1));
  if( pos+2 < sz(s) && jump_ok[pos] )
    add(result, rec(pos+2));
  return dp[pos] = result;
}

int main() {
  //freopen(TASK ".in", "r", stdin);
  //freopen(TASK ".out", "w", stdout);
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);


  while( cin >> s ) {
    for(int i = 0; i < 111; i++)
      dp[i] = vi(1,-1);
    memset(jump_ok,0,sizeof jump_ok);
    for(int i = 0; i < sz(s)-1; i++) {
      jump_ok[i] = 1;
      jump_ok[i] &= (s[i]-'0') * 10 + (s[i+1]-'0') <= 33;
      jump_ok[i] &= s[i] != '0';
    }
    if( sz(s) <= 1 )
      cout << 1 << "\n";
    else {
      dp[sz(s)-1] = vi(1,1);
      dp[sz(s)-2] = jump_ok[sz(s)-2] ? vi(1,2) : vi(1,1);
      vi res = rec(0);
      cout << ((res.empty()) ? 0 : res.back());
      for(int i = sz(res)-2;  i >= 0; --i)
        cout << setw(9) << setfill('0') << res[i];
      cout << "\n";
    }
  }


  return 0;
}
