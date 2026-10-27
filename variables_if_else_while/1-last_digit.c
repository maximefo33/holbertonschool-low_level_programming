#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/**
 * main - Checks the last digit of a random number.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int n;
	int N;

	srand(time(0));
	n = rand() - RAND_MAX / 2;

	/* N récupère le dernier chiffre (garde son signe - s'il existe) */
	N = n % 10;

	/* 1. On filtre d'abord le zéro */
	if (N == 0)
	{
		printf("Last digit of %d is %d and is 0\n", n, N);
	}
	/* 2. On filtre les nombres strictement supérieurs à 5 */
	else if (N > 5)
	{
		printf("Last digit of %d is %d and is greater than 5\n", n, N);
	}
	/* 3. Tout le reste entre ici automatiquement (y compris les négatifs) */
	else
	{
		printf("Last digit of %d is %d and is less than 6 "
		       "and not 0\n",
		       n, N);
	}

	return (0);
}
