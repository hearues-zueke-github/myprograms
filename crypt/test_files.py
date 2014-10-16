#! /usr/bin/python3

import os
import subprocess

#subprocess.call("./crypt2withoutprintf");

filecounter = 64

if os.path.isdir("test2") == False:
	os.makedirs("test2")
if os.path.isdir("test3") == False:
	os.makedirs("test3")

loop = 0
while loop < filecounter:
	file1 = "test/file"+str(loop)+".hex"
	file2 = "test2/file"+str(loop)+".txt"
	file3 = "test3/file"+str(loop)+".txt"

	subprocess.call(["./crypt2withoutprintf","filetext.txt",file1,"e",file2])
	subprocess.call(["./crypt2withoutprintf",file2,file1,"d",file3])
	loop += 1

fileplain = open("filetext.txt","rb")
ba = bytearray(fileplain.read())
fileplain.close()

loop = 0
while loop < filecounter:
	file3 = "test3/file"+str(loop)+".txt"
	fileopen = open(file3, "rb")
	ba2 = bytearray(fileopen.read())
	fileopen.close()
	if ba != ba2:
		print("Fail on File "+str(loop))
	loop += 1