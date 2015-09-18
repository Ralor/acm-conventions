#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(x) (int((x).size()))
typedef vector<int> vi;
typedef long long llong;

int DigToNumber(char c) {
    if( c <= '9' && c >= '0' )
        return c-'0';
    return c-'A'+10;
}
char NumberToDig(int n) {
    if( n < 10 )
        return '0'+n;
    return n-10+'A';
}

const int base = 1000*1000*1000;

void mulint(vi& a, int b) {
    for(int i = 0, carry = 0; i < sz(a) || carry; i++) {
        if( i == sz(a) )
            a.push_back(0);
        llong cur = carry + a[i] * 1LL * b;
        a[i] = int(cur%base);
        carry = int(cur/base);
    }
    while( sz(a) > 1 && a.back() == 0 )
        a.pop_back();
}
int divint(vi& a, int d) {
    int carry = 0;
    for(int i = sz(a)-1; i >= 0; i--) {
        llong cur = a[i] + carry * 1LL * base;
        a[i] = int(cur/d);
        carry = int(cur%d);
    }
    while( sz(a) > 1 && a.back() == 0 )
        a.pop_back();
    return carry;
}
void add(vi& a, vi& b) {
    for(int i = 0, c = 0, l = max(sz(a),sz(b)); i < l || c; i++) {
        if( i == sz(a) )
            a.push_back(0);
        a[i] += ((i<sz(b))?b[i]:0) + c;
        c = a[i] >= base;
        if( c ) a[i] -= base;
    }
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int from, to; cin >> from >> to;
    string s; cin >> s;
    vi res(1,0); vi m(1,1); vi tmp;
    for(int i = sz(s)-1; i >= 0; i--) {
    	tmp.assign(m.begin(), m.end());
        mulint(tmp,DigToNumber(s[i]));
        add(res,tmp); mulint(m,from);
    }
    vi ans;
    while( sz(res) > 1 || res.back() != 0 )
        ans.push_back(divint(res,to));
    if( sz(ans) == 0 )
        ans.push_back(0);
    for(int i = sz(ans)-1; i >= 0; i--)
        cout << NumberToDig(ans[i]);
    cout << "\n";

    return 0;
}
