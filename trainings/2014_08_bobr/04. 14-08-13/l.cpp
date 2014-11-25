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

const int MOD = 21092013;

string initial, following;

int main() {
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
#   ifndef _DEBUG
        freopen("l.in", "r", stdin);
        freopen("l.out", "w", stdout);
#   endif
    int tests;
    cin >> tests;
    int caseNum = 1;
    int i;
    while (tests--) {
        cout << "Case " << caseNum++ << ": ";
        cin >> initial >> following;
        int trg = 0;
        for (i = 0; i < (int)initial.length(); i++)
            if (initial[i] == 'U') {
                if (trg)
                    trg--;
            } else
                initial[trg++] = initial[i];
        initial.resize(trg);
        int result = 1;
        int right = 1, left = 1;
        for (i = 0; i < (int)following.length(); i++)
            switch (following[i]) {
                case 'L':
                    result = (result + left) % MOD;
                    right = (right + left) % MOD;
                    break;

                case 'R':
                    result = (result + right) % MOD;
                    left = (left + right) % MOD;
                    break;

                case 'U':
                    if (!initial.empty()) {
                        result = (result + 1) % MOD;
                        if (initial[initial.length() - 1] == 'L')
                            right = (right + 1) % MOD;
                        else
                            left = (left + 1) % MOD;
                        initial.resize(initial.length() - 1);
                    }
            }
        cout << result << '\n';
    }
}
