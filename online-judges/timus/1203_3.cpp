#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define pb push_back
#define mp make_pair

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  while(cin>>n) {
    int ts,te;
    vector<pair<int,int>> segments;
    while(n--) {
      cin>>ts>>te; 
      segments.pb(mp(te,ts));
    }
    sort(begin(segments), end(segments));
    int ub = 0, result = 0;
    for(auto seg : segments)
      if( ub < seg.second )
        ub = seg.first, ++result;
    cout<<result<<"\n";
  }
  
  return 0;
}