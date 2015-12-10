#define VERBOSE
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

llong mx[4100][4100];
bitset<4100> alive;
int size[4100];

struct Item {
    ldouble dist;
    int i, j;

    Item() { }
    Item(ldouble d, int i, int j) : dist(d), i(i), j(j) { }

    bool operator<(const Item& i) const {
        return dist > i.dist;
    }
};

int main() {
#   ifdef _DEBUG
        freopen("h.in", "r", stdin);
#   else
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, j, n;
    string s;
    cout << setprecision(7) << fixed;
    while (cin >> n) {
        alive.reset();
        memset(size, 0x00, sizeof size);
        memset(mx, 0x00, sizeof mx);
        for (i = 0; i < n; i++) {
            alive[i] = true;
            size[i] = 1;
        }
        for (i = 0; i < n; i++) {
            cin >> s;
            for (j = 0; j < n; j++)
                mx[i][j] = s[j] - '0';
        }
        priority_queue<Item> q;
        for (i = 0; i < n; i++)
            for (j = 0; j < i; j++)
                q.emplace((ldouble)mx[i][j], i, j);
        int curN = n;
        for (int step = 1; step < n; step++) {
            Item it;
            do {
                it = q.top();
                q.pop();
            } while (!alive[it.i] || !alive[it.j]);
            cout << it.j + 1 << ' ' << it.i + 1 << ' ' << it.dist << '\n';
            alive[it.i] = alive[it.j] = false;
            alive[curN] = true;
            size[curN] = size[it.i] + size[it.j];
            for (i = 0; i < curN; i++) {
                mx[i][curN] = mx[curN][i] = mx[it.i][i] + mx[it.j][i];
                q.emplace((ldouble)mx[i][curN] / ldouble(size[curN] * size[i]), curN, i);
            }
            curN++;
        }
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
