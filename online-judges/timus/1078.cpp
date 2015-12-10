//Отрезки.
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

struct Line {
    int id;
    int a, b;
    vector<Line*> inner;
    mutable int dp = -1;

    Line() { }

    Line(int id, int a, int b): id(id), a(a), b(b) {
        if (a > b)
            swap(a, b);
    }

    bool Contains(const Line& another) const {
        return a < another.a && b > another.b;
    }
    
    int Dyn() const {
        if (dp != -1)
            return dp;
        int result = 0;
        for (auto line: inner)
            result = max(result, line->Dyn());
        return (dp = result + 1);
    }
};

int n;
vector<Line> lines;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, j;
    lines.reserve(500);
    while (cin >> n) {
        lines.clear();
        for (i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            lines.emplace_back(i, a, b);
        }
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (lines[i].Contains(lines[j]))
                    lines[i].inner.push_back(&lines[j]);
        int best, result = INT_MIN;
        for (i = 0; i < n; i++)
            if (lines[i].Dyn() > result)
                result = lines[best = i].Dyn();
        cout << result << '\n';
        vector<int> st = { best };
        auto line = &lines[best];
        while (line->Dyn() != 1) {
            for (auto line2: line->inner)
                if (line2->Dyn() == line->Dyn() - 1) {
                    line = line2;
                    break;
                }
            st.push_back(line->id);
        }
        for_each(st.rbegin(), st.rend(), [ ](int x) { cout << x + 1 << ' '; } );
        cout << '\n';
    }
}
