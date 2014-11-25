#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_;
template<typename I> inline void in(I l,I r)
{while(l!=r)cin>>*l,++l;}
template<typename I> inline void out(I l,I r,char D=' ')
{if(l!=r){cout<<*l;while(++l!=r)cout<<D<<*l;}cout<<'\n';}

#define forn(i,n) for(int i=0;i<(n);++i)
#define pb        push_back
#define mp        make_pair
#define sz(x)     int((x).size())
#define all(x)    (x).begin(), (x).end()
#define eps       1e-8
#define inf       (1000 * 1000 * 1000)
#define linf      (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)    ((x) * (x))
#define eq(x, y)  (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)

typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;

namespace Random_conventions {
	// my_variable_name;
	// or
	// myVariableName;

	// void my_function()
	// or
	// void myFunction()

	// class MyClass;

	// void MyClass::my_method()
	// or
	// void MyClass::myMethod()

	// int a = x * (3 + M_PI) / 2 + 0.5;
	// or
	// int a=x*(3+M_PI)/2 + 0.5;

	// T  t,tt,tmp;      // temporary
	// char c;			 // temporary char

	// vector<T> inp; // offline input
	// T result;      // number, array, ... used in answer output/return value

	//if( ... )
	//or
	//if (...)

	// if (...) {
	//
	// } else if (...) {
	//
	// } else {
	//
	//	}

	// forn(i,n) forn(j,n) forn(k,n) {
	// 		i=n; j=n; k=n;
	//		break; continue; // <- always on separate line
	//		// or
	//		goto stop1;
	// }
	// stop1:;
}

namespace Adhoc { // problem/subproblem
	// just code it fast and use one-letter names
	// possible names:
	// int n,m;
	// string s;
	// vi/vvi a,b,c;
	// map<K,V> m;
}

namespace Graphs {
	// n - vertex count
	// m - edge count

	// int u,v, a,b, aa,bb;   // edges (u,v) (a,b) (aa,bb) 0..n-1

	// vvi g(n); 		 // graph of n vertexes
	// vvi u(n), bad(n); // used/bad edges of Graph
	// vvi d(n); 		 // delta array (for edge deleting)

	// vvi a(n,vi(n));        // adjecenty matrix n x n

	// vi u(n,0), used(n,0);  // used
	// vi d(n,0/inf/-inf);    // distance
	// vi p(n,-1);            // parent
	// queue<T> q;			  // bfs queue
	// vi inq(n,0);			  // in queue
	// vi st;                 // dfs stack
	// vi t_in(n), t_out(n);  // dfs time in/out
}

namespace DP {
	// T dp[123][421]; // dp[A][B] = what?  // always commented
	// map<parameter_type,T> dp[123][421];  // to avoid ML
	// dp[i][j] = -1/-inf/-MAX;				// undefined

	// int rec(params)
	//		if( f(params) )
	//      	return ...; // recursion base
	//      if( dp[params] != undefined )
	//          return dp[params]; // memoization
	//      T result;
	//      result = ...;
	//      return dp[params] = result;
}

int main() {
#   ifdef LOCAL_PROJECT
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   endif



    return 0;
}
