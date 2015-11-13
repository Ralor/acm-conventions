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

int n;
vector<string> names;
map<string, int> nameMap;
vector<pair<int, int>> v;
int winner;
int rowWidths[5];
int rowStart[5];
int maxDepth;
map<int, map<int, char>> result;

int Register(const string& s) {
    auto it = nameMap.find(s);
    if (it != nameMap.end())
        return it->snd;
    int id = (int)names.size();
    nameMap.emplace(s, id);
    names.push_back(s);
    return id;
}

struct Node;

Node* CreateNode(int, int);

struct Node {
    int teamId;
    int nesting;
    Node* top = nullptr;
    Node* bottom = nullptr;

    Node(int teamId, int nesting): teamId(teamId), nesting(nesting) { }

    void Dfs(int depth) {
        assert(depth < 5);
        maxDepth = max(maxDepth, depth);
        rowWidths[depth] = max(rowWidths[depth], (int)names[teamId].length() + 2);
        if (top) {
            top->Dfs(depth + 1);
            bottom->Dfs(depth + 1);
        }
    }

    void Print(int y, int x, int depth) {
        result[y][x] = '_';
        int x1 = x + 1;
        for (int i = 0; i < (int)names[teamId].length(); i++)
            result[y][x1++] = names[teamId][i];
        while (x1 - x < rowWidths[depth])
            result[y][x1++] = '_';
        if (top) {
            int arcLen = 1 << (maxDepth - depth - 1);
            int y1 = y;
            x1 = x - 1;
            for (int i = 0; i < arcLen; i++)
                result[y1--][x1--] = '\\';
            top->Print(y1, rowStart[depth + 1], depth + 1);
            y1 = y + 1;
            x1 = x - 1;
            for (int i = 0; i < arcLen; i++)
                result[y1++][x1--] = '/';
            bottom->Print(y1 - 1, rowStart[depth + 1], depth + 1);
        }
    }
};

vector<Node> nodes;

Node* CreateNode(int teamId, int nesting) {
    nodes.emplace_back(teamId, nesting);
    return &nodes.back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    names.reserve(16);
    v.reserve(16);
    nodes.reserve(31);
    int i, j;
    string s;
    int ci = 1;
    while (cin >> n, n != -1) {
        names.clear();
        nameMap.clear();
        v.clear();
        result.clear();
        nodes.clear();
        for (i = 0; i < ((n + 1) >> 1) - 1; i++) {
            cin >> s;
            int a = Register(s);
            cin >> s;
            int b = Register(s);
            v.emplace_back(a, b);
        }
        cin >> s;
        winner = nameMap.find(s)->snd;
        Node* curNode[16] = { };
        auto root = CreateNode(winner, 0);
        curNode[winner] = root;
        for_each(v.rbegin(), v.rend(),
            [&](pair<int, int> p) {
                assert(!curNode[p.fst] != !curNode[p.snd]);
                auto node = curNode[p.fst] ? curNode[p.fst] : curNode[p.snd];
                curNode[p.fst] = node->top = CreateNode(p.fst, node->nesting + 1);
                curNode[p.snd] = node->bottom = CreateNode(p.snd, node->nesting + 1);
            }
        );
        fill_n(rowWidths, 5, 0);
        maxDepth = 0;
        root->Dfs(0);
        rowStart[maxDepth] = 0;
        for (i = maxDepth - 1, j = 1; i >= 0; i--, j <<= 1)
            rowStart[i] = rowStart[i + 1] + rowWidths[i + 1] + j;
        cout << "Tournament " << ci++ << '\n';
        for (i = 0; i < 5; i++)
            debug << rowStart[i] << ' ';
        debug << '\n';
        root->Print(0, rowStart[0], 0);
        for (const auto& kv: result) {
            const auto& row = kv.snd;
            int prev = 0;
            for (auto kv: row) {
                for (i = prev; i < kv.fst; i++)
                    cout << ' ';
                cout << kv.snd;
                prev = kv.fst + 1;
            }
            cout << '\n';
        }
        debug << '\n';
    }
}