#include "testlib.h"
#include <cassert>
#include <fstream>
#include <set>
#include <iostream>

using namespace std;

typedef pair<int, int> pii;

int main(int argc, char * argv[])
{
    setName("check and score user output for game \"Balda\"");
    registerTestlibCmd(argc, argv);
    
    int score = 0;
    
    string lang = inf.readString();
    string word = inf.readString();
    size_t n = word.length();
    
    assert(lang == "ru" || lang == "en" || lang == "tr");
    assert(n % 2 == 1);
    assert(n >= 5 && n <= 11);
    
    set<string> dict;
    while (!inf.seekEof()) {
        string word = inf.readToken();
        dict.insert(word);
    }
#ifndef NSUTS
    fprintf(stderr, "Loaded %s dictionary with %d words\n", lang.c_str(), dict.size());
#endif
    if (lang == "en") assert(dict.count("cat"));
    if (lang == "tr") assert(dict.count("kedi"));
    if (lang == "ru") assert(dict.count(string() + char(170) + char(174) + char(226)));
    
    set<string> used;
    assert(dict.count(word));
    used.insert(word);
    
    vector<string> field(n, string(n, '.'));
    field[n/2] = word;
    
    int letters = ouf.readInt();
    for (int lt = 0; lt < letters; ++lt) {
        int r = ouf.readInt(1, n);
        int c = ouf.readInt(1, n);
        string new_letter = ouf.readToken();
        string new_word = ouf.readToken();
        int sr = ouf.readInt(1, n);
        int sc = ouf.readInt(1, n);
        string moves = ouf.readToken();
        
        if (new_letter.length() > 1) quit(_pe, "user wrote string instead letter");
        if (field[r-1][c-1] != '.') quit(_pe, "the cell already used");
        if (new_word.length() != 1 + moves.length()) quit(_pe, "number of moves should be length of the new word minus one");
        
        field[r-1][c-1] = new_letter[0];
        
        set<pii> positions;
        
        int cr = sr;
        int cc = sc;
        
        for (int i = 0; i < new_word.length(); ++i) {
            positions.insert(pii(cr, cc));
            if (field[cr - 1][cc - 1] != new_word[i]) quitf(_pe, "%d-th position in the word does not match field (%d, %d)", i, cr, cc); 
            if (i < moves.length()) {
                if (moves[i] == 'u') cr -=1; else
                if (moves[i] == 'd') cr +=1; else
                if (moves[i] == 'l') cc -=1; else
                if (moves[i] == 'r') cc +=1; else
                quit(_pe, "wrong command in moves");
            }
            
            if (cr < 1 || cr > n || cc < 1 || cc > n) quit(_pe, "position outside the field");
        }
        
        if (positions.count(pii(r, c)) == 0) quit(_pe, "new letter does not covered");
        if (positions.size() != new_word.length()) quit(_pe, "the same cell was visited twice"); 
        
        if (dict.count(new_word) == 0) quitf(_wa, "%s-dict does not contain word '%s'", lang.c_str(), new_word.c_str());
        if (used.count(new_word)) quitf(_wa, "word '%s' already used", new_word.c_str());
        
        used.insert(new_word);
        
        score += new_word.length();
    }

    score = score * 1000LL / (n*n);
#ifdef NSUTS
    printf("%d\n", score);
#else
    quitf(_ok, "Score: %d", score);
#endif
}
