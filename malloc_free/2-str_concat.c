#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * str_concat - Concatenates two strings into a newly allocated memory space.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: A pointer to the concatenated string, or NULL if allocation fails.
 * NULL strings are treated as empty strings.
 */

char *str_concat(char *s1, char *s2)
{
	char *result = s1;
	int len1 = 0;
	int len2 = 0;
	int i;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	while (s1[len1] != '\0')
	{

		len1++;
	}

	while (s2[len2] != '\0')
	{
		len2++;
	}

	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		return (NULL);
	}

	i = 0;

	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}

	while (i < (len1 + len2))
	{
		result[i] = s2[i - len1];
		i++;
	}

	result[i] = '\0';

	return (result);
}
