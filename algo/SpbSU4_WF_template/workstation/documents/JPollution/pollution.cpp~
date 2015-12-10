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

#define TASKNAME "pollution"
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
const double eps = 1e-9;

int sgn(const ld &x) { return x < -eps ? -1 : x > eps; }
struct pt {
  ld x, y;
  pt() : x(0), y(0) {}
  pt(ld x, ld y) : x(x), y(y) {}
  pt operator-(const pt &p2) const { return pt(x - p2.x, y - p2.y); }
  pt operator+(const pt &p2) const { return pt(x + p2.x, y + p2.y); }
  pt operator*(const double &b) const { return pt(x * b, y * b); }
  ld dist2() const { return x * x + y * y; }
  bool operator<(const pt &p2) const { return fabs(x - p2.x) < eps ? y < p2.y - eps : x < p2.x; }
  bool operator==(const pt &p2) const { return fabs(x - p2.x) < eps && fabs(y - p2.y) < eps; }

};
struct line {
  ld a, b, c;
  line() : a(0), b(0), c(1) {}
  line(const pt &p1, const pt &p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a * p1.x - b * p1.y;
    #ifdef DEBUG
    assert(side(p1) == 0);
    assert(side(p2) == 0);
    #endif
  }
  ld distz(const pt &p) const { return a * p.x + b * p.y + c; }
  ld norm2() const { return a * a + b * b; }
  int side(const pt &p) const { return sgn(distz(p)); }
};

bool is_in(ld a, ld b, ld x) {
  if (a > b) swap(a, b);
  return a <= x + eps && x - eps <= b;
}
bool is_in(const pt &a, const pt &b, const pt &p) {
  return is_in(a.x, b.x, p.x) && is_in(a.y, b.y, p.y);
}

vector<pt> cross(const pt &center, ld r, const line &l) {
  ld di = l.distz(center);
  ld d2 = l.norm2();
  #ifdef DEBUG
  assert(fabs(d2) > eps);
  #endif
  pt mid = center - pt(l.a, l.b) * (di / d2);
  #ifdef DEBUG
  assert(l.side(mid) == 0);
  #endif
  
  ld s = r * r - di * di / d2;
  if (s < -eps) return vector<pt>();
  if (fabs(di * di - r * r * d2) < eps)
    return vector<pt>(1, mid);
  pt off = pt(-l.b, l.a) * sqrt(s / d2);
  #ifdef DEBUG
  assert(fabs(off.dist2() - s) < eps);
  #endif
  vector<pt> res;
  res.pb(mid + off);
  res.pb(mid - off);
  return res;
}

ld get_sector(const pt &a, const pt &b, const double &r) {
  double asin = a.x * b.y - a.y * b.x;
  double acos = a.x * b.x + a.y * b.y;
  if (fabs(asin) < eps && fabs(acos) < eps)
    return 0;
  double ang = atan2(asin, acos);
  return ang * r * r / 2;
}

ld calc(const pt &a, const pt &b, const double &r) {
  pt mid = (a + b) * 0.5;
  if (mid.dist2() <= r * r + eps) {
//  if (a.dist2() < r * r - eps || b.dist2() < r * r - eps) {
//    assert(a.dist2() <= r * r + eps && b.dist2() <= r * r + eps);
    return (a.x * b.y - a.y * b.x) / 2;
  } else {
//    assert(a.dist2() >= r * r - eps && b.dist2() >= r * r - eps);
    return get_sector(a, b, r);
  }
}

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif
  
  int n; double r;
  while (scanf("%d%lf", &n, &r) == 2) {
    vector<pt> pts(n);
    for (int i = 0; i < n; i++) {
      double x, y;
      scanf("%lf%lf", &x, &y);
      pts[i] = pt(x, y);
    }
    pts.pb(pts[0]);
    
    ld ans = 0;
    for (int i = 0; i < n; i++) {
      pt a = pts[i], b = pts[i + 1];
      if (a == b) continue;
      vector<pt> cro = cross(pt(), r, line(a, b));
      cro.pb(a);
      cro.pb(b);
      sort(cro.begin(), cro.end());
      if (b < a)
        reverse(cro.begin(), cro.end());
      int off = 0;
      for (int i = 0; i < sz(cro); i++)
        if (is_in(a, b, cro[i]))
          cro[off++] = cro[i];
      cro.resize(off);
      cro.erase(unique(cro.begin(), cro.end()), cro.end());
      for (int i2 = 0; i2 + 1 < sz(cro); i2++) {
        ld tmp = calc(cro[i2], cro[i2 + 1], r);
//        eprintf("cro=%.2lf %.2lf; %.2lf %.2lf\n", cro[i2].x, cro[i2].y, cro[i2 + 1].x, cro[i2 + 1].y);
//        eprintf("  tmp=%.2lf\n", tmp);
        ans += tmp;
      }
    }
    printf("%.9lf\n", (double)fabs(ans));
  }
  TIMESTAMP("end");
  return 0;
}

