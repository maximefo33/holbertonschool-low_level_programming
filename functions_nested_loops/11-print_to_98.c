#include "main.h"
#include <stdio.h>

/**
 * add - adds two integers
 * @n: first integer
 * @m: second integer
 *
 * Return: the sum of n and m
 */
void print_to_98(int n)
{
	for (; n <= 98; n++)
	{
		if (n != 98)
		{
			printf("%d, ", n);
		}
		else
		{
			printf("%d\n", n);
		}
	}
}
