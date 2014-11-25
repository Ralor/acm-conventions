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

int cityValues[(int)1e5];
int citySums[(int)1e5];
bool cityOk[(int)1e5];

int main() {
#   ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);  
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   else
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
    int cityCount;
    int i, j, x;
    int caseNum = 1;
    while (cin >> cityCount, cityCount) {
        memset(cityOk, 0x01, sizeof cityOk);
        for (i = 0; i < cityCount; i++) {
            cin >> x; 
            cityValues[i] = x;
        }
        for (i = 0; i < cityCount; i++) {
            cin >> x; 
            cityValues[i] -= x;
        }
        int start = 0, end = 1;
        memset(citySums, 0x00, sizeof citySums);
        j = 0;
        while (start != end) {
            for (i = start; i < end; i++)
                if (cityOk[i]) {
                    citySums[i] += cityValues[j];
                    if (citySums[i] < 0)
                        cityOk[i] = false;
                }
            if (++j == cityCount)
                j = 0;
            if (end < cityCount)
                end++;
            else
                start++;
        }
        cout << "Case " << caseNum << ':';
        for (i = 0; i < cityCount; i++)
            if (cityOk[i])
                cout << ' ' << i + 1;
        cout << '\n';
        caseNum++;
    }
#   ifdef _DEBUG
        while (cin.get() != '\n') { }
        while (cin.get() != '\n') { }
#   endif
    return 0;
}
