//Brackets sequence.
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

string s;
vector<int> roundPos, indexPos;
int dp[101][101];//[left][right]
string answer[101][101];

int Dyn(int left, int right) {
    if (dp[left][right] != -1)
        return dp[left][right];
    int i = left;
    int pre = 0;
    string sPre;
    while (i < right) {
        if (s[i] == ')')
            sPre += '(';
        else if (s[i] == ']')
            sPre += '[';
        else
            break;
        pre++;
        i++;
    }
    answer[left][right] = sPre = string(sPre.rbegin(), sPre.rend()) + s.substr(left, i - left);
    if (i >= right)
        return (dp[left][right] = pre);
    int result = Dyn(i + 1, right) + 1;
    string sResult;
    if (s[i] == '(') {
        sResult = "()" + answer[i + 1][right];
        for (int j: roundPos)
            if (j > i && j < right) {
                int d = Dyn(i + 1, j) + Dyn(j + 1, right);
                if (d < result) {
                    result = d;
                    sResult = "(" + answer[i + 1][j] + ")" + answer[j + 1][right];
                }
            }
    } else /*if (s[i] == '[')*/ {
        sResult = "[]" + answer[i + 1][right];
        for (int j: indexPos)
            if (j > i && j < right) {
                int d = Dyn(i + 1, j) + Dyn(j + 1, right);
                if (d < result) {
                    result = d;
                    sResult = "[" + answer[i + 1][j] + "]" + answer[j + 1][right];
                }
            }
    }
    answer[left][right] = sPre + sResult;
    return (dp[left][right] = pre + result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> s) {
        roundPos.clear();
        indexPos.clear();
        memset(dp, 0xFF, sizeof dp);
        for (int i = 0; i < (int)s.length(); i++)
            if (s[i] == ')')
                roundPos.push_back(i);
            else if (s[i] == ']')
                indexPos.push_back(i);
        Dyn(0, s.length());
        cout << answer[0][s.length()] << '\n';
    }
}
