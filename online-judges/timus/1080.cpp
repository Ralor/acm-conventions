#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);++i)
#define pb push_back
#define mp make_pair
#define sz(x) static_cast<int>((x).size())

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {

	int n;
	while(cin>>n) {
		vvi g(n); int aa,bb;
		forn(i,n) {
			int tt;
			while(cin>>tt && tt){
				--tt; g[i].pb(tt); g[tt].pb(i);
			}
		}
		vi u(n,0);
		bool ok = true;
		queue<int> q;
		q.push(0); u[0]=1;
		while( !q.empty() && ok ){
			int v=q.front();
			q.pop();
			forn(i,sz(g[v])) {
				int nxt=g[v][i];
				if( u[nxt] && u[nxt]==u[v] ) {
					ok = false; break;
				}
				if( !u[nxt] ) {
					u[nxt] = u[v]==1 ? 2 : 1;
					q.push(nxt);
				}
			}
		}
		if( ok ) {
			forn(i,n)
				cout<<u[i]-1;
			cout<<"\n";
		} else {
			cout<<"-1\n";
		}
	}

	return 0;
}
