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

        int n, m; cin >> n >> m;
        vector<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];

        for(int mask = 0, stop = 1 << (n-1); mask < stop; mask++) {
                int cur = a[0];
                for(int i = 0; i < n-1; i++)
                        if( (mask>>i) & 1 ) // i-й бит числа (с младшего разряда)
                                cur += a[i+1];
                        else 
                                cur -= a[i+1];

                if( cur == m ) {
                        cout << a[0];
                        for(int i = 0; i < n-1; i++)
                                if( (mask>>i) & 1 )
                                        cout << "+" << a[i+1];
                                else
                                        cout << "-" << a[i+1];
                        cout << "=" << m << "\n";
                        return 0;
                }
        }        
        cout << "No solution\n";
    return 0;
}