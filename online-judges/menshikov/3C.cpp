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


const int maxN = 50*1000;
int mn[maxN], mx[maxN];
 
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    for(int i = 0; i < maxN; i++)
        mx[i] = 0, mn[i] = inf;
 
    int e,f; cin >> e >> f; // empty, full
    int n; cin >> n;   
    vector<int> w(n), p(n);
    for(int i = 0; i < n; i++)
        cin >> p[i] >> w[i];
 
	// отмечаем начальные точки, в которые можно добраться
    for(int i = 0; i < n; i++)
        mn[e+w[i]] = min(mn[e+w[i]], p[i]),
        mx[e+w[i]] = max(mx[e+w[i]], p[i]);
 
	// идем из достижимых и улучшаем следующие
    for(int pos = e; pos <= f; pos++) {
        if( mn[pos] != inf )
            for(int i = 0; i < n; i++)
                mn[pos+w[i]] = min(mn[pos+w[i]], mn[pos] + p[i]);
        if( mx[pos] != 0 )
            for(int i = 0; i < n; i++)
                mx[pos+w[i]] = max(mx[pos+w[i]], mx[pos] + p[i]);
    }
 
	// проверяем, достижим ли искомый вес
    if( mn[f] == inf )
        cout << "This is impossible.\n";
    else
        cout << mn[f] << " " << mx[f] << "\n";
   
    return 0;
}