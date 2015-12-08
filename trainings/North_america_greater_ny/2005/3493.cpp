//3493
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



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    string a, b, c;
    for (int ci = 1; ci <= tests; ci++) {
        cin >> a >> b;
        c.clear();
        int carry = 0;
        for (int i = 0; carry || i < (int)max(a.length(), b.length()); i++) {
            int x = carry;
            if (i < (int)a.length())
                x += a.rbegin()[i] - '0';
            if (i < (int)b.length())
                x += b.rbegin()[i] - '0';
            c += char((x & 0x1) + '0');
            carry = x >> 1;
        }
        while (c.length() > 1 && c.back() == '0')
            c.pop_back();
        cout << ci << ' ';
        for_each(c.rbegin(), c.rend(), [ ](char c) { cout << c; } );
        cout << '\n';
    }
}
