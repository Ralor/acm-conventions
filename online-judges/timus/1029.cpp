//Ministry.
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

int m, n;
int fee[100][500];
int dp[101][500];//[floor][room]
int toLeft[500], toRight[500];

void Dyn() {
    for (int fl = m - 1; fl >= 0; fl--) {
        int room;
        for (room = 0; room < n; room++)
            toLeft[room] = toRight[room] = dp[fl + 1][room];
        for (room = 1; room < n; room++)
            toLeft[room] = min(toLeft[room], toLeft[room - 1] + fee[fl][room - 1]);
        for (room = n - 2; room >= 0; room--)
            toRight[room] = min(toRight[room], toRight[room + 1] + fee[fl][room + 1]);
        for (room = 0; room < n; room++)
            dp[fl][room] = min(min(toLeft[room], toRight[room]) + fee[fl][room], LIM);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, j;
    while (cin >> m >> n) {
        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                cin >> fee[i][j];
        for (i = 0; i < n; i++)
            dp[m][i] = 0;
        Dyn();
        int result = INT_MAX;
        int room;
        for (i = 0; i < n; i++)
            if (dp[0][i] < result)
                result = dp[0][room = i];
        int fl = 0;
        debug << "Sum: " << result << '\n';
        cout << room + 1;
        while (fl < m - 1) {
            if (dp[fl + 1][room] == dp[fl][room] - fee[fl][room])
                fl++;
            else if (room && dp[fl][room - 1] == dp[fl][room] - fee[fl][room])
                room--;
            else /*if (room < n - 1 && dp[fl][room + 1] == dp[fl][room] - fee[fl][room])*/
                room++;
            /*
            else {
                cerr << "Invalid path\n";
                return 1;
            }
            */
            cout << ' ' << room + 1;
        }
        cout << '\n';
    }
}
