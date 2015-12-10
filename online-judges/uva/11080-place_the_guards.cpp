#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)

typedef vector<int> vi;
typedef vector<vi> vvi;

bool dfs(vvi& a, vi& c, vi& cnt, int v, int color) {    
    c[v]=color; ++cnt[color];
    int anti = color==1?2:1;
    bool ok = true;
    forn(i,a.size())
        if( a[i][v] ) {
            if( c[i]==0 && !dfs(a,c,cnt,i,anti) )
                ok = false;
            if( c[i]==color )
                ok = false;
        }
    return ok;
}

int main () {

#ifdef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
#endif

    int tests; cin>>tests;
    forn(test,tests){
        int n,m,u,v; cin>>n>>m;
        vvi a(n,vi(n,0));
        forn(i,m) {
            cin>>u>>v;//, --u, --v;
            a[u][v]=a[v][u]=1;
        }
        int answer=0;
        vi c(n,0);
        forn(ii,n) 
            if( c[ii]==0 ) {
                vi cnt(3,0);
                if( !dfs(a,c,cnt,ii,1) ) {
                    answer=-1; 
                    break;
                }
                answer += max(1,min(cnt[1],cnt[2]));
            }
        cout<<answer<<"\n";        
    }

    return 0;
}