#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	char *result;
	unsigned int len1 = 0, len2 = 0, i;

	if (s1 == NULL)
		s1 = "";
	while (s1[len1] != '\0')
		len1++;
	if (s2 == NULL)
		s2 = "";
	while (s2[len2] != '\0' && len2 < n)
		len2++;
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
