#include <iostream>
#include <vector>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);++i)

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi g, st;

void make_st(vvi& g, vvi& st, vi& u, int v) {
	int n = g.size();
	u[v] = 1;
	forn(i,n)
		if( !u[i] && g[v][i] ) {
			g[v][i]=g[i][v]=0;
			st[v][i]=st[i][v]=1;
			make_st(g,st,u,i);
		}
}

vvi result;
void gen(vvi& st, vi& bf, vi& u, int a, int b) {
	int n = st.size();
	u[a]=1;
	bf.push_back(a);
	if( a==b )
		result.push_back(bf);
	forn(i,n)
		if( st[a][i] && !u[i] )
			gen(st,bf,u,i,b);
	bf.pop_back();
}

int main() {

	int n,m;
	while(cin>>n>>m){
		vvi g(n,vi(n,0)), st(n,vi(n,0));
		while(m--) {
			int aa,bb;
			cin>>aa>>bb,--aa,--bb;
			g[aa][bb]=g[bb][aa]=1;
		}
		vi u(n,0);
		forn(i,n)
			if( !u[i] )
				make_st(g,st,u,i);
		result.clear();
		vi bf; bf.reserve(200*200);
		for(int i = 0; i < n; i++)
			for(int j = i+1; j < n; j++) {
				if( !g[i][j] )
					continue;
				u.assign(n,0);
				gen(st,bf,u,i,j);
			}
		cout<<result.size()<<"\n";
		forn(i,result.size()) {
			vi& t = result[i];
			cout<<t.size();
			forn(j,t.size())
				cout<<" "<<t[j]+1;
			cout<<"\n";
		}
	}

	return 0;
}
