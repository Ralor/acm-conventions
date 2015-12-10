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

struct PathInfo {
    int len;
    int next;

    PathInfo(): len(-1), next(-1) { }
};

#include <csetjmp>

#ifdef _DEBUG
    const int ALPH_SIZE = 3;
#else
    const int ALPH_SIZE = 26;
#endif

bool mx[ALPH_SIZE][ALPH_SIZE];
vector< vector<int> > graph;
PathInfo dp[ALPH_SIZE];
bool processing[ALPH_SIZE];
int loopStart;
//int loopLen;
jmp_buf buf;
char result[20][20];

enum DpResult {
    NOTHING_INTERESTING,
    LOOP_FOUND,
};

DpResult FindPath(int pos) {
    if (dp[pos].len != -1)
        return NOTHING_INTERESTING;
    if (processing[pos]) {
        loopStart = pos;
        //loopLen = 1;
        return LOOP_FOUND;
    }
    processing[pos] = true;
    for (int i = 0; i < (int)graph[pos].size(); i++) {
        debug << char(pos + 'a') << " -> " << char(graph[pos][i] + 'a') << '\n';
        DpResult res = FindPath(graph[pos][i]);
        if (res == LOOP_FOUND) {
            dp[pos].next = graph[pos][i];
            if (pos == loopStart) {
                //Jumping out to the main.
                longjmp(buf, 1);
            } else {
                //loopLen++;
                return LOOP_FOUND;
            }
        }
    }
    int maxI = 0;
    for (int i = 0; i < (int)graph[pos].size(); i++)
        if (dp[graph[pos][i]].len > dp[maxI].len)
            maxI = graph[pos][i];
    //if (maxPath.next != -1)
        //maxPath.len++;
    dp[pos].len = dp[maxI].len + 1;
    dp[pos].next = maxI;
    debug << char(pos + 'a') << ".len = " << dp[pos].len << '\n';
    processing[pos] = false;
    return NOTHING_INTERESTING;
}

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
    int i, j, n;
    while (tests--) {
        memset(mx, 0x01, sizeof mx);
        memset(processing, 0x00, sizeof processing);
        graph.clear();
        graph.resize(ALPH_SIZE);
        loopStart = -1;
        for (i = 0; i < ALPH_SIZE; i++)
            dp[i] = PathInfo();
        cin >> n;
        while (n--) {
            char c0, c1;
            cin >> c0 >> c1;
            mx[c0 - 'a'][c1 - 'a'] = false;
        }
        for (i = 0; i < ALPH_SIZE; i++)
            for (j = 0; j < ALPH_SIZE; j++)
                if (mx[i][j])
                    graph[i].push_back(j);
        int resultSize;
        switch (setjmp(buf)) {
            case 0: {
                //Initial.
                for (i = 0; i < ALPH_SIZE; i++)
                    FindPath(i);
                int cur = 0;
                for (i = 1; i < ALPH_SIZE; i++)
                    if (dp[i].len > dp[cur].len)
                        cur = i;
                debug << "maxLen: " << char(cur + 'a') << ": " << dp[cur].len + 1 << '\n';
                int maxLen = dp[cur].len + 1;
                if (!(maxLen & 0x1))
                    maxLen--;
                resultSize = ((maxLen - 1) >> 1) + 1;
                for (i = 0; i < maxLen; i++, cur = dp[cur].next)
                    for (j = 0; j <= i; j++)
                        if (j < resultSize)
                            result[j][i - j] = cur + 'a';
                break;
            }

            case 1: {
                //A loop is found.
                int maxLen = max(resultSize, 20);
                result[0][0] = loopStart + 'a';
                int cur = dp[loopStart].next;
                for (i = 1; i < maxLen; i++, cur = dp[cur].next)
                    result[0][i] = cur + 'a';
                for (i = 1; i < maxLen; i++) {
                    for (j = 0; j < maxLen - 1; j++) {
                        result[i][j] = result[i - 1][j + 1];
                    }
                    result[i][maxLen - 1] = result[i - 1][0];
                }
                resultSize = 20;
            }
        }
        for (i = 0; i < resultSize; i++) {
            cout.write(result[i], resultSize * sizeof(char));
            cout << '\n';
        }
        debug << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
