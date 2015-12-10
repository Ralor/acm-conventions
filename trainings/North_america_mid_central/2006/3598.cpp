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
    string s;
    vector<pair<string, bitset<26>>> v;
    while (cin >> s, s[0] != '#') {
        v.clear();
        do {
            bitset<26> b;
            for (char c: s)
                b[c - 'a'] = true;
            v.emplace_back(move(s), b);
        } while (cin >> s, s[0] != '*');
        sort(v.begin(), v.end(),
            [ ](const pair<string, bitset<26>>& a, const pair<string, bitset<26>>& b) {
                return a.fst < b.fst;
            }
        );
        while (cin >> s, s[0] != '*') {
            s += '|';
            for (const auto& p: v) {
                bool foundUnsigned = false;
                bool skipAlternative = false;
                for (int i = 0; i < (int)s.length(); i++) {
                    if (!skipAlternative) {
                        if (s[i] == '+') {
                            if (!p.snd[s[++i] - 'a']) {
                                skipAlternative = true;
                                continue;
                            }
                        } else if (s[i] == '-') {
                            if (p.snd[s[++i] - 'a']) {
                                skipAlternative = true;
                                continue;
                            }
                        } else if (islower(s[i]) && p.snd[s[i] - 'a'])
                            foundUnsigned = true;
                    }
                    if (s[i] == '|') {
                        if (!skipAlternative && foundUnsigned) {
                            cout << p.fst << '\n';
                            goto nextQuery;
                        }
                        foundUnsigned = false;
                        skipAlternative = false;
                    }
                }
            }
            cout << "NONE\n";
        nextQuery:
            ;
        }
        cout << "$\n";
    }
}