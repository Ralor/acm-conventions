//3497
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

struct Cmd {
    char type;
    int jmp;

    explicit Cmd(char type): type(type) { }
    Cmd(char type, int jmp): type(type), jmp(jmp) { }
};

char memory[0x8000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (cin.get() != '\n') { }
    string s;
    vector<Cmd> program;
    vector<int> st;
    int ci = 1;
    while (tests--) {
        cout << "PROGRAM #" << ci++ << ":\n";
        program.clear();
        st.clear();
        int p = 0, pos = 0;
        while (getline(cin, s), s != "end") {
            for (char c: s)
                switch (c) {
                    case '>': case '<': case '+': case '-': case '.': {
                        program.emplace_back(c);
                        pos++;
                        break;
                    }
                    case '[': {
                        program.emplace_back('[');
                        st.push_back(pos++);
                        break;
                    }
                    case ']': {
                        if (st.empty())
                            goto error;
                        program.emplace_back(']', st.back() + 1);
                        assert(program[st.back()].type == '[');
                        program[st.back()].jmp = ++pos;
                        st.pop_back();
                        break;
                    }
                    case '%': goto nextLine;
                }
        nextLine:
            ;
        }
        for (auto& cmd: program)
            debug << cmd.type;
        debug << '\n';
        if (!st.empty())
            goto error;
        pos = 0;
        fill_n(memory, 0x8000, 0x00);
        while (pos < (int)program.size()) {
            assert(pos >= 0);
            auto& cmd = program[pos++];
            switch (cmd.type) {
                case '>': {
                    if (++p == 0x8000)
                        p = 0;
                    break;
                }
                case '<': {
                    if (!p--)
                        p = 0x7FFF;
                    break;
                }
                case '+': {
                    memory[p]++;
                    break;
                }
                case '-': {
                    memory[p]--;
                    break;
                }
                case '.': {
                    cout << memory[p];
                    break;
                }
                case '[': {
                    if (!memory[p])
                        pos = cmd.jmp;
                    break;
                }
                case ']': {
                    if (memory[p])
                        pos = cmd.jmp;
                    break;
                }
                default: assert(false);
            }
        }
        cout << '\n';
        continue;
    error:
        cout << "COMPILE ERROR\n";
    }
}
