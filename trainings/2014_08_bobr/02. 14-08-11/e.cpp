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

string words[30];
vector<string> cubes;
bool alphaExists[256];
bool mx[256][256];
int wordLen;

int main() {
#   ifdef _DEBUG
        freopen("e.in", "r", stdin);
#   else
        freopen("e.in", "r", stdin);
        freopen("e.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, j, k, n;
    cubes.reserve(4);
    while (cin >> n, n) {
        char exclude;
        cin >> exclude;
        memset(alphaExists, 0x00, sizeof alphaExists);
        if (exclude != '-')
            alphaExists[exclude] = true;
        memset(mx, 0x01, sizeof mx);
        for (i = 0; i < 256; i++)
            mx[i][i] = false;
        for (i = 0; i < n; i++) {
            cin >> words[i];
            string& word = words[i];
            wordLen = word.length();
            for (j = 0; j < wordLen; j++) {
                alphaExists[word[j]] = true;
                for (k = j + 1; k < wordLen; k++)
                    mx[word[j]][word[k]] = mx[word[k]][word[j]] = false;
            }
        }
        for (i = 0; i < 256; i++)
            if (!alphaExists[i])
                for (j = 0; j < 256; j++)
                    mx[i][j] = mx[j][i] = false;
        debug << "Powers:\n";
        for (i = 'A'; i <= 'Z'; i++) {
            int p = 0;
            for (j = 'A'; j <= 'Z'; j++)
                if (mx[i][j])
                    p++;
            debug << char(i) << ": " << p << '\n';
        }
        debug << '\n';
        //Степень вершины.
    calcPowerAgain:
        for (i = 'A'; i <= 'Z'; i++)
            if (alphaExists[i]) {
                int p = 0;
                for (j = 'A'; j <= 'Z'; j++)
                    if (mx[i][j]) {
                        if (++p > 5)
                            break;
                    }
                if (p == 5) {
                    string cube;
                    cube += char(i);
                    for (j = 'A'; j <= 'Z'; j++)
                        if (mx[i][j]) {
                            cube += char(j);
                            for (k = 'A'; k <= 'Z'; k++)
                                mx[j][k] = false;
                        }
                    sort(cube.begin(), cube.end());
                    cubes.push_back(cube);
                    goto calcPowerAgain;
                }
            }
        debug << "count: " << cubes.size() << '\n';
        for (i = 0; i < (int)cubes.size(); i++)
            cout << cubes[i] << ' ';
        cout << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
