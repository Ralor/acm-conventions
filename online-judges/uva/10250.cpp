#include <bits/stdc++.h>
using namespace std;

struct Point {
	double x,y;
	Point() { }
	Point(double x, double y) : x(x), y(y) { }
	Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
	Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
	Point operator * (double m) const { return Point(x * m, y * m); }
	Point rotate() const { return Point(-y,x); }
};

int main() {
	cout<<setprecision(10)<<fixed;
	Point a,b;
	while( cin>>a.x>>a.y>>b.x>>b.y ) {
		Point c = a + (b - a) * 0.5;
		a = c + (a - c).rotate();
		b = c + (b - c).rotate();
		cout<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<"\n";
	}
	return 0;
}