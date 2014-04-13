#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <climits>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <ctime>
#include <cmath>
using namespace std;

typedef long long llong;
typedef unsigned long long ullong;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define spresent(c,v) ( find( all(c), v ) != (c).end() )
#define present(c,v) ( (c).find(v) != (c).end() )
#define sqr(x) ((x)*(x))
#define mp(x,y) make_pair((x),(y))
#define eps 1e-8
#define inf 1000*1000*1000
#define linf 4LL*1000*1000*1000*1000*1000*1000
#define eq(x,y) (fabs(double(x) - double(y)) <= eps)
#define ls(x,y) (double(x) < double(y) && !eq(x,y))
#define gr(x,y) (double(x) > double(y) && !eq(x,y))

int ans[44], N;
void rec(int pos, int prv, int n) {
	if( n == 0 ) {
		cout << ans[0];
		for(int i = 1; i < pos; i++)
			cout << "+" << ans[i];
		cout << "\n";
		return;
	}

	int i = prv;
	while( i <= n - i ) // i <= n/2
		ans[pos] = i, rec(pos+1,i,n-i), ++i;

	if( n == N )
		return;

	ans[pos] = n;
	cout << ans[0];
	for(i = 1; i <= pos; i++)
		cout << "+" << ans[i];
	cout << "\n";
}

int main() {
	//freopen(TASK ".in", "r", stdin);
	//freopen(TASK ".out", "w", stdout);   
	//freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
	//freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);
    ios_base::sync_with_stdio(0);    
	cin.tie(0);
	
	cin >> N;
	rec(0,1,N);

    return 0;
}