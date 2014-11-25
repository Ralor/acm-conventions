/*
  sortme.cpp
  Sort Me, MCPC 2013, Problem H
  C++ solution by Michael Goldwasser
*/
#include<iostream>
#include<fstream>
using namespace std;

ifstream fin("sortme.in");
int ordinal[26];
string words[20];

bool comp(string a, string b) {
    for (int j=0; j < a.size(); j++) {
        if (j == b.size()) return false;  // b is prefix of a
        int x = ordinal[a[j] - 'A'];
        int y = ordinal[b[j] - 'A'];
        if (x < y) return true;
        else if (x > y) return false;
    }
    return true; // a is prefix of b
}

int main() {
    int trial = 1;
    while (true) {
        int N;
        fin >> N;
        if (N == 0) break;
        string code;
        fin >> code;
        for (int j=0; j < 26; j++) ordinal[code[j]-'A'] = j;
        for (int j=0; j < N; j++) fin >> words[j];
        sort(words, words+N, comp);
        cout << "year " << trial++ << endl;
        for (int j=0; j<N; j++) cout << words[j] << endl;
    }
}

