#! /usr/bin/python3

import sys
import copy
from random import randint

array_formula_n = [["n","(n+0)"], \
                   ["n","(n-0)"], \
                   ["n","(0+n)"], \
                   ["n","(n*1)"], \
                   ["n","(n/1)"], \
                   ["n","(1*n)"]]
array_formula_1 = [["1","(n^0)"], \
                   ["1","(n/n)"], \
                   ["1","(exp(0))"]]
array_formula_0 = [["0","(0^n)"], \
                   ["0","(n-n)"], \
                   ["0","(ln(1))"]]
array_formula = [copy.deepcopy(array_formula_n), \
                 copy.deepcopy(array_formula_1), \
                 copy.deepcopy(array_formula_0)]

def main():
  if len(sys.argv) < 3 and False:
    print("FALSE")
  # if
  variable_to_calculate = "n"
  variable_as_constants = ["a","b","c","d","e"]
  formula = "n"
  loop_complication = 0
  for loop_complication in range(10):
    what_to_complicate = randint(0,2)
    
  # for
  return 0
# main

if __name__ == "__main__":
  main()
# if