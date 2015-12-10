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

#define TASKNAME "low"
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

int n, k;
vi as;
bool check(int maxDiff) {
  int rem = 0;
  int pairsRem = n;
  for (int i = 0; i < sz(as); i++) {
    if (pairsRem > 0 && i + 1 < sz(as)) {
      int curDiff = as[i + 1] - as[i];
      if (curDiff <= maxDiff) {
        pairsRem--;
        rem += 2 * k - 2;
        i++;
        continue;
      }
    }
    rem--;
    if (rem < 0) return false;
  }
  assert(pairsRem == 0);
  assert(rem == 0);
  return true;
}

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif

  while (scanf("%d%d", &n, &k) == 2) {
    as = vi(2 * n * k);
    for (int i = 0; i < sz(as); i++)
      scanf("%d", &as[i]);
    sort(as.begin(), as.end());
      
    int L = -1, R = 1e9 + 100;
    assert(check(R));
    while (L + 1 < R) {
      int M = (L + R) / 2;
      if (check(M)) R = M;
      else L = M;
    }
    printf("%d\n", R);
  }
  TIMESTAMP("end");
  return 0;
}

