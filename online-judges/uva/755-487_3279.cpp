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


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  map<char,char> button;
  button['A'] = '2';
  button['B'] = '2';
  button['C'] = '2';
  button['D'] = '3';
  button['E'] = '3';
  button['F'] = '3';
  button['G'] = '4';
  button['H'] = '4';
  button['I'] = '4';
  button['J'] = '5';
  button['K'] = '5';
  button['L'] = '5';
  button['M'] = '6';
  button['N'] = '6';
  button['O'] = '6';
  button['P'] = '7';
  button['R'] = '7';
  button['S'] = '7';
  button['T'] = '8';
  button['U'] = '8';
  button['V'] = '8';
  button['W'] = '9';
  button['X'] = '9';
  button['Y'] = '9';
  
  int cn; cin>>cn;
  forn(ci,cn) {
    map<string,int> mem;
    int n; cin>>n;
    int mx = 0;
    forn(word, n) {
      string number; cin>>number;
      string standart;
      for(char c : number) 
        if( isdigit(c) )
          standart += c;
        else if( isalpha(c) && c != 'Q' && c != 'Z' )
          standart += button[c];
      mx = max(mx, ++mem[standart]);
    }    
    if( ci )
      cout<<"\n";
    if( mx <= 1 ) {
      cout<<"No duplicates.\n";
    } else {
      for(auto p : mem) if( p.second > 1 )
        cout<<p.first.substr(0,3)<<"-"<<p.first.substr(3)<<" "<<p.second<<"\n";
    }
  }
  
  
  
  TIMESTAMP("end");
  return 0;
}
