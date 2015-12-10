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
    int id;
    bool watching;
    bool good;
    int len;
    int num;
};

struct QNode {
    Node* node;
    int num;

    QNode() { }
    QNode(Node* n, int nm): node(n), num(nm) { }

    bool operator<(const QNode& rhs) const {
        return node->len > rhs.node->len;
    }
};

Node nodes[2000];
int mx[2000][2000];

int main() {
#   ifdef _DEBUG
        freopen("k.in", "r", stdin);
#   else
        freopen("k.in", "r", stdin);
        freopen("k.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    priority_queue<QNode> q;
    while (tests--) {
        int i, n, m, t, s, g, h;
        cin >> n >> m >> t >> s >> g >> h;
        s--;
        g--;
        h--;
        memset(mx, 0xFF, sizeof mx);
        for (i = 0; i < n; i++) {
            nodes[i].id = i;
            nodes[i].watching = false;
            nodes[i].good = false;
            nodes[i].len = INT_MAX;
            nodes[i].num = 0;
        }
        for (i = 0; i < m; i++) {
            int a, b, d;
            cin >> a >> b >> d;
            a--;
            b--;
            mx[a][b] = mx[b][a] = d;
        }
        for (i = 0; i < t; i++) {
            int x;
            cin >> x;
            x--;
            nodes[x].watching = true;
        }
        nodes[s].len = 0;
        nodes[s].num = 1;
        q.push(QNode(&nodes[s], 1));
        while (!q.empty()) {
            QNode qn = q.top();
            q.pop();
            debug << qn.node->len << '\n';
            if (qn.num != qn.node->num)
                continue;
            Node* node = qn.node;
            for (i = 0; i < n; i++)
                if (mx[node->id][i] > 0) {
                    bool good = (node->id == h && i == g) || (node->id == g && i == h) || node->good;
                    if (node->len + mx[node->id][i] < nodes[i].len || (good && node->len + mx[node->id][i] == nodes[i].len)) {
                        nodes[i].good = good;
                        nodes[i].len = node->len + mx[node->id][i];
                        q.push(QNode(&nodes[i], ++nodes[i].num));
                    }
                }
        }
        for (i = 0; i < n; i++)
            if (nodes[i].watching && nodes[i].good)
                cout << i + 1 << ' ';
        cout << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
