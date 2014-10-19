#include <stdio.h>

int main(int argc, char **argv)
{
  int a = 1;
	switch (a)
	{
		case 1:case 2:
      printf("switch 1 and 2\n");
		  break;
    case 3:
      printf("switch 3\n");
      break;
	}
	return 0;
}