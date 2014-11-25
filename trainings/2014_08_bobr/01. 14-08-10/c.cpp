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

struct Node {
    vector<int> edges;
    mutable bool used;
    mutable int result;

    int Calc() const;
};

vector<Node> graph;

int Node::Calc() const {
    if (used)
        return result;
    int maxNum = 1;
    bool twoMaxs = false;
    for (int i = 0; i < (int)edges.size(); i++) {
        int x = graph[edges[i]].Calc();
        if (x == maxNum)
            twoMaxs = true;
        else if (x > maxNum) {
            maxNum = x;
            twoMaxs = false;
        }
    }
    used = true;
    return (result = twoMaxs ? maxNum + 1 : maxNum);
}

int main() {
#   ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);  
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   else
        freopen("c.in", "r", stdin);
        freopen("c.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
    int tests;
    cin >> tests;
    while (tests--) {
        int k, n, m;
        cin >> k >> n >> m;
        cout << k << ' ';
        graph.clear();
        graph.resize(n);
        for (int i = 0; i < n; i++)
            graph[i].used = false;
        while (m--) {
            int from, to;
            cin >> from >> to;
            graph[to - 1].edges.push_back(from - 1);
        }
        int last = 0;
        for (int i = 0; i < n; i++) {
            if (!graph[i].used)
                last = i;
            graph[i].Calc();
        }
        cout << graph[last].Calc() << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
