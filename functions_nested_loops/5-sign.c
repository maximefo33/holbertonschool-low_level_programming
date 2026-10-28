#include "main.h"
/**
 * print_sign - Affiche le signe d'un nombre
 * @n: Le nombre entier a verifier
 *
 * Return: 1 si positif, 0 si nul, -1 si negatif
 */

int print_sign(int n)
{
	if (n > 0)
	{
		_putchar('+');
		return (1);
	}
	else if (n == 0)
	{
		_putchar('0');
		return (0);
	}
	else
	{
		_putchar('-');
		return (-1);
	}
}
