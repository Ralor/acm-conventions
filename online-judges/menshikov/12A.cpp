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

int add_mod(int a, int b, int mod = 10) {return (a+b)%mod;}

void mul_matr(vvi& a, vvi& b) {
  static vvi t(3,vi(3));
  forn(i,3) forn(j,3) {
    t[i][j] = 0;
    forn(k,3)
      t[i][j] = add_mod(t[i][j], a[i][k] * b[k][j]);
  }
  a.assign(all(t));
}

void pow_matr(vvi& a, llong p) {
  vvi res(3,vi(3,0));
  res[0][0] = res[1][1] = res[2][2] = 1;
  while( p ) {
    if( p & 1 )
      mul_matr(res,a);
    mul_matr(a,a); p>>=1;
  }
  a.assign(all(res));
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

   int d1,d2,d3;
   llong N;
   while( cin >> d1 >> d2 >> d3 >> N ) {
     vvi r(3,vi(3,0));
     r[0][1] = r[1][2] = 1;
     r[2][0] = r[2][1] = r[2][2] = 1;
     if( N == 1 ) { cout << d1 << "\n"; continue; }
     if( N == 2 ) { cout << d2 << "\n"; continue; }
     if( N == 3 ) { cout << d3 << "\n"; continue; }
     pow_matr(r,N-3);
     cout << add_mod(r[2][0] * d1, add_mod(r[2][1] * d2, r[2][2] * d3)) << "\n";
   }

  return 0;
}
