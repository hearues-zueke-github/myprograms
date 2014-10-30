#include <stdio.h>

#define IN_LENGTH 50
#define COMBINE_LENGTH 64
#define PERMUTATION_LENGTH 16

void printCharArray(char *array, int length)
{
  int loop;
  for (loop = 0; loop < length; loop++)
  {
    printf("%2d,", array[loop]);
  }
  printf("\n");
}
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
void copyArrayFromOther(char *from, char *to, int length)
{
  int loop = 0;
    for (loop = 0; loop < length; loop++)
    {
      to[loop] = from[loop];
    }
}
void getPermutationArray(char *in, int in_length, char *combine, int combine_length, char *permutation, char *temp, int permutation_length)
{
  int temp_length = 0;
  int temp_position = 0;
  int loop;
  int loop2;
  int loop3;
  int loop4;
  for (loop = 0; loop < combine_length; loop++)
  {
    combine[loop] = combine[loop] % permutation_length == 0 ? permutation_length : combine[loop] % permutation_length;
  }
  loop2 = 0;
  for (loop = 0; loop < in_length; loop++)
  {
    if (temp_length < permutation_length)
    {
      temp[loop] = in[loop];
      temp_length++;
    }
    else
    {
      loop2 = loop2 % combine_length;
      temp_position = combine[loop2];
      permutation[loop - permutation_length] = temp[temp_position - 1];
      for (loop3 = temp_position - 1; loop3 < permutation_length - 1; loop3++)
      {
        temp[loop3] = temp[loop3 + 1];
      }
      temp[permutation_length - 1] = in[loop];
      loop2++;
    }
  }
  for (loop3 = permutation_length; loop3 > 0; loop3--)
  {
    loop2 = loop2 % combine_length;
    temp_position = (combine[loop2] - 1) % loop3;
    permutation[in_length - permutation_length - 1 + loop3] = temp[temp_position];
    for (loop4 = temp_position; loop4 < loop3 - 1; loop4++)
    {
      temp[loop4] = temp[loop4 + 1];
    }
    loop2++;
  }
}
int findElementInArray(char *array, int length, char value)
{
  int loop = 0;
  for (loop = 0; loop < length; loop++)
  {
    if (array[loop] == value)
    {
      return loop;
    }
  }
  return -1;
}

int main(int argc, char **argv)
{
  char array[IN_LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
  char array_combine[COMBINE_LENGTH] = {2,8,7,2,5,4,3,2,5,7,4,2,4,5,1,5,7,2,2,4,5,7,7,4,1,2,5,4,3,5,2,7};
  char temp_array[PERMUTATION_LENGTH];
  printCharArray(array, IN_LENGTH);
  char array_finish[IN_LENGTH];
  int loop = 0;
  for (loop = 0; loop < 1000000; loop++)
  {
    getPermutationArray(array, IN_LENGTH, array_combine, COMBINE_LENGTH, array_finish, temp_array, PERMUTATION_LENGTH);
    printCharArray(array_finish, IN_LENGTH);
    copyArrayFromOther(array_finish, array, IN_LENGTH);
  }
  return 0;
}