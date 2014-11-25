//Anniversary Party.
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

struct Node {
    int value;
    vector<Node*> children;
    mutable int dp[2] = { -1, -1 };

    explicit Node(int v = 0): value(v) { }

    int Dyn(bool canAttend = true) {
        if (dp[canAttend] != -1)
            return dp[canAttend];
        int result = 0;
        for (auto child: children)
            result += child->Dyn(true);
        if (canAttend) {
            int result1 = value;
            for (auto child: children)
                result1 += child->Dyn(false);
            result = max(result, result1);
        }
        return (dp[canAttend] = result);
    }
};

int n;
vector<Node> nodes;
bitset<6000> isRoot;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;
    nodes.reserve(6000);
    while (cin >> n) {
        nodes.clear();
        isRoot.set();
        for (i = 0; i < n; i++) {
            int x;
            cin >> x;
            nodes.emplace_back(x);
        }
        int a, b;
        while (cin >> a >> b, a || b) {
            a--;
            b--;
            nodes[b].children.push_back(&nodes[a]);
            isRoot[a] = false;
        }
        for (i = 0; !isRoot[i]; i++) { }
        cout << nodes[i].Dyn() << '\n';
    }
}
