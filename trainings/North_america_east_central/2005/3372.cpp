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

string p, t;
int nums[150];
int dp[151][150][150];//[pPos][tPos][lastNum]

int Dyn(int i, int j, int last) {
  if (j >= (int)t.length())
    return i == (int)p.length();
  if (~dp[i][j][last])
    return dp[i][j][last];
  bool canPlace = i < (int)p.length() && p[i] == t[j];
  bool mustPlace = nums[j] > 0 && last != nums[j];
  int result = 0;
  if (canPlace)
    result += Dyn(i + 1, j + 1, abs(nums[j]));
  if (!mustPlace)
    result += Dyn(i, j + 1, last);
  return (dp[i][j][last] = result);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int k;
  string s, text;
  set<string> banned;
  while (cin >> k, k) {
    banned.clear();
    while (k--) {
      cin >> s;
      banned.insert(s);
    }
    while (cin >> s >> ws, getline(cin, text), s != "LAST" || text != "CASE") {
      cout << s;
      istringstream ss(text);
      p.clear();
      t.clear();
      for (char c: s)
        p += (char)tolower(c);
      int curWord = 1;
      while (ss >> s) {
        if (banned.find(s) != banned.end())
          continue;
        for (char c: s) {
          nums[t.length()] = -curWord;
          t += c;
        }
        nums[t.length() - 1] = curWord++;
      }
      memset(dp, 0xFF, sizeof dp);
      int result = Dyn(0, 0, 0);
      if (result)
        cout << " can be formed in " << result << " ways\n";
      else
        cout << " is not a valid abbreviation\n";
    }
  }
  TIMESTAMP("end");
  return 0;
}
