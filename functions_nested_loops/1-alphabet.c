#include "main.h"

/**
 * print_alphabet - Affiche l'alphabet en minuscules
 *
 * Return: void
 */
void print_alphabet(void)
{
	char lettre = 'a';

	while (lettre <= 'z')
	{
		_putchar(lettre);
		lettre++;
	}
	_putchar('\n');
}
