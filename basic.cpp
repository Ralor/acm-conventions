// --------------------------
// inlcude
// --------------------------
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
// scanf/printf 
#include <iostream>
#include <cstdio>
// fabs, sqrt, log
#include <cmath>
// sort
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
// --------------------------
using namespace std;

// --------------------------
// types
// --------------------------

// just for bit operations (simplify debugging it with calc in programmer mode)
typedef unsigned int uint;

// use ullong when values can't be < 0
typedef long long llong;
typedef unsigned long long ullong;
// better than int64 & uint64 (no numbers)

// extremely hard to debug 
// just for high speed coding
// and dynamic allocation
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
// preferred array types (global, static):
// double [], [][]
// int [], [][]
// string, char[], string []
//
// char[] for recursion, output by for(i..len). Use printf when you can't get "len", but '\0' is ok
// no [2][][] (just for dp), use fname[][], sname[][]
// 
// don't use float, size_t, short, void*, long etc (just for very small ML)
//
// *********
// question:
// what's better?
//
// rand()/double(RAND_MAX)
// rand()*1.0/RAND_MAX
// 
// a[i] * 1LL * b[i]
// a[i] * llong(b[i]);
// we must choose one of them and forget about other
// I prefer 1LL/1ULL/1.0
// I's easy and suitable for ullong a += 1LL (int may overflow in several cases)
// but I'm not sure whether compiler choose (double) for 1.0 (not float)
// --------------------------

// --------------------------
// macro
// --------------------------
#define eps 1e-8
// no problems with inf+inf for int and linf+linf for llong
// use ULLONG_MAX for ullong (it must be >= 0 anyway)
#define inf 1000*1000*1000
#define linf 4LL*1000*1000*1000*1000*1000*1000
#define sqr(x) ((x)*(x))
// may use fabs() if cmath included
#define eq(x,y) ((((x)>(y))?(x)-(y):(y)-(x)) <= eps)
// no warnings and type casting in solution
#define sz(x) (int((x).size()))
// sort(all(a)) is better than sort(a.begin(), a.end())
#define all(x) (x).begin(), (x).end()
// sort(rall(x)) 
// firstValuePos = find(all(x), value) - x.begin() // == sz(x) if not present
// lastValuePos = x.rend() - find(rall(x),value) - 1/ / == -1 if value not present
// lastValuePosFromEnd = find(rall(x), value) - x.rbegin() // == sz(x) if value not present
#define rall(x) (x).rbegin(), (x).rend()
#define mp(x,y) make_pair((x),(y))
#define dbg(x) cout << #x << " : " << x << "\n"
// --------------------------

// -------------------------
// data structures
// -------------------------
// don't use pair<>, never
// just in case when you're asked to sort N[] = (ai,bi) and send it to output
// in normal case it's
struct MinimalEx {
	int a,b;
	MinimalEx() {} // for vector<MinimalEx> arr. And usually cin >> arr[i].a >> arr[i].b goes next.
	// and sometimes second can help
	MinimalEx(int a, int b) : a(a), b(b) {} // push_back(MinimalEx(1,1)) and other
	// use const type& a if "a" is a big string or smth else
};
bool cmp(const MinimalEx& ii, const  MinimalEx& jj) {
	return mp(ii.a, ii.b) < mp(jj.a, jj.b);
	// gcc -O2 makes it the same as
	return (ii.a == jj.a) ? ii.b < jj.b : ii.a < jj.a;
}
// 
// never try to go in situation when you need to cast one structure to another
// use one big for all operations, if their purposes intersects 
// (Tree with pointer to array of childrens may have int type = 1,2,3, instead of 3 types of Trees)
// -------------------------

// --------------------------
// declaring constant values
// --------------------------
// better than enum
// no mess with different types declaration
const int UNDEFINED_INDEX = -1;
const double SOME_MULTIPIER = 0.123456;
// better than char[] because of functions and operators
const string RES_NO = "Impossible!";

// bfs on grid
const int dSz = 4;
// delta row, col
// clockwise priority by default
// values for case when (0,0) if left up corner
const int dr[] = {-1,0,1,0};
const int dc[] = {0,1,0,-1};
// -------------------------

// -------------------------
// function calls
// -------------------------
// usual recursion or dp, may use exit(0)
int n;
// char/int res[111]; to save generated results, mb it's {([])()} or smth else like this
int dp[111][111]; // dp[pos][value] // write such comment while thinking about states
int rec(int pos, int value) { // and declare same variables
	// check indexes first
	if( pos < 0 )
		return 0;
	if( pos == n ) // or send "res" to output here
		return 1; 
	// reuse calculated values (if you need)
	// you don't need it if you generate some strings or sequences in "res",
	if( dp[pos][value] != -1 ) 
		return dp[pos][value];
	int ret = 0;
	// start making decisions... 
	// ret = max(ret, rec(pos..n-1, 1..value) ) or just ret = max(a,b), It depends.
	return dp[pos][value] = ret;
}

// functions makes code slower
// but sometimes it's very hard to write it under if( )
int isPrime(int x) { // O(sqrt(x))
	if( x < 2 )
		return 0;
	if( x == 2 )
		return 1;
	for(llong i = 3; i*i <= x; i+=2) // int is enought for most cases, but not always
		if( x%i == 0 )
			return 0;
	return 1; // I mean don't use bool
}
// use short names, don't try to make it faster using &,* when it's not really needed
int isLetter(char a) {
	return 'A' <= a && a <= 'Z' || 'a' <= a && a <= 'z';
}
// use & when you need to avoid creation of object copy
// or change it actual value in function
void rmSpaces(string &s) { 
	for(int i = 0; i < sz(s); i++)
		if( s[i] == ' ' )
			s.erase(i,1), --i;
}
// if you can't declare object in global scape 
// but need to make recursive call
// use pointers in such way
void someRec(string *s, int val) {
	string &c = *s;

	// no (*s)[0] or s->at(0), just
	c[0] = 1; 
	c.insert(0,val,'A'+val);
	c.insert(sz(c)-1,val,'A'+val);
	// etc..
	// it's useful for tree traversing, merging or smth mb (never seen)
	
	someRec(s);
}
// -------------------------

int main() {
	//freopen(TASK ".in", "r", stdin);
	//freopen(TASK ".out", "w", stdout);  
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	//freopen("info.txt","r",stdin);
	//freopen("info.txt","w",stdout);
	ios_base::sync_with_stdio(0);    
	cin.tie(0);



	return 0;
}