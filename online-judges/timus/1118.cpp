#include <bits/stdc++.h>
using namespace std;

int main() {
	int a,b;
	while( cin>>a>>b ) {
		if( a == 1 ) {
			cout<<"1\n";
			continue;
		}
		int best_number = -1;
		double best_frac = 1000*1000;
		for(int number = b; number >= a; number--) {
			int i;
			double frac = 1.0;
			for(i = 2; i*i <= number; i++)
				if( number % i == 0 ) 
					frac += i + number / i;
			--i;
			if( i*i == number )
				frac -= i;
			frac /= number;
			if( best_frac > frac ) {
				best_frac = frac;
				best_number = number;
			}
			if( best_frac == 1.0 / number)
				break; // we've found prime number!
		}
		cout<<best_number<<"\n";
	}
	return 0;
}