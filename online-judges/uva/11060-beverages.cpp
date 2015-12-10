#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;

#define forn(i,n) for(int i=0;i<(n);++i)
#define pb        push_back

typedef vector<int> vi;
typedef vector<vi> vvi;

struct __{__(){ios_base::sync_with_stdio(0);cin.tie(0);}} ___;

int main() {
#   ifdef LOCAL_PROJECT
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
#   endif	

    int n,m,u,v;
    string f,s;
    int ci=1;
    while(cin>>n){                
        map<string,int> nid;
        vector<string> idn(n);        
        forn(i,n) 
            cin>>idn[i], nid[idn[i]]=i;
        vvi a(n,vi(n,0));
        vi p_in(n,0);
        cin>>m;
        forn(i,m) {
            cin>>f>>s;
            u=nid[f], v=nid[s];
            if( !a[u][v] ) {
                a[u][v]=1;
                ++p_in[v];
            }
        }                    
        cout<<"Case #"<<ci<<": Dilbert should drink beverages in this order:"; 
        ++ci;
        vi inq(n,0);
        priority_queue<int> q;
        forn(i,n)
            if( p_in[i]==0 ) 
                q.push(-i);           
        forn(step,n) {            
            v=-q.top();
            q.pop();
            cout<<" "<<idn[v];
            forn(i,n)
                if( a[v][i] ) {
                    a[v][i]=0; --p_in[i];
                    if( p_in[i]==0 )
                        q.push(-i);
                }            
        }                
        cout<<".\n\n";
    }
    
    return 0;
}
