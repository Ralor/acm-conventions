/*
 *  @EXPECTED_RESULTS@: CORRECT
 */

#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	while (N--)
	{
		int n,m;
		cin >> n >> m;
		cout << n-1 << endl;
		while (m--)
		{
			cin >> n >> n;
		}
	}
	return 0;
}
