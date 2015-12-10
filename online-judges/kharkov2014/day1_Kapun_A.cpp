#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double res(int n, int k) {
	double res = 0;
	for(int i = 1; i <= n; i++)
		res += log(i);
	for(int i = 1; i <= k; i++)
		res -= log(i);
	for(int i = 1; i <= n-k; i++)
		res -= log(i);
	return pow(2,res/log(2)-n);
}

int main() {
	
	int n,m;
	cout << setprecision(8) << fixed;
	
	while( cin >> n >> m ) 
		if( n < m || n%2 != m%2 )
			cout << 0 << "\n";
		else
			cout << res(n,(n+m)/2) << "\n";
	
	return 0;
}