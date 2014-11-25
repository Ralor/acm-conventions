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
#ifdef _DEBUG
#   include <conio.h>
#endif

#ifndef _DEBUG
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

using namespace std;

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

const int maxLength = 50;

string ToString(int x) {
    string result;
    do
        result += char(x % 10 + '0');
    while (x /= 10);
    return string(result.rbegin(), result.rend());
}

int GetDivLen(int a, int b) {
    int result = ToString(a / b).length();
    int x = a % b;
    if (!x)
        return result;
    set<int> s;
    int i = 0;
    while (s.find(x) == s.end()) {
        s.insert(x);
        x = (x * 10) % b;
        i++;
        if (!x)
            return result + 1 + i;
    }
    return result + 3 + s.size();
}

pair<string,int> get_res(int a, int b) {
  pair<string,int> ppp;
  ostringstream out;
  bool dot = false; int dot_pos = -1;  
  out << a/b;
  int int_sz = sz(out.str());
  if( a%b > 0 ) {
    a %= b; a *= 10; out << '.'; 
    dot = true; dot_pos = sz(out.str())-1;
    for(int i = 0; i < maxLength; i++)
      if( a > 0 ) 
        out << a/b, a %= b, a *= 10;
      else 
        break;    
  }
  
  string s = out.str();
  ppp.first = s;
  
  bool rep_found = false;
  int mx_frac = 0, mx_len = 0, mx_offset = 0;
  if( dot ) {
    s = s.substr(dot_pos+1);
    mx_frac = sz(s);
    for (int offset = 0; offset < (int)s.length(); offset++) {
        for (int len = 1; len <= ((int)s.length()  - offset) >> 1; len++) {
          bool found = true;
          for(int j = offset + len; j <= sz(s) - offset - len; j += len)
            for(int k = 0; k < len; k++)
              found &= s[offset + k] == s[j + k];
          if( found ) {
            rep_found = true;
            mx_offset = offset; mx_len = len;
            offset = len = inf; // alternative to "goto"
            break;
          }
        }
    }
  }

  ppp.second = int_sz;
  if( dot && !rep_found ) 
    ppp.second += 1 + mx_frac;  
  if( dot && rep_found )
    ppp.second += 1 + mx_offset + 2 + mx_len;
  return ppp;
}

//#include <fstream>

short res[] = {1,3,5,5,5,6,10,10,10,10,10,10,10,11,11,11,20,20,22,22,22,22,26,26,26,26,26,26,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,50,50,50,50,50,50,50,50,50,50,50,50,62,62,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,100,100,100,100,100,100,100,100,100,100,100,100,112,112,112,112,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,170,170,170,170,170,170,170,170,170,170,170,170,182,182,184,184,184,184,184,184,184,184,184,184,184,184,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,226,226,226,226,226,226,232,232,232,232,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,260,260,260,260,260,260,266,266,266,266,266,266,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,316,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,340,346,346,346,346,346,346,370,370,370,370,370,370,370,370,370,370,370,370,382,382,382,382,386,386,386,386,386,386,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,422,422,422,422,422,422,422,422,422,422,422,422,422,422,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,436,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,464,490,490,490,490,494,494,494,494,494,494,494,494,502,502};

int main() {
#   ifdef _DEBUG
        freopen("f.in", "r", stdin);
#   else
        freopen("f.in", "r", stdin);
        freopen("f.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; 
    while( cin >> n && n) {
      cout << res[n-1] << "\n";
    }

    //debug << GetDivLen(1, 3) << '\n';
    //debug << GetDivLen(4, 2) << '\n';
    //debug << GetDivLen(1, 4) << '\n';
    //debug << GetDivLen(10, 3) << '\n';
    //debug << GetDivLen(1, 7) << '\n';
    //debug << GetDivLen(1, 45) << '\n';
    //
    //vector<int> a(501,0);
    //for(int n = 1; n <= 500; n++) {
    //  int best = a[n-1];
    //  for(int i = 1; i <= n; i++)        
    //    best = max(best, max(GetDivLen(i,n), GetDivLen(n,i)));
    //  cout << n << "\n";
    //  a[n] = best;      
    //}


    //ofstream out("test.txt");
    //out << "{" << a[0];
    //for(int i = 2; i <= 500; i++)
    //  out << "," << a[i];
    //out << "};";
    //out.close();
   
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
