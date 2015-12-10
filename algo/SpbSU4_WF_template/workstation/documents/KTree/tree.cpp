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

#define TASKNAME "tree"
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

const int MAXN = 30;

const int PRE = 0;
const int IN = 1;
const int POST = 2;

struct Tree {
  string s[3];
  
  Tree() {}
  Tree(const Tree &l, const Tree &r, const char &root) {
    s[0] = root + l.s[0] + r.s[0];
    s[1] = l.s[1] + root + r.s[1];
    s[2] = l.s[2] + r.s[2] + root;
  }
  bool operator<(const Tree &t2) const {
    for (int t = 0; t < 3; t++)
      if (s[t] != t2.s[t]) return s[t] < t2.s[t];
    return false;
  }
  int getMask() const {
    int res = 0;
    for (int i = 0; i < sz(s[0]); i++)
      res |= 1 << (s[0][i] - 'A');
    return res;
  }
};

bool check_ord(const pii &a, const pii &b) {
  if (a.first < 0 || b.first < 0) return true;
  return a.second < b.first;
}

int n;
char s[3][MAXN + 1];
int msks[3][MAXN][MAXN];
map<int, pii> has[3];

bool check(int sid, int t, int ml, int mr, char _root) {
  int root = 1 << (_root - 'A');
  if (!has[sid].count(root))
    return false;
    
  pii posl = ml ? has[sid][ml] : mp(-1,- 1);
  pii posr = mr ? has[sid][mr] : mp(-1, -1);
  pii posroot = has[sid][root];
  
  pii arr[3];
  switch (t) {
  case PRE: arr[0] = posroot; arr[1] = posl; arr[2] = posr; break;
  case IN: arr[0] = posl; arr[1] = posroot; arr[2] = posr; break;
  case POST: arr[0] = posl; arr[1] = posr; arr[2] = posroot; break;
  default:
    assert(false);
  }
  for (int i = 0; i < 3; i++)
  for (int j = i + 1; j < 3; j++)
    if (!check_ord(arr[i], arr[j]))
      return false;
  return true;
}

int ord[6];
Tree dyn[MAXN][MAXN][3][3][3];
bool was[MAXN][MAXN][3][3][3];

Tree calc(int l1, int r1, int t1, int t2, int t3) {
  assert(l1 <= r1);
    
  Tree &res = dyn[l1][r1][t1][t2][t3];
  if (was[l1][r1][t1][t2][t3])
    return res;

  was[l1][r1][t1][t2][t3] = true;
  res = Tree();
  {
    int msk = msks[0][l1][r1];
    if (!has[1].count(msk)) return res;
    if (!has[2].count(msk)) return res;
  }
  #define neL ord[t1 * 2 + 0], ord[t2 * 2 + 0], ord[t3 * 2 + 0]
  #define neR ord[t1 * 2 + 1], ord[t2 * 2 + 1], ord[t3 * 2 + 1]
  switch (t1) {
  case PRE: {
    char root = s[0][l1];
    for (int firR = l1 + 1; firR <= r1 + 1; firR++) {
      Tree l, r;
      if (l1 + 1 < firR) {
        l = calc(l1 + 1, firR - 1, neL);
        if (l.s[0].empty()) continue;
      }
      if (firR <= r1) {
        r = calc(firR, r1, neR);
        if (r.s[0].empty()) continue;
      }
      int ml = l.getMask();
      int mr = r.getMask();
      if (!check(1, t2, ml, mr, root)) continue;
      if (!check(2, t3, ml, mr, root)) continue;
      
      Tree cur(l, r, root);
      if (res.s[0].empty()) res = cur;
      res = min(res, cur);
    }
  } break;
  case IN: {
    for (int i = l1; i <= r1; i++) {
      char root = s[0][i];
      Tree l, r;
      if (l1 < i) {
        l = calc(l1, i - 1, neL);
        if (l.s[0].empty()) continue;
      }
      if (i < r1) {
        r = calc(i + 1, r1, neR);
        if (r.s[0].empty()) continue;
      }
      int ml = l.getMask();
      int mr = r.getMask();
      if (!check(1, t2, ml, mr, root)) continue;
      if (!check(2, t3, ml, mr, root)) continue;
      
      Tree cur(l, r, root);
      if (res.s[0].empty()) res = cur;
      res = min(res, cur);
    }
  } break;
  case POST: {
    char root = s[0][r1];
    for (int firR = l1; firR <= r1; firR++) {
      Tree l, r;
      if (l1 < firR) {
        l = calc(l1, firR - 1, neL);
        if (l.s[0].empty()) continue;
      }
      if (firR < r1) {
        r = calc(firR, r1 - 1, neR);
        if (r.s[0].empty()) continue;
      }
      int ml = l.getMask();
      int mr = r.getMask();
      if (!check(1, t2, ml, mr, root)) continue;
      if (!check(2, t3, ml, mr, root)) continue;
      
      Tree cur(l, r, root);
      if (res.s[0].empty()) res = cur;
      res = min(res, cur);
    }
  } break;
  }
  return res;
}

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif

  while (scanf("%s%s%s", s[0], s[1], s[2]) == 3) {
    n = strlen(s[0]);
    
    for (int t = 0; t < 3; t++) {
      has[t].clear();
      
      for (int l = 0; l < n; l++) {
        int msk = 0;
        for (int r = l; r < n; r++) {
          msk |= 1 << (s[t][r] - 'A');
          msks[t][l][r] = msk;
          has[t][msk] = mp(l, r);
        }
      }
    }
    
    for (int i = 0; i < 6; i++)
      ord[i] = i / 2;
      
    bool first = true;
    do {
      for (int l = 0; l < n; l++)
      for (int r = l; r < n; r++)
      for (int t1 = 0; t1 < 3; t1++)
      for (int t2 = 0; t2 < 3; t2++)
      for (int t3 = 0; t3 < 3; t3++)
        was[l][r][t1][t2][t3] = false;
      Tree res = calc(0, n - 1, 0, 1, 2);
      if (res.s[0].empty()) continue;
      
      const char *names[] = { "Pre", "In", "Post" };
      if (!first) printf("\n");
      first = false;
      for (int i = 0; i < 6; i++)
        printf("%s%c", names[ord[i]], "\n "[i + 1 < 6]);
      for (int t = 0; t < 3; t++)
        printf("%s\n", res.s[t].c_str());
    } while (next_permutation(ord, ord + 6));
    assert(!first);
    #ifdef DEBUG
    printf("==========\n");
    #endif
  }
  TIMESTAMP("end");
  return 0;
}

