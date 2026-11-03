#include "main.h"
#include <stdio.h>

/**
 * _strlen - Counts the number of characters in a string.
 * @s: Pointer to the string to be measured.
 *
 * Return: The number of characters in the string.
 */

int _strlen(char *s)
{
	int compteur = 0;

	while (*s != '\0')
	{
		s++;
		compteur++;
	}
	return (compteur);
}
