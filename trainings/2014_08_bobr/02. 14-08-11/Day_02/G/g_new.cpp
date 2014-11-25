/*
  cashcow.cpp
  Cash Cow, MCPC 2013, Problem G
  C++ solution by Michael Goldwasser
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

//ifstream fin("cashcow.in");
const int NUM_ROWS = 12;
const int NUM_COLS = 10;

// board represented as sequence of COLUMNS, each ordered from bottom to top.
vector<vector<char> > board;   

void parseBoard() {
    board.clear();
    for (int i=0; i < NUM_COLS; i++)
        board.push_back(vector<char>(NUM_ROWS,'.'));
    for (int row=NUM_ROWS-1; row >= 0; row--) {
        string temp;
        cin >> temp;
        for (int col=0; col < NUM_COLS; col++)
            board[col][row] = temp[col];
    }
}

int numPieces() {
    int total=0;
    for (int row=NUM_ROWS-1; row >= 0; row--) {
        for (int col=0; col < NUM_COLS; col++)
            if (board[col][row] != '.')
                total++;
    }
    return total;
}

void findComponent(int row, int col, set<pair<int,int> > &component) {
    int delta[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
    for (int k=0; k < 4; k++) {
        int newR = row + delta[k][0];
        int newC = col + delta[k][1];
        if (newR >= 0 && newR < NUM_ROWS && newC >= 0 && newC < NUM_COLS
            && board[col][row] == board[newC][newR]
            && component.find(make_pair(newC,newR)) == component.end()) {
                component.insert(make_pair(newC,newR));
                findComponent(newR, newC, component);
        }
    }
}

// get rid of value from interior, and then pad with it at the end
template <typename T>
void slideAndFill(vector<T> &data, T val) {
    typename vector<T>::iterator boundary = remove(data.begin(), data.end(), val);
    fill(boundary, data.end(), val);
}

void compress() {
    for (int c=0; c < NUM_COLS; c++)
        slideAndFill(board[c], '.');
    slideAndFill(board, vector<char>(NUM_ROWS, '.'));
}

void processClick(int row, int col) {
    if (board[col][row] != '.') {
        set<pair<int,int> > group;
        group.insert(make_pair(col,row));
        findComponent(row, col, group);
        if (group.size() >= 3) {
            for (set<pair<int,int> >::iterator it = group.begin(); it != group.end(); ++it)
                board[it->first][it->second] = '.';
            compress();
        }
    }
}

int main() {
    freopen("cashcow.out","w",stdout);
    freopen("cashcow.in","r",stdin);
    int t;
    while (true) {
        cin >> t;
        if (t == 0) break;
        parseBoard();
        for (int j=0; j<t; j++){
            char c;
            int r;
            cin >> c >> r;
            processClick(r-1, c-'a');  // zero-indexed
        }
        cout << numPieces() << endl;
    }
}

