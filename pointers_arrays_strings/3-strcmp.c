#include "main.h"
/**
 * _strcmp - Compare deux chaînes de caractères.
 * @s1: Pointeur vers la première chaîne à comparer.
 * @s2: Pointeur vers la deuxième chaîne à comparer.
 *
 * Return:
 *   - Une valeur positive (> 0) si s1 est supérieure à s2.
 *   - Une valeur négative (< 0) si s1 est inférieure à s2.
 *   - 0 si les deux chaînes sont parfaitement identiques.
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{

		s1++;
		s2++;
	}

	if (*s1 > *s2)
	{
		return (1);
	}
	else if (*s1 < *s2)
	{
		return (-1);
	}

	return (0);
}
