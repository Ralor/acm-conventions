/*
  missing.cpp
  Missing Pages, MCPC 2013, Problem C
  C++ solution by Michael Goldwasser
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("missing.in");

int main() {
    int N, P;
    while (true) {
        fin >> N;
        if (N == 0) break;
        fin >> P;

        int small;
        if (P <= N/2)
            small = ((P+1)/2) * 2 - 1;
        else
            small = ((N-P)/2) * 2 + 1;

        vector<int> missing(4);

        missing[0] = small;
        missing[1] = small+1;
        missing[2] = N-small;
        missing[3] = N-small+1;
        //      cout << "N=" << N << " P=" << P << endl;
        //      cout << missing[0] << " " << missing[1] << " " << missing[2] << " " << missing[3] << endl;
        for (int k=0; k < 4; k++)
            if (missing[k] == P)
                missing.erase(k + missing.begin());

        cout << missing[0] << " " << missing[1] << " " << missing[2] << endl;
    }
}

