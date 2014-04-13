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

void myNextPerm(string &s) {
    int pos1 = -1, pos2 = -1;
    for(int i = sz(s)-1; i > 0; i--)
        if( s[i] > s[i-1] ) {
            pos1 = i-1; break;
        }
    if( pos1 == -1 ) {
        reverse( all(s) ); return;
    }
    for(int i = sz(s)-1; i > pos1; i--)
        if( s[i] > s[pos1] ) {
            pos2 = i; break;
        }
    swap(s[pos1], s[pos2]);
    reverse(s.begin() + pos1 + 1, s.end() );
}
 
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
 
	// аналогично 2В, не вижу разницы
    string s; cin >> s; cout << s << "\n";
    string tmp = s;
    myNextPerm(s);
    while( s != tmp )
        cout << s << "\n", myNextPerm(s);
 
    return 0;
}