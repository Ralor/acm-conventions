#include <bits/stdc++.h>
using namespace std;

#define sqr(x) ((x)*(x))

int main() {
	cout<<setprecision(3)<<fixed;
	
	double a, r;
	while( cin>>a>>r ) {
		const double step = 1e-5;
		double s = 0;
		for(double x = step; x <= a; x += step) 
			s += min(a/2, sqrt(max(0.0, sqr(r) - sqr(x - a/2))));
		cout<<s * step * 2<<"\n";
	}
	
	return 0;
}