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

struct Pos {
    int y, x;

    Pos() { }
    Pos(int i, int j): y(i), x(j) { }
};

struct Cell: public Pos {
    int dist;

    Cell() { }
    Cell(int i, int j, int d): Pos(i, j), dist(d) { }
};

int h, w;
char field[104][104];

void Bfs(int f[ ][104], int y, int x) {
    memset(f, 0xFF, 104 * 104 * sizeof(int));
    static const char delta[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
    deque<Cell> dq;
    dq.push_front(Cell(y, x, 0));
    while (!dq.empty()) {
        Cell c = dq.front();
        dq.pop_front();
        if (f[c.y][c.x] != -1)
            continue;
        for (char i = 0; i < 4; i++) {
            char near = field[c.y + delta[i][0]][c.x + delta[i][1]];
            if (near == '.')
                dq.push_front(Cell(c.y + delta[i][0], c.x + delta[i][1], c.dist));
            else if (near == '#')
                dq.push_back(Cell(c.y + delta[i][0], c.x + delta[i][1], c.dist + 1));
        }
        f[c.y][c.x] = c.dist;
    }
}

int main() {
#   ifdef _DEBUG
        freopen("j.in", "r", stdin);
#   else
        freopen("j.in", "r", stdin);
        freopen("j.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    int i, j;
    string s;
    vector<Pos> prizoners;
    prizoners.reserve(2);
    while (tests--) {
        cin >> h >> w;
        prizoners.clear();
        //The outer wall.
        memset(field[0], '*', sizeof field[0]);
        memset(field[1], '.', sizeof field[1]);
        for (i = 1; i < 103; i++) {
            field[i][0] = '*';
            field[i][1] = '.';
        }
        memset(field[h + 2], '.', 104 * sizeof(char));
        memset(field[h + 3], '*', 104 * sizeof(char));
        for (i = 1; i < 103; i++) {
            field[i][w + 2] = '.';
            field[i][w + 3] = '*';
        }
        field[h + 2][0] = field[h + 3][w + 2] = '*';
        for (i = 0; i < h; i++) {
            cin >> s;
            for (j = 0; j < w; j++) {
                if (s[j] == '$') {
                    prizoners.push_back(Pos(i + 2, j + 2));
                    s[j] = '.';
                }
                field[i + 2][j + 2] = s[j];
            }
        }
        for (i = 0; i < h + 4; i++) {
            for (j = 0; j < w + 4; j++)
                debug << field[i][j];
            debug << '\n';
        }
        int outer[104][104];
        int first[104][104];
        int second[104][104];
        Bfs(outer, 1, 1);
        Bfs(first, prizoners[0].y, prizoners[0].x);
        Bfs(second, prizoners[1].y, prizoners[1].x);
        int result = INT_MAX;
        for (i = 1; i < 103; i++)
            for (j = 1; j < 103; j++)
                if (outer[i][j] != -1)
                    result = min(
                        result,
                        outer[i][j] + first[i][j] + second[i][j] - 2 * (field[i][j] == '#')
                    );
        cout << result << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
