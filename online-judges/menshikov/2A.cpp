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

typedef long long int64;
typedef vector<int> vi;
typedef pair<int,int> pii;

#define sz(c) (int((c).size()))
#define all(c) (c).begin(),(c).end()
#define rall(c) (c).rbegin(),(c).rend()
#define spresent(c,v) ( find( all(c) ) != (c).end() )
#define present(c,v) ( (c).find(v) != (c).end() )
#define sqr(x) ((x)*(x))
#define eps 1e-9
#define inf 1000*1000*1000
#define INF 2147483647
#define linf 4LL*1000*1000*1000*1000*1000*1000
#define LINF 9223372036854775807LL

const int maxN = 1000*1000 + 500;
int prime[maxN];
 
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    //ios::sync_with_stdio(0);
    cin.tie(0);
   
	//http://e-maxx.ru/algo/eratosthenes_sieve
	// там опять все лучше
    for(int i = 0; i < maxN; i++)
        prime[i] = 1;
 
    prime[0] = prime[1] = 0;

	// а можно было сначала двойки просеять, а потом идти от 3 с шагом i += 2
    for(int i = 2; i*i < maxN; i++)
        if( prime[i] )
            for(int j = i + i; j < maxN; j += i)
                prime[j] = 0;
 
    int n,m; cin >> n >> m;
    int ok = 0;
    for(int i = n; i <= m; i++)
        if( prime[i] )
            cout << i << "\n", ok = 1;
    if( !ok )
        cout << "Absent\n";  
 
    return 0;
}