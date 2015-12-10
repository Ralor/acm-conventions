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
struct p
 {
   int x;
   int y;
 };
int main() {
#   ifdef LOCAL_PROJECT
        freopen("f.in", "r", stdin);
#   else
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#   endif
    
    cout << setprecision(9) << fixed;

    int m;
    cin>>m;
    vector<p> lom(m+1);
    forn(i,m+1)
      cin>>lom[i].x>>lom[i].y;
    int w;
    cin>>w;
    vector <string> dict(w);
    forn(i,w)
      cin>>dict[i];
    int k;
    cin >>k;
    //char alf[k];
    p key[26];
    char c;
    forn(i,k) 
    {
      cin>>c;
      cin>>key[c-'a'].x>>key[c-'a'].y;
    }
    double sum;
    p b;
    double min=1e8;
    forn(i,w)
    {
      sum=0;
      forn(k,dict[i].size())
        {
          b=key[dict[i][k]-'a'];
          sum+=sqrt(sqr(b.x-lom[k].x)+sqr(b.y-lom[k].y));
        }
      if(min>sum) min=sum;
    }
    cout<<min;
#   ifdef LOCAL_PROJECT
        _getch();
#   endif
    return 0;
}
