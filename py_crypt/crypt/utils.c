#include "utils.h"

void exitWithError(int e, void *details)
{
  switch(e)
  {
    case ERR_WRONG_USAGE: 
      printf("Wrong usage: <program> <file_in> <file_crypt> <crypt_mode> <file_out>\n");
      break;
    case ERR_NO_MODE: 
      printf("No mode specified. Use 'e' for encryption or 'd' for decryption.\n");
      break;
    case ERR_NO_MEM: 
      printf("No more memory!\n");
      break;
    case ERR_FILE_NOT_FOUND:
      printf("File not found: %s", (char *)details);
    default:
      printf("Something happened and the devs were too lazy to write appropriate error messages.\n");
      break;
  }
  exit(e);
}

size_t fileSize(FILE *file)
{
  size_t offset = ftell(file);
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, SEEK_SET, offset);
  return size;
}

void printArray(unsigned char *array, int array_length)
{
  int loop;
  loop = 0;
  while (loop < array_length)
  {
    printf("%02x ", array[loop]);
    if ((loop % 16 == 15))
    {
      printf("\n");
    }
    loop++;
  }
  printf("\n");
}
