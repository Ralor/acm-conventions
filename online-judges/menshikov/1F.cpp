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
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    vi a(5);
    cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4];
    sort( all(a) );
    int used[14]; memset(used,0,sizeof(used) );
    // два максимума, первый и второй
	// в них - количество повторений какого-либо из чисел
	int mx1 = 0, mx2 = 0;
    for(int i = 0; i < 5; i++)
        if( !used[a[i]] ) {        
            int cur = 0;           
            for(int j = i; j < 5; j++)
                    cur += (a[i] == a[j]);
            if( cur > mx1 )
                mx2 = mx1, mx1 = cur;
            else
            if( cur > mx2 )
                mx2 = cur;     
            used[a[i]] = 1;
        }
 
    if( a[0] == a[4] ) // значит все элементы равны (они же сортированные)
        cout << "Impossible\n";
    else
    if( a[0] == a[3] || a[1] == a[4] ) // значит четыре элемента равны
        cout << "Four of a Kind\n";
    else
    if( mx1 == 3 &&  mx2 == 2 )
        cout << "Full House\n";
    else
    if( (a[0]+1) == a[1]
    &&  (a[1]+1) == a[2]
    &&  (a[2]+1) == a[3]
    &&  (a[3]+1) == a[4] )
        cout << "Straight\n";
    else
    if( mx1 == 3 )
        cout << "Three of a Kind\n";
    else
    if( mx1 == mx2 && mx2 == 2 )
        cout << "Two Pairs\n";
    else
    if( mx1 == 2 )
        cout << "One Pair\n";
    else
        cout << "Nothing\n";
   
    return 0;
}