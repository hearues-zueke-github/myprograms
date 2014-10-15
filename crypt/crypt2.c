#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NUMBER_ALGORITHM 8

int fileSize(FILE *file);
void pressEnter();
void printArray(unsigned char *array, int array_length);
void algorithmEncrypt(unsigned char *array_in, int array_length_in, unsigned char *array_crypt, int array_length_crypt);
void algorithmDecrypt(unsigned char *array_in, int array_length_in, unsigned char *array_crypt, int array_length_crypt);

int main(int argc, char **argv)
{
  int output_status = 0;
  int output_files = 0;
  int press_enter = 0;
  int crypt_modus;
  if (argc != 5)
  {
    printf("Wrong usage: <program> <file_in> <file_crypt> <crypt_modus> <file_out>\n");
    pressEnter();
    return 1;
  }

  if ((argv[3][0] != 'e') && (argv[3][0] != 'd') &&
      (argv[3][0] != '1') && (argv[3][0] != '2'))
  {
    printf("4th argument is false! Use:\ne or 1 for encrypt\nOR\nd or 2 for decrypt\n");
    pressEnter();
    return 1;
  }
  if ((argv[3][0] == 'e') || (argv[3][0] == '1'))
  {
    crypt_modus = 1;
  }
  else if ((argv[3][0] == 'd') || (argv[3][0] == '2'))
  {
    crypt_modus = 2;
  }
  //printf("%s\n", argv[1]);
  char *file_name_in = argv[1];
  char *file_name_crypt = argv[2];
  char *file_name_out = argv[4];

  FILE *file_in = fopen(file_name_in, "rb");
  FILE *file_crypt = fopen(file_name_crypt, "rb");

  int array_length_in;
  int array_length_crypt;

  unsigned char *array_in;
  unsigned char *array_crypt;

  if (file_in == NULL)
  {
    printf("<file_in> not found!\n");
    pressEnter();
    return 2;
  }
  if (file_crypt == NULL)
  {
    printf("<file_crypt> not found!\n");
    fclose(file_in);
    pressEnter();
    return 2;
  }
  if (output_status == 1)
  {
    printf("Files OK!\n");
    printf("Modus: %d\n", crypt_modus);
  }

  array_length_in = fileSize(file_in);
  array_length_crypt = fileSize(file_crypt);

  array_in = (unsigned char*) malloc(sizeof(char) * array_length_in);
  if (array_in == NULL)
  {
    fclose(file_in);
    fclose(file_crypt);
    printf("No more memory!\n");
    return 3;
  }
  array_crypt = (unsigned char*) malloc(sizeof(char) * array_length_crypt);
  if (array_crypt == NULL)
  {
    fclose(file_in);
    fclose(file_crypt);
    free(array_in),
    printf("No more memory!\n");
    return 3;
  }

  fread(array_in, array_length_in, sizeof(char), file_in);
  fread(array_crypt, array_length_crypt, sizeof(char), file_crypt);
  fclose(file_in);
  fclose(file_crypt);
  if (output_files == 1)
  {
    printf("File in:\n");
    printArray(array_in, array_length_in);
    printf("Crypt:\n");
    printArray(array_crypt, array_length_crypt);
  }

  if (crypt_modus == 1)
  {
    algorithmEncrypt(array_in, array_length_in, array_crypt, array_length_crypt);
  }
  else if (crypt_modus == 2)
  {
    algorithmDecrypt(array_in, array_length_in, array_crypt, array_length_crypt);
  }
  if (output_files == 1)
  {
    printf("Array Out:\n");
    printArray(array_in, array_length_in);
  }

  FILE *file_out = fopen(file_name_out, "wb");
  fwrite(array_in, array_length_in, sizeof(char), file_out);
  fclose(file_out);
  free(array_in);
  free(array_crypt);
  if (output_status == 1)
  {
    printf("Finish!\n");
  }
  if (press_enter == 1)
  {
    pressEnter();
  }
  return 0;
}

int fileSize(FILE *file)
{
  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  fseek(file, SEEK_SET, 0);
  return size;
}

