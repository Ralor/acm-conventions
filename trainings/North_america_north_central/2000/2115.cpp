#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <valarray>
#include <vector>
#include <assert.h>
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define fst        first
#define snd        second
#define pb         push_back
#define mp         make_pair
#define eb         emplace_back
#define ef         emplace_front
#define mt         make_tuple
#define eps        1e-8
#define inf        int(1e9)
#define linf       llong(4e18)
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

#define TIMESTAMP(msg) debug << "[" msg "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n' 
#define DBG(x) debug << "[" #x "] = " << x << '\n'
#define DOUT(x) debug << x << '\n'
#define _ << " " <<

typedef unsigned char       uchar;
typedef basic_string<uchar> ustring;
typedef long long           llong;
typedef unsigned long long  ullong;
typedef long double         ldouble;
typedef vector<int>         vi;
typedef vector<vi>          vvi;
typedef vector<double>      vd;
typedef vector<vd>          vvd;
typedef pair<int,int>       pii;

namespace BigInt {
  typedef vector<int> bigint;
  bigint ZERO = bigint();
  bigint ONE = bigint(1,1);
  const int base = 1000*1000*1000;
  void init(bigint& a, const string& s) {
    a.clear();
    for(int i = sz(s); i > 0; i -= 9)
      if( i >= 9 )
        a.eb(atoi(s.substr(i-9,9).c_str()));
      else
        a.eb(atoi(s.substr(0,i).c_str()));
  }
  ostream& operator << (ostream& out, bigint& a) {
    out<<(a.empty() ? 0 : a.back());
    for(int i = sz(a)-2; i >= 0; i--)
      out<<setw(9)<<setfill('0')<<a[i];
    return out;
  }
  int div(bigint& a, int divisor) {
    int carry = 0;
    for(int i = sz(a) - 1; i >= 0; i--) {
      int cur = carry + a[i];
      carry = cur % divisor;
      a[i] = cur / divisor;
    }
    while( sz(a) > 1 && a.back() == 0 )
      a.pop_back();
    return carry;
  }
  void add(bigint& a, bigint& b) {
    for(int i = 0, len = max(sz(a),sz(b)), carry = 0; i < len || carry; i++) {
      if( i == sz(a) ) 
        a.eb(0);
      a[i] += carry + (i < sz(b) ? b[i] : 0);
      carry = a[i] >= base;
      if( carry )
        a[i] -= base;
    }
  }
}

using BigInt::operator<<;
using BigInt::bigint;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int ci = 1;
  
  string number;
  while( cin>>number, number != "-1" ) {
    bigint n, result, temp;
    if( ci++ > 1 )
      cout<<"\n";
    DOUT("string = " _ number);
    BigInt::init(n, number);
    cout<<"f("<<n<<") = ";
    while( temp = n, n != BigInt::ONE && BigInt::div(temp, 2) ) {
      bigint temp2 = temp;
      // if( (n/2) % 2 )
        // result += (n/2 + 1)/2, n = n/2;      
      // else
        // result += n/4, n = n/2 + 1;
      if( BigInt::div(temp2, 2) ) {
        n = temp; 
        BigInt::add(temp, BigInt::ONE);
        BigInt::div(temp, 2);
        BigInt::add(result, temp);
      } else {
        BigInt::add(result, temp2);
        BigInt::add(temp, BigInt::ONE);
        n = temp;
      }
    }
    if( n == BigInt::ONE )
      BigInt::add(result, BigInt::ONE);
    else
      BigInt::div(n, 2), BigInt::add(result, n);
    cout<<result<<"\n";
  }
  
  TIMESTAMP("end");
  return 0;
}
