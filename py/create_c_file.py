#! /usr/bin/python3

import sys

def main():
	if len(sys.argv) < 3:
		print("Wrong Arguments, try:\n" \
			    "./<program> <name> <language>\n" \
			    "For langue type:\n" \
			    "c|C for C-Language\n" \
			    "cpp|c++|CPP|C++ for C++-Language")
		return 1
	#end if
	fileout = open(sys.argv[1], "w")
	if sys.argv[2] == "c" or sys.argv[2] == "C":
		fileout.write("#include <stdio.h>\n\n")
		fileout.write("int main(int argc, char **argv)\n{\n")
		fileout.write("  return 0;\n")
		fileout.write("}")
	#end if
	fileout.close()
	return 0
#end main

if __name__ == "__main__":
  main()