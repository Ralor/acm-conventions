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

#pragma comment(linker,"/STACK:512000000000")

typedef long long int64;
typedef vector<int> vi;
typedef pair<int,int> pii;

#define sz(c) int((c).size())
#define all(c) (c).begin(),(c).end()
#define rall(c) (c).rbegin(),(c).rend()
#define spresent(c,v) ( find( all(c) ) != (c).end() )
#define present(c,v) ( (c).find(v) != (c).end() )
#define sqr(x) (x)*(x)
#define eps 1e-8
#define inf 1000*1000*1000
#define linf 9LL*1000*1000*1000*1000*1000*1000
#define eq(x,y) (fabs(double(x) - double(y)) <= eps)
#define le(x,y) (double(x) < double(y) && !eq(x,y))
#define gr(x,y) (double(x) > double(y) && !eq(x,y))

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);       

    ios::sync_with_stdio(0);
    cin.tie(0);

	int m,n; cin >> m >> n;
    int ok = 0;
    for(int p = 2; p <= 24; p++) {
 
        int a = 1 << (p-1), b = (1<<p) - 1;
        int c = a*b;
        int sum = 1, i;
        for(i = 2; i*i <= c; i++)
            if( c % i == 0 )
                sum += i, sum += c/i;
        --i; if( i*i == c ) sum -= i;
        if( sum == c && sum >= m && sum <= n )
            cout << c << "\n", ok = 1;
    }
    if( !ok ) cout << "Absent";
    cout << "\n";

    return 0;
}