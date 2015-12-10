#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i,n) for(int i = 0; i < (n); i++)
#define pb push_back
#define mp make_pair
#define inf 1000*1000*1000

vector<pair<int,int>> segments;
int search(int i) { // right most conference compatible with ith
  int ts = segments[i].second;
  int ub = upper_bound(begin(segments), end(segments), mp(ts-1, inf)) - begin(segments);
  if( ub ) 
    return ub-1;
  return -1;
}

vi dp(100*1000 + 5); // dp[i] = maximal count of visits considering 0..i conferences
int rec(int i) {
  if( i == -1 ) return 0;
  if( dp[i] != -1 )
    return dp[i];
  return dp[i] = max(rec(i-1), 1 + rec(search(i)));
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  while(cin>>n) {
    int ts,te;
    segments.clear();
    forn(i,n) {
      cin>>ts>>te; 
      segments.pb(mp(te,ts));
    }
    sort(begin(segments), end(segments));
    dp.assign(100*1000 + 5,-1);
    cout<<rec(n-1)<<"\n";
  }
  
  return 0;
}