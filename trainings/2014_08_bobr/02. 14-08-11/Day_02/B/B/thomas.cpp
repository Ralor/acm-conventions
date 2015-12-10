// Solution to Bribe
// Author: Thomas Beuman

// Time complexity: O(n^2 * 2^n)
// Memory: O(n * 2^n)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: depth-first search with memoization


#include <cstdio>
#include <algorithm>
using namespace std;


int B[16];
double P[16];

double Prob[17][1<<16]; // Memoization: [number-left-to-convert][spies-approached(binary)]
// Note that the amount of money left is implicitly set by spies-approached


double prob (int n, int toconvert, int moneyleft, int approached)
{ if (toconvert == 0) // Mission accomplished!
    return 1.0;
  if (Prob[toconvert][approached] >= 0) // Already calculated
    return Prob[toconvert][approached];
  int i;
  double best = 0, p;

  // Try all henchmen
  for (i = 0; i < n; i++)
    if (!(approached & (1<<i)) && B[i] <= moneyleft) // Possible target
    { p = P[i] * prob(n, toconvert-1, moneyleft - B[i], approached | (1<<i)) // success
          + (1-P[i]) * prob(n, toconvert, moneyleft - B[i], approached | (1<<i)); // fail
      best = max(best, p);
    }

  return Prob[toconvert][approached] = best; // Store and return
}


int main()
{ int cases, casenr, n, c, m, i, p, j;
  
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++)
  { 
    // Read input
    scanf("%d %d %d\n", &n, &c, &m);
    for (i = 0; i < n; i++)
    { scanf("%d %d\n", &B[i], &p);
      P[i] = p / 100.0;
    }
    
    // Initialize memoization array to "not calculated yet"
    for (i = 0; i <= n; i++)
      for (j = 0; j < (1<<n); j++)
        Prob[i][j] = -1;
    
    printf("%lf\n", prob(n, c, m, 0));
  }
  return 0;
}

