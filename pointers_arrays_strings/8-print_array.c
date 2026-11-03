#include "main.h"

/**
 * print_array - Prints n elements of an array of integers,
 *               followed by a new line.
 * @a: Pointer to the array of integers to be printed.
 * @n: Number of elements of the array to be printed.
 *
 * Return: Nothing.
 */

void print_array(int *a, int n)
{

	int i = 0;
	while (i < n)
	{
		printf("%d", a[i]);
		printf(",");
		printf(" ");
		i++;
	}
}
