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

class Mul;

class ResultExpr {
public:
    vector<Mul*> items;
};

/*abstract*/ class Item {
public:
    ~Item() { }

    virtual ResultExpr* Multiply(llong value) const = 0;
};

class Expr: public Item {
public:
    ResultExpr* Multiply(llong value) const {
        ResultExpr* result = new ResultExpr;
        for (int i = 0; i < (int)items.size(); i++) {
            ResultExpr* e = items[i]->Multiply(value);
            for (int j = 0; j < (int)e->items.size(); j++)
                result->items.push_back(e->items[j]);
        }
        return result;
    }
    
    vector<Item*> items;
};

class Mul: public Item {
public:
    ResultExpr* Multiply(llong value) const {
        ResultExpr* result = new ResultExpr;
        result->items.push_back(new Mul);
        result->items[0]->value = this->value * value;
        result->items[0]->var = var;
        return result;
    }

    llong value;
    char var;//'x' | 'y' | '\0'
};

class ComplexMul: public Item {
public:
    ResultExpr* Multiply(llong value) const {
        ResultExpr* result = new ResultExpr;
        value *= multiplier;
        for (int i = 0; i < (int)e->items.size(); i++) {
            ResultExpr* e2 = e->items[i]->Multiply(value);
            for (int j = 0; j < (int)e2->items.size(); j++)
                result->items.push_back(e2->items[j]);
        }
        return result;
    }

    llong multiplier;
    Expr* e;
};

Expr* ParseExpr(const string& s, int& pos) {
    Expr* result = new Expr;
    while (pos < (int)s.length() && s[pos] != ')') {
        bool neg = s[pos] == '-';
        if (neg || s[pos] == '+')
            pos++;
        llong multiplier = 1;
        if (s[pos] >= '0' && s[pos] <= '9') {
            char* end;
            multiplier = strtol(s.c_str() + pos, &end, 10);
            pos = end - s.c_str();
        }
        if (s[pos] == 'x' || s[pos] == 'y') {
            Mul* m = new Mul;
            m->value = neg ? -multiplier : multiplier;
            m->var = s[pos++];
            result->items.push_back(m);
        } else if (s[pos] == '(') {
            ComplexMul* cm = new ComplexMul;
            cm->multiplier = neg ? -multiplier : multiplier;
            cm->e = ParseExpr(s, ++pos);
            result->items.push_back(cm);
        } else {
            Mul* m = new Mul;
            m->value = neg ? -multiplier : multiplier;
            m->var = '\0';
            result->items.push_back(m);
        }
    }
    pos++;
    return result;
}

int main() {
#   ifdef LOCAL_PROJECT
        freopen("h.in", "r", stdin);
#   else
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#   endif
    string s1, s2, s3, s4;
    cout << setprecision(5) << fixed;
    while (getline(cin, s1) && !s1.empty()) {
        getline(cin, s3);
        size_t index = s1.rfind('=');
        s2 = s1.substr(index + 1);
        s1.resize(index);
        index = s3.rfind('=');
        s4 = s3.substr(index + 1);
        s3.resize(index);
        int pos;
        ResultExpr* e1 = ParseExpr(s1, pos = 0)->Multiply(1);
        ResultExpr* e2 = ParseExpr(s2, pos = 0)->Multiply(1);
        ResultExpr* e3 = ParseExpr(s3, pos = 0)->Multiply(1);
        ResultExpr* e4 = ParseExpr(s4, pos = 0)->Multiply(1);
        llong k[6] = { 0 };
        for (int i = 0; i < (int)e1->items.size(); i++) {
            if (e1->items[i]->var == 'x')
                k[0] += e1->items[i]->value;
            else if (e1->items[i]->var == 'y')
                k[1] += e1->items[i]->value;
            else
                k[2] += e1->items[i]->value;
        }
        for (int i = 0; i < (int)e2->items.size(); i++) {
            if (e2->items[i]->var == 'x')
                k[0] -= e2->items[i]->value;
            else if (e2->items[i]->var == 'y')
                k[1] -= e2->items[i]->value;
            else
                k[2] -= e2->items[i]->value;
        }
        for (int i = 0; i < (int)e3->items.size(); i++) {
            if (e3->items[i]->var == 'x')
                k[3] += e3->items[i]->value;
            else if (e3->items[i]->var == 'y')
                k[4] += e3->items[i]->value;
            else
                k[5] += e3->items[i]->value;
        }
        for (int i = 0; i < (int)e4->items.size(); i++) {
            if (e4->items[i]->var == 'x')
                k[3] -= e4->items[i]->value;
            else if (e4->items[i]->var == 'y')
                k[4] -= e4->items[i]->value;
            else
                k[5] -= e4->items[i]->value;
        }
        llong a = k[0];
        llong b = k[1];
        llong c = k[2];
        llong d = k[3];
        llong e = k[4];
        llong f = k[5];
        double denominator = double(a * e - b * d);
        cout << (b * f - c * e) / denominator << '\n' << (c * d - a * f) / denominator << '\n';
        debug << '\n';
    }
#   ifdef LOCAL_PROJECT
        _getch();
#   endif
    return 0;
}
