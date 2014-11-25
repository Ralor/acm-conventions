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

#ifndef _DEBUG
#   undef VERBOSE
#endif

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;

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
bool visible[100][100] = { };
int color[100] = { };
int succeed = 0;

bool Fill(int node) {
    if (color[node])
        return true;
    bool available[4] = { true, true, true, true };
    char count = 4;
    for (int i = 0; i < n; i++)
        if (visible[node][i] && color[i] && available[color[i] - 1]) {
            available[color[i] - 1] = false;
            if (!--count)
                return false;
        }
    int backupColor[100];
    memcpy(backupColor, color, sizeof color);
    for (unsigned char i = 0; i < 4; i++)
        if (available[i]) {
            color[node] = i + 1;
            succeed++;
            for (int j = 0; j < n; j++)
                if (visible[node][j]) {
                    debug << node + 1 << " > " << j + 1 << '\n';
                    bool f = Fill(j);
                    debug << node + 1 << " < " << j + 1 << '\n';
                    if (!f) {
                        succeed--;
                        memcpy(color, backupColor, sizeof color);
                        break;
                    }
                }
            if (color[node])
                return true;
        }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
#   ifndef _DEBUG
        freopen("g.in", "r", stdin);
        freopen("g.out", "w", stdout);
#   endif
    int i, j;
    cin >> n;
    int a, b;
    char c;
    while (cin >> a >> c >> b) {
        a--;
        b--;
        visible[a][b] = visible[b][a] = true;
    }
    for (i = 0; i < n; i++) {
        color[i] = 1;
        succeed++;
        for (j = 0; succeed < n && j < n; j++)
            if (visible[i][j]) {
                debug << "> " << j + 1 << '\n';
                Fill(j);
                debug << "< " << j + 1 << '\n';
            }
        if (succeed == n) {
            for (j = 0; j < n; j++)
                cout << j + 1 << ' ' << color[j] << '\n';
            return 0;
        }
    }
}
