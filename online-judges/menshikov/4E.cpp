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

int main() {
	//freopen(TASK ".in", "r", stdin);
	//freopen(TASK ".out", "w", stdout);   
	//freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
	//freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);
    ios_base::sync_with_stdio(0);    
	cin.tie(0);
	
	const int base = 1000*1000*1000;
	vi a; int b;
	string s; cin >> s; cin >> b;
	for(int i = sz(s); i > 0; i-=9)
		if( i < 9 )
			a.push_back( atoi(s.substr(0,i).c_str()) );
		else
			a.push_back( atoi(s.substr(i-9,9).c_str()) );

	int carry = 0;
	for(int i = sz(a) - 1; i >= 0; i--) {
		llong cur = carry * 1LL * base + a[i];
		carry = int(cur%b);
		a[i] = int(cur/b);
	}
	while( sz(a) > 1 && a.back() == 0 )
		a.pop_back();

	cout << ((a.back() == 0) ? 0 : a.back());
	for(int i = sz(a)-2; i >= 0; i--)
		cout << setw(9) << setfill('0') << a[i];
	cout << "\n";
	cout << carry << "\n";

    return 0;
}