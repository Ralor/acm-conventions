#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <climits>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <ctime>
#include <cmath>
using namespace std;

typedef long long llong;
typedef unsigned long long ullong;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define spresent(c,v) ( find( all(c), v ) != (c).end() )
#define present(c,v) ( (c).find(v) != (c).end() )
#define sqr(x) ((x)*(x))
#define mp(x,y) make_pair((x),(y))
#define eps 1e-8
#define inf 1000*1000*1000
#define linf 4LL*1000*1000*1000*1000*1000*1000
#define eq(x,y) (fabs(double(x) - double(y)) <= eps)
#define ls(x,y) (double(x) < double(y) && !eq(x,y))
#define gr(x,y) (double(x) > double(y) && !eq(x,y))
#define dbg(x) cout << #x << " : " << x << "\n";


int N, K, dp[100][100][2], a[100][100];

int main() {
	//freopen(TASK ".in", "r", stdin);
	//freopen(TASK ".out", "w", stdout);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	//freopen("info.txt","r",stdin);
	//freopen("info.txt","w",stdout);

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K;
	memset(dp, -1, sizeof dp);
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin >> a[i][j];

	int bf = 0;
	dp[0][0][0] = a[0][0];
	for(int k = 0; k < K-1; k++) {
		int curBf = (bf+1)%2;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++) {
				int prv = -1;
				if( i + 1 < N && dp[i+1][j][bf] != -1 )
					prv = max(prv, dp[i+1][j][bf]);
				if( i - 1 >= 0 && dp[i-1][j][bf] != -1 )
					prv = max(prv, dp[i-1][j][bf]);
				if( j + 1 < N && dp[i][j+1][bf] != -1 )
					prv = max(prv, dp[i][j+1][bf]);
				if( j - 1 >= 0 && dp[i][j-1][bf] != -1 )
					prv = max(prv, dp[i][j-1][bf]);
				dp[i][j][curBf] = ((prv == -1) ? -1 : a[i][j] + prv);
			}
		bf = (bf+1)%2;
	}

	int ans = 0;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			ans = max(ans, dp[i][j][bf]);
	cout << ans << "\n";

	return 0;
}
