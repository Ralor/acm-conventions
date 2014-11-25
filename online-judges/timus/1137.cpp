#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {

	int n;
	while(cin>>n){
		const int maxn=10*1000+1;
		vector<set<int>> gg(maxn);
		vi ideg(maxn,0), odeg(maxn);
		map<int,int> nti; vi itn(maxn);
		while(n--) {
			int cnt,aa,prv=-1;
			cin>>cnt,++cnt;
			while(cnt--) {
				cin>>aa;
				if( nti.count(aa) ) {
					aa=nti[aa];
				} else {
					int id = nti.empty() ? 0 : nti.size();
					nti[aa]=id;
					itn[id]=aa;
					aa=id;
				}
				if( prv!=-1 && gg[prv].find(aa)==gg[prv].end() ) {
					gg[prv].insert(aa);
					++odeg[prv];
					++ideg[aa];
				}
				prv=aa;
			}
		}
		n = nti.size();
		vvi g(n), u(n);
		for(int i=0;i<n;i++) {
			g[i].assign(gg[i].begin(), gg[i].end());
			u[i].assign(g[i].size(), 0);
		}
		for(int i=0;i<n;i++)
			if( ideg[i]!=odeg[i] ) {
				n=-1;
			}
		if( n==-1 ) {
			cout<<"0\n";
			continue;
		}
		vi st, result;
		st.push_back(0);
		while( !st.empty() ) {
			int v=st.back();
			int i;
			for(i=0;i<g[v].size();i++)
				if( !u[v][i] )
					break;
			if( i==g[v].size() ) {
				result.push_back(v);
				st.pop_back();
			} else {
				st.push_back(g[v][i]);
				u[v][i]=1;
			}
		}
		reverse(result.begin(), result.end());
		cout<<result.size()-1;
		for(int i=0;i<result.size();i++)
			cout<<" "<<itn[result[i]];
		cout<<"\n";
	}

	return 0;
}
