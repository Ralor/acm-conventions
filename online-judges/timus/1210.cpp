#include <bits/stdc++.h>
using namespace std;

int main() {

	int n;
	while(cin>>n){
		vector<vector<int>> dp(33,vector<int>(33,1000*1000*1000));
		dp[0][1] = 0;
		for(int lvl=1;lvl<=n;++lvl){
			int k;cin>>k;
			for(int i=1;i<=k;i++){
				int prev,cost;
				while( cin>>prev && prev ) {
					cin>>cost;
					dp[lvl][i] = min(dp[lvl][i], dp[lvl-1][prev] + cost);
				}
			}
			if( lvl<n )
				while( cin.get()!='*' ) { }
		}
		cout<<*min_element(dp[n].begin(), dp[n].end())<<"\n";
	}
	return 0;
}
