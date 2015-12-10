/*
  welcome-matching.cpp
  Welcome Party, MCPC 2013, Problem A
  C++ solution by Michael Goldwasser

  This particular solution is based on solving the underlying vertex cover problem
  by computing a maximum matching of the bipartite graph (as a simple network flow).

  If the input filename is given as an explicit command-line argument,
  the program will also output its solution, and a certificate of optimality.
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Note: code is written assuming any names may be used, even though by problem
// statement, last names will be restricted to first 18 characters of the alphabet.
bool graph[26][26];
int match[52];   // left side are 0-25, right 26-51
int numMatched;

void reset() {
    for (int a=0; a<26; a++) {
        for (int b=0; b<26; b++)
            graph[a][b] = false;
    }
    for (int j=0; j<52; j++) match[j] = -1;
}       


// called on odd-length augmenting path
bool augmentRecurse(vector<int>& path, bool used[]) {
    int left = path[path.size()-1];
    for (int right=0; right < 26; right++) {
        int bigRight = 26+right;
        if (graph[left][right] && match[left] != bigRight && !used[bigRight]) {
            path.push_back(bigRight); used[bigRight] = true;
            if (match[bigRight] == -1)
                return true; // success
            else {
                path.push_back(match[bigRight]); used[match[bigRight]] = true;
                if (augmentRecurse(path, used))
                    return true;   // leave path intact
                else {
                    used[path[path.size()-1]] = false; path.pop_back(); 
                    used[path[path.size()-1]] = false; path.pop_back();
                }
            }
        }
    }
    return false;
}

/* Augment matching if possible and return true. Otherwise false. */
bool augmentPath() {
    vector<int> path;
    bool used[52];

    for (int left=0; left<26; left++) {
        if (match[left] == -1) {
            path.clear();
            for (int j=0; j<52; j++) used[j] = false;
            path.push_back(left); used[left] = true;
            if (augmentRecurse(path, used)) {   // success
                for (int j=0; j < path.size(); j += 2) {
                    int a = path[j];
                    int b = path[j+1];
                    match[a] = b;
                    match[b] = a;
                }
                return true;
            }
        }
    }
    return false;
}

int solve() {
    numMatched = 0;
    while (augmentPath()) numMatched++;
    return numMatched;
}


/* The following is only used to provide verbose description of solutions. */
#include <set>
void printCertificate() {
    int level[52];
    for (int k=0; k<52; k++)
        level[k] = ((match[k] == -1) ? 0 : -1);

    int d = 1;
    bool change = true;
    while (change) {
        change = false;
        for (int k=0; k<52; k++)
            if (level[k] == -1) {
                bool left = k < 26;
                int val = k % 26;
                for (int j=0; j<26; j++) {
                    int bigJ = j + (left ? 26 : 0);
                    if (level[bigJ] == d-1 && match[k] != bigJ) {
                        if (left ? graph[val][j] : graph[j][val]) {
                            level[k] = d;
                            level[match[k]] = d+1;
                            change = true;
                        }
                    }
                }
            }
        d += 2;
    }

    string left,right;
    for (int j=0; j<26; j++) {
        if (level[j] % 2)
            left += char('A'+j);
        if (level[26+j] > 0 && level[26+j] % 2)
            right += char('A'+j);
    }

    cout << "This can be achieved using first initials (" << left;
    cout << ") and last initials (" << right << ")" << endl;

    cout << "This is required because of following incompatible people:" << endl;
    for (int j=0; j<26; j++)
        if (match[j] != -1)
            cout << " " << char('A'+j) << char('A'+match[j]-26);
    cout << endl;
}


int main(int argc, char *argv[]) {
    ifstream fin;
    bool CERTIFICATE = false;

    if (argc > 1) {
        CERTIFICATE = true;
        fin.open(argv[1]);
    } else
        fin.open("welcome.in");

    while (true) {
        int N;
        fin >> N;
        if (N == 0) break;

        reset();
        for (int j=0; j<N; j++) {
            string first,last;
            fin >> first >> last;
            graph[first[0] - 'A'][last[0] - 'A'] = true;
        }
        cout << solve() << endl;
        if (CERTIFICATE) printCertificate();
    }
}

