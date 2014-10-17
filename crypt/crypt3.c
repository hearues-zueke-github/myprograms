// Author: Ziko Haris
// Date: 2014.10.16 (YYYYMMDD)
// Title: My Crypt Program, 3rd time XD, again
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define TRUE 1
#define FALSE 0
#define FILE_CRYPT_SIZE_MAX 4194304
#define B1 0x1
#define B2 0x3
#define B3 0x7
#define B4 0xF
#define B5 0x1F
#define B6 0x3F
#define B7 0x7F
#define B8 0xFF
// IMPORTANT !!!!
#define MS 4

#define ERR_WRONG_USAGE 1
#define ERR_NO_MODE 2
#define ERR_FILE_NOT_FOUND 3
#define ERR_FILE_NOT_CORRECT 4

void waitForEnter();
size_t fileSize(FILE *file);

//// Short function overview of the (en/de)cryption of this program:
//// The Matrix will be mixed by 2 Bytestime
//// mode,row1,row2,row3,dimension,
//// 1st byte: e.g. 10010111
////              0b10 is the crypt mode
////                0b01 is the 1st row
////                  0b01 is the 2nd row
////                    0b11 is the 3rd row
//// 2nd byte: e.g. 01110110
////              0b01 is the line dimenion, in which line this will happen
////                0b1 is the direction, which will be crypted
////                 0b10110 is the value for the (en/de)cryption
void encryption(char matrix[MS][MS][MS][MS], char *crypt, int crypt_length);
void decryption(char matrix[MS][MS][MS][MS], char *crypt, int crypt_length);

