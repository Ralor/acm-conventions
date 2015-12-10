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

double undef = -2*linf-100;
double mem[2222];
double* fib = mem + 1111;
double rec(llong n) {
  if( fib[n] == undef )
    return fib[n] = rec(n-1) + rec(n-2);
  return fib[n];
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

  cout << setprecision(0) << fixed;
  double fi,fj;
  llong i,j,n;
  while( cin >> i >> fi >> j >> fj >> n ) {
    forn(k,2222) mem[k] = undef;
    if( i > j ) swap(i,j), swap(fi,fj);

    fib[i] = fi; fib[j] = fj;
    double l = -linf, r = linf + 1;
    forn(zz,10*1000) {
      double mid = l + (r-l)/2;
      fib[i+1] = mid;
      for(llong k = i+2; k <= j; k++)
        fib[k] = fib[k-1] + fib[k-2];
      if( fib[j] > fj )
        r = mid;
      else
        l = mid;
      fib[j] = fj;
    }
    for(llong k = j+1; k <= 1000; k++)
      fib[k] = fib[k-1] + fib[k-2];
    for(llong k = i-1; k >= -1000; k--)
      fib[k] = fib[k+2] - fib[k+1];
    cout << fib[n] + 5e-5 << "\n";
  }

  return 0;
}
