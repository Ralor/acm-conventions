/*
  welcome-enumerate.cpp
  Welcome Party, MCPC 2013, Problem A
  Alternate C++ solution by Michael Goldwasser

  This is a less efficient, but correct, solution for solving the
  underlying vertex cover. It enumerates over every possible choice of
  subsets of last-name initials (there are 2^18 of them), adding to it
  the implied first-name groups that must be formed for those not in a
  last-name group.
*/
#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("welcome.in");

const int MAX_FIRST = 26;
const int MAX_LAST = 18;           // we assume this is the smaller of the two limits
bool graph[MAX_FIRST][MAX_LAST];

void reset() {
    for (int a=0; a < MAX_FIRST; a++)
        for (int b=0; b < MAX_LAST; b++)
            graph[a][b] = false;
}       

// utilities for bitcodes
bool testBit(long bitcode, int k) { return ( (1L << k) & bitcode ); }
void setBit(long &bitcode, int k) { bitcode |= (1L << k); }
int numOnes(long bitcode) {
    int count=0;
    for (int k=0; k < MAX_FIRST; k++)
        if (testBit(bitcode, k)) count++;
    return count;
}

int solve() {
    long opposite[MAX_LAST];
    for (int k=0; k < MAX_LAST; k++) {
        opposite[k] = 0;
        for (int j=0; j < MAX_FIRST; j++)
            if (graph[j][k])
                setBit(opposite[k], j);
    }

    int best=MAX_FIRST;   // that many groups will surely suffice
    for (long code=0; code < (1L << MAX_LAST); code++) {
        long mask = 0;
        for (int k=0; k < MAX_LAST; k++)
            if (!testBit(code, k))
                mask |= opposite[k];
        int temp = numOnes(code) + numOnes(mask);
        if (temp < best)
            best = temp;
    }
    return best;
}

int main() {
    while (true) {
        int N;
        fin >> N;
        if (N == 0) break;

        reset();
        for (int t=0; t<N; t++) {
            string first,last;
            fin >> first >> last;
            int j = first[0] - 'A';
            int k = last[0] - 'A';
            if (j < 0 || j >= MAX_FIRST || k < 0 || k >= MAX_LAST)
                cerr << "ILLEGAL NAME: " << first << " " << last << endl;
            else                
                graph[j][k]= true;
        }
        cout << solve() << endl;
    }
}

