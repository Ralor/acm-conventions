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

int n;
int arr[21][21];
bool result[21];
bool cache[1 << 20];
int balance[21];
int balances[20][1 << 20];

void Rcsv(int mask, int count) {
    cache[mask] = true;
    if (count == 1) {
        int i = 0;
        while (true) {
            if (!(mask & 0x1)) {
                result[i] = true;
                return;
            }
            mask >>= 1;
            i++;
        }
    } else
        for (int i = 0; i < n; i++)
            if (!(mask & (1 << i)) && balances[i][mask] < 0) {
                if (!cache[mask | 1 << i]) {
                    //balance[i] -= balances[i][mask | 1 << i];
                    Rcsv(mask | 1 << i, count - 1);
                    //balance[i] += balances[i][mask | 1 << i];
                }
            }
}

int main() {
#   ifdef _DEBUG
        freopen("a.in", "r", stdin);
#   else
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    int i, j, k;
    while (tests--) {
        memset(result, 0x00, sizeof result);
        memset(cache, 0x00, sizeof cache);
        memset(balance, 0x00, sizeof balance);
        memset(balances, 0x00, sizeof balances);
        cin >> n;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {
                cin >> arr[i][j];
                balance[j] += arr[i][j];
            }
        for (i = 0x00; i < 1 << n; i++) {
            for (j = 0; j < n; j++) {
                if (!(i & (1 << j)))
                    for (k = 0; k < n; k++) {
                        if (!(i & (1 << k))) {
                            balances[j][i] += arr[k][j];
                        }
                    }
            }
        }
        for (i = 0; i < n; i++)
            debug << balance[i] << ' ';
        debug << '\n';
        Rcsv(0x00, n);
        bool printZero = true;
        for (i = 0; i < n; i++)
            if (result[i]) {
                cout << i + 1 << ' ';
                printZero = false;
            }
        if (printZero)
            cout << '0';
        cout << '\n';
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
