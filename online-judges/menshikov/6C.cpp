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

const int days[] = {-1, 31,29,31,30,31,30,31,31,30,31,30,31};
int dp[32][13];
int rec(int day, int month) {
  if( day == 31 && month == 12 )
    return 0;
  //debug << day << ':' << month << ':' << dp[day][month] << '\n';
  if( dp[day][month] != -1 )
    return dp[day][month];

  int result = 1;
  if( day+1 <= days[month] )
    result &= !rec(day+1,month);
  if( day+2 <= days[month] )
    result &= !rec(day+2, month);
  if( month < 12 && day <= days[month+1] )
    result &= !rec(day, month+1);
  if( month < 11 && day <= days[month+2] )
    result &= !rec(day, month+2);
  return dp[day][month] = result;
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

  int day, month;
  memset(dp, -1, sizeof dp);
  while( cin >> day >> month ) {
    cout << ((rec(day, month)) ? '2' : '1') << "\n";
  }


  return 0;
}
