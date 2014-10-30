//BigInteger.c

#include <stdio.h>
#include <stdlib.h>

#include "BigInteger.h"

BigInteger* construct(char data[], size_t length) {
if (length > 40)
return NULL;
BigInteger* bi = malloc(sizeof(BigInteger*));
bi->length = length;
bi->data = malloc(bi->length*sizeof(char));
intcpy(bi->data, data, bi->length);
return bi;
}

BigInteger* add(BigInteger* x, BigInteger* y) {
char* add_data(char*, char*, int*);

int len = (x->length > y->length) ? x->length : y->length;

char** resized = get_adjusted(x, y);
char* tmp_x = resized[0];
char* tmp_y = resized[1];

char* ret = add_data(tmp_x, tmp_y, &len);
if (ret == NULL)
return NULL;

BigInteger *b = construct(ret, len);

return b;
}

BigInteger* subtract(BigInteger* x, BigInteger* y) {
char** resized = get_adjusted(x, y);
char *tmp_x = resized[0];
char *tmp_y = resized[1];

enum Sign {
EQUAL = 0, POSITIVE = 1, NEGATIVE = 2
};

short ret_sign = EQUAL;

int i;
for (i = x->length - 1; i >= 0; i--) {
if (tmp_x[i] == tmp_y[i])
continue;
else if (tmp_x[i] > tmp_y[i]) {
ret_sign = POSITIVE;
break;
} else {
ret_sign = NEGATIVE;
break;
}

}
// TODO: separate the following logic into its own utility function
BigInteger* bi;
if (ret_sign == EQUAL) {
char ret[1] = {0};
bi= construct(ret, 1);
}else if (ret_sign == POSITIVE){
char ret[x->length];
for (i=0; i<x->length;i++){
int tmp = tmp_x[i]-tmp_y[i];
if (tmp <0){
tmp_x[i+1]--;
tmp = (tmp_x[i]+10)-tmp_y[i];
}
ret[i] = tmp;
}
bi=construct(ret, x->length);
}else{
char ret[y->length];
for (i=0; i<y->length;i++){
int tmp = tmp_y[i]-tmp_x[i];
if (tmp <0){
tmp_y[i+1]--;
tmp = (tmp_y[i]+10)-tmp_x[i];
}
ret[i] = tmp;
}
bi=construct(ret, y->length);
bi->sign = 1;
}

return bi;
}

char* get(BigInteger* bi) {
return bi->data;
}

void print(BigInteger* bi) {
char* d = bi->data;
if (bi->sign) printf("%c", '-');
int i;
for (i = (bi->length)-1; i>=0; --i) {
printf("%i", d[i]);
}
printf("\n");
}

char* add_data(char* x, char* y, int *len) {
int i, reminder = 0;
char *ret = malloc(sizeof(char) * *len);

for (i = 0; i < *len; i++) {
int tmp = x[i] + y[i] + reminder;
ret[i] = tmp % 10;
reminder = (tmp - ret[i]) / 10;
}

if (reminder) {
if (i==40){
fprintf(stderr, "Arithmetic OverFlown");
return NULL;
}else{
ret[i] =reminder;
(*len)++;
}
}
return ret;
}

static void intcpy(char* dest, char* src, int l) {
while (l-- > 0)
*dest++ = *src++;
}

static char** get_adjusted(BigInteger* x, BigInteger *y) {
char **ret = malloc(sizeof(char**));
int len = (x->length > y->length) ? x->length : y->length;

char *tmp_x = get(x);
char *tmp_y = get(y);

int diff;
if ((diff = len - x->length) > 0) {
intcpy(tmp_x, get(x), len);
while (diff > 0) {
tmp_x[x->length++] = 0;
diff--;
}
} else if ((diff = len - y->length) > 0) {
intcpy(tmp_y, get(y), len);
while (diff > 0) {
tmp_y[y->length++] = 0;
diff--;
}
}
ret[0] = tmp_x;
ret[1] = tmp_y;
return ret;
}