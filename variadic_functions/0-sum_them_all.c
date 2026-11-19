#include <stdarg.h>

/**
 * sum_them_all - adds all the integers passed as arguments
 * @n: number of integers to add
 *
 * Return: the sum of all integers, or 0 if n is 0
 */

int sum_them_all(const unsigned int n, ...)
{
	va_list ap;
	unsigned int i = 0;
	int data;
	int somme = 0;

	if (n == 0)
	{
		return (0);
	}

	va_start(ap, n);

	while (i < n)

	{
		data = va_arg(ap, int);
		somme = somme + data;
		i++;
	}
	va_end(ap);
	return (somme);
}
