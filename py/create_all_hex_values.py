#! /usr/bin/python3
m="0123456789ABCDEF";a=0;b=0;s=""
for a in range(0, 256):s+=str(m[int(a/16)%16])+str(m[a%16]);
print(s)