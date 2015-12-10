#define _USE_MATH_DEFINES
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;

typedef long long int64;
typedef vector<int> vi;
typedef pair<int,int> pii;

#define sz(c) (int((c).size()))
#define all(c) (c).begin(),(c).end()
#define rall(c) (c).rbegin(),(c).rend()
#define spresent(c,v) ( find( all(c) ) != (c).end() )
#define present(c,v) ( (c).find(v) != (c).end() )
#define sqr(x) ((x)*(x))
#define eps 1e-9
#define inf 1000*1000*1000
#define INF 2147483647
#define linf 4LL*1000*1000*1000*1000*1000*1000
#define LINF 9223372036854775807LL

typedef vector<int> lnum;
const int base = 1000*1000*1000;
 
// чтение длинного a из входного потока in
lnum &readLnum(istream &in) {
    lnum *ans = new lnum();
    string s; in >> s;
    for(int i = sz(s); i > 0; i -= 9)
        if( i < 9 )
            (*ans).push_back( atoi(s.substr(0,i).c_str()) );           
         else
            (*ans).push_back( atoi(s.substr(i-9,9).c_str()) );     
    while( sz(*ans) > 1 && (*ans).back() == 0 )
        (*ans).pop_back();
    return *ans;
}
// печать длинного а в выходной поток out
void printLnum(ostream &out, lnum &a) {
    out << (a.empty() ? 0 : a.back());
    for(int i = sz(a)-2; i >= 0; i--)
        out << setw(9) << setfill('0') << a[i];
    out << "\n";
}
// прибавление длинного b к длинному a
void addToLnum(lnum &a, lnum &b) {
    for(int i = 0, carry = 0, len = max(sz(a),sz(b)); i < len || carry; i++) {
        if( i == sz(a) )
            a.push_back(0);
        a[i] += carry + ((i < sz(b)) ? b[i] : 0);
        carry = (a[i] >= base);
        if( carry ) a[i] -= base;
    }
}
// умножение двух чисел, все так же как и на емаксе в "длинная арифметика"
lnum &mulLnum(lnum &a, lnum &b) {
    lnum *ans = new lnum(sz(a) + sz(b));
    lnum &c = *ans;
    for(int i = 0; i < sz(a); i++)
        for(int j = 0, carry = 0; j < sz(b) || carry; j++) {
            int64 cur = c[i+j] + carry + 1LL*a[i]*((j<sz(b)) ? b[j] : 0);
            c[i+j] = int(cur % base);
            carry = int(cur / base);
        }
    while( sz(c) > 1 && c.back() == 0 )
        c.pop_back();
    return *ans;
}
// чтобы не умножать n раз число можно его иногда умножать на само себя
// ведь 2^9 = 2^8 * 2 = 4^4 * 2 = 16^2 * 2
// но более подробно написано на емаксе, "бинарное возведение в степень"
lnum &lnumBinPow(lnum &a, int n) {
    lnum *ans = new lnum(1,1);
    while( n ) {
        if( n&1 )
            (*ans) = mulLnum(*ans,a);
        n >>= 1;
        a = mulLnum(a,a);
    }
    return *ans;
}
 
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);

    lnum a( readLnum(cin) ); // конструктор длинного a
	// инициализируется ссылкой, пришедшей из функции
	int n; cin >> n;
    printLnum(cout, lnumBinPow(a,n));
 
    return 0;
}