#include "../main.h"
#include <stdio.h>

/**
 * main - Point d'entrée pour tester la fonction _strncpy
 *
 * Return: Toujours 0.
 */
int main(void)
{
	char dest[6] = "p";
	char src[] = "bonjout"; /* 1. Ajout des crochets [] */
	int n = 6;

	/* 2 & 3. Appel de la fonction avec ses arguments */
	_strncpy(dest, src, n);

	printf("%s\n", dest);

	return (0);
}
