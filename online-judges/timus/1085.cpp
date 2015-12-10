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

	int n,m;
	while(cin>>n>>m){
		vvi g(n);
		while(m--){
			int aa,bb;
			int cnt;cin>>cnt;
			if(cnt==1)continue;
			vi t(cnt);
			forn(i,cnt)cin>>t[i],--t[i];
			forn(i,cnt) forn(j,i) {
				g[t[i]].pb(t[j]);
				g[t[j]].pb(t[i]);
			}
		}

		int k;cin>>k;
		vi fv(k), fm(k), fc(k);
		forn(i,k) {
			int money,vertex,pr; cin>>money>>vertex>>pr,--vertex;
			fv[i]=vertex;
			fm[i]=money;
			fc[i] = pr ? 0 : 4;
		}
		int best_v = -1, best_m = 1000*1000*1000;
		forn(vertex,n) {
			int sum=0;
			forn(start,k) {
				queue<int> q;
				vi u(n,0), d(n, 1000*1000*1000);
				u[fv[start]]=1;
				d[fv[start]]=0;
				q.push(fv[start]);
				while( !q.empty() ){
					int v=q.front();
					q.pop();
					forn(i,sz(g[v])) {
						int nxt=g[v][i];
						if( !u[nxt] ){
							u[nxt]=1;
							d[nxt]=d[v]+fc[start];
							q.push(nxt);
						}
					}
				}
				if( d[vertex] <= fm[start] ) {
					sum+=d[vertex];
				} else {
					sum=-1; break;
				}
			}
			if( sum==-1 )
				continue;
			if( best_v==-1 || best_m>sum ) {
				best_m=sum;
				best_v=vertex;
			}
		}
		if( best_v==-1 ) {
			cout<<"0\n";
		} else {
			cout<<best_v+1<<" "<<best_m<<"\n";
		}
	}

	return 0;
}
