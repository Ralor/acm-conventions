/*
  digitsum.cpp
  Digit Sum, MCPC 2013, Problem F
  C++ solution by Michael Goldwasser
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin("digitsum.in");
const int MAX = 14;
const int HALFMAX = (MAX+1)/2;  // length of longest operand

int original[MAX];
int terms[2][HALFMAX];

int computeSum() {
    int sum = 0;
    int base = 1;
    for (int k=0; k < HALFMAX; k++) {
        sum += base * (terms[0][k] + terms[1][k]);
        base *= 10;
    }
    return sum;
}


int main(int argv, char** argc) {
    bool DEBUG = (argv > 1);

    while (true) {
        int N;
        fin >> N;
        if (N==0) break;

        for (int k=0; k<N; k++)
            fin >> original[k];
        sort(original, original+N);  // alphabetic order is numeric order

        // initialize terms array
        for (int k=0; k <HALFMAX; k++)
            terms[0][k] = terms[1][k] = 0;

        int nonzero=0;
        while (original[nonzero] == 0)
            nonzero++;

        int j = N;  // remaining numbers to place

        terms[j%2][(j-1)/2] = original[nonzero];
        j--;
        terms[j%2][(j-1)/2] = original[nonzero+1];
        j--;

        for (int k=0; k < N; k++)
            if (k < nonzero || k > nonzero+1) {
                terms[j%2][(j-1)/2] = original[k];
                j--;
            }

        if (DEBUG)
            for (int a=0; a<2; a++) {
                int b = HALFMAX-1;
                while (terms[a][b] == 0) b--;
                while (b >= 0) {
                    cout << terms[a][b--];
                }
                cout << (a == 0 ? " + " : " = ");
            }

        cout << computeSum() << endl;
    }
}

