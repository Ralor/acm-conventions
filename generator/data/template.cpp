#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#if 0 //[[[cog
if getch:
    cog.outl("#ifdef " + LOCAL)
    cog.outl("#   include <conio.h>")
    cog.outl("#else")
else:
    cog.outl("#ifndef " + LOCAL)
cog.outl("#   undef VERBOSE")
cog.outl("#endif")
#endif //]]]
//[[[end]]]

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define pb         push_back
#define mp         make_pair
#define eps        1e-8
#define inf        int(1e9)
#define linf       llong(4e18)

#define TIMESTAMP(msg) cerr << "[" msg "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n'

using namespace std;

typedef unsigned char      uchar;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;
typedef pair<int, int>     pii;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;



int main() {
#if 0 //[[[cog
shared_input = debug_in and debug_in == release_in
shared_output = debug_out and debug_out == release_out
if shared_input:
    cog.outl(4 * ' ' + 'freopen("%s", "r", stdin);' % debug_in)
    debug_in = release_in = ""
if shared_output:
    cog.outl(4 * ' ' + 'freopen("%s", "w", stdout);' % debug_out)
    debug_out = release_out = ""
if not (shared_input and shared_output) and (debug_in or debug_out or release_in or release_out):
    if debug_in or debug_out:
        cog.outl("#   ifdef " + LOCAL)
        if debug_in:
            cog.outl(8 * ' ' + 'freopen("%s", "r", stdin);' % debug_in)
        if debug_out:
            cog.outl(8 * ' ' + 'freopen("%s", "w", stdout);' % debug_out)
        if release_in or release_out:
            cog.outl("#   else")
    else:
        cog.outl("#   ifndef " + LOCAL)
    if release_in:
        cog.outl(8 * ' ' + 'freopen("%s", "r", stdin);' % release_in)
    if release_out:
        cog.outl(8 * ' ' + 'freopen("%s", "w", stdout);' % release_out)
    cog.outl("#   endif")
#endif //]]]
//[[[end]]]
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
#if 0 //[[[cog
if getch:
    cog.outl("#   ifdef " + LOCAL)
    cog.outl("        %s();" % getch)
    cog.outl("#   endif")
#endif //]]]
//[[[end]]]
    return 0;
}
