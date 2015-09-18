#include <bits/stdc++.h>
using namespace std;
 
int main() {
 
	int n;
	while( cin>>n ) {
		vector<double> x(n), y(n);
		for(int i = 0; i < n; i++) 
			cin>>x[i]>>y[i];
		for(int i = 1; i < n; i++) {
			double a1 = x[i] - x[0], a2 = y[i] - y[0];
			int cnt_left = 0, cnt_right = 0;
			for(int j = 1; j < n; j++) 
				if( i != j ) {
					double b1 = x[j] - x[0], b2 = y[j] - y[0];
					double s = a1 * b2 - a2 * b1;
					cnt_left += s > 0;
					cnt_right += s < 0;
				}
			if( cnt_left == cnt_right ) {
				cout<<"1 "<<i+1<<"\n";
				break;
			}
		}
	}
 
	return 0;
}