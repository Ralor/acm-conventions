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

struct Item {
    int price;
    llong count;

    Item(int p = 0, llong c = 0) : price(p), count(c) { }

    bool operator<(const Item& i) const {
        return price < i.price;
    }

    bool operator==(const Item& i) const {
        return price == i.price;
    }
};

int main() {
#   ifdef _DEBUG
    freopen("b.in", "r", stdin);
#   else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, n, m;
    while (cin >> n >> m) {
        map<int, llong> hornMap, hoofMap;
        int price;
        llong count;
        llong elapsed = 0, remaining = 0;
        for (i = 0; i < n; i++) {
            cin >> price >> count;
            hornMap[price] += count;
        }
        for (i = 0; i < m; i++) {
            cin >> price >> count;
            hoofMap[price] += count;
            remaining += count;
        }
        vector<Item> horns, hoofs;
        horns.reserve(n);
        hoofs.reserve(m);
        for (const auto& kv : hornMap)
            horns.push_back(Item(kv.first, kv.second));
        for (const auto& kv : hoofMap)
            hoofs.push_back(Item(kv.first, kv.second));
        n = horns.size();
        m = hoofs.size();
        int curHoof = 0, curHorn;
        llong a = 0, b = 0, c = 0;
        for (curHorn = 0; curHorn < n && curHoof < m; curHorn++) {
            if (horns[curHorn].price < hoofs[curHoof].price) {
                a += horns[curHorn].count * elapsed;
                c += horns[curHorn].count * remaining;
            }
            else if (horns[curHorn].price == hoofs[curHoof].price) {
                remaining -= hoofs[curHoof].count;
                a += horns[curHorn].count * elapsed;
                b += horns[curHorn].count * hoofs[curHoof].count;
                c += horns[curHorn].count * remaining;
                elapsed += hoofs[curHoof].count;
                curHoof++;
            }
            else /*if (horns[curHorn].price >= hoofs[curHoof].price)*/ {
                remaining -= hoofs[curHoof].count;
                elapsed += hoofs[curHoof].count;
                curHoof++;
                curHorn--;
            }
        }
        while (curHorn < n)
            a += horns[curHorn++].count * elapsed;
        cout << a << ' ' << b << ' ' << c << '\n';
    }
#   ifdef _DEBUG
    _getch();
#   endif
    return 0;
}
