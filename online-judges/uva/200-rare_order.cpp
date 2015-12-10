#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define mp make_pair

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {

	while(1){
		vector<string> inp;
		string s;
		set<char> sym;
		while( getline(cin,s) && s!="#" )
			inp.pb(s), sym.insert(s.begin(), s.end());
		if( inp.empty() )
			break;
		int id=0;
		map<char,int> sid;
		map<int,char> ids;
		for(char c : sym)
			sid[c]=id,ids[id]=c,++id;
		int n=sym.size();
		vvi g(n);
		forn(i,inp.size()-1) {
			int j=0;
			while( j<inp[i].size() && j<inp[i+1].size() && inp[i][j]==inp[i+1][j] )
				++j;
			if( j<inp[i].size() && j<inp[i+1].size() )
				g[sid[inp[i][j]]].pb(sid[inp[i+1][j]]);
		}
		vi u(n,0);
		vi topsort;
		forn(i,n) {
			if( u[i] )
				continue;
			vector<pair<int,int>> st;
			st.pb(mp(i,0));
			while( !st.empty() ) {
				int v=st.back().first;
				int& ii=st.back().second;
				u[v]=1;
				while( ii<g[v].size() && u[g[v][ii]] )
					++ii;
				if( ii==g[v].size() ) {
					st.pop_back();
					topsort.pb(v);
				} else {
					st.pb(mp(g[v][ii],0));
				}
			}
		}
		forn(i,n)
			cout<<ids[topsort[n-i-1]];
		cout<<"\n";
	}

	return 0;
}
