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
#define dbg(x) cout << #x << " : " << x << "\n"

struct Point {
	double x,y;
	Point() {}
	Point(const double& x, const double& y) : x(x), y(y) {}
};

Point arr[1111];

int main() {
    //freopen(TASK ".in", "r", stdin);
    //freopen(TASK ".out", "w", stdout);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);

    ios_base::sync_with_stdio(0);
    //cin.tie(0);
	int n; cout << setprecision(1) << fixed;
	while( cin >> n ) {
		for(int i = 0; i < n; i++)
			cin >> arr[i].x >> arr[i].y;

		vector<Point> res;
		int cur = 0;
		for(int i = 0; i < n; i++)
			if( mp(arr[i].x, -arr[i].y) < mp(arr[cur].x, -arr[cur].y) )
				cur = i;
		int start = cur;
		double dx = 0, dy = -1.0;
		for(int cnt = 0; cnt < n; cnt++) {
			double angcos = -2.0, dist = 0;
			int nxt = -1;
			for(int i = 0; i < n; i++) {
				if( i != cur ) {
					double sp = dx * (arr[i].x - arr[cur].x) + dy * (arr[i].y - arr[cur].y);
					double len = sqrt(sqr(arr[i].x-arr[cur].x) + sqr(arr[i].y-arr[cur].y));
					double newcos = sp/len; // cos down -> angle bigger
					if( eq(angcos,newcos) && gr(len,dist) || ls(angcos,newcos) )
						nxt = i, angcos = newcos, dist = len;
				}
			}
			dx = arr[nxt].x - arr[cur].x;
			dy = arr[nxt].y - arr[cur].y;
			dist = sqrt(sqr(dx)+sqr(dy));
			dx /= dist; dy /= dist;
			res.push_back(Point(arr[nxt].x,arr[nxt].y));
			cur = nxt;
			if( nxt == start ) break;
		}

		double ans = 0.0;
		for(int i = 0, j = sz(res) - 1; i < sz(res); j = i, i++)
			ans += sqrt(sqr(res[i].x-res[j].x) + sqr(res[i].y-res[j].y));
		cout << ans << "\n";
	}

	return 0;
}
