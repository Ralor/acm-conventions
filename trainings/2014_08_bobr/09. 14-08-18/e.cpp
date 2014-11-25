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

struct Node {
    //string name;
    Node* left;
    Node* right;
    bitset<26> exists;
    set<int> positions[26];
    
    Node(const string& name): /*name(name),*/ left(NULL), right(NULL) {
        if (islower(name[0])) {
            static vector<int> v[26];
            for (int i = 0; i < 26; i++)
                v[i].clear();
            for (int i = 0; i < (int)name.length(); i++)
                v[name[i] - 'a'].push_back(i);
            for (int i = 0; i < 26; i++)
                if (!v[i].empty()) {
                    exists[i] = true;
                    positions[i] = set<int>(v[i].begin(), v[i].end());
                }
        }
    }

    void Precalc() {
        if (left) {
            left->Precalc();
            exists |= left->exists;
        }
        if (right) {
            right->Precalc();
            exists |= right->exists;
        }
    }

    int Parse(const string& s, int pos) const {
        if (pos >= (int)s.length() || !exists[s[pos] - 'a'])
            return pos;
        if (left) {
            int next = left->Parse(s, pos);
            if (right)
                next = right->Parse(s, next);
            return next;
        }
        int i = -1;
        while (pos < (int)s.length()) {
            set<int>::const_iterator it = positions[s[pos] - 'a'].upper_bound(i);
            if (it == positions[s[pos] - 'a'].end())
                return pos;
            i = *it;
            pos++;
        }
        return pos;
    }

    void DebugPrint() const {
        debug << /*name <<*/ " <\n";
        if (left)
            left->DebugPrint();
        if (right)
            right->DebugPrint();
        debug << ">\n";
    }
};

map<string, Node*> grammarMapping;

Node* Insert(const string& s) {
    map<string, Node*>::iterator lb = grammarMapping.lower_bound(s);
    if (lb != grammarMapping.end() && !grammarMapping.key_comp()(s, lb->first))
        return lb->second;
    Node* item = new Node(s);
    grammarMapping.insert(lb, make_pair(s, item));
    return item;
}

int main() {
#   ifdef _DEBUG
        freopen("e.in", "r", stdin);
#   else
        freopen("e.in", "r", stdin);
        freopen("e.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    string s, lhs, a, b;
    char c;
    while (tests--) {
        int n;
        cin >> n;
        while (cin.get() != '\n') { }
        while (n--) {
            getline(cin, s);
            //debug << '<' << s << ">\n";
            istringstream ss(s);
            b.clear();
            ss >> lhs >> c >> a >> c >> b;//lhs = a [+ b]
            Node* lhsItem = Insert(lhs);
            Node* aItem = Insert(a);
            Node* bItem = NULL;
            if (!b.empty())
                bItem = Insert(b);
            lhsItem->left = aItem;
            lhsItem->right = bItem;
        }
        cin >> s;
        Node* root = grammarMapping[s];
        root->Precalc();
        //root->DebugPrint();
        cin >> s;
        cout << (root->Parse(s, 0) == s.length() ? "YES\n" : "NO\n");
        map<string, Node*>::iterator it;
        for (it = grammarMapping.begin(); it != grammarMapping.end(); it++)
            delete it->second;
        grammarMapping.clear();
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
