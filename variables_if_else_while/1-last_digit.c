#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - Checks if a random number is positive, negative or zero.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int n;
	srand(time(0));
	n = rand() - RAND_MAX / 2;
	int N = abs(n) % 10;
	if (N > 5)
	{
		printf("Last digit of %d is %d and is greater than 5\n", n, N);
	}
	else if (N < 0)
	{
		printf("Last digit of %d is %d and is 0\n", n, N);
	}
	else if (N < 6 && N != 0)
	{
		printf("Last digit of %d is %d and is less than 6 and not 0\n", n, N);
	}
	else
	{
	}

	return (0);
}