void pressEnter()
{
  printf("Press ENTER to exit...");
  while(getchar() != '\n')
  {
  }
}

void printArray(unsigned char *array, int array_length)
{
  int loop;
  loop = 0;
  while (loop < array_length)
  {
    if ((loop % 16 == 0) && (loop != 0))
    {
      printf("\n%02x ", array[loop]);
    }
    else
    {
      printf("%02x ", array[loop]);
    }
    loop++;
  }
  printf("\n");
}

void algorithmEncrypt(unsigned char *array_in, int array_length_in, unsigned char *array_crypt, int array_length_crypt)
{
  int main_loop;
  int loop1;
  int loop2;
  int loop3;
  int temp_int;
  int value1;
  int value2;
  int value3;
  main_loop = 0;
  value3 = (array_length_in > 255 ? 255 : array_length_in / 2);
  while (main_loop < array_length_crypt - 1)
  {
    value1 = ((int)(array_crypt[main_loop] & 0xFF)) % NUMBER_ALGORITHM;
    value2 = ((int)(array_crypt[main_loop + 1] & 0xFF)) % ((int)(value3)) + 1;
    switch (value1)
    {
      case 0:
        loop1 = 0;
        while (loop1 + value2 < array_length_in)
        {
          temp_int = array_in[loop1];
          array_in[loop1] = array_in[loop1 + value2];
          array_in[loop1 + value2] = temp_int;
          loop1++;
        }
      break;

      case 1:
        loop1 = array_length_in - 1;
        while (loop1 - value2 >= 0)
        {
          temp_int = array_in[loop1];
          array_in[loop1] = array_in[loop1 - value2];
          array_in[loop1 - value2] = temp_int;
          loop1--;
        }
      break;

      case 2:
        loop1 = 0;
        loop2 = 1;
        while (loop1 < array_length_in)
        {
          temp_int = 255 - array_in[loop1];
          if (temp_int >= loop2)
          {
            array_in[loop1] = array_in[loop1] + loop2;
          }
          else
          {
            array_in[loop1] = loop2 - temp_int - 1;
          }
          loop1++;
          loop2++;
          if (loop2 > value2)
          {
            loop2 = 1;
          }
        }
      break;

      case 3:
        loop1 = array_length_in - 1;
        loop2 = 1;
        while (loop1 >= 0)
        {
          temp_int = 255 - array_in[loop1];
          if (temp_int >= loop2)
          {
            array_in[loop1] = array_in[loop1] + loop2;
          }
          else
          {
            array_in[loop1] = loop2 - temp_int - 1;
          }
          loop1--;
          loop2++;
          if (loop2 > value2)
          {
            loop2 = 1;
          }
        }
      break;

      case 4:
        loop1 = 0;
        loop2 = 1;
        while (loop1 < array_length_in - 2)
        {
          if ((loop1 + loop2) < array_length_in)
          {
            temp_int = array_in[loop1];
            array_in[loop1] = array_in[loop1 + loop2];
            array_in[loop1 + loop2] = temp_int;
          }
          loop2++;
          if (loop2 > value2)
          {
            loop2 = 1;
          }
          loop1++;
        }
      break;

      case 5:
        loop1 = array_length_in - 1;
        loop2 = 1;
        while (loop1 > 0)
        {
          if ((loop1 - loop2) >= 0)
          {
            temp_int = array_in[loop1];
            array_in[loop1] = array_in[loop1 - loop2];
            array_in[loop1 - loop2] = temp_int;
          }
          loop2++;
          if (loop2 > value2)
          {
            loop2 = 1;
          }
          loop1--;
        }
      break;

      case 6:
        loop1 = 0;
        loop2 = 0;
        loop3 = 1;
        while (loop1 < array_length_in)
        {
          array_in[loop1] += loop3;
          loop3++;
          if (loop3 > loop2 + 1)
          {
            loop3 = 1;
            loop2++;
            if (loop2 >= value2)
            {
              loop2 = 0;
            }
          }
          loop1++;
        }
      break;

      case 7:
        loop1 = array_length_in - 1;
        loop2 = 0;
        loop3 = 1;
        while (loop1 >= 0)
        {
          array_in[loop1] += loop3;
          loop3++;
          if (loop3 > loop2 + 1)
          {
            loop3 = 1;
            loop2++;
            if (loop2 >= value2)
            {
              loop2 = 0;
            }
          }
          loop1--;
        }
      break;
    }
    main_loop += 2;
  }
}

