#include "main.h"

/**
 * _atoi - Converts a string to an integer.
 * @s: Pointer to the string to convert.
 *
 * Return: The integer value, or 0 if no numbers are found.
 */
int _atoi(char *s)
{
	int sinb = 0;
	int result = 0;
	int found_digit = 0;

	while (*s != '\0')
	{
		if (*s == '-')
		{
			sinb++;
		}
		else if (*s >= '0' && *s <= '9')
		{
			found_digit = 1;
			/* On construit le nombre en négatif pour éviter l'overflow de INT_MIN */
			if (sinb % 2 != 0)
			{
				result = result * 10 - (*s - '0');
			}
			else
			{
				result = result * 10 + (*s - '0');
			}
		}
		else if (found_digit == 1)
		{
			/* On s'arrête dès qu'un caractère non-numérique suit les chiffres */
			break;
		}
		s++;
	}

	return (result);
}
