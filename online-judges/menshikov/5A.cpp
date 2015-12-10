#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <climits>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <ctime>
#include <cmath>
using namespace std;

typedef long long llong;
typedef unsigned long long ullong;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define spresent(c,v) ( find( all(c), v ) != (c).end() )
#define present(c,v) ( (c).find(v) != (c).end() )
#define sqr(x) ((x)*(x))
#define mp(x,y) make_pair((x),(y))
#define eps 1e-8
#define inf 1000*1000*1000
#define linf 4LL*1000*1000*1000*1000*1000*1000
#define eq(x,y) (fabs(double(x) - double(y)) <= eps)
#define ls(x,y) (double(x) < double(y) && !eq(x,y))
#define gr(x,y) (double(x) > double(y) && !eq(x,y))
#define dbg(x) cout << #x << " : " << x << "\n"

int arr[87][2] = {
{ 1, 0},
{ 6, 6},
{ 28, 28},
{ 220, 284},
{ 284, 220},
{ 496, 496},
{ 1184, 1210},
{ 1210, 1184},
{ 2620, 2924},
{ 2924, 2620},
{ 5020, 5564},
{ 5564, 5020},
{ 6232, 6368},
{ 6368, 6232},
{ 8128, 8128},
{ 10744, 10856},
{ 10856, 10744},
{ 12285, 14595},
{ 14595, 12285},
{ 17296, 18416},
{ 18416, 17296},
{ 63020, 76084},
{ 66928, 66992},
{ 66992, 66928},
{ 67095, 71145},
{ 69615, 87633},
{ 71145, 67095},
{ 76084, 63020},
{ 79750, 88730},
{ 87633, 69615},
{ 88730, 79750},
{ 100485, 124155},
{ 122265, 139815},
{ 122368, 123152},
{ 123152, 122368},
{ 124155, 100485},
{ 139815, 122265},
{ 141664, 153176},
{ 142310, 168730},
{ 153176, 141664},
{ 168730, 142310},
{ 171856, 176336},
{ 176272, 180848},
{ 176336, 171856},
{ 180848, 176272},
{ 185368, 203432},
{ 196724, 202444},
{ 202444, 196724},
{ 203432, 185368},
{ 280540, 365084},
{ 308620, 389924},
{ 319550, 430402},
{ 356408, 399592},
{ 365084, 280540},
{ 389924, 308620},
{ 399592, 356408},
{ 430402, 319550},
{ 437456, 455344},
{ 455344, 437456},
{ 469028, 486178},
{ 486178, 469028},
{ 503056, 514736},
{ 514736, 503056},
{ 522405, 525915},
{ 525915, 522405},
{ 600392, 669688},
{ 609928, 686072},
{ 624184, 691256},
{ 635624, 712216},
{ 643336, 652664},
{ 652664, 643336},
{ 667964, 783556},
{ 669688, 600392},
{ 686072, 609928},
{ 691256, 624184},
{ 712216, 635624},
{ 726104, 796696},
{ 783556, 667964},
{ 796696, 726104},
{ 802725, 863835},
{ 863835, 802725},
{ 879712, 901424},
{ 898216, 980984},
{ 901424, 879712},
{ 947835, 1125765},
{ 980984, 898216},
{ 998104, 1043096}
};

int inSeg(int left, int right, int value) {
    return left <= value && value <= right;
}

int used[1000*1000 + 100*1000];

int main() {
    //freopen(TASK ".in", "r", stdin);
    //freopen(TASK ".out", "w", stdout);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    //freopen("info.txt","r",stdin);
    //freopen("info.txt","w",stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m,n;
    while( cin >> m >> n ) {
        int ok = 0;
        memset(used, 0, sizeof used);
        for(int i = 0; i < 87; i++)
            if( inSeg(m,n,arr[i][0]) && inSeg(m,n,arr[i][1]) && !used[arr[i][0]] && !used[arr[i][1]] && arr[i][0] != arr[i][1] ) {
                cout << min(arr[i][0], arr[i][1]) << " " << max(arr[i][0], arr[i][1]) << "\n", ok = 1;
                used[arr[i][0]] = used[arr[i][1]] = 1;
            }
        if( !ok )
            cout << "Absent" << "\n";
    }
    return 0;
}
