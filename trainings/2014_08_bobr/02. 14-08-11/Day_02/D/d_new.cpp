/*
  paradox.cpp
  Probability Paradox, MCPC 2013, Problem D
  C++ solution by Michael Goldwasser
*/

#include <iostream>
#include <cstdio>
#include <string>
//#include <fstream>
#include <vector>
#include <map>
using namespace std;

const int MAXLEN = 9;
int DEBUG = 0;
long long MAXVAL;

// support for working with fractions
long long gcd(long long a, long long b) {
    if (DEBUG > 0) MAXVAL = max(MAXVAL, max(a,b));
    return (b ? gcd(b, a % b) : a);
}
class Fraction {
public:
    long long n,d;    // numerator and denominator left public for convenience

    Fraction(long long num=0, long long denom=1) : n(num), d(denom) {
        long long temp = gcd(n,d);              // need gcd definition from elsewhere
        if ((temp < 0) != (denom < 0))
            temp = -temp;                  // reverse sign
        n /= temp;
        d /= temp;
    }

    bool operator<(const Fraction& other) const {
        return (n*other.d < other.n*d);
    }
    bool operator==(const Fraction& other) const {
        return (n == other.n && d == other.d);        // since already reduced
    }
    bool operator!=(const Fraction& other) const {
        return (n != other.n || d != other.d);
    }
    Fraction operator+(const Fraction& other) const {
        return Fraction(n*other.d + d*other.n, d*other.d);
    }
    Fraction operator-(const Fraction& other) const {
        return Fraction(n*other.d - d*other.n, d*other.d);
    }
    Fraction operator*(const Fraction& other) const {
        return Fraction(n*other.n, d*other.d);
    }
    Fraction operator/(const Fraction& other) const {
        return Fraction(n*other.d, d*other.n);
    }
};
ostream& operator<<(ostream& out, Fraction& f) {
    out << f.n;
    if (f.d > 1)
        out << "/" << f.d;
    return out;
}


const int MAX_M = 2*MAXLEN + 1;
Fraction coef[MAX_M][1 + MAX_M];  // prob(A|S) = coef[S][M] + sum(coef[S][T] * prob(A|T))

void dumpEquations(map<string,int> &index);   // used only for debugging; defined at bottom

// find the key in the index having the greatest overlap with a suffix of newest
int transition(map<string,int> &index, string newest) {
    for (int k=0; k < newest.size(); k++) {
        map<string,int>::iterator it = index.find(newest.substr(k));
        if (it != index.end())
            return it->second;   // found it
    }
    return 0;  // index of empty string
}

Fraction solve(string A, string B) {
    // The following is for judging validity only
    MAXVAL = 0;
    if (DEBUG > 1) cout << "Solving " << A << " vs " << B << endl;

    map<string,int> index;    // map from relevant string to unique index (with empty string as 0)
    index[""] = 0;
    int n = A.size();
    string players[] = {A,B};
    for (int k=0; k <= n; k++)
        for (int j=0; j<2; j++) {
            string sub = players[j].substr(0,k);
            if (index.find(sub) == index.end()) {
                int i = index.size();
                index[sub] = i;
            }
        }

    int M = index.size();      // number of states

    // reset coef to zeros
    for (int j=0; j < M; j++)
        for (int k=0; k < M+1; k++)
            coef[j][k] = 0;
    coef[index[A]][M] = 1;        // A has won;  prob(A|A) = 1
    coef[index[B]][M] = 0;        // A has lost; prob(A|B) = 0

    for (map<string,int>::iterator it = index.begin(); it != index.end(); ++it) {
        string sub = it->first;
        int i = it->second;
        if (sub.size() < n) {       // not either player's complete string
            coef[index[sub]][transition(index, sub+"H")] = Fraction(1,2);
            coef[index[sub]][transition(index, sub+"T")] = Fraction(1,2);
        }
    }
    dumpEquations(index);  // for debugging only

    // row reduce to eliminate variables
    for (int r=M-1; r >= 0; r--) {
        // eliminate variable prob(A|r) from all equations by subtracting off multiple of row r

        // first eliminate use of variable r in its own row
        // if prob(A|r)  =  t * prob(A|r) + stuff, then prob(A|r) = stuff / (1-t).
        if (coef[r][r] != 0) {
            Fraction denom = (Fraction(1) - coef[r][r]);
            for (int k=0; k < M+1; k++)
                coef[r][k] = coef[r][k] / denom;
            coef[r][r] = 0;
        }

        for (int a=0; a < M; a++) {
            Fraction factor = coef[a][r];
            if (factor != 0) {
                for (int k=0; k<M+1; k++) {
                    if (coef[r][k] != 0)
                        coef[a][k] = coef[a][k] + factor * coef[r][k];
                }
                coef[a][r] = 0;
            }
        }
        if (DEBUG > 1) cout << "After clearing col " << r << endl;
        dumpEquations(index);  // for debugging only
    }

    return coef[0][M];  // constant value of empty string probability
}

int main(int argv, char** argc) {
//fstream fin("paradox.in");
    freopen("paradox.out","w",stdout);
    freopen("paradox.in","r",stdin);

    DEBUG = 0;
    //ifstream fin;
    //fin.open((argv > 1) ? argc[1] : "paradox.in");  // allow command line argument to override input file name
    while (true) {
        string playerA,playerB;
        cin >> playerA;
        if (playerA == "$") break;
        cin >> playerB;
        if (playerA.size() != playerB.size() || playerA.size() > MAXLEN)
            cerr << "INVALID INPUT: " << playerA << " " << playerB << endl;
        Fraction answer = solve(playerA, playerB);
        cout << answer.n << "/" << answer.d;
        if (DEBUG > 0) cout << "\t\t(max value " << MAXVAL << ")";
        cout << endl;


    }
}


// used only for debugging
void dumpEquations(map<string,int> &index) {
    if (DEBUG > 1) {
        int M = index.size();
        vector<string> states(M);
        for (map<string,int>::iterator it = index.begin(); it != index.end(); ++it) {
            if (it->first == "")
                states[it->second] = "''";
            else
                states[it->second] = it->first;
        }
        for (int j=0; j < M; j++) {
            cout << states[j] << " = ";
            int terms=0;
            for (int k=0; k < M; k++) {
                if (coef[j][k] != 0) {
                    if (++terms > 1)
                        cout << " + ";
                    cout << "(" << coef[j][k] << ")*" << states[k];
                }
            }
            if (coef[j][M] != 0) {
                if (++terms > 1)
                    cout << " + ";
                cout << coef[j][M];
                terms++;
            }
            if (terms == 0)
                cout << 0;
            cout << endl;
        }
    }
}

