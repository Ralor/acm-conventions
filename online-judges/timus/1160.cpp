#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define mp make_pair

struct Edge {
	int u,v,w;
	Edge() { }
	Edge(int u, int v, int w) : u(u), v(v), w(w) { }
	bool operator<(const Edge& e) const {
		return w<e.w;
	}
};

namespace DSU {
	int p[1111], r[1111];
	void init(int n = 1111) {
		forn(i,n) p[i]=i, r[i]=0;
	}
	int get(int v) {
		if( p[v]==v )
			return v;
		return p[v]=get(p[v]);
	}
	bool merge(int u, int v) {
		u=get(u); v=get(v);
		if( u!=v ) {
			if( r[u]>r[v] )
				swap(u,v);
			p[u]=v;
			if( r[u]==r[v] )
				++r[v];
			return true;
		}
		return false;
	}
}

int main() {

	int n,m;
	while(cin>>n>>m){
		vector<Edge> edge; edge.reserve(m);
		forn(i,m) {
			int u,v,w;
			cin>>u>>v>>w,--u,--v;
			edge.pb(Edge(u,v,w));
		}
		sort(edge.begin(), edge.end());

		int added=0;
		DSU::init();
		vector<int> cnt; cnt.reserve(m);
		vector<int> mx_pos; mx_pos.reserve(m);
		mx_pos.pb(0);
		forn(i,m) {
			if( DSU::merge(edge[i].u, edge[i].v) )
				++added;
			cnt.pb(added);
			if( edge[mx_pos.back()].w==edge[i].w )
				mx_pos.back()=i;
			else
				mx_pos.pb(i);
		}
		forn(i,mx_pos.size())
			if( cnt[mx_pos[i]]>=n-1 ) {
				cout<<edge[mx_pos[i]].w<<"\n";
				cout<<mx_pos[i]+1<<"\n";
				forn(j,mx_pos[i]+1)
					cout<<edge[j].u+1<<" "<<edge[j].v+1<<"\n";
				break;
			}
	}

	return 0;
}
