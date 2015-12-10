#include <cassert>
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

const double dx[] = {0, 1, 0, -1, -1/sqrt(2), 1/sqrt(2), 1/sqrt(2), -1/sqrt(2)};
const double dy[] = {1, 0, -1, 0, 1/sqrt(2), 1/sqrt(2), -1/sqrt(2), -1/sqrt(2)};

int get_dir(char a, char b) {
  if( !isalpha(b) )
    return a == 'N' ? 0 :
           a == 'E' ? 1 :
           a == 'S' ? 2 :
           a == 'W' ? 3 : -1;
  return a == 'N' && b == 'W' ? 4 : 
         a == 'N' && b == 'E' ? 5 :
         a == 'S' && b == 'E' ? 6 :
         a == 'S' && b == 'W' ? 7 : -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout<<setprecision(3)<<fixed;
  
  int ci = 1;
  
  string line;
  while( getline(cin,line), line != "END" ) {
    int i = 0;
    double curx = 0, cury = 0;
    while( i < sz(line) ) {
      int d = 0;
      while( isdigit(line[i]) )
        d = d * 10 + int(line[i] - '0'), ++i;
      int dir = get_dir(line[i], line[i+1]);
      curx += dx[dir] * d;
      cury += dy[dir] * d;
      while( line[i] != ',' && line[i] != '.' ) 
        ++i;
      ++i;
    }
    cout<<"Map #"<<ci++<<"\n";
    cout<<"The treasure is located at ("<<curx<<","<<cury<<").\n";
    cout<<"The distance to the treasure is "<<sqrt(sqr(curx)+sqr(cury))<<".\n\n";
  }
  
  TIMESTAMP("end");
  return 0;
}