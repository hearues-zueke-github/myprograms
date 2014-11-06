#! bin/bash

make
cp zeros test
./crypt3 e t test
cp encryption_files/test test
./crypt3 d t test
diff zeros decryption_files/test