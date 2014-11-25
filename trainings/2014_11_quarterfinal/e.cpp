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
#ifdef LOCAL_PROJECT
#   include <conio.h>
#endif

#ifndef LOCAL_PROJECT
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
#define mt       make_tuple
#define pb       push_back

using namespace std;

#define forn(i, n) for(int i = 0; i < (n); ++i)

struct __{__(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}_;
template<typename I> inline void in(I l,I r)
{while(l!=r)cin>>*l,++l;}
template<typename I> inline void out(I l,I r,char D=' ')
{if(l!=r){cout<<*l;while(++l!=r)cout<<D<<*l;}cout<<'\n';}



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

llong bruteforce(llong n) {
  int best = inf, best_i = 1;      
      for(int i = 2; i <= int(32e6); ++i) {
        int cnt = 0; llong tmp = n;                
        while( tmp ) {         
          cnt += tmp % i > 0, tmp /= i;
        }
        if( cnt < best ) best = cnt, best_i = i;        
      }
      //int meth = 0;
      //for(int i = 2; i <= int(32e6) && meth < 5; ++i) {
      //  int cnt = 0; llong tmp = n;                
      //  while( tmp ) {         
      //    cnt += tmp % i > 0, tmp /= i;
      //  }
      //  if( cnt == best ) cout << i << " - " << best << "\n", meth++;        
      //}
      if( best == 1 )        
        return best_i;
      else
        return n;        

}

llong my_pow(llong a, llong p) {
  return 0;
}

llong solve(llong n) {  
  for(llong q = 2; q < 2.3e7; q++) {
    //llong k = (llong)floor(log(ldouble(n)) / log(ldouble(q)));
    //ldouble a = n / pow(ldouble(q), ldouble(k));
    /*if( eq(a, ceil(a - eps)) ) {
      return q;      
    }*/    
    llong x = 1;    
    while (x < n)
      x *= q;
    x /= q;
    //ldouble a = ldouble(n) / x;
    if (!(n % x))
      return q;
  }
  return n;
}

int main() {
#   ifdef LOCAL_PROJECT
        freopen("e.in", "r", stdin);
#   else
#   endif
    
    llong n;
    while( cin >> n ) {

      time_t t = clock();
      //cout << n << ":\n";
      //bruteforce(n);
      //llong br = bruteforce(n);
      cout << solve(n) << "\n";

      debug << (clock() - t) / double(CLOCKS_PER_SEC) << "\n\n";
      //t = clock();

      //vector<llong> d;

      //while( n%2 == 0 ) d.push_back(2), n /= 2;

      //for(llong i = 3; i * i <= n; i += 2 ) {
      //  while( n%i == 0 ) d.push_back(i), n /= i;
      //}
      //if( n ) d.push_back(n);

      //map<llong,int> cnt;
      //forn(i,sz(d)) ++cnt[d[i]];
      //int mn = inf;
      //for(map<llong,int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
      //  mn = min(mn, it->second);
      //}
      //llong result = 1;
      //for(map<llong,int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
      //  result *= (mn == it->second) ? it->first : 1;
      //}
      ////cout << result << "\n";
      //cout << (clock() - t) / double(CLOCKS_PER_SEC) << "\n\n";
    }

#   ifdef LOCAL_PROJECT
        _getch();
#   endif
    return 0;
}
