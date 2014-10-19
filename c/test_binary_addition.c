#include <stdio.h>

int main(int argc, char **argv)
{
  char a;
  unsigned char b;
  unsigned char c;
  int array_i[10];
  a = 0xFF;
  b = a;
  c = b + a;
  printf("a=%d  b=%d  c=%d", a, b, c);
	return 0;
}