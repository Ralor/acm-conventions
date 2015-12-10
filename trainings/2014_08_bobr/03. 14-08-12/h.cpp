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

struct Stream {
    int id;
    int start;
    int end;
    int priority;

    bool Overlaps(const Stream& s) const {
        if (start == s.start)
            return false;//contains.
        if (start < s.start)
            return end > s.start && end < s.end;
        return s.end > start && s.end < end;
    }

    static bool SortByTime(const Stream& a, const Stream& b) {
        return make_pair(a.start, b.end) < make_pair(b.start, a.end);
    }
};

int n;
Stream streams[5000];
int dp[5000][5000];//[startStream][endStream]

//Отрезки не должны лежать один внутри другого!
int Rcsv(int startStream, int endStream) {
    if (startStream >= n || endStream >= n)
        return 0;
    if (dp[startStream][endStream] != -1)
        return dp[startStream][endStream];
    int result;
    if (startStream == endStream) {
        Stream& stream = streams[startStream];
        result = stream.priority;
        for (int curI = startStream + 1; curI < n && streams[curI].start < stream.end; curI++) {
            Stream& cur = streams[curI];
            if (cur.end <= stream.end) {
                
            }
        }
    } else {
        if (streams[startStream].Overlaps(streams[endStream]))
            result = max(Rcsv(startStream, startStream), Rcsv(endStream, endStream));
        else {
            
            result = Rcsv(startStream, startStream) + Rcsv(endStream, endStream);
        }
    }
    return (dp[startStream][endStream] = result);
}

int main() {
#   ifdef _DEBUG
        freopen("h.in", "r", stdin);
#   else
        freopen("h.in", "r", stdin);
        freopen("h.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;
    cin >> n;
    for (i = 0; i < n; i++) {
        int duration;
        cin >> streams[i].start >> duration >> streams[i].priority;
        streams[i].id = i;
        streams[i].end = streams[i].start + duration;
    }
    sort(streams, streams + n, Stream::SortByTime);
    memset(dp, 0xFF, sizeof dp);
    cout << Rcsv(0, n - 1);
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
