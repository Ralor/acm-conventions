#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);++i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define sz(x) static_cast<int>((x).size())

typedef unsigned int uint;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {

	int n;
	while(cin>>n) {
		vector<vector<pair<uint,uint>>> a(n); // a[i]<ip,netmask>
		forn(i,n) {
			int cnt; cin>>cnt;
			forn(j,cnt) {
				char c;
				uint i1,i2,i3,i4;
				uint n1,n2,n3,n4;
				cin>>i1>>c>>i2>>c>>i3>>c>>i4;
				cin>>n1>>c>>n2>>c>>n3>>c>>n4;
				uint ip = i1*256*256*256 + i2*256*256 + i3*256 + i4;
				uint ms = n1*256*256*256 + n2*256*256 + n3*256 + n4;
				a[i].pb(mp(ip,ms));
			}
		}

		vvi g(n);
		forn(i,n) forn(j,i) {
			forn(ii,sz(a[i])) forn(jj,sz(a[j]))
				if( (a[i][ii].first & a[i][ii].second) == (a[j][jj].first & a[j][jj].second) ) {
					g[i].pb(j); g[j].pb(i); ii = sz(a[i]); jj = sz(a[j]);
					break;
				}
		}

		int from,to;
		cin>>from>>to,--from,--to;
		vi p(n,-1), u(n, 0);
		queue<int> q; q.push(from); u[from] = 1;
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			if( cur == to ) break;
			forn(i,sz(g[cur])) {
				if( !u[g[cur][i]] ){
					p[g[cur][i]]=cur;
					u[g[cur][i]]=1;
					q.push(g[cur][i]);
				}
			}
		}
		if( !u[to] ) {
			cout<<"No\n";
		} else {
			cout<<"Yes\n";
			vi result;
			for(int i = to; i != -1; i = p[i])
				result.pb(i);
			reverse(all(result));
			forn(i,sz(result))
				cout<<result[i]+1<<" ";
			cout<<"\n";
		}
	}

	return 0;
}
