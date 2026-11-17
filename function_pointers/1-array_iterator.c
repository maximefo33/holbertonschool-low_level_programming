#include <stdio.h>

/**
 * array_iterator - executes a function on each element of an array
 * @array: array of integers
 * @size: number of elements in the array
 * @action: pointer to the function to execute on each element
 *
 * Return: Nothing.
 */

void array_iterator(int *array, size_t size, void (*action)(int))
{
	int i = 0;

	while (i != size)
	{
		action(array[i]);
		i++;
	}
}
