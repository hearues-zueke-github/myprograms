// Author: Ziko Haris
// Date: 2014.10.16 (YYYYMMDD)
// Title: My Crypt Program, 3rd time XD, again

//// Short function overview of the (en/de)cryption of this program:
//// Command to start this program:
////     ./<program> <cryptmode> <cryptfile> <file1> <file2> ...
//// Function of the crypt algorithm:
//// 1.) At first the crypt file will be readed in a array with a max size of 4 MiB
//// 2.) Next in the output file will be written, how long the input file is 
//// 3.) Then it will read 256 bytes (4*4*4*4) from the input file in a 4-dimension-array-matrix
//// 3.1.) If the input file has not 256 bytes in it, then the rest of the matrix
////       will be filled with other numbers e.g. "0" or with random generated numbers
//// 4.) This matrix will be crypted with the crypt file, which was readed in an array
//// 5.) After the crypting, it will be printed out in an output file.
//// 6.) If the input file is bigger than 256 bytes, then it will repeat step 3 again,
////     until the crypting is done
//// The Matrix will be crypted by 4 Bytes
//// 1st Byte: e.g. 10110101
//                 b10 is the mode of the en/de crypting
//                   b11 is the number for the 1st row of the matrix
//                     b01 is the number for the 2nd row of the matrix
//                       b01 is the number for the 3rd row of the matrix
//// 2nd Byte: e.g. 10010101
//                 b1 is the direction of crypting (e.g. 0 is right and 1 is left)
//                  b00 is the number for the 1st dimension
//                    b101 is the number for the 2nd dimension
//                       b01 is the number for the 3rd dimension
//// 3rd Byte: e.g. 10010101
//                 b100
//                    b100
//                       b00
//// 4th Byte: e.g. 10010101

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define TRUE 1
#define FALSE 0
#define FILE_CRYPT_SIZE_MAX 4194304
#define PRINT_OUT_MODE 0
#define PRINT_MATRIX 1
#define B1 0x1
#define B2 0x3
#define B3 0x7
#define B4 0xF
#define B5 0x1F
#define B6 0x3F
#define B7 0x7F
#define B8 0xFF
// VERY IMPORTANT !!!! Matrix Size!
#define MS 4
#define MATRIX_LENGTH MS*MS*MS*MS

#define ERR_WRONG_USAGE 1
#define ERR_WRONG_CRYPT_MODUS 2
#define ERR_CRYPT_FILE_NOT_FOUND 3
#define ERR_CRYPT_FILE_TOO_BIG 4

#define ERRMSG_WRONG_USAGE "Wrong usage: <program> <crypt_modus> <file_crypt> <file_in>...\n"
#define ERRMSG_WRONG_CRYPT_MODUS "1st argument is false! Use:\ne for encrypt\nOR\nd for decrypt\n"
#define ERRMSG_CRYPT_FILE_NOT_FOUND "<file_crypt> not found!\n"
#define ERRMSG_CRYPT_FILE_TOO_BIG "Crypt File is too big! It should not be bigger than 4 MiB!\n"

typedef unsigned char uchar;

void waitForEnter();
void printArrayOneDimension(uchar *array, int array_length);
size_t fileSize(FILE *file);
int gcd(int n1, int n2);
void printMatrix(uchar matrix[MS][MS][MS][MS], int length);

void encryptionmodus(uchar matrix[MS][MS][MS][MS], uchar *crypt, long long crypt_size, int argc, char **argv);
void decryptionmodus(uchar matrix[MS][MS][MS][MS], uchar *crypt, long long crypt_size, int argc, char **argv);

void encryptionfunctions(uchar matrix[MS][MS][MS][MS], uchar *crypt, int crypt_size);
void decryptionfunctions(uchar matrix[MS][MS][MS][MS], uchar *crypt, int crypt_size);

void incrementencryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void decrementencryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void shiftencryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void invertencryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);

void incrementdecryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void decrementdecryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void shiftdecryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);
void invertdecryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4);

void (*functionsencryption[])(uchar [MS][MS][MS][MS], int, int, int, int) =
{&incrementencryption, &decrementencryption, &shiftencryption, &invertencryption};
void (*functionsdecryption[])(uchar [MS][MS][MS][MS], int, int, int, int) =
{&incrementdecryption, &decrementdecryption, &shiftdecryption, &invertdecryption};

