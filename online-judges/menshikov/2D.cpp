#define _USE_MATH_DEFINES
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;

typedef long long int64;
typedef vector<int> vi;
typedef pair<int,int> pii;

#define sz(c) (int((c).size()))
#define all(c) (c).begin(),(c).end()
#define rall(c) (c).rbegin(),(c).rend()
#define spresent(c,v) ( find( all(c) ) != (c).end() )
#define present(c,v) ( (c).find(v) != (c).end() )
#define sqr(x) ((x)*(x))
#define eps 1e-9
#define inf 1000*1000*1000
#define INF 2147483647
#define linf 4LL*1000*1000*1000*1000*1000*1000
#define LINF 9223372036854775807LL

class myVec {
public:
    double x, y;
    myVec(double x, double y) : x(x), y(y) {}
    myVec operator+(myVec a) {
        return myVec(x + a.x, y + a.y);
    }
    myVec operator-(myVec a) {
        return myVec(x-a.x, y-a.y);
    }
    int operator%(myVec a) {
        return x*a.x + y*a.y;
    }
    int operator/(myVec a) {
        return x*a.y - y*a.x;
    }
};
// вещественные числа сравнивать надо так
// equal
bool eq(double a, double b) {
	return fabs(a-b) <= eps;
}
// greater
bool gr(double a, double b) {
	return !eq(a,b) && a > b;
}
// less
bool ls(double a, double b) {
	return !eq(a,b) && a < b;
}
 
// принадлежит ли точка p отрезку (a,b)
bool pointInSegment(myVec &p, myVec &a, myVec &b) {
    return ( eq((b-a)/(p-a), 0.0) && !gr((a-p)%(b-p), 0.0) );
}
// пересекаются ли отрезки (a,b) и (c,d)
bool segmentCross(myVec &a, myVec &b, myVec &c, myVec &d) {
	// идея решения отсюда
	// http://habrahabr.ru/post/148325/
	myVec ab(b-a), cd(d-c);
    double s1 = (c-a)/ab, s2 = (d-a)/ab;
    double s3 = (a-c)/cd, s4 = (b-c)/cd;
   
    if( s1*s2 < 0 && s3*s4 < 0 ) return true;
	else // если отрезки лежат на одной прямой нужна еще проверка
    if( pointInSegment(c,a,b)
    ||  pointInSegment(d,a,b)
    ||  pointInSegment(a,c,d)
    ||  pointInSegment(b,c,d) ) return true;
	else
    return false;
}
 
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
	// кучу раз были проблемы с интами. Когда геометрия, делайте в даблах.
    double x,y;
    cin >> x >> y; myVec a(x,y);
    cin >> x >> y; myVec b(x,y);
    cin >> x >> y; myVec c(x,y);
    cin >> x >> y; myVec d(x,y);   
 
    cout << (( segmentCross(a,b,c,d) ) ? "Yes\n" : "No\n");
   
    return 0;
}