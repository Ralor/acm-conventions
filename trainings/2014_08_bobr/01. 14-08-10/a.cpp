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



int main() {
#   ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);  
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   else
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
    int i;
    int tests;
    cin >> tests;
    while (tests--) {
        int k;
        cin >> k;
        cout << k << ' ';
        int arr[15];
        for (i = 0; i < 15; i++)
            cin >> arr[i];
        int st = 0;
        int res = 0;
        for (i = 1; i < 15; i++) {
            if (arr[i] > arr[i - 1])
                st++;
            else if (arr[i] < arr[i - 1]) {
                if (st) {
                    st--;
                    res++;
                }
            }
        }
        cout << res << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
