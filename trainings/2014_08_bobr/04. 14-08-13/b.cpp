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



int main() {
#   ifdef _DEBUG
        freopen("b.in", "r", stdin);
#   else
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n1, n2, m;
    int caseNum = 1;
    while (true) {
        cin >> n1 >> n2 >> m;
        if (!(n1 || n2 || m))
            break;
        vector<int> t1(n1, -1);
        vector<int> t2(n2, -1);
        while (m--) {
            int x;
            cin >> x;
            vector<int>* v = &t1;
            while (true) {
                int key = x % v->size();
                int temp = v->at(key);
                v->at(key) = x;
                if (temp == -1)
                    break;
                x = temp;
                v = ((v == &t1) ? (&t2) : (&t1));
            }
        }
        cout << "Case " << caseNum++ << ":\n";
        {
            ostringstream out;
            for (int i = 0; i < n1; i++)
                if (t1[i] != -1)
                    out << i << ':' << t1[i] << '\n';
            string s = out.str();
            if (!s.empty())
                cout << "Table 1\n" << s;
        }
        ostringstream out;
        for (int i = 0; i < n2; i++)
            if (t2[i] != -1)
                out << i << ':' << t2[i] << '\n';
        string s = out.str();
        if (!s.empty())
            cout << "Table 2\n" << s;
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
