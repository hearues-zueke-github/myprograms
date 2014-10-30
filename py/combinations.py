#! /usr/bin/python3

import sys
import copy

def main():
  if len(sys.argv) < 3 and False:
    print("FALSE")
  # if
  array = createArray(9)
  array2D = createArrayInArray(a, 9)
  printArray(array, 1, 1)
  printArray(array2D, 2, 2)
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
        # else
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