#include "main.h"
#include <stdio.h>

/**
 * reset_to_98 - Changes the value of the integer pointed to by n to 98.
 * @n: Pointer to the integer variable to be modified.
 *
 * Return: Nothing.
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