void algorithmDecrypt(unsigned char *array_in, int array_length_in, unsigned char *array_crypt, int array_length_crypt)
{
  int main_loop;
  int loop1;
  int loop2;
  int loop3;
  int temp_int;
  int value1;
  int value2;
  int value3;
  main_loop = (array_length_crypt / 2) * 2 - 2;
  value3 = (array_length_in > 255 ? 255 : array_length_in / 2);
  while (main_loop >= 0)
  {
    value1 = ((int)(array_crypt[main_loop] & 0xFF)) % NUMBER_ALGORITHM;
    value2 = ((int)(array_crypt[main_loop + 1] & 0xFF)) % ((int)(value3)) + 1;
    switch (value1)
    {
      case 0:
        loop1 = array_length_in - 1;
        while (loop1 - value2 >= 0)
        {
          temp_int = array_in[loop1];
          array_in[loop1] = array_in[loop1 - value2];
          array_in[loop1 - value2] = temp_int;
          loop1--;
        }
      break;

      case 1:
        loop1 = 0;
        while (loop1 + value2 < array_length_in)
        {
          temp_int = array_in[loop1];
          array_in[loop1] = array_in[loop1 + value2];
          array_in[loop1 + value2] = temp_int;
          loop1++;
        }
      break;

      case 2:
        loop1 = 0;
        loop2 = 1;
        while (loop1 < array_length_in)
        {
          array_in[loop1] -= loop2;
          loop1++;
          loop2++;
          if (loop2 > value2)
          {
            loop2 = 1;
          }
        }
      break;

      case 3:
        loop1 = array_length_in - 1;
        loop2 = 1;
        while (loop1 >= 0)
        {
          array_in[loop1] -= loop2;
          loop1--;
          loop2++;
          if (loop2 > value2)
          {
            loop2 = 1;
          }
        }
      break;

      case 4:
        loop1 = array_length_in - 1;
        if ((loop2 = array_length_in % value2) == 0)
        {
          loop2 = value2;
        }
        while (loop1 >= 0)
        {
          if ((loop1 + loop2) < array_length_in)
          {
            temp_int = array_in[loop1];
            array_in[loop1] = array_in[loop1 + loop2];
            array_in[loop1 + loop2] = temp_int;
          }
          loop2--;
          if (loop2 < 1)
          {
            loop2 = value2;
          }
          loop1--;
        }
      break;

      case 5:
        loop1 = 0;
        if ((loop2 = array_length_in % value2) == 0)
        {
          loop2 = value2;
        }
        while (loop1 <= array_length_in - 1)
        {
          if ((loop1 - loop2) >= 0)
          {
            temp_int = array_in[loop1];
            array_in[loop1] = array_in[loop1 - loop2];
            array_in[loop1 - loop2] = temp_int;
          }
          loop2--;
          if (loop2 < 1)
          {
            loop2 = value2;
          }
          loop1++;
        }
      break;

      case 6:
        loop1 = 0;
        loop2 = 0;
        loop3 = 1;
        while (loop1 < array_length_in)
        {
          array_in[loop1] -= loop3;
          loop3++;
          if (loop3 > loop2 + 1)
          {
            loop3 = 1;
            loop2++;
            if (loop2 >= value2)
            {
              loop2 = 0;
            }
          }
          loop1++;
        }
      break;

      case 7:
        loop1 = array_length_in - 1;
        loop2 = 0;
        loop3 = 1;
        while (loop1 >= 0)
        {
          array_in[loop1] -= loop3;
          loop3++;
          if (loop3 > loop2 + 1)
          {
            loop3 = 1;
            loop2++;
            if (loop2 >= value2)
            {
              loop2 = 0;
            }
          }
          loop1--;
        }
      break;
    }
    main_loop -= 2;
  }
}