#define _USE_MATH_DEFINES
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;

#pragma comment(linker,"/STACK:512000000000")

typedef long long int64;
typedef vector<int> vi;
typedef pair<int,int> pii;

#define sz(c) int((c).size())
#define all(c) (c).begin(),(c).end()
#define rall(c) (c).rbegin(),(c).rend()
#define spresent(c,v) ( find( all(c) ) != (c).end() )
#define present(c,v) ( (c).find(v) != (c).end() )
#define sqr(x) (x)*(x)
#define eps 1e-8
#define inf 1000*1000*1000
#define linf 9LL*1000*1000*1000*1000*1000*1000
#define eq(x,y) (fabs(double(x) - double(y)) <= eps)
#define le(x,y) (double(x) < double(y) && !eq(x,y))
#define gr(x,y) (double(x) > double(y) && !eq(x,y))

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);       

    ios::sync_with_stdio(0);
    cin.tie(0);

	int m,n; cin >> m >> n;
    int arr[] = {6,28,496,8128,33550336,1000*1000*1000};
    int l = 0, r = 0;
    while( r < 5 && n >= arr[r] ) ++r;
    while( l < r && m > arr[l] ) ++l;
    for(int i = l; i < r; i++)
        cout << arr[i] << "\n";
    if( l == r )
        cout << "Absent\n";

    return 0;
}