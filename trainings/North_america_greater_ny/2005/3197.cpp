// Problem : WTF?
// tAgs :

#include <algorithm>
#include <cstdio>
#include <deque>
#include <queue>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>

#define pb push_back
#define mp make_pair
#define sqr(a) ((a)*(a))
#define sz(x) ((int)(x.size()))
#define forn(i,n) for(int i = 0; i < (n); ++i)
#define update(buf,val) buf = max((buf),val) 

using namespace std;
stringstream fakestream;

typedef long long llong;
typedef unsigned long long ullong;
typedef vector < int > vi;
typedef vector < double > vd;

typedef vector < vi > vvi;
typedef pair <int,int> pi;

struct point
{
    double x;
    double y;
};

typedef vector < point > vp;

void get_row(const vp& data, vp& res )
{
    res.clear();
    for(int i = 1; i < sz(data); ++i)
    {
        point a = data[ i - 1];
        point b = data[ i ];
        point del;
        point med;
        med.x = (a.x + b.x)/ 2;
        med.y = (a.y + b.y)/ 2;
        
        
        del.x = b.x - a.x;
        del.y = b.y - a.y;
        double len = sqrt(sqr( del.x ) + sqr(del.y));
        double nlen = sqrt( 4 - sqr(len) / 4);
        //cout << "len "<< len << " "<< nlen << endl;
        
        del.x /= len;
        del.y /= len;
        point np;
        np.x = -1 * nlen * del.y + med.x;
        np.y = nlen * del.x + med.y;
        if(np.x < 0)
        {
            np.x *= -1;
            np.y *= -1;
        }
        res.pb( np);
        //cout << "pos "<< np.x << " "<< np.y << endl;
       
    }
}
bool comp(point a, point b)
{
    return a.x < b.x;
    
}
int main(){
    #ifdef LOCAL_PROJECT
        freopen("input","r",stdin);
    #endif
    //freopen("output.txt","w",stdout);
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
        cout << setprecision(4) << fixed;
        int n;
        
        while(cin >> n &&  n != 0)
        {
            vp source( n );
            vp buf;
            vp *from;
            vp *to;
            for(int i = 0 ; i < n; ++i)
            {
                cin >> source[ i ].x;
                source[ i ].y = 1;
        
            }
            sort(source.begin(), source.end(), comp);
        
            for(int i =0; i < n - 1; ++i)
            {
                if(i % 2 == 0)
                    get_row( source, buf);
                else
                    get_row( buf, source);
        
            }
            if( (n - 1) % 2 ==0 )
            {    
                for(int i =0; i < sz(source); ++i)
                    cout << source[ i ].x << " " << source[ i ].y << "\n";
            }
    
            else
            {
                for(int i =0; i < sz(buf); ++i)
                    cout << buf[ i ].x << " " << buf[ i ].y << "\n";
        
            }
        }
    
    return 0;
}