void increment(char matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void decrement(char matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void shift(char matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void invert(char matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);

void (*functions[])(char [MS][MS][MS][MS], int, int, int, int) = {&increment, &decrement, &shift, &invert};

int main (int argc, char **argv)
{
  int flag_cryptmodus;
  int flag_output_status = 1;
  char matrix[MS][MS][MS][MS];
  char crypt[4194304];
  int file_crypt_size;
  long long file_in_size;
  long long file_in_position;
  if (argc < 4)
  {
    printf("Wrong usage: <program> <crypt_modus> <file_crypt> <file_in>...\n");
    waitForEnter();
    return 1;
  }
  if ((strlen(argv[1]) > 1) || ((argv[1][0] != 'e') && (argv[1][0] != 'd')))
  {
    printf("1st argument is false! Use:\ne for encrypt\nOR\nd for decrypt\n");
    waitForEnter();
    return 1;
  }
  if (argv[1][0] == 'e')
  {
    flag_cryptmodus = 1;
  }
  else if (argv[1][0] == 'd')
  {
    flag_cryptmodus = 2;
  }
  FILE *file_crypt = fopen(argv[2], "rb");
  if (file_crypt == NULL)
  {
    printf("<file_crypt> not found!\n");
    waitForEnter();
    return 2;
  }
  file_crypt_size = fileSize(file_crypt);
  if (file_crypt_size > FILE_CRYPT_SIZE_MAX)
  {
    printf("Crypt File is too big! It should not be bigger than 4 MiB!\n");
    fclose(file_crypt);
    return 3;
  }
  fread(crypt, file_crypt_size, sizeof(char), file_crypt);
  fclose(file_crypt);
  if (flag_output_status == TRUE)
  {
    printf("Crypt File OK!\n");
    printf("Modus: %d\n", flag_cryptmodus);
  }
  int loop_file = 3;
  if (flag_cryptmodus == 1) { // encryption
    while (loop_file < argc) {
      FILE *file_in = fopen(argv[loop_file], "rb");
      system("[ -d encryption_files ] || mkdir encryption_files\n");
      char filenamedest[strlen(argv[loop_file]) + 8];
      strcpy(filenamedest, "encryption_files/");
      strcat(filenamedest, argv[loop_file]);
      FILE *file_out = fopen(filenamedest, "wb");
      if (file_in != NULL) {
        file_in_size = fileSize(file_in);
        int loop = 8;
        while (loop > 0)
        {
          fputc((file_in_size >> (8 * (loop - 1))) & 0xFF, file_out);
          loop--;
        }
        file_in_position = file_in_size;
        while (file_in_position > 0) {
          int pos = 0;
          // read in
          for(; (pos < (MS*MS*MS*MS)) && (file_in_position - pos > 0); pos++) {
            matrix[(pos / (MS*MS*MS)) % MS][(pos / (MS*MS)) % MS][(pos / MS) % MS][pos % MS] = fgetc(file_in);
          }
          file_in_position -= pos;
          // check, if last pos is MS*MS*MS*MS (e.g. for MS = 4 is MS^4 = 256)
          if (pos != (MS*MS*MS*MS))
          {
            int loop_fill_rest = pos;
            while (loop_fill_rest < (MS*MS*MS*MS)) {
              matrix[(loop_fill_rest / (MS*MS*MS)) % MS][(loop_fill_rest / (MS*MS)) % MS][(loop_fill_rest / MS) % MS][loop_fill_rest % MS] = 0;
              loop_fill_rest++;
            }
          }
          // encrypt algorithm
          encryption(matrix, crypt, file_crypt_size);
          // write out
          if (pos > 0) {
            int loop = 0;
            while (loop < (MS*MS*MS*MS)) {
              fputc(matrix[(loop / (MS*MS*MS)) % MS][(loop / (MS*MS)) % MS][(loop / MS) % MS][loop % MS], file_out);
              loop++;
            }
          }
        }
        fclose(file_in);
        fclose(file_out);
      }
      else
      {
        printf("File %s is not found!\n", argv[loop_file]);
      }  
      loop_file++;
    } // end while
  }
  else if (flag_cryptmodus == 2) { // decryption
    while (loop_file < argc) {
      FILE *file_in = fopen(argv[loop_file], "rb");
      system("[ -d decryption_files ] || mkdir decryption_files\n");
      char filenamedest[strlen(argv[loop_file]) + 8];
      strcpy(filenamedest, "decryption_files/");
      strcat(filenamedest, argv[loop_file]);
      FILE *file_out = fopen(filenamedest, "wb");
      if (file_in != NULL) {
        file_in_size = fileSize(file_in);
        int file_size_number = 0;
        int shift = 8;
        while (shift > 0)
        {
          file_size_number += (fgetc(file_in) & 0xFF) << (8 * (shift - 1));
          shift--;
        }
        file_in_position = file_in_size - 8;
        if (file_in_position >= file_size_number) {
          while (file_in_position > 0) {
            int pos = 0;
            // read in
            for(; (pos < (MS*MS*MS*MS)) && (file_in_position - pos > 0); pos++) {
              matrix[pos / (MS*MS*MS)][pos / (MS*MS)][pos / MS][pos % MS] = fgetc(file_in);
            }
            // decrypt algorithm

            // write out
            file_in_position -= pos;
            if (pos > 0) {
              int loop = 0;
              while (loop < pos) {
                fputc(matrix[pos / (MS*MS*MS)][pos / (MS*MS)][pos / MS][pos % MS], file_out);
                loop++;
              }
            }
          }
        }
        else
        {
          printf("Something is wrong with the File! Maybe not a encrypted File???\n");
        }
        fclose(file_in);
        fclose(file_out);
      }
      else
      {
        printf("File %s is not found!\n", argv[loop_file]);
      }  
      loop_file++;
    }  // end while
  }
  return 0;
}

void waitForEnter()
{
  printf("Press ENTER to exit...");
  while(getchar() != '\n')
  {
  }
}
size_t fileSize(FILE *file)
{
  size_t offset = ftell(file);
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, SEEK_SET, offset);
  return size;
}

void encryption(char matrix[MS][MS][MS][MS], char *crypt, int crypt_length)
{
  int b1; int b2; int b3; int b4;
  int loop = 0;
  while (loop + 3 < crypt_length)
  {
    b1 = crypt[loop];
    b2 = crypt[loop + 1];
    b3 = crypt[loop + 2];
    b4 = crypt[loop + 3];
    switch ((b1 >> 6) & B2)
    {
      case 0: functions[0](matrix, b1, b2, b3, b4); break;
      case 1: functions[1](matrix, b1, b2, b3, b4); break;
      case 2: functions[2](matrix, b1, b2, b3, b4); break;
      case 3: functions[3](matrix, b1, b2, b3, b4); break;
    }
    loop += 4;
  }
}
void decryption(char matrix[MS][MS][MS][MS], char *crypt, int crypt_length)
{

}

void increment(char matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  int row1,  row2, row3;
  int direction, dim1, dim2, dim3;
  int jumper, shifter, multiplier;
  int value;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  int loop1,loop2, loop3;
  if (direction == 0)
  {
    // 1st Dimension
    for (loop = 0; loop < MS; loop++)
    {
      switch (dim1)
      {
        case 0: matrix[row1][row2][row3][loop] = matrix[row1][row2][row3][loop] + (value & 0xFF); break;
        case 1: matrix[row1][row2][loop][row3] = matrix[row1][row2][loop][row3] + (value & 0xFF); break;
        case 2: matrix[row1][loop][row2][row3] = matrix[row1][loop][row2][row3] + (value & 0xFF); break;
        case 3: matrix[loop][row1][row2][row3] = matrix[loop][row1][row2][row3] + (value & 0xFF); break;
      }
    }
    // 2nd Dimension
    for (loop1 = 0; loop1 < MS; loop1++)
    {
      for (loop2 = 0; loop2 < MS; loop2++)
      {
        switch (dim2)
        {
          case 6:
          case 0: matrix[row1][row2][loop1][loop2] = matrix[row1][row2][loop1][loop2] + (value & 0xFF); break;
          case 1: matrix[row1][loop1][row2][loop2] = matrix[row1][loop1][row2][loop2] + (value & 0xFF); break;
          case 2: matrix[row1][loop1][loop2][row2] = matrix[row1][loop1][loop2][row2] + (value & 0xFF); break;
          case 3: matrix[loop1][row1][row2][loop2] = matrix[loop1][row1][row2][loop2] + (value & 0xFF); break;
          case 4: matrix[loop1][row1][loop2][row2] = matrix[loop1][row1][loop2][row2] + (value & 0xFF); break;
          case 7:
          case 5: matrix[loop1][loop2][row1][row2] = matrix[loop1][loop2][row1][row2] + (value & 0xFF); break;
        }
      }
    }
    // 3rd Dimension
    for (loop1 = 0; loop1 < MS; loop1++)
    {
      for (loop2 = 0; loop2 < MS; loop2++)
      {
        for (loop3 = 0; loop3 < MS; loop3++)
        {
          switch (dim3)
          {
            case 0: matrix[row1][loop1][loop2][loop3] = matrix[row1][loop1][loop2][loop3] + (value & 0xFF); break;
            case 1: matrix[loop1][row1][loop2][loop3] = matrix[loop1][row1][loop2][loop3] + (value & 0xFF); break;
            case 2: matrix[loop1][loop2][row1][loop3] = matrix[loop1][loop2][row1][loop3] + (value & 0xFF); break;
            case 3: matrix[loop1][loop2][loop3][row1] = matrix[loop1][loop2][loop3][row1] + (value & 0xFF); break;
          }
        }
      }
    }
  }
  else if (direction == 1)
  {
    // 1st Dimension
    for (loop = MS; loop >= 0; loop--)
    {
      switch (dim1)
      {
        case 0: matrix[row1][row2][row3][loop - 1] = matrix[row1][row2][row3][loop - 1] + (value & 0xFF); break;
        case 1: matrix[row1][row2][loop - 1][row3] = matrix[row1][row2][loop - 1][row3] + (value & 0xFF); break;
        case 2: matrix[row1][loop - 1][row2][row3] = matrix[row1][loop - 1][row2][row3] + (value & 0xFF); break;
        case 3: matrix[loop - 1][row1][row2][row3] = matrix[loop - 1][row1][row2][row3] + (value & 0xFF); break;
      }
    }
    // 2nd Dimension
    for (loop1 = MS; loop1 > 0; loop1--)
    {
      for (loop2 = MS; loop2 > 0; loop2--)
      {
        switch (dim2)
        {
          case 6:
          case 0: matrix[row1][row2][loop1 - 1][loop2 - 1] = matrix[row1][row2][loop1 - 1][loop2 - 1] + (value & 0xFF); break;
          case 1: matrix[row1][loop1 - 1][row2][loop2 - 1] = matrix[row1][loop1 - 1][row2][loop2 - 1] + (value & 0xFF); break;
          case 2: matrix[row1][loop1 - 1][loop2 - 1][row2] = matrix[row1][loop1 - 1][loop2 - 1][row2] + (value & 0xFF); break;
          case 3: matrix[loop1 - 1][row1][row2][loop2 - 1] = matrix[loop1 - 1][row1][row2][loop2 - 1] + (value & 0xFF); break;
          case 4: matrix[loop1 - 1][row1][loop2 - 1][row2] = matrix[loop1 - 1][row1][loop2 - 1][row2] + (value & 0xFF); break;
          case 7:
          case 5: matrix[loop1 - 1][loop2 - 1][row1][row2] = matrix[loop1 - 1][loop2 - 1][row1][row2] + (value & 0xFF); break;
        }
      }
    }
    // 3rd Dimension
    for (loop1 = MS; loop1 > 0; loop1--)
    {
      for (loop2 = MS; loop2 > 0; loop2--)
      {
        for (loop3 = MS; loop3 > 0; loop3--)
        {
          switch (dim3)
          {
            case 0: matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] = matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] + (value & 0xFF); break;
            case 1: matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] = matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] + (value & 0xFF); break;
            case 2: matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] = matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] + (value & 0xFF); break;
            case 3: matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] = matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] + (value & 0xFF); break;
          }
        }
      }
    }
  }
}
void decrement(char matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  int row1; int row2; int row3;
  int dimension; int direction; int value;
  row1 = (b1 >> 4) & B2;
  row2 = (b1 >> 2) & B2;
  row3 = (b1 >> 0) & B2;
  dimension = (b2 >> 6) & B2;
  direction = (b2 >> 5) & B1;
  value = b2 & B5;
  if (direction == 0)
  {
    int loop = 0;
    for (; loop < MS; loop++)
    {
      switch (dimension)
      {
        case 0: matrix[row1][row2][row3][loop] = matrix[row1][row2][row3][loop] - (value & 0xFF); break;
        case 1: matrix[row1][row2][loop][row3] = matrix[row1][row2][loop][row3] - (value & 0xFF); break;
        case 2: matrix[row1][loop][row2][row3] = matrix[row1][loop][row2][row3] - (value & 0xFF); break;
        case 3: matrix[loop][row1][row2][row3] = matrix[loop][row1][row2][row3] - (value & 0xFF); break;
      }
    }
  }
  else if (direction == 1)
  {
    int loop = MS;
    for (; loop >= 0; loop--)
    {
      switch (dimension)
      {
        case 0: matrix[row1][row2][row3][loop - 1] = matrix[row1][row2][row3][loop - 1] - (value & 0xFF); break;
        case 1: matrix[row1][row2][loop - 1][row3] = matrix[row1][row2][loop - 1][row3] - (value & 0xFF); break;
        case 2: matrix[row1][loop - 1][row2][row3] = matrix[row1][loop - 1][row2][row3] - (value & 0xFF); break;
        case 3: matrix[loop - 1][row1][row2][row3] = matrix[loop - 1][row1][row2][row3] - (value & 0xFF); break;
      }
    }
  }
}
void shift(char matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  /*int row1; int row2; int row3;
  int dimension; int direction; int value;
  row1 = (b1 >> 4) & 0xFF;
  row2 = (b1 >> 2) & 0xFF;
  row3 = (b1 >> 0) & 0xFF;
  dimension = (b2 >> 6) & 0xFF;
  direction = (b2 >> 5) & 0xFF;
  value = b2 & 0xFF;*/
}
void invert(char matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  /*int row1; int row2; int row3;
  int dimension; int direction; int value;
  row1 = (b1 >> 4) & 0xFF;
  row2 = (b1 >> 2) & 0xFF;
  row3 = (b1 >> 0) & 0xFF;
  dimension = (b2 >> 6) & 0xFF;
  direction = (b2 >> 5) & 0xFF;
  value = b2 & 0xFF;*/
}