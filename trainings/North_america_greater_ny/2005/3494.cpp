//3494
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

const int FEB = 1;
const int DAYS[ ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool IsLeap(int y) {
    return !(y & 0x3) && (y % 100 || !(y % 400));
}

struct Date {
    int d, m, y;

    Date& operator++() {
        if (++d >= DAYS[m]) {
            if (m == FEB && d == DAYS[FEB] && IsLeap(y))
                return *this;
            d = 0;
            if (++m == 12) {
                m = 0;
                y++;
            }
        }
        return *this;
    }

    Date& operator--() {
        if (!d--) {
            if (!m--) {
                y--;
                m = 11;
            }
            d = DAYS[m] + (m == FEB && IsLeap(y)) - 1;
        }
        return *this;
    }

    Date operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }

    Date operator--(int) {
        auto temp = *this;
        --*this;
        return temp;
    }

    bool operator==(const Date& rhs) const {
        return d == rhs.d && m == rhs.m;
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        return os << d.m + 1 << '/' << d.d + 1 << '/' << d.y;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    char c;
    for (int ci = 1; ci <= tests; ci++) {
        Date x, y;
        cin >> x.m >> c >> x.d >> c >> x.y >> y.m >> c >> y.d;
        x.d--;
        x.m--;
        y.d--;
        y.m--;
        cout << ci;
        if (x == y) {
            cout << " SAME DAY\n";
            continue;
        }
        Date t = x;
        for (int i = 1; i <= 7; i++) {
            t++;
            if (t == y) {
                cout << ' ' << t << " IS " << i << " DAY";
                if (i != 1)
                    cout << 'S';
                cout << " AFTER\n";
                goto nextCase;
            }
        }
        t = x;
        for (int i = 1; i <= 7; i++) {
            t--;
            if (t == y) {
                cout << ' ' << t << " IS " << i << " DAY";
                if (i != 1)
                    cout << 'S';
                cout << " PRIOR\n";
                goto nextCase;
            }
        }
        cout << " OUT OF RANGE\n";
    nextCase:
        ;
    }
}
