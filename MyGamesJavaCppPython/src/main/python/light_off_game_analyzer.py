#! /usr/bin/python3

import numpy as np
import pickle as pkl
import scipy as sp

import matplotlib.pyplot as plt

from PIL import Image

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

def increase_pix(pix, rate=2):
    y, x, _ = pix.shape
    new_pix = np.zeros((y*rate, x*rate, 3)).astype(np.uint8)

    for j in range(0, y):
        for i in range(0, x):
            new_pix[j*rate:(j+1)*rate, i*rate:(i+1)*rate] = pix[j, i]

    return new_pix

moves_amount = 10
moves = [(np.random.randint(0, y), np.random.randint(0, x)) for _ in range(0, moves_amount)]

def do_moves(field, moves, poss_moves):
    for move in moves:
        j, i = move
        field = (field+poss_moves[j, i]) % 2

    return field

field = do_moves(field, moves, poss_moves)

# moves = [(2, 2), (3, 4), (2, 1), (0, 1), (3, 0)]
# for move in moves:
#     j, i = move
#     field = (field+poss_moves[j, i]) % 2
# field = (field+poss_moves[1, 2]) % 2
# field = (field+poss_moves[2, 2]) % 2

print("field:\n{}".format(field))

pix = np.zeros((y+2, x+2, 3)).astype(np.uint8)
pix[:, :, 0] = field
pix[:, :, 1] = field
pix *= 255

pix_larger = increase_pix(pix, 50)

img = Image.fromarray(pix_larger)
img.show()

pix_new = np.zeros((y, x, 3)).astype(np.int8)
pix_new[:, :, 0] = pix[1: -1, 1: -1, 0]
pix_new[:, :, 1] = pix[1: -1, 1: -1, 1]
pix_new[:, :, 2] = pix[1: -1, 1: -1, 2]
# print("pix_new:\n{}".format(pix_new))
pix_larger = increase_pix(pix_new, 50)
img = Image.fromarray(pix_larger)
img.show()

def solve_up_down(field, y, x, poss_moves):
    for j in range(2, y):
        for i in range(2, x):
            
