#include <bits/stdc++.h>
using namespace std;

// tests:
// 9
// 1 2 3 4 1 3 5 6 4
// 5
// 1 4 2 3 4
// 17
// 1 2 3 4 5 6 7 2 8 9 5 10 8 9 11 3 9
// 9
// 1 2 7 3 2
// 8 4 8 5
// 10
// 1 2 3 4 2 3 4 2 3 4
// 13
// 1 2 3 4 5 6 7 6 2 6 8 9 7

int main() {
#ifdef RALOR_PROJECT
  freopen("input.txt","r",stdin);
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  while( cin>>n ) {
    vector<int> a(n), jump(n, -1);
    vector<int> last_pos(100*1000+1, -1);
    for(int i = 0; i < a.size(); i++) {
      cin>>a[i];
      if( last_pos[a[i]] != -1 ) {
        jump[last_pos[a[i]]] = i;
      }
      last_pos[a[i]] = i;
    }
    vector<int> dp(n), nxt(n, -1); // dp[i] = how many steps left to the end
    dp[n-1] = 0;
    for(int i = n-2; i >= 0; i--) {
      dp[i] = dp[i+1] + 1;
      nxt[i] = i+1;
      if( jump[i] != -1 && dp[i] > dp[jump[i]]) {
        dp[i] = dp[jump[i]];
        nxt[i] = nxt[jump[i]];
      }
    }
    for(int i = 0; i != -1; i = nxt[i])
      cout<<a[i]<<" ";
    cout<<"\n";
  }
  return 0;
}