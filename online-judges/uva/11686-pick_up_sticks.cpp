#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define mp make_pair

typedef vector<int> vi;
typedef vector<vi> vvi;

struct __{__(){ios_base::sync_with_stdio(0);cin.tie(0);}} ___;

bool topsort(vvi& g, vi& ts) {
    int n=g.size(), u, v;    
    vi c(n,0);
    vector<pair<int,int>> st;
    forn(ii,n)
        if( c[ii]==0 ) {
            st.pb(mp(ii,-1));
            while(!st.empty()){
                u=st.back().first;                
                c[u]=1;
                int& i=st.back().second;
                ++i;
                for(i;i<g[u].size();i++) {
                    v=g[u][i];
                    if( c[v]==1 )
                        return false;
                    if( c[v]==0 )
                        break;                        
                }
                if( i==g[u].size() ) {
                    c[u]=2;
                    st.pop_back();
                    ts.pb(u);
                } else {
                    st.pb(mp(v,-1));
                }
            }
        }    
    return true;
}

int main() {
    
    #ifdef LOCAL_PROJECT
        freopen("input.txt","r",stdin);
    #endif
    
    int n,m,u,v;
    while(cin>>n>>m&&n&&m) {
        vvi g(n);
        forn(i,m) {
            cin>>u>>v,--u,--v;
            g[v].pb(u);
        }
        vi ts;
        if( topsort(g,ts) ) {
            forn(i,n)
                cout<<ts[i]+1<<"\n";
        } else {
            cout<<"IMPOSSIBLE\n";
        }
    }
    
    return 0;
}