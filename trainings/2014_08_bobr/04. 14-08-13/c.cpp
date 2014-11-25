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

struct Pos {
    short row, col;
};

vector< vector<char> > table;
bool used[26];
Pos positions[26];
char dummy;

void Push(short i) {
    if (table.empty() || table[table.size() - 1].size() == 5) {
        vector<char> v;
        v.reserve(5);
        v.push_back(i + 'A');
        table.push_back(v);
    } else
        table[table.size() - 1].push_back(i + 'A');
    positions[i].row = table.size() - 1;
    positions[i].col = table[table.size() - 1].size() - 1;
}

char GetNext(const string& s, int i) {
    if (dummy > 'Z')
       dummy = 'A';
    if (i == (int)s.length() - 1)
        return dummy++;
    if (s[i] == s[i + 1]) {
        if (s[i] != dummy)
            return dummy++;
        dummy++;
        return dummy++;
    }
    return s[i + 1];
}

bool is_letter_ok(char c) {
  return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}
char my_to_upper(char c) {
  if( 'A' <= c && c <= 'Z' )
    return c;
  return c-'a' + 'A';
}

int main() {
#   ifdef _DEBUG
        freopen("c.in", "r", stdin);
#   else
        freopen("c.in", "r", stdin);
        freopen("c.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    string s;
    int i;
    table.reserve(5);
    getline(cin, s);
    for (int testNum = 1; testNum <= tests; testNum++) {
        getline(cin, s);
        table.clear();
        memset(used, 0x00, sizeof used);
        for (i = 0; i < (int)s.length(); i++)
            if (is_letter_ok(s[i])) {
                char c = my_to_upper(s[i]);
                if (!used[c - 'A']) {
                    used[c - 'A'] = true;
                    Push(c - 'A');
                }
            }
        for (i = 0; i < 26; i++)
            if (i != 'J' - 'A' && !used[i])
                Push(i);
        getline(cin, s);
        string plain;
        plain.reserve(s.length());
        for (i = 0; i < (int)s.length(); i++)
            if (is_letter_ok(s[i]))
                plain.push_back(my_to_upper(s[i]));
        cout << "Case " << testNum << ": ";
        dummy = 'A';
        for (i = 0; i < (int)plain.length(); i += 2) {
            int temp = dummy;
            char c1 = plain[i];
            char c2 = GetNext(plain, i);
            //debug << c1 << c2 << '\n';
            if (dummy != temp)
                i--;
            Pos p1 = positions[c1 - 'A'];
            Pos p2 = positions[c2 - 'A'];
            if (p1.row == p2.row) {
                if (++p1.col == 5)
                    p1.col = 0;
                if (++p2.col == 5)
                    p2.col = 0;
            } else if (p1.col == p2.col) {
                if (++p1.row == 5)
                    p1.row = 0;
                if (++p2.row == 5)
                    p2.row = 0;
            } else
                swap(p1.col, p2.col);
            cout << table[p1.row][p1.col] << table[p2.row][p2.col];
        }
        cout << '\n';
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
