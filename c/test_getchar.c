#include <stdio.h>

int main(int argc, char **argv)
{
	char input;
	input = getchar();
	while (input != 'a')
	{
		printf("%c", input);
		input = getchar();
	}
	return 0;
}