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

#define eps      1e-8
#define inf      (1000 * 1000 * 1000)
#define linf     (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)   ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)    static_cast<int>((x).size())
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define mp       make_pair
#define mt       make_tuple
#define pb       push_back

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

int gcd(int a, int b) {while(a)b%=a,swap(a,b);return b;}

struct Frac {
  int up,down;
  Frac() {}
  Frac(int up, int down) : up(up), down(down) {
    fit();
  }
  Frac(const string& s) {
    init(s);
  }
  Frac operator + (const Frac& f) const {
    Frac a(*this), b(f);
    a.up *= b.down; b.up *= a.down;
    a.down = b.down = a.down * b.down;
    a.up += b.up;
    return a.fit();
  }
  Frac operator - (const Frac& f) const {
    Frac a(*this), b(f);
    a.up *= b.down; b.up *= a.down;
    a.down = b.down = a.down * b.down;
    a.up -= b.up;
    return a.fit();
  }
  Frac operator * (const Frac& f) const {
    Frac a(*this);
    a.up *= f.up;
    a.down *= f.down;
    return a.fit();
  }
  Frac operator / (const Frac& f) const {
    Frac b(f);
    swap(b.up, b.down);
    return *this * b;
  }

  Frac fit() {
    int t = gcd(abs(up), abs(down));
    up /= t; down /= t;
    return *this;
  }

  void init(const string& s) {
    istringstream in(s);
    int a,b,c; char t;
    if( in >> a >> b >> t >> c )
      up = a*c + (a?a/abs(a):0)*b, down = c;
    else {
      istringstream in2(s);
      if( !(in2 >> up >> t >> down) ) {
        istringstream in3(s);
        in3 >> up; down = 1;
      }
    }
    fit();
  }
};

ostream& operator<<(ostream& out, const Frac& f) {
  bool int_out = false;
  if( f.up == 0 )
    return out << 0;
  if( f.up/f.down )
    out << f.up/f.down, int_out = true;
  if( f.up%f.down ) {
    out << (int_out?" ":"") << (int_out?abs(f.up):f.up)%f.down << "/" << f.down;
  }
  return out;
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

  string f,t,s;
  while( getline(cin, f) && getline(cin, t) && getline(cin, s) ) {
    Frac a(f), b(s);
    switch(t[0]) {
    case '+' : cout << a+b << "\n"; break;
    case '-' : cout << a-b << "\n"; break;
    case '*' : cout << a*b << "\n"; break;
    case '/' : cout << a/b << "\n"; break;
    }
  }

  return 0;
}
