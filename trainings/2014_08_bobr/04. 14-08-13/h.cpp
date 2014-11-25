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


int len;
int board[1001][3];
int dp[1001][1<<3]; // dp[pos][bin_mask]
int rec(int pos, int bin_mask) {
  if( pos == len )
    return 0;
  if( dp[pos][bin_mask] != -1 )
    return dp[pos][bin_mask];  

  int res = 0;
  for(int i = 0; i < pos; i++)
    debug << " ";
  debug << pos << " : " << bitset<3>(bin_mask) << "\n";
  for(int i = 0; i < sz(ternary_masks); i++)
    if( ternary_mask_fit(ternary_masks[i], bin_mask, pos) ) {
      int t_bin_mask;
      next_binary_mask(ternary_masks[i], t_bin_mask);
      int f = calc_ternary_mask(pos,ternary_masks[i]);     
      int s = rec(pos+1,t_bin_mask);           
      for(int j = 0; j < pos; j++)
        debug << " ";
      debug << pos << ", " << ternary_masks[i]/9 << ternary_masks[i]/3%3 << ternary_masks[i]%3            
            << " : " << f << " + " << s << " = " << f+s << "\n";      
      res = max(res, f+s);
    }
  for(int i = 0; i < pos; i++)
    debug << " ";
  debug << pos << " : best is " << res << "\n";
  return dp[pos][bin_mask] = res;
}

int main() {
#   ifdef _DEBUG
        freopen("h.in", "r", stdin);
#   else
        freopen("h.in", "r", stdin);
        freopen("h.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
        
    // generate valid masks
    for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
        for(int k = 0; k < 3; k++) {
         if( i == 2 && j != 2 ||
             k == 2 && j != 2 ||
             j == 2 && (i != 2 && k != 2) ||
             i == j && j == k && i == 2)
             continue;
         ternary_masks.push_back(i*3*3 + j*3 + k);
        }
    for(int i = 0; i < sz(ternary_masks); i++)
      debug << i << ": " << ternary_masks[i]/9 << ternary_masks[i]/3%3 << ternary_masks[i]%3 << "\n";
    
    int ci = 1;
    while( cin >> len && len != 0 ) {
      memset(dp, -1, sizeof dp);
      for(int i = 0; i < 3; i++)
        for(int j = 0; j < len; j++)
          cin >> board[j][i];
      cout << "Case " << ci << ": " 
           << rec(0,0) << "\n";
    }


#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
