#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i,n) for(int i = 0; i < (n); i++)
#define sqr(x) ((x)*(x))

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
inline bool le(double a, double b) {
  return a < b || eq(a,b);
}

struct Point {
  double x,y,z;
  Point() : x(0), y(0), z(0) { }
  Point(double x, double y) : x(x), y(y), z(0) { }
  double dist(const Point& p) const {
    return sqrt(sqr(x-p.x) + sqr(y-p.y) + sqr(z-p.z));
  }
};

double A,B,C;
enum { UP, DOWN, FRONT, REAR, LEFT, RIGHT };
struct Rect {
  int type;
  Point a,b; // left down, right up
  Rect() { }
  Rect(int type, double x, double y, double width, double height) 
    : type(type), a(Point(x,y)), b(Point(x+width,y+height)) { }
  bool contains(const Point& p) const {
    return le(a.x, p.x) && le(p.x, b.x) && le(a.y, p.y) && le(p.y, b.y);
  }
  void do_job(Point& p) const {
    switch( type ) {
    case UP:
      // nothing
      break;
    case DOWN:
      p.z = -C;
      p.y = b.y + C + B - p.y;
      break;
    case FRONT:
      p.z = p.y - b.y;
      p.y = b.y;
      break;
    case REAR:
      p.z = a.y - p.y;
      p.y = a.y;
      break;
    case LEFT:
      p.z = p.x - b.x;
      p.x = b.x;
      break;
    case RIGHT:
      p.z = a.x - p.x;
      p.x = a.x;
      break;
    }
  }
};

int main() {
#ifdef LOCAL_PROJECT
  freopen("input.txt","r",stdin);
#endif
  
  cout<<setprecision(6)<<fixed;
  
  Point a,b;
  while( cin>>A>>B>>C>>a.x>>a.y>>b.x>>b.y ) {
    vector<Rect> fig;
    fig.emplace_back(UP,    C, B + C,     A, B);
    fig.emplace_back(DOWN,  C, 0,         A, B);
    fig.emplace_back(FRONT, C, B,         A, C);
    fig.emplace_back(REAR,  C, B + C + B, A, C);
    fig.emplace_back(LEFT,  0, B + C,     C, B);
    fig.emplace_back(RIGHT, C + A, B + C, C, B);
    bool a_done = false, b_done = false;
    for(Rect& surface : fig) {
      if( !a_done && surface.contains(a) ) {
        a_done = true;
        DBG(a_done); DBG(surface.type);
        surface.do_job(a);
      }
      if( !b_done && surface.contains(b) ) {
        b_done = true;
        DBG(b_done); DBG(surface.type);
        surface.do_job(b);
      }
    }
    DBG(a.x);DBG(a.y);DBG(a.z);
    DBG(b.x);DBG(b.y);DBG(b.z);
    cout<<a.dist(b)<<"\n";
  }
  
  return 0;
}
