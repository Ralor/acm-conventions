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

// Убойная задача)
int a[111][111];
int cur = 1;
// функция заполняет числами края таблицы
// left, right, up, down
// значит для таблицы NxN нужно вызвать ее N/2 раз

void doIt(int l, int r, int u, int d) {
    for(int j = 0; j < r-l; j++) a[u][l+j] = cur++;
    for(int i = 0; i < d-u; i++) a[u+i][r] = cur++;
    for(int j = r; j > l; j--) a[d][j] = cur++;
    for(int i = d; i > u; i--) a[i][l] = cur++;
}
 
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int n; cin >> n;
   
	// лучше способа лично я не нашел. Так же как когда матрицу нужно повернуть
	// на 90 градусов. 4 фора - железный вариант. Только с формулами помучаться.
    a[n>>1][n>>1] = n*n;
    for(int i = 0; i < n>>1; i++)
        doIt(i,n-i-1,i,n-i-1);
 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
 
    return 0;
}