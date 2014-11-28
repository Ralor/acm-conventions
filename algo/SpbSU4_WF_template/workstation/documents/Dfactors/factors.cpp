#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <list>
#include <set>
#include <map>

using namespace std;

#define TASKNAME "factors"
#define pb push_back
#define mp make_pair
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif
#define TIMESTAMP(msg) eprintf("["msg"] Time=%.3lfs\n", clock() * 1.0 / CLOCKS_PER_SEC)
#define sz(x) ((int)(x).size())

typedef long double ld;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

const int inf = 1e9;
const double eps = 1e-9;

ll mul (ll a, ll num, ll den)
{
 // eprintf("%lld %lld %lld\n", a, num, den);
  ll d=__gcd(a,den);
  a/=d, den/=d;
  assert(num%den==0);
  num/=den;
  if (num*1.0*a>10e18 || num*a<0)
    return -1ll;
  return num*a;
}

vi Pr;
ll res, n;
int minsum;
//int Q[40];

void go (ll cur, int pos, int last, ll f, int csum)
{
 // if (last<80)
//    eprintf("%lld %d %d %lld %d\n", cur, pos, last, f, csum);
 // if (last>80)
 //   exit(0);
  if (f==n)
  {
    if (cur<res || res==-1ll)
      res=cur;
    return;
  }
  ll tmp=cur;
  for (int i=1; i<=minsum-csum; i++)
  {
    tmp=mul(tmp,Pr[pos],1);
    if (tmp==-1ll || (res!=-1ll && tmp>res))
      return;
  }
  ll d=__gcd(f,n);
  tmp=f/d;
  for (int i=0; i<(int)Pr.size(); i++)
    if (Pr[i]>last && tmp%Pr[i]==0)
      return;
  for (int i=1; i<=last; i++)
  {
    //eprintf("III   %lld\n", cur);
    f=mul(f,csum+i,i);
    if (f==-1 || f>n)
      return;
    cur=mul(cur,Pr[pos],1);
    if (cur==-1 || (res!=-1ll && cur>res))
      return;
    go(cur,pos+1,i,f,csum+i);
  }
}

ll solve ()
{
//  eprintf("%lld\n", n);
  if (n==1ll)
    return 2ll;
  res=-1ll;
  for (int i=0; i<(int)Pr.size(); i++)
    if (n%Pr[i]==0)
      minsum=Pr[i];
  go(1ll,0,inf,1,0);
  assert(res!=-1ll);
  return res;
}

int main() {
  int i, j;
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif
  for (i=2; i<100; i++)
  {
    bool fl=1;
    for (j=2; j*j<=i; j++)
      if (i%j==0)
        fl=0;
    if (fl)
      Pr.pb(i);
  }
  while (scanf("%lld", &n)==1)
    printf("%lld %lld\n", n, solve());
  
  TIMESTAMP("end");
  return 0;
}

