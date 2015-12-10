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

const enum {
    LOW, MIDDLE, HIGH, UNKNOWN
} TUNES[10] = { LOW, LOW, UNKNOWN, UNKNOWN, MIDDLE, MIDDLE, UNKNOWN, UNKNOWN, HIGH, HIGH };

/*
    0 -> 1 [mid];
    1 -> 2 [mid];
    2 -> 2 [mid];
    2 -> 3 [low];
    3 -> 0 [high] [!];
    3 -> 1 [mid];
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    int ci = 1;
    while (tests--) {
        cout << "Program " << ci++ << '\n';
        int cs = 0;
        int curTime = 0;
        int i, x, y;
        while (cin >> x, x != 10) {
            int c = TUNES[x];
            switch (cs) {
                case 0: {
                    if (c == MIDDLE)
                        cs = 1;
                    break;
                }
                case 1: {
                    cs = c == MIDDLE ? 2 : 0;
                    break;
                }
                case 2: {
                    if (c == LOW)
                        cs = 3;
                    else if (c != MIDDLE)
                        cs = 0;
                    break;
                }
                case 3: {
                    if (c == MIDDLE)
                        cs = 1;
                    else {
                        if (c == HIGH) {
                            int startTime = (curTime - 3) / 3;
                            cout << setw(2) << setfill('0') << startTime / 60 << ':';
                            cout << setw(2) << setfill('0') << startTime % 60 << " Speed ";
                            int z = 0x0;
                            for (i = 0; i < 3; i++) {
                                cin >> x >> y;
                                assert(x != 10 && y != 10);
                                if (TUNES[x] == LOW && TUNES[y] == HIGH)
                                    z |= 1 << i;
                                else
                                    assert(TUNES[x] == MIDDLE && TUNES[y] == MIDDLE);
                            }
                            cout << z << " Inclination ";
                            z = 0x0;
                            for (i = 0; i < 3; i++) {
                                cin >> x >> y;
                                assert(x != 10 && y != 10);
                                if (TUNES[x] == LOW && TUNES[y] == HIGH)
                                    z |= 1 << i;
                                else
                                    assert(TUNES[x] == MIDDLE && TUNES[y] == MIDDLE);
                            }
                            cout << z << '\n';
                            curTime += 12;
                        }
                        cs = 0;
                    }
                    break;
                }
                default: assert(false);
            }
            curTime++;
        }
        debug << '\n';
    }
}