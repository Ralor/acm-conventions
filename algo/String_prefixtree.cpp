#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <fstream>
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
# undef VERBOSE
#endif
#ifdef NDEBUG
#define VERBOSE
#endif

#define eps 1e-8
#define inf (1000 * 1000 * 1000)
#define linf (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x) ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x) int((x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define mp make_pair

using namespace std;

typedef unsigned uint;
typedef long long llong;
typedef unsigned long long ullong;
typedef long double ldouble;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
struct debug_t {
  template <typename T>
  debug_t& operator<<(const T& value) {
# ifdef VERBOSE
    cout << value;
# endif
    return *this;
  }
} debug;

struct Vertex {
  map<char,int> nxt;
  bool leaf;
  Vertex(bool leaf = false) : leaf(leaf) {}
};
typedef vector<Vertex> Trie;

int trie_try_add_edge(Trie& trie, int index, char edge_symbol) {  
  map<char,int>& nxt = trie[index].nxt;
  map<char,int>::iterator lb = nxt.lower_bound(edge_symbol);
  
  if( lb != nxt.end() && edge_symbol == lb->first )
    return lb->second;  
  
  int new_vertex = sz(trie);
  nxt.insert(lb, mp(edge_symbol,new_vertex));
  trie.push_back(Vertex());
  return new_vertex;
}
void trie_add_string(Trie& trie, const string& s) {
  int ind = 0;
  for(int i = 0; i < sz(s); i++) {
    ind = trie_try_add_edge(trie, ind, s[i]);
  }
  trie[ind].leaf = true;
}
Trie& get_trie(const vector<string>& strings) {
  Trie *trie = new Trie(); trie->push_back(Vertex());
  for(int i = 0; i < sz(strings); i++)
    trie_add_string(*trie, strings[i]);
  return *trie;
}
bool trie_find(Trie& trie, const string& s) {
  int ind = 0;
  for(int i = 0; i < sz(s); i++) {
    map<char,int>& nxt = trie[ind].nxt;
    map<char,int>::iterator lb = nxt.lower_bound(s[i]);    
    if( lb != nxt.end() && s[i] == lb->first )        
      ind = lb->second;
    else
      return false;
  }
  return trie[ind].leaf == true;
}

int main() {
  //freopen(TASK ".in", "r", stdin);
  //freopen(TASK ".out", "w", stdout);
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //freopen("info.txt", "r", stdin);
  //freopen("info.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);  

  string s; 
  vector<string> inp;
  while(cin >> s) 
    inp.push_back(s);

  Trie trie(get_trie(inp));

  if( trie_find(trie, "Hello!") )
    cout << "Yes we can!" << "\n";
  
  return 0;
}
