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
#define pb       push_back
#define forn(i,n) for(int i = 0;i < (n); i++)
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

struct Vertex {
    int w, h;
    Vertex() { }
    Vertex(int w, int h) : w(w), h(h){ }
};

Vertex dijkstra(const vector<Vertex>& v, const vvi& g, int start, int stop, int start_w, int start_h) {
    int n = sz(g);

    vector<Vertex> fits(n);
    fits[start].w = min(start_w, v[start].w);
    fits[start].h = min(start_h, v[start].h);
    
    vi area(n, -inf);
    area[start] = fits[start].w * fits[start].h;
    
    vi used(n, 0);

    forn(step, n) {
        int max_i = -1;
        forn(i, n)
            if (!used[i] && area[i] != -inf && (max_i == -1 || area[i] > area[max_i]))
                max_i = i;
        
        if (max_i == -1)
            break;

        used[max_i] = 1;

        forn(i, sz(g[max_i])) {            
            int ind = g[max_i][i];            
            int w = min(v[ind].w, fits[max_i].w), 
                h = min(v[ind].h, fits[max_i].h);            
            int nxt_area = w * h;
            if (nxt_area > area[ind]) {
                area[ind] = nxt_area;
                fits[ind].w = w;
                fits[ind].h = h;
            }
        }
    }

    return fits[stop]; // solution exists
}

int main() {
#   ifdef _DEBUG
        freopen("e.in", "r", stdin);
#   else
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c;
    while (cin >> a >> b >> c) {
        vector<pair<int, int>> t;
        t.pb(mp(a, 0)); t.pb(mp(b, 1)); t.pb(mp(c, 2));
        sort(all(t));

        int n; cin >> n;
        vector<Vertex> vert; vert.reserve(n);
        vvi g(n);
        forn(v, n) {
            int w, h; cin >> w >> h;
            vert.pb(Vertex(w, h));
            int k; cin >> k;
            forn(i, k) {
                int ind; cin >> ind; --ind; 
                g[v].pb(ind);
            }            
        }

        //                                            width       height
        Vertex res1 = dijkstra(vert, g, 0, sz(g) - 1, t[0].first, t[1].first);
        Vertex res2 = dijkstra(vert, g, 0, sz(g) - 1, t[1].first, t[0].first);

        vi res(3);
        res[t[0].second] = res1.w;
        res[t[1].second] = res1.h;
        res[t[2].second] = t[2].first;        
        
        if (res1.w * res1.h < res2.w * res2.h)
            swap(res[t[0].second], res[t[1].second]);

        cout << res[0] << " " << res[1] << " " << res[2] << "\n";
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
