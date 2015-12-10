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
#include <assert.h>
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
#define size(x) int(x.size())
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

int getVal(const string& str)
{
  int res  = 0;
  int i = 0;
  while(i < size(str))
  {
    char a = str[ i ];
    int va = 0;
    switch(a)
      {
        case 'I':{va = 1; break;}
        case 'V':{va = 5; break;}
        case 'X':{va = 10; break;}
        case 'L':{va = 50; break;}
        case 'C':{va = 100; break;}
        case 'D':{va = 500; break;}
        case 'M':{va = 1000; break;}
      }
    if( i+1 < size(str) )
    {
      char b = str[ i + 1 ];
      int vb = 0;
      switch (b)
      {
        case 'I':{vb = 1; break;}
        case 'V':{vb = 5; break;}
        case 'X':{vb = 10; break;}
        case 'L':{vb = 50; break;}
        case 'C':{vb = 100; break;}
        case 'D':{vb = 500; break;}
        case 'M':{vb = 1000; break;}
      }    
      // 0 1 2 3 4 5
      if( vb > va)
      {
        vb -= va;
        res += vb;
        i += 2;
      }
      else
      {
        res += va;
        //res = res * 10 + vb;
        ++i;
      }
    }
    else
    {
        res += va;
        //res = res * 10 + vb;
        ++i;
    }
    
  }
  return res;
}
struct digit{
  int val;
  string script;
};
vector < digit > row;
void getStr(int n, string& str)
{
  forn(i,13)
    while( n >=    row[i].val ){
      n -= row[ i ].val;
   
     //cout << row[i].script << endl;
      str += row[i].script;
    }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  row.resize(13);
  row[ 0 ].val = 1000;
  row[ 0 ].script = "M";
  
  row[ 1 ].val = 900;
  row[ 1 ].script = "CM";
  
  
  row[ 2 ].val = 500;
  row[ 2 ].script = "D";
  
  row[ 3 ].val = 400;
  row[ 3 ].script = "CD";
 
  row[ 4 ].val = 100;
  row[ 4 ].script = "C";
  
  row[ 5 ].val = 90;
  row[ 5 ].script = "XC";
  
  row[ 6 ].val = 50;
  row[ 6 ].script = "L";
  
  row[ 7 ].val = 40;
  row[ 7 ].script = "XL";
  
  row[ 8 ].val = 10;
  row[ 8 ].script = "X";
  
  row[ 9 ].val = 9;
  row[ 9 ].script = "IX";
  
  row[ 10 ].val = 5;
  row[ 10 ].script = "V";
  
  
  row[ 11 ].val = 4;
  row[ 11 ].script = "IV";
  
  row[ 12 ].val = 1;
  row[ 12 ].script = "I";
  int cas = 0;
  int n;
  while(cin >> n && n != 0){
    ++cas;
    int sum = 0;
    string str;
    forn(i,n)
    {
      cin >> str;
      sum += getVal(str);
    }
    string res;
    string tnum;
    tnum.clear();
    res.clear();
    getStr(sum ,res);
    getStr(cas ,tnum);
    
    cout << "Case "<< tnum<< ": " <<  res << "\n";
  }
  TIMESTAMP("end");
  return 0;
}
