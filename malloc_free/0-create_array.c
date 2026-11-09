#include <stdlib.h>

/**
 * create_array - Creates an array of chars initialized with a specific char.
 * @size: The size of the array to create.
 * @c: The character used to initialize each element.
 *
 * Return: A pointer to the array, or NULL if size is 0 or allocation fails.
 */

char *create_array(unsigned int size, char c)
{

	char *arr;
	unsigned int i;

	if (size == 0)
	{
		return (NULL);
	}

	arr = malloc(sizeof(char) * size);
	if (arr == NULL)
	{
		return (NULL);
		;
	}

	i = 0;

	while (i < size)
	{
		arr[i] = c;
		i++;
	}

	return (arr);
}
