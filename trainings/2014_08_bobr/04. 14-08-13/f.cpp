#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#ifdef _DEBUG
#   include <conio.h>
#endif

#ifndef _DEBUG
#   undef VERBOSE
#endif

#define eps      1e-8
#define inf      (1000 * 1000 * 1000)
#define linf     (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)   ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)    int((x).size())
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define mp       make_pair

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;

typedef vvi Graph;

map<string, int> name_to_index;
map<int,string> index_to_name;

int main() {
#   ifdef _DEBUG
        freopen("f.in", "r", stdin);
#   else
        freopen("f.in", "r", stdin);
        freopen("f.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int ci = 1;

    int n; 
    while( cin >> n && n != 0) {
      index_to_name.clear();
      name_to_index.clear();

      int vertex_ind = 0;

      Graph g, rev_g;
      for(int i = 0; i < n; i++) {
        string a,b; cin >> a >> b;
        int aa = -1, bb = -1;
        if( name_to_index.find(a) == name_to_index.end() ) {
          name_to_index[a] = vertex_ind;
          index_to_name[vertex_ind] = a; 
          aa = vertex_ind++;
        }
        if( name_to_index.find(b) == name_to_index.end() ) {
          name_to_index[b] = vertex_ind; 
          index_to_name[vertex_ind] = b; 
          bb = vertex_ind++;
        }
        if( aa == -1 ) aa = name_to_index[a];
        if( bb == -1 ) bb = name_to_index[b];
        while( sz(g) <= max(aa,bb) )
          g.push_back(vi()), rev_g.push_back(vi());
        g[aa].push_back(bb); rev_g[bb].push_back(aa);
      }

      vector<vi> walkable(sz(g));
      vector<int> calced(sz(g), 0);
      for(int i = 0; i < sz(g); i++) {
        
        vector<int> visited(sz(g),0);
        queue<int> u; calced[i] = 1;        
        u.push(i); visited[i] = 1;        
        while( !u.empty() ) {
          int cur = u.front(); u.pop();          
          for(int j = 0; j < sz(g[cur]); j++) {
            int nxt = g[cur][j];
            if( !visited[nxt] ) {
              walkable[i].push_back(nxt);
              u.push(nxt); visited[nxt] = 1;
            }
          }
        }
      }
      for(int i = 0; i < sz(g); i++)
        sort(all(walkable[i]));

      /*for(int i = 0; i < sz(walkable); i++) {
        debug << index_to_name[i] << ": ";
        for(int j = 0; j < sz(walkable[i]); j++)
          debug << index_to_name[walkable[i][j]] << " ";
        debug << "\n";
      }*/

      vector< pair<string,string> > answer;

      for(int i = 0; i < sz(g); i++) 
        for(int j = 0; j < sz(g[i]); j++) {
          int from = i, to = g[i][j];
          vector<int> alternatives(all(rev_g[to]));
          bool exist = false;
          for(int k = 0; k < sz(alternatives); k++)
            exist |= binary_search(all(walkable[from]), alternatives[k]);
          if( exist ) answer.push_back(mp(index_to_name[from], index_to_name[to]));
        }      

      sort(all(answer));

      cout << "Case " << ci++ << ": " << sz(answer);
      for(int i = 0; i < sz(answer); i++)
        cout << " " << answer[i].first << "," << answer[i].second;      
      cout << "\n";
    }


#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
