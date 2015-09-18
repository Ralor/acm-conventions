#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back

typedef vector<int> vi;
typedef vector<vi> vvi;

int main () {

#ifdef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
#endif
    
    int tests; cin>>tests;
    forn(test,tests) {
        int n; cin>>n;
        vvi g(n);
        int u,v;
        forn(i,n) {
            int cnt; cin>>cnt;
            forn(j,cnt) {
                cin>>v, --v;
                if( v < n )
                    g[i].pb(v),g[v].pb(i);
            }
        }
        vi c(n,0);
        int answer = 0;
        forn(ii,n)
            if( c[ii]==0 ) {
                queue<int> q;
                int cnt_o=0, cnt_t=0;
                bool cycle = false;
                q.push(ii); c[ii]=1;
                while( !q.empty() ) {
                    u = q.front(); q.pop();
                    cnt_o+=c[u]==1;
                    cnt_t+=c[u]==2;
                    forn(i,g[u].size()){
                        v = g[u][i];
                        if( c[v]==c[u] ) 
                            cycle = true;
                        else if( c[v]==0 )
                            c[v] = (c[u]==2?1:2), q.push(v);                                                                
                    }
                }
                if( !cycle )
                    answer += max(cnt_o, cnt_t);
            }
        cout<<answer<<"\n";
    }
    
    return 0;
}