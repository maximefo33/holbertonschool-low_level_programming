#include "main.h"
/**
 * _strncpy - Copies a string using at most n bytes.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 * @n: The maximum number of bytes to copy.
 *
 * Return: A pointer to the original destination string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	char *result = dest;

	while (*src != '\0' && n > 0)
	{

		*dest = *src;
		src++;
		dest++;
		n--;
	}
	while (n != 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}

	return (result);
}
