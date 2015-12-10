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
    double operator/(myVec a) {
        return x*a.y - y*a.x;
    }
    bool isZero() {
        return fabs(x) <= eps && fabs(y) <= eps;
    }
};
 
int sign(double x) {
    return (fabs(x) < eps) ? 0 :
           (x < 0.0) ? -1 : 1;
}
 
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);      
 
    ios::sync_with_stdio(0);
    cin.tie(0);
    double x,y;
    cin >> x >> y; myVec a(x,y);
    cin >> x >> y; myVec b(x,y);
    cin >> x >> y; myVec c(x,y);
    cin >> x >> y; myVec p(x,y);   
 
	// Опять таки, то самое решение где было непонятное векторное произведение,
	// тут оно сделано оператором / для удобства.
	// Считаем его для каждой стороны и точки p, смотрим сколько получилось
	// с одинаковым знаком. Потом проверяем на равенство с точками a,b,c
    if( abs( sign( (b-a)/(p-a) )
           + sign( (c-b)/(p-b) )
           + sign( (a-c)/(p-c) ) ) >= 2 ) cout << "In\n";
    else
    if( (p-a).isZero() || (p-b).isZero() || (p-c).isZero() )
        cout << "In\n";
    else
        cout << "Out\n";
 
    return 0;
}