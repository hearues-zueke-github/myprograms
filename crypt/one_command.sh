#! /bin/bash
./create_random_hex_file.py
./crypt3 e t random_hex.hex
cp encryption_files/random_hex.hex random_hex2.hex
./crypt3 d t random_hex2.hex
./check_if_files_equal.py random_hex.hex decryption_files/random_hex2.hex