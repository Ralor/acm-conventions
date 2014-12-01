#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define mp make_pair

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

// Usage: 
// call BArp::init(adj_matrix);
// call BArp::rec/iter(
//          vvi& bridge, 
//          vi& articulation_point, 
//          int vertex); from all !BArp::used(v) vertexes
namespace BArp {    
    int tm;
    vvi a;
    vi parent;
    vi num, low;
    int root, rootChildren;        
    
    void barp_rec(vvi& b, vi& ap, int u) {
        num[u]=low[u]=tm; ++tm;
        forn(v,a.size()) 
            if( a[u][v] ) {            
                if( num[v]==0 ) {
                    parent[v]=u;
                    if( u==root )
                        ++rootChildren;
                    barp_rec(b,ap,v);
                    if( low[v]>=num[u] )
                        ap[u]=1;
                    if( low[v]>num[u]&&a[u][v]==1 )
                        b[u][v]=b[v][u]=1;
                    low[u]=min(low[u], low[v]);
                } else if( v!=parent[u] ) {
                    low[u]=min(low[u], num[v]);
                }
            }
    }
    void init(vvi& adj_matrix) {
        a.assign(adj_matrix.begin(), adj_matrix.end());
        int n = adj_matrix.size();        
        parent.assign(n,-1);
        num.assign(n,0);
        low.assign(n,0);
        tm=1;
    }
    void rec(vvi& bridge, vi& articulation_point, int vertex) {
        root=vertex;
        rootChildren=0;
        barp_rec(bridge, articulation_point, vertex);
        articulation_point[vertex] = (rootChildren>1);
    }
    void iter(vvi& b, vi& ap, int root) {
        rootChildren=0;
        vector<pii> st;
        st.pb(mp(root,-1));
        while( !st.empty() ) {
            int u=st.back().first;
            num[u]=low[u]=tm; ++tm;
            int& v=st.back().second;            
            for(v++;v<a.size();v++)
                if( a[u][v] )
                    break;
            if( v==a.size() ) {
                st.pop_back();
                int p=parent[u];
                if( p!=-1 ) {
                    if( low[u]>=num[p] )
                        ap[p]=1;
                    if( low[u]>num[p]&&a[p][u]>1 )
                        b[p][u]=b[u][p]=1;
                    low[p]=min(low[p], low[u]);
                }
            } else {
                if( parent[u]==-1 )
                    ++rootChildren;
                if( num[v]==0 ) {
                    parent[v]=u;
                    st.pb(mp(v,-1));              
                } else if( v!=parent[u] ) {
                    low[u]=min(low[u],num[v]);
                }
            }
        }
        ap[root] = (rootChildren>1);
    }
    bool used(int i) {
        return num[i]!=0;
    }    
}

int main() {
#ifdef LOCAL_PROJECT
    freopen("input.txt","r",stdin);
#endif
    
    int n,m,u,v;
    while(cin>>n>>m){
        vvi a(n, vi(n,0));
        forn(i,m) {
            cin>>u>>v,--u,--v;
            ++a[u][v]; ++a[v][u];
        }
        vi ap; // Articulation points, ap[i]=1
        vvi b; // Bridges, b[u][v]=1              
        
        // Recursive
        BArp::init(a);
        ap.assign(n,0); b.assign(n,vi(n,0));
        forn(u,n) if( !BArp::used(u) )
            BArp::rec(b,ap,u);                
        cout<<"Articulation points:\n";
        forn(u,n) if( ap[u] )
            cout<<u+1<<" ";
        cout<<"\nBridges:\n";
        forn(v,n) forn(u,v) if( b[u][v] ) 
            cout<<u+1<<" "<<v+1<<"\n";
        
        // Iterations
        BArp::init(a);
        ap.assign(n,0); b.assign(n,vi(n,0));        
        forn(u,n) if( !BArp::used(u) )
            BArp::rec(b,ap,u);                
        cout<<"Articulation points:\n";
        forn(u,n) if( ap[u] )
            cout<<u+1<<" ";
        cout<<"\nBridges:\n";
        forn(v,n) forn(u,v) if( b[u][v] ) 
            cout<<u+1<<" "<<v+1<<"\n";        
            
    }
    
    return 0;
}