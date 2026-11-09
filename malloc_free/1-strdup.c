#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _strdup - Duplicates a string into a newly allocated memory space.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string, or NULL if str is NULL
 * or if memory allocation fails.
 */

char *_strdup(char *str)
{
	char *result = str;
	int len = 0;
	int i;

	if (str == 0)
	{
		return (NULL);
	}

	while (str[len] != '\0')
	{

		len++;
	}

	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
	{
		return (NULL);
	}

	i = 0;

	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}
