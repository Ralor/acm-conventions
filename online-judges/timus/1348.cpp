#include <bits/stdc++.h>
using namespace std;

#define eps 1e-8

inline bool eq(double a, double b) {
	return fabs(a-b) <= eps;	
}

struct Point {
	double x,y;
	Point() { }
	Point(double x, double y) : x(x), y(y) { }
	double len_sq() const {	return x*x + y*y;}
	double len() const { return sqrt(len_sq());}
	Point operator + (const Point& p) const { return Point(x+p.x, y+p.y); }
	Point operator - (const Point& p) const { return Point(x-p.x, y-p.y); }
	Point operator * (const double& m) const { return Point(x*m, y*m); }
	double operator % (const Point& p) const { return x*p.x + y*p.y; }
	double operator * (const Point& p) const { return x*p.y - y*p.x; }
	Point line_projection(const Point& a, const Point& b) const {
		Point ab = b - a, ac = *this - a;
		return a + Point(ab * ((ab % ac) / (ab % ab)));
	}
	bool on_segment(const Point& a, const Point& b) const {
		return eq((a-b).len(), (a - *this).len() + (b - *this).len());
	}
	double dist_to_segment(const Point& a, const Point& b) const {
		Point lp = line_projection(a,b);
		if( lp.on_segment(a,b))
			return (lp - *this).len();
		return sqrt(min((a - *this).len_sq(), (b - *this).len_sq()));
	}
};



int main() {
	cout<<setprecision(2)<<fixed;
	
	Point a,b,c;
	double L;
	while( cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y>>L ) {
		cout<<max(0.0, c.dist_to_segment(a,b) - L)<<"\n";
		cout<<max(0.0, sqrt(max((a-c).len_sq(), (b-c).len_sq())) - L)<<"\n";
	}
	
	return 0;
}