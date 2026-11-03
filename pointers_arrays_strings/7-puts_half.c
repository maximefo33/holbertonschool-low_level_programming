#include "main.h"

/**
 * puts_half - Prints the second half of a string.
 * @str: Pointer to the string to be printed.
 *
 * Return: Nothing.
 */
void puts_half(char *str)
{
	int i = 0;
	int compter = 0;

	while (str[i] != '\0')
	{
		compter++;
		i++;
	}
	i = (compter + 1) / 2;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
	_putchar('\n');
}
