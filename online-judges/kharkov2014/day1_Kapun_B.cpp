#include <iostream>
using namespace std;

int main() {
	
	int n; cin >> n;
	double res = 0;
	for(int i = 1, t; i <= n; i++)
		cin >> t, res += (t != i);
	cout << res << "\n";
	// after shuffling at least on of cubes will take his place
	
	return 0;
}