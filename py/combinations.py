#! /usr/bin/python3

import sys
import copy

def main():
  if len(sys.argv) < 3 and False:
    print("FALSE")
  # if
  a = createArray(4)
  a2 = createArrayInArray(a, 6)
  a3 = createArrayInArray(a2, 5)
  a4 = createArrayInArray(a3, 3)
  printArray(a, 1, 1)
  printArray(a2, 2, 2)
  printArray(a3, 3, 2)
  printArray(a4, 3, 2)
  return 0
# main

def hallo():
  print("Hello World!")
# hallo

def createArray(length):
  loop = 0
  a = []
  for loop in range(length):
    a.append(0)
  # for
  return a
# createArray

def createArrayInArray(array, length):
  loop = 0
  a = []
  for loop in range(length):
    a.append(copy.deepcopy(array))
  # for
  return a
# createArrayInArray

def checkArrayDimension(array):
  is_array = True
  dimension = 0
  while is_array:
    if type(array) == type([]):
      array = array[0]
      dimension += 1
    # if
    else:
      is_array = False
    # else
  # while
  return dimension
# checkArrayDimension

def printArray(array, dimension = 1, maxdimension = 1):
  loop = 0
  if type(array) == type([]):
    if array != []:
      for loop in range(len(array)):
        if dimension == 1:
          print(str(array))
          break
        # if
        else:
          printArray(array[loop], dimension - 1, maxdimension)
        #else
      # for
      if dimension == maxdimension:
        print("")
      # if
    # if
  # if
# print Array

if __name__ == "__main__":
  main()
# if