#include <bits/stdc++.h>
using namespace std;

struct debug_t {
  template<typename T>
  debug_t& operator << (const T& o) {
#   ifdef LOCAL_DEBUG
    cout<<o<<flush;
#   endif
    return *this;
  }
} debug;

#define TIMESTAMP(msg) debug << "[" << msg << "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n' 
#define DBG(x) debug << "[" #x "] = " << x << '\n'
#define forn(i,n) for(int i = 0; i < (n); i++)
#define sqr(x) ((x)*(x))

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long llong;

llong total_popcnt(llong x) {
  llong result = 0;
  for(int power = 0; power <= 31; power++) 
    if( x & (1LL << power) ) 
      result += power * (1LL << (power-1)) + 1 + x % (1LL << power);
  return result;
}

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  int a,b;
  int cn = 1;
  while( cin>>a>>b && (a || b) ) {
    if( a ) --a;
    cout<<"Case "<<cn++<<": "<<total_popcnt(b) - total_popcnt(a)<<"\n";
  }
  
  return 0;
}
