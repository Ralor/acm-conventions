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
#ifdef LOCAL_PROJECT
#   include <conio.h>
#endif

#ifndef LOCAL_PROJECT
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
#define mt       make_tuple
#define pb       push_back

using namespace std;

#define forn(i, n) for(int i = 0; i < (n); ++i)

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_;
template<typename I> inline void in(I l,I r)
{while(l!=r)cin>>*l,++l;}
template<typename I> inline void out(I l,I r,char D=' ')
{if(l!=r){cout<<*l;while(++l!=r)cout<<D<<*l;}cout<<'\n';}



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

namespace dsu {
    int data[90003];

    void Build(int n) {
        while (n--)
            data[n] = n;
    }

    int Get(int x) {
        return x == data[x] ? x : (data[x] = Get(data[x]));
    }

    int Unite(int a, int b) {
        a = Get(a);
        b = Get(b);
        if (rand() & 0x1)
            swap(a, b);
        return (data[a] = b);
    }
}

struct Column;

struct ColEdge {
    Column* a;
    Column* b;
    int weight;

    ColEdge() { }
    ColEdge(Column* a, Column* b, int w): a(a), b(b), weight(w) { }
};

struct Column {
    vector<ColEdge> edges;
    vector<int> adjRegions;//sorted
};

struct Region;

struct RegEdge {
    Region* a;
    Region* b;
    int weight;

    RegEdge() { }
    RegEdge(Region* a, Region* b, int w): a(a), b(b), weight(w) { }
};

struct Region {
    int id;
    map<Region*, RegEdge> edges;
    int minOuter;

    Region(): minOuter(INT_MAX) { }

    void Update(Region* adj, int weight) {
        auto it = edges.find(adj);
        if (it != end(edges))
            it->second.weight = min(it->second.weight, weight);
        else
            edges.emplace(adj, RegEdge(this, adj, weight));
    }
};

map<int, Column*> columnMap;
vector<Column> columns;
vector<Region> regions;

Column* RegisterColumn(int x) {
    auto lb = columnMap.lower_bound(x);
    if (lb != end(columnMap) && !columnMap.key_comp()(x, lb->first))
        return lb->second;
    int result = columns.size();
    columns.emplace_back();
    columnMap.insert(lb, make_pair(x, &columns[result]));
    return &columns[result];
}

int main() {
#   ifdef LOCAL_PROJECT
        freopen("g.in", "r", stdin);
#   else
#   endif
    srand((uint)time(nullptr));
    int i, j, n, x;
    vector<Column*> circle;
    columns.reserve(600000);
    regions.reserve(90001);
    while (cin >> n) {
        columnMap.clear();
        columns.clear();
        regions.assign(n, Region());
        dsu::Build(n);
        for (i = 0; i < n; i++) {
            regions[i].id = i;
            int k;
            cin >> k;
            circle.assign(k, nullptr);
            for (j = 0; j < k; j++) {
                cin >> x;
                circle[j] = RegisterColumn(x);
                circle[j]->adjRegions.push_back(i);
            }
            for (j = 1; j < k; j++) {
                cin >> x;
                circle[j]->edges.emplace_back(circle[j], circle[j - 1], x);
                //circle[j - 1]->edges.emplace_back(circle[j], circle[j - 1], x);
            }
            cin >> x;
            circle[0]->edges.emplace_back(circle[0], circle[k - 1], x);
            //circle[k - 1]->edges.emplace_back(circle[0], circle[k - 1], x);
        }
        int regIds[2];
        for (const auto& col: columns)
            for (const auto& edge: col.edges)
                if (set_intersection(begin(edge.a->adjRegions), end(edge.a->adjRegions), begin(edge.b->adjRegions), end(edge.b->adjRegions), regIds) == regIds + 2) {
                    regions[regIds[0]].Update(&regions[regIds[1]], edge.weight);
                    regions[regIds[1]].Update(&regions[regIds[0]], edge.weight);
                } else
                    regions[regIds[0]].minOuter = min(regions[regIds[0]].minOuter, edge.weight);
        map<pair<Region*, Region*>, RegEdge> edgeMap;
        for (const auto& col: regions)
            for (const auto& kv: col.edges) {
                Region* a = kv.second.a;
                Region* b = kv.second.b;
                if (a > b)
                    swap(a, b);
                edgeMap.emplace(make_pair(a, b), kv.second);
            }
        vector<RegEdge> allEdges;
        allEdges.reserve(edgeMap.size());
        for (const auto& kv: edgeMap)
            allEdges.push_back(kv.second);
        sort(begin(allEdges), end(allEdges),
            [ ](const RegEdge& a, const RegEdge& b) {
                return a.weight < b.weight;
            }
        );
        llong result1 = 0;
        for (const auto& e: allEdges) {
            int a = e.a->id;
            int b = e.b->id;
            if (dsu::Get(a) != dsu::Get(b)) {
                dsu::Unite(a, b);
                result1 += e.weight;
            }
        }
        vector<int> outer(n, INT_MAX);
        for (const auto& reg: regions)
            outer[dsu::Get(reg.id)] = min(outer[dsu::Get(reg.id)], reg.minOuter);
        llong sum = 0;
        int count = 0;
        for (int x: outer)
            if (x != INT_MAX) {
                sum += x;
                count++;
            }
        if (count > 1)
            result1 += sum;
        
        llong result2 = 0;
        dsu::Build(n + 1);
        regions.emplace_back();
        regions[n].id = n;
        for (auto& reg: regions)
            if (reg.minOuter != INT_MAX)
                allEdges.emplace_back(&reg, &regions[n], reg.minOuter);
        sort(begin(allEdges), end(allEdges),
            [ ](const RegEdge& a, const RegEdge& b) {
                return a.weight < b.weight;
            }
        );
        for (const auto& e: allEdges) {
            int a = e.a->id;
            int b = e.b->id;
            if (dsu::Get(a) != dsu::Get(b)) {
                dsu::Unite(a, b);
                result2 += e.weight;
            }
        }
        cout << min(result1, result2) << '\n';
    }
#   ifdef LOCAL_PROJECT
        _getch();
#   endif
    return 0;
}
