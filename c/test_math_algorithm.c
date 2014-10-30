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
void printIntArray(int *array, int length, int end_line)
{
  int loop;
  for (loop = 0; loop < length; loop++)
  {
    printf("%d,", array[loop]);
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
void sortArrayWithShellsort(int *array, int length)
{
  int loop = 0;
  int loop2 = 0;
  int loop3 = 0;
  int loop4 = 0;
  int temp;
  int counter = 1;
  for (;;)
  {
    counter = counter * 2 + 1;
    loop++;
    if (counter >= length)
    {
      break;
    }
  }
  int temp_jumper[loop];
  temp_jumper[0] = 1;
  counter = loop;
  for (loop2 = 1; loop2 < loop; loop2++)
  {
    temp_jumper[loop2] = temp_jumper[loop2 - 1] * 2 + 1;
  }
  for (loop2 = counter; loop2 >= 0; loop2--)
  {
    for (loop = 0; loop < temp_jumper[loop2]; loop++)
    {
      for (loop3 = 1; loop + loop3 * temp_jumper[loop2] < length; loop3++)
      {
        for (loop4 = loop3; loop + (loop4 - 1) * temp_jumper[loop2] >= 0; loop4--)
        {
          if (array[loop + (loop4 - 1) * temp_jumper[loop2]] > array[loop + loop4 * temp_jumper[loop2]])
          {
            temp = array[loop + (loop4 - 1) * temp_jumper[loop2]];
            array[loop + (loop4 - 1) * temp_jumper[loop2]] = array[loop + loop4 * temp_jumper[loop2]];
            array[loop + loop4 * temp_jumper[loop2]] = temp;
          }
          else
          {
            break;
          }
        }
      }
    }
  }
}
void getStatisticOfArray(int *array, int length)
{
  int loop = 0;
  int counter = 0;
  int position = 0;
  sortArrayWithShellsort(array, length);
  for (loop = 0; loop < length - 1; loop++)
  {
    if (array[loop] != array[loop + 1])
    {
      counter++;
    }
  }
  int array_statistic[counter][2];
  for (loop = 0; loop < counter; loop++)
  {
    array_statistic[loop][1] = 0;
  }
  position = 0;
  array_statistic[0][0] = array[0];
  array_statistic[0][1] = 1;
  for (loop = 1; loop < length; loop++)
  {
    if (array_statistic[position][0] == array[loop])
    {
      array_statistic[position][1]++;
    }
    else
    {
      position++;
      array_statistic[position][0] = array[loop];
      array_statistic[position][1] = 1;
    }
    //array_statistic[loop][1] = 0;
  }
  for (loop = 0; loop < counter; loop++)
  {
    printf("%5d, %5d\n", array_statistic[loop][0], array_statistic[loop][1]);
  }
}

int main(int argc, char **argv)
{
  int loop = 0;
<<<<<<< HEAD
  for (loop = 0; loop < 1000000; loop++)
=======
  int loop2 = 0;
  int in_length = 32;
  int combine_length = 6;
  int permutation_length = 6;
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
>>>>>>> a6edd1b9bf6f33ec5790b40b7588205ed7a0438d
  {
    if (loop2 % 10000 == 0){printf("%d\n", loop2);}
    copyArrayFromTo(array_original, array, in_length);
    fillArrayWithNumbers(array_finish, in_length, 0);
    for (loop = 0; (loop < 100000) && !checkIfArraysEqual(array_finish, array_original, in_length); loop++)
    {
      getPermutationArray(array, in_length, array_combine, combine_length, array_finish, temp_array, permutation_length);
      //printCharArray(array_finish, in_length);
      copyArrayFromTo(array_finish, array, in_length);
    }
    //printCharArray(array_combine, combine_length, 0); printf("loop=%d\n",loop);
    array_counter[loop2] = loop;
    incrementArrayByOne(array_combine, combine_length, permutation_length);
  }
  //printf("min=%d   max=%d\n", getMinOfArray(array_counter, all_possibilities), getMaxOfArray(array_counter, all_possibilities));
  //printIntArray(array_counter, all_possibilities, 1);
  getStatisticOfArray(array_counter, all_possibilities);
  //printIntArray(array_counter, all_possibilities, 1);
  return 0;
}