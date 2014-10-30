//main.c

#include <stdio.h>
#include "BigInteger.h"

void test_add1() {
printf("Start Testing ADD n");
char d1[] = { 1, 2};            // from right to left, so its value is 21
char d2[] = { 5};                       // and this is 5

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = add(bi1, bi2);
print(ret);
printf("End Testing...n");
}
void test_add2() {
printf("Start Testing ADD n");
char d1[40];
char d2[40];

int i=0;
for (i=0; i<40;i++){
d1[i] = 3;
d2[i] = 5;
}

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = add(bi1, bi2);
print(ret);
printf("End Testing...n");
}

/**
* Will print "Arithmetic Overflow" and returns NULL
*/
void test_add3() {
printf("Start Testing ADD n");
char d1[40];
char d2[40];

int i=0;
for (i=0; i<40;i++){
d1[i] = 5;
d2[i] = 5;
}

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = add(bi1, bi2);
if (ret == NULL)
printf("NULLn");
//print(ret);
printf("End Testing...n");
}

void test_add4() {
printf("Start Testing ADD n");
char d1[] = { 9, 9};
char d2[] = { 9, 9};

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = add(bi1, bi2);
print(ret);
printf("End Testing...n");
}

void test_add5() {
printf("Start Testing ADD n");
char d1[] = { 1, 2, 0, 0, 1, 2, 3, 4, 5, 9 ,3, 1, 3, 4, 4, 2, 1};               // from right to left, so its value is 21
char d2[] = { 1, 3, 3, 4, 5, 5, 3, 0, 0, 0, 0, 0, 2, 1, 1, 1, 9};                       // and this is 5

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = add(bi1, bi2);
print(ret);
printf("End Testing...n");
}

void test_subtract1() {
printf("Start Testing SUBTRACT n");
char d1[] = { 1, 2};            // this is 21
char d2[] = { 5, 2};            // and this is 25

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = subtract(bi1, bi2);
print(ret);
printf("End Testing...n");
}

void test_subtract2() {
printf("Start Testing SUBTRACT n");

char d1[] = { 9, 9};
char d2[] = { 9, 9};

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = subtract(bi1, bi2);
print(ret);
printf("End Testing...n");
}

void test_subtract3() {
printf("Start Testing SUBTRACT n");

char d1[40];
char d2[40];

int i=0;
for (i=0; i<40;i++){
d1[i] = 3;
d2[i] = 5;
}

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = subtract(bi1, bi2);
print(ret);
printf("End Testing...n");
}

void test_subtract4() {
printf("Start Testing SUBTRACT n");

char d1[] = { 1, 2, 0, 0, 1, 2, 3, 4, 5, 9 ,3, 1, 3, 4, 4, 2, 1};               // from right to left, so its value is 21
char d2[] = { 1, 3, 3, 4, 5, 5, 3, 0, 0, 0, 0, 0, 2, 1, 1, 1, 9};                       // and this is 5

BigInteger* bi1 = construct(d1, sizeof(d1) / sizeof(char));
BigInteger* bi2 = construct(d2, sizeof(d2) / sizeof(char));
print(bi1);
print(bi2);
BigInteger *ret = subtract(bi1, bi2);
print(ret);
printf("End Testing...n");
}


int main(void) {
test_add1();
test_add2();
test_add3();
test_add4();
test_add5();
test_subtract1();
test_subtract2();
test_subtract3();
test_subtract4();
return 0;
}