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

#define TASKNAME "congest"
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

class Solver {
  struct Edge {
    int b, fl, w, revi;
  };
  vector<vector<Edge> > es;
  vi was;
  int wver;
  
  int en;
  
  bool dfs(int v) {
//    assert(0 <= v && v < sz(es));
//    assert(sz(es) == sz(was));
    if (v == en) return true;
    if (was[v] >= wver) return false;
    was[v] = wver;
    for (int i = 0; i < sz(es[v]); i++) if (es[v][i].fl < es[v][i].w) {
      int b = es[v][i].b;
//      assert(0 <= b && b < sz(es));
      
      if (dfs(es[v][i].b)) {
        es[v][i].fl++;
        int bi = es[v][i].revi;
//        assert(0 <= bi && bi < sz(es[b]));
        es[b][bi].fl--;
        return true;
      }
    }
    return false;
  }
  
  public:
  Solver(int n) : es(n), was(n, 0), wver(0) {}
  void adde(int a, int b, int w) {
    assert(0 <= a && a < sz(es));
    assert(0 <= b && b < sz(es));
    int aid = sz(es[a]);
    int bid = sz(es[b]);
    
    Edge e;
    e.b = b; e.fl = 0; e.w = w; e.revi = bid;
    es[a].pb(e);
    
    e.b = a; e.fl = 0; e.w = 0; e.revi = aid;
    es[b].pb(e);
  }
  void reset() {
    for (int i = 0; i < sz(es); i++)
    for (int i2 = 0; i2 < sz(es[i]); i2++)
      es[i][i2].fl = 0;
  }
  bool goFrom(int v, int _en) {
    assert(0 <= v && v < sz(es));
    assert(0 <= _en && _en < sz(es));
    en = _en;
    wver++;
    return dfs(v);   
  }
};

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif
  
  int n, m, c;
  while (scanf("%d%d%d", &n, &m, &c) == 3) {
    vvi es(n), esw(n);
    for (int i = 0; i < m; i++) {
      int a, b, w;
      scanf("%d%d%d", &a, &b, &w);
      a--, b--;
      es[a].pb(b); esw[a].pb(w);
      es[b].pb(a); esw[b].pb(w);
    }
    vi d(n, inf);
    priority_queue<pii> q;
    d[0] = 0;
    q.push(mp(-d[0], 0));
    while (!q.empty()) {
      int cd = -q.top().first;
      int v = q.top().second;
      q.pop();
      
      if (d[v] != cd) continue;
      for (int i = 0; i < sz(es[v]); i++) {
        int b = es[v][i];
        int nd = cd + esw[v][i];
        if (nd >= d[b]) continue;
        d[b] = nd;
        q.push(mp(-d[b], b));
      }
    }
    
    Solver s(n);
    for (int i = 0; i < n; i++)
    for (int i2 = 0; i2 < sz(es[i]); i2++) {
      int b = es[i][i2];
      if (d[b] == d[i] + esw[i][i2]) {
        s.adde(b, i, 1);
//        eprintf("edge: %d-->%d\n", b + 1, i + 1);
      }
    }
    map<int, vi> cnts;
    for (int i = 0; i < c; i++) {
      int x;
      scanf("%d", &x), x--;
      cnts[d[x]].pb(x);
    }
    int ans = 0;
    for (auto it = cnts.begin(); it != cnts.end(); it++) {
      s.reset();
//      eprintf("reset\n");
      const vi &cur = it->second;
      for (int i = 0; i < sz(cur); i++) {
//        eprintf("try %d\n", cur[i] + 1);
        if (s.goFrom(cur[i], 0)) {
          ans++;
        }
      }
    }
    printf("%d\n", ans);
//    break;
  }

  TIMESTAMP("end");
  return 0;
}

