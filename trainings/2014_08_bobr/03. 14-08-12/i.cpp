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

struct Word {
    int id;
    int count;

    Word(int n = 0, int c = 0): id(n), count(c) { }

    bool operator<(const Word& w) const {
        return count < w.count;
    }

    static bool Predicate(const Word&, const Word&);
};

struct Memory {
    Word words[20000];

    Memory() {
        for (int i = 0; i < 20000; i++)
            words[i] = Word(i);
    }
};

map<string, int> wordMap;
vector<string> words;
queue<Memory*> q;
Memory* lastMap;
Memory sevenDaysMap;

bool Word::Predicate(const Word& a, const Word& b) {
    return make_pair(b.count, words[a.id]) < make_pair(a.count, words[b.id]);
}

int main() {
#   ifdef _DEBUG
        freopen("i.in", "r", stdin);
#   else
        freopen("i.in", "r", stdin);
        freopen("i.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    words.reserve(20000);
    int i;
    string s;
    while (cin >> s) {
        if (s == "<text>") {
            q.push((lastMap = new Memory));
            if (q.size() > 7) {
                Memory* toDel = q.front();
                for (i = 0; i < (int)words.size(); i++)
                    sevenDaysMap.words[i].count -= toDel->words[i].count;
                q.pop();
            }
            while (cin >> s, s != "</text>") {
                if (s.length() < 4)
                    continue;
                map<string, int>::iterator lb = wordMap.lower_bound(s);
                int id;
                if (lb != wordMap.end() && !wordMap.key_comp()(s, lb->first)) {
                    //existing.
                    id = lb->second;
                } else {
                    //new.
                    id = words.size();
                    wordMap.insert(lb, make_pair(s, id));
                    words.push_back(s);
                }
                lastMap->words[id].count++;
                sevenDaysMap.words[id].count++;
            }
        } else if (s == "<top") {
            int howMany;
            cin >> howMany >> s;//"/>"
            priority_queue<Word> pq(sevenDaysMap.words, sevenDaysMap.words + words.size());
            vector<Word> result(1);
            result.reserve(20000);
            Word w = pq.top();
            pq.pop();
            cout << "<top " << howMany << ">\n";
            howMany--;
            result[0] = w;
            int prevCount = w.count;
            while (!pq.empty()) {
                w = pq.top();
                if (howMany <= 0 && w.count != prevCount)
                    break;
                pq.pop();
                howMany--;
                result.push_back(w);
                prevCount = w.count;
            }
            sort(result.begin(), result.end(), Word::Predicate);
            for (i = 0; i < (int)result.size(); i++)
                cout << words[result[i].id] << ' ' << result[i].count << '\n';
            cout << "</top>\n";
        } else if (!s.empty()) {
            cerr << "Invalid command '" << s << "'\n";
            return 0;
        }
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
