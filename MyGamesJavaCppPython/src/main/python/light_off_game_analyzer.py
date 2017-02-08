#! /usr/bin/python3

import numpy as np
import pickle as pkl
import scipy as sp

import matplotlib.pyplot as plt

y, x = 5, 5

field = np.zeros((y+2, x+2)).astype(np.int8)

# print("field:\n{}".format(field))

# field[((0, 0), (0, 0))] += 1

# print("field:\n{}".format(field))

# field[np.random.randint(0, x+2, (2, 120)).tolist()] = np.random.randint(0, 100, (120, ))
# print("field:\n{}".format(field))

print("field%5:\n{}".format(field%5))
print("(field%5)-6:\n{}".format((field%5)-6))
print("((field%5)-6)%5:\n{}".format(((field%5)-5)%5))

# Define all possible moves
poss_moves = np.zeros((y, x, y+2, x+2)).astype(np.int8)

for j in range(1, y+1):
    for i in range(1, x+1):
        poss_moves[j-1, i-1][((j, j+1, j-1, j, j), (i, i, i, i+1, i-1))] = (1, 1, 1, 1, 1)

for i, poss_move in enumerate(poss_moves):
    print("nr. {}, poss_move:\n{}".format(i, poss_move))