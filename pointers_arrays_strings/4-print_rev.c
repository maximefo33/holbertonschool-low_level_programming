#include "main.h"

void print_rev(char *s)
{
	// On récupère directement la taille grâce à l'exercice précédent
	int i = _strlen(s);

	// On part directement du dernier caractère et on recule
	for (i = i - 1; i >= 0; i--)
	{
		_putchar(s[i]);
	}
	_putchar('\n');
}
