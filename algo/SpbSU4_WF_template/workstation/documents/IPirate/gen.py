#!/usr/bin/python
from random import *
h=500
w=500
a=randint(1, 500)
b=randint(1, 500)
print("%d %d %d %d" % (a, b, h, w))
for _ in range(w * h):
  print(randint(0, int(1e9)))
  
