#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back


typedef vector<int> vi;
typedef vector<vi> vvi;

int main () {
#ifdef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
#endif

    int n,u,v;
    while(cin>>n&&n) {
        vvi g(n);
        while(cin>>u>>v&&u&&v) {
            --u,--v;
            g[u].pb(v);
            g[v].pb(u);
        }
        vi c(n,0);
        forn(ii,n)
            if( c[ii]==0 ) {
                c[ii]=1;
                queue<int> q;
                q.push(ii);
                while( !q.empty() ) {
                    u=q.front(); q.pop();                    
                    forn(i,g[u].size()) {
                        v=g[u][i];
                        if( c[v]==0 ) {
                            c[v]=(c[u]==1?2:1);
                            q.push(v);
                        }
                    }
                }
            }
        // check whether matching succeded
        bool ok=true;
        forn(ii,n) forn(jj,g[ii].size())
            ok &= (c[ii]!=c[g[ii][jj]]);
        if( !ok ) {
            cout<<"NO\n";
            continue;
        }
        // check whether graph can be separated correctly
        int cnt=count(c.begin(), c.end(), 1);        
        int mcolor=1;
        if( cnt<n-cnt ) {
            cnt=n-cnt;
            mcolor=2;
        }        
        int sum=0;
        forn(ii,n)
            if( c[ii]==mcolor )
                sum += g[ii].size();        
        int nn=sum+n-cnt;
        int mm=sum;
        // k claws consist of
        // nn == 4*k - vertexes, mm == 3*k - edges
        if( nn%4==0 && mm%3==0 && nn/4==mm/3 )
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }

    return 0;
}