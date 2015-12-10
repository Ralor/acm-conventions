//Джентльмены.
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

int total;
int n;
int cards[100];
int dp[100][100000];//[pos][weight]
bitset<100> take[100000];

int Dyn(int pos, int weight) {
    if (pos >= n)
        return weight == total ? 0 : -2;
    if (dp[pos][weight] != -1)
        return dp[pos][weight];
    int result = -2;
    int x = Dyn(pos + 1, weight);
    if (x != -2) {
        result = x;
        take[pos][weight] = false;
    }
    x = Dyn(pos + 1, weight + cards[pos]);
    if (x != -2) {
        if (result != -2)
            throw 0;
        result = x + 1;
        take[pos][weight] = true;
    }
    return (dp[pos][weight] = result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;
    while (cin >> total >> n) {
        for (i = 0; i < n; i++)
            cin >> cards[i];
        memset(dp, 0xFF, sizeof dp);
        int count;
        try {
            count = Dyn(0, 0);
        }
        catch (int) {
            cout << "-1\n";
            continue;
        }
        if (count == -2) {
            cout << "0\n";
            continue;
        }
        int w = 0;
        for (i = 0; i < n; i++)
            if (take[i][w])
                w += cards[i];
            else
                cout << i + 1 << ' ';
        cout << '\n';
    }
}
