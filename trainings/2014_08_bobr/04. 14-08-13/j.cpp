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

#ifndef _DEBUG
#   undef VERBOSE
#endif

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;

const int MAX_WORD_LENGTH = 20;
const int MAX_WORDS_IN_SENTENCE = 100;
const int MAX_SENTENCE_LENGTH = MAX_WORD_LENGTH * MAX_WORDS_IN_SENTENCE + MAX_WORDS_IN_SENTENCE - 1;
const int TOTAL_WORDS = 20000;
const int TOTAL_SENTENCES = 1000 + 1000;
const int MAX_FRAGMENT_SIZE = 5;
const char* STUDENT_NAME = "joe";//lowercase

typedef short WordId;

struct Sentence {
    vector<WordId> wordIds;

    void Append(WordId wordId) { wordIds.push_back(wordId); }
    WordId GetWord(int i) const { return wordIds[i]; }
    int GetWordsCount() const { return wordIds.size(); }
};

struct TrieNode {
    map<WordId, TrieNode*> edges;

    struct Result {
        TrieNode* node;
        bool inserted;

        Result(TrieNode* n, bool b): node(n), inserted(b) { }
    };

    ~TrieNode() {
        Clear();
    }

    void Clear() {
        for (map<WordId, TrieNode*>::iterator it = edges.begin(); it != edges.end(); it++)
            delete it->second;
        edges.clear();
    }

    Result Get(WordId wordId) {
        map<WordId, TrieNode*>::iterator lb = edges.lower_bound(wordId);
        if (lb != edges.end() && !edges.key_comp()(wordId, lb->first))
            return Result(lb->second, false);
        TrieNode* node = new TrieNode;
        edges.insert(lb, make_pair(wordId, node));
        return Result(node, true);
    }
};

struct SearchResult {
    WordId id;
    bool unknown;

    SearchResult(WordId n, bool b): id(n), unknown(b) { }
};

int maxFragmentSize;
map<string, WordId> wordMap;
TrieNode trie;

bool IsDelimiter(char c) {
    return (bool)strchr(".,:;?!", c);
}

SearchResult RecognizeWord(const string& word) {
    string lower;
    lower.reserve(word.length());
    for (unsigned char i = 0; i < (int)word.length(); i++)
        lower += (char)tolower(word[i]);
    map<string, WordId>::iterator lb = wordMap.lower_bound(lower);
    if (lb != wordMap.end() && !wordMap.key_comp()(lower, lb->first))
        return SearchResult(lb->second, false);
    WordId wordId = wordMap.size();
    wordMap.insert(lb, make_pair(lower, wordId));
    return SearchResult(wordId, true);
}

void ReadDictionary() {
    deque<TrieNode*> dq;
    string s;
    while (cin >> s, s[0] != '*')
        if (!IsDelimiter(s[0])) {
            WordId wordId = RecognizeWord(s).id;
            dq.push_back(&trie);
            for (deque<TrieNode*>::iterator it = dq.begin(); it != dq.end(); it++)
                *it = (*it)->Get(wordId).node;
            if ((int)dq.size() >= maxFragmentSize)
                dq.pop_front();
        } else
            dq.clear();
}

//Returns true if the sentence was not understood.
bool Memorize(const Sentence& sentence) {
    deque<TrieNode*> dq;
    bool unknown = false;
    for (int i = 0; i < sentence.GetWordsCount(); i++) {
        dq.push_back(&trie);
        for (deque<TrieNode*>::iterator it = dq.begin(); it != dq.end(); it++) {
            TrieNode::Result next = (*it)->Get(sentence.GetWord(i));
            if (next.inserted)
                unknown = true;
            *it = next.node;
        }
        if ((int)dq.size() >= maxFragmentSize)
            dq.pop_front();
    }
    return unknown;
}

void Process(const Sentence& sentence, const string& asIs) {
    if (Memorize(sentence) && sentence.GetWordsCount() > 1)
        cout << "What does the sentence \"" << asIs << "\" mean?\n";
}

void Practice() {
    string sentenceAsIs;
    sentenceAsIs.reserve(MAX_SENTENCE_LENGTH);
    Sentence sentence;
    string s;
    while (cin >> s, s[0] != '#') {
        if (!IsDelimiter(s[0])) {
            SearchResult found = RecognizeWord(s);
            if (found.unknown)
                cout << "What does the word \"" << s << "\" mean?\n";
            sentence.Append(found.id);
            if (!sentenceAsIs.empty())
                sentenceAsIs += ' ';
            sentenceAsIs += s;
        } else {
            Process(sentence, sentenceAsIs);
            sentence = Sentence();
            sentenceAsIs.clear();
        }
    }
    if (sentence.GetWordsCount())
        Process(sentence, sentenceAsIs);
}

int main() {
    ios_base::sync_with_stdio(false);    
    cin.tie(NULL);
#   ifndef _DEBUG
        freopen("j.in", "r", stdin);
        freopen("j.out", "w", stdout);
#   endif
    int caseNum = 1;
    while (cin >> maxFragmentSize) {
        cout << "Learning case " << caseNum++ << '\n';
        wordMap.clear();
        wordMap[STUDENT_NAME] = 0;
        trie.Clear();

        ReadDictionary();
        Practice();

        cout << '\n';
    }
}
