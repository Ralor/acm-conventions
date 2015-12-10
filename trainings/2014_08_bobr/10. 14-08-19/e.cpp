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
    int firstChild;
    int childrenCount;
    Node* parent;

    Node(int id, Node* parent = NULL): id(id), parent(parent), childrenCount(0) { }
};

int n, k;
vector<Node> nodes;
Node* nodeMap[(int)1e6 + 1];
Node* q[1001];

int main() {
#   ifdef _DEBUG
        freopen("e.in", "r", stdin);
#   else
        freopen("e.in", "r", stdin);
        freopen("e.out", "w", stdout);
#   endif
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int i;
    while (scanf("%d%d", &n, &k) == 2 && n && k) {
        nodes.clear();
        nodes.reserve(n);
        //nodeMap.clear();
        //memset(nodeMap, 0x00, sizeof nodeMap);
        int qWrite = 0, qRead = 0;
        int x, last;
        scanf("%d", &last);
        nodes.push_back(Node(last));
        nodeMap[last] = &nodes[0];
        q[qWrite++] = &nodes[0];
        Node* current = NULL;
        for (i = 1; i < n; i++) {
            scanf("%d", &x);
            if (x != last + 1) {
                current = q[qRead++];
                current->firstChild = x;
            }
            nodes.push_back(Node(x, current));
            current->childrenCount++;
            nodeMap[x] = &nodes[nodes.size() - 1];
            q[qWrite++] = &nodes[nodes.size() - 1];
            last = x;
        }
        current = nodeMap[k];
        if (!current->parent)
            puts("0");
        else {
            Node* parent = current->parent;
            if (!parent->parent)
                puts("0");
            else {
                Node* grandparent = parent->parent;
                int result = 0;
                for (i = 0; i < grandparent->childrenCount; i++)
                    if (grandparent->firstChild + i != parent->id)
                        result += nodeMap[grandparent->firstChild + i]->childrenCount;
                printf("%d\n", result);
            }
        }
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
