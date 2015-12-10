#include <bits/stdc++.h>
using namespace std;

// bullshit
const double pi = atan(1)*4;
const double pi_2 = pi / 2;


enum { CIRCLE = 1, SQUARE = 2, TRIANGLE = 3 };
struct Shape {
	double in_, out_;
	Shape() { }
	Shape(int type, int size) { init(type,size); }
	void init(int type, int size) {
		switch( type ) {
		case CIRCLE : in_ = out_ = 2 * size; 
			break;
		case SQUARE : in_ = sqrt(2 * size * size); out_ = size;
			break;
		case TRIANGLE : in_ = size; out_ = size * cos(pi_2 / 3);
		}	
	}
	bool bigger_than(const Shape& s) const {
		return in_ >= s.out_;
	}
};


int main() {
	
	int type, shape_size;
	while( cin>>type>>shape_size ) {
		Shape base(type, shape_size);
		int n; cin>>n;
		int result = 0;
		while(n--) {
			cin>>type>>shape_size;
			Shape shape(type, shape_size);
			if( base.bigger_than(shape) )
				++result;
		}
		cout<<result<<"\n";
	}
 
	return 0;
}