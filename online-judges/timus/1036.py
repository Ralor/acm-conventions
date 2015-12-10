# Счастливые билеты.
n = 0
dp = [[-1] * 501 for i in range(50)]

def dyn(pos, s):
    if pos >= n:
        return not s
    if s < 0:
        return 0
    if dp[pos][s] != -1:
        return dp[pos][s]
    result = 0
    for i in range(10):
        result += dyn(pos + 1, s - i)
    dp[pos][s] = result
    return result

n, s = map(int, input().split())
if s & 0b1:
    print(0)
else:
    print(dyn(0, s >> 1) ** 2)
