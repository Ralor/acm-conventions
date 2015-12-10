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

typedef vector<string> Board;

const int dSz = 4;
int dr[] = {-1,-1,1,1};
int dc[] = {-1,1,1,-1};

bool cell_valid(Board& board, int row, int col) {
  return 0 <= row && 0 <= col && row < sz(board) && col < sz(board[0]);
}

int rec(Board& board, int row, int col) {

  int result = 0;
  for(int i = 0; i < dSz; i++) {
    int n_row = row + dr[i]*2, // new row, col
        n_col = col + dc[i]*2;
    int b_row = row + dr[i],   // row, col with 'B'
        b_col = col + dc[i];
    if( cell_valid(board, n_row, n_col) &&
        board[n_row][n_col] == '#' &&
        board[b_row][b_col] == 'B' ) 
    {
          board[n_row][n_col] = 'W';
          board[b_row][b_col] = '#';
          board[row][col] = '#';
          result = max(result, 1 + rec(board,n_row,n_col));
          board[n_row][n_col] = '#';
          board[b_row][b_col] = 'B';
          board[row][col] = 'W';
    }
  }
  return result;
}

int main() {
#   ifdef _DEBUG
        freopen("f.in", "r", stdin);
#   else
        freopen("f.in", "r", stdin);
        freopen("f.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tests; cin >> tests;
    while (cin.get() != '\n') { }

    while( tests-- ) {
      string t; getline(cin,t);
      vector<string> board(10);
      for(int i = 0; i < 10; i++)
        getline(cin, board[i]);
      int result = 0;
      for(int i = 0; i < sz(board); i++)
        for(int j = 0; j < sz(board[i]); j++)
          if( board[i][j] == 'W' )
            result = max(result, rec(board,i,j));
      cout << result << "\n";
    }



#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
