#! /usr/bin/env python3
# Author:      Ziko Haris
# Created:     2014.07.09
# Description: Package for Factorial (Mathematics)

'''
#   getArrayChangedElement(array, element, change)
#   getArrayFactorialCombination(length)
'''

def getArrayChangedElement(array, element, change):
    loop = 0
    isthere = False
    while loop < len(array[0]):
        if array[0][loop] == element:
            isthere = True
            break
        loop += 1
    if not isthere:
        return array
    loop = 0
    while loop < len(array):
        loop2 = 0
        while loop2 < len(array[loop]):
            if array[loop][loop2] == element:
                array[loop][loop2] = change
            loop2 += 1
        loop += 1
    return array

def getArrayFactorialCombination(length):
    if length < 1:
        length = 1
    if length == 1:
        return [[0]]
    if length == 2:
        return [[0,1],[1,0]]
    array = [[0,1],[1,0]]
    loop = 2
    while loop < length:

        loop += 1
    return array