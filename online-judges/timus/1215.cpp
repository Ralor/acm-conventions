#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i,n) for(int i = 0; i < (n); i++)

struct debug_t {
  template<typename T>
  debug_t& operator << (const T& o) {
#   ifdef LOCAL_DEBUG
    cout<<o<<flush;
#   endif
    return *this;
  }
} debug;

#define TIMESTAMP(msg) debug << "[" << msg << "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n' 
#define DBG(x) debug << "[" #x "] = " << x << '\n'

inline bool eq(double a, double b) {
  return fabs(a-b) <= 1e-8;
}

struct Point {
  double x,y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double operator % (const Point& p) const { return x*p.x + y*p.y; }
  double operator * (const Point& p) const { return x*p.y - y*p.x; }
  Point operator * (const double& m) const { return Point(x*m, y*m); }
  Point operator + (const Point& p) const { return Point(x+p.x, y+p.y); }
  Point operator - (const Point& p) const { return Point(x-p.x, y-p.y); }
  double sqr_len() const { return *this % *this; }
  double len() const { return sqrt(sqr_len()); }
  Point projection_to(const Point& p) const { 
    return p * (p % *this / (p % p)); 
  }
  Point projection_to_line(const Point& a, const Point& b) const { 
    return a + (*this - a).projection_to(b - a); 
  }
  bool on_segment(const Point& a, const Point& b) const { 
    return eq((a-b).len(), (a-*this).len() + (b-*this).len()); 
  }
  double distance_to_segment(const Point& a, const Point& b) const {
    Point proj = projection_to_line(a,b);
    if( proj.on_segment(a,b) )
      return (*this - proj).len();
    double d1 = (*this - a).len(), 
           d2 = (*this - b).len();
    return min(d1,d2);
  }
};



int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  cout<<setprecision(3)<<fixed;
  Point bomb;
  int n;
  while( cin>>bomb.x>>bomb.y>>n ) {
    vector<Point> p(n);
    forn(i,n) 
      cin>>p[i].x>>p[i].y;
    int sign = 0;
    double smallest_distance = 1000*1000;
    for(int i = 0, j = 1; i < n; i++, j++, j%=n) {
      double sign_area = (p[j] - p[i]) * (bomb - p[i]);
      sign += sign_area > 0 || eq(sign_area, 0);
      double distance = bomb.distance_to_segment(p[i],p[j]);
      DBG(i); DBG(j); DBG(sign_area); DBG(distance);
      smallest_distance = min(smallest_distance, distance);
    }
    DBG(sign); DBG(smallest_distance);
    if( sign == n )
      cout<<"0\n";
    else
      cout<<2 * smallest_distance<<"\n";
    debug<<"============\n";
  }
  
  return 0;
}
