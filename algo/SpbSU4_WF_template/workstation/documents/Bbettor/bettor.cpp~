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

#define TASKNAME "bettor"
#define pb push_back
#define mp make_pair
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif
#define TIMESTAMP(msg) eprintf("["msg"] Time=%.3lfs\n", clock() * 1.0 / CLOCKS_PER_SEC)
#define sz(x) ((int)(x).size())

typedef double ld;
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

const int MAXN = 1000000;

ld Mul[2*MAXN], Div[2*MAXN];
int em, ed;

ld calc (int n, int k, ld p)
{
  em=0, ed=0;
  for (int i=0; i<k; i++)
    Mul[em++]=n-i, Div[ed++]=i+1;
  for (int i=0; i<k; i++)
    Div[ed++]=1.0/p;
  for (int i=0; i<n-k; i++)
    Div[ed++]=1.0/(1.0-p);
  ld res=1.0;
  while (em>0 || ed>0)
  {
    if ((res>1.0 || em==0) && ed!=0)
      ed--, res/=Div[ed];
    else
      em--, res*=Mul[em];
  }
  
/*  ld tmp = 1;
  for (int i = 0; i < k; i++) {
    tmp *= n - i, tmp /= i + 1;
    tmp *= p;
  }
  for (int i = k; i < n; i++)
    tmp *= 1 - p;
  if (n <= 100)
  eprintf("%.6lf %.6lf; %.6lf\n", tmp, res, fabs(tmp - res));*/
  return res;
}

ld x, p;

inline ld get (ld tmp)
{
  return (tmp<0.0)?(tmp*(1.0-x)):(tmp);
}

ld solve (int n)
{
  int mid=(int)(n*p);
  ld coef=calc(n,mid,p);
  ld ret=coef*get(2*mid-n);
  ld coef0 = coef;
/*  for (int i = 0; i <= n; i++) if (i != mid) {
    ret += calc(n, i, p) * get(2 * i - n);
  }
  return ret;*/
  for (int i=mid+1; i<=n; i++)
  {
    if (coef<1e-20)
      break;
    coef*=p, coef/=1.0-p;
    coef*=n-i+1, coef/=i;
    ret+=coef*get(2*i-n);
  }
  coef = coef0;
  for (int i=mid-1; i>=0; i--)
  {
    if (coef<1e-20)
      break;
    coef/=p, coef*=1.0-p;
    coef/=n-i, coef*=i+1;
    ret+=coef*get(2*i-n);
  }
//  eprintf("%d   %.8lf\n", n, ret);
  return ret;
}

int main() {
  ld res=0.0;
  int i;
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif
  scanf("%lf %lf", &x, &p), x/=100.0, p/=100.0;
  if (p<eps)
  {
    printf("%.9lf\n", 0.0);
    return 0;
  }
  
  //eprintf("%.5lf\n", calc(4,2,0.9));
  int l=0, r=MAXN;
  while (r-l>2)
  {
    int m1=(2*l+r)/3;
    int m2=(l+2*r)/3;
    ld f1=solve(m1);
    ld f2=solve(m2);
    (f1<f2)?(l=m1):(r=m2);
  }
//  eprintf("lr=%d %d\n", l, r);
//  eprintf("%.5lf\n", solve(3000));
  for (i=max(l,1); i<=r; i++)
    res=max(res,solve(i));
/*  for (C[0][0]=1.0, i=1; i<MAXN; i++)
    for (C[i][0]=C[i-1][0]*(1.0-p), j=1; j<=i; j++)
      C[i][j]=C[i-1][j]*(1.0-p)+C[i-1][j-1]*p;
  for (n=1; n<MAXN; n++)
  {
    cres=0.0;
    for (i=0; i<=n; i++)
    {
      tmp=i*2.0-n;
      if (tmp<0.0)
        tmp*=1.0-x;
      cres+=C[n][i]*tmp;
    }
    res=max(res,cres);
    eprintf("%d %.8lf\n", n, cres);
  }*/
  printf("%.9lf\n", res);
  TIMESTAMP("end");
  return 0;
}

