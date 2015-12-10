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

struct RecursionState {
    bool start;
    int cur;

    RecursionState() { }
    RecursionState(bool b, int x): start(b), cur(x) { }
};

int n;
bool lab[100000];
bool root[100000];
//bool leaf[100000];
int dp[2][100000];//[startingLab][procedure]
vector< vector<int> > graph;
vector<RecursionState> st;

void Dyn() {
    bool start = st.rbegin()->start;
    int cur = st.rbegin()->cur;
    if (dp[start][cur] == -1) {
        if (graph[cur].empty())
            dp[start][cur] = start != lab[cur];
        else {
            int result0 = INT_MIN;
            int result1 = INT_MIN;
            for (int i = 0; i < (int)graph[cur].size(); i++) {
                st.push_back(RecursionState(0, graph[cur][i]));
                Dyn();
                st.push_back(RecursionState(1, graph[cur][i]));
                Dyn();
                bool oneMore = lab[cur] != lab[graph[cur][i]];
                result0 = max(result0, dp[0][graph[cur][i]] + oneMore);
                result1 = max(result1, dp[1][graph[cur][i]] + oneMore);
            }
            dp[0][cur] = result0;
            dp[1][cur] = result1;
        }
    }
    st.pop_back();
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
    int i;
    while (tests--) {
        int m;
        cin >> n >> m;
        memset(root, 0x01, sizeof root);
        //memset(leaf, 0x01, sizeof leaf);
        memset(dp, 0xFF, sizeof dp);
        graph.clear();
        graph.resize(n);
        for (i = 0; i < n; i++) {
            short laboratory;
            cin >> laboratory;
            lab[i] = laboratory == 1;
        }
        while (m--) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            graph[a].push_back(b);
            //leaf[a] = false;
            root[b] = false;
        }
        int result0 = INT_MIN;
        int result1 = INT_MIN;
        for (i = 0; i < n; i++)
            if (root[i]) {
                st.push_back(RecursionState(0, i));
                Dyn();
                st.push_back(RecursionState(1, i));
                Dyn();
                result0 = max(result0, dp[0][i]);
                result1 = max(result1, dp[1][i]);
            }
        /*for (int k = 0; k < 2; k++) {
            for (i = 0; i < n; i++)
                debug << dp[k][i] << ' ';
            debug << '\n';
        }*/
        cout << min(result0, result1) << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
