#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <fstream>
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

#ifndef _DEBUG
# undef VERBOSE
#endif
#ifdef NDEBUG
#define VERBOSE
#endif

using namespace std;

#pragma comment(linker, "/STACK:256000000")

#define eps 1e-8
#define inf (1000 * 1000 * 1000)
#define linf (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x) ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x) static_cast<int>((x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define mp make_pair
#define mt make_tuple
#define pb push_back

#define forn(i, n) for(int i = 0; i < (n); ++i)

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_;
template<typename I> inline void in(I l,I r)
{while(l!=r)cin>>*l,++l;}
template<typename I> inline void out(I l,I r,char D=' ')
{if(l!=r){cout<<*l;while(++l!=r)cout<<D<<*l;}cout<<'\n';}

struct debug_t {
  template <typename T>
  debug_t& operator<<(const T& value) {
# ifdef VERBOSE
    cout << value;
# endif
    return *this;
  }
} debug;

// just in vs2013, I'll get it after win 8.1)
//void dbg_out(){debug<<'\n';}
//template <typename T, typename... Args>
//void dbg_out(const T& value, const Args&... args)
//{debug<<value;dbg_out(args...);}
//#define dbg(x) #x" = ",x,"; "

typedef unsigned uint;
typedef long long llong;
typedef unsigned long long ullong;
typedef long double ldouble;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;

bool m_isdigit(const char& c) {
  return '0' <= c && c <= '9';
}

int main() {
  //freopen(TASK".in", "r", stdin);
  //freopen(TASK".out", "w", stdout);
#ifdef RALOR_PROJECT
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
#endif
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);     

  int n;
  while( cin >> n ) {
    vvi board(10,vi(10,0));    
    int tt; string ttt;
    cin >> tt >> ttt;
    if( sz(ttt) == count_if(all(ttt), m_isdigit) ) {
      board[tt-1][atoi(ttt.c_str())-1] = 1;
      forn(i,n-1) {
        int x,y; cin >> x >> y; --x; --y;
        board[x][y] = 1;
      }    
      for(int sx = 0; sx < 10; sx++)
        for(int sy = 0; sy < 10; sy++) 
          if( board[sx][sy] ) {
            queue<pair<int,int>> q;
            board[sx][sy] = 0;
            q.push(mp(sx,sy));
            const char dd[] = {'R','T','L','B'};
            const int dx[] = {1,0,-1,0};
            const int dy[] = {0,1,0,-1};
            int cnt = 0;
            cout << sx+1 << " " << sy+1 << "\n";
            while( !q.empty() ) {
              int x = q.front().first, 
                  y = q.front().second;
              q.pop(); ++cnt;
              forn(i,4) {
                int nx = x+dx[i], ny = y+dy[i];
                if( nx >= 0 && ny >= 0 && nx < 10 && ny < 10 && board[nx][ny] ) {          
                  board[nx][ny] = 0;
                  q.push(mp(nx,ny));
                  cout << dd[i];                    
                }        
              }
              cout << (cnt==n ? '.' : ',') << "\n";
            }
          } // if board[sx][sy]
    } else {            
      vector<string> inp; inp.pb(ttt.substr(0,sz(ttt)-1));
      while( cin >> ttt && ttt[sz(ttt)-1] != '.' ) 
        inp.pb(ttt.substr(0,sz(ttt)-1));
      
      int sx = n-1, sy = tt-1;
      board[sx][sy] = 1;
      queue<pair<int,int>> q; q.push(mp(sx,sy));
      forn(i,sz(inp)) {
        string& s = inp[i];
        int dx[255], dy[255];
        dx['R'] = 1; dy['R'] = 0;
        dx['T'] = 0; dy['T'] = 1;
        dx['L'] = -1; dy['L'] = 0;
        dx['B'] = 0; dy['B'] = -1;        
        
        int x = q.front().first, y = q.front().second;
        q.pop();
        for(char c : s) {
          int nx = x + dx[c], ny = y + dy[c];
          board[nx][ny] = 1;
          q.push(mp(nx,ny));
        }
      }
      vector<pair<int,int>> result;
      for(int x = 0; x < 10; x++)
        for(int y = 0; y < 10; y++)
          if( board[x][y] )
            result.pb(mp(x,y));
      cout << sz(result) << "\n";
      forn(i,sz(result))
        cout << result[i].first+1 << " " << result[i].second+1 << "\n";
    }
  }
  
  return 0;
}