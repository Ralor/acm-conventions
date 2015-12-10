//Двоичная яблоня.
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

struct Node;

struct Edge {
    Node* node;
    int weight;

    explicit Edge(Node* n = nullptr, int w = 0): node(n), weight(w) { }
};

struct Node {
    vector<Edge> children;
    mutable int dp[100];//[remaining]
    int id = -1;

    Node() {
        children.reserve(2);
        memset(dp, 0xFF, sizeof dp);
    }

    int Cut(int remaining) {
        if (!remaining)
            return 0;
        if (children.empty())
            return INT_MIN;
        if (dp[remaining] != -1)
            return dp[remaining];
        int result = INT_MIN;
        if (children.size() == 1)
            result = children[0].node->Cut(remaining - 1) + children[0].weight;
        else {
            for (int i = 0; i <= remaining - 2; i++)
                result = max(result,
                    children[0].node->Cut(i) + children[0].weight +
                    children[1].node->Cut(remaining - i - 2) + children[1].weight
                );
            result = max(result, children[0].node->Cut(remaining - 1) + children[0].weight);
            result = max(result, children[1].node->Cut(remaining - 1) + children[1].weight);
        }
        return (dp[remaining] = result);
    }

    void DebugPrint(int space = 0) const {
        for (int i = 0; i < space; i++)
            debug << "  ";
        debug << id << '\n';
        for (const auto& e: children)
            e.node->DebugPrint(space + 1);
    }
};

vector<Node> nodes;
vector<vector<pair<int, int>>> g;

void ConstructTree(int index) {
    nodes[index].id = index;
    for (const auto& child: g[index])
        if (nodes[child.first].id == -1) {
            nodes[index].children.emplace_back(&nodes[child.first], child.second);
            ConstructTree(child.first);
        }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    while (cin >> n >> q) {
        nodes.clear();
        nodes.resize(n);
        g.clear();
        g.resize(n);
        for (int i = 1; i < n; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            a--;
            b--;
            g[a].emplace_back(b, w);
            g[b].emplace_back(a, w);
        }
        ConstructTree(0);
        //nodes[0].DebugPrint();
        cout << nodes[0].Cut(q) << '\n';
    }
}
