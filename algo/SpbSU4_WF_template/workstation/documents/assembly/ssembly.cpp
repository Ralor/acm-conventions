#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <list>
#include <set>
#include <map>

using namespace std;

#define TASKNAME "ssembly"
#define pb push_back
#define mp make_pair
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif
#define TIMESTAMP(msg) eprintf("["msg"] Time=%.3lfs\n", clock() * 1.0 / CLOCKS_PER_SEC)
#define sz(x) ((int)(x).size())

typedef long double ld;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

const int inf = 1e9;
const double eps = 1e-9;

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif

  TIMESTAMP("end");
  return 0;
}

