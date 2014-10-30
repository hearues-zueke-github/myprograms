//BigInteger.h

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

typedef struct {
char *data;
size_t length;
short sign; // 0 for positive (default value), otherwise for negative
} BigInteger;

// BigInteger interface functions

/**
* The char array are provided from right to left, for example if you want to reprensent the number 200, you
* should use array looks like:
* char arr[] = {0, 0, 2};
*/
BigInteger* construct(char[], size_t);
BigInteger* add(BigInteger*, BigInteger*);
BigInteger* subtract(BigInteger*, BigInteger*);
char* get(BigInteger*);
void print(BigInteger*);

// utility functions
static void intcpy(char*, char*, int);
static char** get_adjusted(BigInteger*, BigInteger*);


#endif