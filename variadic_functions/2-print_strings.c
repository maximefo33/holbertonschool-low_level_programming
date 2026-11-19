#include <stdio.h>
#include <stdarg.h>

/**
 * print_strings - prints strings separated by a given string
 * @separator: string printed between the strings
 * @n: number of strings to print
 */

void print_strings(const char *separator, const unsigned int n, ...)
{
	va_list ap;
	unsigned int i = 0;
	char *data;

	if (n == 0)
	{
		printf("\n");
		return;
	}

	va_start(ap, n);

	while (i < n)
	{
		data = va_arg(ap, char *);

		if (i > 0 && separator != NULL)
		{
			printf("%s", separator);
		}

		if (data != NULL)
		{
			printf("%s", data);
		}
		else if (data == NULL)
		{
			printf("(nil)");
		}
		i++;
	}
	printf("\n");
	va_end(ap);
}
