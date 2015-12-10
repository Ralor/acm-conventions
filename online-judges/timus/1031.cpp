//Railway Tickets.
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

const int LIM = (int)1e9 + 1;

int l1, l2, l3, c1, c2, c3;
int n;
int arrival, departure;
int stations[10000];
int dp[10000];//[stationIndex]

int Dyn(int index) {
    if (index >= departure)
        return 0;
    if (dp[index] != -1)
        return dp[index];
    int result = LIM;
    int next;
    next = upper_bound(stations + index + 1, stations + n, stations[index] + l1) - 1 - stations;
    if (next > index)
        result = min(result, Dyn(next) + c1);
    next = upper_bound(stations + index + 1, stations + n, stations[index] + l2) - 1 - stations;
    if (next > index)
        result = min(result, Dyn(next) + c2);
    next = upper_bound(stations + index + 1, stations + n, stations[index] + l3) - 1 - stations;
    //Guaranteed.
    result = min(result, Dyn(next) + c3);
    return (dp[index] = result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    stations[0] = 0;
    int i;
    while (cin >> l1 >> l2 >> l3 >> c1 >> c2 >> c3 >> n >> arrival >> departure) {
        arrival--;
        departure--;
        if (arrival > departure)
            swap(arrival, departure);
        for (i = 1; i < n; i++)
            cin >> stations[i];
        memset(dp, 0xFF, sizeof dp);
        cout << Dyn(arrival) << '\n';
    }
}
