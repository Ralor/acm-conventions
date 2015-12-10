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

struct Station;

struct StPair {
    int colorId;
    Station* fwd;
    Station* bwd;

    StPair(): colorId(0), fwd(NULL), bwd(NULL) { }
    StPair(int c, Station* f, Station* b): colorId(c), fwd(f), bwd(b) { }
};

struct Station {
    int id;
#   ifdef _DEBUG
        string name;
#   endif
    vector<StPair> v;
    int line;
    int len;
};

map<string, int> stationMap;
Station stations[300002];
int stationCount = 0;
map<string, int> colorMap;
int colorCount = 0;

void dfs(Station* cur, Station* prev, int color, int line, int len) {
    if (line == cur->line && len == cur->len)
        return;
    if (line < cur->line || (line == cur->line && len > cur->len)) {
        cur->line = line;
        cur->len = len;
    }
    for (int i = 0; i < (int)cur->v.size(); i++) {
        if (cur->v[i].colorId == color) {
            if (cur->v[i].bwd && cur->v[i].bwd != prev) {
                dfs(cur->v[i].bwd, cur, color, line, len + 1);
            }
            if (cur->v[i].fwd && cur->v[i].fwd != prev) {
                dfs(cur->v[i].fwd, cur, color, line, len + 1);
            }
        } else {
            if (cur->v[i].bwd)  
                if (line + 1 < cur->v[i].bwd->line || (line + 1 == cur->v[i].bwd->line && len + 1 > cur->v[i].bwd->len)) {
                    dfs(cur->v[i].bwd, cur, cur->v[i].colorId, line + 1, len + 1);
                }
            if (cur->v[i].fwd)  
                if (line + 1 < cur->v[i].fwd->line || (line + 1 == cur->v[i].fwd->line && len + 1 > cur->v[i].fwd->len)) {
                    dfs(cur->v[i].fwd, cur, cur->v[i].colorId, line + 1, len + 1);
                }
        }
    }
}

int main() {
#   ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);  
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   else
        freopen("d.in", "r", stdin);
        freopen("d.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
    int tests, i;
    cin >> tests;
    while (tests--) {
        for (i = 0; i < 300002; i++) {
            stations[i].line = INT_MAX;
            stations[i].len = 0;
        }
        string s;
        do
            getline(cin, s);
        while (s.empty());
        istringstream ss(s);
        ss >> s
        if (s != "Stops:") {
            cerr << "Invalid 'Stops:': " << s << '\n';
            exit(1);
        }
        while (ss >> s) {
            if (s[sz(s) - 1] == ',')
                s.resize(sz(s) - 1);
            int id = ++stationCount;
            stations[id].id = id;
            stationMap[s] = id;
#           ifdef _DEBUG
                stations[id].name = s;
#           endif
        }
        debug << "Stations:\n";
        for (map<string, int>::iterator it = stationMap.begin(); it != stationMap.end(); it++)
            debug << it->first << ": " << it->second << '\n';
        do
            getline(cin, s);
        while (s.empty());
        ss.clear();
        ss.str(s);        
        ss >> s;
        if (s != "Lines:") {
            cerr << "Invalid 'Lines:': " << s << '\n';
            exit(1);
        }
        while (ss >> s) {
            if (s[sz(s) - 1] == ',')
                s.resize(sz(s) - 1);
            colorMap[s] = ++colorCount;
        }
        debug << "Colors:\n";
        for (map<string, int>::iterator it = colorMap.begin(); it != colorMap.end(); it++)
            debug << it->first << ": " << it->second << '\n';
        while (true) {
            cin >> s;
            int curColor = colorMap[s];
            cin >> s;
            if (s != "route:")
                break;
            if (!curColor) {
                cerr << "Invalid color name: " << s << '\n';
                exit(1);
            }
            do
                getline(cin, s);
            while (s.empty());
            ss.clear();
            ss.str(s);
            Station* prev = NULL;
            while (ss >> s) {
                if (s[sz(s) - 1] == ',')
                    s.resize(sz(s) - 1);
                int id = stationMap[s];
                if (!id) {
                    cerr << "Invalid station name: " << s << '\n';
                    exit(1);
                }
                stations[id].v.push_back(StPair(curColor, NULL, prev));
                if (prev)
                    prev->v[prev->v.size() - 1].fwd = &stations[id];
                prev = &stations[id];
            }
        }
        string arrivalName, departureName;
        //Johny lives
        cin >> s >> arrivalName;//at somewhere
        Station* startStation = &stations[stationMap[arrivalName]];
        cin >> s >> s >> s >> departureName;//Michelle lives at somewhere
        Station* endStation = &stations[stationMap[departureName]];
        startStation->line = 0;
        startStation->len = 0;
        for (i = 0; i < (int)startStation->v.size(); i++) {
            if (startStation->v[i].bwd)
                dfs(startStation->v[i].bwd, startStation, startStation->v[i].colorId, 1, 1);
            if (startStation->v[i].fwd)
                dfs(startStation->v[i].fwd, startStation, startStation->v[i].colorId, 1, 1);
        }
        cout << "optimal travel from " << arrivalName << " to " << departureName << ": " << endStation->line << " line";
        if (endStation->line > 1)
            cout << 's';
        cout << ", " << endStation->len << " minute";
        if (endStation->len > 1)
            cout << 's';
        cout << '\n';
    }
    return 0;
}
