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

	/* On récupère le dernier chiffre */
	N = n % 10;

	/* Si le dernier chiffre est négatif, on le rend positif */
	if (N < 0)
	{
		N = -N;
	}

	/* Gestion des conditions sans utiliser l'opérateur && */
	if (N > 5)
	{
		printf("Last digit of %d is %d and is greater than 5\n", n, N);
	}
	else if (N == 0)
	{
		printf("Last digit of %d is %d and is 0\n", n, N);
	}
	else
	{
		/* Ici, N est obligatoirement inférieur à 6 et différent de 0 */
		printf("Last digit of %d is %d and is less than 6 and not 0\n", n, N);
	}

	return (0);
}
