#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back

typedef vector<int> vi;
typedef vector<vi> vvi;

void dfs(vvi& a, vi& u, vi& ts, int v) {
	u[v]=1;
	forn(i,a.size())
		if( a[v][i] && !u[i] )
			dfs(a,u,ts,i);
	ts.pb(v);
}

int main() {

	int n,m,u,v;
	while(cin>>n>>m&&n) {
		vvi a(n,vi(n,0));
		forn(i,m)
			cin>>u>>v,--u,--v,a[u][v]=1;
		vi ts, u(n,0);
		forn(i,n)
			if( !u[i] )
				dfs(a,u,ts,i);
		cout<<ts[n-1]+1;
		for(int i=1;i<n;i++)
			cout<<" "<<ts[n-i-1]+1;
		cout<<"\n";
	}

	return 0;
}
