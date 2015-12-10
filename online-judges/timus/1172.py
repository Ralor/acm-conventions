# Ship routes.
dp = [[[[-1] * 3 for c in range(31)] for b in range(31)] for a in range(31)]

def dyn(a, b, c, pos):
    if a == b == c == 0:
        return pos != 0
    if dp[a][b][c][pos] != -1:
        return dp[a][b][c][pos]
    result = 0
    if pos != 0 and a != 0:
        result += dyn(a - 1, b, c, 0) * a
    if pos != 1 and b != 0:
        result += dyn(a, b - 1, c, 1) * b
    if pos != 2 and c != 0:
        result += dyn(a, b, c - 1, 2) * c
    dp[a][b][c][pos] = result
    return result

n = int(input())
print(dyn(n - 1, n, n, 0) >> 1)
