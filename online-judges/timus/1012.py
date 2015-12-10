# K-ичные числа. Версия 2.
dp = [[-1, -1] for pos in range(1800)]
n = k = 0

# def dyn(pos, zero):
    # # label0:
    # if pos >= n:
        # return 1
    # if dp[pos][zero] != -1:
        # return dp[pos][zero]
    # result = (k - 1) * dyn(pos + 1, False);
    # # label1:
    # if not zero:
        # # label2:
        # result += dyn(pos + 1, True)
    # # label3:
    # dp[pos][zero] = result
    # return result

def dyn(*args):
    stack = [[0, True, 0, 0]]
    while stack:
        pos, zero, label, result = stack[-1]
        if label == 0:
            if pos >= n:
                dp[pos][zero] = 1
            if dp[pos][zero] != -1:
                stack.pop()
                continue
            stack[-1][2] = 1
            stack.append([pos + 1, False, 0, 0])
            continue
        if label == 1:
            stack[-1][3] = (k - 1) * dp[pos + 1][False]
            if zero:
                label = 3
            else:
                stack[-1][2] = 2
                stack.append([pos + 1, True, 0, 0])
                continue
        if label == 2:
            stack[-1][3] += dp[pos + 1][True]
            label = 3
        if label == 3:
            dp[pos][zero] = stack[-1][3]
            stack.pop()
    return dp[0][True]

n = int(input())
k = int(input())
print(dyn(0, True))
