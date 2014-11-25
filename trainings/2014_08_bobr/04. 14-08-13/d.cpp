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

struct Point {
    int col;
    bool used;

    Point(int c = 0): col(c), used(true) { }
};

struct PointPair {
    int row;
    Point min, max;

    PointPair() { }
    PointPair(int r, const Point& mn, const Point& mx): row(r), min(mn), max(mx) { }
};

struct Cell {
    int row, col;

    Cell() { }
    Cell(int r, int c): row(r), col(c) { }
};

enum Dir {
    D_N = 0x1,
    D_E = 0x2,
    D_S = 0x4,
    D_W = 0x8,
};

Dir GetDir(const Cell& a, const Cell& b) {
    if (a.row == b.row)
        return a.col < b.col ? D_E : D_W;
    if (a.col == b.col)
        return a.row < b.row ? D_S : D_N;
    if (a.row < b.row)
        if (a.col < b.col)
            return Dir(D_S | D_E);
        else
            return Dir(D_S | D_W);
    else
        if (a.col < b.col)
            return Dir(D_N | D_E);
        else
            return Dir(D_N | D_W);
}

void Process(const Cell& cell, Dir& dir, const Cell& nextCell) {
    Dir newDir = GetDir(cell, nextCell);
    if (dir == newDir)
        return;
    switch (dir) {
        case D_N:
            if (newDir == D_E) {
                cout << ' ' << cell.row << ' ' << cell.col;
                dir = newDir;
            } else if (newDir == (D_N | D_E)) {
                cout <<
                    ' ' << cell.row << ' ' << cell.col <<
                    ' ' << cell.row << ' ' << cell.col + 10;
                //dir = D_N;
            } else if (newDir == (D_S | D_E)) {
                cout <<
                    ' ' << cell.row << ' ' << cell.col <<
                    ' ' << cell.row << ' ' << cell.col + 9 <<
                    ' ' << nextCell.row << ' ' << nextCell.col - 1;
                dir = D_E;
            }
            break;

        case D_E:
            if (newDir == D_S) {
                cout << ' ' << cell.row << ' ' << cell.col + 9;
                dir = newDir;
            } else if (newDir == (D_S | D_E)) {
                cout <<
                    ' ' << cell.row << ' ' << cell.col + 9 <<
                    ' ' << nextCell.row << ' ' << nextCell.col - 1;
                //dir = D_E;
            } else if (newDir == (D_S | D_W)) {
                cout <<
                    ' ' << cell.row << ' ' << cell.col + 9 <<
                    ' ' << cell.row + 9 << ' ' << cell.col + 9 <<
                    ' ' << cell.row + 9 << ' ' << cell.col - 1;
                dir = D_S;
            }
            break;

        case D_S:
            if (newDir == D_W) {
                cout << ' ' << cell.row + 9 << ' ' << cell.col + 9;
                dir = newDir;
            } else if (newDir == (D_S | D_W)) {
                cout <<
                    ' ' << cell.row + 9 << ' ' << cell.col + 9 <<
                    ' ' << cell.row + 9 << ' ' << cell.col - 1;
                //dir = D_S;
            } else if (newDir == (D_N | D_W)) {
                cout <<
                    ' ' << cell.row + 9 << ' ' << cell.col + 9 <<
                    ' ' << cell.row + 9 << ' ' << cell.col <<
                    ' ' << nextCell.row + 9 << ' ' << nextCell.col + 10;
                dir = D_W;
            }
            break;

        case D_W:
            if (newDir == D_N) {
                cout << ' ' << cell.row + 9 << ' ' << cell.col;
                dir = newDir;
            } else if (newDir == (D_N | D_W)) {
                cout <<
                    ' ' << cell.row + 9 << ' ' << cell.col <<
                    ' ' << nextCell.row + 9 << ' ' << nextCell.col + 10;
                //dir = D_W;
            } else if (newDir == (D_N | D_E)) {
                cout <<
                    ' ' << cell.row + 9 << ' ' << cell.col <<
                    ' ' << cell.row << ' ' << cell.col <<
                    ' ' << cell.row << ' ' << cell.col + 10;
                dir = D_N;
            }
    }
}

