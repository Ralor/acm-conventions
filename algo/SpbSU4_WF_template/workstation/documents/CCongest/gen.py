#!/usr/bin/python
from random import *
n=25000
m=50000
c=1000
print("%d %d %d" % (n, m, c))
for _ in range(m):
  print(randint(1, n))
  print(randint(1, n))
  print(randint(0, 10000))
for _ in range(c):
  print(randint(1, n))
  

