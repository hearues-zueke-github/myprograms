#include <stdio.h>

#define IN_LENGTH 10
#define COMBINE_LENGTH 4
#define PERMUTATION_LENGTH 3

void getPermutationArray(char *in, int in_length, char *combine, int combine_length, char *permutation, char *temp, int permutation_length)
{
  int temp_length = 0;
  int loop;
  if (combine_length < permutation_length)
  {
    printf("Combine length < permutation length");
  }
  else
  {
    for (loop = 0; loop < combine_length; loop++)
    {
      combine[loop] = combine[loop] % permutation_length == 0 ?
                      combine[loop] = permutation_length :
                      combine[loop] % permutation_length;
    }
    for (loop = 0; loop < in_length; loop++)
    {
      if (loop < permutation_length && loop < in_length)
      {
        temp[loop] = in[loop];
        permutation[loop] = in[loop];
        temp_length++;
      }
      else
      {
        if (loop < in_length - permutation_length)
        {

        }
        else
        {

        }
      }
    }
  }
}

void printCharArray(char *array, int array_length)
{
  int loop;
  printf("Char Array Output:\n");
  for (loop = 0; loop < array_length; loop++)
  {
    printf("%d, ", array[loop]);
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

int main(int argc, char **argv)
{
  //printf("gcd(13, 5) = %d\n", gcd(13, 5));
  char array[IN_LENGTH] = {2,6,4,3,5,8,1,10,9,7};
  char array_combine[COMBINE_LENGTH] = {3,4,6,5};
  char temp_array[PERMUTATION_LENGTH];
  printCharArray(array, IN_LENGTH);
  char array_finish[IN_LENGTH];
  getPermutationArray(array, IN_LENGTH, array_combine, COMBINE_LENGTH, array_finish, temp_array, PERMUTATION_LENGTH);
  printCharArray(array_finish, IN_LENGTH );
  return 0;
}