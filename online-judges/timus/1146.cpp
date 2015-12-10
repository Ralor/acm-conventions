#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i = 0; i < (n); i++)
#define inf 1000*1000*1000

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
	
	int n;
	while( cin>>n ) {
		vvi m(n, vi(n)); // matrix
		forn(i,n) forn(j,n)
			cin>>m[i][j];
		vvi s(n, vi(n)); // sum[i][j] = sum of rect 0..i x 0..j (inclusively)
		forn(i,n) forn(j,n) {
			s[i][j] = m[i][j];
			if( i )
				s[i][j] += s[i-1][j];
			if( j )
				s[i][j] += s[i][j-1];
			if( i && j )
				s[i][j] -= s[i-1][j-1];
		}
		int result = -inf;
		forn(i,n) forn(j,n) forn(k,i+1) forn(t,j+1) {
			int current = s[i][j];
			if( t )
				current -= s[i][t-1];
			if( k )
				current -= s[k-1][j];
			if( t && k )
				current += s[k-1][t-1];
			result = max(result, current);
			// cout<<"("<<k<<";"<<t<<") ("<<i<<";"<<j<<") = "<<current<<"\n";
		}
		cout<<result<<"\n";
	}
	
	return 0;
}