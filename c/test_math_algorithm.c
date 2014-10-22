#include <stdio.h>

void printCharArray(char *array, int length, int end_line)
{
  int loop;
  for (loop = 0; loop < length; loop++)
  {
    printf("%2d,", array[loop]);
  }
  if (end_line == 1)
  {
    printf("\n");
  }
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
void copyArrayFromTo(char *from, char *to, int length)
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
int checkIfArraysEqual(char *array1, char *array2, int length)
{
  int loop = 0;
  for (loop = 0; loop < length; loop++)
  {
    if (array1[loop] != array2[loop])
    {
      return 0;
    }
  }
  return 1;
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
void fillArrayWithNumbers(char *array, int length, int modus)
{
  int loop = 0;
  if (modus == 0)
  {
    for (loop = 0; loop < length; loop++)
    {
      array[loop] = 1;
    }
  }
  if (modus == 1)
  {
    for (loop = 0; loop < length; loop++)
    {
      array[loop] = loop + 1;
    }
  }
}
int incrementArrayByOne(char *array, int length, int max_number)
{
  int loop = 0;
  max_number++;
  for (loop = 0; loop < length; loop++)
  {
    array[loop]++;
    if (array[loop] % max_number == 0)
    {
      array[loop] = 1;
      if (loop == length - 1)
      {
        return 1;
      }
    }
    else
    {
      break;
    }
  }
  return 0;
}
int power(int n1, int n2)
{
  int loop = 0;
  int temp = 1;
  for (loop = 0; loop < n2; loop++)
  {
    temp *= n1;
  }
  return temp;
}
int getMinOfArray(int *array, int length)
{
  int loop = 0;
  int min = array[0];
  for (loop = 1; loop < length; loop++)
  {
    if (min > array[loop])
    {
      min = array[loop];
    }
  }
  return min;
}
int getMaxOfArray(int *array, int length)
{
  int loop = 0;
  int max = array[0];
  for (loop = 1; loop < length; loop++)
  {
    if (max < array[loop])
    {
      max = array[loop];
    }
  }
  return max;
}

int main(int argc, char **argv)
{
  int loop = 0;
  int loop2 = 0;
  int in_length = 64;
  int combine_length = 4;
  int permutation_length = 8;
  char array_original[in_length];
  fillArrayWithNumbers(array_original, in_length, 1);
  char array[in_length];
  char array_combine[combine_length];
  fillArrayWithNumbers(array_combine, combine_length, 0);
  char temp_array[permutation_length];
  char array_finish[in_length];
  int all_possibilities = power(permutation_length, combine_length);
  int array_counter[all_possibilities];
  for (loop2 = 0; loop2 < all_possibilities; loop2++)
  {
    copyArrayFromTo(array_original, array, in_length);
    fillArrayWithNumbers(array_finish, in_length, 0);
    for (loop = 0; (loop < 100000) && !checkIfArraysEqual(array_finish, array_original, in_length); loop++)
    {
      getPermutationArray(array, in_length, array_combine, combine_length, array_finish, temp_array, permutation_length);
      //printCharArray(array_finish, in_length);
      copyArrayFromTo(array_finish, array, in_length);
    }
    printCharArray(array_combine, combine_length, 0);
    printf("loop=%d\n",loop);
    array_counter[loop2] = loop;
    incrementArrayByOne(array_combine, combine_length, permutation_length);
  }
  printf("min=%d   max=%d\n", getMinOfArray(array_counter, all_possibilities), getMaxOfArray(array_counter, all_possibilities));
  return 0;
}
