# Флаги.
n = int(input())
a = b = 2
for i in range(n - 2):
    a, b = b, a + b
print(b)
