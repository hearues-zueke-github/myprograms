#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NUMBER_ALGORITHM
#define FILE_CRYPT_SIZE_MAX 4194304

#define ERR_WRONG_USAGE 1
#define ERR_NO_MODE 2
#define ERR_FILE_NOT_FOUND 3

void waitForEnter();
size_t fileSize(FILE *file);

int main (int argc, char **argv)
{
  int flag_cryptmodus;
  int flag_output_status = 1;
  char matrix[2][2][2][2];
  char crypt[4194304];
  int file_crypt_size;
  long long file_in_size;
  long long file_in_position;
  char char_temp;
  if (argc < 4)
  {
    printf("Wrong usage: <program> <crypt_modus> <file_crypt> <file_in>...\n");
    waitForEnter();
    return 1;
  }
  if ((strlen(argv[1]) > 1) || (argv[1][0] != 'e') && (argv[1][0] != 'd'))
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
  fclose(file_crypt);
  if (file_crypt_size > FILE_CRYPT_SIZE_MAX)
  {
    printf("Crypt File is too big! It should not be bigger than 4 MiB!\n");
    fclose(file_crypt);
    return 3;
  }
  fread(crypt, file_crypt_size, sizeof(char), file_crypt);
  if (flag_output_status == TRUE)
  {
    printf("Files OK!\n");
    printf("Modus: %d\n", flag_cryptmodus);
  }
  int loop_file = 3;
  if (flag_cryptmodus == 1) { // encryption
    while (loop_file < argc) {
      FILE *file_in = fopen(argv[loop_file], "rb");
      char filenamedest[strlen(argv[loop_file]) + 8];
      strcpy(filenamedest, "output/");
      strcat(filenamedest, argv[loop_file]);
      FILE *file_out = fopen(filenamedest, "wb");
      if (file_in != NULL) {
        // Hier kann man dann ruhig beginnen zu progen!!!
        file_in_size = fileSize(file_in);
        fputc((file_in_size >> 56) & 0xFF, file_out);
        fputc((file_in_size >> 48) & 0xFF, file_out);
        fputc((file_in_size >> 40) & 0xFF, file_out);
        fputc((file_in_size >> 32) & 0xFF, file_out);
        fputc((file_in_size >> 24) & 0xFF, file_out);
        fputc((file_in_size >> 16) & 0xFF, file_out);
        fputc((file_in_size >> 8 ) & 0xFF, file_out);
        fputc(file_in_size & 0xFF, file_out);
        file_in_position = 0;
        while (file_in_position < file_in_size) {
          int pos = 0;
          char c;
          for(; pos < 256 && (c = fgetc(file_in)); pos++) {
            matrix[pos / 8][pos / 4][pos / 2][pos % 2] = c;
          }
          file_in_position += pos + 1;
          if (pos > 0) {
            fwrite(matrix, pos, sizeof(char), file_out);
          }
        }
        fclose(file_in);
        fclose(file_out);
      }
      else
      {
        printf("File %d is not found!\n", argv[loop_file]);
      }  
      loop_file++;
    }
  }
  else if (flag_cryptmodus == 2) { // decryption
    while (loop_file <= argc) {
      FILE *file_in = fopen(argv[loop_file], "rb");
      char filenamedest[strlen(argv[loop_file]) + 8];
      strcpy(filenamedest, "output/");
      strcat(filenamedest, argv[loop_file]);
      FILE *file_out = fopen(filenamedest, "wb");
      if (file_in != NULL) {
        // Hier kann man dann ruhig beginnen zu progen!!!
        file_in_size = fileSize(file_in);

        fclose(file_in);
      }
      loop_file++;
    }
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