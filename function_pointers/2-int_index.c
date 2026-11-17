#include <stdio.h>

/**
 * int_index - searches for the first element matching a condition
 * @array: array of integers to search
 * @size: number of elements in the array
 * @cmp: pointer to the comparison function
 *
 * Return: index of the first matching element, or -1 if none is found.
 */

int int_index(int *array, int size, int (*cmp)(int))
{
	int i = 0;

	if (size <= 0)
	{
		return (-1);
	}

	while (i != size)
	{
		if (cmp(array[i]) != 0)
		{
			return (i);
		}

		i++;
	}
	return (-1);
}
