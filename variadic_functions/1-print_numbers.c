#include <stdio.h>
#include <stdarg.h>

/**
 * print_numbers - prints integers separated by a given string
 * @separator: string printed between the numbers
 * @n: number of integers to print
 */

void print_numbers(const char *separator, const unsigned int n, ...)
{
	va_list ap;
	unsigned int i = 0;
	int data;

	if (n == 0)
	{
		printf("\n");
		return;
	}

	va_start(ap, n);

	while (i < n)
	{
		data = va_arg(ap, int);
		if (i > 0 && separator != NULL)
		{
			printf("%s", separator);
		}
		printf("%d", data);

		i++;
	}
	printf("\n");
	va_end(ap);
}
