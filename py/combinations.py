#! /usr/bin/python3

import sys
import copy

def main():
  if len(sys.argv) < 3 and False:
    print("FALSE")
  # if
  #array = createArrayInArray(0, 9)
  # array2D = createArrayInArray(array, 9)
  # printArray(array, 1, 1)
  # printArray(array2D, 2, 2)
  array_sudoku_number = 3
  array_sudoku = createSudoku2NumberArray(array_sudoku_number)
  print(str(array_sudoku))
  loop = 1
  while loop < array_sudoku_number:
    loop2 = loop + 1
    while loop2 <= array_sudoku_number:
      array_sudoku_temp = replaceArray2Values(array_sudoku, loop, loop2)
      print(str(array_sudoku_temp))
      loop2 += 1
    # while
    loop += 1
  # while
  return 0
# main

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

def createSudoku2NumberArray(number = 1):
  array = []
  loop = 1
  while loop < number + 1:
    loop2 = loop
    while loop2 < number + 1:
      if loop2 == loop:
        array.append(loop)
      # if
      else:
        array.append(loop)
        array.append(loop2)
      # else
      loop2 += 1
    # while
    loop += 1
  # while
  return array
# createSudoku2NumberArray

def replaceArray2Values(array, num1, num2):
  loop = 0
  while loop < len(array):
    if array[loop] == num1:
      array[loop] = num2
    # if
    elif array[loop] == num2:
      array[loop] = num1
    # elif
    loop += 1
  # while
  return array
# replaceArray2Values

if __name__ == "__main__":
  main()
# if