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

struct Person {
  string name;
  vector<Person*> children;
  int dp[1000] = { };

  explicit Person(const string& name): name(name) { }

  void Calc() {
    if (dp[0])
      return;
    dp[0] = (int)children.size();
    for (auto child: children) {
      child->Calc();
      for (int i = 0; i < 999; i++)
        dp[i + 1] += child->dp[i];
    }
  }
};

int n, d;
vector<Person> people;
map<string, Person*> byName;

Person* Register(const string& name) {
  auto it = byName.lower_bound(name);
  if (it != byName.end() && !byName.key_comp()(name, it->first))
    return it->second;
  people.emplace_back(name);
  byName.emplace_hint(it, name, &people.back());
  return &people.back();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tests;
  cin >> tests;
  int i, k;
  string s;
  vector<Person*> result;
  people.reserve(1000);
  bool first = true;
  for (int test = 1; test <= tests; test++) {
    if (first)
      first = false;
    else
      cout << '\n';
    people.clear();
    byName.clear();
    cin >> n >> d;
    for (i = 0; i < n; i++) {
      cin >> s >> k;
      auto p = Register(s);
      while (k--) {
        cin >> s;
        p->children.push_back(Register(s));
      }
    }
    for (auto& person: people)
      person.Calc();
    result.resize(people.size());
    for (i = 0; i < (int)people.size(); i++)
      result[i] = &people[i];
    sort(result.begin(), result.end(),
      [&](const Person* a, const Person* b) {
        return make_pair(-a->dp[d - 1], a->name) < make_pair(-b->dp[d - 1], b->name);
      }
    );
    /*
    for (i = 0; i< (int)result.size(); i++) {
      debug << result[i]->name;
      for (k = 0; k < 1000 && result[i]->dp[k]; k++)
        debug << ' ' << result[i]->dp[k];
      debug << '\n';
    }
    */
    cout << "Tree " << test << ":\n";
    for (i = 0; i < (int)result.size(); i++) {
      if (!result[i]->dp[d - 1] || (i >= 3 && result[i]->dp[d - 1] != result[i - 1]->dp[d - 1]))
        break;
      cout << result[i]->name _ result[i]->dp[d - 1] << '\n';
    }
  }
  TIMESTAMP("end");
  return 0;
}
