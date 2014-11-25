//#define VERBOSE
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

const int HEIGHT = 12, WIDTH = 10;

char field[HEIGHT][WIDTH];
bool used[HEIGHT][WIDTH];

/*void Dfs(int y, int x) {
    while (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && field[y][x] == currentPopping) {
        field[y][x] = '.';
        Dfs(y - 1, x);
        Dfs(y + 1, x);
        Dfs(y, x - 1);
        //Dfs(y, x + 1);
        x++;
    }
}*/

struct Pos {
    int y, x;

    Pos() { }
    Pos(int i, int j): y(i), x(j) { }
};

void Pop(int y, int x) {
    char currentPopping = field[y][x];
    if (currentPopping == '.')
        return;
    vector<Pos> delayed;
    delayed.reserve(2);
    bool ok = false;
    queue<Pos> q;
    q.push(Pos(y, x));
    memset(used, 0x00, sizeof used);
    while (!q.empty()) {
        Pos p = q.front();
        q.pop();
        if (p.y >= 0 && p.y < HEIGHT && p.x >= 0 && p.x < WIDTH && field[p.y][p.x] == currentPopping && !used[p.y][p.x]) {
            if (!ok) {  
              if (delayed.size() == 2) {
                    field[delayed[0].y][delayed[0].x] = '.';
                    field[delayed[1].y][delayed[1].x] = '.';
                    field[p.y][p.x] = '.';
                    ok = true;
                } else
                    delayed.push_back(p);
            } else
                field[p.y][p.x] = '.';
            used[p.y][p.x] = true;
            q.push(Pos(p.y - 1, p.x));
            q.push(Pos(p.y + 1, p.x));
            q.push(Pos(p.y, p.x - 1));
            q.push(Pos(p.y, p.x + 1));
        }
    }
}

void GravitateDown() {
    for (int x = 0; x < WIDTH; x++) {
        int trg = 0;
        for (int y = 0; y < HEIGHT; y++) {
            field[trg][x] = field[y][x];
            if (field[y][x] != '.')
                trg++;
        }
        for (int y = trg; y < HEIGHT; y++)
            field[y][x] = '.';
    }
}

bool IsColumnEmpty(int x) {
    for (int y = 0; y < WIDTH; y++)
        if (field[y][x] != '.')
            return false;
    return true;
}

void GravitateLeft() {
    int trg = 0;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++)
            field[y][trg] = field[y][x];
        if (!IsColumnEmpty(x))
            trg++;
    }
    for (int x = trg; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++)
            field[y][x] = '.';
}

void DebugPrint() {
    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++)
            debug << field[y][x];
        debug << '\n';
    }
    debug << '\n';
}

int main() {
#   ifdef _DEBUG
        freopen("g.in", "r", stdin);
#   else
        freopen("g.in", "r", stdin);
        freopen("g.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    int i, j, n;
    while (cin >> n, n) {
        for (i = HEIGHT - 1; i >= 0; i--) {
            cin >> s;
            for (j = 0; j < WIDTH; j++)
                field[i][j] = s[j];
        }
        DebugPrint();
        while (n--) {
            char c;
            cin >> c >> i;
            i--;
            j = c - 'a';
            debug << "popping...\n";
            Pop(i, j);
            DebugPrint();
            GravitateDown();
            DebugPrint();
            GravitateLeft();
            DebugPrint();
        }
        int result = 0;
        for (i = 0; i < HEIGHT; i++)
            for (j = 0; j < WIDTH; j++)
                if (field[i][j] != '.')
                    result++;
        cout << result << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
