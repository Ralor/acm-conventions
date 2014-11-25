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



int main() {
#   ifdef LOCAL_PROJECT
        freopen("d.in", "r", stdin);
#   else
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#   endif
    
    int n, k, s; 
    while( cin >> n >> k >> s ) {
      int first, fourth;
      for(int i = 1; i <= k; i++) {
        if( s - n*i <= (k-i)*(n-1) ) {
          first = i; break;
        }
      }      
      fourth = min(k, s - first*(n-1));

      int second, third;
      second = s/n; third = second + (s%n > 0);
      cout << first << " " << second << " " << third << " " << fourth << "\n";
    }

#   ifdef LOCAL_PROJECT
        _getch();
#   endif
    return 0;
}