int main() {
#   ifdef _DEBUG
        freopen("d.in", "r", stdin);
#   else
        freopen("d.in", "r", stdin);
        freopen("d.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    map<int, PointPair> rowMap;
    vector<PointPair> v;
    vector<Cell> vc;
    int i, n;
    int test = 1;
    while (cin >> n, n) {
        rowMap.clear();
        for (i = 0; i < n; i++) {
            int r, c;
            cin >> r >> c;
            r /= 10;
            c /= 10;
            map<int, PointPair>::iterator lb = rowMap.lower_bound(r);
            if (lb != rowMap.end() && !rowMap.key_comp()(r, lb->first)) {
                if (c < lb->second.min.col)
                    lb->second.min.col = c;
                else if (c > lb->second.max.col)
                    lb->second.max.col = c;
            } else {
                Point p(c);
                rowMap.insert(lb, make_pair(r, PointPair(r, p, p)));
            }
        }
        v.clear();
        v.reserve(rowMap.size());
        for (map<int, PointPair>::iterator it = rowMap.begin(); it != rowMap.end(); it++)
            v.push_back(it->second);
        int lCen = 0, rCen = 0;
        for (i = 1; i < (int)v.size(); i++) {
            if (v[i].min.col < v[lCen].min.col)
                lCen = i;
            if (v[i].max.col > v[rCen].max.col)
                rCen = i;
        }
        int lPrev = v[0].min.col;
        int rPrev = v[0].max.col;
        for (i = 1; i < (int)v.size() - 1; i++) {
            bool lDec = i <= lCen;
            bool rDec = i > rCen;
            if (lDec) {
                if (v[i].min.col > lPrev)
                    v[i].min.used = false;
                else
                    lPrev = v[i].min.col;
            } else {
                if (v[i].min.col < lPrev)
                    v[i].min.used = false;
                else
                    lPrev = v[i].min.col;
            }
            if (rDec) {
                if (v[i].max.col > rPrev)
                    v[i].max.used = false;
                else
                    rPrev = v[i].max.col;
            } else {
                if (v[i].max.col < rPrev)
                    v[i].max.used = false;
                else
                    rPrev = v[i].max.col;
            }
        }
        vc.clear();
        vc.reserve(v.size() << 1);
        vc.push_back(Cell(v[0].row * 10, v[0].min.col * 10));
        //TODO: Check uniquality.
        for (i = 0; i < (int)v.size(); i++)
            if (v[i].max.used && (i || v[0].min.col != v[0].max.col))
                vc.push_back(Cell(v[i].row * 10, v[i].max.col * 10));
        for (i = (int)v.size() - 1; i > 0; i--)
            if (v[i].min.used && (i != (int)v.size() - 1 || v[i].min.col != v[i].max.col))
                vc.push_back(Cell(v[i].row * 10, v[i].min.col * 10));
        cout << "Case " << test++ << ": " << vc[0].row << ' ' << vc[0].col;
        if (v.size() == 1) {
            //The only row.
            cout <<
                ' ' << v[0].row * 10 << ' ' << v[0].max.col * 10 + 9 <<
                ' ' << v[0].row * 10 + 9 << ' ' << v[0].max.col * 10 + 9 <<
                ' ' << v[0].row * 10 + 9 << ' ' << v[0].min.col * 10;
        } else if (GetDir(vc[0], vc[1]) == D_S) {
            //The only column.
            cout <<
                ' ' << vc[0].row << ' ' << vc[0].col + 9 <<
                ' ' << vc[vc.size() - 1].row + 9 << ' ' << vc[vc.size() - 1].col + 9 <<
                ' ' << vc[vc.size() - 1].row + 9 << ' ' << vc[vc.size() - 1].col;
        } else {
            Cell cell = vc[0];
            Dir dir = D_E;
            for (i = 1; i < (int)vc.size(); i++) {
                Cell& nextCell = vc[i];
                Process(cell, dir, nextCell);
                cell = nextCell;
            }
            Process(cell, dir, vc[0]);
        }
        cout << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
