#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <valarray>
#include <vector>
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define fst        first
#define snd        second
#define pb         push_back
#define mp         make_pair
#define eb         emplace_back
#define ef         emplace_front
#define mt         make_tuple
#define eps        1e-8
#define inf        int(1e9)
#define linf       llong(4e18)
using namespace std;

struct debug_t {
  template<typename T>
  debug_t& operator << (const T& o) {
#   ifdef LOCAL_DEBUG
    cout<<o<<flush;
#   endif
    return *this;
  }
} debug;

#define TIMESTAMP(msg) debug << "[" msg "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n' 
#define DBG(x) debug << "[" #x "] = " << x << '\n'
#define DOUT(x) debug << x << '\n'
#define _ << " " <<

typedef unsigned char       uchar;
typedef basic_string<uchar> ustring;
typedef long long           llong;
typedef unsigned long long  ullong;
typedef long double         ldouble;
typedef vector<int>         vi;
typedef vector<vi>          vvi;
typedef vector<double>      vd;
typedef vector<vd>          vvd;
typedef pair<int,int>       pii;

const char* REPR[ ] = {
  nullptr, "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
};
int values[17];

pair<int, char> ReadCard() {
  char c;
  cin >> c;
  int x;
  if (c == '1') {
    cin >> c;
    if (c != '0')
      return { 1, c };
    x = 10;
  } else if (isdigit(c))
    x = c - '0';
  else
    x = values[c - 'A'];
  return { x, cin.get() };
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i, n;
  values['A' - 'A'] = 1;
  values['J' - 'A'] = 11;
  values['Q' - 'A'] = 12;
  values['K' - 'A'] = 13;
  cin >> n;
  pair<int, char> cards[5];
  while (n--) {
    for (i = 0; i < 5; i++)
      cards[i] = ReadCard();
    sort(cards, cards + 5);
    do {
      if (cards[0].snd != cards[1].snd)
        continue;
      int x = cards[1].fst;
      auto m = min_element(cards + 2, cards + 5);
      x += m - cards - 1;
      pair<int, char>* prev = nullptr;
      for (i = 2; i < 5; i++)
        if (&cards[i] != m) {
          if (prev) {
            if (*prev > cards[i])
              x += 3;
          } else
            prev = &cards[i];
        }
      x = (x - 1) % 13 + 1;
      if (x == cards[0].fst)
        goto done;
    } while (next_permutation(cards, cards + 5));
    assert(false);
  done:
    for (i = 0; i < 5; i++) {
      if (i)
        cout << ' ';
      cout << REPR[cards[i].fst] << cards[i].snd;
    }
    cout << '\n';
  }
  TIMESTAMP("end");
  return 0;
}
