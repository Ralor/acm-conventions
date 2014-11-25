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
#include <fstream>
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

struct Position {
    short x, y;
    bool IsCalced() const { return x != -1 && y != -1; }
    bool IsWinning() const { return x || y; }
    void SetLosing() { x = y = 0; }
};

Position dp[101][101][101]; //dp[p][q][r], bottom, middle, top

void rec(int p, int q, int r) {
  if( dp[p][q][r].IsCalced() ) 
    return;
  
  if( p <= 1 && q <= 0 && r <= 0 ) {
    dp[p][q][r].SetLosing();
    return;
  }
 
  for(int i = r - 1; i >= 0; --i) {
    rec(p, q, i);
    if (!dp[p][q][i].IsWinning()) {
      dp[p][q][r].x = i;
      dp[p][q][r].y = 2;
      return;
    }
  }

  for(int i = q - 1; i >= 0; --i) {
    rec(p, i, min(r, i));
    if (!dp[p][i][min(r, i)].IsWinning()) {
      dp[p][q][r].x = i;
      dp[p][q][r].y = 1;
      return;
    }
  }

  for(int i = p - 1; i >= 1; --i) {
    rec(i, min(q, i), min(r, i));
    if (!dp[i][min(q, i)][min(r, i)].IsWinning()) {
      dp[p][q][r].x = i;
      dp[p][q][r].y = 0;
      return;
    }
  }

  dp[p][q][r].SetLosing();
}

int main() {
#   ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        //freopen(TASK ".in", "r", stdin);
        //freopen(TASK ".out", "w", stdout);  
        //freopen("info.txt", "r", stdin);
        //freopen("info.txt", "w", stdout);
#   else
        freopen("f.in", "r", stdin);
        freopen("f.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /*ofstream f("test.txt");
    f << "300\n";
    int number = 1;
    for (int k = 0; k <= 100; k++) {
      for (int j = k; j <= 100; j++) {
        for (int i = j; i <= 100; i++) {
          f << number << ' ' << i << ' ' << j << ' ' << k << '\n';
          number++;
        }
      }
    }
    f.close();
    return 0;*/
    
    int tests;
    cin >> tests;
    memset(dp, 0xFF, sizeof dp);
    while (tests--) {
      int test;
      cin >> test;
      cout << test << ' ';


      int p, q, r;
      cin >> p >> q >> r;
      /*if (!p && !q && !r) {
        cout << "W 0 0\n";
        continue;
      }*/

      //dp[p][q][r], bottom, middle, top
      rec(p,q,r);
      if (dp[p][q][r].IsWinning())
        cout << "W " << dp[p][q][r].x + 1 << ' ' << dp[p][q][r].y + 1 << '\n';
      else
        cout << "L\n";
      
      /*int ok = 0;

      // row = 2;
      for(int col = 0; col < r; ++col)
        if( ok = !rec(p,q,col) ) {
          cout << "W " << col+1 << " 3\n";                
          break;
        }

      if( ok ) continue;

      // row = 1;
      for(int col = 0; col < q; ++col)
        if( ok = !rec(p, col, min(col,r)) ) {
          cout << "W " << col+1 << " 2\n";
          break;
        }

      if( ok ) continue;

      // row = 0;
      for(int col = 1; col < p; ++col)
        if( ok = !rec(col, min(col,q), min(col,r)) ) {
          cout << "W " << col+1 << " 1\n";
          break;
        }

      if( ok ) continue;

      cout << "L\n";*/
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
