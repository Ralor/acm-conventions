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
    int i, n;
    string s;
    set<pair<int, string>> st;
    while (cin >> n, n != -1) {
        st.clear();
        for (i = 0; i < n; i++) {
            int a, b, c;
            cin >> a >> b >> c >> s;
            a *= b * c;
            st.emplace(a, s);
        }
        cout << st.rbegin()->snd << " took clay from " << st.begin()->snd << ".\n";
    }
}