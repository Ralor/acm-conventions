#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);++i)
#define pb push_back
#define mp make_pair


typedef vector<int> vi;
typedef vector<vi> vvi;

// return true when if cycle found
bool dfs(vvi& a, vi& u, vi& ts, int v) {
	// u[v]==0 // white
	u[v]=1; // gray
	forn(i,a.size())
		if( a[v][i] ) {
			if( u[i]==1 )
				return true;
			if( u[i]==0 && dfs(a,u,ts,i) )
				return true;
		}
	u[v]=2; // black
	ts.pb(v);
	return false;
}

// return false on failure (cycle found)
bool topsort_rec(vvi& a, vi& ts) {
	int n=a.size();
	vi u(n,0);
	forn(i,n)
		if( u[i]==0 && dfs(a,u,ts,i) )
			return false;
	reverse(ts.begin(), ts.end());
	return true;
}

// return false on failure (cycle found)
bool topsort_iter(vvi& a, vi& ts) {
	int n=a.size();
	vi u(n,0);
	vector<pair<int,int>> st; // <vertex,used neighbour>
	forn(ii,n)
		if( u[ii]==0 ) {
			st.pb(mp(ii,-1));
			while( !st.empty() ) {
				int v = st.back().first;
				// u[v]==0 // white
				u[v]=1; // gray
				int& i = st.back().second;
				++i;
				for(i;i<n;i++)
					if( a[v][i] ) {
						if( u[i]==0 )
							break;
						if( u[i]==1 )
							return false;
					}
				if( i==n ) {
					st.pop_back();
					u[v]=2; // black
					ts.pb(v);
				} else {
					st.pb(mp(i,-1));
				}
			}
		}
	reverse(ts.begin(), ts.end());
	return true;
}

template<typename I> void out(I l, I r)
{if(l!=r){cout<<*l;while(++l!=r)cout<<' '<<*l;}cout<<'\n';}

int main() {

	int n,m,u,v;

	while(cin>>n>>m) {
		vvi a(n,vi(n,0));
		forn(i,m) {
			cin>>u>>v,--u,--v;
			a[u][v]=1;
		}
		bool failure=false;
		vi ts1, ts2;
		if( !topsort_rec(a, ts1) ) {
			cout<<"Cycle found (rec)\n";
			failure=true;
		}
		if( !topsort_iter(a, ts2) ) {
			cout<<"Cycle found (iter)\n";
			failure=true;
		}
		if( failure )
			continue;
		forn(i,n)
			++ts1[i], ++ts2[i];
		out(ts1.begin(), ts1.end());
		out(ts2.begin(), ts2.end());
	}


	return 0;
}
