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


// если требуются пояснения, они даны в задаче 1E
typedef vector<int> lnum;
const int base = 1000*1000*1000;
 
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
void printLnum(ostream &out, lnum &a) {
    out << (a.empty() ? 0 : a.back());
    for(int i = sz(a)-2; i >= 0; i--)
        out << setw(9) << setfill('0') << a[i];
    out << "\n";
}
void addToLnum(lnum &a, lnum &b) {
    for(int i = 0, carry = 0, len = max(sz(a),sz(b)); i < len || carry; i++) {
        if( i == sz(a) )
            a.push_back(0);
        a[i] += carry + ((i < sz(b)) ? b[i] : 0);
        carry = (a[i] >= base);
        if( carry ) a[i] -= base;
    }
}
 
int main() {
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
    lnum f( readLnum(cin) );
    lnum s( readLnum(cin) );
 
    addToLnum(f,s);
    printLnum(cout,f);
 
    return 0;
}