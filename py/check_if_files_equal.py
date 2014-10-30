#! /usr/bin/python3
import sys
import os
import binascii

if (len(sys.argv) != 3):
  print("Wrong Parameters!\n Use: ./<program> <file1> <fil2>")

if (os.path.isfile(sys.argv[1]) == False):
  print("1st file not exist!")
elif (os.path.isfile(sys.argv[2]) == False):
  print("2nd file not exist!")
else:
  file1 = open(sys.argv[1], "rb")
  content1 = binascii.hexlify(file1.read())
  file1.close()
  print("File1 readed in!")
  #print(str(content1))
  file2 = open(sys.argv[2], "rb")
  content2 = binascii.hexlify(file2.read())
  file2.close()
  #print(str(content2))
  print("File2 readed in!")
  if len(content1) != len(content2):
    print("Length is not OK! Therefore NOT equal!!!")
  else:
    loop = 0
    while loop < len(content1):
      if content1[loop] != content2[loop]:
        print("At position " + str(loop) + ": 1st file=" +str(content1[loop]) + " 2nd file=" + content2[loop])
      loop += 1