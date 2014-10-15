#! /usr/bin/env python3

from os import walk
from os.path import join
from subprocess import call

INPUT_D = "input"
OUTPUT_D = "output"

CRYPT = "crypt"
CRYPT_FILE = "crypt/t"
CRYPT_MODE = "e"

# recursive listdir see: http://stackoverflow.com/questions/19309667/recursive-os-listdir
# [os.path.join(dirpath, f) for dirpath, dirname, filename in os.walk(os.path.expanduser(INPUT_D)) for f in filename]
[call([CRYPT, INPUT_D + fn, CRYPT_FILE, CRYPT_MODE, OUTPUT_D + fn]) for fn in join(dirpath, f) for dirpath, dirname, filename in walk(INPUT_D) for f in filename]