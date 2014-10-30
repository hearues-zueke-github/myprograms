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
    print("Length is OK!")
    isok = True
    loop = 0
    while loop < len(content1):
      if content1[loop] != content2[loop]:
        isok = False
        print("At position " + str(hex(int(loop/2))) + ": 1st file=" +str(content1)[loop + 2] + " 2nd file=" + str(content2)[loop + 2])
      loop += 1
    if isok == True:
      print("Files are really, I mean REALLY ident!!")
    else:
      print("Files are not OK!!!!!")