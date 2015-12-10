#include <bits/stdc++.h>
using namespace std;

#define inf (1000 * 1000 * 1000)
#define sz(x) static_cast<int>((x).size())
#define pb push_back
#define forn(i, n) for(int i = 0; i < (n); ++i)

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
	
  int n,m;
  while( cin >> n && n != -1 && cin >> m ) {
    vvi a(n,vi(n,inf));
    while( m-- ) {
      int u,v,l; cin >> u >> v >> l;
      --u; --v;
      a[u][v] = a[v][u] = min(l, a[u][v]);
    }
    vvi g(n), c(n);
    forn(i,n) forn(j,n)
      if( a[i][j] < inf )
        g[i].pb(j), c[i].pb(a[i][j]);

    int best = inf, to_u = -1, to_v = -1;
    vi result;

    forn(vertex, n) {
      vi dist(n,inf);
      vi used(n,0);
      vi parent(n,-1);
      dist[vertex] = 0; 
      forn(step,n) {
        int min_i = -1;
        forn(i,n)
          if(!used[i]&&(min_i == -1 || dist[i] < dist[min_i]))
            min_i = i;
        if( dist[min_i] == inf ) break;
        used[min_i] = 1;
        forn(i,sz(g[min_i])) {
          int nxt = g[min_i][i], cost = c[min_i][i];
          if( dist[nxt] > cost + dist[min_i] ) {
            dist[nxt] = cost + dist[min_i];
            parent[nxt] = min_i;
          }
        }
      }
      forn(u,n) forn(v,u) 
        if( parent[u] != v && parent[v] != u && a[u][v] < inf ) {
            int w = min(inf, dist[u] + dist[v] + a[u][v]);
            if( best > w ) {
              best = w;
              result.assign(all(parent));
              to_u = u; to_v = v;
            }
        }
    }


    if( best == inf )  {
      cout << "No solution.\n";
    } else {
      vi t_u;
      for(int v = to_u; v != -1; v = result[v])
        t_u.pb(v+1);
      vi t_v;
      for(int v = to_v; v != -1; v = result[v])
        t_v.pb(v+1);
      t_v.pop_back(); reverse(all(t_v));
      out(all(t_u), ' ', ' '); out(all(t_v));
    }
  }

  return 0;
}