#include <bits/stdc++.h>
using namespace std;

#define in 1000*1000*1000
#define sz(x) static_cast<int>((x).size())
#define forn(i,n) for(int i = 0; i < (n); ++i)
#define pb push_back

typedef vector<int> vi;
typedef vector<vi> vvi;

struct Graph {
	vvi a,g,d,n; // adjacenty, good, deltas, edge number
	vi p; // p(x) where x - vertex
	int edgeCount;
	Graph() : edgeCount(0) { }
	Graph(int n) {
		this->edgeCount = 0;
		this->a.assign(n,vi());
		this->g.assign(n,vi());
		this->d.assign(n,vi());
		this->n.assign(n,vi());
		this->p.assign(n,0);
	}
	void add_edge(int u, int v) {
		d[v].pb(sz(a[u])); a[u].pb(v); n[u].pb(edgeCount); g[u].pb(1); ++p[u];
		d[u].pb(sz(a[v])); a[v].pb(u); n[v].pb(edgeCount); g[v].pb(1); ++p[v];
		++edgeCount;
	}
	void del(int u, int i) {
		int v = a[u][i];
		int j = d[u][i];
		g[u][i] = g[v][j] = 0;
		--edgeCount;
	}
	vi& operator[](const int& index) {
		return a[index];
	}
	bool ok(int u, int i) {
		return g[u][i];
	}
	int num(int u, int i) {
		return n[u][i];
	}
};

namespace DFS {

int cur;

void init() {
	cur = 0;
}

void dfs(Graph& g, vi& perm, int v) {
	forn(i,sz(g[v])) if( g.ok(v,i) ) {
		g.del(v,i); perm[g.num(v,i)] = cur; ++cur;
		dfs(g,perm,g[v][i]);
	}
}

}

int main() {

	int n,m;
	while( cin >> n >> m ) {
		Graph g(n); int aa,bb;
		forn(i,m) cin>>aa>>bb, g.add_edge(aa-1,bb-1);
		vi perm(m); forn(i,m) perm[i] = i;
		DFS::init();
		DFS::dfs(g,perm,0);
		cout<<"YES\n";
		forn(i,m) cout<<perm[i]+1<<" ";
		cout<<"\n";
	}

	return 0;
}
