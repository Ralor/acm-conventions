#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <list>
#include <set>
#include <map>

using namespace std;

#define TASKNAME "assembly"
#define pb push_back
#define mp make_pair
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif
#define TIMESTAMP(msg) eprintf("["msg"] Time=%.3lfs\n", clock() * 1.0 / CLOCKS_PER_SEC)
#define sz(x) ((int)(x).size())

typedef long double ld;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

const int inf = 1e9;
const double eps = 1e-9;

char s[20];

bool g[55][55];
int used[55];
bool found;

void dfs(int v){
  if (used[v] == 1){
    found = true;
    return;
  }
  if (used[v] == 2) return;
  used[v] = 1;
  for (int i = 0; i < 52; i++)
    if (g[v][i])
      dfs(i);
  used[v] = 2;
}

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif
  
  int n;
  scanf("%d",&n);
  
  for (int i = 0; i < n; i++){
    scanf("%s",s);
    vector<int> v;
    for (int j = 0; j < 4; j++){
      if (s[2*j] == '0') continue;
      int id = s[2*j] - 'A';
      if (s[2*j + 1] == '-')
        id = 2*id;
      else
        id = 2*id + 1;
      v.pb(id);
    }
//    eprintf("%d\n",i);
    for (int j = 0; j < (int)v.size(); j++)
      for (int k = 0; k < (int)v.size(); k++)
        if (k != j){
//          eprintf("%d %d\n",v[j]^1,v[k]);
          g[v[j]^1][v[k]] = true;
        }
  }
  for (int j = 0; j < 52; j++)
     dfs(j);
  if (found){
    printf("unbounded");      
  } else {
    printf("bounded");
  }

  TIMESTAMP("end");
  return 0;
}

