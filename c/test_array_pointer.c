#include <stdio.h>

int main(int argc, char **argv)
{
	int array[4];
	printf(" array = %d\n", array);
	printf("*array = %d\n", *array);
	printf("*(&array) = %d\n", *(&array));
	printf("&array = %d\n", &array);
	printf("&array[0] = %d\n", &array[0]);
	return 0;
}