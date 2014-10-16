#! /usr/bin/python3

import binascii
from random import randint
import os

arrayhex = ["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"]

filecounter = 64
arraybytes = []
loop = 0
hs = ""
while loop < filecounter:
	loop2 = 0
	while loop2 < 4:
		hs += arrayhex[randint(0,15)]
		loop2  += 1
	hb = binascii.a2b_hex(hs)
	arraybytes.append(hb)
	loop += 1

loop = 0
while loop < filecounter:
	filename = "test/file" + str(loop) + ".hex"
	if os.path.isfile(filename):
		os.remove(filename)
	fileout = open(filename, "ab")
	fileout.write(arraybytes[loop])
	fileout.close()
	loop += 1