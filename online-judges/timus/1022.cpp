#include <bits/stdc++.h>
using namespace std;

#define inf 1000*1000*1000
#define sz(x) static_cast<int>((x).size())
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define forn(i,n) for(int i = 0; i < (n); ++i)

template<typename I>
void out(I l,I r,char A = ' ',char B = '\n') {
	if( l != r ) {
		cout<<*l; while(++l!=r)cout<<A<<*l;
	}
	cout << B;
}

typedef vector<int> vi;
typedef vector<vi> vvi;

void dfs(vvi& g, vi& used, vi& res, int v) {
	used[v] = 1;
	forn(i,sz(g[v])) {
		int nxt = g[v][i];
		if( !used[nxt] )
			dfs(g,used,res,nxt);
	}
	res.pb(v+1);
}

int main() {
	
	int n;
	while( cin >> n ) {
		vvi g(n);
		forn(i,n) { 
			int a; 
			while( cin >> a && a )
				g[i].pb(a-1); 
		}
		vi used(n,0), result; result.reserve(n);
		forn(i, n) 
			if( !used[i] ) 
				dfs(g,used,result,i);
		reverse(all(result));
		out(all(result));
	}
	
	return 0;
}