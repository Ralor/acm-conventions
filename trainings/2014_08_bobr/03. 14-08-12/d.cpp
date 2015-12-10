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

/*
void invert(const char s[ ], int len, string& res) {
    res.clear();
    res.reserve(len);
    for (int i = len - 1; i >= 0; i--)
        res += s[i] == 'R' ? 'L' : 'R';
}
*/

struct SubString {
    const char* s;
    int len;
    bool fwd;

    SubString(const char* str, int len, bool fwd = true): s(str), len(len), fwd(fwd) { }

    int Cmp(const SubString& a) const {
        const char* p = s;
        const char* p2 = a.s;
        int lim = min(len, a.len);
        for (int i = 0; i < lim; i++) {
            if (*p < *p2)
                return -1;
            if (*p > *p2)
                return 1;
            if (fwd)
                p++;
            else
                p--;
            if (a.fwd)
                p2++;
            else
                p2--;
        }
        if (len != a.len)
            return len < a.len ? -1 : 1;
        return 0;
    }

    bool operator==(const SubString& a) const {
        if (len != a.len)
            return false;
        if (s == a.s && fwd == a.fwd)
            return true;
        return !Cmp(a);
    }

    bool operator<(const SubString& a) const {
        return Cmp(a) < 0;
    }
};

char Ls[102];
map<SubString, short> cache;

bool check(int num, SubString s) {
    if (num <= 0)
        return false;
    char c = s.fwd ? 'L' : 'R';
    if (!s.len || (s.len == 1 && *s.s == c))
        return true;
    map<SubString, short>::iterator lb = cache.lower_bound(s);
    if (lb != cache.end() && !cache.key_comp()(s, lb->first)) {
        if (num >= lb->second)
            return true;
        else if (lb->second == SHRT_MAX)
            return false;
    }
    bool f = false;
    const char* s2 = s.s;
    for (int i = 0; i < s.len; i++) {
        if (*s2 == c) {
            f = true;
            if (check(num - 1, SubString(s.s, i, s.fwd)) && /*
            */ check(num - 1, SubString(s.s + s.len - 1, s.len - i - 1, !s.fwd)))
                cache.insert(lb, make_pair(s, num));
                return true;
        }
        if (s.fwd)
            s2++;
        else
            s2--;
    }
    if (!f)
        return check(num - 1, SubString(Ls, s.len));
    cache.insert(lb, make_pair(s, SHRT_MAX));
    return false;
}

int main() {
#   ifdef _DEBUG
        freopen("d.in", "r", stdin);
#   else
        freopen("d.in", "r", stdin);
        freopen("d.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    int num = 1;
    memset(Ls, 'L', sizeof Ls);
    while (tests--) {
        int n;
        string s;
        cin >> n >> s;
        cout << "Case " << num++ << ": " << (check(n, SubString(s.data(), s.length())) ? "Yes" : "No") << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