int main (int argc, char **argv)
{
  int flag_cryptmodus;
  int flag_output_status = 1;
  uchar crypt[1024*1024*4];
  uchar matrix[MS][MS][MS][MS];
  long file_crypt_size;
  // Check for argument count
  if (argc < 4)
  {
    printf(ERRMSG_WRONG_USAGE);
    waitForEnter();
    return ERR_WRONG_USAGE;
  }
  // Check, if 2nd argument is e or d, for encrypt or decrypt
  if ((strlen(argv[1]) > 1) || ((argv[1][0] != 'e') && (argv[1][0] != 'd')))
  {
    printf(ERRMSG_WRONG_CRYPT_MODUS);
    waitForEnter();
    return ERR_WRONG_CRYPT_MODUS;
  }
  // Set flag_cryptmodus for encryption or decryption
  if (argv[1][0] == 'e')
  {
    flag_cryptmodus = 1;
  }
  else if (argv[1][0] == 'd')
  {
    flag_cryptmodus = 2;
  }
  // Do open the crypt File
  FILE *file_crypt = fopen(argv[2], "rb");
  // If the crypt File not exist, return Value "Crypt file not found!"
  if (file_crypt == NULL)
  {
    printf(ERRMSG_CRYPT_FILE_NOT_FOUND);
    waitForEnter();
    return ERR_CRYPT_FILE_NOT_FOUND;
  }
  file_crypt_size = fileSize(file_crypt);
  if (file_crypt_size > FILE_CRYPT_SIZE_MAX)
  {
    printf(ERRMSG_CRYPT_FILE_TOO_BIG);
    fclose(file_crypt);
    return ERR_CRYPT_FILE_TOO_BIG;
  }
  fread(crypt, file_crypt_size, sizeof(char), file_crypt);
  fclose(file_crypt);
  if (flag_output_status == TRUE)
  {
    printf("Crypt File OK!\n");
    printf("Modus: %d\n", flag_cryptmodus);
  }
  if (flag_cryptmodus == 1) // encryption
  {
    // DO the encryption of the files
    encryptionmodus(matrix, crypt, file_crypt_size, argc, argv);
  }
  else if (flag_cryptmodus == 2) // decryption
  {
    // DO the decryption of the files
    decryptionmodus(matrix, crypt, file_crypt_size, argc, argv);
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
void printArrayOneDimension(uchar *array, int array_length)
{
  int loop;
  printf("Print the array:\n");
  for (loop = 0; loop < array_length; loop++)
  {
    printf("array[%d] = %d\n", loop, array[loop]);
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
    while (n2 > 0)
    {
      number = n1 % n2;
      n1 = n2;
      n2 = number;
    }
  }
  return n1;
}
void printMatrix(uchar matrix[MS][MS][MS][MS], int length)
{
  int loop = 0;
  for (loop = 0; loop < 16; loop++)
  {
    if (loop != 0)
    {
      printf(" \033[31m%02x\033[49m", loop);
    }
    else
    {
      printf("%*s \033[31m%02x\033[49m", 6, " ", loop);
    }
  }
  printf("\n");
  for (loop = 0; loop < length; loop++)
  {
    if ((loop != 0) && (loop % 16 != 0))
    {
      if (loop % 16 != 15)
      {
        printf(" \033[39m%02x", matrix[(loop / (MS*MS*MS)) % MS][(loop / (MS*MS)) % MS][(loop / MS) % MS][loop % MS]);
      }
      else
      {
        printf(" \033[39m%02x\n", matrix[(loop / (MS*MS*MS)) % MS][(loop / (MS*MS)) % MS][(loop / MS) % MS][loop % MS]);
      }
    }
    else
    {
      printf("\033[32m0x%02x   \033[39m%02x", loop / 16, matrix[(loop / (MS*MS*MS)) % MS][(loop / (MS*MS)) % MS][(loop / MS) % MS][loop % MS]);
    }
  }
  printf("\n");
}

void encryptionmodus(uchar matrix[MS][MS][MS][MS], uchar *crypt, long long crypt_size, int argc, char **argv)
{
  long long file_in_size;
  long long file_in_position;
  int loop_file = 3;
  while (loop_file < argc) {
    FILE *file_in = fopen(argv[loop_file], "rb");
    system("[ -d encryption_files ] || mkdir encryption_files\n");
    char filenamedest[strlen(argv[loop_file]) + 19];
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
        if (PRINT_MATRIX)
        {
          printMatrix(matrix, MATRIX_LENGTH);
        }
        encryptionfunctions(matrix, crypt, crypt_size);
        if (PRINT_MATRIX)
        {
          printMatrix(matrix, MATRIX_LENGTH);
        }
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
void decryptionmodus(uchar matrix[MS][MS][MS][MS], uchar *crypt, long long crypt_size, int argc, char **argv)
{
  long long file_in_size;
  long long file_in_position;
  int loop_file = 3;
  while (loop_file < argc) {
    FILE *file_in = fopen(argv[loop_file], "rb");
    system("[ -d decryption_files ] || mkdir decryption_files\n");
    char filenamedest[strlen(argv[loop_file]) + 19];
    strcpy(filenamedest, "decryption_files/");
    strcat(filenamedest, argv[loop_file]);
    FILE *file_out = fopen(filenamedest, "wb");
    if (file_in != NULL) {
      file_in_size = fileSize(file_in);
      int file_size_number = 0;
      int shift;
      for (shift = 8; shift > 0; shift--)
      {
        file_size_number += (fgetc(file_in) & 0xFF) << (8 * (shift - 1));
      }
      file_in_position = file_in_size - 8;
      if (file_size_number <= file_in_position) {
        while (file_in_position > 0) {
          int pos = 0;
          // read in
          for(; (pos < (MS*MS*MS*MS)) && (file_in_position - pos) > 0; pos++) {
            matrix[(pos / (MS*MS*MS)) % MS][(pos / (MS*MS)) % MS][(pos / MS) % MS][pos % MS] = fgetc(file_in);
          }
          // decrypt algorithm
          if (PRINT_MATRIX)
          {
            printMatrix(matrix, MATRIX_LENGTH);
          }
          decryptionfunctions(matrix, crypt, crypt_size);
          if (PRINT_MATRIX)
          {
            printMatrix(matrix, MATRIX_LENGTH);
          }
          // write out
          file_in_position -= pos;
          if (pos > 0) {
            int loop = 0;
            while (loop < pos) {
              fputc(matrix[(loop / (MS*MS*MS)) % MS][(loop / (MS*MS)) % MS][(loop / MS) % MS][loop % MS], file_out);
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

void encryptionfunctions(uchar matrix[MS][MS][MS][MS], uchar *crypt, int crypt_size)
{
  if (PRINT_OUT_MODE == 1) {printf("Encryption Mode:\n");}
  int b1; int b2; int b3; int b4;
  int loop = 0;
  while (loop + 3 < crypt_size)
  {
    b1 = crypt[loop];
    b2 = crypt[loop + 1];
    b3 = crypt[loop + 2];
    b4 = crypt[loop + 3];
    //printf("%d  %d  %d  %d\n", loop, loop+1, loop+2, loop+3);
    //printf("%02x  %02x  %02x  %02x\n", b1&B8, b2&B8, b3&B8, b4&B8);
    //printf("%d\n", (b1 >> 6) & B2);
    switch ((b1 >> 6) & B2)
    {
      case 0: functionsencryption[0](matrix, b1, b2, b3, b4); break;
      case 1: functionsencryption[1](matrix, b1, b2, b3, b4); break;
      case 2: functionsencryption[2](matrix, b1, b2, b3, b4); break;
      case 3: functionsencryption[3](matrix, b1, b2, b3, b4); break;
    }
    loop += 4;
  }
  if (PRINT_OUT_MODE == 1) {printf("\n");}
}
void decryptionfunctions(uchar matrix[MS][MS][MS][MS], uchar *crypt, int crypt_size)
{
  if (PRINT_OUT_MODE == 1) {printf("Decryption Mode:\n");}
  int b1; int b2; int b3; int b4;
  int loop = 0;
  loop = (crypt_size / 4) * 4 - 3;
  while (loop > 0)
  {
    b1 = crypt[(loop - 1)];
    b2 = crypt[(loop - 1) + 1];
    b3 = crypt[(loop - 1) + 2];
    b4 = crypt[(loop - 1) + 3];
    //printf("%d  %d  %d  %d\n", (loop-1), (loop-1)+1, (loop-1)+2, (loop-1)+3);
    //printf("%02x  %02x  %02x  %02x\n", b1&B8, b2&B8, b3&B8, b4&B8);
    //printf("%d\n", (b1 >> 6) & B2);
    switch ((b1 >> 6) & B2)
    {
      case 0: functionsdecryption[1](matrix, b1, b2, b3, b4); break;
      case 1: functionsdecryption[0](matrix, b1, b2, b3, b4); break;
      case 2: functionsdecryption[2](matrix, b1, b2, b3, b4); break;
      case 3: functionsdecryption[3](matrix, b1, b2, b3, b4); break;
    }
    loop -= 4;
  }
  if (PRINT_OUT_MODE == 1) {printf("\n");}
}

void incrementencryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  if (PRINT_OUT_MODE == 1) {printf("IE ");}
  uchar row1,  row2, row3;
  uchar direction, dim1, dim2, dim3;
  uchar jumper, shifter, multiplier;
  uchar value, value_temp, value_temp2;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  uchar loop1, loop2, loop3, loopm;
  value_temp = 0;
  for (loopm = 0; loopm < multiplier; loopm++)
  {
    value_temp = (value + (value_temp >> shifter) + (value_temp << shifter)) & B8;
    if (direction == 0)
    {
      // 1st Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        value_temp2 = (value_temp + loop1 * jumper + loopm) & B8;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1] = matrix[row1][row2][row3][loop1] + value_temp2; break;
          case 1: matrix[row1][row2][loop1][row3] = matrix[row1][row2][loop1][row3] + value_temp2; break;
          case 2: matrix[row1][loop1][row2][row3] = matrix[row1][loop1][row2][row3] + value_temp2; break;
          case 3: matrix[loop1][row1][row2][row3] = matrix[loop1][row1][row2][row3] + value_temp2; break;
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          value_temp2 = (value_temp + (loop1 + loop2) * jumper + loopm) & B8;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][loop2] = matrix[row1][row2][loop1][loop2] + value_temp2; break;
            case 1: matrix[row1][loop1][row2][loop2] = matrix[row1][loop1][row2][loop2] + value_temp2; break;
            case 2: matrix[row1][loop1][loop2][row2] = matrix[row1][loop1][loop2][row2] + value_temp2; break;
            case 3: matrix[loop1][row1][row2][loop2] = matrix[loop1][row1][row2][loop2] + value_temp2; break;
            case 4: matrix[loop1][row1][loop2][row2] = matrix[loop1][row1][loop2][row2] + value_temp2; break;
            case 7:
            case 5: matrix[loop1][loop2][row1][row2] = matrix[loop1][loop2][row1][row2] + value_temp2; break;
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
            value_temp2 = (value_temp + (loop1 + loop2 + loop3) * jumper + loopm) & B8;
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][loop3] = matrix[row1][loop1][loop2][loop3] + value_temp2; break;
              case 1: matrix[loop1][row1][loop2][loop3] = matrix[loop1][row1][loop2][loop3] + value_temp2; break;
              case 2: matrix[loop1][loop2][row1][loop3] = matrix[loop1][loop2][row1][loop3] + value_temp2; break;
              case 3: matrix[loop1][loop2][loop3][row1] = matrix[loop1][loop2][loop3][row1] + value_temp2; break;
            }
          }
        }
      }
    } // end if
    else if (direction == 1)
    {
      // 1st Dimension
      for (loop1 = MS; loop1 > 0; loop1--)
      {
        value_temp2 = (value_temp + (loop1 - 1) * jumper + loopm) & B8;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1 - 1] = matrix[row1][row2][row3][loop1 - 1] + value_temp2; break;
          case 1: matrix[row1][row2][loop1 - 1][row3] = matrix[row1][row2][loop1 - 1][row3] + value_temp2; break;
          case 2: matrix[row1][loop1 - 1][row2][row3] = matrix[row1][loop1 - 1][row2][row3] + value_temp2; break;
          case 3: matrix[loop1 - 1][row1][row2][row3] = matrix[loop1 - 1][row1][row2][row3] + value_temp2; break;
        }
      }
      // 2nd Dimension
      for (loop1 = MS; loop1 > 0; loop1--)
      {
        for (loop2 = MS; loop2 > 0; loop2--)
        {
          value_temp2 = (value_temp + (loop1 - 1 + loop2 - 1) * jumper + loopm) & B8;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1 - 1][loop2 - 1] = matrix[row1][row2][loop1 - 1][loop2 - 1] + value_temp2; break;
            case 1: matrix[row1][loop1 - 1][row2][loop2 - 1] = matrix[row1][loop1 - 1][row2][loop2 - 1] + value_temp2; break;
            case 2: matrix[row1][loop1 - 1][loop2 - 1][row2] = matrix[row1][loop1 - 1][loop2 - 1][row2] + value_temp2; break;
            case 3: matrix[loop1 - 1][row1][row2][loop2 - 1] = matrix[loop1 - 1][row1][row2][loop2 - 1] + value_temp2; break;
            case 4: matrix[loop1 - 1][row1][loop2 - 1][row2] = matrix[loop1 - 1][row1][loop2 - 1][row2] + value_temp2; break;
            case 7:
            case 5: matrix[loop1 - 1][loop2 - 1][row1][row2] = matrix[loop1 - 1][loop2 - 1][row1][row2] + value_temp2; break;
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
            value_temp2 = (value_temp + (loop1 - 1 + loop2 - 1 + loop3 - 1) * jumper + loopm) & B8;
            switch (dim3)
            {
              case 0: matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] = matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] + value_temp2; break;
              case 1: matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] = matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] + value_temp2; break;
              case 2: matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] = matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] + value_temp2; break;
              case 3: matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] = matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] + value_temp2; break;
            }
          }
        }
      }
    } // end else if
  } // end for
}
void decrementencryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  if (PRINT_OUT_MODE == 1) {printf("DE ");}
  uchar row1,  row2, row3;
  uchar direction, dim1, dim2, dim3;
  uchar jumper, shifter, multiplier;
  uchar value, value_temp, value_temp2;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  uchar loop1, loop2, loop3, loopm;
  value_temp = 0;
  for (loopm = 0; loopm < multiplier; loopm++)
  {
    value_temp = (value + (value_temp >> shifter) + (value_temp << shifter)) & B8;
    if (direction == 0)
    {
      // 1st Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        value_temp2 = (value_temp + loop1 * jumper + loopm) & B8;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1] = matrix[row1][row2][row3][loop1] - value_temp2; break;
          case 1: matrix[row1][row2][loop1][row3] = matrix[row1][row2][loop1][row3] - value_temp2; break;
          case 2: matrix[row1][loop1][row2][row3] = matrix[row1][loop1][row2][row3] - value_temp2; break;
          case 3: matrix[loop1][row1][row2][row3] = matrix[loop1][row1][row2][row3] - value_temp2; break;
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          value_temp2 = (value_temp + (loop1 + loop2) * jumper + loopm) & B8;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][loop2] = matrix[row1][row2][loop1][loop2] - value_temp2; break;
            case 1: matrix[row1][loop1][row2][loop2] = matrix[row1][loop1][row2][loop2] - value_temp2; break;
            case 2: matrix[row1][loop1][loop2][row2] = matrix[row1][loop1][loop2][row2] - value_temp2; break;
            case 3: matrix[loop1][row1][row2][loop2] = matrix[loop1][row1][row2][loop2] - value_temp2; break;
            case 4: matrix[loop1][row1][loop2][row2] = matrix[loop1][row1][loop2][row2] - value_temp2; break;
            case 7:
            case 5: matrix[loop1][loop2][row1][row2] = matrix[loop1][loop2][row1][row2] - value_temp2; break;
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
            value_temp2 = (value_temp + (loop1 + loop2 + loop3) * jumper + loopm) & B8;
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][loop3] = matrix[row1][loop1][loop2][loop3] - value_temp2; break;
              case 1: matrix[loop1][row1][loop2][loop3] = matrix[loop1][row1][loop2][loop3] - value_temp2; break;
              case 2: matrix[loop1][loop2][row1][loop3] = matrix[loop1][loop2][row1][loop3] - value_temp2; break;
              case 3: matrix[loop1][loop2][loop3][row1] = matrix[loop1][loop2][loop3][row1] - value_temp2; break;
            }
          }
        }
      }
    } // end if
    else if (direction == 1)
    {
      // 1st Dimension
      for (loop1 = MS; loop1 > 0; loop1--)
      {
        value_temp2 = (value_temp + (loop1 - 1) * jumper + loopm) & B8;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1 - 1] = matrix[row1][row2][row3][loop1 - 1] - value_temp2; break;
          case 1: matrix[row1][row2][loop1 - 1][row3] = matrix[row1][row2][loop1 - 1][row3] - value_temp2; break;
          case 2: matrix[row1][loop1 - 1][row2][row3] = matrix[row1][loop1 - 1][row2][row3] - value_temp2; break;
          case 3: matrix[loop1 - 1][row1][row2][row3] = matrix[loop1 - 1][row1][row2][row3] - value_temp2; break;
        }
      }
      // 2nd Dimension
      for (loop1 = MS; loop1 > 0; loop1--)
      {
        for (loop2 = MS; loop2 > 0; loop2--)
        {
          value_temp2 = (value_temp + (loop1 - 1 + loop2 - 1) * jumper + loopm) & B8;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1 - 1][loop2 - 1] = matrix[row1][row2][loop1 - 1][loop2 - 1] - value_temp2; break;
            case 1: matrix[row1][loop1 - 1][row2][loop2 - 1] = matrix[row1][loop1 - 1][row2][loop2 - 1] - value_temp2; break;
            case 2: matrix[row1][loop1 - 1][loop2 - 1][row2] = matrix[row1][loop1 - 1][loop2 - 1][row2] - value_temp2; break;
            case 3: matrix[loop1 - 1][row1][row2][loop2 - 1] = matrix[loop1 - 1][row1][row2][loop2 - 1] - value_temp2; break;
            case 4: matrix[loop1 - 1][row1][loop2 - 1][row2] = matrix[loop1 - 1][row1][loop2 - 1][row2] - value_temp2; break;
            case 7:
            case 5: matrix[loop1 - 1][loop2 - 1][row1][row2] = matrix[loop1 - 1][loop2 - 1][row1][row2] - value_temp2; break;
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
            value_temp2 = (value_temp + (loop1 - 1 + loop2 - 1 + loop3 - 1) * jumper + loopm) & B8;
            switch (dim3)
            {
              case 0: matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] = matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] - value_temp2; break;
              case 1: matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] = matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] - value_temp2; break;
              case 2: matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] = matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] - value_temp2; break;
              case 3: matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] = matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] - value_temp2; break;
            }
          }
        }
      }
    } // end else if
  } // end for
}
void shiftencryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  if (PRINT_OUT_MODE == 1) {printf("SE ");}
  uchar row1,  row2, row3;
  uchar direction, dim1, dim2, dim3;
  uchar jumper, shifter, multiplier;
  uchar value, value_temp, value_temp2, value_temp3, value_gcd;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  uchar loop1, loop2, loop3, loopm, loop_s;
  value = jumper;jumper=value;
  if (shifter % 3 == 0) {shifter = 3;}
  else {shifter = shifter % 3;}
  value_gcd = gcd(MS, shifter);
  multiplier = multiplier % 4;
  for (loopm = 0; loopm < multiplier; loopm++)
  {
    if (direction == 0)
    {
      // 1st Dimension
      for (loop1 = 0; loop1 < value_gcd; loop1++)
      {
        switch (dim1)
        {
          case 0: value_temp = matrix[row1][row2][row3][loop1]; break;
          case 1: value_temp = matrix[row1][row2][loop1][row3]; break;
          case 2: value_temp = matrix[row1][loop1][row2][row3]; break;
          case 3: value_temp = matrix[loop1][row1][row2][row3]; break;
        }
        for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
        {
          value_temp2 = (uchar)(loop1 + loop_s * shifter) % MS;
          value_temp3 = (uchar)(loop1 + (loop_s + 1) * shifter) % MS;
          switch (dim1)
          {
            case 0: matrix[row1][row2][row3][value_temp2] = matrix[row1][row2][row3][value_temp3]; break;
            case 1: matrix[row1][row2][value_temp2][row3] = matrix[row1][row2][value_temp3][row3]; break;
            case 2: matrix[row1][value_temp2][row2][row3] = matrix[row1][value_temp3][row2][row3]; break;
            case 3: matrix[value_temp2][row1][row2][row3] = matrix[value_temp3][row1][row2][row3]; break;
          }
        }
        value_temp2 = (uchar)(loop1 - shifter) % MS;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][value_temp2] = value_temp; break;
          case 1: matrix[row1][row2][value_temp2][row3] = value_temp; break;
          case 2: matrix[row1][value_temp2][row2][row3] = value_temp; break;
          case 3: matrix[value_temp2][row1][row2][row3] = value_temp; break;
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < value_gcd; loop2++)
        {
          switch (dim2)
          {
            case 6:
            case 0: value_temp = matrix[row1][row2][loop1][loop2]; break;
            case 1: value_temp = matrix[row1][loop1][row2][loop2]; break;
            case 2: value_temp = matrix[row1][loop1][loop2][row2]; break;
            case 3: value_temp = matrix[loop1][row1][row2][loop2]; break;
            case 4: value_temp = matrix[loop1][row1][loop2][row2]; break;
            case 7:
            case 5: value_temp = matrix[loop1][loop2][row1][row2]; break;
          }
          for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
          {
            value_temp2 = (uchar)(loop2 + loop_s * shifter) % MS;
            value_temp3 = (uchar)(loop2 + (loop_s + 1) * shifter) % MS;
            switch (dim2)
            {
              case 6:
              case 0: matrix[row1][row2][loop1][value_temp2] = matrix[row1][row2][loop1][value_temp3]; break;
              case 1: matrix[row1][loop1][row2][value_temp2] = matrix[row1][loop1][row2][value_temp3]; break;
              case 2: matrix[row1][loop1][value_temp2][row2] = matrix[row1][loop1][value_temp3][row2]; break;
              case 3: matrix[loop1][row1][row2][value_temp2] = matrix[loop1][row1][row2][value_temp3]; break;
              case 4: matrix[loop1][row1][value_temp2][row2] = matrix[loop1][row1][value_temp3][row2]; break;
              case 7:
              case 5: matrix[loop1][value_temp2][row1][row2] = matrix[loop1][value_temp3][row1][row2]; break;
            }
          }
          value_temp2 = (uchar)(loop2 - shifter) % MS;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][value_temp2] = value_temp; break;
            case 1: matrix[row1][loop1][row2][value_temp2] = value_temp; break;
            case 2: matrix[row1][loop1][value_temp2][row2] = value_temp; break;
            case 3: matrix[loop1][row1][row2][value_temp2] = value_temp; break;
            case 4: matrix[loop1][row1][value_temp2][row2] = value_temp; break;
            case 7:
            case 5: matrix[loop1][value_temp2][row1][row2] = value_temp; break;
          }
        }
      }
      // 3rd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop3 = 0; loop3 < value_gcd; loop3++)
          {
            switch (dim3)
            {
              case 0: value_temp = matrix[row1][loop1][loop2][loop3]; break;
              case 1: value_temp = matrix[loop1][row1][loop2][loop3]; break;
              case 2: value_temp = matrix[loop1][loop2][row1][loop3]; break;
              case 3: value_temp = matrix[loop1][loop2][loop3][row1]; break;
            }
            for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
            {
              value_temp2 = (uchar)(loop3 + loop_s * shifter) % MS;
              value_temp3 = (uchar)(loop3 + (loop_s + 1) * shifter) % MS;
              switch (dim3)
              {                
                case 0: matrix[row1][loop1][loop2][value_temp2] = matrix[row1][loop1][loop2][value_temp3]; break;
                case 1: matrix[loop1][row1][loop2][value_temp2] = matrix[loop1][row1][loop2][value_temp3]; break;
                case 2: matrix[loop1][loop2][row1][value_temp2] = matrix[loop1][loop2][row1][value_temp3]; break;
                case 3: matrix[loop1][loop2][value_temp2][row1] = matrix[loop1][loop2][value_temp3][row1]; break;
              }
            }
            value_temp2 = (uchar)(loop3 - shifter) % MS;
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][value_temp2] = value_temp; break;
              case 1: matrix[loop1][row1][loop2][value_temp2] = value_temp; break;
              case 2: matrix[loop1][loop2][row1][value_temp2] = value_temp; break;
              case 3: matrix[loop1][loop2][value_temp2][row1] = value_temp; break;
            }
          }
        }
      }
    } // end if
    else if (direction == 1)
    {
      // 3rd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop3 = 0; loop3 < value_gcd; loop3++)
          {
            switch (dim3)
            {
              case 0: value_temp = matrix[row1][loop1][loop2][loop3]; break;
              case 1: value_temp = matrix[loop1][row1][loop2][loop3]; break;
              case 2: value_temp = matrix[loop1][loop2][row1][loop3]; break;
              case 3: value_temp = matrix[loop1][loop2][loop3][row1]; break;
            }
            for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
            {
              value_temp2 = (uchar)(loop3 + loop_s * shifter) % MS;
              value_temp3 = (uchar)(loop3 + (loop_s + 1) * shifter) % MS;
              switch (dim3)
              {                
                case 0: matrix[row1][loop1][loop2][value_temp2] = matrix[row1][loop1][loop2][value_temp3]; break;
                case 1: matrix[loop1][row1][loop2][value_temp2] = matrix[loop1][row1][loop2][value_temp3]; break;
                case 2: matrix[loop1][loop2][row1][value_temp2] = matrix[loop1][loop2][row1][value_temp3]; break;
                case 3: matrix[loop1][loop2][value_temp2][row1] = matrix[loop1][loop2][value_temp3][row1]; break;
              }
            }
            value_temp2 = (uchar)(loop3 - shifter) % MS;
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][value_temp2] = value_temp; break;
              case 1: matrix[loop1][row1][loop2][value_temp2] = value_temp; break;
              case 2: matrix[loop1][loop2][row1][value_temp2] = value_temp; break;
              case 3: matrix[loop1][loop2][value_temp2][row1] = value_temp; break;
            }
          }
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < value_gcd; loop2++)
        {
          switch (dim2)
          {
            case 6:
            case 0: value_temp = matrix[row1][row2][loop1][loop2]; break;
            case 1: value_temp = matrix[row1][loop1][row2][loop2]; break;
            case 2: value_temp = matrix[row1][loop1][loop2][row2]; break;
            case 3: value_temp = matrix[loop1][row1][row2][loop2]; break;
            case 4: value_temp = matrix[loop1][row1][loop2][row2]; break;
            case 7:
            case 5: value_temp = matrix[loop1][loop2][row1][row2]; break;
          }
          for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
          {
            value_temp2 = (uchar)(loop2 + loop_s * shifter) % MS;
            value_temp3 = (uchar)(loop2 + (loop_s + 1) * shifter) % MS;
            switch (dim2)
            {
              case 6:
              case 0: matrix[row1][row2][loop1][value_temp2] = matrix[row1][row2][loop1][value_temp3]; break;
              case 1: matrix[row1][loop1][row2][value_temp2] = matrix[row1][loop1][row2][value_temp3]; break;
              case 2: matrix[row1][loop1][value_temp2][row2] = matrix[row1][loop1][value_temp3][row2]; break;
              case 3: matrix[loop1][row1][row2][value_temp2] = matrix[loop1][row1][row2][value_temp3]; break;
              case 4: matrix[loop1][row1][value_temp2][row2] = matrix[loop1][row1][value_temp3][row2]; break;
              case 7:
              case 5: matrix[loop1][value_temp2][row1][row2] = matrix[loop1][value_temp3][row1][row2]; break;
            }
          }
          value_temp2 = (uchar)(loop2 - shifter) % MS;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][value_temp2] = value_temp; break;
            case 1: matrix[row1][loop1][row2][value_temp2] = value_temp; break;
            case 2: matrix[row1][loop1][value_temp2][row2] = value_temp; break;
            case 3: matrix[loop1][row1][row2][value_temp2] = value_temp; break;
            case 4: matrix[loop1][row1][value_temp2][row2] = value_temp; break;
            case 7:
            case 5: matrix[loop1][value_temp2][row1][row2] = value_temp; break;
          }
        }
      }
      // 1st Dimension
      for (loop1 = 0; loop1 < value_gcd; loop1++)
      {
        switch (dim1)
        {
          case 0: value_temp = matrix[row1][row2][row3][loop1]; break;
          case 1: value_temp = matrix[row1][row2][loop1][row3]; break;
          case 2: value_temp = matrix[row1][loop1][row2][row3]; break;
          case 3: value_temp = matrix[loop1][row1][row2][row3]; break;
        }
        for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
        {
          value_temp2 = (uchar)(loop1 + loop_s * shifter) % MS;
          value_temp3 = (uchar)(loop1 + (loop_s + 1) * shifter) % MS;
          switch (dim1)
          {
            case 0: matrix[row1][row2][row3][value_temp2] = matrix[row1][row2][row3][value_temp3]; break;
            case 1: matrix[row1][row2][value_temp2][row3] = matrix[row1][row2][value_temp3][row3]; break;
            case 2: matrix[row1][value_temp2][row2][row3] = matrix[row1][value_temp3][row2][row3]; break;
            case 3: matrix[value_temp2][row1][row2][row3] = matrix[value_temp3][row1][row2][row3]; break;
          }
        }
        value_temp2 = (uchar)(loop1 - shifter) % MS;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][value_temp2] = value_temp; break;
          case 1: matrix[row1][row2][value_temp2][row3] = value_temp; break;
          case 2: matrix[row1][value_temp2][row2][row3] = value_temp; break;
          case 3: matrix[value_temp2][row1][row2][row3] = value_temp; break;
        }
      }
    } // end else if
  } // end for
}
void invertencryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  if (PRINT_OUT_MODE == 1) {printf("VE ");}
  uchar row1, row2, row3;
  uchar direction, dim1, dim2, dim3;
  uchar jumper, shifter, multiplier;
  uchar value, value_temp;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  value = jumper; jumper = shifter; shifter = value;
  uchar loop1, loop2, loop3, loopm;
  multiplier = 1;
  for (loopm = 0; loopm < multiplier; loopm++)
  {
    if (direction == 0)
    {
      // 1st Dimension
      for (loop1 = 0; loop1 < MS / 2; loop1++)
      {
        switch (dim1)
        {
          case 0: value_temp = matrix[row1][row2][row3][loop1]; break;
          case 1: value_temp = matrix[row1][row2][loop1][row3]; break;
          case 2: value_temp = matrix[row1][loop1][row2][row3]; break;
          case 3: value_temp = matrix[loop1][row1][row2][row3]; break;
        }
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1] = 0xFF - matrix[row1][row2][row3][MS - 1 - loop1]; break;
          case 1: matrix[row1][row2][loop1][row3] = 0xFF - matrix[row1][row2][MS - 1 - loop1][row3]; break;
          case 2: matrix[row1][loop1][row2][row3] = 0xFF - matrix[row1][MS - 1 - loop1][row2][row3]; break;
          case 3: matrix[loop1][row1][row2][row3] = 0xFF - matrix[MS - 1 - loop1][row1][row2][row3]; break;
        }
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][MS - 1 - loop1] = value_temp; break;
          case 1: matrix[row1][row2][MS - 1 - loop1][row3] = value_temp; break;
          case 2: matrix[row1][MS - 1 - loop1][row2][row3] = value_temp; break;
          case 3: matrix[MS - 1 - loop1][row1][row2][row3] = value_temp; break;
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS / 2; loop2++)
        {
          switch (dim2)
          {
            case 6:
            case 0: value_temp = matrix[row1][row2][loop1][loop2]; break;
            case 1: value_temp = matrix[row1][loop1][row2][loop2]; break;
            case 2: value_temp = matrix[row1][loop1][loop2][row2]; break;
            case 3: value_temp = matrix[loop1][row1][row2][loop2]; break;
            case 4: value_temp = matrix[loop1][row1][loop2][row2]; break;
            case 7:
            case 5: value_temp = matrix[loop1][loop2][row1][row2]; break;
          }
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][loop2] = 0xFF - matrix[row1][row2][loop1][MS - 1 - loop2]; break;
            case 1: matrix[row1][loop1][row2][loop2] = 0xFF - matrix[row1][loop1][row2][MS - 1 - loop2]; break;
            case 2: matrix[row1][loop1][loop2][row2] = 0xFF - matrix[row1][loop1][MS - 1 - loop2][row2]; break;
            case 3: matrix[loop1][row1][row2][loop2] = 0xFF - matrix[loop1][row1][row2][MS - 1 - loop2]; break;
            case 4: matrix[loop1][row1][loop2][row2] = 0xFF - matrix[loop1][row1][MS - 1 - loop2][row2]; break;
            case 7:
            case 5: matrix[loop1][loop2][row1][row2] = 0xFF - matrix[loop1][MS - 1 - loop2][row1][row2]; break;
          }
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][MS - 1 - loop2] = value_temp; break;
            case 1: matrix[row1][loop1][row2][MS - 1 - loop2] = value_temp; break;
            case 2: matrix[row1][loop1][MS - 1 - loop2][row2] = value_temp; break;
            case 3: matrix[loop1][row1][row2][MS - 1 - loop2] = value_temp; break;
            case 4: matrix[loop1][row1][MS - 1 - loop2][row2] = value_temp; break;
            case 7:
            case 5: matrix[loop1][MS - 1 - loop2][row1][row2] = value_temp; break;
          }
        }
      }
      // 3rd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop3 = 0; loop3 < MS /2; loop3++)
          {
            switch (dim3)
            {
              case 0: value_temp = matrix[row1][loop1][loop2][loop3]; break;
              case 1: value_temp = matrix[loop1][row1][loop2][loop3]; break;
              case 2: value_temp = matrix[loop1][loop2][row1][loop3]; break;
              case 3: value_temp = matrix[loop1][loop2][loop3][row1]; break;
            }
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][loop3] = 0xFF - matrix[row1][loop1][loop2][MS - 1 - loop3]; break;
              case 1: matrix[loop1][row1][loop2][loop3] = 0xFF - matrix[loop1][row1][loop2][MS - 1 - loop3]; break;
              case 2: matrix[loop1][loop2][row1][loop3] = 0xFF - matrix[loop1][loop2][row1][MS - 1 - loop3]; break;
              case 3: matrix[loop1][loop2][loop3][row1] = 0xFF - matrix[loop1][loop2][MS - 1 - loop3][row1]; break;
            }
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][MS - 1 - loop3] = value_temp; break;
              case 1: matrix[loop1][row1][loop2][MS - 1 - loop3] = value_temp; break;
              case 2: matrix[loop1][loop2][row1][MS - 1 - loop3] = value_temp; break;
              case 3: matrix[loop1][loop2][MS - 1 - loop3][row1] = value_temp; break;
            }
          }
        }
      }
    } // end if
    else if (direction == 1)
    {
      // 1st Dimension
      for (loop1 = MS; loop1 > MS / 2; loop1--)
      {
        switch (dim1)
        {
          case 0: value_temp = matrix[row1][row2][row3][loop1 - 1]; break;
          case 1: value_temp = matrix[row1][row2][loop1 - 1][row3]; break;
          case 2: value_temp = matrix[row1][loop1 - 1][row2][row3]; break;
          case 3: value_temp = matrix[loop1 - 1][row1][row2][row3]; break;
        }
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1 - 1] = 0xFF - matrix[row1][row2][row3][MS - loop1]; break;
          case 1: matrix[row1][row2][loop1 - 1][row3] = 0xFF - matrix[row1][row2][MS - loop1][row3]; break;
          case 2: matrix[row1][loop1 - 1][row2][row3] = 0xFF - matrix[row1][MS - loop1][row2][row3]; break;
          case 3: matrix[loop1 - 1][row1][row2][row3] = 0xFF - matrix[MS - loop1][row1][row2][row3]; break;
        }
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][MS - loop1] = value_temp; break;
          case 1: matrix[row1][row2][MS - loop1][row3] = value_temp; break;
          case 2: matrix[row1][MS - loop1][row2][row3] = value_temp; break;
          case 3: matrix[MS - loop1][row1][row2][row3] = value_temp; break;
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = MS; loop2 > MS / 2; loop2--)
        {
          switch (dim2)
          {
            case 6:
            case 0: value_temp = matrix[row1][row2][loop1][loop2 - 1]; break;
            case 1: value_temp = matrix[row1][loop1][row2][loop2 - 1]; break;
            case 2: value_temp = matrix[row1][loop1][loop2 - 1][row2]; break;
            case 3: value_temp = matrix[loop1][row1][row2][loop2 - 1]; break;
            case 4: value_temp = matrix[loop1][row1][loop2 - 1][row2]; break;
            case 7:
            case 5: value_temp = matrix[loop1][loop2 - 1][row1][row2]; break;
          }
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][loop2 - 1] = 0xFF - matrix[row1][row2][loop1][MS - loop2]; break;
            case 1: matrix[row1][loop1][row2][loop2 - 1] = 0xFF - matrix[row1][loop1][row2][MS - loop2]; break;
            case 2: matrix[row1][loop1][loop2 - 1][row2] = 0xFF - matrix[row1][loop1][MS - loop2][row2]; break;
            case 3: matrix[loop1][row1][row2][loop2 - 1] = 0xFF - matrix[loop1][row1][row2][MS - loop2]; break;
            case 4: matrix[loop1][row1][loop2 - 1][row2] = 0xFF - matrix[loop1][row1][MS - loop2][row2]; break;
            case 7:
            case 5: matrix[loop1][loop2 - 1][row1][row2] = 0xFF - matrix[loop1][MS - loop2][row1][row2]; break;
          }
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][MS - loop2] = value_temp; break;
            case 1: matrix[row1][loop1][row2][MS - loop2] = value_temp; break;
            case 2: matrix[row1][loop1][MS - loop2][row2] = value_temp; break;
            case 3: matrix[loop1][row1][row2][MS - loop2] = value_temp; break;
            case 4: matrix[loop1][row1][MS - loop2][row2] = value_temp; break;
            case 7:
            case 5: matrix[loop1][MS - loop2][row1][row2] = value_temp; break;
          }
        }
      }
      // 3rd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop3 = MS; loop3 > MS / 2; loop3--)
          {
            switch (dim3)
            {
              case 0: value_temp = matrix[row1][loop1][loop2][loop3 - 1]; break;
              case 1: value_temp = matrix[loop1][row1][loop2][loop3 - 1]; break;
              case 2: value_temp = matrix[loop1][loop2][row1][loop3 - 1]; break;
              case 3: value_temp = matrix[loop1][loop2][loop3 - 1][row1]; break;
            }
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][loop3 - 1] = 0xFF - matrix[row1][loop1][loop2][MS - loop3]; break;
              case 1: matrix[loop1][row1][loop2][loop3 - 1] = 0xFF - matrix[loop1][row1][loop2][MS - loop3]; break;
              case 2: matrix[loop1][loop2][row1][loop3 - 1] = 0xFF - matrix[loop1][loop2][row1][MS - loop3]; break;
              case 3: matrix[loop1][loop2][loop3 - 1][row1] = 0xFF - matrix[loop1][loop2][MS - loop3][row1]; break;
            }
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][MS - loop3] = value_temp; break;
              case 1: matrix[loop1][row1][loop2][MS - loop3] = value_temp; break;
              case 2: matrix[loop1][loop2][row1][MS - loop3] = value_temp; break;
              case 3: matrix[loop1][loop2][MS - loop3][row1] = value_temp; break;
            }
          }
        }
      }
    } // end else if
  } // end for
}

void incrementdecryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  if (PRINT_OUT_MODE == 1) {printf("ID ");}
  uchar row1,  row2, row3;
  uchar direction, dim1, dim2, dim3;
  uchar jumper, shifter, multiplier;
  uchar value, value_temp, value_temp2;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  uchar loop1,loop2, loop3, loopm;
  uchar value_temp_array[multiplier];
  for (loopm = 0; loopm < multiplier; loopm++)
  {
    if (loopm != 0)
    {
      value_temp_array[loopm] = value + (value_temp_array[loopm - 1] >> shifter) + (value_temp_array[loopm - 1] << shifter);
    }
    else
    {
      value_temp_array[loopm] = value + (0 >> shifter) + (0 << shifter);
    }
  }
  for (loopm = multiplier; loopm > 0; loopm--)
  {
    value_temp = value_temp_array[loopm - 1];
    if (direction == 0)
    {
      // 3rd Dimension
      for (loop3 = MS; loop3 > 0; loop3--)
      {
        for (loop2 = MS; loop2 > 0; loop2--)
        {
          for (loop1 = MS; loop1 > 0; loop1--)
          {
            value_temp2 = (value_temp + (loop1 - 1 + loop2 - 1 + loop3 - 1) * jumper + loopm - 1) & B8;
            switch (dim3)
            {
              case 0: matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] = matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] + value_temp2; break;
              case 1: matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] = matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] + value_temp2; break;
              case 2: matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] = matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] + value_temp2; break;
              case 3: matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] = matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] + value_temp2; break;
            }
          }
        }
      }
      // 2nd Dimension
      for (loop2 = MS; loop2 > 0; loop2--)
      {
        for (loop1 = MS; loop1 > 0; loop1--)
        {
          value_temp2 = (value_temp + (loop1 - 1 + loop2 - 1) * jumper + loopm - 1) & B8;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1 - 1][loop2 - 1] = matrix[row1][row2][loop1 - 1][loop2 - 1] + value_temp2; break;
            case 1: matrix[row1][loop1 - 1][row2][loop2 - 1] = matrix[row1][loop1 - 1][row2][loop2 - 1] + value_temp2; break;
            case 2: matrix[row1][loop1 - 1][loop2 - 1][row2] = matrix[row1][loop1 - 1][loop2 - 1][row2] + value_temp2; break;
            case 3: matrix[loop1 - 1][row1][row2][loop2 - 1] = matrix[loop1 - 1][row1][row2][loop2 - 1] + value_temp2; break;
            case 4: matrix[loop1 - 1][row1][loop2 - 1][row2] = matrix[loop1 - 1][row1][loop2 - 1][row2] + value_temp2; break;
            case 7:
            case 5: matrix[loop1 - 1][loop2 - 1][row1][row2] = matrix[loop1 - 1][loop2 - 1][row1][row2] + value_temp2; break;
          }
        }
      }
      // 1st Dimension
      for (loop1 = MS; loop1 > 0; loop1--)
      {
        value_temp2 = (value_temp + (loop1 - 1) * jumper + loopm - 1) & B8;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1 - 1] = matrix[row1][row2][row3][loop1 - 1] + value_temp2; break;
          case 1: matrix[row1][row2][loop1 - 1][row3] = matrix[row1][row2][loop1 - 1][row3] + value_temp2; break;
          case 2: matrix[row1][loop1 - 1][row2][row3] = matrix[row1][loop1 - 1][row2][row3] + value_temp2; break;
          case 3: matrix[loop1 - 1][row1][row2][row3] = matrix[loop1 - 1][row1][row2][row3] + value_temp2; break;
        }
      }
    } // end if
    else if (direction == 1)
    {
      // 3rd Dimension
      for (loop3 = 0; loop3 < MS; loop3++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop1 = 0; loop1 < MS; loop1++)
          {
            value_temp2 = (value_temp + (loop1 + loop2 + loop3) * jumper + loopm - 1) & B8;
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][loop3] = matrix[row1][loop1][loop2][loop3] + value_temp2; break;
              case 1: matrix[loop1][row1][loop2][loop3] = matrix[loop1][row1][loop2][loop3] + value_temp2; break;
              case 2: matrix[loop1][loop2][row1][loop3] = matrix[loop1][loop2][row1][loop3] + value_temp2; break;
              case 3: matrix[loop1][loop2][loop3][row1] = matrix[loop1][loop2][loop3][row1] + value_temp2; break;
            }
          }
        }
      }
      // 2nd Dimension
      for (loop2 = 0; loop2 < MS; loop2++)
      {
        for (loop1 = 0; loop1 < MS; loop1++)
        {
          value_temp2 = (value_temp + (loop1 + loop2) * jumper + loopm - 1) & B8;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][loop2] = matrix[row1][row2][loop1][loop2] + value_temp2; break;
            case 1: matrix[row1][loop1][row2][loop2] = matrix[row1][loop1][row2][loop2] + value_temp2; break;
            case 2: matrix[row1][loop1][loop2][row2] = matrix[row1][loop1][loop2][row2] + value_temp2; break;
            case 3: matrix[loop1][row1][row2][loop2] = matrix[loop1][row1][row2][loop2] + value_temp2; break;
            case 4: matrix[loop1][row1][loop2][row2] = matrix[loop1][row1][loop2][row2] + value_temp2; break;
            case 7:
            case 5: matrix[loop1][loop2][row1][row2] = matrix[loop1][loop2][row1][row2] + value_temp2; break;
          }
        }
      }
      // 1st Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        value_temp2 = (value_temp + (loop1) * jumper + loopm - 1) & B8;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1] = matrix[row1][row2][row3][loop1] + value_temp2; break;
          case 1: matrix[row1][row2][loop1][row3] = matrix[row1][row2][loop1][row3] + value_temp2; break;
          case 2: matrix[row1][loop1][row2][row3] = matrix[row1][loop1][row2][row3] + value_temp2; break;
          case 3: matrix[loop1][row1][row2][row3] = matrix[loop1][row1][row2][row3] + value_temp2; break;
        }
      }
    } // end else if
  } // end for
}
void decrementdecryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  if (PRINT_OUT_MODE == 1) {printf("DD ");}
  uchar row1,  row2, row3;
  uchar direction, dim1, dim2, dim3;
  uchar jumper, shifter, multiplier;
  uchar value, value_temp, value_temp2;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  uchar loop1,loop2, loop3, loopm;
  uchar value_temp_array[multiplier];
  for (loopm = 0; loopm < multiplier; loopm++)
  {
    if (loopm != 0)
    {
      value_temp_array[loopm] = value + (value_temp_array[loopm - 1] >> shifter) + (value_temp_array[loopm - 1] << shifter);
    }
    else
    {
      value_temp_array[loopm] = value + (0 >> shifter) + (0 << shifter);
    }
  }
  for (loopm = multiplier; loopm > 0; loopm--)
  {
    value_temp = value_temp_array[loopm - 1];
    if (direction == 0)
    {
      // 3rd Dimension
      for (loop3 = MS; loop3 > 0; loop3--)
      {
        for (loop2 = MS; loop2 > 0; loop2--)
        {
          for (loop1 = MS; loop1 > 0; loop1--)
          {
            value_temp2 = (value_temp + (loop1 - 1 + loop2 - 1 + loop3 - 1) * jumper + loopm - 1) & B8;
            switch (dim3)
            {
              case 0: matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] = matrix[row1][loop1 - 1][loop2 - 1][loop3 - 1] - value_temp2; break;
              case 1: matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] = matrix[loop1 - 1][row1][loop2 - 1][loop3 - 1] - value_temp2; break;
              case 2: matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] = matrix[loop1 - 1][loop2 - 1][row1][loop3 - 1] - value_temp2; break;
              case 3: matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] = matrix[loop1 - 1][loop2 - 1][loop3 - 1][row1] - value_temp2; break;
            }
          }
        }
      }
      // 2nd Dimension
      for (loop2 = MS; loop2 > 0; loop2--)
      {
        for (loop1 = MS; loop1 > 0; loop1--)
        {
          value_temp2 = (value_temp + (loop1 - 1 + loop2 - 1) * jumper + loopm - 1) & B8;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1 - 1][loop2 - 1] = matrix[row1][row2][loop1 - 1][loop2 - 1] - value_temp2; break;
            case 1: matrix[row1][loop1 - 1][row2][loop2 - 1] = matrix[row1][loop1 - 1][row2][loop2 - 1] - value_temp2; break;
            case 2: matrix[row1][loop1 - 1][loop2 - 1][row2] = matrix[row1][loop1 - 1][loop2 - 1][row2] - value_temp2; break;
            case 3: matrix[loop1 - 1][row1][row2][loop2 - 1] = matrix[loop1 - 1][row1][row2][loop2 - 1] - value_temp2; break;
            case 4: matrix[loop1 - 1][row1][loop2 - 1][row2] = matrix[loop1 - 1][row1][loop2 - 1][row2] - value_temp2; break;
            case 7:
            case 5: matrix[loop1 - 1][loop2 - 1][row1][row2] = matrix[loop1 - 1][loop2 - 1][row1][row2] - value_temp2; break;
          }
        }
      }
      // 1st Dimension
      for (loop1 = MS; loop1 > 0; loop1--)
      {
        value_temp2 = (value_temp + (loop1 - 1) * jumper + loopm - 1) & B8;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1 - 1] = matrix[row1][row2][row3][loop1 - 1] - value_temp2; break;
          case 1: matrix[row1][row2][loop1 - 1][row3] = matrix[row1][row2][loop1 - 1][row3] - value_temp2; break;
          case 2: matrix[row1][loop1 - 1][row2][row3] = matrix[row1][loop1 - 1][row2][row3] - value_temp2; break;
          case 3: matrix[loop1 - 1][row1][row2][row3] = matrix[loop1 - 1][row1][row2][row3] - value_temp2; break;
        }
      }
    } // end if
    else if (direction == 1)
    {
      // 3rd Dimension
      for (loop3 = 0; loop3 < MS; loop3++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop1 = 0; loop1 < MS; loop1++)
          {
            value_temp2 = (value_temp + (loop1 + loop2 + loop3) * jumper + loopm - 1) & B8;
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][loop3] = matrix[row1][loop1][loop2][loop3] - value_temp2; break;
              case 1: matrix[loop1][row1][loop2][loop3] = matrix[loop1][row1][loop2][loop3] - value_temp2; break;
              case 2: matrix[loop1][loop2][row1][loop3] = matrix[loop1][loop2][row1][loop3] - value_temp2; break;
              case 3: matrix[loop1][loop2][loop3][row1] = matrix[loop1][loop2][loop3][row1] - value_temp2; break;
            }
          }
        }
      }
      // 2nd Dimension
      for (loop2 = 0; loop2 < MS; loop2++)
      {
        for (loop1 = 0; loop1 < MS; loop1++)
        {
          value_temp2 = (value_temp + (loop1 + loop2) * jumper + loopm - 1) & B8;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][loop2] = matrix[row1][row2][loop1][loop2] - value_temp2; break;
            case 1: matrix[row1][loop1][row2][loop2] = matrix[row1][loop1][row2][loop2] - value_temp2; break;
            case 2: matrix[row1][loop1][loop2][row2] = matrix[row1][loop1][loop2][row2] - value_temp2; break;
            case 3: matrix[loop1][row1][row2][loop2] = matrix[loop1][row1][row2][loop2] - value_temp2; break;
            case 4: matrix[loop1][row1][loop2][row2] = matrix[loop1][row1][loop2][row2] - value_temp2; break;
            case 7:
            case 5: matrix[loop1][loop2][row1][row2] = matrix[loop1][loop2][row1][row2] - value_temp2; break;
          }
        }
      }
      // 1st Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        value_temp2 = (value_temp + (loop1) * jumper + loopm - 1) & B8;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1] = matrix[row1][row2][row3][loop1] - value_temp2; break;
          case 1: matrix[row1][row2][loop1][row3] = matrix[row1][row2][loop1][row3] - value_temp2; break;
          case 2: matrix[row1][loop1][row2][row3] = matrix[row1][loop1][row2][row3] - value_temp2; break;
          case 3: matrix[loop1][row1][row2][row3] = matrix[loop1][row1][row2][row3] - value_temp2; break;
        }
      }
    } // end else if
  } // end for
}
void shiftdecryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  if (PRINT_OUT_MODE == 1) {printf("SD ");}
  uchar row1,  row2, row3;
  uchar direction, dim1, dim2, dim3;
  uchar jumper, shifter, multiplier;
  uchar value, value_temp, value_temp2, value_temp3, value_gcd;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  uchar loop1, loop2, loop3, loopm, loop_s;
  value = jumper;jumper=value;
  if (shifter % 3 == 0) {shifter = 3;}
  else {shifter = shifter % 3;}
  value_gcd = gcd(MS, shifter);
  multiplier = multiplier % 4;
  for (loopm = 0; loopm < multiplier; loopm++)
  {
    if (direction == 0)
    {
      // 3rd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop3 = MS; loop3 > MS - value_gcd; loop3--)
          {
            switch (dim3)
            {
              case 0: value_temp = matrix[row1][loop1][loop2][loop3 - 1]; break;
              case 1: value_temp = matrix[loop1][row1][loop2][loop3 - 1]; break;
              case 2: value_temp = matrix[loop1][loop2][row1][loop3 - 1]; break;
              case 3: value_temp = matrix[loop1][loop2][loop3 - 1][row1]; break;
            }
            for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
            {
              value_temp2 = (uchar)(loop3 - 1 - loop_s * shifter) % MS;
              value_temp3 = (uchar)(loop3 - 1 - (loop_s + 1) * shifter) % MS;
              switch (dim3)
              {                
                case 0: matrix[row1][loop1][loop2][value_temp2] = matrix[row1][loop1][loop2][value_temp3]; break;
                case 1: matrix[loop1][row1][loop2][value_temp2] = matrix[loop1][row1][loop2][value_temp3]; break;
                case 2: matrix[loop1][loop2][row1][value_temp2] = matrix[loop1][loop2][row1][value_temp3]; break;
                case 3: matrix[loop1][loop2][value_temp2][row1] = matrix[loop1][loop2][value_temp3][row1]; break;
              }
            }
            value_temp2 = (uchar)(loop3 - 1 + shifter) % MS;
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][value_temp2] = value_temp; break;
              case 1: matrix[loop1][row1][loop2][value_temp2] = value_temp; break;
              case 2: matrix[loop1][loop2][row1][value_temp2] = value_temp; break;
              case 3: matrix[loop1][loop2][value_temp2][row1] = value_temp; break;
            }
          }
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = MS; loop2 > MS - value_gcd; loop2--)
        {
          switch (dim2)
          {
            case 6:
            case 0: value_temp = matrix[row1][row2][loop1][loop2 - 1]; break;
            case 1: value_temp = matrix[row1][loop1][row2][loop2 - 1]; break;
            case 2: value_temp = matrix[row1][loop1][loop2 - 1][row2]; break;
            case 3: value_temp = matrix[loop1][row1][row2][loop2 - 1]; break;
            case 4: value_temp = matrix[loop1][row1][loop2 - 1][row2]; break;
            case 7:
            case 5: value_temp = matrix[loop1][loop2 - 1][row1][row2]; break;
          }
          for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
          {
            value_temp2 = (uchar)(loop2 - 1 - loop_s * shifter) % MS;
            value_temp3 = (uchar)(loop2 - 1 - (loop_s + 1) * shifter) % MS;
            switch (dim2)
            {
              case 6:
              case 0: matrix[row1][row2][loop1][value_temp2] = matrix[row1][row2][loop1][value_temp3]; break;
              case 1: matrix[row1][loop1][row2][value_temp2] = matrix[row1][loop1][row2][value_temp3]; break;
              case 2: matrix[row1][loop1][value_temp2][row2] = matrix[row1][loop1][value_temp3][row2]; break;
              case 3: matrix[loop1][row1][row2][value_temp2] = matrix[loop1][row1][row2][value_temp3]; break;
              case 4: matrix[loop1][row1][value_temp2][row2] = matrix[loop1][row1][value_temp3][row2]; break;
              case 7:
              case 5: matrix[loop1][value_temp2][row1][row2] = matrix[loop1][value_temp3][row1][row2]; break;
            }
          }
          value_temp2 = (uchar)(loop2 - 1 + shifter) % MS;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][value_temp2] = value_temp; break;
            case 1: matrix[row1][loop1][row2][value_temp2] = value_temp; break;
            case 2: matrix[row1][loop1][value_temp2][row2] = value_temp; break;
            case 3: matrix[loop1][row1][row2][value_temp2] = value_temp; break;
            case 4: matrix[loop1][row1][value_temp2][row2] = value_temp; break;
            case 7:
            case 5: matrix[loop1][value_temp2][row1][row2] = value_temp; break;
          }
        }
      }
      // 1st Dimension
      for (loop1 = MS; loop1 > MS - value_gcd; loop1--)
      {
        switch (dim1)
        {
          case 0: value_temp = matrix[row1][row2][row3][loop1 - 1]; break;
          case 1: value_temp = matrix[row1][row2][loop1 - 1][row3]; break;
          case 2: value_temp = matrix[row1][loop1 - 1][row2][row3]; break;
          case 3: value_temp = matrix[loop1 - 1][row1][row2][row3]; break;
        }
        for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
        {
          value_temp2 = (uchar)(loop1 - 1 - loop_s * shifter) % MS;
          value_temp3 = (uchar)(loop1 - 1 - (loop_s + 1) * shifter) % MS;
          switch (dim1)
          {
            case 0: matrix[row1][row2][row3][value_temp2] = matrix[row1][row2][row3][value_temp3]; break;
            case 1: matrix[row1][row2][value_temp2][row3] = matrix[row1][row2][value_temp3][row3]; break;
            case 2: matrix[row1][value_temp2][row2][row3] = matrix[row1][value_temp3][row2][row3]; break;
            case 3: matrix[value_temp2][row1][row2][row3] = matrix[value_temp3][row1][row2][row3]; break;
          }
        }
        value_temp2 = (uchar)(loop1 - 1 + shifter) % MS;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][value_temp2] = value_temp; break;
          case 1: matrix[row1][row2][value_temp2][row3] = value_temp; break;
          case 2: matrix[row1][value_temp2][row2][row3] = value_temp; break;
          case 3: matrix[value_temp2][row1][row2][row3] = value_temp; break;
        }
      }
    } // end if
    else if (direction == 1)
    {
      // 1st Dimension
      for (loop1 = MS; loop1 > MS - value_gcd; loop1--)
      {
        switch (dim1)
        {
          case 0: value_temp = matrix[row1][row2][row3][loop1 - 1]; break;
          case 1: value_temp = matrix[row1][row2][loop1 - 1][row3]; break;
          case 2: value_temp = matrix[row1][loop1 - 1][row2][row3]; break;
          case 3: value_temp = matrix[loop1 - 1][row1][row2][row3]; break;
        }
        for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
        {
          value_temp2 = (uchar)(loop1 - 1 - loop_s * shifter) % MS;
          value_temp3 = (uchar)(loop1 - 1 - (loop_s + 1) * shifter) % MS;
          switch (dim1)
          {
            case 0: matrix[row1][row2][row3][value_temp2] = matrix[row1][row2][row3][value_temp3]; break;
            case 1: matrix[row1][row2][value_temp2][row3] = matrix[row1][row2][value_temp3][row3]; break;
            case 2: matrix[row1][value_temp2][row2][row3] = matrix[row1][value_temp3][row2][row3]; break;
            case 3: matrix[value_temp2][row1][row2][row3] = matrix[value_temp3][row1][row2][row3]; break;
          }
        }
        value_temp2 = (uchar)(loop1 - 1 + shifter) % MS;
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][value_temp2] = value_temp; break;
          case 1: matrix[row1][row2][value_temp2][row3] = value_temp; break;
          case 2: matrix[row1][value_temp2][row2][row3] = value_temp; break;
          case 3: matrix[value_temp2][row1][row2][row3] = value_temp; break;
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = MS; loop2 > MS - value_gcd; loop2--)
        {
          switch (dim2)
          {
            case 6:
            case 0: value_temp = matrix[row1][row2][loop1][loop2 - 1]; break;
            case 1: value_temp = matrix[row1][loop1][row2][loop2 - 1]; break;
            case 2: value_temp = matrix[row1][loop1][loop2 - 1][row2]; break;
            case 3: value_temp = matrix[loop1][row1][row2][loop2 - 1]; break;
            case 4: value_temp = matrix[loop1][row1][loop2 - 1][row2]; break;
            case 7:
            case 5: value_temp = matrix[loop1][loop2 - 1][row1][row2]; break;
          }
          for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
          {
            value_temp2 = (uchar)(loop2 - 1 - loop_s * shifter) % MS;
            value_temp3 = (uchar)(loop2 - 1 - (loop_s + 1) * shifter) % MS;
            switch (dim2)
            {
              case 6:
              case 0: matrix[row1][row2][loop1][value_temp2] = matrix[row1][row2][loop1][value_temp3]; break;
              case 1: matrix[row1][loop1][row2][value_temp2] = matrix[row1][loop1][row2][value_temp3]; break;
              case 2: matrix[row1][loop1][value_temp2][row2] = matrix[row1][loop1][value_temp3][row2]; break;
              case 3: matrix[loop1][row1][row2][value_temp2] = matrix[loop1][row1][row2][value_temp3]; break;
              case 4: matrix[loop1][row1][value_temp2][row2] = matrix[loop1][row1][value_temp3][row2]; break;
              case 7:
              case 5: matrix[loop1][value_temp2][row1][row2] = matrix[loop1][value_temp3][row1][row2]; break;
            }
          }
          value_temp2 = (uchar)(loop2 - 1 + shifter) % MS;
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][value_temp2] = value_temp; break;
            case 1: matrix[row1][loop1][row2][value_temp2] = value_temp; break;
            case 2: matrix[row1][loop1][value_temp2][row2] = value_temp; break;
            case 3: matrix[loop1][row1][row2][value_temp2] = value_temp; break;
            case 4: matrix[loop1][row1][value_temp2][row2] = value_temp; break;
            case 7:
            case 5: matrix[loop1][value_temp2][row1][row2] = value_temp; break;
          }
        }
      }
      // 3rd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop3 = MS; loop3 > MS - value_gcd; loop3--)
          {
            switch (dim3)
            {
              case 0: value_temp = matrix[row1][loop1][loop2][loop3 - 1]; break;
              case 1: value_temp = matrix[loop1][row1][loop2][loop3 - 1]; break;
              case 2: value_temp = matrix[loop1][loop2][row1][loop3 - 1]; break;
              case 3: value_temp = matrix[loop1][loop2][loop3 - 1][row1]; break;
            }
            for (loop_s = 0; loop_s < (MS / value_gcd - 1); loop_s++)
            {
              value_temp2 = (uchar)(loop3 - 1 - loop_s * shifter) % MS;
              value_temp3 = (uchar)(loop3 - 1 - (loop_s + 1) * shifter) % MS;
              switch (dim3)
              {                
                case 0: matrix[row1][loop1][loop2][value_temp2] = matrix[row1][loop1][loop2][value_temp3]; break;
                case 1: matrix[loop1][row1][loop2][value_temp2] = matrix[loop1][row1][loop2][value_temp3]; break;
                case 2: matrix[loop1][loop2][row1][value_temp2] = matrix[loop1][loop2][row1][value_temp3]; break;
                case 3: matrix[loop1][loop2][value_temp2][row1] = matrix[loop1][loop2][value_temp3][row1]; break;
              }
            }
            value_temp2 = (uchar)(loop3 - 1 + shifter) % MS;
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][value_temp2] = value_temp; break;
              case 1: matrix[loop1][row1][loop2][value_temp2] = value_temp; break;
              case 2: matrix[loop1][loop2][row1][value_temp2] = value_temp; break;
              case 3: matrix[loop1][loop2][value_temp2][row1] = value_temp; break;
            }
          }
        }
      }
    } // end else if
  } // end for
}
void invertdecryption(uchar matrix[MS][MS][MS][MS], int b1, int b2, int b3, int b4)
{
  if (PRINT_OUT_MODE == 1) {printf("VD ");}
  uchar row1, row2, row3;
  uchar direction, dim1, dim2, dim3;
  uchar jumper, shifter, multiplier;
  uchar value, value_temp;
  row1 = (b1 >> 4) & B2; row2 = (b1 >> 2) & B2; row3 = (b1 >> 0) & B2;
  direction = (b2 >> 7) & B1; dim1 = (b2 >> 5) & B2; dim2 = (b2 >> 2) & B3; dim3 = (b2 >> 0) & B2;
  jumper = (b3 >> 5) & B3; shifter = (b3 >> 2) & B3; multiplier = (b3 >> 0) & B2;
  value = b4 & B8;
  value = jumper; jumper = shifter; shifter = value;
  uchar loop1, loop2, loop3, loopm;
  multiplier = 1;
  for (loopm = 0; loopm < multiplier; loopm++)
  {
    if (direction == 0)
    {
      // 3rd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop3 = MS; loop3 > MS /2; loop3--)
          {
            switch (dim3)
            {
              case 0: value_temp = matrix[row1][loop1][loop2][loop3 - 1]; break;
              case 1: value_temp = matrix[loop1][row1][loop2][loop3 - 1]; break;
              case 2: value_temp = matrix[loop1][loop2][row1][loop3 - 1]; break;
              case 3: value_temp = matrix[loop1][loop2][loop3 - 1][row1]; break;
            }
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][loop3 - 1] = 0xFF - matrix[row1][loop1][loop2][MS - loop3]; break;
              case 1: matrix[loop1][row1][loop2][loop3 - 1] = 0xFF - matrix[loop1][row1][loop2][MS - loop3]; break;
              case 2: matrix[loop1][loop2][row1][loop3 - 1] = 0xFF - matrix[loop1][loop2][row1][MS - loop3]; break;
              case 3: matrix[loop1][loop2][loop3 - 1][row1] = 0xFF - matrix[loop1][loop2][MS - loop3][row1]; break;
            }
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][MS - loop3] = value_temp; break;
              case 1: matrix[loop1][row1][loop2][MS - loop3] = value_temp; break;
              case 2: matrix[loop1][loop2][row1][MS - loop3] = value_temp; break;
              case 3: matrix[loop1][loop2][MS - loop3][row1] = value_temp; break;
            }
          }
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = MS; loop2 > MS / 2; loop2--)
        {
          switch (dim2)
          {
            case 6:
            case 0: value_temp = matrix[row1][row2][loop1][loop2 - 1]; break;
            case 1: value_temp = matrix[row1][loop1][row2][loop2 - 1]; break;
            case 2: value_temp = matrix[row1][loop1][loop2 - 1][row2]; break;
            case 3: value_temp = matrix[loop1][row1][row2][loop2 - 1]; break;
            case 4: value_temp = matrix[loop1][row1][loop2 - 1][row2]; break;
            case 7:
            case 5: value_temp = matrix[loop1][loop2 - 1][row1][row2]; break;
          }
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][loop2 - 1] = 0xFF - matrix[row1][row2][loop1][MS - loop2]; break;
            case 1: matrix[row1][loop1][row2][loop2 - 1] = 0xFF - matrix[row1][loop1][row2][MS - loop2]; break;
            case 2: matrix[row1][loop1][loop2 - 1][row2] = 0xFF - matrix[row1][loop1][MS - loop2][row2]; break;
            case 3: matrix[loop1][row1][row2][loop2 - 1] = 0xFF - matrix[loop1][row1][row2][MS - loop2]; break;
            case 4: matrix[loop1][row1][loop2 - 1][row2] = 0xFF - matrix[loop1][row1][MS - loop2][row2]; break;
            case 7:
            case 5: matrix[loop1][loop2 - 1][row1][row2] = 0xFF - matrix[loop1][MS - loop2][row1][row2]; break;
          }
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][MS - loop2] = value_temp; break;
            case 1: matrix[row1][loop1][row2][MS - loop2] = value_temp; break;
            case 2: matrix[row1][loop1][MS - loop2][row2] = value_temp; break;
            case 3: matrix[loop1][row1][row2][MS - loop2] = value_temp; break;
            case 4: matrix[loop1][row1][MS - loop2][row2] = value_temp; break;
            case 7:
            case 5: matrix[loop1][MS - loop2][row1][row2] = value_temp; break;
          }
        }
      }
      // 1st Dimension
      for (loop1 = MS; loop1 > MS / 2; loop1--)
      {
        switch (dim1)
        {
          case 0: value_temp = matrix[row1][row2][row3][loop1 - 1]; break;
          case 1: value_temp = matrix[row1][row2][loop1 - 1][row3]; break;
          case 2: value_temp = matrix[row1][loop1 - 1][row2][row3]; break;
          case 3: value_temp = matrix[loop1 - 1][row1][row2][row3]; break;
        }
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1 - 1] = 0xFF - matrix[row1][row2][row3][MS - loop1]; break;
          case 1: matrix[row1][row2][loop1 - 1][row3] = 0xFF - matrix[row1][row2][MS - loop1][row3]; break;
          case 2: matrix[row1][loop1 - 1][row2][row3] = 0xFF - matrix[row1][MS - loop1][row2][row3]; break;
          case 3: matrix[loop1 - 1][row1][row2][row3] = 0xFF - matrix[MS - loop1][row1][row2][row3]; break;
        }
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][MS - loop1] = value_temp; break;
          case 1: matrix[row1][row2][MS - loop1][row3] = value_temp; break;
          case 2: matrix[row1][MS - loop1][row2][row3] = value_temp; break;
          case 3: matrix[MS - loop1][row1][row2][row3] = value_temp; break;
        }
      }
    } // end if
    else if (direction == 1)
    {
      // 3rd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS; loop2++)
        {
          for (loop3 = 0; loop3 < MS / 2; loop3++)
          {
            switch (dim3)
            {
              case 0: value_temp = matrix[row1][loop1][loop2][loop3]; break;
              case 1: value_temp = matrix[loop1][row1][loop2][loop3]; break;
              case 2: value_temp = matrix[loop1][loop2][row1][loop3]; break;
              case 3: value_temp = matrix[loop1][loop2][loop3][row1]; break;
            }
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][loop3] = 0xFF - matrix[row1][loop1][loop2][MS - 1 - loop3]; break;
              case 1: matrix[loop1][row1][loop2][loop3] = 0xFF - matrix[loop1][row1][loop2][MS - 1 - loop3]; break;
              case 2: matrix[loop1][loop2][row1][loop3] = 0xFF - matrix[loop1][loop2][row1][MS - 1 - loop3]; break;
              case 3: matrix[loop1][loop2][loop3][row1] = 0xFF - matrix[loop1][loop2][MS - 1 - loop3][row1]; break;
            }
            switch (dim3)
            {
              case 0: matrix[row1][loop1][loop2][MS - 1 - loop3] = value_temp; break;
              case 1: matrix[loop1][row1][loop2][MS - 1 - loop3] = value_temp; break;
              case 2: matrix[loop1][loop2][row1][MS - 1 - loop3] = value_temp; break;
              case 3: matrix[loop1][loop2][MS - 1 - loop3][row1] = value_temp; break;
            }
          }
        }
      }
      // 2nd Dimension
      for (loop1 = 0; loop1 < MS; loop1++)
      {
        for (loop2 = 0; loop2 < MS / 2; loop2++)
        {
          switch (dim2)
          {
            case 6:
            case 0: value_temp = matrix[row1][row2][loop1][loop2]; break;
            case 1: value_temp = matrix[row1][loop1][row2][loop2]; break;
            case 2: value_temp = matrix[row1][loop1][loop2][row2]; break;
            case 3: value_temp = matrix[loop1][row1][row2][loop2]; break;
            case 4: value_temp = matrix[loop1][row1][loop2][row2]; break;
            case 7:
            case 5: value_temp = matrix[loop1][loop2][row1][row2]; break;
          }
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][loop2] = 0xFF - matrix[row1][row2][loop1][MS - 1 - loop2]; break;
            case 1: matrix[row1][loop1][row2][loop2] = 0xFF - matrix[row1][loop1][row2][MS - 1 - loop2]; break;
            case 2: matrix[row1][loop1][loop2][row2] = 0xFF - matrix[row1][loop1][MS - 1 - loop2][row2]; break;
            case 3: matrix[loop1][row1][row2][loop2] = 0xFF - matrix[loop1][row1][row2][MS - 1 - loop2]; break;
            case 4: matrix[loop1][row1][loop2][row2] = 0xFF - matrix[loop1][row1][MS - 1 - loop2][row2]; break;
            case 7:
            case 5: matrix[loop1][loop2][row1][row2] = 0xFF - matrix[loop1][MS - 1 - loop2][row1][row2]; break;
          }
          switch (dim2)
          {
            case 6:
            case 0: matrix[row1][row2][loop1][MS - 1 - loop2] = value_temp; break;
            case 1: matrix[row1][loop1][row2][MS - 1 - loop2] = value_temp; break;
            case 2: matrix[row1][loop1][MS - 1 - loop2][row2] = value_temp; break;
            case 3: matrix[loop1][row1][row2][MS - 1 - loop2] = value_temp; break;
            case 4: matrix[loop1][row1][MS - 1 - loop2][row2] = value_temp; break;
            case 7:
            case 5: matrix[loop1][MS - 1 - loop2][row1][row2] = value_temp; break;
          }
        }
      }
      // 1st Dimension
      for (loop1 = 0; loop1 < MS / 2; loop1++)
      {
        switch (dim1)
        {
          case 0: value_temp = matrix[row1][row2][row3][loop1]; break;
          case 1: value_temp = matrix[row1][row2][loop1][row3]; break;
          case 2: value_temp = matrix[row1][loop1][row2][row3]; break;
          case 3: value_temp = matrix[loop1][row1][row2][row3]; break;
        }
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][loop1] = 0xFF - matrix[row1][row2][row3][MS - 1 - loop1]; break;
          case 1: matrix[row1][row2][loop1][row3] = 0xFF - matrix[row1][row2][MS - 1 - loop1][row3]; break;
          case 2: matrix[row1][loop1][row2][row3] = 0xFF - matrix[row1][MS - 1 - loop1][row2][row3]; break;
          case 3: matrix[loop1][row1][row2][row3] = 0xFF - matrix[MS - 1 - loop1][row1][row2][row3]; break;
        }
        switch (dim1)
        {
          case 0: matrix[row1][row2][row3][MS - 1 - loop1] = value_temp; break;
          case 1: matrix[row1][row2][MS - 1 - loop1][row3] = value_temp; break;
          case 2: matrix[row1][MS - 1 - loop1][row2][row3] = value_temp; break;
          case 3: matrix[MS - 1 - loop1][row1][row2][row3] = value_temp; break;
        }
      }
    } // end else if
  } // end for
}