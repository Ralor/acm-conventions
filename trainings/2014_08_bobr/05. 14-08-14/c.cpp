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

int n;
//bool mx[10000][10000];
//bool used[10000];
//int sum;
int joined[10000];
int dsu[10000], rang[10000];
int dsuCount[10000];

void dsu_make(int i) {
  dsu[i] = i;
  rang[i] = 0;
}
int dsu_get(int i) {
  if( dsu[i] == i )
    return i;
  return dsu[i] = dsu_get(dsu[i]);
}
int dsu_merge(int i, int j) {
  i = dsu_get(i); j = dsu_get(j);
  if( i != j ) {
    if( rang[i] > rang[j] )
      swap(i,j);
    dsu[i] = j;
    if( rang[i] == rang[j] )
      ++rang[j];
  }
  return j;
}

/*bool Dfs(int node) {
    if (used[node])
        return false;
    if (joined[node] >= 3)
        sum++;
    if (sum >= 2)
        return true;
    used[node] = true;
    for (int i = 0; i < n; i++)
        if (mx[node][i]) {
            if (Dfs(i))
                return true;
        }
    return false;
}*/

int main() {
#   ifdef _DEBUG
        freopen("c.in", "r", stdin);
#   else
        freopen("c.in", "r", stdin);
        freopen("c.out", "w", stdout);
#   endif
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int m;
    while (scanf("%d%d", &n, &m) == 2) {
        //memset(mx, 0x00, sizeof mx);
        memset(joined, 0x00, sizeof joined);
        memset(dsuCount, 0x00, sizeof dsuCount);
        for (int i = 0; i < n; i++)
            dsu_make(i);
        bool ok = false;
        while (m--) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (ok)
                continue;
            x--;
            y--;
            //mx[x][y] = mx[y][x] = true;
            if (++joined[x] >= 4)
                ok = true;
            else if (++joined[y] >= 4)
                ok = true;
            else {
                bool j1 = joined[x] >= 3;
                bool j2 = joined[y] >= 3;
                x = dsu_get(x);
                y = dsu_get(y);
                if (j1)
                    dsuCount[x]++;
                if (x != y && j2)
                    dsuCount[y]++;
                int z = dsu_merge(x, y);
                if (x != y)
                    dsuCount[z] = dsuCount[x] + dsuCount[y];
                if (dsuCount[z] >= 2)
                    ok = true;
            }
        }
        /*if (!ok) {
            memset(used, 0x00, sizeof used);
            for (int i = 0; !ok && i < n; i++) {
                sum = 0;
                ok = Dfs(i);
            }
        }*/
        puts(ok ? "YES" : "NO");
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
