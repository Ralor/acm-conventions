//#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
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
#ifdef _DEBUG
#   include <conio.h>
#endif

#ifndef _DEBUG
#   undef VERBOSE
#endif

#define eps      1e-8
#define inf      (1000 * 1000 * 1000)
#define linf     (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)   ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)    int((x).size())
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define mp       make_pair

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;

template <typename T>
struct Point {
    T x, y;

    Point() { }
    Point(T x, T y): x(x), y(y) { }

    bool IsNear(const Point& another, T sqrDistance) const {
        T dx = x - another.x;
        T dy = y - another.y;
        T r = dx * dx + dy * dy;
        return r < sqrDistance;
    }
};

struct IntersectionResult {
    bool parallel;
    Point<double> p;
};

struct Line {
    int a, b, c;

    Line() { }
    Line(const Point<int>& p1, const Point<int>& p2):
        a(p2.y - p1.y), b(p1.x - p2.x), c(p2.x * p1.y - p1.x * p2.y) { }

    IntersectionResult Intersect(const Line& another) const {
        int d = a * another.b - b * another.a;
        IntersectionResult result;
        result.parallel = d == 0;
        if (result.parallel)
            return result;
        double d1 = double(-c) * another.b - double(b) * -another.c;
        double d2 = double(a) * -another.c - double(-c) * another.a;
        result.p = Point<double>(d1 / d, d2 / d);
        return result;
    }

    /*double SqrDistanceTo(const Point<double>& p) const {
        
        return .0;
    }*/
};

int main() {
#   ifdef _DEBUG
        freopen("a.in", "r", stdin);
#   else
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int r, cx, cy, n;
    int i, j;
    vector<Line> lines;
    while (scanf("%d%d%d%d", &r, &cx, &cy, &n) == 4 && r) {
        lines.clear();
        Point<double> center(cx, cy);
        double sqrR = r * r;
        int result = 1;
        for (i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            Point<int> a(x1, y1);
            Point<int> b(x2, y2);
            Line ln(a, b);
            Point<int> c(x2 - x1, y2 - y1);//Vector.
            Point<int> p(cx - x1, cy - y1);//Vector.
            double doubleS = fabs(double(c.x * p.y - c.y * p.x));
            double baseLen = sqrt(double(c.x * c.x + c.y * c.y));
            //double dist = ln.SqrDistanceTo(center);
            double h = doubleS / baseLen;
            debug << h << ' ';
            if (h < r || eq(h, r)) {
                result++;
                for (j = 0; j < (int)lines.size(); j++) {
                    IntersectionResult res = ln.Intersect(lines[j]);
                    if (!res.parallel && res.p.IsNear(center, sqrR))
                        result++;
                }
                lines.push_back(ln);
            }
        }
        debug << '\n';
        printf("%d\n", result);
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
