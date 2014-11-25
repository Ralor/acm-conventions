#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i = 0; i < (n); ++i)
#define pb push_back
#define sz(x) static_cast<int>((x).size())

typedef vector<int> vi;
typedef vector<vi> vvi;

int dfs(vvi& g, int v, int p = -1) {
	int win = 0;
	forn(i,sz(g[v])) if( g[v][i] != p ) {
		win |= !dfs(g, g[v][i], v);
	}
 	return win;
}

int main() {

	int n,start;
	while(cin>>n>>start){
		vvi g(n); int aa,bb;
		forn(i,n-1)
			cin >> aa >> bb, g[aa-1].pb(bb-1), g[bb-1].pb(aa-1);
		forn(i,n)
			sort(g[i].rbegin(), g[i].rend());
		int where = -1;
		forn(i,sz(g[start-1]))
			if( !dfs(g,g[start-1][i],start-1) )
				where = g[start-1][i];
		if( where==-1 )
			cout<<"First player loses\n";
		else
			cout<<"First player wins flying to airport "<<where+1<<"\n";
	}

	return 0;
}
