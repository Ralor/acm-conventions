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
    Node* parent;
    vector<int> nodes;
    int weight;
    int childrenSum;
    bool used;
};

int n;
vector<Node> elements;
vector<Node*> sorted;
int mx[1000][1000];
//int dp[1000];

/*int Rcsv(int index) {
    if (dp[index] != -1)
        return dp[index];
    Node& node = elements[index];
    int result = 0;
    for (int i = 0; i < (int)node.edges.size(); i++) {
        int sub = node.edges[i].weight;
        if (!elements[node.edges[i].node].edges.empty())
            sub = min(sub, Rcsv(node.edges[i].node));
        result += sub;
    }
    return (dp[index] = result);
}*/

/*void PrintTree(int index, int spaces = 0) {
    for (int i = 0; i < spaces; i++)
        debug << "  ";
    debug << index + 1 << '\n';
    for (int i = 0; i < (int)elements[index].edges.size(); i++)
        PrintTree(elements[index].edges[i].node, spaces + 1);
}*/

void TopSort(int node) {
    for (int i = 0; i < (int)elements[node].nodes.size(); i++)
        if (!elements[elements[node].nodes[i]].used) {
            int another = elements[node].nodes[i];
            elements[another].used = true;
            //debug << node + 1 << " -> " << i + 1 << " (" << mx[node][i] << ")\n";
            elements[another].parent = &elements[node];
            elements[another].weight = mx[node][another];
            //mx[node][another] = mx[another][node] = 0;
            TopSort(another);
            sorted.push_back(&elements[another]);
        }
}

int main() {
#   ifdef _DEBUG
        freopen("g.in", "r", stdin);
#   else
        freopen("g.in", "r", stdin);
        freopen("g.out", "w", stdout);
#   endif
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int i, root;
    //elements.push_back(Node());
    while (/*cin >> n >> root*/ scanf("%d%d", &n, &root) == 2) {
        elements.resize(n);
        sorted.clear();
        //memset(mx, 0x00, sizeof mx);
        //memset(dp, 0xFF, sizeof dp);
        root--;
        for (i = 0; i < n; i++) {
            elements[i].nodes.clear();
            elements[i].childrenSum = 0;
            elements[i].used = false;
        }
        for (i = 1; i < n; i++) {
            int u, v, w;
            //cin >> u >> v >> w;
            scanf("%d%d%d", &u, &v, &w);
            u--;
            v--;
            mx[u][v] = mx[v][u] = w;
            elements[u].nodes.push_back(v);
            elements[v].nodes.push_back(u);
        }
        elements[root].used = true;
        TopSort(root);
        for (i = 0; i < n - 1; i++) {
            Node* node = sorted[i];
            int s = node->weight;
            if (node->childrenSum)
                s = min(s, node->childrenSum);
            node->parent->childrenSum += s;
        }
        printf("%d\n", elements[root].childrenSum);
        //debug << "tree:\n";
        //PrintTree(root);
        //debug << '\n';
        //debug << "(empty: " << (elements[0].edges.empty() ? "true" : "false") << ")\n";
        //cout << Rcsv(0) << '\n';
        //printf("%d\n", Rcsv(0));
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
