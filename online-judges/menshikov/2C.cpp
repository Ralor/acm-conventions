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

int dp[255][255], from[255][255];

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
	// пожалуй важный момент, считывать удобнее не посимвольно, а сразу строками
    int n; cin >> n; vector<string> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
 
	// инициализация краев и уголков
    from[0][0] = -1; dp[0][0] = a[0][0] - '0';
    for(int i = 1; i < n; i++)
        from[i][0] = 'u',
        dp[i][0] = dp[i-1][0] + a[i][0] - '0';
    for(int j = 1; j < n; j++)
        from[0][j] = 'l',
        dp[0][j] = dp[0][j-1] + a[0][j] - '0';
 
	// подсчет динамики
    for(int i = 1; i < n; i++)
        for(int j = 1; j < n; j++)
            if( dp[i-1][j] < dp[i][j-1] )
                from[i][j] = 'u',
                dp[i][j] = dp[i-1][j] + a[i][j] - '0';
            else
                from[i][j] = 'l',
                dp[i][j] = dp[i][j-1] + a[i][j] - '0';
 

	// составление ответа
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            a[i][j] = '-';

    int curi = n-1, curj = n-1;
    while( from[curi][curj] != -1 ) {
        a[curi][curj] = '#';
        if( from[curi][curj] == 'l' )
            curj--;
        else
            curi--;
    } a[0][0] = '#';
       
	// вывод ответа
    for(int i = 0; i < n; i++)
        cout << a[i] << "\n";
 
    return 0;
}