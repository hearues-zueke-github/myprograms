#! /usr/bin/env python3
# Author:      Ziko Haris
# Created:     2014.07.09
# Description: Package for Graphtheory

import copy

'''
#   checkIfArrayIsGraph(array)
#   checkIfArrayAreCoordinate(array)
#   getDictionaryFromArray(array)
#   getArrayHamiltonPointPosition(array, point)
#   getArrayStringCombination(digits, length)
#   getArrayStringCombinationGraph(array)
#   getArrayAllVertexConnected(length)
#   searchHamiltonPath(array)
#   searchShortestPath(array)
#   printGraphArraySolution(array)
#   printArrayStringCombinationSolution(arraystring, arraysolution)
'''

def checkIfArrayIsGraph(array):
    startpointexist = False
    # Checks, if Graph is not a Tree!!
    for x in array:
        if len(x) > 0:
            for y in x:
                if y == x[0]:
                    if len(y) != 1:
                        return False
                elif y == x[1]:
                    if len(y) == 0:
                        return False
    # Checks, if every Point is not defined twice!
    for x in array:
        for y in array:
            if x != y:
                if x[0][0] == y[0][0]:
                    return False
    # Checks, if a Point is not defined with itself!
    for x in array:
        for y in x[1]:
            if y == x[0][0]:
                return False
    # Checks, if every vertex comes 1 time
    vertexesfrom = []
    '''for x in array:
        for y in x[1]:
            for z in vertexesfrom:
                if z == y:
                    return False
            vertexesfrom.append(y)'''
    return True

def checkIfArrayAreCoordinate(array, dimension):
    if dimension < 1:
        dimension = 1
    for x in array:
        if type(x) == type([]):
            if len(x) < dimension:
                return False
        else:
            return False
    return True

def getDictionaryFromArray(array):
    dictarray = {}
    i = 0
    for x in array:
        dictarray.update({x[0][0]:i})
        i += 1
    return dictarray

def getArrayHamiltonPointPosition(array, point):
    loop = 0
    length = len(array)
    while loop < length:
        if point == array[loop][0][0]:
            return loop
        loop += 1
    return -1

def getArrayStringCombination(digits, length):
    array = []
    arraytemp = []
    loop = 0
    while loop < length:
        arraytemp.append(0)
        loop += 1
    isfinished = False
    while not isfinished:
        array.append(copy.deepcopy(arraytemp))
        loop = 0
        while True:
            arraytemp[loop] += 1
            if arraytemp[loop] < digits:
                break
            else:
                arraytemp[loop] = 0
                loop += 1
                if loop >= length:
                    isfinished = True
                    break
    return array

def getArrayStringCombinationGraph(array):
    arraygraph = []
    loopx = 0
    for x in array:
        loopy = 0
        arraytemp = [[loopx],[]]
        for y in array:
            if x != y:
                if len(x) > 1:
                    ischainable = True
                    loop = 0
                    while loop < len(x) - 1:
                        if x[loop] != y[loop + 1]:
                            ischainable = False
                            break
                        loop += 1
                    if ischainable:
                        arraytemp[1].append(loopy)
                else:
                    arraytemp[1].append(loopy)
            loopy += 1
        arraygraph.append(copy.deepcopy(arraytemp))
        loopx += 1
    return arraygraph

def getArrayAllVertexConnected(length):
    if length < 1:
        length = 1
    array = []
    loop = 0
    while loop < length:
        arraytemp = [[loop],[]]
        loop2 = 0
        while loop2 < loop:
            arraytemp[1].append(loop2)
            loop2 += 1
        loop2 = loop + 1
        while loop2 < length:
            arraytemp[1].append(loop2)
            loop2 += 1
        loop += 1
        array.append(copy.deepcopy(arraytemp))
    return array

def searchHamiltonPath(array):
    arrayhamilton = []
    if not checkIfArrayIsGraph(array):
        return ["Not a correct Array for Graph"]
    arrayrecursion = []
    for x in array:
        arrayrecursion.append([0, -1])
    dictarray = getDictionaryFromArray(array)
    foundhamiltonpath = 0
    lenarray = len(array)
    position = 0
    while True:
        if position >= lenarray - 1:
            arraytemp = []
            loop = 0
            for x in arrayrecursion:
                arraytemp.append(array[x[0]][0][0])
            arrayhamilton.append(copy.deepcopy(arraytemp))
            foundhamiltonpath += 1
            if foundhamiltonpath > 0 and False:
                break
            position -= 2
        else:
            arrayrecursion[position][1] += 1
            if arrayrecursion[position][1] >= len(array[arrayrecursion[position][0]][1]):
                if position == 0:#Position of last searching
                    break
                    arrayrecursion[0][0] += 1
                    if arrayrecursion[0][0] >= len(array):
                        break
                    arrayrecursion[position][1] = -1
                    position -= 1
                else:
                    arrayrecursion[position][1] = -1
                    position -= 2
            else:
                arrayrecursion[position + 1][0] = \
                dictarray[array[arrayrecursion[position][0]][1][arrayrecursion[position][1]]]
                duplicatevertex = False
                loop = 0
                while loop <= position:
                    if arrayrecursion[loop][0] == arrayrecursion[position + 1][0]:
                        duplicatevertex = True
                        break
                    loop += 1
                if duplicatevertex == True:
                    position -= 1
        position += 1
    return arrayhamilton

def searchShortestPath(array):
    arraypath = []
    return arraypath

def printGraphArraySolution(array):
    for x in array:
        print(str(x))

def printArrayStringCombination(array):
    for x in array:
        loop = len(x) - 1
        while loop >= 0:
            print(str(x[loop])+" ,",end="")
            loop -= 1

def printArrayStringCombinationSolution(arraystring, arraysolution):
    stringsolution = ""
    splitstring = " "
    loop = 0
    while loop < len(arraystring[0]):
        if loop > 0:
            stringsolution += splitstring + str(arraystring[arraysolution[0]][loop])
        else:
            stringsolution += str(arraystring[0][loop])
        loop += 1
    loop = 1
    while loop < len(arraysolution):
        stringsolution += splitstring + str(arraystring[arraysolution[loop]][0])
        loop += 1
    print(stringsolution)