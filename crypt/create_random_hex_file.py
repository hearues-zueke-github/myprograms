#! /usr/bin/python3

import binascii
from random import randint
import os

arrayhex = ["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"]

file_length = 1023 * 2
loop = 0
hs = ""
while loop < file_length:
	hs += arrayhex[randint(0,15)]
	loop  += 1
hb = binascii.a2b_hex(hs)
filename = "random_hex.hex"
if os.path.isfile(filename):
	os.remove(filename)
fileout = open(filename, "ab")
fileout.write(hb)
fileout.close()