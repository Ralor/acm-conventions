#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <list>
#include <cstring>
#include <iomanip>
#include <climits>
using namespace std;

typedef unsigned int uint;
typedef long long llong;
typedef unsigned long long ullong;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;

#define eps 1e-8
#define inf 1000*1000*1000
#define linf 4LL*1000*1000*1000*1000*1000*1000
#define sqr(x) ((x)*(x))
#define eq(x,y) ((((x)>(y))?(x)-(y):(y)-(x)) <= eps)
#define sz(x) (int((x).size()))
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define mp(x,y) make_pair((x),(y))
#define dbg(x) cout << #x << " : " << x << "\n"

void qSort(vi *a, int mn, int mx) {
	vi &M = *a;
	int l = mn,
		r = mx;
	int x = M[l + rand()%(r-l+1)]; // no hacks please
	while(1)
	{
		while(M[l] < x) l++;  
        while(M[r] > x) r--; 
        if(l <= r)     
			swap(M[l], M[r]), ++l, --r;                     
		if (l >= r) break;
	}
	if (mn < r) qSort(a, mn ,r);
	if (l < mx) qSort(a, l, mx);
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

	// will be checked in future
	srand(0xbeef); rand();
	int n = 15;
	vi a(n); 
	for(int i = 0; i < n; i++) 
		a[i] = rand()%50;

	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";

	qSort(&a,0,n-1);
	
	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";


	return 0;
}