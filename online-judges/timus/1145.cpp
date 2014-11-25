#include <bits/stdc++.h>
using namespace std;

int main() {

	int n,m;
	while(cin>>n>>m){
		swap(n,m);
		const int dr[]={-1,0,1,0};
		const int dc[]={0,1,0,-1};
		vector<string> board(n);
		for(int i=0;i<n;i++)cin>>board[i];
		for(int aa=0;aa<n;aa++)
			for(int bb=0;bb<m;bb++)
				if( board[aa][bb]=='.' ) {
					int best_v=aa*m+bb, best_d=0;
					for(int dfs=0;dfs<2;dfs++) {
						vector<int> st;
						vector<int> u(n*m,0), d(n*m,0);
						st.push_back(best_v);
						d[best_v]=best_d=0;
						while( !st.empty() ) {
							int r = st.back()/m,
								c = st.back()%m,
								v = st.back();
							u[v]=1;
							if( best_d<d[v] ) {
								best_d=d[v];
								best_v=v;
							}
							int i,nxt=-1;
							for(int i=0;i<4;i++) {
								int nr = r+dr[i], nc=c+dc[i];
								int nv = nr*m+nc;
								if( board[nr][nc]=='.' && !u[nv] ) {
									nxt=nv;
									break;
								}
							}
							if( nxt==-1 ) {
								st.pop_back();
							} else {
								st.push_back(nxt);
								d[nxt]=d[v]+1;
							}
						}
					}
					cout<<best_d<<"\n";
					aa=n; bb=m;
				}
	}

	return 0;
}
