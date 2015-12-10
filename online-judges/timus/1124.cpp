#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back

typedef vector<int> vi;
typedef vector<vi> vvi;

int solve(vvi& g, vvi& u, vi& c, vi& st, int vert) {
	int result=0;
	st.push_back(vert);
	while( !st.empty() ) {
		int v = st.back();
		c[v]=1;
		int i;
		for(i=0;i<g[v].size();i++)
			if( !u[v][i] )
				break;
		if( i==g[v].size() ) {
			st.pop_back();
		} else {
			st.pb(g[v][i]);
			u[v][i]=1;
			++result;
		}
	}
	return result;
}

int main() {

	int n,m;
	while(cin>>n>>m) {
		vvi g(n), u(n); int aa;
		forn(i,n) forn(j,m) {
			cin>>aa,--aa;
			if( aa==i ) continue;
			g[i].pb(aa); u[i].pb(0);
		}
		int repl=0, comp=0;
		vi c(n,0), st;
		forn(vert,n)
			if( !c[vert] && !g[vert].empty() && g[vert].size()%2 )
				repl += solve(g,u,c,st,vert), ++comp;
		forn(vert,n)
			if( !c[vert] && !g[vert].empty() )
				repl += solve(g,u,c,st,vert), ++comp;
		cout<<repl+comp-(comp>0)<<"\n";
	}

	return 0;
}
