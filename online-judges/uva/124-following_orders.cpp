#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define mp make_pair

typedef vector<int> vi;
typedef vector<vi> vvi;

void solve(int n, vi& g, vector<char>& ids, vector<string>& result) {
	int u=0;
	vector<char> mem(n);
	vector<pair<pair<int,int>,int>> st;
	forn(i,n){
		st.pb(mp(mp(i,0),-1));
		while(!st.empty()){
			int v=st.back().first.first,
				d=st.back().first.second;
			u|=1<<v;
			mem[d]=ids[v];
			int& ii=st.back().second;
			++ii;
			for(ii;ii<n;ii++)
				if( !((u>>ii)&1) && !(g[ii]&u) )
					break;
			if( ii==n ) {
				if( d==n-1 )
					result.pb(string(mem.begin(), mem.end()));
				st.pop_back();
				u^=1<<v;
			} else {
				st.pb(mp(mp(ii,d+1),-1));
			}
		}
	}
}

int main() {

	bool first=true;
	string ff,ss;
	while(getline(cin,ff)&&getline(cin,ss)) {
		  string f,s;
		  istringstream in_f(ff);
		  int id=0;
		  vector<char> ids;
		  map<char,int> sid;
		  while(in_f>>f) {
		  	ids.pb(f[0]);
		  	sid[ids.back()]=id;
		  	++id;
		  }
		  int n=id;
		  vi g(n,0);
		  istringstream in_s(ss);
		  while(in_s>>f>>s)
		  	g[sid[f[0]]] |= 1<<sid[s[0]];
		  vector<string> result;
		  solve(n,g,ids,result);
		  if( result.empty() )
		  	continue;
		  if( !first )
		  	cout<<"\n";
		  sort(result.begin(), result.end());
		  first=false;
		  forn(i,result.size())
		  	cout<<result[i]<<"\n";
	}
	return 0;
}
