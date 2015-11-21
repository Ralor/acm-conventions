#include <bits/stdc++.h>

#define _   << ' ' <<
#define fst first
#define snd second

using namespace std;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& obj) {
#       ifdef LOCAL_DEBUG
            cout << obj << flush;
#       endif
        return *this;
    }

    debug_t& write(const char data[ ], size_t n) {
#       ifdef LOCAL_DEBUG
            cout.write(data, n);
            cout << flush;
#       endif
        return *this;
    }
} debug;

typedef unsigned char       uchar;
typedef basic_string<uchar> ustring;
typedef long long           llong;
typedef unsigned long long  ullong;
typedef long double         ldouble;

string s;
int n;

int GetScore(int pos, int d) {
    while (pos += d, pos >= 0 && pos < n && s[pos] != '.')
        if (s[pos] != '_')
            return 0;
    return 100;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> s, s[0] != '#') {
        n = (int)s.length();
        int score = 0;
        for (int i = 0; i < n; i++)
            if (s[i] == '.')
                score += 100;
            else if (s[i] == '\\')
                score += GetScore(i, 1);
            else if (s[i] == '/')
                score += GetScore(i, -1);
            else if (s[i] == '|')
                score += (GetScore(i, 1) + GetScore(i, -1)) >> 1;
        cout << score / n << '\n';
    }
}