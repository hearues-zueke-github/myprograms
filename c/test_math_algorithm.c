#include <stdio.h>

int gcd(int n1, int n2)
{
  int number;
  if (n1 == n2)
  {
    return 0;
  }
  else
  {
    if (n1 < n2)
    {
      number = n1;
      n1 = n2;
      n2 = number;
    }
    printf("%d\n", n1);
    while (n2 > 0)
    {
      number = n1 % n2;
      n1 = n2;
      n2 = number;
      printf("%d\n", n1);
    }
  }
  return n1;
}

int main(int argc, char **argv)
{
  printf("gcd(13, 5) = %d\n", gcd(13, 5));
  return 0;
}