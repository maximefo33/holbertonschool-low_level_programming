#include "main.h"

void print_alphabet_x10(void)
{
	char lettre;
	int i = 0;

	while (i < 10)
	{
		lettre = 'a';

		while (lettre <= 'z')
		{
			_putchar(lettre);
			lettre++;
		}

		_putchar('\n');
		i++;
	}
}
