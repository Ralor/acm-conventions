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

bool stopped;

string f(const string& s, const vector<pair<string,string> >& m) {
  forn(i,sz(m)) {
    const string& a = m[i].first;
    const string& b = m[i].second;
    int pos = s.find(a);
    if( pos != string::npos ) {
      return s.substr(0, pos) + b + s.substr(pos + sz(a));
    }
  }
  stopped = true;
  return s;
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


  string s;
  while( getline(cin,s) ) {
    vector<pair<string,string> > m;
    string inp;
    while( getline(cin,inp) ) {
      if( inp.empty() ) { break; }
      string tmp = "";
      forn(i,sz(inp))
        if( inp[i] != ' ' )
          tmp += inp[i];
      int pos = tmp.find("->");
      m.pb(mp(tmp.substr(0,pos), tmp.substr(pos + 2)));
    }

    stopped = false;
    string t = f(s,m), h = f(f(s,m), m);
    while( t != h )
      t = f(t,m), h = f(f(h,m),m);

    int pos = 0;
    t = s;
    while( t != h )
      ++pos, t = f(t,m), h = f(h,m);

    int len = 1;
    h = f(t,m);
    while( t != h )
      ++len, h = f(h,m);

    if( stopped )
      cout << pos << " 0\n";
    else
      cout << pos << " " << len << "\n";
  }

  return 0;
}
