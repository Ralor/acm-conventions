#include <bits/stdc++.h>
using namespace std;

const double pi = atan(1) * 4;
const double pi_2 = pi / 2;

#define forn(i,n) for(int i = 0; i < (n); i++)
#define eps 1e-8

inline bool eq(double a, double b) {
	return fabs(a-b) <= eps;
}	

struct Point {
	double x,y;
	Point() { }
	Point(double x, double y) : x(x), y(y) { }
	Point operator - (const Point& p) { return Point(x - p.x, y - p.y); }
	Point operator = (const Point& p) { x=p.x; y = p.y; return *this; }
	bool operator != (const Point& p) { return !eq(x,p.x) || !eq(y,p.y); }
	double operator * (const Point& p) const { return x*p.y - y*p.x; }
	double operator % (const Point& p) const { return x*p.x + y*p.y; }
	double angle_to(const Point& p) const { return atan2(*this * p, *this % p); }
	double angle_to_2(const Point& p) const { double t=angle_to(p); return t > -eps ? t : 2*pi+t; }
	double len() const { return sqrt(*this % *this); }
};

int main() {
	
	int n;
	double L;
	while( cin>>n>>L ) {
		vector<Point> a(n);
		forn(i,n) {
			cin>>a[i].x>>a[i].y;
			a[i].x += 1e5;
			a[i].y += 1e5;
		}
		Point prev_dir(1,0), prev_point(0,0);
		vector<int> used(n);
		vector<Point> ch;
		forn(i,n) {
			int mn_id = -1;
			double mn_angle = 111 * pi, mn_dist = 1000*1000*1000;
			forn(j,n) 
				if( a[j] != prev_point ) {
					//cout<<"Checking ("<<a[j].x-1e5<<" "<<a[j].y-1e5<<")\n";
					double angle = prev_dir.angle_to_2(a[j] - prev_point);
					double dist = (a[j] - prev_point).len();
					//cout<<"Angle = "<<angle<<"; Dist = "<<dist<<";\n";
					if( mn_angle > angle || eq(mn_angle, angle) && dist < mn_dist) {
						mn_angle = angle;
						mn_dist = dist;
						mn_id = j;
						//cout<<"Update!\n";
					}
				}
			//cout<<"Found : "<<a[mn_id].x-1e5<<" "<<a[mn_id].y-1e5<<"\n";
			if( used[mn_id] ) 
				break;
			used[mn_id] = 1;
			ch.push_back(a[mn_id]);
			prev_dir = a[mn_id] - prev_point;
			prev_point = a[mn_id];
		}
		double length = 0;
		for(unsigned i=0,j=1,k=2; i < ch.size(); i++, j++, k++, j %= ch.size(), k%=ch.size()) {
			Point first = ch[j] - ch[i], second = ch[k] - ch[j];
			length += first.len();
			length += L * first.angle_to_2(second); // 2 * Pi * L in sum
		}
		cout<<int(length + 0.5)<<"\n";
	}
	
	return 0;
}