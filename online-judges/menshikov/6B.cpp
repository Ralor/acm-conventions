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
int a[500];
bool cache[501][50001];

void Rcsv(int pos, int sum) {
    if (pos > n || cache[pos][sum])
        return;
    cache[pos][sum] = true;
    Rcsv(pos + 1, sum + a[pos]);
    Rcsv(pos + 1, sum);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, j;
    while (cin >> n) {
        memset(cache, 0x00, sizeof cache);
        for (i = 0; i < n; i++)
            cin >> a[i];
        int result = 0;
        Rcsv(0, 0);
        for (i = 0; i < 50001; i++)
            for (j = 0; j <= n; j++)
                if (cache[j][i]) {
                    result++;
                    break;
                }
        cout << result << '\n';
    }
}
