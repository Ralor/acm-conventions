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

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    int n; cin >> n;
    vector<vi> mem(2*n);
 
	// способ навороченный, но вот мне он яснее
	// смысл в том, чтобы по отдельности выписать все
	// диагонали (по которым надо заполнять, змейкой)
	// а потом так их вывести, чтобы получился ответ
    int cur = 1;
    for(int diag = 1; diag <= 2*n-1; diag++) {
        mem[diag].resize(n - abs(diag - n));
        if( diag & 1 )
            for(int i = 0; i < sz(mem[diag]); i++)
                mem[diag][i] = cur++;
        else
            for(int i = sz(mem[diag])-1; i >= 0; i--)
                mem[diag][i] = cur++;
    }
       
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << mem[i+j+1].back() << " ", mem[i+j+1].pop_back();
        cout << "\n";
    }
   
    return 0;
}