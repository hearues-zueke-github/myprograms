#! /usr/bin/env python3
# Author:      Ziko Haris
# Created:     2014.06.28
# Description: Seraching for the Path or Circuits with Euler or Hamilton

import GraphPackage as gp
import FactorialPackage as fp
import NumberPackage as np

array_4f = [[[1],[8,10,11,14,17,18,19,23,24]],[[2],[7,9,12,13,17,18,20,23,24]],[[3],[8,11,12,14,16,17,20,21,22]],[[4],[7,11,12,13,15,18,19,21,22]],[[5],[7,9,10,14,15,16,20,22,23]],[[6],[8,9,10,13,15,16,19,21,24]],\
[[7],[2,4,5,16,17,18,21,23,24]],[[8],[1,3,6,15,17,18,22,23,24]],[[9],[2,5,6,14,16,18,19,20,22]],[[10],[1,5,6,13,15,17,19,20,21]],[[11],[1,3,4,13,14,16,20,22,24]],[[12],[2,3,4,13,14,15,19,21,23]],\
[[13],[2,4,6,10,11,12,21,22,23]],[[14],[1,3,5,9,11,12,21,22,24]],[[15],[4,5,6,8,10,12,19,20,24]],[[16],[3,5,6,7,9,11,19,20,23]],[[17],[1,2,3,7,8,10,19,22,24]],[[18],[1,2,4,7,8,9,20,21,23]],\
[[19],[1,4,6,9,10,12,15,16,17]],[[20],[2,3,5,9,10,11,15,16,18]],[[21],[3,4,6,7,10,12,13,14,18]],[[22],[3,4,5,8,9,11,13,14,17]],[[23],[1,2,5,7,8,12,13,16,18]],[[24],[1,2,6,7,8,11,14,15,17]]]

array_test = [[[1],[2,4,5]],[[2],[1,5,3]],[[3],[4,5,2]],[[4],[1,5,3]],[[5],[1,2,3,4]]]
array_cube = [[[1],[3,4,5,6]],[[2],[3,4,5,6]],[[3],[1,2,5,6]],[[4],[1,2,5,6]],[[5],[1,2,3,4]],[[6],[1,2,3,4]]]
array_2 = [[[1],[2,3]],[[2],[1,3]],[[3],[1,2]]]
array_3 = [[[1],[2,3,4]],[[2],[1,3,4]],[[3],[1,2,4]],[[4],[1,2,3]]]
array_5_2 = [[[1],[2,3]],[[2],[3,4]],[[3],[4,5]],[[4],[5,1]],[[5],[1,2]]]
array_5_3 = [[[1],[2,3,4]],[[2],[3,4,5]],[[3],[4,5,1]],[[4],[5,1,2]],[[5],[1,2,3]]]
array_5_4 = [[[1],[2,3,4,5]],[[2],[3,4,5,1]],[[3],[4,5,1,2]],[[4],[5,1,2,3]],[[5],[1,2,3,4]]]
array_6_2 = [[[1],[2,3]],[[2],[3,4]],[[3],[4,5]],[[4],[5,6]],[[5],[6,1]],[[6],[1,2]]]
array_6_3 = [[[1],[2,3,4]],[[2],[3,4,5]],[[3],[4,5,6]],[[4],[5,6,1]],[[5],[6,1,2]],[[6],[1,2,3]]]
array_7_2 = [[[1],[2,3]],[[2],[3,4]],[[3],[4,5]],[[4],[5,6]],[[5],[6,7]],[[6],[7,1]],[[7],[1,2]]]
array_7_3 = [[[1],[2,3,4]],[[2],[3,4,5]],[[3],[4,5,6]],[[4],[5,6,7]],[[5],[6,7,1]],[[6],[7,1,2]],[[7],[1,2,3]]]
array_7_4 = [[[1],[2,3,4,5]],[[2],[3,4,5,6]],[[3],[4,5,6,7]],[[4],[5,6,7,1]],[[5],[6,7,1,2]],[[6],[7,1,2,3]],[[7],[1,2,3,4]]]
array_comb_3_2 = [[[1],[2,3]],[[2],[4,5,6]],[[3],[7,8,9]],\
				  [[4],[1,2,3]],[[5],[4,6]],[[6],[7,8,9]],\
				  [[7],[1,2,3]],[[8],[4,5,6]],[[9],[7,8]]]


#arraystring = gp.getArrayStringCombination(16,2)
#arraystringgraph = gp.getArrayStringCombinationGraph(arraystring)
#arraygraph = gp.searchHamiltonPath(arraystringgraph)
'''
gp.printGraphArraySolution(gp.searchHamiltonPath(gp.getArrayAllVertexConnected(4)))
gp.printGraphArraySolution(gp.searchHamiltonPath(gp.getArrayAllVertexConnected(5)))
gp.printGraphArraySolution(gp.searchHamiltonPath(gp.getArrayAllVertexConnected(6)))
gp.printGraphArraySolution(gp.searchHamiltonPath(gp.getArrayAllVertexConnected(7)))
gp.printGraphArraySolution(gp.searchHamiltonPath(gp.getArrayAllVertexConnected(8)))
gp.printGraphArraySolution(gp.searchHamiltonPath(gp.getArrayAllVertexConnected(9)))
gp.printGraphArraySolution(gp.searchHamiltonPath(gp.getArrayAllVertexConnected(10)))
'''
array = gp.searchHamiltonPath(array_comb_3_2)
gp.printGraphArraySolution(array)
print(len(array))
# print(array)
#print(len(array))
# gp.printArrayStringCombinationSolution(arraystring, arraygraph[0])
# print(fp.getArrayChangedElement(fp.getArrayFactorialCombination(2),0,2))
#print(np.getFactorialCombinations(3))