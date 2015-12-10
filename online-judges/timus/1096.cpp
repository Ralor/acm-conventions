#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);++i)
#define pb push_back
#define mp make_pair
#define sz(x) static_cast<int>((x).size())
#define all(x) (x).begin(), (x).end()
#define inf 1000*1000*1000

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {

	int n;
	while(cin>>n){
		vector<pair<int,int>> m(n);
		forn(i,n)
			cin>>m[i].first>>m[i].second;
		vvi g(n);
		forn(i,n)forn(j,n) {
			int a=m[i].first,
			    b=m[i].second;
			int c=m[j].first,
			    d=m[j].second;
			if( a==c || b==c )
				g[i].pb(j);
			if( c==a || d==a )
				g[j].pb(i);
		}
		int target,a,b; cin>>target>>a>>b;
		queue<int> q;
		vi u(n,0), d(n, -1), p(n, -1);
		forn(i,n)
			if( a==m[i].first || b==m[i].first ) {
				u[i]=1;
				d[i]=0;
				q.push(i);
			}
		while( !q.empty() ) {
			int v=q.front();
			q.pop();
			forn(i,sz(g[v])) {
				int nxt=g[v][i];
				if( !u[nxt] ) {
					u[nxt]=1;
					d[nxt]=d[v]+1;
					p[nxt]=v;
					q.push(nxt);
				}
			}
		}
		int best_v=-1, best_d=1000*1000*1000;
		forn(i,n)
			if( m[i].first==target || m[i].second==target ) {
				if( u[i] && (best_v==-1 || best_d>d[i]) ) {
					best_d=d[i];
					best_v=i;
				}
			}
		if( best_v==-1 ) {
			cout<<"IMPOSSIBLE\n";
			continue;
		}
		vi result;
		for(int v=best_v;v!=-1;v=p[v])
			result.pb(v);
		reverse(all(result));
		cout<<sz(result)<<"\n";
		forn(i,sz(result))
			cout<<result[i]+1<<"\n";
		cout<<"\n";
	}

	return 0;
}
