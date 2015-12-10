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
 
#define TASKNAME "matryoshka"
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
 
const int MAXN = 510;
 
int a[MAXN];
int minv[MAXN][MAXN];
int maxv[MAXN][MAXN];
int lcnt[MAXN][MAXN];
int dp[MAXN][MAXN];
int dp2[MAXN];
int n;
 
int used[MAXN], usedptr;
 
 
int getcost(int l,int mid,int r){
  if (minv[l][mid-1] < minv[mid][r-1])
    return (r - l) - (lcnt[mid][minv[mid][r-1]] - lcnt[l][minv[mid][r-1]]);
  assert(minv[l][mid-1] != minv[mid][r-1]);
  return (r - l) - (lcnt[r][minv[l][mid-1]] - lcnt[mid][minv[l][mid-1]]);
}
 
bool check(int i,int j){
  ++usedptr;
  for (int k = i; k < j; k++)
     if (used[a[k]] == usedptr)
         return false;
     else
         used[a[k]] = usedptr;
  return true;
}
 
int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif
  
  scanf("%d",&n);
  for (int i = 0; i < n; i++){
    scanf("%d",&a[i]);
    if (a[i] > n) {
      printf("impossible\n");
      return 0;
    }
  }
    
  for (int i = 0; i < n; i++){
    minv[i][i] = maxv[i][i] = a[i];
    for (int j = i+1; j < n; j++) {
      minv[i][j] = min(minv[i][j-1], a[j]);
      maxv[i][j] = max(maxv[i][j-1], a[j]);
      #ifdef DEBUG
        assert(minv[i][j] == *min_element(a+i, a+j+1));
        assert(maxv[i][j] == *max_element(a+i, a+j+1));
      #endif
    }
  }
  
  
  for (int i = 0; i < n; i++)
    for (int j = 0; j <= n; j++)
      for (int k = 0; k < i; k++)
        if (a[k] < j)
          lcnt[i][j]++;
 
    
  for (int len = 2; len <= n; len++){
    for (int i = 0; i+len <= n; i++){
      int j = i + len;
        dp[i][j] = inf;
      if (!check(i,j)){
        continue;
      }
      for (int k = i+1; k < j; k++)
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + getcost(i,k,j));      
//      eprintf("%d %d %d\n",i,j,dp[i][j]);
    }
  }
    
  for (int i = 1; i <= n; i++)
    dp2[i] = inf;
    
  for (int i = 0; i < n; i++){
    if (dp2[i] == inf) continue;
    for (int j = i+1; j <= n; j++)
      if (minv[i][j-1] == 1 && maxv[i][j-1] == j-i)
        dp2[j] = min(dp2[j], dp2[i] + dp[i][j]);      
  }
    
  if (dp2[n] == inf)
    printf("impossible\n");
  else
    printf("%d\n",dp2[n]);
 
  TIMESTAMP("end");
  return 0;
}
 
