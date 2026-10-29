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
	int resulta;

	for (i = 0; i <= 9; i++)
	{
		for (conteur = 0; conteur <= 9; conteur++)
		{
			resulta = i * conteur;

			if (conteur == 0)
			{
				_putchar(resulta + '0');
			}
			else
			{
				_putchar(',');
				_putchar(' ');
				if (resulta < 10)
				{
					_putchar(' ');
					_putchar(resulta + '0');
				}
				else
				{
					_putchar((resulta / 10) + '0');
					_putchar((resulta % 10) + '0');
				}
			}
		}
		_putchar('\n');
	}
}
