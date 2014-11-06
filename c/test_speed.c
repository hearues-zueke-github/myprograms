#include <stdio.h>

int main(int argc, char **argv)
{
	long long i;
	long long sum1 = 0;
	long long sum2 = 0;
	for (i = 0; i < 100000000; i++)
	{
		if (i == 1)
		{
			sum1++;
		}
		/*else if (i != 1)
		{
			sum1++;
		}*/
		else
		{
			sum2++;
		}
	}
	printf("%lld  %lld\n", sum1, sum2);
  return 0;
}