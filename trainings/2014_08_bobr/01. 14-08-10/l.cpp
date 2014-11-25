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

enum {
    B_TOP    = 0x1,
    B_RIGHT  = 0x2,
    B_BOTTOM = 0x4,
    B_LEFT   = 0x8,
};

struct Cell {
    bool used;
    bool typeNumber;
    int col;
    uint border;

    Cell(): used(false), typeNumber(false), border(0x0) { }
    Cell(bool t, uint b): typeNumber(t), border(b) { }
};

struct Row {
    Cell cells[9];
    int pos;

    Row(): pos(0) { }

    void Push(const Cell& cell) {
        while (cells[pos].used)
            pos++;
        Push(cell, pos);
    }

    void Push(const Cell& cell, int where) {
        cells[where] = cell;
        cells[where].used = true;
        cells[where].col = where;
    }

    void Clear() {
        pos = 0;
        for (int i = 0; i < 9; i++) {
            cells[i].used = false;
            cells[i].typeNumber = false;
            cells[i].col = 0;
            cells[i].border = 0x0;
        }
    }
};

Row rows[9];
char result[20][30];

int main() {
#   ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);  
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   else
        freopen("l.in", "r", stdin);
        freopen("l.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
    int i, j, n;
    while (cin >> n, n) {
        for (i = 0; i < 9; i++)
            rows[i].Clear();
        int colCount = 0;
        for (int curRow = 0; curRow < n; curRow++) {
            int cellsInRow;
            cin >> cellsInRow;
            for (int curCell = 0; curCell < cellsInRow; curCell++) {
                int rowSpan, colSpan;
                cin >> rowSpan >> colSpan;
                uint style = B_TOP | B_LEFT;
                if (rowSpan == 1)
                    style |= B_BOTTOM;
                if (colSpan == 1)
                    style |= B_RIGHT;
                rows[curRow].Push(Cell(true, style));
                int curColumn = rows[curRow].cells[rows[curRow].pos].col;
                colCount = max(colCount, curColumn + colSpan);
                for (i = 0; i < rowSpan; i++)
                    for (j = 0; j < colSpan; j++)
                        if (i || j) {
                            style = 0x0;
                            if (!i)
                                style |= B_TOP;
                            if (!j)
                                style |= B_LEFT;
                            if (i == rowSpan - 1)
                                style |= B_BOTTOM;
                            if (j == colSpan - 1)
                                style |= B_RIGHT;
                            rows[curRow + i].Push(Cell(false, style), curColumn + j);
                        }
            }
        }
        memset(result, ' ', sizeof result);
        for (i = 0; i < n; i++) {
            for (j = 0; j < colCount; j++) {
                Cell& cell = rows[i].cells[j];
                if (cell.border & B_TOP)
                    result[i << 1][1 + (j * 3)] = result[i << 1][2 + (j * 3)] = '-';
                if (cell.border & B_BOTTOM)
                    result[(i + 1) << 1][1 + (j * 3)] = result[(i + 1) << 1][2 + (j * 3)] = '-';
                if (cell.border & B_LEFT)
                    result[1 + (i << 1)][j * 3] = '|';
                if (cell.border & B_RIGHT)
                    result[1 + (i << 1)][(j + 1) * 3] = '|';
                if (cell.typeNumber) {
                    result[1 + (i << 1)][1 + (j * 3)] = i + '1';
                    result[1 + (i << 1)][2 + (j * 3)] = cell.col + '1';
                }
            }
        }
        //debug << "colCount = " << colCount << '\n';
        for (i = 0; i < (n << 1) + 1; i++) {
            cout.write(result[i], (3 * colCount + 1) * sizeof(char));
            cout << '\n';
        }
        cout << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
