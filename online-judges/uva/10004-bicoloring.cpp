#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)

typedef vector<int> vi;
typedef vector<vi> vvi;

int main () {

#ifdef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
#endif

    int n,m,u,v;
    while(cin>>n&&n&&cin>>m){
        vvi a(n,vi(n,0));
        forn(i,m) {
            cin>>u>>v;
            a[u][v]=a[v][u]=1;
        }
        vi used(n,0);
        bool ok = true;
        forn(ii,n)
            if( used[ii]==0 && ok ) {
                queue<int> q; q.push(ii); used[ii]=1;
                while( !q.empty() && ok ) {
                    u = q.front(); q.pop();      
                    forn(i,n)
                        if( a[u][i] ) {
                            if( used[i]==used[u] )
                                ok = false;
                            else if( used[i]==0 )
                                used[i]=(used[u]==2?1:2), q.push(i);
                        }
                }
            }
        if( !ok )
            cout<<"NOT BICOLORABLE.\n";
        else
            cout<<"BICOLORABLE.\n";        
    }

    return 0;
}