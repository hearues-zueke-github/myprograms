#include <stdio.h>

void foo2(int matrix[4][4][4][4])
{
	matrix[2][1][3][0] = 6;
}

void foo(int matrix[4][4][4][4])
{
	foo2(matrix);
}

int main(int argc, char **argv)
{
	int matrix[4][4][4][4];
	matrix[2][1][3][0] = 3;
	printf("matrix[2][1][3][0] = %d\n", matrix[2][1][3][0]);
	foo(matrix);
	printf("matrix[2][1][3][0] = %d\n", matrix[2][1][3][0]);
	return 0;
}