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

int num[33], sign[33];
int n, trueVal;
 
void myPrint() {
    for(int i = 0; i < n; i++) {
        cout << num[i];
        if( i < n - 1 )
            cout << char(sign[i]);
    }
    cout << "=" << trueVal << "\n";
}
 
void rec(int step, int val) {
    if( step == n ) {
        if( val == trueVal ) {
            myPrint();
            exit(0);
        }
        else return;
    }
    sign[step] = '+';
    rec(step+1,val+num[step+1]);
    sign[step] = '-';
    rec(step+1,val-num[step+1]);
}
 
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> trueVal;
    for(int i = 0; i < n; i++)
        cin >> num[i];
    rec(0,num[0]);
    cout << "No solution\n";
 
    return 0;
}