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

#define TASKNAME "maptiles"
#define pb push_back
#define mp make_pair
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif
#define TIMESTAMP(msg) eprintf("["msg"] Time=%.3lfs\n", clock() * 1.0 / CLOCKS_PER_SEC)
#define sz(x) ((int)(x).size())

typedef double ld;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

const int inf = 1e9;
const double eps = 1e-6;

int sgn(ld x) { return x < -eps ? -1 : x > eps; }
struct pt {
  int x, y;
  pt() : x(0), y(0) {}
  pt(int x, int y) : x(x), y(y) {}
  pt operator-(const pt &p2) const { return pt(x - p2.x, y - p2.y); }
  int operator*(const pt &p2) const { return sgn(x * p2.y - y * p2.x); }
};
struct ptld {
  ld x, y;
  ptld() : x(0), y(0) {}
  ptld(const pt &p) : x(p.x), y(p.y) {}
  ptld(ld x, ld y) : x(x), y(y) {}
  ptld operator+(const ptld &p2) const { return ptld(x + p2.x, y + p2.y); }
  bool operator<(const ptld &p2) const {
    if (fabs(x - p2.x) > eps) return x < p2.x;
    return y < p2.y;
  }
  bool operator==(const ptld &p2) const {
    return fabs(x - p2.x) < eps && fabs(y - p2.y) < eps;
  }
};
struct line {
  ld a, b, c;
  line() : a(0), b(0), c(0) {}
  line(const ptld &p1, const ptld &p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a * p1.x - b * p1.y;
  }
  int side(const ptld &p) const { return sgn(a * p.x + b * p.y + c); }
};
void cross(const line &l1, const line &l2, vector<ptld> &re) {
  ld d = l1.a * l2.b - l1.b * l2.a;
  if (fabs(d) < eps) return;
  ptld res(
    (l1.b * l2.c - l1.c * l2.b) / d,
    (l1.a * l2.c - l1.c * l2.a) / -d
  );
  #ifdef DEBUG
  assert(l1.side(res) == 0);
  assert(l2.side(res) == 0);
  #endif
  re.pb(res);
}

bool is_in_c(ld l, ld r, ld x) {
  if (l > r) swap(l, r);
  return l <= x + eps && x - eps <= r;
}
bool is_in_old(ld l, ld r, ld x) {
  if (l > r) swap(l, r);
  return l < x - eps && x + eps < r;
}
bool is_in_o(int l, int r, int x) {
  if (l > r) swap(l, r);
  return l < x && x < r;
}
bool contains_o(const pt &a, const pt &b, const pt &p) {
  if ((p - a) * (p - b) != 0) return false;
  return is_in_o(a.x, b.x, p.x) && is_in_o(a.y, b.y, p.y);
}

int n;
vector<pt> pts;
bool is_inside(const pt &p) {
  assert(sz(pts) == n + 1);
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    pt a = pts[i], b = pts[i + 1];
    if (contains_o(a, b, p)) return true;
    
    if (a.y > b.y) swap(a, b);
    if (a.y == b.y || p.y <= a.y || b.y < p.y)
      continue;
      
    if (ll(b.x - a.x) * ll(p.y - a.y) - ll(b.y - a.y) * ll(p.x - a.x) >= 0)
      cnt++;
  }
  return (cnt & 1) ? true : false;
}

bool check(int x1, int y1, int x2, int y2) {
  if (is_inside(pt((x1 + x2) / 2, (y1 + y2) / 2)))
    return true;
  for (int i = 0; i < n; i++) {
    if (is_in_o(x1, x2, pts[i].x) && is_in_o(y1, y2, pts[i].y))
      return true;
      
    vector<ptld> all;
    line l(pts[i], pts[i + 1]);
    cross(l, line(ptld(x1, y1), ptld(x1, y2)), all);
    cross(l, line(ptld(x1, y1), ptld(x2, y1)), all);
    cross(l, line(ptld(x1, y2), ptld(x2, y2)), all);
    cross(l, line(ptld(x2, y1), ptld(x2, y2)), all);
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    
    int off = 0;
    for (int i2 = 0; i2 < sz(all); i2++)
      if (is_in_c(x1, x2, all[i2].x) && is_in_c(y1, y2, all[i2].y)) {
        if (is_in_c(pts[i].x, pts[i + 1].x, all[i2].x) &&
            is_in_c(pts[i].y, pts[i + 1].y, all[i2].y)) {
          all[off++] = all[i2];
        }
      }
    all.resize(off);
    assert(sz(all) <= 2);
    if (sz(all) == 2) {
      ptld mid = all[0] + all[1];
      mid.x /= 2;
      mid.y /= 2;
      if (is_in_old(x1, x2, mid.x) && is_in_old(y1, y2, mid.y))
        return true;
    }
  }
  return false;
}

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif
  
  int w0, h0;
  while (scanf("%d%d%d", &n, &w0, &h0) == 3) {
    w0 *= 2;
    h0 *= 2;
    
    pts = vector<pt>(n);
    vi xs, ys;
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &pts[i].x, &pts[i].y);
      pts[i].x *= 2;
      pts[i].y *= 2;
      xs.pb(pts[i].x % w0);
      ys.pb(pts[i].y % h0);
    }
    pts.pb(pts[0]);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int ans = 1e9;    
    for (int cy = 0; cy < sz(ys); cy++)
    for (int cx = 0; cx < sz(xs); cx++) {
      int x0 = xs[cx] - w0;
      int y0 = ys[cy] - h0;
//      if (x0 != -196 || y0 != -2)
//        continue;
      
      int minx = inf, miny = 1e9;
      int maxx = -inf, maxy = -1e9;
      for (int i = 0; i < n; i++) {
        assert(pts[i].x >= x0);
        assert(pts[i].y >= y0);
        
        int myx = (pts[i].x - x0) / w0;
        int myy = (pts[i].y - y0) / h0;
        minx = min(minx, myx);
        maxx = max(maxx, myx);
        miny = min(miny, myy);
        maxy = max(maxy, myy);
      }
      assert(minx <= maxx);
      assert(miny <= maxy);
      maxx++;
      maxy++;
//      minx--; miny--;
//      maxx++; maxy++;
//      eprintf("x: %d..%d\n", minx, maxx);
//      eprintf("y: %d..%d\n", miny, maxy);
      int cans = 0;
      for (int y = miny; y <= maxy; y++)
      for (int x = minx; x <= maxx; x++) {
        int x1 = x * w0 + x0;
        int x2 = (x + 1) * w0 + x0;
        int y1 = y * h0 + y0;
        int y2 = (y + 1) * h0 + y0;
        cans += check(x1, y1, x2, y2);
      }
      ans = min(ans, cans);
    }
    printf("%d\n", ans);
  }
  TIMESTAMP("end");
  return 0;
}

