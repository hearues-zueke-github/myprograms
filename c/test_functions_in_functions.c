#include <stdio.h>

void func11(int a) {printf("func 11,%d\n", a);}
void func12(int a) {printf("func 12,%d\n", a);}

void func21(int a) {printf("func 21,%d\n", a);}
void func22(int a) {printf("func 22,%d\n", a);}

void (*functions1[])(int) = {&func11, &func12};
void (*functions2[])(int) = {&func21, &func22};

void (**functions[])(int) = {&functions1, &functions2};

int main(int argc, char **argv)
{
  functions[1][1](5);
  return 0;
}