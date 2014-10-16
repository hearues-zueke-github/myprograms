#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NUMBER_ALGORITHM

#define ERR_WRONG_USAGE 1
#define ERR_NO_MODE 2
#define ERR_FILE_NOT_FOUND 3

void waitForEnter();
size_t fileSize(FILE *file);

int main (int argc, char **argv)
{
    int flag_cryptmodus;
    int flag_output_status = 1;
    char quad[2][2][2][2];
    char crypt[4194304];
    int file_crypt_size_max = 4194304;
    int file_crypt_size;
    int file_in_size;
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
    if (file_crypt_size > file_crypt_size_max)
    {
        printf("Crypt File is too big! It should not be bigger than 4 MiB!\n");
        fclose(file_crypt);
        return 3;
    }
    if (flag_output_status == TRUE)
    {
        printf("Files OK!\n");
        printf("Modus: %d\n", flag_cryptmodus);
    }
    int loop_file = 3;
    while (loop_file <= argc)
    {
        FILE *file_in = fopen(argv[loop_file], "rb");
        if (file_in != NULL)
        {
            // Hier kann man dann ruhig beginnen zu progen!!!
            
            fclose(file_in);
        }
        loop_file++;
    }
    fclose(file_crypt);
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