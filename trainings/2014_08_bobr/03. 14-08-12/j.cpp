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
#ifdef _DEBUG
#   include <conio.h>
#endif

#ifndef _DEBUG
#   undef VERBOSE
#endif

#define eps      1e-8
#define inf      (1000 * 1000 * 1000)
#define linf     (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)   ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)    int((x).size())
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define mp       make_pair

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;

struct Cleaner {
  double x,y;
  double D,d;
  double sqrR, sqrr;
  Cleaner() {}
  Cleaner(double x, double y, double D, double d) : x(x), y(y), D(D), d(d), sqrR(sqr(D+d)), sqrr(sqr(D-d)) {}
  bool contains(double x, double y) const {
    double dist = sqr(x - this->x) + sqr(y - this->y);
    return dist <= sqrR && sqrr <= dist;
  }
  bool intersects(Cleaner other) const {
    Cleaner me = *this;    
    double dist = sqrt(sqr(x-other.x)+sqr(y-other.y));
    if( dist > other.sqrR + me.sqrR )
      return false;
    return true;
  }
};

void find_intersections(vector< vector<int> >& rel, vector<Cleaner>& cleaners) {
  rel.resize(sz(cleaners));
  for(int i = 0; i < sz(cleaners)-1; i++)
    for(int j = i+1; j < sz(cleaners); j++)
      if( cleaners[i].intersects(cleaners[j]) ) {
        rel[i].push_back(j); rel[j].push_back(i);
      }
}


int main() {
#   ifdef _DEBUG
        freopen("j.in", "r", stdin);
#   else
        freopen("j.in", "r", stdin);
        //freopen("j.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int cn; cin >> cn;

    for(int ci = 1; ci <= cn; ci++) {
      int n; cin >> n;      
      vector<Cleaner> cleaners; cleaners.reserve(n);
      for(int i = 0; i < n; i++) {
        double x,y,D,d;
        cin >> x >> y >> D >> d;
        cleaners.push_back(Cleaner(x+1000,y+1000,D,d));        
      }
      
      double step = 0.1, sqr_step = sqr(step);
      int steps = (int)floor(2000 / step + eps);
      bool need_to_fix_answer = false;//(2000 - steps * step) > eps;

      vector<Cleaner> cur_buf;

      double ans = 0;
      double x,y;
      for(int i = 0; i < steps; i++) {
        x = i*step + step/2;
        for(int j = 0; j < steps; j++) {
          y = j*step + step/2;     
          int found = 0;
          if( cur_buf.empty() ) {            
            for(int k = 0; k < n; k++)            
              if( cleaners[k].contains(x,y) ) {
                ans += sqr_step;  
                cur_buf.assign(all(cleaners[k]));
                
                break;
              }            
          } else {
            for(int k = 0; k < sz(cur_buf); k++)
              if( cur_buf[k].contains(x,y) ) {
                ans += sqr_step;  
                ++found;
                break;
              }
            if( !found ) {
              cur_buf.clear();
            }
          }
            
        }
      }

      if( need_to_fix_answer ) {
        step = 2000 - steps * step;
        sqr_step = step*step;
        steps = (int)floor(2000 / step + eps);        
        for(int i = 0; i < steps; i++) {
          double x = 2000 - step/2, y = i*step + step/2;
          for(int j = 0; j < n; j++)
            if( cleaners[j].contains(x,y) ) {
              ans += sqr_step;              
              break;
            }
        }
        for(int j = 0; j < steps-1; j++) {
          double x = j*step + step/2, y = 2000 - step/2;
          for(int i = 0; i < n; i++)
            if( cleaners[i].contains(x,y) ) {
              ans += sqr_step;
              break;
            }
        }
      }
      cout << "Case " << ci << ": " << ans << "\n";
    }

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
