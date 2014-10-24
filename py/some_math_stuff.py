#! /usr/bin/python3

from random import randint

y=5
x=y+1

matrix = []
loop = 0
while loop < y:
  array = []
  loop2 = 0
  while loop2 < x:
    array.append(0)
    loop2 += 1
  matrix.append(array)
  loop += 1

loop = 0
while loop < y:
  print(str(matrix[loop]))
  loop += 1


loop = 0
while loop < y:
  loop2 = 0
  while loop2 < x:
    matrix[loop][loop2] = float(randint(1,10))
    loop2 += 1
  loop += 1

