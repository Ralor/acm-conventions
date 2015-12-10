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
    int i, x, a[15];
    while (cin >> x, x != -1) {
        a[0] = x;
        bool used[100] = { };
        used[x] = true;
        for (i = 1; cin >> a[i], a[i]; i++)
            used[a[i]] = true;
        int result = 0;
        while (i--)
            if (!(a[i] & 0x1) && used[a[i] >> 1])
                result++;
        cout << result << '\n';
    }
}