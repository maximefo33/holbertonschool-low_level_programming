#include "main.h"

/**
 * times_table - Prints the 9 times table
 *
 * Return: Nothing
 */
void times_table(void)
{
	int conteur;
	int i;

	for (i = 0; i <= 9; i++)
	{
		for (conteur = 0; conteur < 10; conteur++)
		{
			int resulta;
			int unite;
			int dizaine;

			resulta = i * conteur;
			unite = resulta % 10;
			dizaine = resulta / 10;

			if (resulta >= 10)
			{
				_putchar(dizaine + '0');
			}
			_putchar(unite + '0');
			if (conteur < 9)
			{
				_putchar(',');
				_putchar(' ');
			}
		}
		_putchar('\n');
	}
}
