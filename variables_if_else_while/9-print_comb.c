/**
 * main - Point d'entrée du programme
 *
 * Description: Affiche l'alphabet en minuscules suivi d'un retour à la ligne
 * Return: Toujours 0 (Succès)
 */
#include <stdio.h>

int main(void)
{
	int symbole = 0;

	while (symbole <= 9)
	{
		putchar(symbole + '0');

		if (symbole < 9)
		{
			putchar(',');
			putchar(' ');
		}
		symbole++;
	}
	putchar('\n');
	return (0);
}
