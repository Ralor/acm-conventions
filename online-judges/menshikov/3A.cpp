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


int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
	
    int n; cin >> n;
    vector<int> ans;
	// важно не забыть про int64, ведь верхняя граница n
	// на пределе типа int32
    for(int64 i = 2; i*i <= n; i++)
        while( n%i == 0 )
            ans.push_back(i), n /= i; 
    // число может просто остаться, а может n вообще само простое
	if( n > 1 ) ans.push_back(n); 

    for(int i = 0; i < sz(ans) - 1; i++)
        cout << ans[i] << "*";
    cout << ans.back() << "\n";
 
    return 0;
}