/*
  cubes.cpp
  Letter Cubes, 2013 Mid-Central Programming Competition, Problem E
  C++ Solution by Michael Goldwasser

  We solve by recursive enumeration, considering the sorted alphabet
  while trying to place each successive alphabet symbol on a
  non-conflicting cube, with conflicts defined for those pairs of
  letters that originally appeared in the same word.
*/  
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
using namespace std;

ifstream fin("cubes.in");
const int MAX_N = 30;
const int MAX_K = 4;
const int MAX_TRIALS = 20;
int N, K;

string alpha;
vector<string> solution;
map<char,set<char> > conflict;

void printSolution(vector<string> &soln) {
    for (int d=0; d < soln.size(); d++) {
        if (d != 0) cout << " ";  // separating space
        cout << soln[d];
    }
    cout << endl;
}

// try to complete partial solution placing letters alpha[j] and onward
// (and make sure to leave parameter the way we found it!)
void solve(int j, vector<string> &partial) {
    if (j == 6*K) {
        if (solution.empty())
            solution = partial;
        else {
            cerr << "Alternative solution found: ";   // shouldn't happen
            printSolution(partial);
        }
    } else {
        // try to add alpha[j] to any one of the cubes
        for (int d=0; d < partial.size(); d++) {
            if (partial[d].size() < 6) {
                bool legal=true;
                for (int c=0; c < partial[d].size(); c++)
                    if (conflict[alpha[j]].find(partial[d][c]) != conflict[alpha[j]].end()) {
                        legal = false; break;
                    }
                if (legal) {
                    partial[d].push_back(alpha[j]);
                    solve(j+1, partial);
                    partial[d].erase(partial[d].size()-1);   // or pop_back in C++11
                }
            }
        }
        // also consider adding new cube
        if (partial.size() < K) {  
            string newest;
            newest.push_back(alpha[j]);
            partial.push_back(newest);
            solve(j+1, partial);
            partial.pop_back();
        }
    }
}

int main(int argv, char** argc) {
    int trial=0;

    while (true) {
        fin >> N;
        if (N == 0) break;

        K = -1;
        trial++;
        solution.clear();
        conflict.clear();
        alpha.clear();

        set<char> tempalpha;
        char extra;
        fin >> extra;
        if (extra != '-')
            tempalpha.insert(extra);
        for (int w=0; w<N; w++) {
            string word;
            fin >> word;
            if (K == -1)
                K = word.size();
            else if (word.size() != K) cerr << "Word " << word << " has inconsistent size" << endl;

            for (int i=0; i<K; i++) {
                tempalpha.insert(word[i]);
                for (int j=0; j<i; j++) {
                    conflict[word[i]].insert(word[j]);
                    conflict[word[j]].insert(word[i]);
                }
            }
        }
        // convert ordered set to string so that we can more easily index within
        alpha = string(tempalpha.begin(), tempalpha.end());

        vector<string> empty;
        solve(0, empty);
        printSolution(solution);

        // some input validity tests (for judges debug only)
        if (alpha.size() != 6 * K) cerr << "Incorrect alphabet size" << endl;
        if (trial > MAX_TRIALS) cerr << "Too many trials: " << trial << endl;
        if (N > MAX_N) cerr << "N is too large: " << N << endl;
        if (K > MAX_K) cerr << "K is too large: " << N << endl;
        if (solution.empty()) cerr << "UNSOLVABLE CASE" << endl;
    }
}

