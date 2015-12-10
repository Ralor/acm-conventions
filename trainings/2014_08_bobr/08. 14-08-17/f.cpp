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

/*
typedef vector<string> Board;
struct Cell {
  int r,c;  
  Cell() {}
  Cell(int r,int c) : r(r), c(c) {}
  bool valid(Board& board) {
    return 0 <= r && 0 <= c && r < sz(board) && c < sz(board[0]);
  }
};
int fact(int n) {
  return n <= 1 ? 1 : n*fact(n-1);
}

const int dSz = 4;
const int dr[] = {-1,0,1,0};
const int dc[] = {0,1,0,-1};


// return (pegs left, moves made)
pair<int,int> go(Board& board, vector<Cell>& cells, vector<vi>& used, Cell& cur) {
  pair<int,int> result(sz(cells),inf);
  
  for(int i = 0; i < dSz; i++) {
    Cell nxt(cur.r + dr[i], cur.c + dc[i]);
    if( !used[nxt.r][nxt.c] && nxt.valid(board) ) {
      used
    }
  }

  return result;
}
*/

struct Pos {
    int y, x;

    Pos() { }
    Pos(int i, int j): y(i), x(j) { }

    Pos Offset(int i, int j) const {
        return Pos(y + i, x + j);
    }
};

char field[10][10];
vector<Pos> pieces;
int piecesLeft;
set<llong> cache;
llong mask;

void Put(llong& mask, const Pos& trg) {
    mask |= 1LL << (trg.y * 9 + trg.x);
}

void Take(llong& mask, const Pos& trg) {
    mask &= ~(1LL << (trg.y * 9 + trg.x));
}

bool CanJump(const Pos& which, const Pos& trg) {
    return field[trg.y][trg.x] == '.' &&
        field[(which.y + trg.y) >> 1][(which.x + trg.x) >> 1] == 'o';
}

void Rcsv(int result) {
    static const int deltas[4][2] = {
        { -2, 0 },
        { 2, 0 },
        { 0, -2 },
        { 0, 2 },
    };
    bool fin = true;
    for (int i = 0; i < (int)pieces.size(); i++)
        if (field[pieces[i].y][pieces[i].x] == 'o')
            for (int j = 0; j < 4; j++) {
                Pos trg = pieces[i].Offset(deltas[j][0], deltas[j][1]);
                if (CanJump(pieces[i], trg)) {
                    fin = false;
                    Take(mask, pieces[i]);
                    Take(mask, Pos((pieces[i].y + trg.y) >> 1, (pieces[i].x + trg.x) >> 1));
                    Put(mask, trg);
                    set<llong>::iterator lb = cache.lower_bound(mask);
                    if (lb == cache.end() || cache.key_comp()(mask, *lb)) {
                        cache.insert(lb, mask);
                        field[pieces[i].y][pieces[i].x] = '.';
                        field[(pieces[i].y + trg.y) >> 1][(pieces[i].x + trg.x) >> 1] = '.';
                        field[trg.y][trg.x] = 'o';
                        pieces[i].y += deltas[j][0];
                        pieces[i].x += deltas[j][1];
                        Rcsv(result - 1);
                        pieces[i].y -= deltas[j][0];
                        pieces[i].x -= deltas[j][1];
                        field[trg.y][trg.x] = '.';
                        field[(pieces[i].y + trg.y) >> 1][(pieces[i].x + trg.x) >> 1] = 'o';
                        field[pieces[i].y][pieces[i].x] = 'o';
                    }
                    Take(mask, trg);
                    Put(mask, Pos((pieces[i].y + trg.y) >> 1, (pieces[i].x + trg.x) >> 1));
                    Put(mask, pieces[i]);
                }
            }
    if (fin && result < piecesLeft)
        piecesLeft = result;
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
    
    int tests;
    cin >> tests; 
    string s;
    int i, j;
    while ( tests-- ) {
      /*string s; getline(cin,s);

      //5x9
      Board board(5);
      for(int i = 0; i < 9; i++)
        getline(cin, board[i]);

      vector<Cell> cells;
      for(int i = 0; i < sz(board); i++)
        for(int j = 0; j < sz(board[i]); j++)
          if( board[i][j] == 'o' )
            cells.push_back(Cell(i,j));
      int perm_cnt = fact(sz(cells));
      
      
      pair<int,int> result(sz(cells), inf);
      for(int i = 0; i < perm_cnt; i++) {
        vector< vector<int> > used(sz(board), vi(sz(board[0],0)));

        pair<int,int> cur_result(sz(cells),inf);
        for(int j = 0; j < sz(cells); j++)
          if( !used[cells[i].r][cells[i].c] )
            cur_result = min(cur_result, go(board,cells,used,cells[i]));
        result = min(result, cur_result);
        next_permutation(all(cells));
      }*/

        int n = 0;
        mask = 0x00;
        cache.clear();
        pieces.clear();
        for (i = 0; i < 5; i++) {
            cin >> s;
            for (j = 0; j < (int)s.length(); j++) {
                field[i][j] = s[j];
                if (s[j] == 'o') {
                    pieces.push_back(Pos(i, j));
                    Put(mask, Pos(i, j));
                    n++;
                }
            }
        }
        piecesLeft = n;
        Rcsv(n);
        cout << piecesLeft << ' ' << n - piecesLeft << '\n';
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
