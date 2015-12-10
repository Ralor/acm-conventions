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

#define TASKNAME "pirate"
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

const int inf = 1e9 + 100;
const double eps = 1e-9;

class Dsu {
  vi par, ss;
  
  int get(int x) { return par[x] == x ? x : par[x] = get(par[x]); }
  public:
  Dsu(int n) : par(n), ss(n, 1) {
    for (int i = 0; i < n; i++)
      par[i] = i;
  }
  int merge(int a, int b) {
    a = get(a); b = get(b);
    if (a == b) return ss[a];
    if (ss[a] > ss[b]) swap(a, b);
    par[a] = b;
    ss[b] += ss[a];
    return ss[b];
  }
};

vi solve(const vi &vals) {  
  const int n = sz(vals);
  vector<pii> all(n);
  for (int i = 0; i < n; i++)
    all[i] = mp(vals[i], i);
  sort(all.begin(), all.end());
  reverse(all.begin(), all.end());
  
  Dsu s(n);
  vi ans(n + 1, 0);
  int maxsz = 1;
  for (int i = 0; i < sz(all); i++) {
    int x = all[i].second;
    if (x > 0 && vals[x] <= vals[x - 1]) {
      maxsz = max(maxsz, s.merge(x - 1, x));
    }
    if (x + 1 < n && vals[x] <= vals[x + 1]) {
      maxsz = max(maxsz, s.merge(x + 1, x));
    }
    ans[maxsz] = max(ans[maxsz], all[i].first);
  }
  for (int i = sz(ans) - 2; i >= 0; i--)
    ans[i] = max(ans[i], ans[i + 1]);
    
  for (int cw = 1; cw <= n; cw++) {
    int best = 0;
    for (int i = 0; i + cw <= n; i++) {
      int myv = 2e9;
      for (int i2 = 0; i2 < cw ;i2++)
        myv = min(myv, vals[i + i2]);
      best = max(best, myv);
    }
    assert(ans[cw] == best);
  }
  return ans;
}

const int MAXN = 510;
int h, w;
int f[MAXN][MAXN];

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif
  
  int a, b;
  while (scanf("%d%d%d%d", &a, &b, &h, &w) == 4) {
    for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
      scanf("%d", &f[y][x]);
      
    ll ans = 0;
    for (int y1 = 0; y1 < h; y1++) {
      vi dns(w, inf);
      for (int y2 = y1; y2 < h; y2++) {
        int ch = y2 - y1 + 1;
        for (int x = 0; x < w; x++)
          dns[x] = min(dns[x], f[y2][x]);
          
        vi vals = solve(dns);
        for (int cw = 1; cw <= w; cw++) {
          if (vals[cw] < 1) continue;
          
          if ( (ch <= a && cw <= b) ||
               (ch <= b && cw <= a)) {
            ll den = w * h - cw * ch;
            assert(den > 0);
            ll cz = (ll(vals[cw]) * w * h - 1) / den;
            ll cans = ll(cw) * ch * cz;
//            eprintf("y1=%d, y2=%d, cw=%d, ch=%d, cz=%lld\n");
            ans = max(ans, cans);
          }
        }
      }
    }
    printf("%lld\n", ans);
  }

  TIMESTAMP("end");
  return 0;
}

