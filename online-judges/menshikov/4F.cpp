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

bool isOpen(char c) {
	return c == '(' || c == '{' || c == '[';
}
char rev(char c) {
	if( c == '(' ) return ')';
	if( c == '{' ) return '}';
	if( c == '[' ) return ']';
	if( c == ']' ) return '[';
	if( c == '}' ) return '{';
	if( c == ')' ) return '(';
	return 0;
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

	int n; cin >> n;
	string s; cin >> s;
	
	stack<char> st;
	for(int i = 0; i < n; i++) 
		if( isOpen(s[i]) )
			st.push(s[i]);
		else {
			if( st.empty() || st.top() != rev(s[i]) )
				cout << "No" << "\n", exit(0);				
			else
				st.pop();
		}
	cout << ((st.empty()) ? "Yes" : "No") << "\n";

    return 0;
}