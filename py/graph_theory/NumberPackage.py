#! /usr/bin/env python3
# Author:      Ziko Haris
# Created:     2014.07.09
# Description: Package for Numbertheory

import math
import copy

'''
#   getArrayPrimes(number)
#   getFactorialCombinations(number)
#   calcExponentRecursion(exponent, recursion, maxnum)
'''

def getArrayPrimes(number):
    array = [2,3,5]
    if number == 2:
        return array[0:1]
    elif number == 3:
        return array[0:2]
    elif number == 5:
        return array[0:3]
    loop = 7
    while loop <= number:
        loop2 = 0
        limit = int(math.sqrt(loop)) + 1
        isprime = True
        while array[loop2] < limit:
            if loop % array[loop2] == 0:
                isprime = False
                break
            loop2 += 1
        if isprime:
            array.append(loop)
        loop += 2
        if loop % 5 == 0:
            loop += 2
    return array

def changeArrayNumber(array, prev, next):
    array2 = []
    loop = 0
    for x in array:
        array2.append([])
        loop2 = 0
        for y in x:
            if y == prev:
                array2[loop].append(next)
            else:
                array2[loop].append(array[loop][loop2])
            loop2 += 1
        loop += 1
    return array2

def getFactorialCombinations(number):
    array = [[0,1],[1,0]]
    if number < 1:
        number = 1
    if number == 1:
        array = [[0]]
    elif number == 2:
        array = [[0,1],[1,0]]
    #print(changeArrayNumber(array,1,3))
    loop = 2
    while loop < number:
        arraytemp = []
        loop2 = 0
        while loop2 < len(array):
            arraytemp2 = [loop]
            loop3 = 0
            while loop3 < loop:
                arraytemp2.append(array[loop2][loop3])
                loop3 += 1
            arraytemp.append(copy.deepcopy(arraytemp2))
            loop2 += 1
        array = copy.deepcopy(arraytemp)
        loop2 = 0
        while loop2 < loop:
            arraytemp3 = changeArrayNumber(array, loop2, loop)
            arraytemp = []
            loop3 = 0
            while loop3 < len(array):
                arraytemp2 = [loop2]
                loop4 = 0
                while loop4 < loop:
                    arraytemp2.append(arraytemp3[loop3][loop4])
                    loop4 += 1
                arraytemp.append(copy.deepcopy(arraytemp2))
                loop3 += 1
            loop2 += 1
            looparray = 0
            while looparray < len(arraytemp):
                array.append(copy.deepcopy(arraytemp[looparray]))
                looparray += 1
        loop += 1
    return array

def calcExponentRecursion(exponent, recursion, maxnum):
    loop = 0
    number = exponent
    while loop < recursion and number <= maxnum:
        print(str(loop) + " : " + str(math.log(number)/math.log(10)))
        number = number * number
        loop += 1