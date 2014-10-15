#include <string.h>

#include "encraption.h"
#include "utils.h"

int main(int argc, char **argv)
{
  int flag_encrypt;
  if (argc != 5)
  {
    exitWithError(ERR_WRONG_USAGE, NULL);
  }

  if (((argv[3][0] != 'e') && (argv[3][0] != 'd')) || strlen(argv[3]) > 1) //only allow e or d, should use glib options
  {
    exitWithError(ERR_NO_MODE, NULL);
  }
  else
  {
     flag_encrypt = argv[3][0] == 'e'; //warning: this is evil. You really should use glib options
  }

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
    exitWithError(ERR_FILE_NOT_FOUND, file_name_in);
  }
  else if (file_crypt == NULL)
  {
    exitWithError(ERR_FILE_NOT_FOUND, file_name_crypt);
  }
  else
  {
    printf("Files OK!\n");
  }

  array_length_in = fileSize(file_in);
  array_length_crypt = fileSize(file_crypt);

  array_in = (unsigned char*) malloc(sizeof(char) * array_length_in);
  if (array_in == NULL)
  {
    fclose(file_in);
    fclose(file_crypt);
    exitWithError(ERR_NO_MEM, NULL);
  }
  array_crypt = (unsigned char*) malloc(sizeof(char) * array_length_crypt);
  if (array_crypt == NULL)
  {
    fclose(file_in);
    fclose(file_crypt);
    free(array_in),
    exitWithError(ERR_NO_MEM, NULL);
  }

  fread(array_in, array_length_in, sizeof(char), file_in);
  fread(array_crypt, array_length_crypt, sizeof(char), file_crypt);
  fclose(file_in);
  fclose(file_crypt);

  printf("File in:\n");
  printArray(array_in, array_length_in);
  printf("Crypt:\n");
  printArray(array_crypt, array_length_crypt);

  if (flag_encrypt)
  {
    algorithmEncrypt(array_in, array_length_in, array_crypt, array_length_crypt);
  }
  else
  {
    algorithmDecrypt(array_in, array_length_in, array_crypt, array_length_crypt);
  }

  printf("Array Out:\n");
  printArray(array_in, array_length_in);

  FILE *file_out = fopen(file_name_out, "wb");
  fwrite(array_in, array_length_in, sizeof(char), file_out);
  fclose(file_out);
  free(array_in);
  free(array_crypt);
  printf("Finish!\n");
  return 0;
}
